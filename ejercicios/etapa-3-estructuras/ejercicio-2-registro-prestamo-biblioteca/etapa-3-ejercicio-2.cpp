#include <iostream>
#include <string>
#include <cstdlib>
#include <limits> // Linea macOS
using namespace std;

/*
    Registro de prestamos de una biblioteca. De cada prestamo se guarda:

    Numero de prestamo,
    Nombre de la persona a la que se le presta,
    Nombre del libro,
    Fecha de prestamo,
    Fecha de devolucion

    El menu muestra la diferencia entre INICIALIZAR los datos (escritos en el
    programa) y CAPTURARLOS (escritos por el usuario al correr el programa).
*/

const int N_INICIALIZADOS = 4;
const int N_CAPTURADOS = 3;

struct Fecha{
    int Dia;
    int Mes;
    int Anio;
};

struct Prestamo{
    int NumeroPrestamo;
    string NombreSocio;
    string NombreLibro;
    Fecha FechaPrestamo;
    Fecha FechaDevolucion;
};

int fechaComoNumero(int dia, int mes, int anio);

int main(){

    Prestamo inicializados[N_INICIALIZADOS] = {
        {1, "Juan",   "Matematicas", {12, 10, 2026}, {16, 10, 2026}},
        {2, "Pedro",  "Espanol III", {13, 10, 2026}, {16, 10, 2026}},
        {3, "Luis",   "Geometria",   {14, 10, 2026}, {16, 10, 2026}},
        {4, "Carlos", "Ingles II",   {13, 10, 2026}, {19, 10, 2026}}
    };

    Prestamo capturados[N_CAPTURADOS];

    int i;
    int opcion;
    int prestamo, devolucion; // fechas como numero aaaammdd, para compararlas

    do{
        system("clear");
        cout << "PRESTAMOS DE LA BIBLIOTECA" << endl << endl;
        cout << "1. Mostrar prestamos inicializados" << endl;
        cout << "2. Capturar prestamos" << endl;
        cout << "3. Salir" << endl << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1){

            system("clear");
            cout << "Prestamos inicializados en el programa" << endl << endl;
            cout << "NumeroPrestamo\tNombre\tLibro\t\tFechaPrestamo\t\tFechaDevolucion" << endl << endl;
            for (i = 0; i < N_INICIALIZADOS; i++){
                cout << inicializados[i].NumeroPrestamo << "\t\t" << inicializados[i].NombreSocio << "\t" << inicializados[i].NombreLibro << "\t";
                cout << inicializados[i].FechaPrestamo.Dia << "/" << inicializados[i].FechaPrestamo.Mes << "/" << inicializados[i].FechaPrestamo.Anio << "\t\t";
                cout << inicializados[i].FechaDevolucion.Dia << "/" << inicializados[i].FechaDevolucion.Mes << "/" << inicializados[i].FechaDevolucion.Anio << endl;
            }

        }else if(opcion == 2){

            for (i = 0; i < N_CAPTURADOS; i++){

                system("clear");
                capturados[i].NumeroPrestamo = i + 1;
                cout << "Prestamo " << capturados[i].NumeroPrestamo << endl << endl;
                cout << "Nombre del socio: ";
                cin >> capturados[i].NombreSocio;
                cout << "Nombre del libro: ";
                cin >> capturados[i].NombreLibro;

                cout << endl << "Fecha de prestamo" << endl;
                do{
                    cout << "  Dia (1 a 31): ";
                    cin >> capturados[i].FechaPrestamo.Dia;
                    if(capturados[i].FechaPrestamo.Dia < 1 || capturados[i].FechaPrestamo.Dia > 31){
                        cout << "  ERROR! Dia no valido" << endl;
                    }
                }while(capturados[i].FechaPrestamo.Dia < 1 || capturados[i].FechaPrestamo.Dia > 31);

                do{
                    cout << "  Mes (1 a 12): ";
                    cin >> capturados[i].FechaPrestamo.Mes;
                    if(capturados[i].FechaPrestamo.Mes < 1 || capturados[i].FechaPrestamo.Mes > 12){
                        cout << "  ERROR! Mes no valido" << endl;
                    }
                }while(capturados[i].FechaPrestamo.Mes < 1 || capturados[i].FechaPrestamo.Mes > 12);

                do{
                    cout << "  Anio (4 digitos): ";
                    cin >> capturados[i].FechaPrestamo.Anio;
                    if(capturados[i].FechaPrestamo.Anio < 1000 || capturados[i].FechaPrestamo.Anio > 9999){
                        cout << "  ERROR! El anio debe tener 4 digitos" << endl;
                    }
                }while(capturados[i].FechaPrestamo.Anio < 1000 || capturados[i].FechaPrestamo.Anio > 9999);

                prestamo = fechaComoNumero(capturados[i].FechaPrestamo.Dia, capturados[i].FechaPrestamo.Mes, capturados[i].FechaPrestamo.Anio);

                // Si la devolucion queda antes del prestamo, se vuelve a pedir la fecha completa
                do{
                    cout << endl << "Fecha de devolucion" << endl;
                    do{
                        cout << "  Dia (1 a 31): ";
                        cin >> capturados[i].FechaDevolucion.Dia;
                        if(capturados[i].FechaDevolucion.Dia < 1 || capturados[i].FechaDevolucion.Dia > 31){
                            cout << "  ERROR! Dia no valido" << endl;
                        }
                    }while(capturados[i].FechaDevolucion.Dia < 1 || capturados[i].FechaDevolucion.Dia > 31);

                    do{
                        cout << "  Mes (1 a 12): ";
                        cin >> capturados[i].FechaDevolucion.Mes;
                        if(capturados[i].FechaDevolucion.Mes < 1 || capturados[i].FechaDevolucion.Mes > 12){
                            cout << "  ERROR! Mes no valido" << endl;
                        }
                    }while(capturados[i].FechaDevolucion.Mes < 1 || capturados[i].FechaDevolucion.Mes > 12);

                    do{
                        cout << "  Anio (4 digitos): ";
                        cin >> capturados[i].FechaDevolucion.Anio;
                        if(capturados[i].FechaDevolucion.Anio < 1000 || capturados[i].FechaDevolucion.Anio > 9999){
                            cout << "  ERROR! El anio debe tener 4 digitos" << endl;
                        }
                    }while(capturados[i].FechaDevolucion.Anio < 1000 || capturados[i].FechaDevolucion.Anio > 9999);

                    devolucion = fechaComoNumero(capturados[i].FechaDevolucion.Dia, capturados[i].FechaDevolucion.Mes, capturados[i].FechaDevolucion.Anio);

                    if(devolucion < prestamo){
                        cout << "  ERROR! La devolucion no puede ser antes del prestamo" << endl;
                    }
                }while(devolucion < prestamo);
            }

            system("clear");
            cout << "Prestamos capturados por el usuario" << endl << endl;
            cout << "NumeroPrestamo\tNombre\tLibro\t\tFechaPrestamo\t\tFechaDevolucion" << endl << endl;
            for (i = 0; i < N_CAPTURADOS; i++){
                cout << capturados[i].NumeroPrestamo << "\t\t" << capturados[i].NombreSocio << "\t" << capturados[i].NombreLibro << "\t";
                cout << capturados[i].FechaPrestamo.Dia << "/" << capturados[i].FechaPrestamo.Mes << "/" << capturados[i].FechaPrestamo.Anio << "\t\t";
                cout << capturados[i].FechaDevolucion.Dia << "/" << capturados[i].FechaDevolucion.Mes << "/" << capturados[i].FechaDevolucion.Anio << endl;
            }

        }else if(opcion != 3){
            cout << "ERROR! Opcion no valida" << endl;
        }

        if(opcion != 3){
            cout << endl << "Presiona Enter para volver al menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }

    }while(opcion != 3);

    return 0;
}

int fechaComoNumero(int dia, int mes, int anio){
    return anio * 10000 + mes * 100 + dia;
}
