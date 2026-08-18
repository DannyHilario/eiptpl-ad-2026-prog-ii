#include <iostream>
#include <limits> // Linea macOS
using namespace std;
int main(){
    int I; // FOR
    int N;

    // Validación Numérica de N
    do {
        
        system("clear"); // Linea macOS
        cout << "Introduce la cantidad de temperaturas: ";
        cin >> N;

        if(N < 1){
            cout << "ERROR. Valor no permitido. La cantidad de temperaturas debe ser un numero positivo" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }

    }while(N < 1);

    //Leer las N Temperaturas
    for(I = 1; I <= N; I++)
    {
        cout << "Ejecucion " << I << endl;
    }

}