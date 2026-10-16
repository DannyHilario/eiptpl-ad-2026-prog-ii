#include <iostream>
#include <string>
#include <cstdlib>
#include <limits> // Linea macOS
using namespace std;

const int N = 3;

struct Articulo{
    string Nombre;
    string Marca;
    double PrecioUnitario;
    int Unidades;
};

double calcularImporte(double precio, int unidades);

int main(){

    Articulo articulos[N];
    Articulo masCaro = {"", "", 0.0, 0}; // inicializacion con llaves
    double total = 0.0;

    int i;

    for (i = 0; i < N; i++){

        system("clear");
        cout << "Articulo " << i + 1 << endl << endl << endl;
        cout << "Nombre: ";
        cin >> articulos[i].Nombre;
        cout << "Marca: ";
        cin >> articulos[i].Marca;

        do{
            system("clear");
            cout << "Articulo " << i + 1 << ": " << articulos[i].Nombre << " " << articulos[i].Marca << endl << endl;
            cout << "Precio Unitario: $";
            cin >> articulos[i].PrecioUnitario;

            if(articulos[i].PrecioUnitario <= 0){
                cout << "ERROR! El precio debe ser mayor que 0" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
                cin.get(); // Linea macOS
            }
        }while(articulos[i].PrecioUnitario <= 0);

        do{
            system("clear");
            cout << "Articulo " << i + 1 << ": " << articulos[i].Nombre << " " << articulos[i].Marca << endl << endl;
            cout << "Unidades: ";
            cin >> articulos[i].Unidades;

            if(articulos[i].Unidades <= 0){
                cout << "ERROR! Las unidades deben ser mayores que 0" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
                cin.get(); // Linea macOS
            }
        }while(articulos[i].Unidades <= 0);

    }

    system("clear");
    cout << "Datos de los articulos" << endl << endl;
    cout << "Nombre\tMarca\tPrecioUnitario\tUnidades\tImporte" << endl << endl;

    for(i = 0; i < N; i++)
    {
        double importe = calcularImporte(articulos[i].PrecioUnitario, articulos[i].Unidades);
        total = total + importe;

        if (articulos[i].PrecioUnitario > masCaro.PrecioUnitario){
            masCaro = articulos[i]; // copia el struct completo
        }

        cout << articulos[i].Nombre << "\t" << articulos[i].Marca << "\t"  << articulos[i].PrecioUnitario << "\t\t"  << articulos[i].Unidades << "\t\t" << importe << endl;
    }

    cout << endl << "Valor total del inventario: $" << total << endl;
    cout << "Articulo mas caro: " << masCaro.Nombre << " (" << masCaro.Marca << ") a $" << masCaro.PrecioUnitario << endl;

    return 0;
}

double calcularImporte(double precio, int unidades){
    return precio * unidades;
}