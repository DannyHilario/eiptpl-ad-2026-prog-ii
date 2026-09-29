# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 19 — Valles Arriaga Iker Karol

## Programa 1 — Tiempo de espera en caja

**Compilación:** Compila sin errores. Usa conio.h, propia de Windows; se compiló con un sustituto equivalente sin modificar el código.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 | Vuelve a pedir la cantidad | No la vuelve a pedir: el ciclo no se ejecuta y el reporte muestra 0 y 0 | ❌ |
| Clasificación (más de 10 min) | Tiempos 5, 10, 10.5, 20 | Aceptable 2, excesiva 2 | Aceptable 1, excesivo 2 (el 10 no se contó) | ❌ |
| Reporte | Mismo caso | Total de clientes, aceptables y excesivos | Falta el total de clientes | ❌ |

**Observaciones:**

- No se valida que la cantidad de clientes sea positiva, que era un requisito.
- Error de lógica en la clasificación: se usa if (Tiempo > 10) y luego else if (Tiempo < 10). Un tiempo de exactamente 10 minutos no cumple ninguna de las dos condiciones y no se cuenta en ningún lado; según el enunciado debía contar como aceptable. Bastaba con usar else.
- El reporte no muestra el total de clientes revisados.

**Recomendaciones:**

- Cuando son solo dos categorías, usa if y else: así todos los casos quedan cubiertos.
- Valida la cantidad con un do-while como se vio en clase.
- conio.h se incluye pero no se usa en este programa.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//IKVA
//IKER KAROL VALLES ARRIAGA GPO:323
using namespace std;
#include <iostream>
// [Revisión, línea 5] conio.h no se usa en este programa.
#include <conio.h>

int main (){
	int Totalclientes;
	int clientes;
	float Tiempo;
	int excesivo = 0;
	int aceptable = 0;
	
	cout<< "Cuantos clientes se revisaran: " << endl;
	// [Revisión, línea 15] FALTA VALIDACIÓN: si la cantidad es 0 o negativa, no se vuelve a pedir.
	cin >> Totalclientes;
	
	for(  clientes = 1 ; clientes <= Totalclientes ; clientes++){
	
	cout << "Cliente #" << clientes << endl << "Cuanto tiempo espero el cliente en la caja: " << endl;
	cin >> Tiempo;
	
	if (Tiempo > 10){
		cout << "El tiempo es execesivo" << endl <<endl;
		excesivo = excesivo + 1;
	}
	// [Revisión, línea 26] ERROR DE LÓGICA: con else if (Tiempo < 10), un tiempo de exactamente 10 no entra en ninguna rama y no se cuenta. Bastaba con else.
	else if (Tiempo < 10){
		cout << "El tiempo es aceptable" << endl << endl;
		aceptable = aceptable + 1;
	}
	
	}
	
	
	cout << "******Resultados de los tiempos de espera******" << endl;
	
	// [Revisión, línea 36] FALTA: el total de clientes revisados.
	cout << "Tiempo excesivo: " << excesivo << endl;
	
	cout << "Tiempo aceptable: " << aceptable << endl;
	
	return 0;
}
```

## Programa 2 — Renta de canchas deportivas

**Compilación:** Compila sin errores. Usa conio.h (getch), propia de Windows; se compiló con un sustituto equivalente sin modificar el código.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a pedir la opción | Correcto | ✅ |
| Validación de horas | Horas 0 y -3 | Vuelve a pedir las horas | No valida: acepta 0 y valores negativos | ❌ |
| Rentas y reporte | Fútbol 2.5 h y 1 h, Básquetbol 3 h, Tenis 1 h | Fútbol 2 ($875), Básquetbol 1 ($540), Tenis 1 ($150), 4 rentas, $1565 | Montos correctos, pero no se muestra el total de rentas | ❌ |

**Observaciones:**

- Las tarifas no están declaradas como constantes (const): son variables int normales, y el requisito pedía constantes.
- No se valida que las horas sean positivas.
- Los cálculos de los montos por disciplina y el total recaudado son correctos.
- Al reporte le falta el total de rentas hechas.

**Recomendaciones:**

- Declara las tarifas como const double TARIFA_FUTBOL = 250.00; y así sucesivamente.
- Revisa la ortografía de los mensajes ("Itroduce", "cpsto", "ECHAS").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
using namespace std;
#include <iostream>
#include <conio.h>

int main (){
	
	// [Revisión, línea 7] REQUISITO NO CUMPLIDO: las tarifas deben ser constantes, por ejemplo const double TARIFA_FUTBOL = 250.00;
	int Futbol = 250;
	int basquetbol = 180;
	int tenis = 150;
	int Opcion = 0;
	float horas;
	float monto;
	float totfut = 0, totbasq = 0, tottenis = 0;
	int rentafut = 0, rentabasq = 0, rentatenis= 0;
	float Totalrecaudado;
	
	do{
		
		do{
		system("cls");
	cout << "---Menu de disciplinas---" << endl ;
	
	cout << " 1- Futbol " << endl;
	cout << " 2- Basquetbol " << endl;
	cout << " 3- Tenis " << endl;
	cout << " 4- SALIDA "  << endl;
	
	cout << "Itroduce una opcion: ";
	cin >> Opcion;
	
	if (Opcion < 1 || Opcion > 4 ) {
	cout << "Error....  valor no valido" << endl;
	getch();
    	}
		
		
	    }while (Opcion < 1 || Opcion > 4 );
		
		if (Opcion != 4){
			
			cout << "Cuantas horas se va a rentar la cancha: "  << endl;
			// [Revisión, línea 42] FALTA VALIDACIÓN: no se revisa que las horas sean positivas.
			cin >> horas;
			
			
			switch (Opcion) {
                case 1:
                    monto = Futbol * horas;
                    totfut = totfut + monto;
                    rentafut++;
                    break;

                case 2:
                    monto = basquetbol * horas;
                    totbasq = totbasq + monto;
                    rentabasq++;
                    break;

                case 3:
                    monto = tenis * horas;
                    tottenis = tottenis + monto;
                    rentatenis++;
                    break;
            }
	
			cout << "El cpsto de esta renta es: " << monto << endl;
			getch();
		}
		
	Totalrecaudado = totfut + totbasq + tottenis;
	
	} while (Opcion != 4);
	
	
    // [Revisión, línea 74] FALTA: el total de rentas hechas.
    cout << "*********TOTAL DE RENTAS ECHAS*********"<< endl << endl;
	
	cout << "Futbol: " << rentafut << " rentas, total: " << totfut << endl << endl;
	cout << "Basquetbol: " << rentabasq << " rentas, total: " << totbasq << endl << endl;
	cout << "Tenis: " << rentatenis << " rentas, total: " << tottenis << endl << endl;
	cout << "El total de dinero recaudado de todas las rentas es:"<< Totalrecaudado ;
	
	
	return 0;
	}
```

## Comentario general

Los dos programas compilan y la estructura general (menú, ciclo y switch) es correcta, pero faltan validaciones solicitadas y el Programa 1 tiene un hueco en la lógica de clasificación.
