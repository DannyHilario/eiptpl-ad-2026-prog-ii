#include <iostream>
#include <limits> // Linea macOS
using namespace std;

void procesarSalarioEmpleado(float horas_trabajadas, float tarifa_x_hora);
const float TASA_IMPUESTO = 0.16;

int main() {

    float horas1, tarifa1;
    float horas2, tarifa2;
    float horas3, tarifa3;
    system("clear");

    cout << " ********* CALCULO DE NOMINA (3 EMPLEADOS) ********* " << endl << endl;

    // --- Empleado 1 ---
    cout << "Empleado 1 - Horas trabajadas: ";
    cin >> horas1;
    cout << "Empleado 1 - Tarifa por hora: ";
    cin >> tarifa1;

    procesarSalarioEmpleado(horas1, tarifa1);

    // --- Empleado 2 ---
    cout << "Empleado 2 - Horas trabajadas: ";
    cin >> horas2;
    cout << "Empleado 2 - Tarifa por hora: ";
    cin >> tarifa2;

    procesarSalarioEmpleado(horas2, tarifa2);

    // --- Empleado 3 ---
    cout << "Empleado 3 - Horas trabajadas: ";
    cin >> horas3;
    cout << "Empleado 3 - Tarifa por hora: ";
    cin >> tarifa3;

    procesarSalarioEmpleado(horas3, tarifa3);

    cout << " ********* FIN DEL REPORTE ********* " << endl;

    return 0;
}

void procesarSalarioEmpleado(float horas_trabajadas, float tarifa_x_hora){

    float sueldo_bruto, impuesto, sueldo_neto;

    sueldo_bruto = horas_trabajadas * tarifa_x_hora;
    impuesto = sueldo_bruto * TASA_IMPUESTO;
    sueldo_neto = sueldo_bruto - impuesto;

    cout << "Sueldo bruto: " << sueldo_bruto << endl;
    cout << "Impuesto retenido: " << impuesto << endl;
    cout << "Sueldo neto: " << sueldo_neto << endl << endl;

}