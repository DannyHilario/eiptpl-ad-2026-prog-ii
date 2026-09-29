# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 09 — Moreno Mercado Fernando

## Programa 1 — Monitoreo de batería de dispositivos

**Compilación:** **No compila.** El compilador marca 3 errores: en la línea 29 falta la comilla de apertura del texto en cout << laptop " << i << ..., y en las líneas 38 y 41 las condiciones porcentajeBateria < 0  porcentajeBateria > 100 no tienen el operador lógico o (||) entre las dos comparaciones.

**Observaciones:**

- Lo que se ve del planteamiento (validación del rango 0 a 100 y clasificación con umbral de 20%) iba bien encaminado, pero un programa que no compila no se puede probar.
- El código se revisó tal como se entregó, sin corregir nada.

**Recomendaciones:**

- Antes de entregar, compila y ejecuta en Dev-C++ exactamente el archivo que vas a subir.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

int main() {
    int cantidadLaptops = 0;

    do {
        cout << "Cuantas laptops se van a revisar? ";
        cin >> cantidadLaptops;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cantidadLaptops = -1;
        }

        if (cantidadLaptops <= 0) {
            cout <<"Valor invalido. Debe ser un numero positivo."<< endl;
        }
    } while (cantidadLaptops <= 0);

    int contadorSuficiente = 0;
    int contadorBaja = 0;

    for (int i=1; i<=cantidadLaptops; i++) {
        int porcentajeBateria = -1;

        do {
            // [Revisión, línea 29] NO COMPILA: falta la comilla de apertura. Debía ser cout << "laptop " << i << ...
            cout << laptop " << i << " - porcentaje de bateria (0-100): ";
            cin >> porcentajeBateria;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                porcentajeBateria = -1;
            }

            // [Revisión, línea 38] NO COMPILA: falta el operador || entre las dos comparaciones.
            if (porcentajeBateria < 0  porcentajeBateria > 100) {
                cout << "Valor invalido. Debe ser un entero entre 0 y 100." << endl;
            }
        // [Revisión, línea 41] NO COMPILA: mismo error, falta || entre las dos comparaciones.
        } while (porcentajeBateria < 0  porcentajeBateria > 100);

        if (porcentajeBateria < 20) {
            cout << "Estado: bateria baja mo se presta" << endl;
            contadorBaja++;
        } else {
            cout << "Estado: bateria suficiente" << endl;
            contadorSuficiente++;
        }
    }

    cout << "===== REPORTE FINAL =====" << endl;
    cout << "total de laptops revisadas: " << cantidadLaptops << endl;
    cout << "Laptops con bateria suficiente: " << contadorSuficiente << endl;
    cout << "Laptops con bateria baja: " << contadorBaja << endl;

    return 0;
}
```

## Programa 2 — Estacionamiento

**Compilación:** Compila sin errores.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de opción | Opciones 0 y 7 | Mensaje de error y vuelve a mostrar el menú | Correcto | ✅ |
| Validación de horas | Horas 0 y -3 | Vuelve a pedir las horas | Vuelve a pedirlas | ✅ |
| Cobros y reporte | Auto 2.5 h y 1 h, Camioneta 3 h, Tráiler 1 h | Autos 2 ($52.50), Camionetas 1 ($66), Tráilers 1 ($40), 4 vehículos, $158.50 | Autos 2 con $66 (monto de camionetas), no aparecen camionetas, Tráilers 1 con $158.5 (total general), sin total de vehículos | ❌ |
| Menú | Abrir el programa y ver el menú (luego opción 4 para cerrar) | 1) Auto $15.00/hora, 2) Camioneta $22.00/hora, 3) Tráiler $40.00/hora, 4) Cerrar | "1) Auto (22.00/hora)", "3) Trailer ($`40.00/hora)", "4) Cerrar estacionamiento": falta la opción 2 y el auto muestra la tarifa de la camioneta | ❌ |

**Observaciones:**

- Constantes bien definidas y validaciones de opción y horas correctas (incluso contra entradas no numéricas).
- El cálculo de cada cobro y los acumuladores internos son correctos.
- El menú no muestra la opción 2 (Camioneta) y la opción 1 dice $22.00 cuando la tarifa del auto es $15.00.
- El reporte está mal armado: en la línea de autos imprime montoCamioneta, falta la línea de camionetas, en la de tráilers imprime montoTotal, y no se muestran el total de vehículos ni el monto total por separado. Calculaste totalVehiculos pero nunca lo usas.
- El código no tiene sangría, lo que dificulta leerlo y encontrar errores.

**Recomendaciones:**

- Revisa línea por línea que cada dato del reporte imprima la variable que le corresponde.
- Indenta el código dentro de cada bloque { }.

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
#include <iostream>
using namespace std;

int main() {
// [Revisión, línea 5] Bien: tarifas como constantes.
const double TARIFA_AUTO = 15.00;
const double TARIFA_CAMIONETA = 22.00;
const double TARIFA_TRAILER = 40.00;

int vehiculosAuto = 0, vehiculosCamioneta = 0, vehiculosTrailer = 0;
double montoAuto = 0.0, montoCamioneta = 0.0, montoTrailer = 0.0;

int opcion = 0;
bool estacionamientoAbierto = true;

// [Revisión, línea 15] Sugerencia: el código no tiene sangría, lo que dificulta leerlo.
while (estacionamientoAbierto) {
cout << "\n===== ESTACIONAMIENTO =====" << endl;
// [Revisión, línea 17] ERROR: la opción 1 es Auto y su tarifa es $15.00, no $22.00.
cout << "1) Auto (22.00/hora)" << endl;
// [Revisión, línea 18] FALTA la opción 2 (Camioneta) en el menú.
cout << "3) Trailer ($`40.00/hora)" << endl;
cout << "4) Cerrar estacionamiento" << endl;
cout << "Elige una opcion: ";
cin >> opcion;

if (cin.fail()) {
cin.clear();
cin.ignore(1000, '\n');
opcion = -1;
}

if (opcion < 1 || opcion > 4) {
cout << "Opcion invalida. Debe ser un numero entre 1 y 4." << endl;
continue;
}

if (opcion == 4) {
estacionamientoAbierto = false;
continue;
}

double horas = -1;

do {
cout << "Cuantas horas estuvo estacionado el vehiculo? ";
cin >> horas;

if (cin.fail()) {
cin.clear();
cin.ignore(1000, '\n');
horas = -1;
}

if (horas <= 0) {
cout << "Valor invalido. Debe ser un numero positivo." << endl;
}
} while (horas <= 0);

double cobro = 0.0;

if (opcion == 1) {
cobro = horas * TARIFA_AUTO;
vehiculosAuto++;
montoAuto += cobro;
} else if (opcion == 2) {
cobro = horas * TARIFA_CAMIONETA;
vehiculosCamioneta++;
montoCamioneta += cobro;
} else if (opcion == 3) {
cobro = horas * TARIFA_TRAILER;
vehiculosTrailer++;
montoTrailer += cobro;
}

cout << "Monto a cobrar: `$" << cobro << endl;
}

int totalVehiculos = vehiculosAuto + vehiculosCamioneta + vehiculosTrailer;
double montoTotal = montoAuto + montoCamioneta + montoTrailer;

cout << "\n===== REPORTE DEL DIA =====" << endl;
// [Revisión, línea 79] ERROR: en la línea de autos se imprime montoCamioneta en lugar de montoAuto. Además, falta la línea de camionetas.
cout << "Autos atendidos: " << vehiculosAuto << " | Recaudado: " << montoCamioneta << endl;
// [Revisión, línea 80] ERROR: en tráilers se imprime montoTotal (el total general) en lugar de montoTrailer. Faltan totalVehiculos y el monto total del día.
cout << "Trailers atendidos: " << vehiculosTrailer << " | Recaudado: " << montoTotal << endl;

return 0;
}
```

## Comentario general

El Programa 1 no compila por errores de sintaxis. El Programa 2 calcula bien internamente, pero el menú y el reporte muestran información incorrecta o incompleta.
