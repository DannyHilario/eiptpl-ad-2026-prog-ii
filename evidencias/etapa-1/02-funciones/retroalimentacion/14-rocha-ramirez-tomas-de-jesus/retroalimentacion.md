# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 14 — Rocha Ramirez Tomas De Jesus

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
- Detalle menor: el 0% del primer rango está escrito como 0.0 dentro de la función; para ser consistente, podría ser también una constante.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// Alumno: Rocha Ramirez Tomas De Jesus
// Matricula: [matrícula omitida]
// Programa 1 - Facturacion con descuento por volumen e IVA

#include <iostream>
#include <iomanip>

using namespace std;


// CONSTANTES

// Limites de cantidad
// [Revisión, línea 14] Bien: constantes con nombre y comentadas.
const int LIMITE_DESCUENTO_BAJO = 10;
const int LIMITE_DESCUENTO_ALTO = 50;

// DESCUENTO
const double DESCUENTO_BAJO = 0.05;
const double DESCUENTO_ALTO = 0.12;

// IVA
const double TASA_IVA = 0.16;



//FUNCIONES


double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);



int main() {

	int cantidad;
	double precio_unitario;

	double subtotal;
	double descuento;
	double base_gravable;
	double iva;
	double total;

	// ================  VALIDACION DE DATOS  ======================

	do {
		cout << "Ingrese la cantidad de piezas: ";
		cin >> cantidad;

		if (cantidad <= 0) {
			cout << "Error: la cantidad debe ser mayor que 0." << endl;
		}

	} while (cantidad <= 0);


	do {
		cout << "Ingrese el precio unitario: $";
		cin >> precio_unitario;

		if (precio_unitario <= 0) {
			cout << "Error: el precio debe ser mayor que 0." << endl;
		}

	} while (precio_unitario <= 0);



	//============  LOS CALCULOS  ==============================


	subtotal = calcularSubtotal(cantidad, precio_unitario);

	descuento = calcularDescuento(cantidad, subtotal);

	base_gravable = subtotal - descuento;

	iva = calcularIVA(base_gravable);

	total = calcularTotal(base_gravable, iva);


	cout << fixed << setprecision(2);

	cout << endl;
	cout << "========================================" << endl;
	cout << "           FACTURACION" << endl;
	cout << "========================================" << endl;

	cout << "Cantidad de piezas: " << cantidad << endl;
	cout << "Precio unitario:   $" << precio_unitario << endl;
	cout << "Subtotal:           $" << subtotal << endl;
	cout << "Descuento:          $" << descuento << endl;
	cout << "IVA:                $" << iva << endl;
	cout << "Total a pagar:      $" << total << endl;

	cout << "===================== ===================" << endl;

	return 0;
}

// INVOCAR FUNCIONES

double calcularSubtotal(int cantidad, double precio_unitario) {

	return cantidad * precio_unitario;
}




double calcularDescuento(int cantidad, double subtotal) {

	double porcentaje_descuento;

	if (cantidad < LIMITE_DESCUENTO_BAJO) {

		// [Revisión, línea 121] Detalle menor: el 0% está escrito como 0.0; podría ser también una constante.
		porcentaje_descuento = 0.0;

	} else if (cantidad < LIMITE_DESCUENTO_ALTO) {

		porcentaje_descuento = DESCUENTO_BAJO;

	} else {

		porcentaje_descuento = DESCUENTO_ALTO;
	}

	return subtotal * porcentaje_descuento;
}



double calcularIVA(double base_gravable) {

	return base_gravable * TASA_IVA;
}


double calcularTotal(double base_gravable, double iva) {

	return base_gravable + iva;
}
```

## Programa 2 — Renta de bodega con recargo por peso excedente

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 50 m2, 4000 kg | Renta 2250.00, excedente 0, recargo 0.00, IVA 360.00, total 2610.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 50 m2, 6500 kg | Renta 2250.00, excedente 1500, recargo 1200.00, IVA 552.00, total 4002.00 | Idéntico al esperado | ✅ |
| Límite: exactamente 5000 kg | 50 m2, 5000 kg | Excedente 0, total 2610.00 | Idéntico al esperado | ✅ |
| Un kg excedente | 50 m2, 5001 kg | Excedente 1, recargo 0.80, total 2610.93 | Idéntico al esperado | ✅ |
| Datos inválidos | m2 -1; peso -5 | Vuelve a pedir cada dato | Vuelve a pedir cada dato | ✅ |

**Observaciones:**

- El peso excedente se deduce en su propia función y nunca se le pide al usuario.
- Constantes, funciones puras, validación y reporte con dos decimales correctos.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// Alumno: Rocha Ramirez Tomas De Jesus
// Matricula: [matrícula omitida]
// Programa 2 - Renta de bodega con recargo por peso excedente

#include <iostream>
#include <iomanip>

using namespace std;



// CONSTANTES
const double TARIFA_M2 = 45.00;
const double PESO_INCLUIDO = 5000.00;
const double TARIFA_KG_EXCEDENTE = 0.80;

// Tasa de IVA
const double TASA_IVA = 0.16;


//  FUNCIONES

double calcularCostoRenta(double metros_cuadrados);
double calcularPesoExcedente(double peso_almacenado);
double calcularRecargo(double peso_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);

int main() {

	double metros_cuadrados;
	double peso_almacenado;
	double costo_renta;
	double peso_excedente;
	double recargo;
	double subtotal;
	double iva;
	double total;



	do {

		cout << "Ingrese los metros cuadrados rentados: ";
		cin >> metros_cuadrados;

		if (metros_cuadrados < 0) {
			cout << "Error: los metros cuadrados no pueden ser negativos."
			     << endl;
		}

	} while (metros_cuadrados < 0);


	do {

		cout << "Ingrese el peso almacenado en kg: ";
		cin >> peso_almacenado;

		if (peso_almacenado < 0) {
			cout << "Error: el peso almacenado no puede ser negativo."
			     << endl;
		}

	} while (peso_almacenado < 0);



	// CALCULOS

	costo_renta = calcularCostoRenta(metros_cuadrados);

	peso_excedente = calcularPesoExcedente(peso_almacenado);

	recargo = calcularRecargo(peso_excedente);

	subtotal = costo_renta + recargo;

	iva = calcularIVA(subtotal);

	total = calcularTotal(subtotal, iva);





	cout << fixed << setprecision(2);

	cout << endl;
	cout << "========================================" << endl;
	cout << "          RENTA DE BODEGA" << endl;
	cout << "========================================" << endl;

	cout << "Metros cuadrados:  " << metros_cuadrados << endl;
	cout << "Peso almacenado:  " << peso_almacenado << " kg" << endl;
	cout << "Costo de renta:   $" << costo_renta << endl;
	cout << "Peso excedente:   " << peso_excedente << " kg" << endl;
	cout << "Recargo:           $" << recargo << endl;
	cout << "IVA:               $" << iva << endl;
	cout << "Total a pagar:     $" << total << endl;

	cout << "========================================" << endl;


	return 0;
}



double calcularCostoRenta(double metros_cuadrados) {

	return metros_cuadrados * TARIFA_M2;
}


// [Revisión, línea 116] Bien: el peso excedente se deduce aquí y no se le pide al usuario.
double calcularPesoExcedente(double peso_almacenado) {

	if (peso_almacenado > PESO_INCLUIDO) {

		return peso_almacenado - PESO_INCLUIDO;

	} else {

		return 0.0;
	}
}

double calcularRecargo(double peso_excedente) {

	return peso_excedente * TARIFA_KG_EXCEDENTE;
}


double calcularIVA(double subtotal) {

	return subtotal * TASA_IVA;
}

double calcularTotal(double subtotal, double iva) {

	return subtotal + iva;
}
```

## Comentario general

Excelente trabajo. Ambos programas son correctos, ordenados y cumplen todos los requisitos.
