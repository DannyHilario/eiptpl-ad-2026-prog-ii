# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** Tal como se entregó, no compila: la línea 1 ("Programa realizado por: Jesús Ramirez") es texto que no está marcado como comentario; bastaba con poner `//` al inicio. Con esa línea comentada compila sin errores, y las pruebas de abajo se hicieron así.

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

**Recomendaciones:**

- Recuerda que el encabezado con tu nombre debe ir como comentario (// o /* */).
- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] Esta línea no es comentario y el compilador la lee como código; debe empezar con //.
Programa realizado por: Jesús Ramirez 
#include <iostream>
#include <iomanip>

using namespace std;

// Constantes globales de configuración
// [Revisión, línea 8] Bien: límites, porcentajes y tasa como constantes con nombre.
const int RANGO_MEDIO_MIN = 10;
const int RANGO_ALTO_MIN = 50;

const double PCT_DESC_BAJO = 0.0;
const double PCT_DESC_MEDIO = 0.05;
const double PCT_DESC_ALTO = 0.12;

const double TASA_IVA = 0.16;

// Prototipos de funciones de cálculo
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main() {
    int cantidad = 0;
    double precioUnitario = 0.0;

    // Validación de entrada para cantidad
    // [Revisión, línea 28] Bien: validación de la cantidad con do-while.
    do {
        cout << "Ingrese la cantidad de piezas compradas (debe ser mayor a 0): ";
        cin >> cantidad;
        if (cantidad <= 0) {
            cout << "Error: La cantidad debe ser mayor a 0.\n";
        }
    } while (cantidad <= 0);

    // Validación de entrada para precio unitario
    do {
        cout << "Ingrese el precio unitario (debe ser mayor a 0): ";
        cin >> precioUnitario;
        if (precioUnitario <= 0) {
            cout << "Error: El precio unitario debe ser mayor a 0.\n";
        }
    } while (precioUnitario <= 0);

    // Cálculos
    double subtotal = calcularSubtotal(cantidad, precioUnitario);
    double descuento = calcularDescuento(cantidad, subtotal);
    double baseGravable = subtotal - descuento;
    double iva = calcularIVA(baseGravable);
    double total = calcularTotal(baseGravable, iva);

    // Despliegue de resultados con formato monetario de 2 decimales
    cout << fixed << setprecision(2);
    cout << "\n----------------------------------------\n";
    cout << "          RESUMEN DE COMPRA             \n";
    cout << "----------------------------------------\n";
    cout << "Subtotal:         $" << subtotal << "\n";
    cout << "Descuento:       -$" << descuento << "\n";
    cout << "Base gravable:    $" << baseGravable << "\n";
    cout << "IVA (16%):       +$" << iva << "\n";
    cout << "----------------------------------------\n";
    cout << "Total a pagar:    $" << total << "\n";
    cout << "----------------------------------------\n";

    return 0;
}

// Implementación de funciones de cálculo

double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}

// [Revisión, línea 74] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal) {
    if (cantidad >= RANGO_ALTO_MIN) {
        return subtotal * PCT_DESC_ALTO;
    } else if (cantidad >= RANGO_MEDIO_MIN) {
        return subtotal * PCT_DESC_MEDIO;
    } else {
        return subtotal * PCT_DESC_BAJO;
    }
}

double calcularIVA(double base_gravable) {
    return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double iva) {
    return base_gravable + iva;
}
```

## Programa 2 — Pago por llamadas atendidas en call center

**Compilación:** Mismo caso que en el Programa 1: tal como se entregó, no compila porque la línea 1 ("Programa realizado por: Jesús Ramirez") no está marcada como comentario. Con esa línea comentada compila sin errores, y las pruebas de abajo se hicieron así.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 150 llamadas | Pago base 1200.00, bono no aplica, ISR 120.00, neto 1080.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 250 llamadas | Pago base 2000.00, bono 200.00, ISR 220.00, neto 1980.00 | Idéntico al esperado | ✅ |
| Límite: exactamente la meta | 200 llamadas | Sin bono (no supera la meta), neto 1440.00 | Idéntico al esperado | ✅ |
| Una llamada sobre la meta | 201 llamadas | Bono 160.80, neto 1591.92 | Idéntico al esperado | ✅ |
| Datos inválidos | Llamadas -3 y -1 | Vuelve a pedir el dato (0 sí es válido) | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Funciones puras (sin cin ni cout), constantes con nombre para tarifa, meta, bono e ISR, y validación correctas.
- calcularBono recibe los dos parámetros necesarios y el bono solo aplica si las llamadas SUPERAN la meta.
- Muestra "No aplica" cuando el bono es 0, y el reporte tiene dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] Esta línea no es comentario y el compilador la lee como código; debe empezar con //.
Programa realizado por: Jesús Ramirez 

#include <iostream>
#include <iomanip>

using namespace std;

// Constantes globales de configuración
// [Revisión, línea 9] Bien: constantes con nombre.
const double TARIFA_POR_LLAMADA = 8.00;
const int META_SEMANAL = 200;
const double PCT_BONO = 0.10;
const double TASA_ISR = 0.10;

// Prototipos de funciones de cálculo
double calcularPagoBase(int llamadas_atendidas);
double calcularBono(int llamadas_atendidas, double pago_base);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);

int main() {
    int llamadasAtendidas = 0;

    // Validación de entrada para llamadas atendidas (debe ser >= 0)
    do {
        cout << "Ingrese el numero de llamadas atendidas en la semana (>= 0): ";
        cin >> llamadasAtendidas;
        if (llamadasAtendidas < 0) {
            cout << "Error: El numero de llamadas no puede ser negativo.\n";
        }
    } while (llamadasAtendidas < 0);

    // Cálculos
    double pagoBase = calcularPagoBase(llamadasAtendidas);
    double bono = calcularBono(llamadasAtendidas, pagoBase);
    double ingresoTotal = pagoBase + bono;
    double isr = calcularISR(ingresoTotal);
    double pagoNeto = calcularPagoNeto(ingresoTotal, isr);

    // Despliegue de resultados con formato de 2 decimales
    cout << fixed << setprecision(2);
    cout << "\n----------------------------------------\n";
    cout << "        DESGLOSE DE PAGO SEMANAL        \n";
    cout << "----------------------------------------\n";
    cout << "Llamadas atendidas:  " << llamadasAtendidas << "\n";
    cout << "Pago base:          $" << pagoBase << "\n";
    
    if (bono > 0.0) {
        cout << "Bono (10%):        +$" << bono << "\n";
    } else {
        // [Revisión, línea 50] Bien: muestra "No aplica" cuando el bono es 0.
        cout << "Bono:                No aplica ($0.00)\n";
    }

    cout << "Ingreso total:      $" << ingresoTotal << "\n";
    cout << "ISR (10%):         -$" << isr << "\n";
    cout << "----------------------------------------\n";
    cout << "Pago neto:          $" << pagoNeto << "\n";
    cout << "----------------------------------------\n";

    return 0;
}

// Implementación de funciones de cálculo

double calcularPagoBase(int llamadas_atendidas) {
    return llamadas_atendidas * TARIFA_POR_LLAMADA;
}

double calcularBono(int llamadas_atendidas, double pago_base) {
    // [Revisión, línea 69] Correcto: el bono solo aplica si las llamadas SUPERAN la meta.
    if (llamadas_atendidas > META_SEMANAL) {
        return pago_base * PCT_BONO;
    }
    return 0.0;
}

double calcularISR(double ingreso_total) {
    return ingreso_total * TASA_ISR;
}

double calcularPagoNeto(double ingreso_total, double isr) {
    return ingreso_total - isr;
}
```

## Comentario general

Ninguno de los dos archivos compila tal como se entregó porque el encabezado con tu nombre no está escrito como comentario, igual que en la Evidencia 1. Con esa línea comentada, ambos programas son correctos en todos los casos.
