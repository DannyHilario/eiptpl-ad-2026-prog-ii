#include <iostream>
using namespace std;

// Envio de paqueteria: todo el calculo vive en main.

int main() {

    double peso, tarifa, costo_envio, seguro, total;

    do {
        cout << "Peso del paquete (kg): ";
        cin >> peso;
        if (peso <= 0) {
            cout << "ERROR! El peso debe ser mayor a 0" << endl;
        }
    } while (peso <= 0);

    if (peso <= 5) {
        tarifa = 40;
    } else if (peso <= 15) {
        tarifa = 32;
    } else {
        tarifa = 25;
    }
    costo_envio = peso * tarifa;

    seguro = costo_envio * 0.03;

    total = costo_envio + seguro;

    cout << endl << "GUIA DE ENVIO" << endl;
    cout << "Peso: " << peso << " kg" << endl;
    cout << "Costo de envio: $" << costo_envio << endl;
    cout << "Seguro: $" << seguro << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
