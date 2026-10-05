#include <iostream>
using namespace std;

// Nota de venta de gas LP: todo el calculo vive en main.

int main() {

    double litros, tarifa, importe, cargo, total;

    do {
        cout << "Litros cargados: ";
        cin >> litros;
        if (litros <= 0) {
            cout << "ERROR! Los litros deben ser mayores a 0" << endl;
        }
    } while (litros <= 0);

    if (litros <= 30) {
        tarifa = 12;
    } else if (litros <= 60) {
        tarifa = 11;
    } else {
        tarifa = 10;
    }
    importe = litros * tarifa;

    cargo = importe * 0.05;

    total = importe + cargo;

    cout << endl << "NOTA DE GAS LP" << endl;
    cout << "Litros: " << litros << " L" << endl;
    cout << "Importe: $" << importe << endl;
    cout << "Cargo por servicio: $" << cargo << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
