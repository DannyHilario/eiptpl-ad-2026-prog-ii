#include <iostream>
using namespace std;

// Recibo de viaje por aplicacion: todo el calculo vive en main.

int main() {

    double km, tarifa, costoViaje, cuota, total;

    do {
        cout << "Kilometros recorridos: ";
        cin >> km;
        if (km <= 0) {
            cout << "ERROR! Los kilometros deben ser mayores a 0" << endl;
        }
    } while (km <= 0);

    if (km <= 5) {
        tarifa = 14;
    } else if (km <= 15) {
        tarifa = 11;
    } else {
        tarifa = 9;
    }
    costoViaje = km * tarifa;

    cuota = costoViaje * 0.10;

    total = costoViaje + cuota;

    cout << endl << "RECIBO DE VIAJE" << endl;
    cout << "Distancia: " << km << " km" << endl;
    cout << "Costo del viaje: $" << costoViaje << endl;
    cout << "Cuota de servicio: $" << cuota << endl;
    cout << "Total a pagar: $" << total << endl;

    return 0;
}
