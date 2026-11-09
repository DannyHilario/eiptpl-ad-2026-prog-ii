#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
    Programa 2: AGREGAR a un archivo.
    Pide un producto con su cantidad y lo agrega AL FINAL de compras.txt.
    Modo ios::app: lo que ya tenia el archivo se conserva.
*/

int main(){

    string producto;
    int cantidad;

    cout << "Producto: ";
    cin >> producto;
    cout << "Cantidad: ";
    cin >> cantidad;

    ofstream archivo("compras.txt", ios::app);   // app = append = agregar al final
    archivo << producto << " " << cantidad << endl;

    archivo.close();

    cout << "Agregado al final de compras.txt" << endl;

    return 0;
}
