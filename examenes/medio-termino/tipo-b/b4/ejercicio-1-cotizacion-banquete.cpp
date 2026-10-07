#include <iostream>
using namespace std;

// Cotizacion de banquete: todo el calculo vive en main.

int main() {

    double invitados, tarifa, costo, propina, total;

    do {
        cout << "Numero de invitados: ";
        cin >> invitados;
        if (invitados <= 0) {
            cout << "ERROR! Los invitados deben ser mayores a 0" << endl;
        }
    } while (invitados <= 0);

    if (invitados <= 50) {
        tarifa = 350;
    } else if (invitados <= 100) {
        tarifa = 300;
    } else {
        tarifa = 250;
    }
    costo = invitados * tarifa;

    propina = costo * 0.10;

    total = costo + propina;

    cout << endl << "COTIZACION DE BANQUETE" << endl;
    cout << "Invitados: " << invitados << " personas" << endl;
    cout << "Costo del banquete: $" << costo << endl;
    cout << "Propina meseros: $" << propina << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
