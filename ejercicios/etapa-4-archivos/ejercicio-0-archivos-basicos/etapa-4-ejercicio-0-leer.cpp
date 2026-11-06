#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
    Programa 3: LEER un archivo.
    Muestra todo lo que tiene compras.txt, renglon por renglon, y cuenta los productos.
*/

int main(){

    string producto;
    int cantidad;
    int productos = 0;

    ifstream archivo("compras.txt");   // abre compras.txt para leer

    // Cada vuelta lee un renglon: primero el producto y despues la cantidad.
    // Cuando ya no hay nada que leer, la condicion es falsa y el while termina
    while(archivo >> producto >> cantidad){
        cout << producto << ": " << cantidad << endl;
        productos++;
    }

    archivo.close();

    cout << "Productos en la lista: " << productos << endl;

    return 0;
}
