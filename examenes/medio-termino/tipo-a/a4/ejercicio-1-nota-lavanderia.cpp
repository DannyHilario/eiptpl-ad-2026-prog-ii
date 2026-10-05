#include <iostream>
using namespace std;

// Nota de lavanderia: todo el calculo vive en main.

int main() {

    double kilos, tarifa, costo, iva, total;

    do {
        cout << "Kilos de ropa: ";
        cin >> kilos;
        if (kilos <= 0) {
            cout << "ERROR! Los kilos deben ser mayores a 0" << endl;
        }
    } while (kilos <= 0);

    if (kilos <= 5) {
        tarifa = 30;
    } else if (kilos <= 10) {
        tarifa = 26;
    } else {
        tarifa = 22;
    }
    costo = kilos * tarifa;

    iva = costo * 0.16;

    total = costo + iva;

    cout << endl << "NOTA DE LAVANDERIA" << endl;
    cout << "Ropa: " << kilos << " kg" << endl;
    cout << "Costo de lavado: $" << costo << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
