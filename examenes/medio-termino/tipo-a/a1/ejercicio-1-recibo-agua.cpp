#include <iostream>
using namespace std;

// Recibo de agua: todo el calculo vive en main.

int main() {

    double consumo, tarifa, subtotal, iva, total;

    do {
        cout << "Consumo del mes (m3): ";
        cin >> consumo;
        if (consumo <= 0) {
            cout << "ERROR! El consumo debe ser mayor a 0" << endl;
        }
    } while (consumo <= 0);

    if (consumo <= 20) {
        tarifa = 12;
    } else if (consumo <= 40) {
        tarifa = 18;
    } else {
        tarifa = 25;
    }
    subtotal = consumo * tarifa;

    iva = subtotal * 0.16;

    total = subtotal + iva;

    cout << endl << "RECIBO DE AGUA" << endl;
    cout << "Consumo: " << consumo << " m3" << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
