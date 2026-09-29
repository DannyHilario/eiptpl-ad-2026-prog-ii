# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 01 — Cruz Martinez Cielo Michelle

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
- Reporte completo con dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

// [Revisión, línea 5] Bien: límites, porcentajes y tasa como constantes con nombre.
const int LIMITE_DESCUENTO_1 = 10;
const int LIMITE_DESCUENTO_2 = 50;
const double DESCUENTO_1 = 0.05;
const double DESCUENTO_2 = 0.12;
const double TASA_IVA = 0.16;

// [Revisión, línea 11] Bien: prototipos antes de main.
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main()
{
    int cantidad;
    double precio_unitario;

    // [Revisión, línea 21] Bien: validación de la cantidad con do-while.
    do
    {
        cout << "Ingresa la cantidad de piezas: ";
        cin >> cantidad;

        if (cantidad <= 0)
        {
            cout << "La cantidad debe ser mayor que 0." << endl;
        }
    } while (cantidad <= 0);

    do
    {
        cout << "Ingresa el precio unitario: ";
        cin >> precio_unitario;

        if (precio_unitario <= 0)
        {
            cout << "El precio unitario debe ser mayor que 0." << endl;
        }
    } while (precio_unitario <= 0);

    double subtotal = calcularSubtotal(cantidad, precio_unitario);
    double descuento = calcularDescuento(cantidad, subtotal);
    double base_gravable = subtotal - descuento;
    double iva = calcularIVA(base_gravable);
    double total = calcularTotal(base_gravable, iva);

    cout << fixed << setprecision(2);
    cout << endl;
    cout << "--- FACTURACION ---" << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Descuento aplicado: $" << descuento << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}

double calcularSubtotal(int cantidad, double precio_unitario)
{
    return cantidad * precio_unitario;
}

// [Revisión, línea 65] Bien: función pura (sin cin ni cout) y sin valores fijos escritos.
double calcularDescuento(int cantidad, double subtotal)
{
    if (cantidad >= LIMITE_DESCUENTO_2)
    {
        return subtotal * DESCUENTO_2;
    }
    else if (cantidad >= LIMITE_DESCUENTO_1)
    {
        return subtotal * DESCUENTO_1;
    }
    else
    {
        return 0.0;
    }
}

double calcularIVA(double base_gravable)
{
    return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double iva)
{
    return base_gravable + iva;
}
```

## Programa 2 — Renta de equipo con recargo por retraso

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 5 días, $500.00 | Renta 3500.00, retraso 0, recargo 0.00, IVA 560.00, total 4060.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 10 días, $350.00 | Renta 2450.00, retraso 3, recargo 220.50, IVA 427.28, total 3097.78 | Idéntico al esperado | ✅ |
| Límite: exactamente 7 días | 7 días, $500.00 | Retraso 0, total 4060.00 | Idéntico al esperado | ✅ |
| Un día de retraso | 8 días, $500.00 | Retraso 1, recargo 105.00, total 4181.80 | Idéntico al esperado | ✅ |
| Datos inválidos | Días 0 y -1; tarifa 0 | Vuelve a pedir cada dato | Vuelve a pedir cada dato | ✅ |

**Observaciones:**

- calcularDiasRetraso es la única función que decide si hubo retraso, tal como pedía el enunciado; los días de retraso nunca se le piden al usuario.
- calcularRecargo recibe los dos parámetros necesarios (días de retraso y costo de renta).
- Constantes, funciones puras, validación y reporte completos.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

const int DIAS_SEMANA = 7;
const double RECARGO_POR_DIA = 0.03;
const double TASA_IVA = 0.16;

double calcularCostoRenta(double tarifa_diaria);
int calcularDiasRetraso(int dias_totales);
double calcularRecargo(int dias_retraso, double costo_renta);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main()
{
    int dias_totales;
    double tarifa_diaria;

    do
    {
        cout << "Ingresa los dias totales que tuvo el equipo: ";
        cin >> dias_totales;

        if (dias_totales <= 0)
        {
            cout << "Los dias totales deben ser mayores que 0." << endl;
        }
    } while (dias_totales <= 0);

    do
    {
        cout << "Ingresa la tarifa diaria: ";
        cin >> tarifa_diaria;

        if (tarifa_diaria <= 0)
        {
            cout << "La tarifa diaria debe ser mayor que 0." << endl;
        }
    } while (tarifa_diaria <= 0);

    double costo_renta = calcularCostoRenta(tarifa_diaria);
    int dias_retraso = calcularDiasRetraso(dias_totales);
    double recargo = calcularRecargo(dias_retraso, costo_renta);
    double base_gravable = costo_renta + recargo;
    double iva = calcularIVA(base_gravable);
    double total = calcularTotal(base_gravable, iva);

    cout << fixed << setprecision(2);
    cout << endl;
    cout << "--- RENTA DE EQUIPO ---" << endl;
    cout << "Costo de renta: $" << costo_renta << endl;
    cout << "Dias de retraso: " << dias_retraso << endl;
    cout << "Recargo aplicado: $" << recargo << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}

double calcularCostoRenta(double tarifa_diaria)
{
    return DIAS_SEMANA * tarifa_diaria;
}

// [Revisión, línea 66] Muy bien: esta función es la única responsable de deducir el retraso, como pedía el enunciado.
int calcularDiasRetraso(int dias_totales)
{
    if (dias_totales > DIAS_SEMANA)
    {
        return dias_totales - DIAS_SEMANA;
    }

    return 0;
}

// [Revisión, línea 76] Bien: recibe los dos parámetros necesarios (días de retraso y costo de renta).
double calcularRecargo(int dias_retraso, double costo_renta)
{
    return costo_renta * RECARGO_POR_DIA * dias_retraso;
}

double calcularIVA(double base_gravable)
{
    return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double iva)
{
    return base_gravable + iva;
}
```

## Comentario general

Excelente trabajo. Ambos programas están bien estructurados con funciones, cumplen todos los requisitos y dan los resultados correctos en todos los casos probados.
