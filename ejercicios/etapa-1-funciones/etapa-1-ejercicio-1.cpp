#include <iostream>
#include <limits> // Linea macOS
using namespace std;

double calcularImpuesto(double sueldo_bruto); // Paso 1: Declaración de la función.
double calcularSueldoBruto(double horas_trabajadas, double tarifa_x_hora);
double calcularSueldoNeto(double sueldo_bruto, double impuesto);
const float TASA_IMPUESTO = 0.16;
const int HORAS_MAXIMAS_PERMITIDAS = 80;

int main() {

    int cantidad_empleados;
    int i;
    double tarifa_x_hora, horas_trabajadas;
    double sueldo_bruto, impuesto, sueldo_neto;

    do{
        system("clear");
        cout << "Introduce la cantidad de empleados: " << endl;
        cin >> cantidad_empleados;

        if(cantidad_empleados < 0){
            cout << "ERROR! No hay trabajadores disponibles" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }
    }while(cantidad_empleados < 0);

    for(i = 1; i <= cantidad_empleados; i ++)
    {
        do{
            system("clear");
            cout << "Empleado " << i << endl;
            cout << "Tarifa por hora: " << endl;
            cin >> tarifa_x_hora;

            if(tarifa_x_hora < 0){
                cout << "ERROR! La tarifa no puede ser negativa" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
                cin.get(); // Linea macOS
            }
        }while(tarifa_x_hora < 0);

        // Regla de negocio: Un trabajador puede trabajar máximo 60 horas.

        do{
            system("clear");
            cout << "Empleado " << i << endl;
            cout << "Horas trabajadas: " << endl;
            cin >> horas_trabajadas;

            if(horas_trabajadas < 0 || horas_trabajadas > HORAS_MAXIMAS_PERMITIDAS){
                cout << "ERROR! Las horas trabajadas no son válidas. El máximo es 60 horas." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
                cin.get(); // Linea macOS
            }
        }while(horas_trabajadas < 0 || horas_trabajadas > HORAS_MAXIMAS_PERMITIDAS);

        sueldo_bruto = calcularSueldoBruto(horas_trabajadas, tarifa_x_hora);
        impuesto = calcularImpuesto(sueldo_bruto);
        sueldo_neto = calcularSueldoNeto(sueldo_bruto, impuesto);

        system("clear");
        cout << "Sueldo bruto: " << sueldo_bruto << endl;
        cout << "Impuesto retenido: " << impuesto << endl;
        cout << "Sueldo neto: " << sueldo_neto << endl << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
        cin.get(); // Linea macOS
    }

    return 0;
}

double calcularSueldoBruto(double horas_trabajadas, double tarifa_x_hora){
    return (horas_trabajadas * tarifa_x_hora);
}

double calcularImpuesto(double sueldo_bruto){
    return (sueldo_bruto * TASA_IMPUESTO);
}

double calcularSueldoNeto(double sueldo_bruto, double impuesto){
    return (sueldo_bruto - impuesto);
}