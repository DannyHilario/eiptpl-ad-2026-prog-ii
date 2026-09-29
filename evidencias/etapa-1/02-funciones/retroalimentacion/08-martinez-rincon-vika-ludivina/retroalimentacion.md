# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 08 — Martinez Rincon Vika Ludivina

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
| Datos inválidos | Cantidad 0 y -5; precio 0 y -1 | Vuelve a pedir cada dato hasta que sea mayor a 0 | Vuelve a pedir cada dato | ✅ |
| Formato de montos (dos decimales) | 60 piezas × $50.00 | "Subtotal: $3000.00", "Descuento: $360.00", "IVA (16%): $422.40", "Total: $3062.40" | "Subtotal: $3000", "Descuento: $360", "IVA (16%): $422.4", "Total: $3062.4" | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Estructura completa: prototipos antes de main, definiciones y llamadas correctas.
- Las funciones de cálculo no usan cin ni cout; solo main interactúa con el usuario.
- Límites de rango, porcentajes y tasa de IVA definidos como constantes con nombre.
- Validación de cantidad y precio con do-while, repitiendo la captura.
- Los montos se muestran sin formato de dos decimales (por ejemplo, 422.4 en lugar de 422.40).

**Recomendaciones:**

- Usa fixed y setprecision(2) de iomanip para mostrar los montos.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>


using namespace std;


const int MIN_DESC1 = 10;
const int MIN_DESC2 = 50;
const double PORC_DESC1 = 0.05;
const double PORC_DESC2 = 0.12;
const double TASA_IVA = 0.16;

double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main() {
	int numPiezas;
	double precioPieza;

	do {
		cout << "Cuantas piezas vas a comprar?: ";
		cin >> numPiezas;

		if (numPiezas <= 0) {
			cout << "Error: Ingresa una cantidad mayor a 0." << endl;
		}
	} while (numPiezas <= 0);

	do {
		cout << "Ingresa el precio por pieza: ";
		cin >> precioPieza;

		if (precioPieza <= 0) {
			cout << "Error: El precio debe ser mayor a 0." << endl;
		}
	} while (precioPieza <= 0);

	double sub = calcularSubtotal(numPiezas, precioPieza);
	double desc = calcularDescuento(numPiezas, sub);
	double base = sub - desc;
	double ivaCalculado = calcularIVA(base);
	double totalPagar = calcularTotal(base, ivaCalculado);

	// [Revisión, línea 46] Detalle: sin fixed y setprecision(2) los montos salen sin formato (por ejemplo, 422.4).
	cout << "-- Ticket de compra ---" << endl;
	cout << "Subtotal: $" << sub << endl;
	cout << "Descuento: $" << desc << endl;
	cout << "Base: $" << base << endl;
	cout << "IVA (16%): $" << ivaCalculado << endl;
	cout << "Total: $" << totalPagar << endl;

	return 0;
}


double calcularSubtotal(int cantidad, double precio_unitario) {
	return cantidad * precio_unitario;
}

// [Revisión, línea 61] Bien: función pura con constantes.
double calcularDescuento(int cantidad, double subtotal) {
	if (cantidad >= MIN_DESC2) {
		return subtotal * PORC_DESC2;
	} else if (cantidad >= MIN_DESC1) {
		return subtotal * PORC_DESC1;
	}
	return 0.0;
}

double calcularIVA(double base_gravable) {
	return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double iva) {
	return base_gravable + iva;
}
```

## Programa 2 — Plan de telefonía celular con datos incluidos

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 8 GB | Excedente 0, subtotal 299.00, IVA 47.84, total 346.84 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 14 GB | Excedente 4, subtotal 399.00, IVA 63.84, total 462.84 | Idéntico al esperado | ✅ |
| Límite: exactamente 10 GB | 10 GB | Excedente 0, total 346.84 | Idéntico al esperado | ✅ |
| Fracción de GB | 10.5 GB | Excedente 0.5, total 361.34 | Idéntico al esperado | ✅ |
| Datos inválidos | GB -1 | Vuelve a pedir el dato | Lo vuelve a pedir | ✅ |
| Formato de montos (dos decimales) | 10.5 GB | "Subtotal: 311.50", "IVA: 49.84", "Total a pagar: 361.34" | "Subtotal: 311.5", "IVA: 49.84", "Total a pagar: 361.34" | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Los GB excedentes se deducen en su propia función y nunca se le piden al usuario.
- Constantes, funciones puras y validación correctas.
- Mismo detalle de formato: los montos sin dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;



double calcularGbExcedente(double gb_consumidos);
double calcularSubtotal(double gb_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);

const double GB_INCLUIDOS_PLAN = 10.0;
const double COSTO_PLAN_BASE = 299.00;
const double TARIFA_GB_EXCEDENTE = 25.00;
const double TASA_IVA = 0.16;

int main() {

	double gb_consumidos, gb_excedente, subtotal, iva, total_pagar;

	do {

		cout << "Introduce los GB de datos consumidos en el mes: ";
		cin >> gb_consumidos;

		if (gb_consumidos < 0) {
			cout << "ERROR! Los GB consumidos no pueden ser negativos" << endl;
		}

	} while (gb_consumidos < 0);

	gb_excedente = calcularGbExcedente(gb_consumidos);
	subtotal = calcularSubtotal(gb_excedente);
	iva = calcularIVA(subtotal);
	total_pagar = calcularTotal(subtotal, iva);


	cout << "RECIBO PLAN TELEFONICO" << endl << endl;
	cout << "GB consumidos: " << gb_consumidos << endl;
	cout << "GB excedentes: " << gb_excedente << endl;
	cout << "Subtotal: " << subtotal << endl;
	cout << "IVA: " << iva << endl;
	cout << "Total a pagar: " << total_pagar << endl;

}

// [Revisión, línea 46] Bien: los GB excedentes se deducen aquí y no se le piden al usuario.
double calcularGbExcedente(double gb_consumidos) {
	if (gb_consumidos > GB_INCLUIDOS_PLAN) {
		return (gb_consumidos - GB_INCLUIDOS_PLAN);
	} else {
		return 0.0;
	}
}

double calcularSubtotal(double gb_excedente) {
	return (COSTO_PLAN_BASE + (gb_excedente *TARIFA_GB_EXCEDENTE));
}

double calcularIVA(double subtotal) {
	return (subtotal *TASA_IVA);
}

double calcularTotal(double subtotal, double iva) {
	return (subtotal + iva);
}
```

## Comentario general

Muy buen trabajo. Ambos programas son correctos y bien estructurados; solo falta el formato de dos decimales en los montos.
