# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 18 — Salinas Meza Cesar Eduardo

## Programa 1 — Consumo de datos móviles

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (más de 5 GB) | Consumos 3, 5, 5.1, 10 | Dentro 2, exceden 2 | Dentro 2, exceden 2 | ✅ |

**Observaciones:**

- Validación de la cantidad y de que el consumo no sea negativo; clasificación correcta (5 exacto está dentro del plan) y reporte completo.

**Recomendaciones:**

- Cuida la redacción de los mensajes ("axcendieron", "ESCRIBISTE MAL LA POSITIVA", "consumo de lineas tipo").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Alumno: Salinas Meza Cesar Eduardo 
//Matrícula:[matrícula omitida]
//Programa 1 - Consumo de datos móviles


#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int N;

    // Pedir número de líneas
    do {
        cout << "-------------> cuantas lineas se van a revisar?: ";
        cin >> N;

        if (N <= 0)
            cout << " *ERROR 3312: ESCRIBISTE MAL LA POSITIVA*\n";

    } while (N <= 0);

   
    int dentroPlan = 0, excedenPlan = 0;
    double consumo;

    for (int i = 1; i <= N; i++) {
        do {
            cout << "------------> consumo de lineas tipo: " << i << " (GB): ";
            cin >> consumo;

            // [Revisión, línea 32] Bien: validación de consumo no negativo.
            if (consumo < 0)
                cout << "[ERROR 45: El consumo es Negativo]\n";

        } while (consumo < 0);

        // Clasificación
        // [Revisión, línea 38] Correcto: 5 exacto está dentro del plan.
        if (consumo > 5.0)
            excedenPlan++;
        else
            dentroPlan++;
    }

    // Reporte final
    cout << "\n************ [REPORTE DE LINEAS] *************\n\n";
    cout << "Total en lineas revisadas =  " << N << endl;
    cout << "Lineas dentro del plan =  " << dentroPlan << endl;
    // [Revisión, línea 48] Detalle de redacción: "axcendieron".
    cout << "Lineas que axcendieron =  " << excedenPlan << endl;

    return 0;
}
```

## Programa 2 — Recargas de tiempo aire

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Vuelve a pedir la opción | Vuelve a pedirla | ✅ |
| Recargas y reporte | Básico, Intermedio, Premium, Básico, Cerrar | Básico 2 ($100.00), Intermedio 1 ($100.00), Premium 1 ($200.00), 4 recargas, $400.00 | Idéntico al esperado | ✅ |

**Observaciones:**

- Constantes, validación, switch y reporte con dos decimales correctos; buen detalle documentar las abreviaturas de las variables.

**Recomendaciones:**

- Agrega un salto de línea después del título del reporte; ahora el primer dato queda en la misma línea.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Alumno: Salinas Meza Cesar Eduardo
//Matrícula: [matrícula omitida]
//Programa 2 - Recargas de tiempo aire

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

	// Constantes de los precios
	// PB: Plan Basico | PI: Plan Intermedio | PP: Plan Premium
	// [Revisión, línea 13] Bien: constantes documentadas.
	const double PB = 50.00;
	const double PI = 100.00;
	const double PP = 200.00;

	// Contadores de recargas
	// RB: Recargas Basicas | RI: Recargas Intermedias | RP: Recargas Premium
	int RB = 0, RI = 0, RP = 0;

	int op;

	do {
		cout << "\n-------------> T I E N D A   D E   R E C A R G A S <-------------\n\n";
		cout << " 1. Plan Basico: $50.00 " << endl;
		cout << " 2. Plan Intermedio: $100.00 " << endl;
		cout << " 3. Plan Premium: $200.00 " << endl;
		cout << " 4. == CERRAR CAJA == " << endl << endl;
		cout << " SELECCIONE UNA OPCION: ";
		cin >> op;

		// Validar opcion
		while (op < 1 || op > 4) {
			cout << " ERROR. Seleccione un numero del 1 al 4: ";
			cin >> op;
		}

		if (op != 4) {

			switch (op) {

				case 1:
					RB++;
					cout << " Recarga del Plan Basico registrada " << endl;
					break;

				case 2:
					RI++;
					cout << " Recarga del Plan Intermedio registrada " << endl;
					break;

				case 3:
					RP++;
					cout << " Recarga del Plan Premium registrada " << endl;
					break;
			}
		}

	} while (op != 4);

	// Calcular montos
	double TB = RB * PB;
	double TI = RI * PI;
	double TP = RP * PP;

	int totalRecargas = RB + RI + RP;
	double totalDinero = TB + TI + TP;

	// Reporte final
	cout << fixed << setprecision(2);

	// [Revisión, línea 72] Detalle: falta endl; el primer dato queda en la misma línea del título.
	cout << "************ [REPORTE DEL DIA] *************";

	cout << " Total de Recargas Basicas: " << RB << endl;
	cout << " Monto total Plan Basico: $" << TB << endl << endl;

	cout << " Total de Recargas Intermedias: " << RI << endl;
	cout << " Monto total Plan Intermedio: $" << TI << endl << endl;

	cout << " Total de Recargas Premium: " << RP << endl;
	cout << " Monto total Plan Premium: $" << TP << endl << endl;

	cout << "---------------------------------------------\n";
	cout << " Recargas totales realizadas: " << totalRecargas << endl;
	cout << " Monto total del dia: $" << totalDinero << endl;

	return 0;
}
```

## Comentario general

Excelente trabajo. Ambos programas cumplen con todo lo solicitado.
