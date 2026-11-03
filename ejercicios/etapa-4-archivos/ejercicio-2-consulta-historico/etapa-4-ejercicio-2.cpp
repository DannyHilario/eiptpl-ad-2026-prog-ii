#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits> // Linea macOS
using namespace std;

/*
    Historico de temperaturas, segunda parte: ademas de AGREGAR temperaturas
    (como en el ejercicio 1), el programa LEE el archivo para mostrar el
    historico completo y las estadisticas de un mes. Cada renglon del archivo
    es un registro:

    dia mes anio temperatura

    La carpeta datos/ debe existir: ofstream crea el archivo, pero no la carpeta.
*/

const string ARCHIVO = "datos/historico-temperaturas.txt";
const double TEMP_MIN = -10;
const double TEMP_MAX = 50;

// Resultados de prepararArchivo
const int YA_EXISTE = 0;
const int CREADO = 1;
const int NO_SE_PUDO_CREAR = -1;

struct Fecha{
    int Dia;
    int Mes;
    int Anio;
};

int prepararArchivo(string ruta);
double calcularPromedio(double suma, int cantidad);

int main(){

    Fecha fecha;              // la que captura el usuario en la opcion 1
    double temperatura;

    Fecha fechaLeida;         // la del renglon que se acaba de leer del archivo
    double temperaturaLeida;

    ifstream entrada;         // se declaran una vez y se abren y cierran en cada opcion
    ofstream salida;

    int opcion;
    int registros;            // cuantos renglones se han leido
    int mesBuscado, anioBuscado;
    int cantidad;             // cuantos renglones son del mes buscado
    double suma;
    double maxima, minima;
    int diaMaxima, diaMinima;

    int estado = prepararArchivo(ARCHIVO);

    if(estado == NO_SE_PUDO_CREAR){
        cout << "ERROR! No se pudo crear " << ARCHIVO << " (existe la carpeta datos/?)" << endl;
        return 1;
    }

    if(estado == CREADO){
        cout << "Se creo el archivo vacio " << ARCHIVO << endl;
    }

    if(estado == YA_EXISTE){
        cout << "El archivo " << ARCHIVO << " ya existe" << endl;
    }

    cout << endl << "Presiona Enter para continuar...";
    cin.get();

    do{
        system("clear");
        cout << "HISTORICO DE TEMPERATURAS" << endl << endl;
        cout << "1. Agregar una nueva temperatura" << endl;
        cout << "2. Ver el historico completo" << endl;
        cout << "3. Estadisticas de un mes" << endl;
        cout << "4. Salir" << endl << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion){

            case 1:

                system("clear");
                cout << "Nueva temperatura" << endl << endl;

                do{
                    cout << "Dia (1 a 31): ";
                    cin >> fecha.Dia;
                    if(fecha.Dia < 1 || fecha.Dia > 31){
                        cout << "ERROR! Dia no valido" << endl;
                    }
                }while(fecha.Dia < 1 || fecha.Dia > 31);

                do{
                    cout << "Mes (1 a 12): ";
                    cin >> fecha.Mes;
                    if(fecha.Mes < 1 || fecha.Mes > 12){
                        cout << "ERROR! Mes no valido" << endl;
                    }
                }while(fecha.Mes < 1 || fecha.Mes > 12);

                do{
                    cout << "Anio (4 digitos): ";
                    cin >> fecha.Anio;
                    if(fecha.Anio < 1000 || fecha.Anio > 9999){
                        cout << "ERROR! El anio debe tener 4 digitos" << endl;
                    }
                }while(fecha.Anio < 1000 || fecha.Anio > 9999);

                do{
                    cout << "Temperatura promedio del dia (" << TEMP_MIN << " a " << TEMP_MAX << "): ";
                    cin >> temperatura;
                    if(temperatura < TEMP_MIN || temperatura > TEMP_MAX){
                        cout << "ERROR! Temperatura fuera de rango" << endl;
                    }
                }while(temperatura < TEMP_MIN || temperatura > TEMP_MAX);

                salida.clear();                         // borra la marca de error de un intento anterior
                salida.open(ARCHIVO.c_str(), ios::app); // agrega al final, no borra lo anterior

                if(!salida){
                    cout << endl << "ERROR! No se pudo abrir " << ARCHIVO << " (existe la carpeta datos/?)" << endl;
                }else{
                    salida << fecha.Dia << " " << fecha.Mes << " " << fecha.Anio << " " << temperatura << endl;
                    salida.close();
                    cout << endl << "Temperatura guardada en " << ARCHIVO << endl;
                }
                break;

            case 2:

                system("clear");
                cout << "Historico completo" << endl << endl;

                // Se abre en cada consulta: asi la lectura empieza siempre desde el
                // primer renglon e incluye lo que se agrego con la opcion 1
                entrada.clear();   // la lectura anterior termino en error (asi sale el while): se borra la marca
                entrada.open(ARCHIVO.c_str());

                if(!entrada){
                    cout << "ERROR! No se pudo abrir " << ARCHIVO << endl;
                }else{
                    cout << "#\tFecha\t\tTemperatura" << endl << endl;

                    registros = 0;

                    // Cada vuelta lee un renglon completo (los 4 campos). La condicion es
                    // verdadera mientras la lectura funciona y falsa cuando ya no hay datos
                    while(entrada >> fechaLeida.Dia >> fechaLeida.Mes >> fechaLeida.Anio >> temperaturaLeida){
                        registros++;
                        cout << registros << "\t" << fechaLeida.Dia << "/" << fechaLeida.Mes << "/" << fechaLeida.Anio << "\t" << temperaturaLeida << endl;
                    }
                    entrada.close();

                    if(registros == 0){
                        cout << "El historico esta vacio" << endl;
                    }else{
                        cout << endl << "Registros: " << registros << endl;
                    }
                }
                break;

            case 3:

                system("clear");
                cout << "Estadisticas de un mes" << endl << endl;

                do{
                    cout << "Mes (1 a 12): ";
                    cin >> mesBuscado;
                    if(mesBuscado < 1 || mesBuscado > 12){
                        cout << "ERROR! Mes no valido" << endl;
                    }
                }while(mesBuscado < 1 || mesBuscado > 12);

                do{
                    cout << "Anio (4 digitos): ";
                    cin >> anioBuscado;
                    if(anioBuscado < 1000 || anioBuscado > 9999){
                        cout << "ERROR! El anio debe tener 4 digitos" << endl;
                    }
                }while(anioBuscado < 1000 || anioBuscado > 9999);

                entrada.clear();   // la lectura anterior termino en error (asi sale el while): se borra la marca
                entrada.open(ARCHIVO.c_str());

                if(!entrada){
                    cout << "ERROR! No se pudo abrir " << ARCHIVO << endl;
                }else{
                    cantidad = 0;
                    suma = 0;
                    maxima = 0;     // se reemplazan con el primer renglon del mes;
                    minima = 0;     // se ponen en 0 solo para que no queden sin valor
                    diaMaxima = 0;
                    diaMinima = 0;

                    // Se leen TODOS los renglones, pero solo cuentan los del mes buscado
                    while(entrada >> fechaLeida.Dia >> fechaLeida.Mes >> fechaLeida.Anio >> temperaturaLeida){

                        if(fechaLeida.Mes == mesBuscado && fechaLeida.Anio == anioBuscado){
                            cantidad++;
                            suma += temperaturaLeida;

                            // El primer renglon del mes es, por ahora, la maxima y la minima
                            if(cantidad == 1){
                                maxima = temperaturaLeida;
                                diaMaxima = fechaLeida.Dia;
                                minima = temperaturaLeida;
                                diaMinima = fechaLeida.Dia;
                            }else{
                                if(temperaturaLeida > maxima){
                                    maxima = temperaturaLeida;
                                    diaMaxima = fechaLeida.Dia;
                                }
                                if(temperaturaLeida < minima){
                                    minima = temperaturaLeida;
                                    diaMinima = fechaLeida.Dia;
                                }
                            }
                        }
                    }
                    entrada.close();

                    cout << endl;
                    if(cantidad == 0){
                        cout << "No hay temperaturas registradas de " << mesBuscado << "/" << anioBuscado << endl;
                    }else{
                        cout << "Temperaturas de " << mesBuscado << "/" << anioBuscado << ": " << cantidad << endl;
                        cout << "Promedio: " << calcularPromedio(suma, cantidad) << endl;
                        cout << "Maxima: " << maxima << " (dia " << diaMaxima << ")" << endl;
                        cout << "Minima: " << minima << " (dia " << diaMinima << ")" << endl;
                    }
                }
                break;

            case 4:
                break;  // salir: no hay nada que hacer aqui; el do-while termina

            default:
                cout << "ERROR! Opcion no valida" << endl;
        }

        if(opcion != 4){
            cout << endl << "Presiona Enter para volver al menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }

    }while(opcion != 4);

    return 0;
}

// Revisa si el archivo existe antes de abrir cualquier flujo de escritura y, si no
// existe, lo crea vacio (explicada a detalle en el ejercicio 1)
int prepararArchivo(string ruta){

    ifstream prueba(ruta.c_str()); // ifstream no crea archivos: si no lo abre, no existe

    if(prueba){
        prueba.close();
        return YA_EXISTE;
    }

    ofstream nuevo(ruta.c_str()); // modo por defecto (ios::out): lo crea vacio

    if(!nuevo){
        return NO_SE_PUDO_CREAR;
    }

    nuevo.close();
    return CREADO;
}

// Funcion pura: si no hay datos regresa 0 en lugar de dividir entre 0
double calcularPromedio(double suma, int cantidad){
    if(cantidad == 0){
        return 0;
    }
    return suma / cantidad;
}
