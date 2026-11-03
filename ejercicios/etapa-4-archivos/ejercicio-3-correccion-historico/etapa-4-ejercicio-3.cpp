#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits> // Linea macOS
using namespace std;

/*
    Historico de temperaturas, tercera parte: ademas de agregar y ver, el
    programa permite CORREGIR una temperatura que se capturo mal. Cada renglon
    del archivo es un registro:

    dia mes anio temperatura

    Un renglon no se puede cambiar "en su lugar" dentro del archivo (tema 4.10),
    asi que la correccion sigue tres pasos:

    1) CARGAR: se lee el archivo completo a un arreglo de structs
    2) MODIFICAR: se cambia la temperatura en el arreglo
    3) REESCRIBIR: se vacia el archivo y se escribe otra vez con todo el arreglo

    La carpeta datos/ debe existir: ofstream crea el archivo, pero no la carpeta.
*/

const string ARCHIVO = "datos/historico-temperaturas.txt";
const double TEMP_MIN = -10;
const double TEMP_MAX = 50;
const int MAX_REGISTROS = 100;  // capacidad del arreglo para la correccion

// Resultados de prepararArchivo
const int YA_EXISTE = 0;
const int CREADO = 1;
const int NO_SE_PUDO_CREAR = -1;

struct Fecha{
    int Dia;
    int Mes;
    int Anio;
};

// Un renglon del archivo, completo
struct Registro{
    Fecha FechaRegistro;
    double Temperatura;
};

int prepararArchivo(string ruta);

int main(){

    Registro historico[MAX_REGISTROS];  // solo se llena en la opcion 3
    int n;                              // cuantos registros hay en el arreglo
    int sobrantes;                      // renglones que no cupieron en el arreglo

    Fecha fecha;              // la que captura el usuario en la opcion 1
    double temperatura;

    Fecha fechaLeida;         // la del renglon que se acaba de leer del archivo
    double temperaturaLeida;

    ifstream entrada;         // se declaran una vez y se abren y cierran en cada opcion
    ofstream salida;

    int opcion;
    int registros;
    int numero;               // el # que elige el usuario (empieza en 1)
    int posicion;             // la posicion en el arreglo (empieza en 0)
    int i;

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
        cout << "3. Corregir una temperatura" << endl;
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

                // Agregar NO necesita cargar el archivo: basta con escribir al final
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

                entrada.clear();   // la lectura anterior termino en error (asi sale el while): se borra la marca
                entrada.open(ARCHIVO.c_str());

                if(!entrada){
                    cout << "ERROR! No se pudo abrir " << ARCHIVO << endl;
                }else{
                    cout << "#\tFecha\t\tTemperatura" << endl << endl;

                    registros = 0;
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
                cout << "Corregir una temperatura" << endl << endl;

                // 1) CARGAR: del archivo al arreglo
                entrada.clear();   // la lectura anterior termino en error (asi sale el while): se borra la marca
                entrada.open(ARCHIVO.c_str());

                if(!entrada){
                    cout << "ERROR! No se pudo abrir " << ARCHIVO << endl;
                }else{
                    n = 0;

                    // n < MAX_REGISTROS va PRIMERO: si el arreglo ya esta lleno, el &&
                    // ya no evalua la lectura y no se escribe en historico[MAX_REGISTROS]
                    while(n < MAX_REGISTROS && entrada >> historico[n].FechaRegistro.Dia >> historico[n].FechaRegistro.Mes >> historico[n].FechaRegistro.Anio >> historico[n].Temperatura){
                        n++;
                    }

                    // Si el while anterior se detuvo porque el arreglo se lleno, todavia
                    // quedan renglones en el archivo y este while los cuenta. Si se detuvo
                    // porque el archivo se acabo, la lectura ya fallo y este while no da
                    // ni una vuelta
                    sobrantes = 0;
                    while(entrada >> fechaLeida.Dia >> fechaLeida.Mes >> fechaLeida.Anio >> temperaturaLeida){
                        sobrantes++;
                    }
                    entrada.close();

                    if(sobrantes > 0){
                        // Reescribir solo con lo del arreglo BORRARIA esos renglones
                        cout << "ERROR! El historico tiene " << n + sobrantes << " registros y solo caben " << MAX_REGISTROS << endl;
                        cout << "No se corrige nada para no perder datos" << endl;
                    }else if(n == 0){
                        cout << "El historico esta vacio: no hay nada que corregir" << endl;
                    }else{
                        cout << "#\tFecha\t\tTemperatura" << endl << endl;
                        for(i = 0; i < n; i++){
                            cout << i + 1 << "\t" << historico[i].FechaRegistro.Dia << "/" << historico[i].FechaRegistro.Mes << "/" << historico[i].FechaRegistro.Anio << "\t" << historico[i].Temperatura << endl;
                        }
                        cout << endl;

                        do{
                            cout << "# del registro a corregir (1 a " << n << "): ";
                            cin >> numero;
                            if(numero < 1 || numero > n){
                                cout << "ERROR! Ese registro no existe" << endl;
                            }
                        }while(numero < 1 || numero > n);

                        // La tabla numera desde 1 y el arreglo desde 0
                        posicion = numero - 1;

                        // 2) MODIFICAR: el cambio se hace en el arreglo, no en el archivo
                        cout << endl << "Fecha: " << historico[posicion].FechaRegistro.Dia << "/" << historico[posicion].FechaRegistro.Mes << "/" << historico[posicion].FechaRegistro.Anio << endl;
                        cout << "Temperatura actual: " << historico[posicion].Temperatura << endl;

                        do{
                            cout << "Temperatura correcta (" << TEMP_MIN << " a " << TEMP_MAX << "): ";
                            cin >> historico[posicion].Temperatura;
                            if(historico[posicion].Temperatura < TEMP_MIN || historico[posicion].Temperatura > TEMP_MAX){
                                cout << "ERROR! Temperatura fuera de rango" << endl;
                            }
                        }while(historico[posicion].Temperatura < TEMP_MIN || historico[posicion].Temperatura > TEMP_MAX);

                        // 3) REESCRIBIR: modo normal (ios::out), que VACIA el archivo; con
                        // ios::app el historico quedaria repetido (el viejo y despues el nuevo)
                        salida.clear();
                        salida.open(ARCHIVO.c_str());

                        if(!salida){
                            cout << endl << "ERROR! No se pudo guardar " << ARCHIVO << endl;
                        }else{
                            for(i = 0; i < n; i++){
                                salida << historico[i].FechaRegistro.Dia << " " << historico[i].FechaRegistro.Mes << " " << historico[i].FechaRegistro.Anio << " " << historico[i].Temperatura << endl;
                            }
                            salida.close();
                            cout << endl << "Temperatura corregida. Se reescribieron " << n << " registros en " << ARCHIVO << endl;
                        }
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
