# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 09 — Moreno Mercado Fernando

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
- Código muy bien documentado: explicas en comentarios qué hace cada función y por qué son puras.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;


// [Revisión, línea 6] Muy bien documentado.
// Constantes con nombre (nada de valores "hardcodeados" dentro
// de las funciones)
const int    LIMITE_RANGO1 = 9;    // 1  - 9   piezas -> 0%
const int    LIMITE_RANGO2 = 49;   // 10 - 49  piezas -> 5%
// 50 en adelante -> 12%

const double DESCUENTO_RANGO1 = 0.00;
const double DESCUENTO_RANGO2 = 0.05;
const double DESCUENTO_RANGO3 = 0.12;

const double TASA_IVA = 0.16;

// Prototipos
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

// main() - unica funcion que interactua con el usuario
// (cin / cout solo aqui)
int main() {
    int cantidad;
    double precio_unitario;

    // Captura y validacion de cantidad
    do {
        cout << "Cantidad de piezas compradas: ";
        cin >> cantidad;
        if (cantidad <= 0) {
            cout << "Error: la cantidad debe ser mayor que 0.\n";
        }
    } while (cantidad <= 0);

    // Captura y validacion de precio unitario
    do {
        cout << "Precio unitario: ";
        cin >> precio_unitario;
        if (precio_unitario <= 0) {
            cout << "Error: el precio unitario debe ser mayor que 0.\n";
        }
    } while (precio_unitario <= 0);

    // Calculos (usando las funciones puras)
    double subtotal      = calcularSubtotal(cantidad, precio_unitario);
    double descuento     = calcularDescuento(cantidad, subtotal);
    double base_gravable = subtotal - descuento;
    double iva           = calcularIVA(base_gravable);
    double total         = calcularTotal(base_gravable, iva);

    // --- Salida ---
    cout << fixed << setprecision(2);
    cout << "\n--- Resumen de la compra ---\n";
    cout << "Subtotal:          " << subtotal  << endl;
    cout << "Descuento aplicado:" << " " << descuento << endl;
    cout << "IVA:               " << iva << endl;
    cout << "Total a pagar:     " << total << endl;

    return 0;
}


// Definicion de funciones (puras: sin cin/cout)


// Calcula el subtotal de la compra
double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}

// Calcula el descuento segun el rango de cantidad, aplicado sobre el subtotal
// [Revisión, línea 76] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal) {
    double porcentaje;

    if (cantidad <= LIMITE_RANGO1) {
        porcentaje = DESCUENTO_RANGO1;
    } else if (cantidad <= LIMITE_RANGO2) {
        porcentaje = DESCUENTO_RANGO2;
    } else {
        porcentaje = DESCUENTO_RANGO3;
    }

    return subtotal * porcentaje;
}

// Calcula el IVA sobre la base gravable
double calcularIVA(double base_gravable) {
    return base_gravable * TASA_IVA;
}

// Calcula el total a pagar
double calcularTotal(double base_gravable, double iva) {
    return base_gravable + iva;
}
```

## Programa 2 — Comisión de ventas con penalización por devoluciones

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | $60,000.00, 2 devoluciones | Comisión 4800.00, penalización no aplica, ISR 480.00, neto 4320.00 | Valores correctos, sin decimales | ✅ |
| Caso 2 del enunciado | $60,000.00, 5 devoluciones | Comisión 4800.00, penalización 720.00, ISR 408.00, neto 3672.00 | Valores correctos, sin decimales | ✅ |
| Límite: exactamente 3 devoluciones | $60,000.00, 3 devoluciones | Sin penalización | Idéntico al esperado | ✅ |
| 4 devoluciones | $60,000.00, 4 devoluciones | Penalización 720.00 | Idéntico al esperado | ✅ |
| Datos inválidos | Monto 0 y -5; devoluciones -1 | Vuelve a pedir cada dato | Vuelve a pedir cada dato | ✅ |

**Observaciones:**

- Funciones puras, constantes, validación y "no aplica" correctos.
- Las funciones se definen antes de main en lugar de usar prototipos; es válido en C++, aunque en clase se pidió el esquema prototipo, main, definición.
- Los montos se muestran sin formato de dos decimales.

**Recomendaciones:**

- Usa fixed y setprecision(2) para los montos.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>

using namespace std;

// Constantes con nombre
const double PORCENTAJE_COMISION = 0.08;      // 8% del monto vendido
const int    LIMITE_DEVOLUCIONES = 3;         // límite permitido de devoluciones
const double PORCENTAJE_PENALIZACION = 0.15;   // 15% de la comisión
const double TASA_ISR = 0.10;                 // 10% del ingreso total

// Funciones (sin cin/cout, solo cálculo)

// [Revisión, línea 13] Las funciones se definen antes de main sin prototipos: es válido, aunque en clase se usó el esquema prototipo, main, definición.
double calcularComision(double monto_vendido) {
    return monto_vendido * PORCENTAJE_COMISION;
}

// [Revisión, línea 17] Correcto: la penalización solo aplica si las devoluciones SUPERAN el límite.
double calcularPenalizacion(int devoluciones, double comision) {
    if (devoluciones > LIMITE_DEVOLUCIONES) {
        return comision * PORCENTAJE_PENALIZACION;
    }
    return 0.0;
}

double calcularISR(double ingreso_total) {
    return ingreso_total * TASA_ISR;
}

double calcularPagoNeto(double ingreso_total, double isr) {
    return ingreso_total - isr;
}

// main: única función que interactúa con el usuario
int main() {
    double monto_vendido;
    int devoluciones;

    // Validar monto vendido > 0
    do {
        cout << "Monto vendido en la quincena (pesos): ";
        cin >> monto_vendido;
        if (monto_vendido <= 0) {
            cout << "Error: el monto vendido debe ser mayor que 0.\n";
        }
    } while (monto_vendido <= 0);

    // Validar devoluciones >= 0
    do {
        cout << "Numero de devoluciones en la quincena: ";
        cin >> devoluciones;
        if (devoluciones < 0) {
            cout << "Error: el numero de devoluciones no puede ser negativo.\n";
        }
    } while (devoluciones < 0);

    double comision = calcularComision(monto_vendido);
    double penalizacion = calcularPenalizacion(devoluciones, comision);
    double ingreso_total = comision - penalizacion;
    double isr = calcularISR(ingreso_total);
    double pago_neto = calcularPagoNeto(ingreso_total, isr);

    cout << "\n--- Resultado ---\n";
    // [Revisión, línea 62] Detalle: sin fixed y setprecision(2) los montos salen sin decimales.
    cout << "Comision: " << comision << "\n";
    if (penalizacion > 0) {
        cout << "Penalizacion: " << penalizacion << "\n";
    } else {
        cout << "Penalizacion: no aplica\n";
    }
    cout << "ISR: " << isr << "\n";
    cout << "Pago neto: " << pago_neto << "\n";

    return 0;
}
```

## Comentario general

Excelente trabajo. Ambos programas son correctos y están muy bien documentados.
