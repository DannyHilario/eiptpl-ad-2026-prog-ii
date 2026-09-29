# Retroalimentación — Evidencia 1: Control de flujo y ciclos

**Alumno:** 07 — Ibarra Martinez Victor Miguel

## Programa 1 — Monitoreo de ruido industrial

**Compilación:** Compila sin errores. Usa conio.h, propia de Windows; se compiló con un sustituto equivalente sin modificar el código.

**Pruebas realizadas:**

| Caso | Entrada | Resultado esperado | Resultado obtenido | ¿Correcto? |
|---|---|---|---|---|
| Validación de cantidad | Cantidad -2 y 0 (inválidas), luego 4 | Vuelve a pedir la cantidad | Vuelve a pedirla | ✅ |
| Clasificación (umbral 85 dB) | Niveles 70, 85, 85.5, 100 | Dentro 2, exceden 2 | Dentro 2, exceden 2 | ✅ |

**Observaciones:**

- Validación con do-while, clasificación correcta (85 exacto está dentro del límite) y reporte completo.
- Nombres de variables claros.

**Recomendaciones:**

- Se incluye conio.h pero no se usa ninguna de sus funciones; puedes quitarla.
- Revisa la ortografía de los mensajes ("limita" en lugar de "límite").

**Tu código, con comentarios de revisión:**

Las líneas que empiezan con `// [Revisión, línea N]` son comentarios del profesor, colocados justo arriba de la línea N de tu archivo original. Todo lo demás es tu código tal como lo entregaste.

```cpp
//Ibarra Martinez Victor Miguel

#include <iostream>    
// [Revisión, línea 4] conio.h no se usa en este programa.
#include <conio.h>

using namespace std;

int main() {

    int puntos;
    int fueralimite = 0;
    int dentrolimite = 0;
    double ruido;


    do
    {
   
    

    cout << "Â¿Cuantos puntos de medicion se van a revisar? "<< endl<<endl;
    cin >> puntos;



        if( puntos <= 0 ){

            system("cls");
            cout << "Error, debes introducir un numero positivo";

            system("pause");


        }

    } while (puntos <= 0);
    

    for(int i = 1;i <= puntos;i++ ){

        system("cls");

        cout << "Punto en revision "<< i << endl <<endl;

        cout << " Ingresa el nivel de ruido del punto "<< i << " en db "<<endl<<endl;
        cin >> ruido;

        // [Revisión, línea 48] Correcto: 85 exacto está dentro del límite.
        if(ruido > 85){
            
            system("cls");

            cout << "El ruido excede el limite "<<endl<<endl;

            fueralimite++;

            system("pause");

        }else{

            system("cls");

            cout << "No exceden el limite "<< endl << endl;

            dentrolimite++;

            system("pause");

        }


    }
    

    //Reporte final


    system("cls");

    cout << "****REPORTE FINAL****"<<endl<<endl;
    cout << "Total de puntos que se midieron "<< puntos <<endl<<endl;
    cout << "Puntos dentro del limita "<< dentrolimite << endl <<endl;
    cout << "Puntos fuera del limite "<< fueralimite << endl <<endl;

    system("pause");
}
```

## Programa 2 — Renta de bicicletas

**Compilación:** No se entregó.

**Observaciones:**

- No se entregó el archivo de este programa.

## Comentario general

El Programa 1 está bien resuelto. Faltó entregar el Programa 2, que valía la mitad de la evidencia.
