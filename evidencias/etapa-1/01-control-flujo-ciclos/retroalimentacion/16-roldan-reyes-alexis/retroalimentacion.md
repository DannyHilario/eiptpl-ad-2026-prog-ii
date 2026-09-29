# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 16 — Roldan Reyes Alexis

## Programa 1 — Prueba de resistencia de material

**Compilación:** **No compila.** El compilador marca 20 errores. Los principales: #include(iostream) en la línea 1 (debe ser #include <iostream>), cuut en lugar de cout en la línea 10, cin >>tital totaldepiezas en la línea 11 (sobra la palabra tital), la variable resistencia se usa sin haberla declarado, y se incrementa rechazadas cuando la variable declarada se llama rechasados.

**Observaciones:**

- Al fallar el #include, el compilador tampoco reconoce cout, cin ni endl en todo el archivo.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] NO COMPILA: debe ser #include <iostream>. Como falla, el compilador tampoco reconoce cout, cin ni endl en todo el archivo.
#include(iostream)
using namespace std;
int main () {
	int totaldepiezas = 0;
	int aprobadas = 0;
	int rechasados = 0;
	cout <<"--PRUEBAS DE RESISTENCIA--" << endl;
	//validacion de entrada parar la cantidad de piezas 
	do{
		// [Revisión, línea 10] NO COMPILA: dice cuut en lugar de cout.
		cuut << "ingresa la cantidad de piezas a probar(mayor a 0): ";
		// [Revisión, línea 11] NO COMPILA: sobra la palabra tital.
		cin >>tital totaldepiezas;
		if (totaldepiezas <=0) {
			cout << "error_debe ingresar un numuro entero positivo. " << endl;
		}
	}while (totaldepiezas <= 0);
	//Prosedimiento dde cada pieza
	for (int i = 1; i <= totaldepiezas; i++) {
		//validacion para la resistencia registrada
		do { cout << "\npieza " << i <<" - ingresa la resistencia en kg: ";
		// [Revisión, línea 20] NO COMPILA: la variable resistencia nunca se declaró.
		cin >>resistencia;
		if (resistencia <= 0) {
			cout << "error-la resistencia debe ser un valor pusitivo." << endl;
		}
	}while(resistencia <=0);
		//clasificacion
		if (resistencia < 500.0){
			cout  << "resultado-rechasado (resistencia menor de 500 kg)" << endl;
			// [Revisión, línea 28] NO COMPILA: la variable declarada se llama rechasados (línea 6), no rechazadas.
			rechazadas++;
		}else{
			cout << "resultado-aprodado" << endl;
			aprobadas++;
		}
	}
	//reporte final 
	cout << "\n////////////////////////////////////////////////////////////////" << endl;
	cout << "                       FIN DEL REPORTE                            " << endl;
	cout << "//////////////////////////////////////////////////////////////////" << endl;
	cout << "total de piezas a probadas: " << totaldepiezas << endl;
	cout << "piezas aprobadas:           " << aprobadas << endl;
	cout << "piezas rechasados:          " << rechasados << endl;
	cout << "////////////////////////////////////////////////////" << endl;
	
	return  0;
	
}
```

## Programa 2 — Renta de disfraces

**Compilación:** **No compila.** El compilador marca 6 errores: en las líneas 60 y 67 escribiste TARIFA-ELABORADO y TARIFA-PREMIUM con guion medio (el compilador lo lee como una resta), pero tus constantes se llaman TARIFA_ELABORADO y TARIFA_PREMIUM, con guion bajo; y en la línea 91 falta la comilla de apertura del texto "  |  $".

**Observaciones:**

- El planteamiento (constantes, menú, validación y switch) se veía bien encaminado, pero un programa que no compila no se puede probar.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
#include <iomanip> //Para formato decimal en importes monetarios
using namespace std;
int main() {
    // Tarifas fijas por dia (constantes)
    const double TARIFA_SENCILLO = 80.00;
    const double TARIFA_ELABORADO = 150.00;
    const double TARIFA_PREMIUM = 280.00;
    // Contadores de rentas por tipo
    int rentasSencillo = 0;
    int rentasElaborado = 0;
    int rentasPremium = 0;
    // Acumuladores de montos por tipo
    double montoSencillo = 0.0;
    double montoElaborado = 0.0;
    double montoPremium = 0.0;
    int opcion = 0;
    cout << fixed << setprecision(2); // Formato para mostrar precios con 2 decimales
    do {
        // Menu principal
        cout << "\n/////////////////////////////////" << endl;
        cout << "            RENTA_DE_DISFRACES     " << endl;
        cout << "///////////////////////////////////" << endl;
        cout << "1/ Disfraz Sencillo  ($80.00 - dia)" << endl;
        cout << "2/ Disfraz Elaborado ($150.00 - dia)" << endl;
        cout << "3/ Disfraz Premium   ($280.00 - dia)" << endl;
        cout << "4/ Cerrar mostrador" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        // Validacion de la opcion del menu
        if (opcion < 1 || opcion > 4) {
            cout << "Error: Opcion invalida. Intente de nuevo (1 - 4)." << endl;
            continue;
        }
        // Si elige cerrar el mostrador, se interrumpe el ciclo sin pedir dias
        if (opcion == 4) {
            break;
        }

        // Lectura y validacion de dias de renta
        int dias = 0;
        do {
            cout << "Ingrese el numero de dias de renta (entero positivo): ";
            cin >> dias;
            if (dias <= 0) {
                cout << "Error: El numero de dias debe ser un entero positivo." << endl;
            }
        } while (dias <= 0);

        // Calculo y acumulacion segun el tipo de disfraz
        switch (opcion) {
            case 1: {
                double subtotal = dias * TARIFA_SENCILLO;
                montoSencillo += subtotal;
                rentasSencillo++;
                cout << "Renta registrada: Sencillo por " << dias << " dia(s). Subtotal: $" << subtotal << endl;
                break;
            }
            case 2: {
                // [Revisión, línea 60] NO COMPILA: con guion medio, TARIFA-ELABORADO se lee como TARIFA menos ELABORADO. La constante se llama TARIFA_ELABORADO.
                double subtotal = dias * TARIFA-ELABORADO;
                montoElaborado += subtotal;
                rentasElaborado++;
                cout << "Renta registrada: Elaborado por " << dias << " dia(s). Subtotal: $" << subtotal << endl;
                break;
            }
            case 3: {
                // [Revisión, línea 67] NO COMPILA: mismo error; la constante se llama TARIFA_PREMIUM.
                double subtotal = dias * TARIFA-PREMIUM;
                montoPremium += subtotal;
                rentasPremium++;
                cout << "Renta registrada: Premium por " << dias << " dia(s). Subtotal: $" << subtotal << endl;
                break;
            }
        }

    } while (opcion != 4);

    // Calculos finales para el reporte
    int totalRentas = rentasSencillo + rentasElaborado + rentasPremium;
    double montoTotal = montoSencillo + montoElaborado + montoPremium;

    // Reporte de cierre
    cout << "\n//////////////////////////////////////////////////" << endl;
    cout << "                  FINAL DE CIERRE                   " << endl;
    cout << "////////////////////////////////////////////////////" << endl;
    cout << "Tipo Disfraz  |  Cant. Rentas  |  Monto Recaudado " << endl;
    cout << "____________________________________________________" << endl;
    cout << "Sencillo      |  " << setw(12) << rentasSencillo << "  |  $" << setw(13) << montoSencillo << endl;
    cout << "Elaborado     |  " << setw(12) << rentasElaborado << "  |  $" << setw(13) << montoElaborado << endl;
    cout << "Premium       |  " << setw(12) << rentasPremium   << "  |  $" << setw(13) << montoPremium << endl;
    cout << "_____________________________________________________" << endl;
    // [Revisión, línea 91] NO COMPILA: falta la comilla de apertura antes de   |  $"
    cout << "TOTALES       |  " << setw(12) << totalRentas    <<   |  $" << setw(13) << montoTotal << endl;
    cout << "_______________________________________________________" << endl;

    return 0;
}
```

## Comentario general

Ninguno de los dos programas compila por errores de escritura. Compilar y probar antes de entregar te habría mostrado exactamente dónde estaban.
