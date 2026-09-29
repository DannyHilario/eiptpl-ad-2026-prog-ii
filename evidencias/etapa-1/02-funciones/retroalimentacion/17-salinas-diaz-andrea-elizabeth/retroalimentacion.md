# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 17 — Salinas Diaz Andrea Elizabeth

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** No se entregó.

**Observaciones:**

- Solo se entregó un archivo. Aunque se llama EV1.1_salinasElizadeth_p1.txt, contiene el Programa 2 (renta de local comercial); el Programa 1 (facturación) no se entregó.

## Programa 2 — Renta de local comercial con recargo por consumo eléctrico

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 400 kWh | Excedente 0, subtotal 8000.00, IVA 1280.00, total 9280.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 700 kWh | Excedente 200, subtotal 8700.00, IVA 1392.00, total 10092.00 | Idéntico al esperado | ✅ |
| Límite: exactamente 500 kWh | 500 kWh | Excedente 0, total 9280.00 | Idéntico al esperado | ✅ |
| Fracción de kWh | 500.5 kWh | Excedente 0.50, total 9282.03 | Idéntico al esperado | ✅ |
| Datos inválidos | Consumo -1 | Vuelve a pedir el dato | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Los kWh excedentes se deducen en su propia función y nunca se le piden al usuario.
- Constantes, funciones puras, validación y reporte con dos decimales correctos.
- Las funciones se definen antes de main en lugar de usar prototipos; es válido, aunque en clase se pidió el esquema prototipo, main, definición.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

// Constantes
const double KWH_INCLUIDOS = 500;
const double RENTA_BASE = 8000.00;
const double TARIFA_EXCEDENTE = 3.50;
const double TASA_IVA = 0.16;

// Funciones
// [Revisión, línea 12] Bien: los kWh excedentes se deducen aquí y no se le piden al usuario. (Funciones definidas antes de main sin prototipos: es válido.)
double calcularKwhExcedente(double consumo_kwh) {
    if (consumo_kwh > KWH_INCLUIDOS) {
        return consumo_kwh - KWH_INCLUIDOS;
    } else {
        return 0;
    }
}

double calcularSubtotal(double kwh_excedente) {
    double recargo = kwh_excedente * TARIFA_EXCEDENTE;
    return RENTA_BASE + recargo;
}

double calcularIVA(double subtotal) {
    return subtotal * TASA_IVA;
}

double calcularTotal(double subtotal, double iva) {
    return subtotal + iva;
}

int main() {
    double consumo_kwh;
    double kwh_excedente;
    double subtotal;
    double iva;
    double total;

    // Captura y validación
    do {
        cout << "Ingresa el consumo electrico del mes en kWh: ";
        cin >> consumo_kwh;

        if (consumo_kwh < 0) {
            cout << "Error: el consumo no puede ser negativo." << endl;
        }

    } while (consumo_kwh < 0);

    // Calculos
    kwh_excedente = calcularKwhExcedente(consumo_kwh);
    subtotal = calcularSubtotal(kwh_excedente);
    iva = calcularIVA(subtotal);
    total = calcularTotal(subtotal, iva);

    // Resultados
    cout << fixed << setprecision(2);
    cout << "\n----- RESULTADO -----" << endl;
    cout << "kWh excedentes: " << kwh_excedente << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
```

## Comentario general

El Programa 2 está bien resuelto; el Programa 1 no se entregó.
