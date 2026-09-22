#include <iostream>
#include <limits> // Linea macOS
using namespace std;
int main(){

    const double CERO_ABSOLUTO = -273.15; // Limite fisico: ninguna temperatura puede ser menor
    const double LIMITE_FRIO = 15; // Menor a esto es Frio
    const double LIMITE_CALUROSO = 25; // Mayor a esto es Caluroso
    int I; // FOR
    int N;
    double temperatura, suma_temperaturas = 0, promedio; // suma_temperaturas es acumulador
    int dias_frios = 0, dias_templados = 0, dias_calurosos = 0; // Contadores por categoria

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
        // Validación del cero absoluto (se repite para el mismo dia)
        do {
            cout << "Temperatura del dia " << I << ": ";
            cin >> temperatura;

            if(temperatura < CERO_ABSOLUTO){
                cout << "ERROR. Esa temperatura esta por debajo del cero absoluto (-273.15 C)" << endl;
            }

        }while(temperatura < CERO_ABSOLUTO);

        // Clasificación
        if(temperatura < LIMITE_FRIO){
            dias_frios = dias_frios + 1;
        } else if(temperatura <= LIMITE_CALUROSO){
            dias_templados = dias_templados + 1;
        } else {
            dias_calurosos = dias_calurosos + 1;
        }

        suma_temperaturas = suma_temperaturas + temperatura; // Acumulador
    }

    promedio = suma_temperaturas / N;

    /* REPORTE FINAL */
    system("clear");
    cout << "********* REPORTE FINAL *********" << endl << endl;
    cout << "Dias frios: " << dias_frios << endl;
    cout << "Dias templados: " << dias_templados << endl;
    cout << "Dias calurosos: " << dias_calurosos << endl << endl;
    cout << "Temperatura promedio: " << promedio << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
    cin.get(); // Linea macOS

    return 0;
}
