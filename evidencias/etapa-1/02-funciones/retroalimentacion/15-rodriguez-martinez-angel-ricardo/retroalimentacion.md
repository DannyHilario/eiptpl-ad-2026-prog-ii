# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** Tal como se entregó, no compila: las líneas 4 y 5 dicen solo `#include`, sin la biblioteca. Deben ser `#include <iostream>` y `#include <iomanip>` (esta última hace falta porque el programa usa `setprecision`). Con esas dos líneas completas compila sin errores, y las pruebas de abajo se hicieron así.

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

- Estructura completa: prototipos antes de main, definiciones y llamadas correctas.
- Las funciones de cálculo no usan cin ni cout; solo main interactúa con el usuario.
- Límites de rango, porcentajes y tasa de IVA definidos como constantes con nombre.
- Validación de cantidad y precio con do-while, repitiendo la captura.
- Reporte completo con base gravable y dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Angel Ricardo Rodriguez Martinez Matricula:[matrícula omitida] aboratorio de Programas (Funciones)


// [Revisión, línea 4] #include está vacío y no compila; debe ser #include <iostream>.
#include 
// [Revisión, línea 5] Debe ser #include <iomanip> (necesaria para setprecision).
#include 

using namespace std;


const double TASA_IVA = 0.16;


const int RANGO1_MAX = 9;
const int RANGO2_MAX = 49;


const double DESCUENTO_RANGO1 = 0.00; // 0%
const double DESCUENTO_RANGO2 = 0.05; // 5%
const double DESCUENTO_RANGO3 = 0.12; // 12%


double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main() {
    int cantidad = 0;
    double precioUnitario = 0.0;

    do {
        cout << "Ingrese la cantidad de piezas compradas (mayor a 0): ";
        cin >> cantidad;
        if (cantidad <= 0) {
            cout << "Error: La cantidad debe ser mayor que 0. Intente de nuevo.\n";
        }
    } while (cantidad <= 0);

   
    do {
        cout << "Ingrese el precio unitario (mayor a 0): ";
        cin >> precioUnitario;
        if (precioUnitario <= 0) {
            cout << "Error: El precio unitario debe ser mayor que 0. Intente de nuevo.\n";
        }
    } while (precioUnitario <= 0);


    double subtotal = calcularSubtotal(cantidad, precioUnitario);
    double descuento = calcularDescuento(cantidad, subtotal);
    double baseGravable = subtotal - descuento;
    double iva = calcularIVA(baseGravable);
    double total = calcularTotal(baseGravable, iva);

   
    cout << fixed << setprecision(2);
    cout << " RESUMEN DE FACTURACIÓN " << endl;
    cout << "Subtotal:        $" << subtotal << endl;
    cout << "Descuento:      -$" << descuento << endl;
    cout << "Base gravable:   $" << baseGravable << endl;
    cout << "IVA (16%):      +$" << iva << endl;
    cout << "-------------" << endl;
    cout << "Total a pagar:   $" << total << endl;

    return 0;
}


double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}

// [Revisión, línea 73] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal) {
    if (cantidad <= RANGO1_MAX) {
        return subtotal * DESCUENTO_RANGO1;
    } else if (cantidad <= RANGO2_MAX) {
        return subtotal * DESCUENTO_RANGO2;
    } else {
        return subtotal * DESCUENTO_RANGO3;
    }
}

double calcularIVA(double base_gravable) {
    return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double iva) {
    return base_gravable + iva;
}
```

## Programa 2 — Lavado de autos a domicilio con paquete semanal

**Compilación:** Mismo caso que en el Programa 1: tal como se entregó, no compila porque las líneas 2 y 3 dicen solo `#include`. Deben ser `#include <iostream>` y `#include <iomanip>`. Con esas dos líneas completas compila sin errores, y las pruebas de abajo se hicieron así.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 8 autos | Excedentes 0, subtotal 600.00, IVA 96.00, total 696.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 14 autos | Excedentes 4, subtotal 780.00, IVA 124.80, total 904.80 | Idéntico al esperado | ✅ |
| Límite: exactamente 10 autos | 10 autos | Excedentes 0, total 696.00 | Idéntico al esperado | ✅ |
| Un auto excedente | 11 autos | Excedentes 1, subtotal 645.00, total 748.20 | Idéntico al esperado | ✅ |
| Datos inválidos | Autos -1 | Vuelve a pedir el dato | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Los autos excedentes se deducen en su propia función y nunca se le piden al usuario.
- Funciones puras, constantes con nombre, validación y reporte con dos decimales correctos.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Angel Ricardo Rodriguez Martinez Matricula:[matrícula omitida]
// [Revisión, línea 2] #include está vacío y no compila; debe ser #include <iostream>.
#include 
// [Revisión, línea 3] Debe ser #include <iomanip>.
#include 

using namespace std;


const int AUTOS_INCLUIDOS = 10;
const double COSTO_PAQUETE = 600.00;
const double TARIFA_EXCEDENTE = 45.00;
const double TASA_IVA = 0.16;


int calcularAutosExcedentes(int autos_lavados);
double calcularSubtotal(int autos_excedentes);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);

int main() {
    int autos_lavados = 0;

    do {
        cout << "Ingrese el número de autos lavados en la semana: ";
        cin >> autos_lavados;

        if (autos_lavados < 0) {
            cout << "Error: El número de autos no puede ser negativo. Intente de nuevo.\n\n";
        }
    } while (autos_lavados < 0);

    
    int excedentes = calcularAutosExcedentes(autos_lavados);
    double subtotal = calcularSubtotal(excedentes);
    double iva = calcularIVA(subtotal);
    double total = calcularTotal(subtotal, iva);

   
    cout << fixed << setprecision(2);
    cout << "RESUMEN DE COBRO" << endl;
    cout << "Autos excedentes: " << excedentes << endl;
    cout << "Subtotal:        $" << subtotal << endl;
    cout << "IVA (16%):       $" << iva << endl;
    cout << "Total a pagar:   $" << total << endl;

    return 0;
}



// [Revisión, línea 50] Bien: los autos excedentes se deducen aquí y no se le piden al usuario.
int calcularAutosExcedentes(int autos_lavados) {
    if (autos_lavados > AUTOS_INCLUIDOS) {
        return autos_lavados - AUTOS_INCLUIDOS;
    }
    return 0;
}

double calcularSubtotal(int autos_excedentes) {
    return COSTO_PAQUETE + (autos_excedentes * TARIFA_EXCEDENTE);
}

double calcularIVA(double subtotal) {
    return subtotal * TASA_IVA;
}

double calcularTotal(double subtotal, double iva) {
    return subtotal + iva;
}
```

## Comentario general

Ninguno de los dos archivos compila tal como se entregó porque las líneas #include están vacías. Con esas líneas completas, ambos programas son correctos en todos los casos.
