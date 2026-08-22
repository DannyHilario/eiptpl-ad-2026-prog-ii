#include <iostream>
#include <limits> // Linea macOS
using namespace std;

/*
 * Escribe un programa que calcule el sueldo semanal de un empleado, considerando
 * su sueldo diario. El programa debe calcular el ISR (Impuesto sobre la renta) considerando
 * la siguiente tabla:
 * 
 * TABLA PARA CALCULO DE SUELDO SEMANAL 
 * 
 * Limite inferior | Limite superior | Cuota Fija | Porcentaje sobre el excedente
 *      $0.01              $750.00            $45                  2.57%
 *      $750.01            $2340.00           $119                 12%
 *      $2340.1            en delante         $514                 22.54%
 * 
 * 
 * El prototipo de la función para calcular el ISR será: 
 * double calcularISR(double sueldo_bruto)
 * 
 * sueldo_neto = sueldo_diario * 7 - isr;
 * sueldo_neto = sueldo_bruto - isr;
 * 
 * Pasos para el calculo del ISR
 * 1) Identificar en que rango cae el sueldo bruto
 * 2) Calcular el excedente, restando el sueldo bruto 
 *    del limite inferior del rango donde cae el sueldo bruto
 *    
 * 3) El valor anterior, calcular el porcentaje aplicable a ese valor. 
 * 4) El valor anterior, sumar la cuota fija 
 * 
 
 */

double calcularISR(double sueldo_bruto); // Paso 1: Declaración de la función.

int main() {

    double sueldo_bruto, isr, sueldo_diario, sueldo_neto;
    double excedente;

    do {
        system("clear");
        cout << "Introduce el sueldo diario del empleado: ";
        cin >> sueldo_diario;
        
        if(sueldo_diario < 0.01) {
            cout << "ERROR! Salario no valido" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }

    } while(sueldo_diario < 0.01);

    sueldo_bruto = sueldo_diario * 7;

    /* CALCULO DEL ISR */

    if(sueldo_bruto <= 750){
        // Rango 1
        isr = ((sueldo_bruto - 0.01) * 0.0257) + 45;

    } else if (sueldo_bruto <= 2340 ) {
        // Rango 2
        isr = ((sueldo_bruto - 750.01) * 0.12) + 119;

    } else {
        // Rango 3
        isr = ((sueldo_bruto - 2340.01) * 0.2254) + 514;

    }
    /* FIN DEL CALCULO DEL ISR */
    
    sueldo_neto = sueldo_bruto - isr;







    system("clear");
    cout << "RECIBO SEMANAL" << endl << endl;
    cout << "Sueldo diario: " << sueldo_diario << endl;
    cout << "Sueldo bruto: " << sueldo_bruto << endl;
    cout << "ISR: -" << isr << endl;
    cout << "Sueldo neto: " << sueldo_neto << endl;

}