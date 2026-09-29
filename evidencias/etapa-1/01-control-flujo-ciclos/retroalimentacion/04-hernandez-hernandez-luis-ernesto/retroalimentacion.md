# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 04 — Hernández Hernández Luis Ernesto

## Programa 1 — Radar de velocidad

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (umbral 80 km/h) | Velocidades 60, 80, 80.5, 120 | Dentro 2, exceso 2 | Dentro 2, exceso 2 | ✅ |

**Observaciones:**

- Validación correcta con do-while, clasificación correcta (80 exacto queda dentro del límite) y reporte completo.

**Recomendaciones:**

- Al mensaje "Cuántos vehículos se van a registran" le falta el signo de interrogación y un espacio, y dice "registran" en lugar de "registrar".

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

int main() {
    int nVehiculos;

    // Pedir número de vehículos, validando que sea positivo
    do {
        // [Revisión, línea 9] Detalle: faltan "?" y un espacio al final; dice "registran" en lugar de "registrar".
        cout << "Cuántos vehículos se van a registran";
        cin >> nVehiculos;
        if (nVehiculos <= 0) {
            cout << "El número debe ser positivo. Intenta de nuevo.\n";
        }
    } while (nVehiculos <= 0);

    int dentroLimite = 0;
    int excesoVelocidad = 0;
    double velocidad;

    // Registrar velocidades
    for (int i = 1; i <= nVehiculos; i++) {
        cout << "Introduce la velocidad del vehículo " << i << " (km/h): ";
        cin >> velocidad;

        // [Revisión, línea 25] Correcto: 80 exacto queda dentro del límite.
        if (velocidad > 80) {
            cout << " Vehículo en exceso de velocidad.\n";
            excesoVelocidad++;
        } else {
            cout << " Vehículo dentro del límite.\n";
            dentroLimite++;
        }
    }

    // Reporte final
    cout << "\n===== REPORTE FINAL =====\n";
    cout << "Total de vehículos registrados: " << nVehiculos << endl;
    cout << "Dentro del límite: " << dentroLimite << endl;
    cout << "En exceso de velocidad: " << excesoVelocidad << endl;

    return 0;
}
```

## Programa 2 — Taquilla de estadio

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a mostrar el menú | Correcto | ✅ |
| Validación de cantidad | Cantidades 0 y -3 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Ventas y reporte | General 2+1, Preferente 3, Palco 1 | General 3 ($450), Preferente 3 ($1050), Palco 1 ($800), 7 boletos, $2300 | Idéntico al esperado | ✅ |
| Formato de montos | General 3, Preferente 3, Palco 1, cerrar (opción 4) | Montos con dos decimales: $450.00, $1050.00, $800.00, total $2300.00 | "Monto: $450", "Monto: $1050", "Monto: $800", "Total recaudado: $2300" (sin decimales) | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Constantes bien definidas y usadas también para mostrar el menú.
- La validación contempla incluso entradas no numéricas (cin.fail, cin.clear, cin.ignore): va más allá de lo pedido.
- Reporte completo.

**Recomendaciones:**

- Muestra los montos con dos decimales (fixed y setprecision).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

// Definición de constantes para los precios
const double PRECIO_GENERAL = 150.00;
const double PRECIO_PREFERENTE = 350.00;
const double PRECIO_PALCO = 800.00;

int main() {
    // Variables para acumular boletos y montos
    int boletosGeneral = 0, boletosPreferente = 0, boletosPalco = 0;
    double montoGeneral = 0.0, montoPreferente = 0.0, montoPalco = 0.0;

    int opcion;

    do {
        // Mostrar menú
        cout << "\n--- Taquilla del Estadio ---\n";
        cout << "1) Entrada General ($" << PRECIO_GENERAL << ")\n";
        cout << "2) Entrada Preferente ($" << PRECIO_PREFERENTE << ")\n";
        cout << "3) Entrada Palco ($" << PRECIO_PALCO << ")\n";
        cout << "4) Cerrar taquilla\n";
        cout << "Seleccione una opción (1-4): ";
        cin >> opcion;

        // Validar opción
        // [Revisión, línea 27] Muy bien: valida también entradas no numéricas.
        if (cin.fail() || opcion < 1 || opcion > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: opción inválida. Intente de nuevo.\n";
            continue;
        }

        if (opcion != 4) {
            int cantidad;
            do {
                cout << "Ingrese la cantidad de boletos: ";
                cin >> cantidad;

                // [Revisión, línea 40] Muy bien: misma validación robusta para la cantidad.
                if (cin.fail() || cantidad <= 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error: cantidad inválida. Debe ser un número entero positivo.\n";
                    cantidad = -1; // fuerza repetir
                }
            } while (cantidad <= 0);

            // Procesar venta según tipo de entrada
            switch (opcion) {
                case 1:
                    boletosGeneral += cantidad;
                    montoGeneral += cantidad * PRECIO_GENERAL;
                    break;
                case 2:
                    boletosPreferente += cantidad;
                    montoPreferente += cantidad * PRECIO_PREFERENTE;
                    break;
                case 3:
                    boletosPalco += cantidad;
                    montoPalco += cantidad * PRECIO_PALCO;
                    break;
            }
            cout << "Venta registrada exitosamente.\n";
        }

    } while (opcion != 4);

    // Reporte final
    int totalBoletos = boletosGeneral + boletosPreferente + boletosPalco;
    double totalMonto = montoGeneral + montoPreferente + montoPalco;

    cout << "\n--- Reporte de Ventas ---\n";
    cout << "Boletos General: " << boletosGeneral << " | Monto: $" << montoGeneral << "\n";
    cout << "Boletos Preferente: " << boletosPreferente << " | Monto: $" << montoPreferente << "\n";
    cout << "Boletos Palco: " << boletosPalco << " | Monto: $" << montoPalco << "\n";
    cout << "Total de boletos vendidos: " << totalBoletos << "\n";
    cout << "Total recaudado: $" << totalMonto << "\n";

    cout << "Taquilla cerrada.\n";

    return 0;
}
```

## Comentario general

Excelente trabajo. Ambos programas son correctos, robustos y fáciles de leer.
