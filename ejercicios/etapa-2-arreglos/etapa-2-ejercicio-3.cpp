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
double calcularSueldoBruto(double sueldo_diario);
double calcularSueldoNeto(double sueldo_bruto, double isr);

const int DIAS_SEMANA = 7;

const double LIMITE_INFERIOR[3] = {0.01, 750.01, 2340.01};
const double LIMITE_SUPERIOR[2] = {750.00, 2340.00};
const double CUOTA_FIJA[3] = {45.00, 119.00, 514.00};
const double PORCENTAJE_EXCEDENTE[3] = {0.0257, 0.12, 0.2254};

int main() {

    double sueldo_bruto, isr, sueldo_diario, sueldo_neto;
    double excedente;

    do {
        system("clear");
        cout << "Introduce el sueldo diario del empleado: ";
        cin >> sueldo_diario;
        
        if(sueldo_diario < LIMITE_INFERIOR[0]) {
            cout << "ERROR! Salario no valido" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }

    } while(sueldo_diario < LIMITE_INFERIOR[0]);

    sueldo_bruto = calcularSueldoBruto(sueldo_diario);
    isr = calcularISR(sueldo_bruto);
    sueldo_neto = calcularSueldoNeto(sueldo_bruto, isr);

    system("clear");
    cout << "RECIBO SEMANAL" << endl << endl;
    cout << "Sueldo diario: " << sueldo_diario << endl;
    cout << "Sueldo bruto: " << sueldo_bruto << endl;
    cout << "ISR: -" << isr << endl;
    cout << "Sueldo neto: " << sueldo_neto << endl;
}

double calcularISR(double sueldo_bruto){

    double isr;
    int numero_rango;
    int indice;

    if(sueldo_bruto <= LIMITE_SUPERIOR[0]){
        numero_rango = 1;
    } else if (sueldo_bruto <= LIMITE_SUPERIOR[1] ) {
        numero_rango = 2;
    } else {
        numero_rango = 3; 
    }
    indice = numero_rango - 1;
    isr = ((sueldo_bruto - LIMITE_INFERIOR[indice]) * PORCENTAJE_EXCEDENTE[indice]) + CUOTA_FIJA[indice];
    return isr;
}

double calcularSueldoBruto(double sueldo_diario){
    return (sueldo_diario * DIAS_SEMANA);
}

double calcularSueldoNeto(double sueldo_bruto, double isr){
    return (sueldo_bruto - isr);
}