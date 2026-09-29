# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 05 — Hernandez Lopez Jose

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
- El reporte incluye además la base gravable, cantidad y precio unitario.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//JOSEHERNANDEZLOPEZ//
#include <iostream>
#include <iomanip>

using namespace std;

// Constantes
// [Revisión, línea 8] Bien: constantes con nombre.
const int LIMITE_DESCUENTO_1 = 9;
const int LIMITE_DESCUENTO_2 = 49;

const double DESCUENTO_1 = 0.00;
const double DESCUENTO_2 = 0.05;
const double DESCUENTO_3 = 0.12;

const double TASA_IVA = 0.16;

double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main()
{
    int cantidad;
    double precio_unitario;

    double subtotal;
    double descuento;
    double base_gravable;
    double iva;
    double total;

    do
    {
        cout << "Ingrese la cantidad de piezas: ";
        cin >> cantidad;

        if (cantidad <= 0)
        {
            cout << "La cantidad debe ser mayor que 0." << endl;
        }

    } while (cantidad <= 0);

    do
    {
        cout << "Ingrese el precio unitario: $";
        cin >> precio_unitario;

        if (precio_unitario <= 0)
        {
            cout << "El precio debe ser mayor que 0." << endl;
        }

    } while (precio_unitario <= 0);

    subtotal = calcularSubtotal(cantidad, precio_unitario);

    descuento = calcularDescuento(cantidad, subtotal);

    base_gravable = subtotal - descuento;

    iva = calcularIVA(base_gravable);

    total = calcularTotal(base_gravable, iva);

    cout << fixed << setprecision(2);

    cout << endl;
    cout << "===== REPORTE DE COMPRA =====" << endl;
    cout << "Cantidad de piezas: " << cantidad << endl;
    cout << "Precio unitario: $" << precio_unitario << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Descuento: $" << descuento << endl;
    cout << "Base gravable: $" << base_gravable << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}

double calcularSubtotal(int cantidad, double precio_unitario)
{
    return cantidad * precio_unitario;
}

// [Revisión, línea 87] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal)
{
    double porcentaje;

    if (cantidad <= LIMITE_DESCUENTO_1)
    {
        porcentaje = DESCUENTO_1;
    }
    else if (cantidad <= LIMITE_DESCUENTO_2)
    {
        porcentaje = DESCUENTO_2;
    }
    else
    {
        porcentaje = DESCUENTO_3;
    }

    return subtotal * porcentaje;
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

## Programa 2 — Renta de auto semanal con kilometraje incluido

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | Tarifa $600.00, 500 km | Renta 4200.00, excedente 0, recargo 0.00, IVA 672.00, total 4872.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | Tarifa $600.00, 900 km | Renta 4200.00, excedente 200, recargo 600.00, IVA 768.00, total 5568.00 | Idéntico al esperado | ✅ |
| Límite: exactamente 700 km | Tarifa $600.00, 700 km | Excedente 0, total 4872.00 | Idéntico al esperado | ✅ |
| Un km excedente | Tarifa $600.00, 701 km | Excedente 1, recargo 3.00, total 4875.48 | Idéntico al esperado | ✅ |
| Datos inválidos | Tarifa -1; km -5 | Vuelve a pedir cada dato | Vuelve a pedir cada dato | ✅ |

**Observaciones:**

- Los km excedentes se deducen en su propia función y nunca se le piden al usuario, como indicaba el enunciado.
- Constantes, funciones puras y validación correctas.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//JOSE HERNANDEZ LOPEZ//
#include <iostream>
#include <iomanip>

using namespace std;

// Constantes
const int DIAS_SEMANA = 7;
const int KM_INCLUIDOS = 700;
const double TARIFA_KM_EXCEDENTE = 3.00;
const double TASA_IVA = 0.16;

// Prototipos
double calcularCostoRenta(double tarifa_diaria);
int calcularKmExcedente(int km_recorridos);
double calcularRecargo(int km_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);

int main()
{
    double tarifa_diaria;
    int km_recorridos;

    double costo_renta;
    int km_excedentes;
    double recargo;
    double subtotal;
    double iva;
    double total;

    // Captura de tarifa diaria
    do
    {
        cout << "Ingrese la tarifa diaria del auto: $";
        cin >> tarifa_diaria;

        if (tarifa_diaria < 0)
        {
            cout << "La tarifa no puede ser negativa." << endl;
        }

    } while (tarifa_diaria < 0);

    // Captura de kilometros recorridos
    do
    {
        cout << "Ingrese los kilometros recorridos: ";
        cin >> km_recorridos;

        if (km_recorridos < 0)
        {
            cout << "Los kilometros no pueden ser negativos." << endl;
        }

    } while (km_recorridos < 0);

    // Calculos
    costo_renta = calcularCostoRenta(tarifa_diaria);

    km_excedentes = calcularKmExcedente(km_recorridos);

    recargo = calcularRecargo(km_excedentes);

    subtotal = costo_renta + recargo;

    iva = calcularIVA(subtotal);

    total = calcularTotal(subtotal, iva);

    // Reporte final
    cout << fixed << setprecision(2);

    cout << endl;
    cout << "===== REPORTE DE RENTA =====" << endl;
    cout << "Tarifa diaria: $" << tarifa_diaria << endl;
    cout << "Costo de renta: $" << costo_renta << endl;
    cout << "Kilometros excedentes: " << km_excedentes << endl;
    cout << "Recargo: $" << recargo << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}

// Calcula el costo de la semana completa
double calcularCostoRenta(double tarifa_diaria)
{
    return DIAS_SEMANA * tarifa_diaria;
}

// Calcula los kilometros excedentes
// [Revisión, línea 93] Bien: los km excedentes se deducen aquí y no se le piden al usuario.
int calcularKmExcedente(int km_recorridos)
{
    if (km_recorridos > KM_INCLUIDOS)
    {
        return km_recorridos - KM_INCLUIDOS;
    }
    else
    {
        return 0;
    }
}

// Calcula el recargo por kilometros excedentes
double calcularRecargo(int km_excedente)
{
    return km_excedente * TARIFA_KM_EXCEDENTE;
}

// Calcula el IVA
double calcularIVA(double subtotal)
{
    return subtotal * TASA_IVA;
}

// Calcula el total
double calcularTotal(double subtotal, double iva)
{
    return subtotal + iva;
}
```

## Comentario general

Excelente trabajo. Ambos programas cumplen todos los requisitos y son correctos en todos los casos probados.
