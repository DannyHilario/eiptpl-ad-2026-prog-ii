#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
    Programa 1: ESCRIBIR un archivo.
    Pide 3 productos con su cantidad y los guarda en compras.txt, uno por renglon.
    Modo normal: si compras.txt ya existia, se BORRA lo que tenia y se empieza de cero.
*/

int main(){

    string producto;
    int cantidad;

    ofstream archivo("compras.txt");   // abre (o crea) compras.txt para escribir

    for(int i = 1; i <= 3; i++){
        cout << "Producto " << i << ": ";
        cin >> producto;
        cout << "Cantidad: ";
        cin >> cantidad;

        archivo << producto << " " << cantidad << endl;   // se escribe igual que con cout
    }

    archivo.close();   // cierra el archivo: ahora si queda guardado

    cout << "Listo, abre compras.txt para ver la lista" << endl;

    return 0;
}
