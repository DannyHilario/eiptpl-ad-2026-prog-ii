# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 11 — Palacios Moreno Jael Yasmani

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** Compila sin errores.

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

**Recomendaciones:**

- Los mensajes de error no llevan endl, así que la siguiente pregunta queda pegada en la misma línea; cuida también el tono de los mensajes ("LOL").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>

using namespace std;
const int RANGO_MEDIO_MIN = 10;
const int RANGO_ALTO_MIN = 50;

const double DESC_RANGO_BAJO = 0.0; 
const double DESC_RANGO_MEDIO = 0.05;  
const double DESC_RANGO_ALTO = 0.12;  
const double TASA_IVA = 0.16;
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main() {
    int cantidad = 0;
    double precioUnitario = 0.0;

    cout << "SISTEMA DE FACTURACION" << endl;

    do {
        cout << "Ingrese la cantidad de piezas compradas: ";
        cin >> cantidad;
        if (cantidad <= 0) {
            // [Revisión, línea 27] Detalle: falta endl; la siguiente pregunta queda pegada al mensaje.
            cout << "el numero debe de ser mayor";
        }
    } while (cantidad <= 0);

    do {
        cout << "Ingrese el precio: ";
        cin >> precioUnitario;
        if (precioUnitario <= 0) {
            cout << "el precio debe de ser mayor a 0 LOL";
        }
    } while (precioUnitario <= 0);

    double subtotal = calcularSubtotal(cantidad, precioUnitario);
    double descuento = calcularDescuento(cantidad, subtotal);
    double baseGravable = subtotal - descuento;
    double iva = calcularIVA(baseGravable);
    double total = calcularTotal(baseGravable, iva);

    cout << fixed << setprecision(2);
    cout << "RESUMEN DE COMPRA" << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Descuento:  -$" << descuento << endl;
    cout << "Base gravable:  $" << baseGravable << endl;
    cout << "IVA (16%):  $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}

double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}

// [Revisión, línea 60] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal) {
    double porcentaje = 0.0;

    if (cantidad >= RANGO_ALTO_MIN) {
        porcentaje = DESC_RANGO_ALTO;
    } else if (cantidad >= RANGO_MEDIO_MIN) {
        porcentaje = DESC_RANGO_MEDIO;
    } else {
        porcentaje = DESC_RANGO_BAJO;
    }

    return subtotal * porcentaje;
}

double calcularIVA(double base_gravable) {
    return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double iva) {
    return base_gravable + iva;
}
```

## Programa 2 — Colegiatura con recargo por pago atrasado

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 0 días de atraso | Recargo 0.00, total 2500.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 5 días de atraso | Recargo 250.00, total 2750.00 | Idéntico al esperado | ✅ |
| Un día de atraso | 1 día | Recargo 50.00, total 2550.00 | Idéntico al esperado | ✅ |
| Datos inválidos | Días -1 | Vuelve a pedir el dato | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Funciones puras, constantes y validación correctas; sin IVA, como indicaba el enunciado.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

const double MONTO_COLEGIATURA = 2500.00;
const double PORCENTAJE_RECARGO_DIARIO = 0.02; 

double calcularRecargo(int dias_atraso);
double calcularTotal(double recargo);

int main() {
    int diasAtraso = 0;

    cout << "PAGO DE COLEGIATURA MENSUAL" << endl;

    do {
        cout << "Ingrese los dias de atraso en el pago (0 si fue a tiempo): ";
        cin >> diasAtraso;
        if (diasAtraso < 0) {
            cout << "los dias no deben de ser negativos, ponlos bien ";
        }
    } while (diasAtraso < 0);

    double recargo = calcularRecargo(diasAtraso);
    double totalAPagar = calcularTotal(recargo);

    cout << fixed << setprecision(2);
    cout << "DESGLOSE DE PAGO" << endl;
    cout << "Monto base colegiatura: $" << MONTO_COLEGIATURA << endl;
    cout << "Dias de atraso:    " << diasAtraso << " dia(s)" << endl;
    cout << "Recargo aplicado:  +$" << recargo << endl;
    cout << "Total a pagar:   $" << totalAPagar << endl;

    return 0;
}


// [Revisión, línea 39] Bien: función pura con constantes; sin IVA, como indicaba el enunciado.
double calcularRecargo(int dias_atraso) {
    return MONTO_COLEGIATURA * PORCENTAJE_RECARGO_DIARIO * dias_atraso;
}

double calcularTotal(double recargo) {
    return MONTO_COLEGIATURA + recargo;
}
```

## Comentario general

Excelente trabajo. Ambos programas son correctos y cumplen los requisitos.
