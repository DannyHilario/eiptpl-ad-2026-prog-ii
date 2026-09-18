#include <iostream>
#include <limits> // Linea macOS
#include <string>
using namespace std;

int main(){

    double precio_unitario[3] = {45.00, 38.00, 25.50};
    string descripcion_articulo[3] = {"Paracetamol", "Gel antibacterial", "Cubrebocas"};
    int clave_articulo;
    double total_a_pagar, cantidad_articulos;

    cout << "Clave del articulo: ";
    cin >> clave_articulo;
    cout << "Cantidad de articulos: ";
    cin >> cantidad_articulos;


    /*
    switch(clave_articulo){

        case 1:
            total_a_pagar = 45.00 * cantidad_articulos;
            break;

        case 2:
            total_a_pagar = 38.00 * cantidad_articulos;
            break;         
            
        case 3:
            total_a_pagar = 25.50 * cantidad_articulos;
            break;

    }
    */

    total_a_pagar = precio_unitario[clave_articulo - 1] * cantidad_articulos;
    system("clear");
    cout << " RECIBO DE PAGO " << endl << endl << endl;
    cout << "Articulo: " << clave_articulo << " | " << descripcion_articulo[clave_articulo - 1] << endl;
    cout << "Precio unitario: $" << precio_unitario[clave_articulo - 1] << endl;
    cout << "Cantidad: " << cantidad_articulos << endl << endl;
    cout << "TOTAL A PAGAR: $" << total_a_pagar << endl << endl;
    cout << "__________________________________" << endl;
    cout << "GRACIAS POR SU COMPRA Y ASI" << endl;
}