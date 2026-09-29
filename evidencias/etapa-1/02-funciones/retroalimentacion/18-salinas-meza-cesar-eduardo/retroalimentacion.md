# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 18 — Salinas Meza Cesar Eduardo

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

**Observaciones:**

- Estructura completa: prototipos antes de main, definiciones y llamadas correctas.
- Las funciones de cálculo no usan cin ni cout; solo main interactúa con el usuario.
- Límites de rango, porcentajes y tasa de IVA definidos como constantes con nombre.
- Validación de cantidad y precio con do-while, repitiendo la captura.
- Las funciones se definen antes de main en lugar de usar prototipos; es válido en C++.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//cesar Eduardo salinas Meza
//Evidencia

#include <iostream>
#include <iomanip>
using namespace std;

// Constantes
const int LIMITE_DESCUENTO_1 = 10;
const int LIMITE_DESCUENTO_2 = 50;

const double DESCUENTO_1 = 0.00;
const double DESCUENTO_2 = 0.05;
const double DESCUENTO_3 = 0.12;

const double TASA_IVA = 0.16;

// Función para calcular subtotal
// [Revisión, línea 19] Funciones definidas antes de main sin prototipos: es válido en C++.
double calcularSubtotal(int cantidad, double precio_unitario) {
	return cantidad * precio_unitario;
}

// Función para calcular descuento
double calcularDescuento(int cantidad, double subtotal) {
	double porcentaje;

	// [Revisión, línea 27] Correcto: usa < con los límites 10 y 50, equivalente a los rangos del enunciado.
	if (cantidad < LIMITE_DESCUENTO_1) {
		porcentaje = DESCUENTO_1;
	} else if (cantidad < LIMITE_DESCUENTO_2) {
		porcentaje = DESCUENTO_2;
	} else {
		porcentaje = DESCUENTO_3;
	}

	return subtotal * porcentaje;
}

// Función para calcular IVA
double calcularIVA(double base_gravable) {
	return base_gravable * TASA_IVA;
}

// Función para calcular total
double calcularTotal(double base_gravable, double iva) {
	return base_gravable + iva;
}

int main() {
	int cantidad;
	double precio_unitario;

	// Validar cantidad
	do {
		cout << "Ingrese la cantidad de piezas: ";
		cin >> cantidad;

		if (cantidad <= 0) {
			cout << "La cantidad debe ser mayor que 0.\n";
		}

	} while (cantidad <= 0);

	// Validar precio
	do {
		cout << "Ingrese el precio unitario: ";
		cin >> precio_unitario;

		if (precio_unitario <= 0) {
			cout << "El precio debe ser mayor que 0.\n";
		}

	} while (precio_unitario <= 0);


	double subtotal = calcularSubtotal(cantidad, precio_unitario);
	double descuento = calcularDescuento(cantidad, subtotal);
	double base_gravable = subtotal - descuento;
	double iva = calcularIVA(base_gravable);
	double total = calcularTotal(base_gravable, iva);

	cout << fixed << setprecision(2);

	cout << "\n--- FACTURACION ---\n";
	cout << "Subtotal: $" << subtotal << endl;
	cout << "Descuento aplicado: $" << descuento << endl;
	cout << "IVA: $" << iva << endl;
	cout << "Total a pagar: $" << total << endl;

	return 0;
}
```

## Programa 2 — Freelance con bono por horas trabajadas

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 30 horas | Pago base 5400.00, bono no aplica, ISR 540.00, neto 4860.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 40 horas | Pago base 7200.00, bono 576.00, ISR 777.60, neto 6998.40 | Idéntico al esperado | ✅ |
| Límite: exactamente 35 horas | 35 horas | Sin bono, neto 5670.00 | Idéntico al esperado | ✅ |
| Media hora sobre el umbral | 35.5 horas | Bono 511.20, neto 6211.08 | Idéntico al esperado | ✅ |
| Datos inválidos | Horas -1 | Vuelve a pedir el dato | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Funciones puras, constantes, validación y "no aplica" correctos, con dos decimales.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//cesar Eduardo salinas Meza
//Evidencia 2



#include <iostream>
#include <iomanip>



using namespace std;

// Constantes
const double TARIFA_HORA = 180.00;
const double UMBRAL_HORAS = 35.00;
const double PORCENTAJE_BONO = 0.08;
const double TASA_ISR = 0.10;

// Calcular pago base
double calcularPagoBase(double horas_trabajadas) {
	return horas_trabajadas * TARIFA_HORA;
}

// Calcular bono
double calcularBono(double horas_trabajadas, double pago_base) {
	// [Revisión, línea 26] Correcto: el bono solo aplica si las horas SUPERAN el umbral.
	if (horas_trabajadas > UMBRAL_HORAS) {
		return pago_base * PORCENTAJE_BONO;
	} else {
		return 0.00;
	}
}

// Calcular ISR
double calcularISR(double ingreso_total) {
	return ingreso_total * TASA_ISR;
}

// Calcular pago neto
double calcularPagoNeto(double ingreso_total, double isr) {
	return ingreso_total - isr;
}

int main() {
	double horas_trabajadas;

	// Validar horas
	do {
		cout << "Ingrese las horas trabajadas en la semana: ";
		cin >> horas_trabajadas;

		if (horas_trabajadas < 0) {
			cout << "Las horas no pueden ser negativas.\n";
		}

	} while (horas_trabajadas < 0);

	// Cálculos
	double pago_base = calcularPagoBase(horas_trabajadas);
	double bono = calcularBono(horas_trabajadas, pago_base);
	double ingreso_total = pago_base + bono;
	double isr = calcularISR(ingreso_total);
	double pago_neto = calcularPagoNeto(ingreso_total, isr);

	// Mostrar resultados
	cout << fixed << setprecision(2);

	cout << "\n--- PAGO SEMANAL ---\n";
	cout << "Pago base: $" << pago_base << endl;

	if (bono == 0) {
		cout << "Bono: no aplica" << endl;
	} else {
		cout << "Bono: $" << bono << endl;
	}

	cout << "ISR: $" << isr << endl;
	cout << "Pago neto: $" << pago_neto << endl;

	return 0;
}
```

## Comentario general

Excelente trabajo. Ambos programas son correctos y cumplen todos los requisitos.
