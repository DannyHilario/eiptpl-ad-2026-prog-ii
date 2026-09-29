# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 02 — Espinosa Saucedo Angel Xavier

## Programa 1 — Control de calidad en línea de producción

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (495 a 505 g inclusive) | Pesos 495, 505, 494.9, 510 | Dentro 2, fuera 2 | Dentro 2, fuera 2 | ✅ |

**Observaciones:**

- Validación de la cantidad con while.
- La condición peso >= 495 && peso <= 505 respeta correctamente el rango inclusivo.
- Reporte completo.

**Recomendaciones:**

- Mostrar un mensaje con el resultado de cada pieza haría el programa más claro para el usuario.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//[matrícula omitida]-espinosa-saucedo-angel-xavier-Control de calidad en línea de producción
#include <iostream>
using namespace std;

int main() {
    int totalPiezas;
    int dentro = 0;
    int fuera = 0;
    double peso;

    cout << "Cuantas piezas vas a revisar?: ";
    cin >> totalPiezas;

    // [Revisión, línea 14] Bien: validación de la cantidad.
    while (totalPiezas <= 0) {
        cout << "Numero no valido. Ingresa un numero positivo: ";
        cin >> totalPiezas;
    }

    for (int i = 1; i <= totalPiezas; i++) {
        cout << "Peso de la pieza " << i << " (en gramos): ";
        cin >> peso;

        // [Revisión, línea 23] Correcto: rango inclusivo de 495 a 505.
        if (peso >= 495 && peso <= 505) {
            dentro++;
        } else {
            fuera++;
        }
    }

    cout << "REPORTE FINAL" << endl;
    cout << "Piezas revisadas: " << totalPiezas << endl;
    cout << "Dentro de tolerancia: " << dentro << endl;
    cout << "Fuera de tolerancia: " << fuera << endl;

    return 0;
}
```

## Programa 2 — Máquina expendedora de bebidas

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a mostrar el menú | Correcto | ✅ |
| Validación de cantidad | Cantidades 0 y -3 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Ventas y reporte | Agua 2+1, Refresco 3, Jugo 1 | Agua 3 ($36), Refresco 3 ($54), Jugo 1 ($22), 7 piezas, $112 | Idéntico al esperado | ✅ |
| Formato de montos | Agua 3, Refresco 3, Jugo 1, cerrar (opción 4) | Montos con dos decimales: $36.00, $54.00, $22.00, total $112.00 | "Agua:36", "Refresco:54", "Jugo:22", "Total del dia:112" (sin decimales) | ⚠️ |

⚠️ = el cálculo es correcto; solo falta mejorar la presentación de la salida.

**Observaciones:**

- Precios como constantes y validación de opción y cantidad correctas.
- Buena decisión calcular los montos al final a partir de las piezas y las constantes.

**Recomendaciones:**

- Muestra los montos con dos decimales usando fixed y setprecision(2) de la biblioteca iomanip.
- Cuida la redacción de los mensajes ("Dinero juntao", "MAQUINA EXPENDORA").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//[matrícula omitida]-espinosa-saucedo-angel-xavier-Máquina expendedora de bebidas
#include <iostream>
using namespace std;

int main() {
	const double PRECIO_AGUA = 12.0;
	const double PRECIO_REFRESCO = 18.0;
	const double PRECIO_JUGO = 22.0;

	int cantAgua = 0;
	int cantRefresco = 0;
	int cantJugo = 0;
	int opcion = 0;
	int cantidad;

	while (opcion != 4) {
		cout << "MAQUINA EXPENDORA" << endl;
		cout << "1) Agua ($12.00)" << endl;
		cout << "2) Refresco ($18.00)" << endl;
		cout << "3) Jugo ($22.00)" << endl;
		cout << "4) Cerrar maquina" << endl;
		cout << "Elige una opcion: ";
		cin >> opcion;

		if (opcion < 1 || opcion > 4) {
			cout << "Opcion no valida, intenta de nuevo." << endl;
		} else if (opcion != 4) {
			cout << "Cuantas vas a llevar?: ";
			cin >> cantidad;

			// [Revisión, línea 31] Bien: validación de la cantidad.
			while (cantidad <= 0) {
				cout << "Cantidad no valida. Pon un numero positivo: ";
				cin >> cantidad;
			}

			if (opcion == 1) {
				cantAgua = cantAgua + cantidad;
			} else if (opcion == 2) {
				cantRefresco = cantRefresco + cantidad;
			} else if (opcion == 3) {
				cantJugo = cantJugo + cantidad;
			}
		}
	}

	// [Revisión, línea 46] Buena idea: los montos se calculan al final a partir de las constantes.
	double totalAgua = cantAgua * PRECIO_AGUA;
	double totalRefresco = cantRefresco * PRECIO_REFRESCO;
	double totalJugo = cantJugo * PRECIO_JUGO;
	int totalPiezas = cantAgua + cantRefresco + cantJugo;
	double totalEfectivo = totalAgua + totalRefresco + totalJugo;

	cout << "REPORTE DEL DIA" << endl;
	cout << "Piezas vendidas:" << endl;
	cout << "Agua:" << cantAgua << endl;
	cout << "Refresco:" << cantRefresco << endl;
	cout << "Jugo:" << cantJugo << endl;
	cout << "Total de piezas:" << totalPiezas << endl;

	// [Revisión, línea 59] Detalle: sin fixed y setprecision(2) los montos salen sin decimales (36, 112).
	cout << "Dinero juntao:" << endl;
	cout << "Agua:" << totalAgua << endl;
	cout << "Refresco:" << totalRefresco << endl;
	cout << "Jugo:" << totalJugo << endl;
	cout << "Total del dia:" << totalEfectivo << endl;

	return 0;
}
```

## Comentario general

Muy buen trabajo. La lógica de ambos programas es correcta y cumple con los requisitos; solo hay detalles de presentación del reporte.
