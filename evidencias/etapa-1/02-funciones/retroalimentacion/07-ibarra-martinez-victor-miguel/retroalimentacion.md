# Retroalimentación — Evidencia 1.1: Laboratorio de Programas (Funciones)

**Alumno:** 07 — Ibarra Martinez Victor Miguel

## Programa 1 — Facturación con descuento por volumen e IVA

**Compilación:** No se entregó.

**Observaciones:**

- No se entregó el archivo de este programa.

## Programa 2 — Servicio de mensajería con kilos incluidos

**Compilación:** Tal como se entregó, no compila: las líneas 1 ("Evidencia Programa") y 3 (tu nombre) son texto que no está marcado como comentario; bastaba con poner `//` al inicio de cada una. Con esas dos líneas comentadas compila sin errores, y las pruebas de abajo se hicieron así. Usa conio.h (propia de Windows), pero no usa ninguna de sus funciones.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Caso 1 del enunciado | 80 kg | Excedente 0, subtotal 800.00, IVA 128.00, total 928.00 | Valores correctos, sin decimales (800, 128, 928) | ✅ |
| Caso 2 del enunciado | 150 kg | Excedente 50, subtotal 1400.00, IVA 224.00, total 1624.00 | Valores correctos, sin decimales | ✅ |
| Límite: exactamente 100 kg | 100 kg | Excedente 0, total 928.00 | Correcto | ✅ |
| Un kilo excedente | 101 kg | Excedente 1, subtotal 812.00, total 941.92 | Idéntico al esperado | ✅ |
| Datos inválidos | Kilos -1 | Vuelve a pedir el dato (0 sí es válido) | Lo vuelve a pedir | ✅ |

**Observaciones:**

- Los kilos excedentes se deducen en su propia función y nunca se le piden al usuario, como pedía el enunciado.
- Funciones puras (sin cin ni cout), constantes con nombre y validación correctas.
- Los montos se muestran sin formato de dos decimales.

**Recomendaciones:**

- Usa fixed y setprecision(2) de iomanip para los montos.
- conio.h no se usa; puedes quitarla.
- Recuerda que el encabezado con tu nombre debe ir como comentario (// o /* */).

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
// [Revisión, línea 1] Esta línea no es comentario y el compilador la lee como código; debe empezar con //.
Evidencia Programa 

// [Revisión, línea 3] Igual que la línea 1: debe empezar con //.
Ibarra Martinez Victor Miguel [matrícula omitida]





//Victor Miguel Ibarra Martinez
//Evidencia

#include <iostream>
#include <conio.h>

using namespace std;

//Constantes

const int KILOS_INCLUIDOS = 100;
const double COSTO_PLAN = 800.00;
const double TARIFA_EXCEDENTE = 12.00;
const double IVA = 0.16;



//Prototipos

// [Revisión, línea 28] Bien: prototipos antes de main.
int calcularKilosExcedente(int kilos_env);
double calcularSubtotal(int kilos_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);

int main() {

    int kilos_env;
    int kilos_exc;
    
    double subtotal;
    double iva;
    double total;


    do
    {
        
    


    cout <<"****BIENVENIDO AL SERVICIO DE MENSAJERIA****"<<endl<<endl;
    cout << "Cuantos Kilos se enviaron este mes?"<<endl<<endl;
    cin >>  kilos_env;
    if(kilos_env < 0){
	
    
        
        system("cls");
        
        cout << "Debe ingresar un valor positivo, gracias"<<endl<<endl;


    }    
    }while (kilos_env < 0 );


    system("cls");
    cout << "A continuacion veras el reporte mensual :)"<<endl<<endl;
    system("pause");



    
    kilos_exc = calcularKilosExcedente(kilos_env);
    subtotal = calcularSubtotal(kilos_exc);
    iva = calcularIVA(subtotal);
    total = calcularTotal(subtotal, iva);



    cout << "****Reporte Mensual****"<<endl<<endl;

    cout << "1. Kilos excedentes del mes: " << kilos_exc << endl<<endl;
    // [Revisión, línea 82] Detalle: sin fixed y setprecision(2) los montos salen sin decimales.
    cout << "2. Subtotal: "<< subtotal <<endl<<endl;
    cout << "3. iva: "<< iva << endl <<endl;
    cout << "4. total a pagar: "<< total << endl<<endl;









    system("pause");

    return 0;

}

//Calcular kilos excedentes
// [Revisión, línea 101] Bien: los kilos excedentes se deducen aquí y no se le piden al usuario.
int calcularKilosExcedente(int kilos_env)
{
    if(kilos_env > KILOS_INCLUIDOS)

    return kilos_env - KILOS_INCLUIDOS;

    else
        return 0;
    
}

double calcularSubtotal(int kilos_excedentes)
{
    double cargo_excedente;

    cargo_excedente = kilos_excedentes * TARIFA_EXCEDENTE;
    
    return COSTO_PLAN + cargo_excedente;

}

double calcularIVA(double subtotal)
{
    return subtotal * IVA;
}

double calcularTotal(double subtotal, double iva)
{
    return subtotal + iva;
}
```

## Comentario general

El Programa 1 no se entregó. El Programa 2 no compila tal como se entregó por el encabezado sin comentar; con esas dos líneas comentadas, su lógica es correcta.
