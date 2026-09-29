# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 03 — Flores Hidalgo Carolina

## Programa 1 — Filtro de acceso a un evento

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación simétrica | Temperaturas 36.5, 37.5, 37.6, 39 | Normales 2, febriles 2 | Normales 2, elevadas 2 (coincide solo por casualidad) | ❌ |
| Clasificación asimétrica | Temperaturas 39, 36, 38 | Normales 1, febriles 2 | Normales 2, elevadas 1 | ❌ |

**Observaciones:**

- La validación de la cantidad de asistentes con do-while es correcta.
- La lógica de clasificación está invertida: cuando la temperatura es mayor a 37.5 el programa imprime "Normal. Puede pasar" y suma al contador de normales; cuando es menor o igual imprime "Acceso denegado" y suma a los de temperatura elevada.
- Por eso el reporte cuenta al revés. En la primera prueba el resultado pareció correcto solo porque había la misma cantidad de cada tipo; con una prueba distinta el error es evidente.

**Recomendaciones:**

- Cuando una condición decide entre dos casos, revisa que el mensaje y el contador de cada rama correspondan a lo que dice la condición.
- Prueba tu programa con casos donde las cantidades de cada tipo sean diferentes.
- Usa nombres de variables que digan qué guardan (por ejemplo, totalAsistentes, temperatura, normales, febriles en lugar de Tvs, Tem, n, c).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/* Programación II - Carolina Flores Hidalgo
Etapa 1 - D4*/

#include <iostream>

using namespace std;

int main(){
	
	// [Revisión, línea 10] Sugerencia: nombres como Tvs, Tem, n y c no dicen qué guardan.
	int Tvs;
	double Tem;
	int n = 0, c = 0;
	
	do{
		
	cout<< "Ingrese la cantidad de asistentes a revisar, por favor: "<<endl<<endl;
	cin>>Tvs;
	
	if(Tvs<= 0){
		cout<< "Eror. Debe ngresar otro umero."<<endl<<endl<<endl;
	}
	
}while (Tvs <= 0);


	for (int i = 1; i <= Tvs; i++){
		
		cout<< "Asistente #" <<i<<endl<<endl<<endl;
		cout<< "Su temperatura: "<<endl;
		cin>>Tem; 
		
	// [Revisión, línea 32] ERROR DE LÓGICA: si la temperatura es MAYOR a 37.5 la persona es febril, pero aquí se imprime "Normal" y se suma a n (normales). Las dos ramas están invertidas.
	if (Tem > 37.5){
		
		cout<< "Normal. Puede pasar, adelante."<<endl<<endl<<endl;
		n++;
		
	// [Revisión, línea 37] Esta rama (37.5 o menos) es la temperatura normal, pero se cuenta como elevada.
	} else{
		
		cout<< "Ardiente. Acceso denegado." <<endl<<endl<<endl;
		c++;
	}
		
	}
	
	cout<< "************* Reporte Final *************"<<endl<<endl<<endl<<endl;
	cout<< "Total de revisados: " <<Tvs<<endl<<endl;
	cout<< "Asistentes con temperatura normal: " <<n<<endl;
	cout<< "Asistentes con temperatura elevada: "<<c<<endl;
	
	return 0;
}
```

## Programa 2 — Despacho en gasolinera

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Vuelve a pedir la opción | Vuelve a pedirla | ✅ |
| Validación de litros | Litros 0 | Mensaje de error y vuelve a pedir los litros | Ciclo infinito: el mensaje de error se repite sin fin | ❌ |
| Despachos válidos | Magna 2.5 L y 1 L, Premium 3 L, Diésel 1 L | Magna 3.5 L ($82.25), Premium 3 L ($77.40), Diésel 1 L ($26.20), 4 despachos, $185.85 | Montos correctos, pero los tres bloques dicen "Magna" y los despachos salen como 2.00, 1.00 | ❌ |

**Observaciones:**

- Precios definidos como constantes y validación de la opción correcta.
- Error de lógica en la validación de litros: dentro de while (L <= 0) solo se imprime el mensaje de error, pero nunca se vuelve a leer L, así que si el usuario escribe un valor inválido el programa se queda atrapado para siempre.
- Los cálculos de litros y montos por tipo son correctos cuando los datos son válidos.
- El reporte etiqueta los tres combustibles como "Magna" y los contadores de despachos están declarados como double, por lo que se muestran con decimales.

**Recomendaciones:**

- Dentro de un ciclo de validación siempre debe volver a leerse el dato; de lo contrario, la condición nunca cambia.
- Los contadores (cantidad de despachos) deben ser int.
- Revisa las etiquetas del reporte antes de entregar.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/* Programacion II - Carolina Flores Hidalgo
Etapa 1 - D4 - Prt2.*/

#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	
	// [Revisión, línea 11] Bien: precios como constantes.
	const double GM = 23.50, GP = 25.80, GD = 26.20;
	int Op;
	double L;
	double LM = 0, LP = 0, LD = 0;
	double TM = 0, TP = 0, TD = 0;
	// [Revisión, línea 16] DM, DP y DD cuentan despachos: deberían ser int (por eso salen como 2.00).
	double DM = 0, DP = 0, DD = 0;
	
	do{
		
		cout<< "************* Gasolinera *************";
		cout<< "1. Magna. $23.50/L"<<endl;
		cout<< "2. Premium. $25.80/L"<<endl;
		cout<< "3. Diesel. $26.20/L"<<endl;
		cout<< "4. Cerrar turno"<<endl;
		cout<< "Por favor, seleccione una opcion."<<endl;
		cin>>Op;
	
	while (Op < 1 || Op > 4){
		
		cout<< "Error. Por favor, ingrese una opcion de las proporcionadas anteriormente (1-4).";
		cin>>Op;
	}
	
	if (Op != 4){
		
		
		do {
			
			cout<< "Ingrese los litros que desea despachar: "<<endl<<endl;
			cin>>L;
		
		
		// [Revisión, línea 43] ERROR DE LÓGICA: dentro de este while nunca se vuelve a leer L. Si L <= 0, la condición nunca cambia y el programa se cicla para siempre. Faltaba cin >> L; aquí dentro.
		while (L <= 0){
			
			cout<< "Error. Los litros deben ser mayores de 0.";
		}
		
	
	} while (L <= 0);
	
	switch (Op){
		
		case 1:
			LM+= L;
			TM += L * GM;
			DM++;
			break;
			
		case 2:
			LP += L;
			TP += L * GP;
			DP++;
			break;
			
		case 3:
			LD += L;
			TD += L * GD;
			DD++;
			break;
		
		}
	}
	
	} while (Op != 4);
	
	int TDD = DM + DP + DD;
	double EFT = TM + TP + TD;
	
	cout<<fixed<<setprecision(2);
	
	
	cout<< "******************* Reporte Final *******************" <<endl<<endl<<endl;
	cout<< "Magna: "<<LM<<endl;
	cout<< "Despachos: "<<DM<<endl;
	cout<< "Efectivo obtenido: " <<TM<<endl<<endl<<endl;
	
	// [Revisión, línea 87] Etiqueta incorrecta: este bloque es Premium, no Magna.
	cout<< "Magna: "<<LP<<endl;
	cout<< "Despachos: "<<DP<<endl;
	cout<< "Efectivo obtenido: " <<TP<<endl<<endl<<endl;
	
	// [Revisión, línea 91] Etiqueta incorrecta: este bloque es Diésel, no Magna.
	cout<< "Magna: "<<LD<<endl;
	cout<< "Despachos: "<<DD<<endl;
	cout<< "Efectivo obtenido: " <<TD<<endl<<endl<<endl;
	
	cout<< "Total de despachos: " <<TDD<<endl;
	cout<< "Efectivo total: " <<EFT<<endl;

	
	return 0;
}
```

## Comentario general

Los dos programas compilan y la estructura general (ciclos, switch, constantes) está bien planteada, pero ambos tienen errores de lógica importantes: la clasificación invertida en el Programa 1 y la validación de litros que cicla infinitamente en el Programa 2.
