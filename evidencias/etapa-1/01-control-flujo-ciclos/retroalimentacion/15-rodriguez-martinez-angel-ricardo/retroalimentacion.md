# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

## Programa 1 — Entregas de paquetería

**Compilación:** **No compila.** El compilador marca error desde la línea 2: el encabezado (Evidencia - Etapa 1, Alumno, Matricula, Programa 1) está escrito con asteriscos al inicio de cada línea, pero sin abrir el comentario con /* ni cerrarlo con */.

**Observaciones:**

- El compilador intenta interpretar ese encabezado como código de C++ y falla. Bastaba con encerrarlo entre /* y */.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp

 // [Revisión, línea 2] NO COMPILA: este encabezado no está dentro de un comentario. Faltó abrirlo con /* (antes de esta línea) y cerrarlo con */ (después de la línea 6).
 * Evidencia - Etapa 1, Dimensión 4 (Aplicación)
 * Alumno: Rodriguez Martinez Angel Ricardo 
 * Matricula: [matrícula omitida]
 * Programa 1 - Entregas de paqueteria
 

#include <iostream>

using namespace std;

int main() {
    int cantidadEnvios;
    int entregasATiempo = 0;
    int entregasRetrasadas = 0;
    int dias;

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

**Compilación:** **No compila.** El mismo error que en el Programa 1: el encabezado no está encerrado entre /* y */.

**Observaciones:**

- Bastaba con encerrar el encabezado entre /* y */.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp

 // [Revisión, línea 2] NO COMPILA: este encabezado no está dentro de un comentario. Faltó abrirlo con /* (antes de esta línea) y cerrarlo con */ (después de la línea 6).
 * Evidencia - Etapa 1, Dimensión 4 (Aplicación)
 * Alumno: Rodriguez Martinez Angel Ricardo 
 * Matricula: [matrícula omitida]
 * Programa 2 - EEnvíos de paquetería
 

#include <iostream>

using namespace std;

int main() {
    
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

Ninguno de los dos programas compila por el mismo motivo: el comentario del encabezado no está abierto ni cerrado. Es un error pequeño, pero impide que el programa se ejecute.
