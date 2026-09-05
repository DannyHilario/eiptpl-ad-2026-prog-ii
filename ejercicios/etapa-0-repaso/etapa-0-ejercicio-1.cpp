#include <iostream>
#include <limits> // Linea macOS
using namespace std;
int main() {

    const float CALIFICACION_MINIMA = 70;
    float c1, c2, c3, promedio, porcentaje_aprobados; // Declaración: Estas variables se calculan o leen desde el teclado
    int cantidad_aprobados = 0, cantidad_reprobados = 0; // Declaración e inicialización | Contadores
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
            cantidad_aprobados = cantidad_aprobados + 1; // ES LO MISMO QUE contador_aprobados++;

        }
        else {

            cout << "Alumno REPROBADO :(" << endl;
            cantidad_reprobados = cantidad_reprobados + 1;

        }

        cout << "Presiona Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
        cin.get(); // Linea macOS
    }
    system("clear");
    cout << " ********* REPORTE FINAL ********* "<< endl << endl <<endl;
    cout << " Aprobados: " << cantidad_aprobados << endl;
    cout << " Reprobados: " << cantidad_reprobados << endl;
    return 0;
}