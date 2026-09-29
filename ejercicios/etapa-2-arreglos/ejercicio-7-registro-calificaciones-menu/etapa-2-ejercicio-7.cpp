#include <iostream>
#include <limits> // Linea macOS
using namespace std;


int main(){

    const int MAX_ALUMNOS = 5;
    const int MAX_PARCIALES = 3;
    const double CALIF_MINIMA = 0;
    const double CALIF_MAXIMA = 100;
    const double CALIF_MINIMA_APROBATORIA = 70;
    
    double calificaciones[MAX_ALUMNOS][MAX_PARCIALES];
    double promedios[MAX_ALUMNOS];
    int opcion;

    do{
        do{
            system("clear");
            cout << "REGISTRO DE CALIFICACIONES" << endl << endl << endl;
            cout << "1.- Registrar un alumno" << endl;
            cout << "2.- Reporte del grupo" << endl;
            cout << "3.- Tabla de calificaciones" << endl;
            cout << "4.- Salir del programa" << endl << endl;
            cout << "Opcion: ";
            cin >> opcion;
            if(opcion < 1 || opcion > 4){
                system("clear");
                cout << "ERROR! Opcion no valida o no existente" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
                cin.get(); // Linea macOS
            }
        
        }while(opcion < 1 || opcion > 4);

        switch(opcion){

            case 1:
                cout << "Aqui va el caso 1" << endl;
                break;

            case 2:
                cout << "Aqui va el caso 2" << endl;
                break;

            case 3:
                cout << "Aqui va el caso 3" << endl;

        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
        cin.get(); // Linea macOS
    }while(opcion != 4);


}