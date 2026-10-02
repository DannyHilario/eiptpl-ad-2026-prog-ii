# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

## Programa 1 — Entregas de paquetería

**Compilación:** Tal como se entregó, no compila: el encabezado de las líneas 2 a 5 (Evidencia, Alumno, Matrícula, Programa 1) está escrito con asteriscos, pero no está dentro de un comentario porque falta abrirlo con `/*` y cerrarlo con `*/`. Con `/*` en la línea 1 (vacía) y `*/` en la línea 6 (en blanco) compila sin errores, y las pruebas de abajo se hicieron así.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (más de 3 días) | Días 2, 3, 4, 10 | A tiempo 2, retrasadas 2 | A tiempo 2, retrasadas 2 | ✅ |

**Observaciones:**

- Validación de la cantidad de envíos con do-while y mensaje de error claro.
- Clasificación correcta (3 días exactos es entrega a tiempo) con un mensaje para cada envío, y reporte completo.
- Nombres de variables claros.

**Recomendaciones:**

- Recuerda que un comentario de bloque se abre con /* y se cierra con */; los asteriscos al inicio de cada línea son solo decoración.
- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] Aquí falta abrir el comentario con /*: sin él, el compilador lee el encabezado de las líneas 2 a 5 como código.

 * Evidencia - Etapa 1, Dimensión 4 (Aplicación)
 * Alumno: Rodriguez Martinez Angel Ricardo 
 * Matricula: [matrícula omitida]
 * Programa 1 - Entregas de paqueteria
 // [Revisión, línea 6] Aquí falta cerrar el comentario con */.
 

#include <iostream>

using namespace std;

int main() {
    int cantidadEnvios;
    int entregasATiempo = 0;
    int entregasRetrasadas = 0;
    int dias;

    // [Revisión, línea 18] Bien: validación de la cantidad de envíos.
    do {
        cout << "Ingrese la cantidad de envios a revisar: ";
        cin >> cantidadEnvios;
        
        if (cantidadEnvios <= 0) {
            cout << "Numero invalido. Por favor ingrese un numero positivo." << endl;
        }
    } while (cantidadEnvios <= 0);

    cout << endl;

    for (int i = 1; i <= cantidadEnvios; i++) {
        cout << "Envio #" << i << " - ¿Cuantos dias tardo la entrega?: ";
        cin >> dias;

        // [Revisión, línea 33] Correcto: 3 días exactos es entrega a tiempo.
        if (dias > 3) {
            cout << "  -> Entrega retrasada" << endl;
            entregasRetrasadas++; 
        } else {
            cout << "  -> Entrega a tiempo" << endl;
            entregasATiempo++; 
        }
    }

    
    cout << "======================" << endl;
    cout << "           REPORTE FINAL           " << endl;
    cout << "======================" << endl;
    cout << "Total de envios revisados: " << cantidadEnvios << endl;
    cout << "Entregas a tiempo:         " << entregasATiempo << endl;
    cout << "Entregas retrasadas:       " << entregasRetrasadas << endl;
    cout << "======================" << endl;

    return 0;
}
```

## Programa 2 — Envíos de paquetería

**Compilación:** Mismo caso que en el Programa 1: tal como se entregó, no compila porque el encabezado no está encerrado entre `/*` y `*/`. Con `/*` en la línea 1 y `*/` en la línea 6 compila sin errores, y las pruebas de abajo se hicieron así.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a pedir la opción | Correcto | ✅ |
| Validación de cantidad | Cantidades 0 y -3 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Envíos y reporte | Opciones 0 y 7; Documento con cantidades 0 y -3, luego 2; Paquete chico 3; Paquete grande 1; Documento 1; cerrar (opción 4) | Documentos 3, chicos 3, grandes 1, 7 envíos, $765 | Cantidades y montos correctos | ✅ |
| Formato de montos | Mismo caso | Montos con dos decimales: $195.00, $360.00, $210.00, total $765.00 | "Dinero recaudado: $195", "$360", "$210", "GRAN TOTAL RECAUDADO: $765" (sin decimales) | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Precios definidos como constantes y validación de la opción y de la cantidad con while, sin salir del programa.
- Los montos se calculan con el precio constante por la cantidad de envíos; contadores, acumuladores y reporte completos.

**Recomendaciones:**

- Muestra los montos con dos decimales usando fixed y setprecision(2) de la biblioteca iomanip.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] Aquí falta abrir el comentario con /*: sin él, el compilador lee el encabezado de las líneas 2 a 5 como código.

 * Evidencia - Etapa 1, Dimensión 4 (Aplicación)
 * Alumno: Rodriguez Martinez Angel Ricardo 
 * Matricula: [matrícula omitida]
 * Programa 2 - EEnvíos de paquetería
 // [Revisión, línea 6] Aquí falta cerrar el comentario con */.
 

#include <iostream>

using namespace std;

int main() {
    
    // [Revisión, línea 14] Bien: precios como constantes.
    const float PRECIO_DOC = 65.00;
    const float PRECIO_CHICO = 120.00;
    const float PRECIO_GRANDE = 210.00;

    
    int cont_doc = 0;
    int cont_chico = 0;
    int cont_grande = 0;

    
    float total_doc = 0;
    float total_chico = 0;
    float total_grande = 0;

    int opcion;
    int cantidad;

    
    do {
        cout << "--- MENU DE PAQUETERIA ---" << endl;
        cout << "1. Documento ($65.00)" << endl;
        cout << "2. Paquete chico ($120.00)" << endl;
        cout << "3. Paquete grande ($210.00)" << endl;
        cout << "4. Cerrar el mostrador" << endl;
        cout << "Elige una opcion (1-4): ";
        cin >> opcion;

        
        while (opcion < 1 || opcion > 4) {
            cout << "Error: Opcion invalida. Intenta de nuevo (1-4): ";
            cin >> opcion;
        }

        
        if (opcion != 4) {
            cout << "Cuantos envios de esta categoria vas a registrar? ";
            cin >> cantidad;

            
            // [Revisión, línea 53] Bien: validación de la cantidad sin salir del programa.
            while (cantidad <= 0) {
                cout << "Error: La cantidad debe ser mayor a 0. Intenta de nuevo: ";
                cin >> cantidad;
            }

            
            switch (opcion) {
                case 1:
                    cont_doc = cont_doc + cantidad;
                    total_doc = total_doc + (cantidad * PRECIO_DOC);
                    break;
                case 2:
                    cont_chico = cont_chico + cantidad;
                    total_chico = total_chico + (cantidad * PRECIO_CHICO);
                    break;
                case 3:
                    cont_grande = cont_grande + cantidad;
                    total_grande = total_grande + (cantidad * PRECIO_GRANDE);
                    break;
            }
        }

    } while (opcion != 4);

   
    int total_envios = cont_doc + cont_chico + cont_grande;
    float total_dinero = total_doc + total_chico + total_grande;

    
    cout << "====================" << endl;
    cout << "      REPORTE FINAL DEL DIA" << endl;
    cout << "====================" << endl;
    
    cout << "Documentos:" << endl;
    cout << " - Cantidad registrada: " << cont_doc << endl;
    // [Revisión, línea 88] Detalle: sin fixed y setprecision(2) los montos salen sin decimales ($195 en lugar de $195.00).
    cout << " - Dinero recaudado: $" << total_doc << endl;

    cout << "Paquetes chicos:" << endl;
    cout << " - Cantidad registrada: " << cont_chico << endl;
    cout << " - Dinero recaudado: $" << total_chico << endl;

    cout << "Paquetes grandes:" << endl;
    cout << " - Cantidad registrada: " << cont_grande << endl;
    cout << " - Dinero recaudado: $" << total_grande << endl;

    cout << "------------------" << endl;
    cout << "TOTAL DE ENVIOS REALIZADOS: " << total_envios << endl;
    cout << "GRAN TOTAL RECAUDADO: $" << total_dinero << endl;
    cout << "=====================" << endl;

    return 0;
}
```

## Comentario general

Ninguno de los dos archivos compila tal como se entregó porque el comentario del encabezado no está abierto con /* ni cerrado con */. Con esas dos marcas, ambos programas funcionan correctamente; solo falta mostrar los montos con dos decimales.
