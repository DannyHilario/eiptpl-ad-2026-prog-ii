# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

## Programa 1 — Monitoreo de CO2 en un aula

**Compilación:** **No compila.** El compilador marca error en la línea 1: el archivo empieza con el texto "Programa hecho por: Jesús Guadalupe Ramírez Mejorado" y "Programa 1" sin marcarlos como comentario.

**Observaciones:**

- El compilador intenta interpretar ese texto como código de C++ y falla. Bastaba con poner // al inicio de esas dos líneas.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] NO COMPILA: estas dos líneas no son comentario y el compilador intenta leerlas como código. Bastaba con escribir // al inicio de cada una.
Programa hecho por: Jesús Guadalupe Ramírez Mejorado 
Programa 1

#include <iostream>
using namespace std;

int main() {

    int aulas;
    float co2;
    int normal = 0;
    int limite = 0;

    do {
        cout << "Ingresa la cantidad de aulas: ";
        cin >> aulas;

        if (aulas <= 0) {
            cout << "Ingresa un numero positivo." << endl;
        }

    } while (aulas <= 0);

    for (int i = 1; i <= aulas; i++) {

        cout << "Ingresa el nivel de CO2 del aula " << i << ": ";
        cin >> co2;

        if (co2 > 1000) {
            cout << "Excede el limite, necesita ventilarse." << endl;
            limite++;
        }
        else {
            cout << "Nivel normal." << endl;
            normal++;
        }
    }

    cout << endl;
    cout << "REPORTE" << endl;
    cout << "Total de aulas: " << aulas << endl;
    cout << "Aulas normales: " << normal << endl;
    cout << "Aulas que exceden el limite: " << limite << endl;

    return 0;
}
```

## Programa 2 — Taller mecánico

**Compilación:** **No compila.** El mismo error que en el Programa 1: las líneas "Programa hecho por..." y "Programa 2" no están marcadas como comentario.

**Observaciones:**

- Bastaba con poner // al inicio de esas dos líneas.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] NO COMPILA: estas dos líneas no son comentario y el compilador intenta leerlas como código. Bastaba con escribir // al inicio de cada una.
Programa hecho por: Jesús Guadalupe Ramírez Mejorado 
Programa 2

#include <iostream>
using namespace std;

int main() {

    const float PRECIO_AUTO = 350.00;
    const float PRECIO_CAMIONETA = 480.00;
    const float PRECIO_MOTOCICLETA = 220.00;

    int opcion;

    int serviciosAuto = 0;
    int serviciosCamioneta = 0;
    int serviciosMotocicleta = 0;

    float montoAuto = 0;
    float montoCamioneta = 0;
    float montoMotocicleta = 0;
    float montoTotal = 0;

    do {
        cout << "\n--- TALLER MECANICO ---" << endl;
        cout << "1. Auto" << endl;
        cout << "2. Camioneta" << endl;
        cout << "3. Motocicleta" << endl;
        cout << "4. Cerrar turno" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        while (opcion < 1 || opcion > 4) {
            cout << "Opcion invalida. Ingresa una opcion del 1 al 4: ";
            cin >> opcion;
        }

        switch (opcion) {

            case 1:
                serviciosAuto++;
                montoAuto += PRECIO_AUTO;
                montoTotal += PRECIO_AUTO;
                cout << "Servicio de auto registrado." << endl;
                break;

            case 2:
                serviciosCamioneta++;
                montoCamioneta += PRECIO_CAMIONETA;
                montoTotal += PRECIO_CAMIONETA;
                cout << "Servicio de camioneta registrado." << endl;
                break;

            case 3:
                serviciosMotocicleta++;
                montoMotocicleta += PRECIO_MOTOCICLETA;
                montoTotal += PRECIO_MOTOCICLETA;
                cout << "Servicio de motocicleta registrado." << endl;
                break;

            case 4:
                cout << "\nTurno cerrado." << endl;
                break;
        }

    } while (opcion != 4);

    cout << "\n--- REPORTE DEL TURNO ---" << endl;
    cout << "Servicios de auto: " << serviciosAuto << endl;
    cout << "Monto de autos: $" << montoAuto << endl;

    cout << "Servicios de camioneta: " << serviciosCamioneta << endl;
    cout << "Monto de camionetas: $" << montoCamioneta << endl;

    cout << "Servicios de motocicleta: " << serviciosMotocicleta << endl;
    cout << "Monto de motocicletas: $" << montoMotocicleta << endl;

    cout << "Servicios totales: "
         << serviciosAuto + serviciosCamioneta + serviciosMotocicleta << endl;

    cout << "Monto total del turno: $" << montoTotal << endl;

    return 0;
}
```

## Comentario general

Ninguno de los dos programas compila por el mismo motivo: el encabezado con tu nombre no está escrito como comentario. Es un error pequeño, pero impide que el programa se ejecute.
