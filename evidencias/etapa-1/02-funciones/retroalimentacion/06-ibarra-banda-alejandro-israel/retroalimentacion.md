# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 06 — Ibarra Banda Alejandro Israel

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** Compila sin errores. El compilador advierte que la constante LIMITE_DESC_1 nunca se usa.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 5 piezas × $100.00 | Subtotal 500.00, descuento 0.00, IVA 80.00, total 580.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 60 piezas × $50.00 | Subtotal 3000.00, descuento 360.00, IVA 422.40, total 3062.40 | Idéntico al esperado | ✅ |
| Límite superior del rango 1 | 9 piezas × $100.00 | Descuento 0.00, total 1044.00 | Idéntico al esperado | ✅ |
| Límite inferior del rango 2 | 10 piezas × $100.00 | Descuento 50.00 (5%), total 1102.00 | Idéntico al esperado | ✅ |
| Límite superior del rango 2 | 49 piezas × $100.00 | Descuento 245.00 (5%), total 5399.80 | Idéntico al esperado | ✅ |
| Límite inferior del rango 3 | 50 piezas × $100.00 | Descuento 600.00 (12%), total 5104.00 | Idéntico al esperado | ✅ |
| Datos inválidos | Cantidad 0 y -5; precio 0 y -1 | Vuelve a pedir cada dato hasta que sea mayor a 0 | Vuelve a pedir cada dato | ✅ |

**Observaciones:**

- Los resultados son correctos en todos los casos, incluidos los límites.
- Uso parcial de constantes: en calcularDescuento los límites 10 y 50 están escritos directamente en lugar de usar las constantes; de hecho, LIMITE_DESC_1 se declaró pero nunca se usa. El enunciado pedía explícitamente "nada de valores hardcode dentro de las funciones".
- Funciones puras y validación correctas.

**Recomendaciones:**

- Si declaras una constante para un límite, úsala en todas las comparaciones (por ejemplo, cantidad > LIMITE_DESC_1 en lugar de cantidad >= 10).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// Alejandro Israel Ibarra Banda [matrícula omitida]//

#include <iostream>
#include <iomanip> 
using namespace std;


// [Revisión, línea 8] Esta constante se declaró pero nunca se usa (el compilador lo advierte).
const int LIMITE_DESC_1 = 9;
const int LIMITE_DESC_2 = 49;

const double DESCUENTO_0 = 0.00;  
const double DESCUENTO_5 = 0.05;   
const double DESCUENTO_12 = 0.12; 

const double IVA_TASA = 0.16;     


double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);


double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}

double calcularDescuento(int cantidad, double subtotal) {
    double porcentaje = DESCUENTO_0;
    // [Revisión, línea 30] USO PARCIAL DE CONSTANTES: 10 y 50 están escritos directo; debían usarse tus constantes de límite.
    if (cantidad >= 10 && cantidad <= LIMITE_DESC_2) {
   porcentaje = DESCUENTO_5;
    // [Revisión, línea 32] Mismo caso: 50 escrito directo en lugar de una constante.
    } else if (cantidad >= 50) {
   porcentaje = DESCUENTO_12;
    }
    return subtotal * porcentaje;
}

double calcularIVA(double base_gravable) {
    return base_gravable * IVA_TASA;
}

double calcularTotal(double base_gravable, double iva) {
    return base_gravable + iva;
}

int main() {
    int cantidad;
    double precio_unitario;

  
    do {
    cout << "Ingrese la cantidad de piezas: ";
    cin >> cantidad;
    if (cantidad <= 0) {
    cout << "Error: la cantidad debe ser mayor que 0.\n";
        }
    } while (cantidad <= 0);

    do {
   cout << "Ingrese el precio unitario: ";
   cin >> precio_unitario;
   if (precio_unitario <= 0) {
   cout << "Error: el precio debe ser mayor que 0.\n";
        }
    } while (precio_unitario <= 0);

 
    double subtotal = calcularSubtotal(cantidad, precio_unitario);
    double descuento = calcularDescuento(cantidad, subtotal);
    double base_gravable = subtotal - descuento;
    double iva = calcularIVA(base_gravable);
    double total = calcularTotal(base_gravable, iva);

  
    cout << fixed << setprecision(2);
    cout << "\n=== Facturación ===\n";
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Descuento: $" << descuento << endl;
    cout << "Base gravable: $" << base_gravable << endl;
    cout << "IVA (16%): $" << iva << endl;
    cout << "TOTAL A PAGAR: $" << total << endl;

    return 0;
}
```

## Programa 2 — Nómina quincenal con bono por asistencia perfecta

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | Sueldo $400.00, 0 faltas | Días 15, bruto 6000.00, bono 300.00, ISR 630.00, neto 5670.00 | Valores correctos, pero sin decimales (6000, 300, 630, 5670) | ✅ |
| Caso 2 del enunciado | Sueldo $400.00, 2 faltas | Días 13, bruto 5200.00, bono 0.00, ISR 520.00, neto 4680.00 | Valores correctos, sin decimales | ✅ |
| Límite: 1 falta | Sueldo $400.00, 1 falta | Sin bono, neto 5040.00 | Idéntico al esperado | ✅ |
| Datos inválidos | Sueldo 0 y -1; faltas -1 y 16 | Vuelve a pedir cada dato | Vuelve a pedir cada dato | ✅ |

**Observaciones:**

- Los días trabajados se deducen en su propia función a partir de las faltas.
- Constantes, funciones puras, validación del rango 0 a 15 correctas.
- Los montos se muestran sin formato de dos decimales.

**Recomendaciones:**

- Usa fixed y setprecision(2) de iomanip para mostrar los montos.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Alejandro Israel Ibarra Banda [matrícula omitida]//

#include <iostream>
using namespace std;


const int DIAS_QUINCENA = 15;
const double PORCENTAJE_BONO = 0.05;  
const double TASA_ISR = 0.10;         


int calcularDiasTrabajados(int faltas);
double calcularSueldoBruto(int dias_trabajados, double sueldo_diario);
double calcularBono(int faltas, double sueldo_bruto);
double calcularISR(double ingreso_total);
double calcularSueldoNeto(double ingreso_total, double isr);

int main() {
    double sueldo_diario;
    int faltas;


    do {
        cout << "Ingrese el sueldo diario: ";
        cin >> sueldo_diario;
        if (sueldo_diario <= 0) {
            cout << "Error: el sueldo diario debe ser mayor a 0.\n";
        }
    } while (sueldo_diario <= 0);

  
    do {
   cout << "Ingrese el numero de faltas en la quincena (0-15): ";
   cin >> faltas;
   if (faltas < 0 || faltas > DIAS_QUINCENA) {
   cout << "Error: las faltas deben estar entre 0 y 15.\n";
    }
    } while (faltas < 0 || faltas > DIAS_QUINCENA);

   
    int dias_trabajados = calcularDiasTrabajados(faltas);
    double sueldo_bruto = calcularSueldoBruto(dias_trabajados, sueldo_diario);
    double bono = calcularBono(faltas, sueldo_bruto);
    double ingreso_total = sueldo_bruto + bono;
    double isr = calcularISR(ingreso_total);
    double sueldo_neto = calcularSueldoNeto(ingreso_total, isr);

  
    // [Revisión, línea 49] Detalle: sin fixed y setprecision(2) los montos salen sin decimales.
    cout << "\n=== Reporte de Nomina Quincenal ===\n";
    cout << "Dias trabajados: " << dias_trabajados << endl;
    cout << "Sueldo bruto: $" << sueldo_bruto << endl;
    cout << "Bono de puntualidad: $" << bono << endl;
    cout << "ISR: $" << isr << endl;
    cout << "Sueldo neto: $" << sueldo_neto << endl;

    return 0;
}

// [Revisión, línea 59] Bien: los días trabajados se deducen aquí y no se le piden al usuario.
int calcularDiasTrabajados(int faltas) {
    return DIAS_QUINCENA - faltas;
}

double calcularSueldoBruto(int dias_trabajados, double sueldo_diario) {
    return dias_trabajados * sueldo_diario;
}

double calcularBono(int faltas, double sueldo_bruto) {
    if (faltas == 0) {
        return sueldo_bruto * PORCENTAJE_BONO;
    } else {
        return 0.0;
    }
}

double calcularISR(double ingreso_total) {
    return ingreso_total * TASA_ISR;
}

double calcularSueldoNeto(double ingreso_total, double isr) {
    return ingreso_total - isr;
}
```

## Comentario general

La lógica de ambos programas es correcta. En el Programa 1 faltó usar las constantes en todas las comparaciones de rango.
