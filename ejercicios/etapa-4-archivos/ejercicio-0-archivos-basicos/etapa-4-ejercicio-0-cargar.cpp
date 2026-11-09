#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Producto{
    string nombre;
    int cantidad;
};

const int MAX = 15;   // cuantos productos caben en el arreglo

int main(){

    Producto lista[MAX];
    int n = 0;   // cuantos productos se han cargado
    int total = 0;

    ifstream archivo("compras.txt");

    // Cada vuelta lee un renglon y lo guarda en la casilla n del arreglo.
    // Si la lectura sale bien, n++ avanza a la siguiente casilla.
    // Se detiene cuando el archivo se acaba o cuando el arreglo se llena
    while(n < MAX && archivo >> lista[n].nombre >> lista[n].cantidad){
        n++;
    }

    archivo.close();

    // El archivo ya esta cerrado: los datos ahora viven en el arreglo
    cout << "Se cargaron " << n << " productos" << endl;

    for(int i = 0; i < n; i++){
        cout << i + 1 << ". " << lista[i].nombre << ": " << lista[i].cantidad << endl;
        total = total + lista[i].cantidad;
    }

    cout << "Total de piezas: " << total << endl;

    return 0;
}
