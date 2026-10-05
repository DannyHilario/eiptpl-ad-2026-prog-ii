#include <iostream>
using namespace std;

// Ticket de estacionamiento: todo el calculo vive en main.

int main() {

    double horas, tarifa, cobro, comision, total;

    do {
        cout << "Horas de estancia: ";
        cin >> horas;
        if (horas <= 0) {
            cout << "ERROR! Las horas deben ser mayores a 0" << endl;
        }
    } while (horas <= 0);

    if (horas <= 2) {
        tarifa = 25;
    } else if (horas <= 5) {
        tarifa = 20;
    } else {
        tarifa = 15;
    }
    cobro = horas * tarifa;

    comision = cobro * 0.04;

    total = cobro + comision;

    cout << endl << "TICKET DE ESTACIONAMIENTO" << endl;
    cout << "Horas: " << horas << " h" << endl;
    cout << "Cobro: $" << cobro << endl;
    cout << "Comision tarjeta: $" << comision << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
