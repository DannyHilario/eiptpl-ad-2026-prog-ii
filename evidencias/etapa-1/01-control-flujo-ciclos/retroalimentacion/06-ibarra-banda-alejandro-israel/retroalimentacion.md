# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 06 — Ibarra Banda Alejandro Israel

## Programa 1 — Control de inventario

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (umbral 10 piezas) | Existencias 5, 10, 11, 50 | Stock bajo 2, normal 2 | Stock bajo 2, normal 2 | ✅ |

**Observaciones:**

- Validación, clasificación (10 exacto es stock bajo) y reporte correctos.

**Recomendaciones:**

- Usa nombres de variables descriptivos: A, sb, sn y ex no dicen qué guardan (por ejemplo, totalProductos, stockBajo, stockNormal, existencia).
- La biblioteca fstream no se usa en el programa; no es necesario incluirla.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/* Dimension 4 Programa 1 
Alejandro Israel Ibarra Banda */

#include<iostream>
// [Revisión, línea 5] fstream no se usa en este programa.
#include<fstream>
#include<stdlib.h>
using namespace std;
int main(){
	// [Revisión, línea 9] Sugerencia: A, sb, sn y ex no dicen qué guardan.
	int A, sb = 0, sn = 0, ex;
	
	
	do{
		cout<<"¿cuantos productos quiere revisar?";
		cin>>A;
		if(A<=0){
			cout<<"El numero tiene que ser positivo intenta otro amiguito"<<endl;
		}
	}
	while (A<=0);
	
	for(int i = 1; i<=A; i++) {
		cout<<"escriba la cantidad de existencia del producto"<<i<<": ";
		cin>>ex;
		
		// [Revisión, línea 25] Correcto: 10 exacto es stock bajo.
		if(ex<= 10) {
			cout<<"stock bajo D: "<<endl;
			sb++;
		} 
		
		 else {
		cout<<"stock normal :D"<<endl;
		sn++;
		}
	}
	cout<<"\n====Reporte Final===="<<endl;
	cout<<"Total de productos revisados:  "<<A<<endl;
	cout<<"Productos de stock normal:)  : "<<sn<<endl;
	cout<<"Productos de stock bajo :( : "<<sb<<endl;
	
	system("pause");
	return 0;
}
```

## Programa 2 — Centro de fotocopiado

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a mostrar el menú | Correcto | ✅ |
| Validación de cantidad | Páginas 0 | Vuelve a pedir la cantidad de páginas | Muestra error pero regresa al menú en lugar de volver a pedir las páginas | ❌ |
| Trabajos y reporte | B/N 2+1, Color 3, Oficio 1 | B/N 3 ($3.00), Color 3 ($10.50), Oficio 1 ($1.50), 7 páginas, $15.00 | Cantidades correctas, pero se muestra $3.0 y $15.0 | ❌ |

**Observaciones:**

- No se definieron los precios como constantes, que era un requisito explícito: los precios están escritos directamente en los cálculos (pag * 100, pag * 350, pag * 150), expresados en centavos.
- La idea de trabajar en centavos con enteros es ingeniosa, pero al imprimir mBN % 100 los montos que terminan en cero se muestran con un solo decimal ($3.0 en lugar de $3.00), y un monto como 3.05 se mostraría como 3.5.
- Si la cantidad de páginas es inválida, el programa regresa al menú en vez de volver a pedir la cantidad: la validación está incompleta.
- La lógica de contadores y acumuladores por tipo es correcta.

**Recomendaciones:**

- Declara los precios como const double PRECIO_BN = 1.00; y así sucesivamente, y úsalos en los cálculos.
- Para validar la cantidad, usa un do-while que vuelva a pedir el dato hasta que sea válido.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
/*Programa 2 dimension 4 
Alejandro Isarel Ibarra Banda */

#include <iostream>
using namespace std;

int main() {
    int op;
    int pag;
    int toBN = 0, toC = 0, toOf = 0;
    int mBN = 0, mC = 0, mOf = 0;
    do {
        cout << "\n=== Centro de Fotocopiado ===\n";
        cout << "1) Blanco y negro ($1.00 por página)\n";
        cout << "2) Color ($3.50 por página)\n";
        cout << "3) Tamaño oficio ($1.50 por página)\n";
        cout << "4) Cerrar caja\n";
        cout << "Seleccione una opción (1-4): ";
        cin >> op;


        if (op < 1 || op > 4) {
            cout << "Error: opción inválida.\n";
            continue;
        }

        if (op == 4) {
            break;
        }

        cout << "Ingrese la cantidad de páginas: ";
        cin >> pag;
        // [Revisión, línea 33] VALIDACIÓN INCOMPLETA: si la cantidad es inválida, continue regresa al menú en lugar de volver a pedir las páginas.
        if (pag <= 0) {
            cout << "Error: debe ser un número positivo.\n";
            continue; 
        }

       
        switch(op) {
            case 1:
                toBN += pag;
                // [Revisión, línea 42] REQUISITO NO CUMPLIDO: el precio está escrito directo (100 centavos) en lugar de usar una constante.
                mBN += pag * 100;
                break;
            case 2:
                toC += pag;
                // [Revisión, línea 46] REQUISITO NO CUMPLIDO: precio escrito directo (350) en lugar de una constante.
                mC += pag * 350;
                break;
            case 3:
                toOf += pag;
                // [Revisión, línea 50] REQUISITO NO CUMPLIDO: precio escrito directo (150) en lugar de una constante.
                mOf += pag * 150;
                break;
        }

        cout << "Trabajo registrado.\n";

    } while (true);

   
    int paginasTotales = toBN + toC + toOf;
    int montoTotal = mBN + mC + mOf;

    cout << "\n=== Reporte del día ===\n";
    // [Revisión, línea 63] Error de formato: cuando no hay centavos, mBN % 100 da 0 y se imprime $3.0 en lugar de $3.00.
    cout << "Blanco y negro: " << toBN << " páginas, $" << mBN / 100 << "." << mBN % 100 << endl;
    cout << "Color: " << toC << " páginas, $" << mC/ 100 << "." << mC % 100 << endl;
    cout << "Tamaño oficio: " << toOf << " páginas, $" << mOf/ 100 << "." << mOf % 100 << endl;
    cout << "TOTAL: " << paginasTotales << " páginas, $" << montoTotal / 100 << "." << montoTotal % 100 << endl;

    return 0;
}
```

## Comentario general

La lógica de clasificación y conteo es correcta en ambos programas. En el Programa 2 faltó cumplir el requisito de constantes y la validación de la cantidad está incompleta.
