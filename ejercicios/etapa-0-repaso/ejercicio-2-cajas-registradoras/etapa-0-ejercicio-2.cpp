#include <iostream>
#include <limits> // Linea macOS
using namespace std;
int main(){

    int Opcion; // Valor que debe estar entre 1 y 4.
    double ef_cobrado; // Lo que cobró la caja seleccionada
    double ef_caja1 = 0, ef_caja2 = 0, ef_caja3 = 0, ef_total = 0; // Acumuladores de cada caja
    int con_caja1 = 0, con_caja2 = 0, con_caja3 = 0, con_total = 0; // Contadores por caja
    int num_transaccion = 0;

    do {
        num_transaccion = num_transaccion + 1;
        do {
            system("clear");
            
            cout << "********** MENU PRINCIPAL **********" << endl;
            cout << endl << endl << endl;
            cout << "Numero de Transaccion: " << num_transaccion << endl << endl;
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

        if(Opcion != 4){
            cout << "Introduce el efectivo cobrado: ";
            cin >> ef_cobrado;
        }

        system("clear");

        switch(Opcion){
            case 1:
                con_caja1 = con_caja1 + 1; // Contador
                ef_caja1 = ef_caja1 + ef_cobrado; // Acumulador
                break;

            case 2:
                con_caja2 = con_caja2 + 1; // Contador
                ef_caja2 = ef_caja2 + ef_cobrado; //Acumulador
                break;

            case 3:
                con_caja3 = con_caja3 + 1; // Contador
                ef_caja3 = ef_caja3 + ef_cobrado; //Acumulador
                break;
        }

    } while(Opcion != 4);
    /* REPORTE FINAL */

    con_total = con_caja1 + con_caja2 + con_caja3;
    ef_total = ef_caja1 + ef_caja2 + ef_caja3;

    system("clear");

    cout << "********** REPORTE FINAL **********" << endl << endl << endl << endl;
    cout << "Clientes Caja 1: " << con_caja1 << endl;
    cout << "Clientes Caja 2: " << con_caja2 << endl;
    cout << "Clientes Caja 3: " << con_caja3 << endl;
    cout << "Clientes TOTALES: " << con_total << endl << endl << endl;
    cout << "Efectivo Caja 1: " << ef_caja1 << endl;
    cout << "Efectivo Caja 2: " << ef_caja2 << endl;
    cout << "Efectivo Caja 3: " << ef_caja3 << endl;
    cout << "Efectivo TOTAL: " << ef_total << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
    cin.get(); // Linea macOS
}