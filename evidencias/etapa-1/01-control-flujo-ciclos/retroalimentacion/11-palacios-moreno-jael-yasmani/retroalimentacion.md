# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 11 — Palacios Moreno Jael Yasmani

## Programa 1 — Soporte técnico

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (más de 24 h) | Horas 10, 24, 24.5, 48 | Dentro de SLA 2, fuera 2 | Dentro 2, fuera 2 | ✅ |

**Observaciones:**

- Validación de la cantidad y, además, de que las horas no sean negativas.
- Clasificación correcta (24 exacto queda dentro de SLA) y reporte completo.

**Recomendaciones:**

- Agrega saltos de línea después de los mensajes de error y del título "REPORTE FINAL"; ahora todo queda pegado en la misma línea.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Programa 1: Soporte Técnico (Tickets)
#include <iostream>

using namespace std;

int main() {
    int totalTickets;
    int dentroSLA = 0; 
    int fueraSLA = 0;  

    cout << "REVISION DE TICKETS DE SOPORTE \n";
    do {
        cout << "Cuantos tickets vas a revisar?: ";
        cin >> totalTickets;

        if (totalTickets <= 0) {
            // [Revisión, línea 17] Detalle: falta endl; el siguiente mensaje queda pegado.
            cout << "pon un numero mayor";
        }
    } while (totalTickets <= 0);
    for (int i = 1; i <= totalTickets; i++) {
        double horas;

        cout << "Ticket #" << i << " - Horas que tardo: ";
        cin >> horas;

        // [Revisión, línea 26] Bien: validación extra de horas no negativas.
        while (horas < 0) {
            cout << "Las horas no pueden ser negativas. Intenta de nuevo: ";
            cin >> horas;
        }

        // [Revisión, línea 31] Correcto: 24 exacto queda dentro de SLA.
        if (horas > 24) {
            cout << "FUERA de SLA\n";
            fueraSLA++;
        } else {
            cout << "DENTRO de SLA\n";
            dentroSLA++;
        }
    }

    // [Revisión, línea 40] Detalle: falta endl después del título.
    cout << "  REPORTE FINAL ";
    cout << "Total de tickets revisados: " << totalTickets << "\n";
    cout << "Tickets DENTRO de SLA     : " << dentroSLA << "\n";
    cout << "Tickets FUERA de SLA      : " << fueraSLA << "\n";

    return 0;
}
```

## Programa 2 — Lavandería

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Vuelve a pedir la opción | Vuelve a pedirla | ✅ |
| Validación de kilos | Kilos 0 y -3 | Vuelve a pedir los kilos | Vuelve a pedirlos | ✅ |
| Servicios y reporte | Normal 2.5 kg y 1 kg, Delicada 3 kg, Edredón 1 kg | Normal 2 servicios ($63), Delicada 1 ($84), Edredón 1 ($35), 4 servicios, $182 | Idéntico al esperado | ✅ |
| Formato de montos | Normal 1.25 kg, Delicada 2.5 kg, cerrar | Montos con dos decimales: "$22.50", "$70.00"; reporte Edredón "$0.00", total "$92.50" | "Total a pagar: $22.5", "Total a pagar: $70"; en el reporte "$22.5", "$70", "$0" y en el dinero total "$92.5" | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Constantes, validaciones y cálculos correctos; los kilos aceptan decimales como pedía el enunciado.

**Recomendaciones:**

- El menú y el título del reporte no tienen endl, por lo que se imprimen todos en una sola línea y son difíciles de leer.
- Muestra los montos con dos decimales (fixed y setprecision).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Programa 2: Lavanderia
#include <iostream>

using namespace std;

int main() {

    // [Revisión, línea 8] Bien: precios como constantes.
    const double NORMAL = 18.00;
    const double DELICADA = 28.00;
    const double EDREDON = 35.00;

    int cantNormal = 0;
    int cantDelicada = 0;
    int cantEdredon = 0;

    double totalNormal = 0;
    double totalDelicada = 0;
    double totalEdredon = 0;

    int opcion;

    do {
        // [Revisión, línea 23] Detalle: sin endl, todo el menú se imprime en una sola línea.
        cout << "MENU LAVANDERIA";
        cout << "1 Ropa normal ($18/kg)";
        cout << "2 Ropa delicada ($28/kg)";
        cout << "3 Edredon ($35/kg)";
        cout << "4 Cerrar mostrador";
        cout << "Elige una opcion (1-4): ";
        cin >> opcion;

        while (opcion < 1 || opcion > 4) {
            cout << "Opcion no valida. Intenta de nuevo (1-4): ";
            cin >> opcion;
        }
        switch (opcion) {
            case 1: {
                double kilos;
                cout << "Cuantos kilos de ropa normal son?: ";
                cin >> kilos;

                while (kilos <= 0) {
                    cout << "Los kilos deben ser mayor a 0. Intenta de nuevo: ";
                    cin >> kilos;
                }

                double cobro = kilos * NORMAL;
                cantNormal++;
                totalNormal += cobro;
                cout << "Total a pagar: $" << cobro << "\n";
                break;
            }
            case 2: {
                double kilos;
                cout << "Cuantos kilos de ropa delicada son?: ";
                cin >> kilos;

                while (kilos <= 0) {
                    cout << "Los kilos deben ser mayor a 0: ";
                    cin >> kilos;
                }

                double cobro = kilos * DELICADA;
                cantDelicada++;
                totalDelicada += cobro;
                cout << "Total a pagar: $" << cobro << "\n";
                break;
            }
            case 3: {
                double kilos;
                cout << "Cuantos kilos de edredon son?: ";
                cin >> kilos;

                while (kilos <= 0) {
                    cout << "Los kilos deben ser mayor a 0: ";
                    cin >> kilos;
                }

                double cobro = kilos * EDREDON;
                cantEdredon++;
                totalEdredon += cobro;
                cout << "Total a pagar: $" << cobro << "\n";
                break;
            }
            case 4:
                cout << "Cerrando mostrador";
                break;
        }

    } while (opcion != 4);
    int serviciosTotales = cantNormal + cantDelicada + cantEdredon;
    double dineroTotal = totalNormal + totalDelicada + totalEdredon;

    cout << "  CORTE DE CAJA DEL DIA  ";
    cout << "Ropa Normal   : " << cantNormal << " servicios | Recaudado: $" << totalNormal << "\n";
    cout << "Ropa Delicada : " << cantDelicada << " servicios | Recaudado: $" << totalDelicada << "\n";
    cout << "Edredones     : " << cantEdredon << " servicios | Recaudado: $" << totalEdredon << "\n";
    cout << "Servicios Totales : " << serviciosTotales << "\n";
    cout << "Dinero Total      : $" << dineroTotal << "\n";

    return 0;
}
```

## Comentario general

Excelente trabajo. La lógica de ambos programas es correcta; solo falta cuidar los saltos de línea en la presentación.
