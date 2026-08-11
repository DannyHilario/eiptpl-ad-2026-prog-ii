#include <iostream>
#include <limits> // Linea macOS
using namespace std;
int main(){

    int Opcion;

    do {
        do {
            system("clear");
            cout << " ********** MENU PRINCIPAL ********** " << endl;
            cout << endl << endl << endl;
            cout << "Opcion 1: Caja 1" << endl;
            cout << "Opcion 2: Caja 2" << endl;
            cout << "Opcion 3: Caja 3" << endl;
            cout << "Opcion 4: Finalizar Turno" << endl;
            cout << endl << "Introduce una opcion: ";
            cin >> Opcion;

            /* Validación numérica */
            if(Opcion < 1 || Opcion > 4){
                cout << "ERROR. Valor no permitido" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
                cin.get(); // Linea macOS
            }

        }while((Opcion < 1 || Opcion > 4));

        system("clear");

        switch(Opcion){
            case 1:
                cout << "AQUI VA LA LOGICA DEL CASO 1 Y ASI" << endl;
                break;

            case 2:
                cout << "AQUI VA LA LOGICA DEL CASO 2 Y YA QUE" << endl;
                break;

            case 3:
                cout << "AQUI VA LA LOGICA DEL CASO 3 Y SI SI" << endl;
                break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
        cin.get(); // Linea macOS


    } while(Opcion != 4);
    /* REPORTE FINAL */
}