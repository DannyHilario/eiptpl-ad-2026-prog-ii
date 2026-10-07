#include <iostream>
using namespace std;

// Nota de fotocopias: todo el calculo vive en main.

int main() {

    double hojas, tarifa, costo, iva, total;

    do {
        cout << "Hojas a imprimir: ";
        cin >> hojas;
        if (hojas <= 0) {
            cout << "ERROR! Las hojas deben ser mayores a 0" << endl;
        }
    } while (hojas <= 0);

    if (hojas <= 100) {
        tarifa = 2;
    } else if (hojas <= 500) {
        tarifa = 1.5;
    } else {
        tarifa = 1;
    }
    costo = hojas * tarifa;

    iva = costo * 0.16;

    total = costo + iva;

    cout << endl << "NOTA DE FOTOCOPIAS" << endl;
    cout << "Hojas: " << hojas << " hojas" << endl;
    cout << "Costo: $" << costo << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
