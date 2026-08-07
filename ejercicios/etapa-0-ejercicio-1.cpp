#include <iostream>
#include <limits> // Linea macOS
using namespace std;
int main() {

    const float CALIFICACION_MINIMA = 70;
    float c1, c2, c3, promedio;
    int I, N;
    system("clear");
    cout << "Introduce la cantidad de alumnos a evaluar: ";
    cin >> N;
    for(I = 1;I <= N;I++){
        system("clear");
        cout << "Introduce la primer calificacion: ";
        cin >> c1;
        cout << "Introduce la segunda calificacion: ";
        cin >> c2;
        cout << "Introduce la tercera calificacion: ";
        cin >> c3;
        promedio = (c1 + c2 + c3)/3;
        cout << "El promedio del alumno es: " << promedio << endl;
        if(promedio >= CALIFICACION_MINIMA) {
            cout << "Alumno APROBADO :D" << endl;
        }
        else {
            cout << "Alumno NO APROBADO :(" << endl;
        }
        cout << "Presiona Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
        cin.get(); // Linea macOS
    }
}