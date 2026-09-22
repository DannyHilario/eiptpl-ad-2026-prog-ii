#include <iostream>
#include <limits> // Linea macOS
using namespace std;

// Ejemplo de como capturar e imprimir los valores de un arreglo de enteros

int main() {

    int numeros[10];
    int cantidad;
    int I;

    do{

        system("clear");
        cout << "Introduce la cantidad de numeros a capturar" << endl;
        cout << "Max 10" << endl;
        cout << "Cantidad: ";
        cin >> cantidad;

        if(cantidad < 0 || cantidad > 10) {
            system("clear");
            cout << "ERROR! Cantidad no permitida." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Linea macOS
        }

    }while(cantidad < 0 || cantidad > 10);

    /*
    FORMA MANUAL

    system("clear");
    cout << "Elemento 1: ";
    cin >> numeros[0];

    system("clear");
    cout << "El elemento 1 es: " << numeros[0];

    */
    system("clear");
    cout << "CAPTURA DEL ARREGLO" << endl << endl;
    for(I = 0; I < cantidad; I++) {
        
        cout << "Elemento " << I+1 << ": ";
        cin >> numeros[I];
    
    }

    system("clear");
    cout << "IMPRESION DEL ARREGLO" << endl << endl;
    for(I = 0; I < cantidad; I++) {
        cout << "Elemento " << I+1 << ": " << numeros[I] << endl; 
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); // Linea macOS

}