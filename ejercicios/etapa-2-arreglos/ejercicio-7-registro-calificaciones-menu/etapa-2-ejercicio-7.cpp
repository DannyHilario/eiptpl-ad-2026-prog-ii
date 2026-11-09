#include <iostream>
#include <cstdlib>
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
    int registrados = 0;   // cuantos alumnos hay y en que fila va el siguiente
    int opcion;
    int i, j;

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

        system("clear");

        switch(opcion){

            case 1:
                if(registrados == MAX_ALUMNOS){
                    cout << "El registro esta lleno: ya hay " << MAX_ALUMNOS << " alumnos" << endl;
                }
                else{
                    double suma = 0;

                    cout << "ALUMNO " << registrados + 1 << endl;
                    for(j = 0; j < MAX_PARCIALES; j++){
                        do{
                            cout << "  Parcial " << j + 1 << ": ";
                            cin >> calificaciones[registrados][j];
                            if(calificaciones[registrados][j] < CALIF_MINIMA || calificaciones[registrados][j] > CALIF_MAXIMA){
                                cout << "  ERROR! La calificacion debe estar entre " << CALIF_MINIMA << " y " << CALIF_MAXIMA << endl;
                            }
                        }while(calificaciones[registrados][j] < CALIF_MINIMA || calificaciones[registrados][j] > CALIF_MAXIMA);

                        suma = suma + calificaciones[registrados][j];
                    }

                    promedios[registrados] = suma / MAX_PARCIALES;

                    cout << endl << "Promedio: " << promedios[registrados] << " -> ";
                    if(promedios[registrados] >= CALIF_MINIMA_APROBATORIA){
                        cout << "Aprobado" << endl;
                    }
                    else{
                        cout << "Reprobado" << endl;
                    }

                    registrados++;
                }
                break;

            case 2:
                if(registrados == 0){
                    cout << "Todavia no hay alumnos registrados" << endl;
                }
                else{
                    int aprobados = 0;
                    double sumaPromedios = 0;

                    for(i = 0; i < registrados; i++){
                        if(promedios[i] >= CALIF_MINIMA_APROBATORIA){
                            aprobados++;
                        }
                        sumaPromedios = sumaPromedios + promedios[i];
                    }

                    cout << "REPORTE DEL GRUPO" << endl << endl;
                    cout << "Alumnos registrados: " << registrados << endl;
                    cout << "Aprobados: " << aprobados << " (" << aprobados * 100.0 / registrados << "%)" << endl;
                    cout << "Reprobados: " << registrados - aprobados << " (" << (registrados - aprobados) * 100.0 / registrados << "%)" << endl;
                    cout << "Promedio del grupo: " << sumaPromedios / registrados << endl;
                }
                break;

            case 3:
                if(registrados == 0){
                    cout << "Todavia no hay alumnos registrados" << endl;
                }
                else{
                    cout << "TABLA DE CALIFICACIONES" << endl << endl;
                    cout << "\t\tP1\tP2\tP3\tPromedio" << endl;
                    for(i = 0; i < registrados; i++){
                        cout << "Alumno " << i + 1 << "\t";
                        for(j = 0; j < MAX_PARCIALES; j++){
                            cout << "\t" << calificaciones[i][j];
                        }
                        cout << "\t" << promedios[i] << "\t";
                        if(promedios[i] >= CALIF_MINIMA_APROBATORIA){
                            cout << "Aprobado" << endl;
                        }
                        else{
                            cout << "Reprobado" << endl;
                        }
                    }
                }
                break;

            case 4:
                cout << "Fin del programa" << endl;
                break;

        }

        if(opcion != 4){
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }
    }while(opcion != 4);

    return 0;
}
