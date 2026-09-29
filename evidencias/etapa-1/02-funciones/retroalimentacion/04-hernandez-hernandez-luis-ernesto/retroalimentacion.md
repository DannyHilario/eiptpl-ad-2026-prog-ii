# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 04 — Hernández Hernández Luis Ernesto

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
- Código claro y bien comentado.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/* luis ernesto hdz hdz*/
#include <iostream>
#include <iomanip>
using namespace std;

// Constantes
// [Revisión, línea 7] Bien: constantes con nombre para los límites.
const int LIMITE_DESCUENTO_1 = 9;
const int LIMITE_DESCUENTO_2 = 49;

const double DESCUENTO_1 = 0.00;
const double DESCUENTO_2 = 0.05;
const double DESCUENTO_3 = 0.12;

const double TASA_IVA = 0.16;

// Prototipos
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main() {
    int cantidad;
    double precio_unitario;

    // Captura y validación de datos
    do {
        cout << "Ingrese la cantidad de piezas: ";
        cin >> cantidad;

        if (cantidad <= 0) {
            cout << "Error: la cantidad debe ser mayor que 0.\n";
        }

    } while (cantidad <= 0);

    do {
        cout << "Ingrese el precio unitario: $";
        cin >> precio_unitario;

        if (precio_unitario <= 0) {
            cout << "Error: el precio unitario debe ser mayor que 0.\n";
        }

    } while (precio_unitario <= 0);

    // Cálculos
    double subtotal = calcularSubtotal(cantidad, precio_unitario);
    double descuento = calcularDescuento(cantidad, subtotal);
    double base_gravable = subtotal - descuento;
    double iva = calcularIVA(base_gravable);
    double total = calcularTotal(base_gravable, iva);

    // Mostrar resultados
    cout << fixed << setprecision(2);
    cout << "\n===== FACTURA =====\n";
    cout << "Subtotal:       $" << subtotal << endl;
    cout << "Descuento:      $" << descuento << endl;
    cout << "IVA (16%):      $" << iva << endl;
    cout << "Total a pagar:  $" << total << endl;

    return 0;
}

// Función para calcular el subtotal
double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}

// Función para calcular el descuento
// [Revisión, línea 71] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal) {
    double porcentaje;

    if (cantidad <= LIMITE_DESCUENTO_1) {
        porcentaje = DESCUENTO_1;
    }
    else if (cantidad <= LIMITE_DESCUENTO_2) {
        porcentaje = DESCUENTO_2;
    }
    else {
        porcentaje = DESCUENTO_3;
    }

    return subtotal * porcentaje;
}

// Función para calcular el IVA
double calcularIVA(double base_gravable) {
    return base_gravable * TASA_IVA;
}

// Función para calcular el total
double calcularTotal(double base_gravable, double iva) {
    return base_gravable + iva;
}
```

## Programa 2 — Recibo de agua doméstica por rangos de consumo

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 8 m3 | Cargo 90.00, IVA 14.40, total 104.40 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 45 m3 | Cargo 480.00, IVA 76.80, total 556.80 | Idéntico al esperado | ✅ |
| Límite del rango 1 | 10 m3 | Cargo 90.00 (fijo) | Idéntico al esperado | ✅ |
| Límite del rango 2 | 30 m3 | Cargo 270.00, total 313.20 | Idéntico al esperado | ✅ |
| Inicio del rango 3 | 30.5 m3 | Cargo 277.00, total 321.32 | Idéntico al esperado | ✅ |
| Datos inválidos | Consumo -1 | Vuelve a pedir el consumo (0 sí es válido) | Lo vuelve a pedir; acepta 0 | ✅ |

**Observaciones:**

- La tabla de rangos está resuelta con constantes para límites, cuotas fijas y tarifas; ningún valor está escrito directo en la función.
- Validación correcta (consumo mayor o igual a 0) y reporte con dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/*luis ernesto programa 2 */
#include <iostream>
#include <iomanip>

using namespace std;

// Constantes globales de configuración
// [Revisión, línea 8] Bien: toda la tabla de rangos está en constantes.
const double LIMITE_RANGO_1 = 10.0;
const double LIMITE_RANGO_2 = 30.0;

const double CUOTA_FIJA_RANGO_1 = 90.0;
const double CUOTA_FIJA_RANGO_2 = 90.0;
const double CUOTA_FIJA_RANGO_3 = 270.0;

const double TARIFA_EXCEDENTE_RANGO_2 = 9.0;
const double TARIFA_EXCEDENTE_RANGO_3 = 14.0;

const double TASA_IVA = 0.16;

// Prototipos de función
double calcularCargoConsumo(double consumo_m3);
double calcularIVA(double cargo_consumo);
double calcularTotal(double cargo_consumo, double iva);

int main() {
    double consumo_m3 = 0.0;

    // Validación de entrada (repite la captura si consumo < 0)
    // [Revisión, línea 29] Correcto: el consumo debe ser mayor o igual a 0.
    do {
        cout << "Ingrese el consumo del mes en m3: ";
        cin >> consumo_m3;

        if (consumo_m3 < 0.0) {
            cout << "Error: El consumo debe ser un valor mayor o igual a cero. Intente de nuevo.\n";
        }
    } while (consumo_m3 < 0.0);

    // Cálculos utilizando las funciones modularizadas
    double cargo_consumo = calcularCargoConsumo(consumo_m3);
    double iva = calcularIVA(cargo_consumo);
    double total_pagar = calcularTotal(cargo_consumo, iva);

    // Salida de resultados con formato monetario (2 decimales)
    cout << fixed << setprecision(2);
    cout << "\n--- RESUMEN DEL RECIBO DE AGUA ---\n";
    cout << "Cargo por consumo: $" << cargo_consumo << "\n";
    cout << "IVA (" << (TASA_IVA * 100) << "%):        $" << iva << "\n";
    cout << "Total a pagar:     $" << total_pagar << "\n";

    return 0;
}

// Funciones de cálculo (sin cin ni cout)
// [Revisión, línea 54] Bien: la tabla de rangos se resuelve con constantes, sin valores escritos directo.
double calcularCargoConsumo(double consumo_m3) {
    if (consumo_m3 <= LIMITE_RANGO_1) {
        return CUOTA_FIJA_RANGO_1;
    } else if (consumo_m3 <= LIMITE_RANGO_2) {
        return CUOTA_FIJA_RANGO_2 + (consumo_m3 - LIMITE_RANGO_1) * TARIFA_EXCEDENTE_RANGO_2;
    } else {
        return CUOTA_FIJA_RANGO_3 + (consumo_m3 - LIMITE_RANGO_2) * TARIFA_EXCEDENTE_RANGO_3;
    }
}

double calcularIVA(double cargo_consumo) {
    return cargo_consumo * TASA_IVA;
}

double calcularTotal(double cargo_consumo, double iva) {
    return cargo_consumo + iva;
}
```

## Comentario general

Excelente trabajo. Ambos programas están bien estructurados, documentados y correctos en todos los casos.
