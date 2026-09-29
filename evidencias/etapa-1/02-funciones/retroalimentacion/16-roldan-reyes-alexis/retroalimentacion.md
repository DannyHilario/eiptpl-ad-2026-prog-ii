# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 16 — Roldan Reyes Alexis

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** **No compila.** El compilador marca 4 errores: en la línea 12 la constante se declaró como "tasa _IVA" (con un espacio en medio), por lo que en la línea 61 TASA_IVA no existe; además, el archivo termina en la línea 64 sin la llave } que cierra calcularTotal.

**Observaciones:**

- El archivo parece estar incompleto al final.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

// Constantes de negocio (evita hardcode en las funciones)
const int RANGO_DESCUENTO_1_CANT = 10;
const int RANGO_DESCUENTO_2_CANT = 50;
const double PCT_DESCUENTO_0 = 0.00;
const double PCT_DESCUENTO_5 = 0.05;
const double PCT_DESCUENTO_12 = 0.12;

// [Revisión, línea 12] NO COMPILA: el nombre tiene un espacio ("tasa _IVA"). Debía ser TASA_IVA.
const double tasa _IVA = 0.16;
// Prototipos de funciones
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);
int main() {
    int cantidad = 0;
    double precioUnitario = 0.0;
    // Validación de entrada para la cantidad
    do {
        cout << "Ingrese la cantidad de piezas compradas (debe ser mayor a 0): ";
        cin >> cantidad;
    } while (cantidad <= 0);
    // Validación de entrada para el precio unitario
    do {
        cout << "Ingrese el precio unitario (debe ser mayor a 0): ";
        cin >> precioUnitario;
    } while (precioUnitario <= 0);
    // Cálculos llamando a funciones puras
    double subtotal = calcularSubtotal(cantidad, precioUnitario);
    double descuento = calcularDescuento(cantidad, subtotal);
    double baseGravable = subtotal - descuento;
    double iva = calcularIVA(baseGravable);
    double total = calcularTotal(baseGravable, iva);
    // Salida de resultados con formato de moneda (2 decimales)
    cout << fixed << setprecision(2);
    cout << "\n--- RESUMEN DE COMPRA ---" << endl;
    cout << "Subtotal:         $" << subtotal << endl;
    cout << "Descuento:        $" << descuento << endl;
    cout << "IVA (16%):        $" << iva << endl;
    cout << "Total a pagar:    $" << total << endl;

    return 0;
}

// Implementación de funciones puras (sin cin / cout)
double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}
double calcularDescuento(int cantidad, double subtotal) {
    if (cantidad >= RANGO_DESCUENTO_2_CANT) {
        return subtotal * PCT_DESCUENTO_12;
    } else if (cantidad >= RANGO_DESCUENTO_1_CANT) {
        return subtotal * PCT_DESCUENTO_5;
    }
    return subtotal * PCT_DESCUENTO_0;
}
double calcularIVA(double base_gravable) {
    // [Revisión, línea 61] NO COMPILA: TASA_IVA no existe porque se declaró con otro nombre en la línea 12.
    return base_gravable * TASA_IVA;
}
double calcularTotal(double base_gravable, double iva) {
    // [Revisión, línea 64] NO COMPILA: el archivo termina aquí; falta la llave } que cierra la función.
    return base_gravable + iva;
```

## Programa 2 — Vendedor de seguros con bono por pólizas

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 7 pólizas | Comisión 2450.00, bono no aplica, ISR 245.00, neto 2205.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 13 pólizas | Comisión 4550.00, bono 546.00, ISR 509.60, neto 4586.40 | Idéntico al esperado | ✅ |
| Límite: exactamente la meta | 10 pólizas | Sin bono, neto 3150.00 | Idéntico al esperado | ✅ |
| Una póliza sobre la meta | 11 pólizas | Bono 462.00, neto 3880.80 | Idéntico al esperado | ✅ |
| Datos inválidos | Pólizas -1 | Vuelve a pedir el dato | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Funciones puras, constantes, validación y reporte con "No aplica" correctos. Código claro y comentado.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

// Constantes de negocio
// [Revisión, línea 6] Bien: constantes con nombre.
const double COMISION_POR_POLIZA = 350.00;
const int META_POLIZAS = 10;
const double PCT_BONO_META = 0.12;
const double TASA_ISR = 0.10;
// Prototipos de funciones
double calcularComision(int polizas_vendidas);
double calcularBono(int polizas_vendidas, double comision);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);

int main() {
    int polizasVendidas = 0;
    // Validación de entrada para las pólizas vendidas (debe ser >= 0)
    do {
        cout << "Ingrese el numero de polizas vendidas en la quincena: ";
        cin >> polizasVendidas;
        if (polizasVendidas < 0) {
            cout << "El numero de polizas no puede ser negativo. Intente de nuevo.\n";
        }
    } while (polizasVendidas < 0);
    // Cálculos utilizando funciones puras
    double comision = calcularComision(polizasVendidas);
    double bono = calcularBono(polizasVendidas, comision);
    double ingresoTotal = comision + bono;
    double isr = calcularISR(ingresoTotal);
    double pagoNeto = calcularPagoNeto(ingresoTotal, isr);
    // Formato de salida con 2 decimales
    cout << fixed << setprecision(2);
    cout << "\n--- RESUMEN DE PAGO QUINCENAL ---" << endl;
    cout << "Comision:          $" << comision << endl;
    if (bono > 0.0) {
        cout << "Bono por meta:     $" << bono << endl;
    } else {
        cout << "Bono por meta:     No aplica" << endl;
    }
    cout << "ISR (10%):         $" << isr << endl;
    cout << "Pago Neto:         $" << pagoNeto << endl;

    return 0;
}
// Implementación de funciones puras (sin cin / cout)
double calcularComision(int polizas_vendidas) {
    return polizas_vendidas * COMISION_POR_POLIZA;
}
// [Revisión, línea 50] Correcto: el bono solo aplica si las pólizas SUPERAN la meta.
double calcularBono(int polizas_vendidas, double comision) {
    if (polizas_vendidas > META_POLIZAS) {
        return comision * PCT_BONO_META;
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

El Programa 2 está muy bien resuelto; el Programa 1 no compila por un error de escritura en el nombre de una constante y porque el archivo está incompleto.
