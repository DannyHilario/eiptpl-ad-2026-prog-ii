# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 20 — Vazquez Palacios Angel Daniel

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 5 piezas × $100.00 | Subtotal 500.00, descuento 0.00, IVA 80.00, total 580.00 | Idéntico al esperado | ✅ |
| Caso 2 del enunciado | 60 piezas × $50.00 | Subtotal 3000.00, descuento 360.00, IVA 422.40, total 3062.40 | Descuento 0; total 3480.00 | ❌ |
| Límite superior del rango 1 | 9 piezas × $100.00 | Descuento 0.00, total 1044.00 | Idéntico al esperado | ✅ |
| Límite inferior del rango 2 | 10 piezas × $100.00 | Descuento 50.00 (5%), total 1102.00 | Descuento 0; total 1160.00 | ❌ |
| Límite superior del rango 2 | 49 piezas × $100.00 | Descuento 245.00 (5%), total 5399.80 | Descuento 0; total 5684.00 | ❌ |
| Límite inferior del rango 3 | 50 piezas × $100.00 | Descuento 600.00 (12%), total 5104.00 | Descuento 0; total 5800.00 | ❌ |
| Datos inválidos | Cantidad 0 y -5; precio 0 y -1 | Vuelve a pedir cada dato hasta que sea mayor a 0 | Pide cantidad y precio juntos; si la cantidad es inválida pide de todos modos el precio, y además rechaza la cantidad 1, que sí es válida | ❌ |
| Cantidad mínima válida | 1 pieza × $100.00 (luego, si lo vuelve a pedir, 2 piezas × $100.00) | Acepta la cantidad 1: subtotal 100.00, descuento 0.00, IVA 16.00, total 116.00 | Sin mensaje de error, vuelve a preguntar "De cuanto es tu cantidad?" y "De cuanto es el precio unitario?"; solo termina con la segunda captura: "Cantidad: 2 piezas", "TOTAL A PAGAR: $232" | ❌ |
| Etiqueta del descuento | 60 piezas × $50.00 | "Descuento aplicado: $360.00" (monto en pesos) | "Descuento aplicado: 0%" | ❌ |

**Observaciones:**

- ERROR DE LÓGICA: porcentaje_descuento es una variable global de tipo int. Al asignarle 0.05 o 0.12 se trunca a 0, así que el descuento nunca se aplica. En los casos sin descuento el resultado coincide, pero solo por eso.
- Además, calcularDescuento modifica una variable global, así que no es una función pura; el porcentaje debería ser una variable local double.
- La validación pide cantidad y precio en el mismo ciclo, y la condición while (cantidad <= RANGO_MENOR_MIN) rechaza la cantidad 1, que es válida.
- El reporte muestra el descuento en pesos seguido de "%".

**Recomendaciones:**

- Declara el porcentaje como variable local double dentro de calcularDescuento.
- Valida cada dato en su propio do-while.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/* Programa 1: Evidencia 1
Autor: Angel Daniel Vazquez Palacios*/

#include <iostream>

using namespace std;

const double TASA_IVA = 0.16;
// [Revisión, línea 9] ERROR DE LÓGICA: al ser int, esta variable guarda 0 cuando se le asigna 0.05 o 0.12, así que el descuento nunca se aplica. Además, es global: debería ser una variable local double dentro de calcularDescuento.
int porcentaje_descuento = 0;

const int RANGO_MENOR_MIN = 1;
const int RANGO_MENOR_MAX = 9;
const int RANGO_MEDIO_MIN = 10;
const int RANGO_MEDIO_MAX = 49;
const int RANGO_MAYOR = 50;

const double DESCUENTO_BAJO = 0.0;
const double DESCUENTO_MEDIO = 0.05;
const double DESCUENTO_ALTO = 0.12;

double calcularSubtotal(int cantidad, double precio_unitario) {
	return cantidad * precio_unitario;
}

double calcularDescuento(int cantidad, double subtotal) {
	if (cantidad >= RANGO_MENOR_MIN && cantidad <= RANGO_MENOR_MAX) {
		porcentaje_descuento = DESCUENTO_BAJO;
	}
	if (cantidad >= RANGO_MEDIO_MIN && cantidad <= RANGO_MEDIO_MAX) {
		// [Revisión, línea 30] Aquí 0.05 se trunca a 0 al guardarse en un int.
		porcentaje_descuento = DESCUENTO_MEDIO;
	}
	if (cantidad >= RANGO_MAYOR) {
		// [Revisión, línea 33] Aquí 0.12 se trunca a 0 al guardarse en un int.
		porcentaje_descuento = DESCUENTO_ALTO;
	}
	return subtotal * porcentaje_descuento;
}

double calcularBase_gravable(double subtotal, double descuento) {
	return subtotal - descuento;
}

double calcularIVA(double base_gravable) {
	return base_gravable * TASA_IVA;
}

double calcularTotal(double base_gravable, double IVA) {
	return base_gravable + IVA;
}



int main() {
	int cantidad=0;
	float precio_unitario=0;
	
	do {
		do {
			cout << " De cuanto es tu cantidad?" << endl;
			cin >> cantidad;
			if (cantidad <= 0) {
				cout << " Error: Debes de introducir una cantidad positiva y mayor a 0." << endl;
			}
			cout << " De cuanto es el precio unitario?" << endl;
			cin >> precio_unitario;
			if (precio_unitario <= 0) {
				cout << " Error: Debes de introducir una cantidad positiva y mayor a 0." << endl;
			}
		} while (precio_unitario <= 0);
	// [Revisión, línea 69] ERROR: con esta condición una cantidad de 1 pieza (válida) se rechaza. Cada dato debía validarse en su propio ciclo.
	} while (cantidad <= RANGO_MENOR_MIN);

	double subtotal = calcularSubtotal(cantidad, precio_unitario);
	double descuento = calcularDescuento(cantidad, subtotal);
	double base_gravable = subtotal - descuento;
	double IVA = calcularIVA(base_gravable);
	double total = calcularTotal(base_gravable, IVA);
	
	system("cls");
	cout << "======= FACTURA =======" << endl;
	cout << endl;
	cout << " 	|	Cantidad: " << cantidad << "	piezas." << endl;
	cout << "	|	Precio unitario: $" << precio_unitario << endl;
	cout << " 	|	Subtotal: $" << subtotal << endl;
	// [Revisión, línea 83] Error de formato: se imprime el descuento en pesos seguido de "%".
	cout << "	|	Descuento aplicado: " << descuento << "%" << endl;
	cout << "	|	Base gravable: $" << base_gravable << endl;
	cout << "	|	IVA (16%): $" << IVA << endl;
	cout << "	|	-----------------" << endl;
	cout << "	|	TOTAL A PAGAR: $" << total << endl;

	return 0;
}
```

## Programa 2 — Renta de equipo de cómputo con recargo por meses de atraso

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 1 mes | Atraso 0, recargo 0.00, IVA 192.00, total 1392.00 | Valores correctos, sin decimales | ✅ |
| Caso 2 del enunciado | 3 meses | Atraso 2, recargo 144.00, IVA 215.04, total 1559.04 | Idéntico al esperado | ✅ |
| Un mes de atraso | 2 meses | Atraso 1, recargo 72.00, total 1475.52 | Idéntico al esperado | ✅ |
| Datos inválidos | Meses 0 y -1 | Vuelve a pedir el dato | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Los meses de atraso se deducen en su propia función y nunca se le piden al usuario.
- Funciones puras, constantes y validación correctas; los resultados coinciden con el enunciado.
- Hay variables globales (recargo, total_meses) que no se necesitan y código comentado que ya no se usa; conviene quitarlos.

**Recomendaciones:**

- Por convención, los nombres de constantes van en mayúsculas.
- Muestra los montos con dos decimales (fixed y setprecision).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/* Programa 2: Evidencia 1
Autor: Angel Daniel Vazquez Palacios*/

#include<iostream>

using namespace std;

const int meses_incluidos = 1;
const int renta_mensual = 1200;
const float porcentaje_recargo = 0.06;
const float tasa_iva = 0.16;

// [Revisión, línea 13] Estas variables globales no se necesitan (en main se declaran otras con el mismo nombre).
float recargo=0;
int total_meses=0;


// [Revisión, línea 17] Bien: los meses de atraso se deducen aquí y no se le piden al usuario.
int calcularMesesAtraso(int total_meses){
	int atraso = total_meses - meses_incluidos;
	if (atraso > 0) {
		return atraso;
	} else {
		return 0;
	}
}
	double calcularRecargo(int meses_atraso){
	return renta_mensual * porcentaje_recargo * meses_atraso;
	}	
	
	double calcularIVA(double subtotal){
	return subtotal * tasa_iva; 
	}
	
	double calcularTotal(double subtotal, double iva){
	return subtotal + iva;
}

int main(){

	
	do{
		cout<<" Cuantos meses tuviste el equipo en tu poder?"<<endl;
	cin>>total_meses;
	if (total_meses<=0){
		cout<<"Error: Error: Debes de introducir una cantidad mayor a 0."<<endl;
	}
	}while(total_meses<=0);
	
	// [Revisión, línea 48] Conviene quitar el código comentado que ya no se usa.
	/*double subtotal = calcularSubtotal(total_meses);
	double recargo = calcularRecargo(meses_atraso);
	double meses_atraso = subtotal - descuento;
	double IVA = calcularIVA(base_gravable);
	double total = calcularTotal(base_gravable, IVA);*/
	
	int meses_atraso = calcularMesesAtraso(total_meses);
    double recargo = calcularRecargo(meses_atraso);
    double subtotal = renta_mensual + recargo;
    double iva = calcularIVA(subtotal);
    double total = calcularTotal(subtotal, iva);

	system("cls");
	cout << "======= FACTURA =======" << endl;
	cout << endl;
	cout<<"	|	Meses de retraso:"<<meses_atraso<<endl;
	cout<<"	|	Recargo por atraso:"<<recargo<<endl;
	cout<<"	|	IVA (16%):"<<iva<<endl;
	cout<<"----------------------"<<endl;
	cout<<"	|	TOTAL A PAGAR: $"<<total<<endl;
	return 0;
}
```

## Comentario general

El Programa 2 está bien resuelto, pero el Programa 1 tiene un error de lógica grave: el descuento nunca se aplica porque se guarda en una variable int.
