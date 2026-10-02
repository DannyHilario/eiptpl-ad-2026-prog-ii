# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

## Programa 1 — Monitoreo de CO2 en un aula

**Compilación:** Tal como se entregó, no compila: las líneas 1 ("Programa hecho por: Jesús Guadalupe Ramírez Mejorado") y 2 ("Programa 1") son texto que no está marcado como comentario; bastaba con poner `//` al inicio de cada una. Con esas dos líneas comentadas compila sin errores, y las pruebas de abajo se hicieron así.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (más de 1000 ppm) | CO2 999.9, 1000, 1000.1, 1500 | Normales 2, exceden 2 | Normales 2, exceden 2 | ✅ |

**Observaciones:**

- Validación de la cantidad de aulas con do-while.
- Clasificación correcta (1000 exacto es nivel normal) con un mensaje para cada aula, y reporte completo.

**Recomendaciones:**

- Recuerda que el encabezado con tu nombre debe ir como comentario (// o /* */).
- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] Esta línea y la siguiente no son comentario y el compilador las lee como código; cada una debe empezar con //.
Programa hecho por: Jesús Guadalupe Ramírez Mejorado 
Programa 1

#include <iostream>
using namespace std;

int main() {

    int aulas;
    float co2;
    int normal = 0;
    int limite = 0;

    // [Revisión, línea 14] Bien: validación de la cantidad de aulas.
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

        // [Revisión, línea 29] Correcto: 1000 exacto es nivel normal.
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

**Compilación:** Mismo caso que en el Programa 1: tal como se entregó, no compila porque las líneas 1 y 2 ("Programa hecho por..." y "Programa 2") no están marcadas como comentario. Con esas dos líneas comentadas compila sin errores, y las pruebas de abajo se hicieron así.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a pedir la opción | Correcto | ✅ |
| Servicios y reporte | Opciones 0 y 7, luego Auto, Camioneta, Motocicleta, Auto, Cerrar (opción 4) | Autos 2, camionetas 1, motocicletas 1, 4 servicios, $1400 | Cantidades y montos correctos | ✅ |
| Formato de montos | Mismo caso | Montos con dos decimales: $700.00, $480.00, $220.00, total $1400.00 | "Monto de autos: $700", "Monto de camionetas: $480", "Monto de motocicletas: $220", "Monto total del turno: $1400" (sin decimales) | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Precios definidos como constantes con nombres descriptivos.
- Validación de la opción con while, sin salir del programa.
- Contadores y acumuladores separados por tipo; el reporte incluye todo lo solicitado.

**Recomendaciones:**

- Muestra los montos con dos decimales usando fixed y setprecision(2) de la biblioteca iomanip.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] Esta línea y la siguiente no son comentario y el compilador las lee como código; cada una debe empezar con //.
Programa hecho por: Jesús Guadalupe Ramírez Mejorado 
Programa 2

#include <iostream>
using namespace std;

int main() {

    // [Revisión, línea 9] Bien: precios como constantes.
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

        // [Revisión, línea 33] Bien: valida la opción sin salir del programa.
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
    // [Revisión, línea 70] Detalle: sin fixed y setprecision(2) los montos salen sin decimales ($700 en lugar de $700.00).
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

Ninguno de los dos archivos compila tal como se entregó porque el encabezado con tu nombre no está escrito como comentario. Con esas líneas comentadas, ambos programas funcionan correctamente; solo falta mostrar los montos con dos decimales.
