#include <iostream>
#include <limits> // Linea macOS
using namespace std;


int main(){

    const int NUM_ALUMNOS = 5;
    const int NUM_PARCIALES = 3;
    double calificaciones[NUM_ALUMNOS][NUM_PARCIALES];
    double calificacion;
    int i, j;

    system("clear");

    for(i = 0; i < NUM_ALUMNOS; i++){

        system("clear");
        cout << "Alumno " << i + 1 << endl << endl;
        for(j = 0; j < NUM_PARCIALES; j++){

            do{
                cout << "\tCalificacion " << j + 1 << ": ";
                cin >> calificacion;
                if(calificacion < 0 || calificacion > 100){
                    cout << "ERROR! Calificacion no valida. Solo entre 0 y 100" << endl;
                }
            }while(calificacion < 0 || calificacion > 100);

            calificaciones[i][j] = calificacion;

        }
        cout << endl;
        
    }

    system("clear");
    cout << "\t\t" << "P1\tP2\tP3" << endl;
    for(i = 0; i < NUM_ALUMNOS; i++){
        cout << "Alumno " << i + 1;
        for(j = 0; j < NUM_PARCIALES; j++){
            // cout << "Alumno " << i + 1 << "\t" << calificaciones[i][j] << "\t" << calificaciones[i][j+1] << "\t" << calificaciones[i][j+2] << endl;
            cout << "\t" << calificaciones[i][j];
        }
        cout << endl;
    }
}