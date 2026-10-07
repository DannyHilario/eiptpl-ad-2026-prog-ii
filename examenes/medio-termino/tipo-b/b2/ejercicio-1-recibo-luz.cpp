#include <iostream>
using namespace std;

// Recibo de luz: todo el calculo vive en main.

int main() {

    double kwh, tarifa, importe, alumbrado, total;

    do {
        cout << "Consumo del bimestre (kWh): ";
        cin >> kwh;
        if (kwh <= 0) {
            cout << "ERROR! El consumo debe ser mayor a 0" << endl;
        }
    } while (kwh <= 0);

    if (kwh <= 150) {
        tarifa = 2;
    } else if (kwh <= 300) {
        tarifa = 3;
    } else {
        tarifa = 4;
    }
    importe = kwh * tarifa;

    alumbrado = importe * 0.08;

    total = importe + alumbrado;

    cout << endl << "RECIBO DE LUZ" << endl;
    cout << "Consumo: " << kwh << " kWh" << endl;
    cout << "Importe de energia: $" << importe << endl;
    cout << "Alumbrado publico: $" << alumbrado << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
