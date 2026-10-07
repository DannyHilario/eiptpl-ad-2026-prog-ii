#include <iostream>
using namespace std;

// Renta de auto: todo el calculo vive en main.

int main() {

    double dias, tarifa, renta, iva, total;

    do {
        cout << "Dias de renta: ";
        cin >> dias;
        if (dias <= 0) {
            cout << "ERROR! Los dias deben ser mayores a 0" << endl;
        }
    } while (dias <= 0);

    if (dias <= 3) {
        tarifa = 800;
    } else if (dias <= 7) {
        tarifa = 700;
    } else {
        tarifa = 600;
    }
    renta = dias * tarifa;

    iva = renta * 0.16;

    total = renta + iva;

    cout << endl << "CONTRATO DE RENTA" << endl;
    cout << "Dias: " << dias << " dias" << endl;
    cout << "Renta: $" << renta << endl;
    cout << "IVA: $" << iva << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
