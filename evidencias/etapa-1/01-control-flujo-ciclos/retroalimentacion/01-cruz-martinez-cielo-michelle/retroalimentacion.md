# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 01 — Cruz Martinez Cielo Michelle

## Programa 1 — Registro de asistencia

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (umbral 800) | Horas 745, 800, 801, 1430 | Puntuales 2, retardos 2 | Puntuales 2, retardos 2 | ✅ |

**Observaciones:**

- Validación correcta de la cantidad de empleados con do-while.
- Además validaste que la hora sea una hora real (0 a 2359 y minutos menores a 60): no se pedía y está muy bien pensado.
- La clasificación usa correctamente hora <= 800 y el caso límite (800) cuenta como puntual.
- Reporte completo: total, puntuales y retardos.

**Recomendaciones:**

- La variable horas se calcula pero nunca se usa (el compilador lo advierte); si no la necesitas, elimínala.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

int main() {
    int empleados;
    int hora;
    int puntuales = 0;
    int retardos = 0;

    // Validar cantidad de empleados
    do {
        cout << "Cuantos empleados se van a registrar? ";
        cin >> empleados;

        if (empleados <= 0) {
            cout << "Error: la cantidad debe ser un numero positivo." << endl;
        }
    } while (empleados <= 0);

    // Registrar la entrada de cada empleado
    for (int i = 1; i <= empleados; i++) {
        do {
            cout << endl;
            cout << "Empleado " << i << endl;
            cout << "Ingrese la hora de entrada (ejemplo: 815 o 1430): ";
            cin >> hora;

            // [Revisión, línea 28] Esta variable se calcula pero nunca se usa (el compilador lo advierte).
            int horas = hora / 100;
            int minutos = hora % 100;

            // [Revisión, línea 31] Bien: validación extra de que la hora sea real (no se pedía).
            if (hora < 0 || hora > 2359 || minutos >= 60) {
                cout << "Error: ingrese una hora valida." << endl;
            } else {
                break;
            }
        } while (true);

        // Clasificar la entrada
        // [Revisión, línea 39] Correcto: 800 exacto cuenta como puntual.
        if (hora <= 800) {
            cout << "Resultado: Puntual" << endl;
            puntuales++;
        } else {
            cout << "Resultado: Retardo" << endl;
            retardos++;
        }
    }

    // Reporte final
    cout << endl;
    cout << "========== REPORTE FINAL ==========" << endl;
    cout << "Total de empleados: " << empleados << endl;
    cout << "Empleados puntuales: " << puntuales << endl;
    cout << "Empleados con retardo: " << retardos << endl;
    cout << "===================================" << endl;

    return 0;
}
```

## Programa 2 — Caseta de cobro

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a pedir | Mensaje de error y vuelve a pedir | ✅ |
| Registro y reporte | Automóvil, Autobús, Camión, Automóvil, Finalizar | Autos 2 ($90.00), autobuses 1 ($90.00), camiones 1 ($150.00), total 4 vehículos, $330.00 | Idéntico al esperado | ✅ |

**Observaciones:**

- Tarifas definidas como constantes con nombres descriptivos.
- Validación de la opción con while, sin salir del programa.
- Contadores y acumuladores separados por tipo; el reporte incluye todo lo solicitado con dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Tarifas constantes
    // [Revisión, línea 7] Bien: tarifas definidas como constantes.
    const double TARIFA_AUTOMOVIL = 45.00;
    const double TARIFA_AUTOBUS = 90.00;
    const double TARIFA_CAMION = 150.00;

    // Contadores
    int automoviles = 0;
    int autobuses = 0;
    int camiones = 0;

    // Acumuladores
    double cobroAutomoviles = 0.00;
    double cobroAutobuses = 0.00;
    double cobroCamiones = 0.00;

    int opcion;

    do {
        cout << endl;
        cout << "========== CASETA DE COBRO ==========" << endl;
        cout << "1. Automovil - $45.00" << endl;
        cout << "2. Autobus - $90.00" << endl;
        cout << "3. Camion de carga - $150.00" << endl;
        cout << "4. Finalizar turno" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Validar la opcion
        // [Revisión, línea 34] Bien: valida la opción sin salir del programa.
        while (opcion < 1 || opcion > 4) {
            cout << "Error: la opcion debe estar entre 1 y 4." << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
        }

        switch (opcion) {
            case 1:
                automoviles++;
                cobroAutomoviles += TARIFA_AUTOMOVIL;
                cout << "Automovil registrado. Cobro: $"
                     << fixed << setprecision(2)
                     << TARIFA_AUTOMOVIL << endl;
                break;

            case 2:
                autobuses++;
                cobroAutobuses += TARIFA_AUTOBUS;
                cout << "Autobus registrado. Cobro: $"
                     << fixed << setprecision(2)
                     << TARIFA_AUTOBUS << endl;
                break;

            case 3:
                camiones++;
                cobroCamiones += TARIFA_CAMION;
                cout << "Camion de carga registrado. Cobro: $"
                     << fixed << setprecision(2)
                     << TARIFA_CAMION << endl;
                break;

            case 4:
                cout << "Finalizando turno..." << endl;
                break;
        }

    } while (opcion != 4);

    // Calcular totales
    int totalVehiculos = automoviles + autobuses + camiones;
    double totalTurno = cobroAutomoviles + cobroAutobuses + cobroCamiones;

    // Reporte final
    cout << endl;
    cout << "========== REPORTE FINAL ==========" << endl;
    cout << "Automoviles: " << automoviles
         << " | Cobrado: $" << fixed << setprecision(2)
         << cobroAutomoviles << endl;

    cout << "Autobuses: " << autobuses
         << " | Cobrado: $" << fixed << setprecision(2)
         << cobroAutobuses << endl;

    cout << "Camiones de carga: " << camiones
         << " | Cobrado: $" << fixed << setprecision(2)
         << cobroCamiones << endl;

    cout << "-----------------------------------" << endl;
    cout << "Total de vehiculos: " << totalVehiculos << endl;
    cout << "Efectivo total del turno: $"
         << fixed << setprecision(2)
         << totalTurno << endl;
    cout << "===================================" << endl;

    return 0;
}
```

## Comentario general

Excelente trabajo. Ambos programas cumplen con todo lo solicitado, el código está bien organizado y los nombres de variables son claros.
