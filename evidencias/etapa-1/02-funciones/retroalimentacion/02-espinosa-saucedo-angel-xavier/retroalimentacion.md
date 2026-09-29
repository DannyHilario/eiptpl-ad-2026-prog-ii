# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 02 — Espinosa Saucedo Angel Xavier

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 5 piezas × $100.00 | Subtotal 500.00, descuento 0.00, IVA 80.00, total 580.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 60 piezas × $50.00 | Subtotal 3000.00, descuento 360.00, IVA 422.40, total 3062.40 | Idéntico al esperado | ✅ |
| Límite superior del rango 1 | 9 piezas × $100.00 | Descuento 0.00, total 1044.00 | Idéntico al esperado | ✅ |
| Límite inferior del rango 2 | 10 piezas × $100.00 | Descuento 50.00 (5%), total 1102.00 | Idéntico al esperado | ✅ |
| Límite superior del rango 2 | 49 piezas × $100.00 | Descuento 245.00 (5%), total 5399.80 | Idéntico al esperado | ✅ |
| Límite inferior del rango 3 | 50 piezas × $100.00 | Descuento 600.00 (12%), total 5104.00 | Idéntico al esperado | ✅ |
| Datos inválidos | Cantidad 0 y -5; precio 0 y -1 | Vuelve a pedir cada dato hasta que sea mayor a 0 | Vuelve a pedir cada dato, pero sin mostrar ningún mensaje de error | ✅ |

**Observaciones:**

- Estructura completa: prototipos antes de main, definiciones y llamadas correctas.
- Las funciones de cálculo no usan cin ni cout; solo main interactúa con el usuario.
- Límites de rango, porcentajes y tasa de IVA definidos como constantes con nombre.
- La validación funciona, pero no muestra un mensaje que explique al usuario por qué se le vuelve a pedir el dato.

**Recomendaciones:**

- Agrega un mensaje de error dentro del do-while de validación.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
///AngelXavierEspinosaSaucedo
#include <iostream>
#include <iomanip>

using namespace std;


const int RANGO_MEDIO = 10, RANGO_ALTO = 50;
const double DESC_BAJO = 0.0, DESC_MEDIO = 0.05, DESC_ALTO = 0.12;
const double TASA_IVA = 0.16;


double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main() {
	int cantidad;
	double precio;


	// [Revisión, línea 23] Detalle: la validación repite la captura, pero no muestra ningún mensaje de error al usuario.
	do {
		cout << "Cantidad de piezas: ";
		cin >> cantidad;
	} while (cantidad <= 0);

	do {
		cout << "Precio unitario: ";
		cin >> precio;
	} while (precio <= 0);


	double subtotal = calcularSubtotal(cantidad, precio);
	double descuento = calcularDescuento(cantidad, subtotal);
	double baseGravable = subtotal - descuento;
	double iva = calcularIVA(baseGravable);
	double total = calcularTotal(baseGravable, iva);


	cout << fixed << setprecision(2);
	cout << "Subtotal: " << subtotal << endl;
	cout << "Descuento: " << descuento << endl;
	cout << "IVA: " << iva << endl;
	cout << "Total a pagar: " << total << endl;

	return 0;
}


double calcularSubtotal(int cantidad, double precio_unitario) {
	return cantidad * precio_unitario;
}

// [Revisión, línea 55] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal) {
	if (cantidad >= RANGO_ALTO)
		return subtotal * DESC_ALTO;
	if (cantidad >= RANGO_MEDIO)
		return subtotal * DESC_MEDIO;
	return subtotal * DESC_BAJO;
}

double calcularIVA(double base_gravable) {
	return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double iva) {
	return base_gravable + iva;
}
```

## Programa 2 — Comisión de ventas con bono por meta

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | Monto $40,000.00 | Comisión 3200.00, bono no aplica, ISR 320.00, neto 2880.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | Monto $70,000.00 | Comisión 5600.00, bono 560.00, ISR 616.00, neto 5544.00 | Idéntico al esperado | ✅ |
| Límite: exactamente la meta | Monto $50,000.00 | Sin bono (no supera la meta), neto 3600.00 | Idéntico al esperado | ✅ |
| Datos inválidos | Monto 0 y -5 | Vuelve a pedir el monto | Lo vuelve a pedir, sin mensaje de error | ✅ |

**Observaciones:**

- Funciones puras, constantes y cálculo correcto; el bono muestra "no aplica" cuando es 0, como se pidió.
- Mismo detalle que en el Programa 1: la validación no muestra mensaje de error.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
///AngelXavierEspinosaSaucedo
#include <iostream>
#include <iomanip>

using namespace std;


const double PCT_COMISION = 0.08;
const double META_VENTAS = 50000.0;
const double PCT_BONO = 0.10;
const double TASA_ISR = 0.10;


double calcularComision(double monto_vendido, double porcentaje_comision);
double calcularBono(double monto_vendido, double comision);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);

int main() {
	double montoVendido;


	// [Revisión, línea 23] Detalle: igual que en el Programa 1, falta un mensaje de error.
	do {
		cout << "Monto vendido en la quincena: ";
		cin >> montoVendido;
	} while (montoVendido <= 0);


	double comision = calcularComision(montoVendido, PCT_COMISION);
	double bono = calcularBono(montoVendido, comision);
	double ingresoTotal = comision + bono;
	double isr = calcularISR(ingresoTotal);
	double pagoNeto = calcularPagoNeto(ingresoTotal, isr);


	cout << fixed << setprecision(2);
	cout << "Comision: " << comision << endl;
	// [Revisión, línea 38] Bien: muestra "no aplica" cuando el bono es 0.
	if (bono > 0) {
		cout << "Bono: " << bono << endl;
	} else {
		cout << "Bono: no aplica" << endl;
	}
	cout << "ISR: " << isr << endl;
	cout << "Pago neto: " << pagoNeto << endl;

	return 0;
}


double calcularComision(double monto_vendido, double porcentaje_comision) {
	return monto_vendido * porcentaje_comision;
}

// [Revisión, línea 54] Correcto: el bono solo aplica si el monto SUPERA la meta.
double calcularBono(double monto_vendido, double comision) {
	if (monto_vendido > META_VENTAS) {
		return comision * PCT_BONO;
	}
	return 0.0;
}

double calcularISR(double ingreso_total) {
	return ingreso_total * TASA_ISR;
}

double calcularPagoNeto(double ingreso_total, double isr) {
	return ingreso_total - isr;
}
```

## Comentario general

Muy buen trabajo. Ambos programas son correctos y bien estructurados; solo falta mostrar mensajes de error en las validaciones.
