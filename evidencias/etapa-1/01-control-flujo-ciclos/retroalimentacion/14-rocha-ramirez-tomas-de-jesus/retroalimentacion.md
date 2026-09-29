# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 14 — Rocha Ramirez Tomas De Jesus

## Programa 1 — Nivel de tanques de gas

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (menor a 15%) | Niveles 14.9, 15, 50, 5 | Bajo 2, normal 2 | Bajo 2, normal 2 | ✅ |

**Observaciones:**

- Validación de la cantidad y, además, del rango de 0% a 100% en el nivel del tanque.
- Clasificación correcta (15 exacto es nivel normal) y reporte completo.

**Recomendaciones:**

- Mostrar el resultado de cada tanque al capturarlo haría el programa más claro.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//TOMAS DE JESUS ROCHA RAMIREZ  G:223  TC:SC
//Programa 1  Nivel de tanques de gas
//MATRICULA:[matrícula omitida]

#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	int N;
	// contador
	do {
		cout << "|CUANTOS TANQUES DESEA REVISAR ";
		cout << "|";
		cin >> N;

		if (N <= 0)
			cout << "ERROR LA CANTIDAD DE TANQUES DEBE DE SER POSITIVA (+)\n";

	} while (N <= 0);

	int contNormal = 0, contBajo = 0;
	double nivel;

	for (int i = 1; i <= N; i++) {

		do {
			cout << "Nivel de llenado del tanque " << i << " (%): ";
			cin >> nivel;

			// [Revisión, línea 33] Bien: validación extra del rango de 0 a 100.
			if (nivel < 0 || nivel > 100)
				cout << "ERROR. El nivel debe estar entre 0% y 100%\n";

		} while (nivel < 0 || nivel > 100);

		// [Revisión, línea 38] Correcto: 15 exacto es nivel normal.
		if (nivel < 15)
			contBajo++;
		else
			contNormal++;
	}

	cout << "---------- |REPORTE DE TANQUES| ----------";
	cout << endl << endl;

	cout << "|Total de tanques revisados: [ " << N << " ]" << endl;

	cout << "|Tanques con nivel normal: [ " << contNormal << " ]" << endl;

	cout << "|Tanques con nivel bajo: [ " << contBajo << " ]" << endl;

	return 0;
}
```

## Programa 2 — Autolavado

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a mostrar el menú | Correcto | ✅ |
| Lavados y reporte | Auto, Camioneta, Camión, Auto, Cerrar | Autos 2 ($160.00), Camionetas 1 ($110.00), Camiones 1 ($180.00), 4 lavados, $450.00 | Idéntico al esperado | ✅ |

**Observaciones:**

- Constantes, validación, switch y reporte con dos decimales correctos.

**Recomendaciones:**

- Declaraste la variable N y no la usas (el compilador lo advierte).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//TOMAS DE JESUS ROCHA RAMIREZ  G:223  TC:SC
//Programa 2  Autolavado
//MATRICULA:[matrícula omitida]
#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	// [Revisión, línea 11] Bien: precios como constantes.
	const double PRE_AUTO = 80.00;
	const double PRE_CAMIONETA = 110.00;
	const double PRE_CAMION = 180.00;
	int lavadosAuto = 0;
	int lavadosCamioneta = 0;
	int lavadosCamion = 0;

	int opcion;
	// [Revisión, línea 19] Esta variable N se declara pero no se usa.
	int N;

// MENU
	do {
		cout << "----------| AUTOLAVADO |----------" << endl;
		cout << "1* Auto = [$80.00]" << endl;
		cout << "2* Camioneta = [$110.00]" << endl;
		cout << "3* Camion = [$180.00]" << endl;
		cout << "4* [Cerrar turno]" << endl;

		cout << "-----[OPCIONES]------------" << endl;
		cin >> opcion;

		// Validacion
		if (opcion < 1 || opcion > 4) {
			cout << "ERROR INTENTA NUEVAMENTE CON OTRO NUMERO - ENTRE 1-4 PORFAVOR" << endl;
		} else {
			switch (opcion) {

				case 1:
					lavadosAuto++;
					cout << "Lavado de Auto registrado." << endl;
					break;

				case 2:
					lavadosCamioneta++;
					cout << "Lavado de Camioneta registrado." << endl;
					break;

				case 3:
					lavadosCamion++;
					cout << "Lavado de Camion registrado." << endl;
					break;

				case 4:
					cout << "Cerrar turno" << endl;
					break;
			}
		}

	} while (opcion != 4);

	double montoAuto = lavadosAuto * PRE_AUTO;
	double montoCamioneta = lavadosCamioneta * PRE_CAMIONETA;
	double montoCamion = lavadosCamion * PRE_CAMION;

	// Calcular el monto total
	int lavadosTotales = lavadosAuto + lavadosCamioneta + lavadosCamion;
	double montoTotal = montoAuto + montoCamioneta + montoCamion;

	// Reporte o la imprecion
	cout << fixed << setprecision(2);

	cout << "------------------------------------" << endl;
	cout << "      |  REPORTE DEL TURNO  |      " << endl;
	cout << "------------------------------------" << endl;

	cout << "AUTO:" << endl;
	cout << "Lavados= " << lavadosAuto << endl;
	cout << "Monto recaudado: $" << montoAuto << endl;

	cout << "CAMIONETA:" << endl;
	cout << "Lavados= " << lavadosCamioneta << endl;
	cout << "Monto recaudado: $" << montoCamioneta << endl;

	cout << "CAMION:" << endl;
	cout << "Lavados= " << lavadosCamion << endl;
	cout << "Monto recaudado: $" << montoCamion << endl;

	cout << "---------------------------------" << endl;
	cout << "Lavados totales: " << lavadosTotales << endl;
	cout << "Monto total del turno: $" << montoTotal << endl;
	cout << "=================================" << endl;

	return 0;
}
```

## Comentario general

Excelente trabajo. Ambos programas cumplen con todo lo solicitado.
