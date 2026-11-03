#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits> // Linea macOS
using namespace std;

/*
    Historico de temperaturas. Cada vez que se agrega una temperatura se escribe
    un renglon al FINAL del archivo (modo ios::app), asi que lo que ya estaba
    guardado nunca se borra. Cada renglon es un registro con 4 campos separados
    por un espacio:

    dia mes anio temperatura

    La carpeta datos/ debe existir: ofstream crea el archivo, pero no la carpeta.
*/

const string ARCHIVO = "datos/historico-temperaturas.txt";
const double TEMP_MIN = -10;
const double TEMP_MAX = 50;

// Resultados de prepararArchivo: cada numero significa una situacion distinta
const int YA_EXISTE = 0;
const int CREADO = 1;
const int NO_SE_PUDO_CREAR = -1;

struct Fecha{
    int Dia;
    int Mes;
    int Anio;
};

int prepararArchivo(string ruta);

int main(){

    Fecha fecha;
    double temperatura;
    int opcion;
    ofstream salida;  // se declara una vez y se abre y cierra en cada temperatura

    // Antes del menu se revisa el archivo: la funcion no imprime nada, solo
    // regresa un numero, y main decide que mensaje mostrar
    int estado = prepararArchivo(ARCHIVO);

    if(estado == NO_SE_PUDO_CREAR){
        cout << "ERROR! No se pudo crear " << ARCHIVO << " (existe la carpeta datos/?)" << endl;
        return 1; // un return distinto de 0 indica que el programa termino con error
    }

    if(estado == CREADO){
        cout << "Se creo el archivo vacio " << ARCHIVO << endl;
    }

    if(estado == YA_EXISTE){
        cout << "El archivo " << ARCHIVO << " ya existe" << endl;
    }

    // Todavia no se ha usado cin >>, asi que el bufer esta vacio y basta con cin.get()
    cout << endl << "Presiona Enter para continuar...";
    cin.get();

    do{
        system("clear");
        cout << "HISTORICO DE TEMPERATURAS" << endl << endl;
        cout << "1. Agregar una nueva temperatura" << endl;
        cout << "2. Salir" << endl << endl;
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

                // clear() borra la marca de error que pudo dejar un intento anterior
                // (por ejemplo, si faltaba la carpeta); si no se borra, el flujo se
                // queda marcado aunque esta vez el archivo si se abra
                salida.clear();

                // ios::app: se escribe al final y lo que ya tenia el archivo se conserva.
                // Sin ios::app (modo normal), cada temperatura nueva borraria todo el historico
                salida.open(ARCHIVO.c_str(), ios::app);

                if(!salida){
                    cout << endl << "ERROR! No se pudo abrir " << ARCHIVO << " (existe la carpeta datos/?)" << endl;
                }else{
                    // Los espacios separan los campos y endl termina el registro: asi se
                    // podra leer despues con entrada >> dia >> mes >> anio >> temperatura
                    salida << fecha.Dia << " " << fecha.Mes << " " << fecha.Anio << " " << temperatura << endl;
                    salida.close();
                    cout << endl << "Temperatura guardada en " << ARCHIVO << endl;
                }
                break;

            case 2:
                break;  // salir: no hay nada que hacer aqui; el do-while termina

            default:
                cout << "ERROR! Opcion no valida" << endl;
        }

        if(opcion != 2){
            cout << endl << "Presiona Enter para volver al menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
            cin.get(); // Linea macOS
        }

    }while(opcion != 2);

    return 0;
}

/*
    Revisa si el archivo existe ANTES de abrir cualquier flujo de escritura y,
    si no existe, lo crea vacio. No usa cin ni cout: regresa un codigo
    (YA_EXISTE, CREADO o NO_SE_PUDO_CREAR) y main decide que mostrar.

    El orden importa: si se abriera primero un ofstream normal, el archivo se
    vaciaria y se perderia el historico. Por eso primero se "pregunta" con un
    ifstream, que nunca crea ni borra nada.
*/
int prepararArchivo(string ruta){

    // ifstream solo abre archivos que ya existen: si no lo pudo abrir, no existe
    ifstream prueba(ruta.c_str());

    // Un flujo dentro de un if vale verdadero si se abrio y falso si no
    if(prueba){
        prueba.close();
        return YA_EXISTE; // return termina la funcion aqui: lo de abajo ya no se ejecuta
    }

    // Si se llego aqui, el archivo no existe y no hay nada que borrar.
    // ofstream en su modo normal (ios::out) lo crea vacio
    ofstream nuevo(ruta.c_str());

    if(!nuevo){
        return NO_SE_PUDO_CREAR; // normalmente, porque no existe la carpeta datos/
    }

    nuevo.close();
    return CREADO;
}
