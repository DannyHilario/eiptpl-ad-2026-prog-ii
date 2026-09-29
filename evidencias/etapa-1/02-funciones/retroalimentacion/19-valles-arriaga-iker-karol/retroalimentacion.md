# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 19 — Valles Arriaga Iker Karol

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
| Formato de montos | 3 piezas × $33.33 | Subtotal 99.99, descuento 0.00, IVA 16.00, total 115.99 | "El subtotal de su compra es: 99.99", "El descuento total de su compra es: 0", "El total del IVA es: 15.9984", "El toral a pagar es: 115.988" | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Estructura completa: prototipos antes de main, definiciones y llamadas correctas.
- Las funciones de cálculo no usan cin ni cout; solo main interactúa con el usuario.
- Límites de rango, porcentajes y tasa de IVA definidos como constantes con nombre.
- Validación de cantidad y precio con do-while, repitiendo la captura.
- Los montos se muestran sin formato de dos decimales.
- Tipo de dato: las constantes de rango son int pero se inicializan con 10.0 y 50.0; funciona, pero lo correcto es 10 y 50.

**Recomendaciones:**

- Usa fixed y setprecision(2) para los montos (ya incluiste iomanip).
- Revisa la ortografía de los mensajes ("toral").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//IKVA
#include <iomanip>
#include <iostream>
using namespace std;

// [Revisión, línea 6] Tipo de dato: la constante es int pero se inicializa con 10.0; lo correcto es 10.
const int Rango_piezasmedio = 10.0;
const int  Rango_piezasalto = 50.0;
const double desc1 = 0.05;
const double desc2 = 0.12;
const double IVA = 0.16;

double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);

int main(){
	int cantidad;
	double  precio_unitario;
	
	do{
		cout<<"Ingrese la cantidad de piezas compradas: "<<endl;
		cin>>cantidad;
		
		if(cantidad <= 0){
			cout<<"Error.... cantidad de piezas incorrectas"<< endl;
		}
		
	}while(cantidad <= 0);
	
	do {
		
		cout<<"ingrese el precio unitario: "<<endl;
		cin >> precio_unitario;
		
		if(precio_unitario <= 0){
			cout<<"Error.... precio unitario debe ser mayor a 0"<< endl;
		}
	}while (precio_unitario <= 0);
	
double subtotal = calcularSubtotal(cantidad, precio_unitario); 
double descuento = calcularDescuento(cantidad, subtotal);
double base_gravable = subtotal - descuento;
double iva_monto = calcularIVA(base_gravable);
double total = calcularTotal(base_gravable, iva_monto);
	
	// [Revisión, línea 47] Detalle: sin fixed y setprecision(2) los montos salen sin decimales.
	cout<<"------Valor a pagar en total-------"<<endl;
	cout << "El subtotal de su compra es: "<< subtotal<< endl;
	cout<< "El descuento total de su compra es: "<< descuento << endl;
	cout << "El total del IVA es: "<< iva_monto << endl;
	cout <<"El toral a pagar es: "<< total<< endl ;
	
	return 0;
}
double calcularSubtotal(int cantidad, double precio_unitario) {
    return cantidad * precio_unitario;
}

double calcularDescuento(int cantidad, double subtotal) {
    if (cantidad >= Rango_piezasalto) {
        return subtotal * desc2;
    } else if (cantidad >= Rango_piezasmedio) {
        return subtotal * desc1;
    }
    return 0.0;
}

double calcularIVA(double base_gravable) {
    return base_gravable * IVA;
}

double calcularTotal(double base_gravable, double iva) {
    return base_gravable + iva;
}
```

## Programa 2 — Nómina quincenal con descuento por faltas

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | Sueldo $380.00, 1 falta | Días 14, bruto 5320.00, descuento no aplica, ISR 532.00, neto 4788.00 | Valores correctos, sin decimales | ✅ |
| Caso 2 del enunciado | Sueldo $380.00, 4 faltas | Días 11, bruto 4180.00, descuento 418.00, ISR 376.20, neto 3385.80 | Valores correctos, sin decimales | ✅ |
| Límite: exactamente 2 faltas | Sueldo $380.00, 2 faltas | Sin descuento adicional | Idéntico al esperado | ✅ |
| 3 faltas | Sueldo $380.00, 3 faltas | Descuento 456.00 | Idéntico al esperado | ✅ |
| Datos inválidos | Sueldo 0 y -1; faltas -1 y 16 | Vuelve a pedir cada dato | Vuelve a pedir cada dato | ✅ |

**Observaciones:**

- Los días trabajados se deducen en su propia función; funciones puras y validación del rango 0 a 15 correctas.
- En la validación de faltas escribiste 15 directo en lugar de usar tu constante dias_quincena.
- Tipo de dato: días y faltas son cantidades enteras; conviene declarar esas constantes como int.

**Recomendaciones:**

- Por convención, los nombres de constantes van en mayúsculas (DIAS_QUINCENA).
- Revisa la ortografía de los mensajes ("dijite el sueldo diarip").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//IKVA
#include <iostream>
using namespace std;

// [Revisión, línea 5] Por convención, los nombres de constantes van en MAYÚSCULAS; además, días y faltas son enteros (conviene int).
const double dias_quincena = 15.00;
const double  limite_faltas = 2.0;
const double  desc_adicional = 0.10;
const double  isr = 0.10;

int calcularDiasTrabajados(int faltas);
double calcularSueldoBruto(int dias_trabajados, double sueldo_diario);
double calcularDescuentoAdicional(int faltas, double sueldo_bruto);
double calcularISR(double ingreso_total);
double calcularSueldoNeto(double ingreso_total, double isr);

int main(){
 double sueldo_diario;
 int faltas;

  do{
  	
	cout<<"dijite el sueldo diarip"<<endl;
	cin>> sueldo_diario;
	
	if(sueldo_diario <= 0){
		cout<<"ERROR....SUELDO DIARIO NO VALIDO "<< endl;
	}
	
   }while (sueldo_diario <= 0);

   do{
   	
   	cout<<"Digite el numero de faltas totales: "<<endl;
   	cin>> faltas;
   	
   	// [Revisión, línea 36] Detalle: el 15 está escrito directo; podías usar tu constante dias_quincena.
   	if(faltas < 0 || faltas > 15){
   	   cout<<"ERROR.... Numero de faltas no peermitido"<<endl;
	   }
   	
   }while(faltas < 0 || faltas > 15);

int dias_trabajados = calcularDiasTrabajados(faltas);
double sueldo_bruto = calcularSueldoBruto(dias_trabajados, sueldo_diario);
double descuento = calcularDescuentoAdicional(faltas, sueldo_bruto);
double ingreso_total = sueldo_bruto - descuento;
double isr_calculado = calcularISR(ingreso_total);
double sueldo_neto = calcularSueldoNeto(ingreso_total, isr_calculado);

cout<<"------RESUMEN DE SUELDO--------"<<endl;
cout<<"Dias trabajados:"<<dias_trabajados<< endl;
cout<<"Sueldo Bruto:"<< sueldo_bruto<<endl;

if (descuento > 0) {
        cout << "Descuento adicional: " << descuento << endl;
    } else {
        cout << "Descuento adicional: No aplica" << endl;
    }


cout<<"ISR:  "<<isr_calculado<<endl;
cout<<"Sueldo neto: "<<sueldo_neto<<endl;

return 0;
}

int calcularDiasTrabajados(int faltas){
    return dias_quincena - faltas;
}

double calcularSueldoBruto(int dias_trabajados, double sueldo_diario) {
    return dias_trabajados * sueldo_diario;
}

double calcularDescuentoAdicional(int faltas, double sueldo_bruto) {
    if (faltas > limite_faltas) {
        return sueldo_bruto * desc_adicional ;
    }
    return 0;
}

double calcularISR(double ingreso_total) {
    return ingreso_total * isr;
}

double calcularSueldoNeto(double ingreso_total, double isr) {
    return ingreso_total - isr;
}
```

## Comentario general

Muy buen trabajo. La lógica de ambos programas es correcta; hay detalles de formato, ortografía y tipos de datos.
