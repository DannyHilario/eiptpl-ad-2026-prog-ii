# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 10 — Ordaz Segura Melissa Alejandra

## Programa 1 — Control de calidad del agua

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (6.5 a 8.5 inclusive) | pH 6.5, 8.5, 6.4, 9 | Dentro 2, fuera 2 | Dentro 2, fuera 2 | ✅ |

**Observaciones:**

- Validación, clasificación con rango inclusivo y reporte correctos. Mensajes claros para el usuario.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Alumno: Ordaz Segura Melissa Alejandra Matrícula: [matrícula omitida]
//Programa 1 — Control de calidad del agua


#include <iostream>
using namespace std;

int main() {
	int muestra;
	double PH;
	int dentRang = 0;
	int fueraRang = 0;


	do {
		cout << "RANGO" << endl;
		cout << "          6.5 y 8.5" << endl << endl;
		cout << "CUANTAS MUESTRAS SE VAN A REVISAR --> ";
		cin >> muestra;

		// [Revisión, línea 21] Bien: validación de la cantidad.
		if (muestra <= 0) {
			cout << ">>>ERROR: EL NÚMERO DE MUESTRAS DEBE SER POSITIVO<<< " << endl;
		}

	} while (muestra <= 0);

	for (int i = 1; i <= muestra; i++) {
		cout << "INGRESE EL NIVEL DE PH DE LA MUESTRA --> " << i << ": ";
		cin >> PH;

		// [Revisión, línea 31] Correcto: rango inclusivo de 6.5 a 8.5.
		if (PH >= 6.5 && PH <= 8.5) {
			cout << "RESULTADO --> DENTRO DE RANGO NORMAL ´´´´´´" << endl;
			dentRang++;

		} else {
			cout << "RESULTADO --> FUERA DE RANGO *******" << endl;
			fueraRang++;
		}
	}
	cout << "/////////////////////////////////////" << endl;
	cout << "       REPORTE DE CALIDAD DEL AGUA" << endl;
	cout << endl << endl;
	cout << "/////////////////////////////////////" << endl;
	cout << "TOTAL DE MUESTRAS REVISADAS: " << muestra << endl;
	cout << "MUESTRA DENTRO DE RANGO:    " << dentRang << endl;
	cout << "MUESTRA FUERA DE RANGO:     " << fueraRang << endl;



	return 0;
}
```

## Programa 2 — Panadería

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a mostrar el menú | Correcto | ✅ |
| Validación de cantidad | Cantidades 0 y -3 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Ventas y reporte | Bolillo 2+1, Concha 3, Dona 1 | Bolillos 3 ($10.50), Conchas 3 ($36.00), Donas 1 ($15.00), 7 piezas, $61.50 | Idéntico al esperado | ✅ |

**Observaciones:**

- Constantes, validaciones, switch, contadores y acumuladores correctos; reporte completo con dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Alumno: Ordaz Segura Melissa Alejandra Matrícula: [matrícula omitida]//Programa 2 — Panadería
//Programa 2 — Panadería


#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int bolillos = 0;
	int conchas = 0;
	int donas = 0;
	int totalPiezas = 0;
	int opcion;
	int cantidad;

	// [Revisión, línea 17] Bien: precios como constantes.
	const double PRE_BOLILLO = 3.50;
	const double PRE_CONCHA = 12.00;
	const double PRE_DONA = 15.00;

	double totalBolillos = 0.0;
	double totalConchas = 0.0;
	double totalDonas = 0.0;
	double totalDia = 0.0;

	do {
		cout << "            [ PANADERIA ]         " << endl;
		cout << "====================================" << endl;
		cout << "1. BOLILLOS - $" << fixed << setprecision(2) << PRE_BOLILLO << endl;
		cout << "2. CONCHAS  - $" << PRE_CONCHA << endl;
		cout << "3. DONAS    - $" << PRE_DONA << endl;
		cout << "4. CERRAR CAJA" << endl;
		cout << "====================================" << endl;
		cout << "SELECCIONE LOS PRODUTOS ";

		cin >> opcion;

		if (opcion < 1 || opcion > 4) {
			cout << "ERROR: OPCION INVALIDA. DEBE SER ENTRE |1 Y 4 |" << endl;
		}

		if (opcion >= 1 && opcion <= 3) {

			// [Revisión, línea 44] Bien: validación de la cantidad.
			do {
				cout << "¿CUANTAS PIEZAS DESEA COMPRAR? ";
				cin >> cantidad;

				if (cantidad <= 0) {
					cout << "ERROR: LA CANTIDAD DEBE SER UN NUMERO ENTERO POSITIVO." << endl;
				}

			} while (cantidad <= 0);

			// CALCULAR Y ACUMULAR LA VENTA
			switch (opcion) {

				case 1:
					bolillos += cantidad;
					totalBolillos += cantidad * PRE_BOLILLO;
					cout << "VENTA REGISTRADA: " << cantidad << " BOLILLO(S)." << endl;
					break;

				case 2:
					conchas += cantidad;
					totalConchas += cantidad * PRE_CONCHA;
					cout << "VENTA REGISTRADA: " << cantidad << " CONCHA(S)." << endl;
					break;

				case 3:
					donas += cantidad;
					totalDonas += cantidad * PRE_DONA;
					cout << "VENTA REGISTRADA: " << cantidad << " DONA(S)." << endl;
					break;
			}

			totalPiezas += cantidad;
		}

	} while (opcion != 4);

	totalDia = totalBolillos + totalConchas + totalDonas;


	cout << "              REPORTE DEL DIA" << endl;
	cout << "============================================" << endl;

	cout << fixed << setprecision(2);

	cout << "BOLILLOS VENDIDOS:       " << bolillos << endl;
	cout << "MONTO POR BOLILLOS:      $" << totalBolillos << endl;

	cout << "CONCHAS VENDIDAS:        " << conchas << endl;
	cout << "MONTO POR CONCHAS:       $" << totalConchas << endl;

	cout << "DONAS VENDIDAS:           " << donas << endl;
	cout << "MONTO POR DONAS:          $" << totalDonas << endl;

	cout << "--------------------------------------------" << endl;
	cout << "PIEZAS TOTALES VENDIDAS: " << totalPiezas << endl;
	cout << "MONTO TOTAL DEL DIA:     $" << totalDia << endl;
	cout << "============================================" << endl;
	cout << "CAJA CERRADA. GRACIAS POR SU COMPRA." << endl;

	return 0;
}
```

## Comentario general

Excelente trabajo. Ambos programas cumplen con todo lo solicitado y están bien organizados.
