# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 17 — Salinas Diaz Andrea Elizabeth

## Programa 1 — Sensor de ocupación de estacionamiento

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (95% o más) | Ocupación 95, 99, 94.9, 50 | Lleno 2, disponible 2 | Lleno 2, disponible 2 | ✅ |

**Observaciones:**

- Validación de la cantidad y del rango de 0 a 100, clasificación correcta (95 exacto es lleno) y reporte completo.
- Código bien organizado y con comentarios útiles.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

int main()
{
    int mediciones;
    int lleno = 0;
    int disponible = 0;
    float ocupacion;

    cout << "PROGRAMA 1 - SENSOR DE OCUPACION DE ESTACIONAMIENTO" << endl;

    // Pedir numero de mediciones
    do
    {
        cout << "Cuantas mediciones se van a revisar: ";
        cin >> mediciones;

        if (mediciones <= 0)
        {
            cout << "Error. Debe ser un numero positivo." << endl;
        }

    } while (mediciones <= 0);

    // Pedir las mediciones
    for (int i = 1; i <= mediciones; i++)
    {
        do
        {
            cout << "Ingrese el porcentaje de ocupacion " << i << ": ";
            cin >> ocupacion;

            // [Revisión, línea 34] Bien: validación extra del rango de 0 a 100.
            if (ocupacion < 0 || ocupacion > 100)
            {
                cout << "Error. El porcentaje debe estar entre 0 y 100." << endl;
            }

        } while (ocupacion < 0 || ocupacion > 100);

        // Clasificar estacionamiento
        // [Revisión, línea 42] Correcto: 95 exacto es lleno.
        if (ocupacion >= 95)
        {
            cout << "Estacionamiento LLENO" << endl;
            lleno++;
        }
        else
        {
            cout << "Estacionamiento DISPONIBLE" << endl;
            disponible++;
        }
    }

    // Reporte final
    cout << endl;
    cout << "===== REPORTE FINAL =====" << endl;
    cout << "Total de mediciones: " << mediciones << endl;
    cout << "Estacionamientos disponibles: " << disponible << endl;
    cout << "Estacionamientos llenos: " << lleno << endl;

    return 0;
}
```

## Programa 2 — Terminal de autobuses foráneos

**Compilación:** No se entregó.

**Observaciones:**

- No se entregó el archivo de este programa.

## Comentario general

El Programa 1 está bien resuelto. Faltó entregar el Programa 2, que valía la mitad de la evidencia.
