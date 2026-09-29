# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 20 — Vazquez Palacios Angel Daniel

## Programa 1 — Vibración en maquinaria industrial

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad; total revisado 4 | Vuelve a pedirla, pero el total del reporte dice 2 (suma -2 + 0 + 4) | ❌ |
| Clasificación (más de 4.5 mm/s) | Vibraciones 2, 4.5, 4.55, 7 | Normal 2, alerta 2 | Alerta 2, normal 1 (el 4.55 no se contó) | ❌ |
| Clasificación invertida | Cantidad 2; vibraciones 1 y 2 | Normal 2, alerta 0 | "Maquinas en alerta:2", "Maquinas en estado normal:0" | ❌ |

**Observaciones:**

- La clasificación está invertida: if (vibracion <= 4.5) suma a alerta, cuando según el enunciado ese caso es estado normal.
- La rama else tiene una segunda condición (vibracion >= 4.6), así que los valores entre 4.5 y 4.6 no se cuentan en ningún lado.
- El total de máquinas se acumula dentro del ciclo de validación (maquinastotal = maquinastotal + revisar), por lo que suma también los valores inválidos capturados.
- Se usan variables globales sin necesidad, y el mensaje pide la "velocidad" de la máquina en lugar de la vibración.

**Recomendaciones:**

- Cuando son solo dos categorías, usa if y else sin una segunda condición.
- Usa directamente la cantidad validada como total; no hace falta acumularla.
- Declara las variables dentro de main.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/* Programa 1 — Vibración en maquinaria industrial

Una planta industrial mide la vibración de varias máquinas para detectar posibles fallas mecánicas. Escribe un programa que:

Pregunte cuántas máquinas se van a revisar (debe ser un número positivo; si el usuario introduce un valor inválido, debe volver a pedirlo).
Para cada máquina, pida el nivel de vibración registrado en mm/s (número decimal).
Clasifique la máquina:
Si la vibración es mayor a 4.5 mm/s, la máquina entra en estado de alerta.
En caso contrario, está en estado normal.
Lleva un contador de máquinas en estado normal y otro en estado de alerta.
Al final, muestra un reporte con el total de máquinas revisadas, cuántas estuvieron en estado normal y cuántas en alerta.*/

/* Autor: Angel Daniel Vazquez Palacios
Matricula: [matrícula omitida] */

#include<iostream>

using namespace std;

// [Revisión, línea 20] Variables globales sin necesidad; conviene declararlas dentro de main.
int revisar=0, i=1, alerta=0, normal=0, maquinastotal;
float vibracion=0;

int main(){
	
	do{	
	
	system("cls");
		cout<<"!! IMPORTANTE, TIENES QUE INTRODUCIR UN NUMERO MAYOR A 1."<<endl;
		cout<<" ====================:{VIBRACION EN MAQUINARIA INDUSTRIAL}:===================="<<endl;
	 	cout<<endl;
		cout<<" Cuantas veces se va a revisar la maquina?"<<endl;
		cin>>revisar;
		
		// [Revisión, línea 34] ERROR: se acumula dentro del ciclo de validación, así que también suma los valores inválidos (-2 + 0 + 4 = 2).
		maquinastotal= maquinastotal + revisar;
	} while(revisar<=0 && revisar <=0);
		
	system("cls");
	
	do{
		// [Revisión, línea 40] El mensaje dice "velocidad", pero se mide la vibración.
		cout<<"	Cual es la velocidad de la maquina? (puedes introducir decimales)"<<endl;
		cin>>vibracion;
		// [Revisión, línea 42] ERROR DE LÓGICA: está invertido. Una vibración de 4.5 o menos es estado NORMAL, no alerta.
		if (vibracion<=4.5){
			alerta++;
		} else {
			// [Revisión, línea 45] ERROR DE LÓGICA: con esta segunda condición, los valores entre 4.5 y 4.6 (como 4.55) no se cuentan en ningún lado. Bastaba con else.
			if (vibracion>=4.6) {
				normal++;
			}
		}
		
	i++;
	} while(i<=revisar);
	
	system("cls");
	
	cout<<endl;
	cout<<endl;
	cout<<"						|--|REPORTE DE REVISION DE VIBRACION DE MAQUINARIA|--|"<<endl;
	cout<<endl;
	cout<<" |	Maquinas revisadas en total:"<<maquinastotal<<endl;
	cout<<endl;
	cout<<" |	Maquinas en alerta:"<<alerta<<endl;
	cout<<" |	Maquinas en estado normal:"<<normal<<endl;
	
	system("pause");
	return 0;
}
```

## Programa 2 — Museo

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Opción inválida | Opción 7, luego no comprar otro | Mensaje de error, vuelve a pedir la opción; 0 boletos | Muestra error pero no vuelve a pedir la opción; el reporte cuenta 1 boleto vendido | ❌ |
| Respuesta inválida a "¿otro boleto?" | Opción 0, luego 7 | Vuelve a preguntar | El programa termina sin mostrar el reporte | ❌ |
| Ventas válidas | Joven, Adulto, Adulto mayor (uno por vez) | Joven 1 ($30), Adulto 1 ($60), Adulto mayor 1 ($25), 3 boletos, $115 | Correcto | ✅ |
| Cantidad de boletos | Opción 2 (Adulto), cantidad 3 | Pide cuántos boletos; reporte Adulto 3 ($180), 3 boletos, $180 | No pide la cantidad: muestra "Usted escogio 1 boleto de adulto." y pregunta "Te gustaria comprar otro boleto?" (el 3 se toma como respuesta y el programa termina sin reporte) | ❌ |
| Cerrar la taquilla | Opción 4, luego 2 en "¿otro boleto?" | Muestra el reporte con 0 boletos, sin más preguntas | Pregunta "Te gustaria comprar otro boleto?" y el reporte dice "Boletos en total:1" | ❌ |

**Observaciones:**

- Los precios no se definieron como constantes: se escribieron directamente (30, 60, 25) en los cálculos.
- No se pregunta cuántos boletos se compran; cada selección vende solo uno.
- Las condiciones de validación (boleto <= 0 && boleto >= 5 y salir >= 2 && salir <= 0) nunca pueden ser verdaderas, porque un número no puede ser menor o igual a 0 y a la vez mayor o igual a 5. Por eso nunca se vuelve a pedir el dato.
- Una opción inválida se cuenta como boleto vendido (totalboleto++ se ejecuta siempre), y si la respuesta a "¿otro boleto?" no es 1 ni 2, el programa termina sin reporte.
- El flujo no sigue el enunciado: en lugar de volver al menú hasta elegir "cerrar", se pregunta si se desea comprar otro boleto.

**Recomendaciones:**

- Para validar un rango usa || (o): opcion < 1 || opcion > 4.
- Declara los precios como constantes y pide la cantidad de boletos con su propia validación.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/*Programa 2 — Museo
Un museo vende boletos de entrada según el tipo de visitante: 1) Niño, 2) Adulto, 3) Adulto mayor. Cada tipo tiene un precio de boleto fijo. Escribe un programa que:

Defina en el código, como constantes, el precio del boleto para cada tipo de visitante:
Niño: $30.00
Adulto: $60.00
Adulto mayor: $25.00

|Muestre un menú con los 3 tipos de visitante más una cuarta opción para cerrar la taquilla.
|Valide que la opción introducida esté entre 1 y 4; si no, muestre un error y vuelva a pedir la opción (sin salir del programa).
|Si la opción no es "cerrar", pida cuántos boletos de ese tipo se están comprando (número entero positivo; si es inválido, debe volver a pedirse) 
y usa el precio constante correspondiente para calcular el monto de esa venta, acumulándolo en el total de su tipo, además de contar cuántos boletos de ese tipo se han vendido.

|El programa debe seguir mostrando el menú y registrando ventas hasta que el usuario elija "cerrar la taquilla".
|Al finalizar, muestra un reporte con: boletos vendidos por tipo de visitante, boletos totales vendidos, monto recaudado por tipo (calculado a partir del precio constante)
y monto total del día.*/

/*Autor: Angel Daniel Vazquez Palacios
Matricula: [matrícula omitida]
*/

#include<iostream>

using namespace std;

int main(){
	int boleto, totalboleto=0, total=0, boletojoven=0, boletoadulto=0, boletoadultomayor=0, totalboletojoven=0, totalboletoadulto=0, totalboletoadultomayor=0, salir=0;
	
	do{
		do{
			system("cls");
			cout<<"!! IMPORTANTE, TIENES QUE INTRODUCIR UN NUMERO MAYOR A 1 Y MENOR A 5."<<endl;
			cout<<" ====================:{ MUSEO }:===================="<<endl;
	   		cout<<endl;
			cout<<" [1].- Boleto de joven."<<endl;
			cout<<endl;
			cout<<" [2].- Boleto de adulto."<<endl;
			cout<<endl;
			cout<<" [3].- Boleto de adulto mayor."<<endl;
			cout<<endl;
			cout<<" [4].- Salir.<<"<<endl;
			cin>>boleto;
		
			switch (boleto){
			// [Revisión, línea 45] FALTA: no se pregunta cuántos boletos se compran; cada selección vende solo uno.
			case 1: cout<<" Usted escogio 1 boleto de joven."<<endl;
			boletojoven++;
			// [Revisión, línea 47] REQUISITO NO CUMPLIDO: el precio está escrito directo (30) en lugar de una constante; igual con 60 y 25.
			totalboletojoven = totalboletojoven + 30;
			cout<<endl; break;
			case 2: cout<<" Usted escogio 1 boleto de adulto."<<endl;
			boletoadulto++;
			totalboletoadulto = totalboletoadulto + 60;
			cout<<endl; break;
			case 3: cout<<" Usted escogio 1 boleto de adulto mayor."<<endl;
			boletoadultomayor++;
			totalboletoadultomayor = totalboletoadultomayor + 25;
			cout<<endl; break;
		
			case 4: cout<<" Buena suerte!"<<endl; break;
		default: cout<<" No esta en el rango permitido."<<endl; break;
		}
		// [Revisión, línea 61] ERROR DE LÓGICA: un número no puede ser <= 0 y >= 5 al mismo tiempo, así que esta condición nunca es verdadera y nunca se vuelve a pedir la opción. Debía ser boleto < 1 || boleto > 4.
		} while (boleto<=0 && boleto >=5 && boleto!=4);
		
		// [Revisión, línea 63] ERROR: se ejecuta siempre, incluso si la opción fue inválida o 4, así que una opción inválida cuenta como boleto vendido.
		totalboleto++;
		do {
			cout<<" Te gustaria comprar otro boleto?"<<endl;
			cout<<endl;
			cout<<" [1].- Si"<<endl;
			cout<<endl;
			cout<<" [2].- No"<<endl;
			cin>>salir;
		// [Revisión, línea 71] ERROR DE LÓGICA: misma situación; esta condición nunca es verdadera.
		} while(salir>=2 && salir <=0);
	} while (salir==1);
		
	// [Revisión, línea 74] Si salir no es 2 (por ejemplo, 7), el programa termina sin mostrar el reporte.
	if (salir==2) {
		system("cls");
		cout<<"					|--|REPORTE DE BOLETOS DE MUSEO|--|"<<endl;
		cout<<endl;
		cout<<" |	Boletos en total:"<<totalboleto<<endl;
		cout<<endl;
		cout<<" |	Boletos de joven:"<<boletojoven<<endl;
		cout<<endl;
		cout<<" |	Boletos de adulto:"<<boletoadulto<<endl;
		cout<<endl;
		cout<<" |	Boletos de adulto mayor:"<<boletoadultomayor<<endl;
		cout<<endl;
		cout<<" -----------------------------"<<endl;
		cout<<endl;
		cout<<" |	Total dinero en boleto de joven:"<<totalboletojoven<<endl;
		cout<<endl;
		cout<<" |	Total dinero en boleto de adulto:"<<totalboletoadulto<<endl;
		cout<<endl;
		cout<<" |	Total dinero en boleto de adulto mayor:"<<totalboletoadultomayor<<endl;
		cout<<endl;
		cout<<endl;
		
		cout<<" -----------------------------"<<endl;
		cout<<endl;
		total = totalboletojoven + totalboletoadulto + totalboletoadultomayor;
		cout<<" |	Dinero en total:"<<total<<endl;
		cout<<endl;
		cout<<endl;
	}
	system("pause");
	return 0;
}
```

## Comentario general

Los dos programas compilan, pero la lógica tiene errores importantes en ambos: la clasificación invertida del Programa 1 y las validaciones que nunca se cumplen en el Programa 2. Te recomiendo repasar operadores lógicos (&& y ||) y la estructura if/else.
