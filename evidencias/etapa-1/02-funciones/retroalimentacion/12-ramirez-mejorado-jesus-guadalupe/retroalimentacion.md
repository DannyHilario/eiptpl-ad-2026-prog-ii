# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** **No compila.** El compilador marca error en la línea 1: el archivo empieza con "Programa realizado por: Jesús Ramirez" sin marcarlo como comentario.

**Observaciones:**

- Es el mismo error que en la Evidencia 1. Bastaba con poner // al inicio de esa línea.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] NO COMPILA: esta línea no es comentario y el compilador intenta leerla como código. Bastaba con escribir // al inicio.
Programa realizado por: Jesús Ramirez 
#include <iostream>
#include <iomanip>

using namespace std;

// Constantes globales de configuración
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

**Compilación:** **No compila.** El mismo error en la línea 1: "Programa realizado por: Jesús Ramirez" no está marcado como comentario.

**Observaciones:**

- Bastaba con poner // al inicio de esa línea.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] NO COMPILA: esta línea no es comentario y el compilador intenta leerla como código. Bastaba con escribir // al inicio.
Programa realizado por: Jesús Ramirez 

#include <iostream>
#include <iomanip>

using namespace std;

// Constantes globales de configuración
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

Ninguno de los dos programas compila por el mismo motivo que en la Evidencia 1: el encabezado con tu nombre no está escrito como comentario.
