#include <iostream>
#include <cstdlib> // system()
using namespace std;

const int TAMANIO = 50;
int busquedaLineal(const int arreglo[], int tamanio, int clave); // Declaración

int main(){
    int numero_buscado;
    int indice;
    int folios[TAMANIO] = {
        34, 71,  8, 56, 19, 92, 45, 27, 63, 11,
        80,  3, 58, 27, 94, 40, 16, 75, 52, 88,
         7, 69, 31, 27, 99, 14, 47, 85, 22, 60,
        38, 77,  5, 91, 50, 26, 66, 13, 82, 44,
        97, 29, 61, 18, 73, 36, 54, 10, 89, 65
    };
    system("clear"); // En Dev-C++ (Windows): system("cls");
    cout << "BUSQUEDA DE FOLIOS" << endl << endl;
    cout << "Numero a buscar: ";
    cin >> numero_buscado;
    indice = busquedaLineal(folios, TAMANIO, numero_buscado);
    if(indice != -1){
        cout << "Numero encontrado! :D" << endl << endl;
        cout << "Indice del arreglo: " << indice << endl;
        cout << "Posicion: " << indice + 1 << endl;
        cout << "Numero: " << folios[indice] << endl;
    } else {
        cout << "Numero NO encontrado :(" << endl;
        cout << "Respuesta de la funcion: " << indice << endl;
    }
}

// Definición de busquedaLineal
int busquedaLineal(const int arreglo[], int tamanio, int clave){
    int i;
    for(i = 0; i < tamanio; i ++){
        if(clave == arreglo[i]){
            return i;
        }
    }
    // La unica forma de llegar aquí, es que el arreglo no contiene clave
    return -1;
}
