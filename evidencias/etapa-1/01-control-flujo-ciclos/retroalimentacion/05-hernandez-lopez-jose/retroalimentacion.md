# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 05 — Hernandez Lopez Jose

## Programa 1 — Monitoreo de consumo eléctrico

**Compilación:** **No compila.** El compilador marca errores en la línea 60: el archivo termina a la mitad de la instrucción cout << "Casas, sin cerrar el texto.

**Observaciones:**

- El archivo entregado está incompleto: se corta en el reporte final, por lo que faltan el resto del reporte, el return 0; y la llave de cierre de main.
- Lo que alcanza a verse (validación de la cantidad de casas y clasificación con umbral de 300 kWh) iba bien encaminado, pero un programa que no compila no se puede probar.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Después de guardar el archivo .txt, ábrelo para confirmar que tiene el código completo antes de subirlo.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

int main() {

    int cantidad_casas;
    float consumo;

    int casas_normales = 0;
    int casas_alto_consumo = 0;

    do {

        system("cls");

        cout << "********* MONITOREO DE CONSUMO ELECTRICO *********" << endl << endl;

        cout << "Cuantas casas se van a revisar: ";
        cin >> cantidad_casas;

        if (cantidad_casas <= 0) {
            cout << "ERROR! La cantidad debe ser positiva." << endl;
            system("pause");
        }

    } while (cantidad_casas <= 0);


    for (int casa = 1; casa <= cantidad_casas; casa++) {

        system("cls");

        cout << "********* CASA " << casa << " *********" << endl << endl;

        cout << "Introduce el consumo del mes en kWh: ";
        cin >> consumo;

        // [Revisión, línea 38] Bien: umbral de 300 kWh correcto.
        if (consumo > 300) {

            cout << "Alto consumo" << endl;

            casas_alto_consumo++;

        } else {

            cout << "Consumo normal" << endl;

            casas_normales++;
        }

        system("pause");
    }


    system("cls");

    cout << "********* REPORTE FINAL *********" << endl << endl;

    cout << "Total de casas revisadas: " << cantidad_casas << endl;
    // [Revisión, línea 60] NO COMPILA: el archivo se corta aquí, a mitad del texto. Faltan el resto del reporte, return 0; y la llave } que cierra main.
    cout << "Casas
```

## Programa 2 — Farmacia

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a mostrar el menú | Correcto | ✅ |
| Validación de cantidad | Cantidades 0 y -3 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Ventas y reporte | Paracetamol 2+1, Gel 3, Cubrebocas 1 | Paracetamol 3 ($135), Gel 3 ($114), Cubrebocas 1 ($25), 7 piezas, $274 | Idéntico al esperado | ✅ |
| Formato de montos | Paracetamol 3, Gel 3, Cubrebocas 1, cerrar (opción 4) | Montos con dos decimales: $135.00, $114.00, $25.00, total $274.00 | "Monto recaudado: $135", "$114", "$25", "Monto total del dia: $274" (sin decimales) | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Precios como constantes, validaciones con do-while, switch para acumular por producto y reporte completo.
- Código muy bien organizado y con nombres descriptivos.

**Recomendaciones:**

- Muestra los montos con dos decimales (fixed y setprecision).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

// [Revisión, línea 4] Bien: precios como constantes.
const float PRECIO_PARACETAMOL = 45.00;
const float PRECIO_GEL = 38.00;
const float PRECIO_CUBREBOCAS = 25.00;

int main() {

    int opcion;
    int cantidad;

    int piezas_paracetamol = 0;
    int piezas_gel = 0;
    int piezas_cubrebocas = 0;

    float total_paracetamol = 0;
    float total_gel = 0;
    float total_cubrebocas = 0;
    float total_dia = 0;


    do {

        system("cls");

        cout << "********* FARMACIA *********" << endl << endl;

        cout << "1. Paracetamol (caja) - $" << PRECIO_PARACETAMOL << endl;
        cout << "2. Gel antibacterial - $" << PRECIO_GEL << endl;
        cout << "3. Cubrebocas (paquete) - $" << PRECIO_CUBREBOCAS << endl;
        cout << "4. Cerrar caja" << endl << endl;

        cout << "Selecciona una opcion: ";
        cin >> opcion;


        if (opcion < 1 || opcion > 4) {

            cout << endl;
            cout << "ERROR! Opcion no valida." << endl;

            system("pause");

        } else if (opcion != 4) {

            // [Revisión, línea 47] Bien: validación de la cantidad con do-while.
            do {

                cout << endl;
                cout << "Cuantas piezas quieres comprar: ";
                cin >> cantidad;

                if (cantidad <= 0) {

                    cout << "ERROR! La cantidad debe ser positiva." << endl;
                }

            } while (cantidad <= 0);


            switch (opcion) {

                case 1:

                    piezas_paracetamol = piezas_paracetamol + cantidad;

                    total_paracetamol = total_paracetamol
                                      + cantidad * PRECIO_PARACETAMOL;

                    break;


                case 2:

                    piezas_gel = piezas_gel + cantidad;

                    total_gel = total_gel
                              + cantidad * PRECIO_GEL;

                    break;


                case 3:

                    piezas_cubrebocas = piezas_cubrebocas + cantidad;

                    total_cubrebocas = total_cubrebocas
                                     + cantidad * PRECIO_CUBREBOCAS;

                    break;
            }

            cout << endl;
            cout << "Venta registrada correctamente." << endl;

            system("pause");
        }

    } while (opcion != 4);


    total_dia = total_paracetamol + total_gel + total_cubrebocas;


    system("cls");

    cout << "********* REPORTE FINAL *********" << endl << endl;

    cout << "PARACETAMOL" << endl;
    cout << "Piezas vendidas: " << piezas_paracetamol << endl;
    // [Revisión, línea 111] Detalle: sin fixed y setprecision(2) los montos salen sin decimales.
    cout << "Monto recaudado: $" << total_paracetamol << endl << endl;

    cout << "GEL ANTIBACTERIAL" << endl;
    cout << "Piezas vendidas: " << piezas_gel << endl;
    cout << "Monto recaudado: $" << total_gel << endl << endl;

    cout << "CUBREBOCAS" << endl;
    cout << "Piezas vendidas: " << piezas_cubrebocas << endl;
    cout << "Monto recaudado: $" << total_cubrebocas << endl << endl;

    cout << "Total de piezas vendidas: "
         << piezas_paracetamol + piezas_gel + piezas_cubrebocas << endl;

    cout << "Monto total del dia: $" << total_dia << endl;

    cout << endl;
    cout << "********* FIN DEL REPORTE *********" << endl;

    system("pause");

    return 0;
}
```

## Comentario general

El Programa 2 está muy bien resuelto; el Programa 1 no se pudo evaluar porque el archivo entregado está incompleto y no compila.
