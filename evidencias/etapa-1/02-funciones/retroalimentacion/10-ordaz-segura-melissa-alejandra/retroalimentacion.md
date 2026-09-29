# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 10 — Ordaz Segura Melissa Alejandra

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** No se entregó.

**Observaciones:**

- Los dos archivos que se subieron (EV1.1_..._p1.txt y EV1.1_..._p2.txt) contienen el mismo programa: el Programa 2 (tienda departamental). Solo difieren en unos espacios al final de la primera línea.
- El Programa 1 (facturación) no aparece en ninguno de los dos archivos.

## Programa 2 — Tienda departamental con descuento por compras acumuladas

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | $4,000.00 | Descuento 8%, 320.00, IVA 588.80, total 4268.80 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | $15,000.00 | Descuento 20% (tope), 3000.00, IVA 1920.00, total 13920.00 | Idéntico al esperado | ✅ |
| Justo en el tope | $10,000.00 | Descuento 20%, total 9280.00 | Idéntico al esperado | ✅ |
| Menos de $1,000 | $999.99 | Descuento 0% | Idéntico al esperado | ✅ |
| Parte entera de los miles | $4,999.99 | Descuento 8% (4 miles completos), total 5335.99 | Idéntico al esperado | ✅ |
| Datos inválidos | Monto 0 y -5 | Vuelve a pedir el monto | Lo vuelve a pedir | ✅ |

**Observaciones:**

- El cálculo del porcentaje (miles completos y tope máximo) es correcto, y el tope se aplica bien.
- Detalle: el divisor 1000.00 está escrito directo dentro de calcularPorcentajeDescuento; también debería ser una constante con nombre.
- Detalle: el descuento en pesos se calcula dos veces, en main y dentro de calcularSubtotal. Conviene una sola función calcularDescuento y usar su resultado.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// ALUMNA: MELISSA ALEJANDRA ORDAZ SEGURA    
// MATRICULA: [matrícula omitida]
// [Revisión, línea 3] Este mismo programa se subió también como p1; el Programa 1 (facturación) no se entregó.
// PROGRAMA 2 - TIENDA DEPARTAMENTAL
#include <iostream>
#include <iomanip>

using namespace std;

const double DESCUENTO_POR_MIL = 0.02;
const double DESCUENTO_MAXIMO = 0.20;
const double TASA_IVA = 0.16;

double calcularPorcentajeDescuento(double monto_acumulado);
double calcularSubtotal(double monto_acumulado, double porcentaje_descuento);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);

int main() {

	double monto_acumulado;
	double porcentaje_descuento;
	double descuento;
	double subtotal;
	double iva;
	double total;

	do {

		cout << "INGRESE EL MONTO ACUMULADO EN LA QUINCENA: $";
		cin >> monto_acumulado;

		if (monto_acumulado <= 0) {
			cout << "ERROR: EL MONTO DEBE SER MAYOR QUE 0." << endl;
		}

	} while (monto_acumulado <= 0);

	porcentaje_descuento = calcularPorcentajeDescuento(monto_acumulado);

	// [Revisión, línea 40] Detalle: el descuento se calcula aquí y otra vez dentro de calcularSubtotal; conviene una sola función.
	descuento = monto_acumulado * porcentaje_descuento;

	subtotal = calcularSubtotal(monto_acumulado, porcentaje_descuento);

	iva = calcularIVA(subtotal);

	total = calcularTotal(subtotal, iva);

	cout << fixed << setprecision(2);

	cout << endl;
	cout << "##########################################" << endl;
	cout << "          TIENDA DEPARTAMENTAL" << endl;
	cout << "##########################################" << endl;

	cout << "MONTO ACUMULADO     : $" << monto_acumulado << endl;
	cout << "DESCUENTO APLICADO  : " << porcentaje_descuento * 100 << "%" << endl;
	cout << "DESCUENTO           : $" << descuento << endl;
	cout << "SUBTOTAL            : $" << subtotal << endl;
	cout << "IVA                 : $" << iva << endl;
	cout << "TOTAL A PAGAR       : $" << total << endl;

	cout << "##########################################" << endl;

	return 0;
}

double calcularPorcentajeDescuento(double monto_acumulado) {

	int miles_completos;
	double porcentaje_descuento;

	// [Revisión, línea 72] Detalle: 1000.00 está escrito directo; también debería ser una constante con nombre.
	miles_completos = static_cast<int>(monto_acumulado / 1000.00);

	porcentaje_descuento = miles_completos * DESCUENTO_POR_MIL;

	// [Revisión, línea 76] Correcto: se aplica el tope máximo de descuento.
	if (porcentaje_descuento > DESCUENTO_MAXIMO) {
		porcentaje_descuento = DESCUENTO_MAXIMO;
	}

	return porcentaje_descuento;
}

double calcularSubtotal(double monto_acumulado, double porcentaje_descuento) {

	double descuento;

	descuento = monto_acumulado * porcentaje_descuento;

	return monto_acumulado - descuento;
}

double calcularIVA(double subtotal) {

	return subtotal * TASA_IVA;
}

double calcularTotal(double subtotal, double iva) {

	return subtotal + iva;
}
```

## Comentario general

El Programa 2 está bien resuelto, pero el Programa 1 no se entregó: se subió dos veces el mismo Programa 2.
