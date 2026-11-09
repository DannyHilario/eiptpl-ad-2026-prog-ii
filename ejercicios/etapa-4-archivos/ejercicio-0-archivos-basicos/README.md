# Ejercicio 0 — Archivos básicos (empieza aquí)

*Etapa IV — Archivos · Temas: 4.8–4.10 · Programas: [`escribir`](etapa-4-ejercicio-0-escribir.cpp), [`agregar`](etapa-4-ejercicio-0-agregar.cpp), [`leer`](etapa-4-ejercicio-0-leer.cpp) y [`cargar`](etapa-4-ejercicio-0-cargar.cpp) · Siguiente: [Ejercicio 1](../ejercicio-1-historico-temperaturas/README.md)*

## Para qué sirve

Antes de los ejercicios 1 a 3, que tienen menú, funciones y validaciones, aquí está lo mínimo
para trabajar con archivos: **escribir**, **agregar**, **leer** y **cargar en un arreglo de
structs**. Son cuatro programas muy cortos,
sin menú y sin validaciones, que usan el **mismo archivo**: `compras.txt`, una lista del súper
con un producto por renglón.

```
Leche 2
Pan 1
Huevo 12
```

Guarda los cuatro `.cpp` en la **misma carpeta** y compílalos ahí: así todos usan el mismo
`compras.txt`, que aparece en la carpeta donde está el `.exe`.

| Programa | Qué hace con `compras.txt` | Cómo lo abre |
|---|---|---|
| 1. Escribir | Lo **escribe desde cero** con 3 productos | `ofstream archivo("compras.txt");` |
| 2. Agregar | Le **agrega** un producto al final | `ofstream archivo("compras.txt", ios::app);` |
| 3. Leer | **Muestra** lo que tiene y cuenta los productos | `ifstream archivo("compras.txt");` |
| 4. Cargar | Lo **guarda en un arreglo de structs** para usarlo después | `ifstream archivo("compras.txt");` |

## Programa 1: escribir

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

    string producto;
    int cantidad;

    ofstream archivo("compras.txt");   // abre (o crea) compras.txt para escribir

    for(int i = 1; i <= 3; i++){
        cout << "Producto " << i << ": ";
        cin >> producto;
        cout << "Cantidad: ";
        cin >> cantidad;

        archivo << producto << " " << cantidad << endl;   // se escribe igual que con cout
    }

    archivo.close();   // cierra el archivo: ahora si queda guardado

    cout << "Listo, abre compras.txt para ver la lista" << endl;

    return 0;
}
```

Solo hay **tres cosas nuevas**:

1. `#include <fstream>`: la biblioteca de los archivos (*file stream*).
2. `ofstream archivo("compras.txt");`: crea una variable `archivo` conectada al archivo
   `compras.txt`. `ofstream` es para **escribir** (*output*). Si el archivo no existe, lo crea.
3. `archivo << ...`: escribe en el archivo **igual que `cout <<`** escribe en la pantalla. El
   espacio entre producto y cantidad y el `endl` al final dejan un producto por renglón.

Al terminar, `archivo.close();` cierra el archivo.

Una ejecución:

```
Producto 1: Leche
Cantidad: 2
Producto 2: Pan
Cantidad: 1
Producto 3: Huevo
Cantidad: 12
Listo, abre compras.txt para ver la lista
```

Abre `compras.txt` con el Bloc de notas:

```
Leche 2
Pan 1
Huevo 12
```

## Programa 2: agregar

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

    string producto;
    int cantidad;

    cout << "Producto: ";
    cin >> producto;
    cout << "Cantidad: ";
    cin >> cantidad;

    ofstream archivo("compras.txt", ios::app);   // app = append = agregar al final

    archivo << producto << " " << cantidad << endl;

    archivo.close();

    cout << "Agregado al final de compras.txt" << endl;

    return 0;
}
```

Es casi igual al programa 1. La **única diferencia importante** está en cómo se abre el archivo:

```cpp
ofstream archivo("compras.txt");             // programa 1: borra lo que tenía y empieza de cero
ofstream archivo("compras.txt", ios::app);   // programa 2: lo conserva y escribe al final
```

Después de agregar `Cafe 1`, `compras.txt` queda:

```
Leche 2
Pan 1
Huevo 12
Cafe 1
```

## Programa 3: leer

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

    string producto;
    int cantidad;
    int productos = 0;

    ifstream archivo("compras.txt");   // abre compras.txt para leer

    // Cada vuelta lee un renglon: primero el producto y despues la cantidad.
    // Cuando ya no hay nada que leer, la condicion es falsa y el while termina
    while(archivo >> producto >> cantidad){
        cout << producto << ": " << cantidad << endl;
        productos++;
    }

    archivo.close();

    cout << "Productos en la lista: " << productos << endl;

    return 0;
}
```

- `ifstream` es para **leer** (*input*).
- `archivo >> producto >> cantidad` lee del archivo **igual que `cin >>`** lee del teclado:
  toma el siguiente producto y la siguiente cantidad.
- Esa lectura va **dentro de la condición del `while`**: mientras haya un renglón que leer, el
  `while` da otra vuelta; cuando el archivo se acaba, se detiene solo. No hace falta saber
  cuántos renglones tiene.

Con el archivo de arriba:

```
Leche: 2
Pan: 1
Huevo: 12
Cafe: 1
Productos en la lista: 4
```

## Programa 4: cargar en un arreglo de structs

El programa 3 muestra cada renglón y lo olvida. Casi siempre se necesita lo contrario: **guardar
todo en un arreglo de structs** para después buscar, sumar, ordenar o cambiar datos. A eso se le
llama **cargar** el archivo.

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Producto{
    string nombre;
    int cantidad;
};

const int MAX = 15;   // cuantos productos caben en el arreglo

int main(){

    Producto lista[MAX];
    int n = 0;   // cuantos productos se han cargado
    int total = 0;

    ifstream archivo("compras.txt");

    // Cada vuelta lee un renglon y lo guarda en la casilla n del arreglo.
    // Si la lectura sale bien, n++ avanza a la siguiente casilla.
    // Se detiene cuando el archivo se acaba o cuando el arreglo se llena
    while(n < MAX && archivo >> lista[n].nombre >> lista[n].cantidad){
        n++;
    }

    archivo.close();

    // El archivo ya esta cerrado: los datos ahora viven en el arreglo
    cout << "Se cargaron " << n << " productos" << endl;

    for(int i = 0; i < n; i++){
        cout << i + 1 << ". " << lista[i].nombre << ": " << lista[i].cantidad << endl;
        total = total + lista[i].cantidad;
    }

    cout << "Total de piezas: " << total << endl;

    return 0;
}
```

Es el mismo `while` del programa 3, con dos cambios:

- Ahora cada renglón se lee **directo a una casilla del arreglo**: `lista[n].nombre` y
  `lista[n].cantidad`. Dentro del `while` solo queda `n++`, que pasa a la siguiente casilla.
- La condición empieza con `n < MAX &&`: si el arreglo ya se llenó, el `while` se detiene **antes
  de leer** y no escribe fuera del arreglo. El orden importa: primero se revisa que haya lugar y
  después se lee.

Al terminar, `n` dice **cuántos productos se cargaron**. Es el mismo contador `n` de la
[sesión 3.5](../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md): el arreglo
tiene capacidad para `MAX`, pero solo las casillas `0` a `n - 1` tienen datos. Por eso el `for`
va hasta `n` y no hasta `MAX`.

Con los 5 productos de los pasos de abajo (`Leche 2`, `Pan 1`, `Huevo 12`, `Cafe 1`, `Azucar 3`):

```
Se cargaron 5 productos
1. Leche: 2
2. Pan: 1
3. Huevo: 12
4. Cafe: 1
5. Azucar: 3
Total de piezas: 19
```

### ¿Y un archivo aparte con cuántos registros hay?

Otra forma conocida es guardar dos archivos: uno con el número de registros (por ejemplo, `5`) y
otro con los datos; primero se lee el número y después un `for` de ese tamaño. Funciona, pero
**no hace falta**: el `while` cuenta solo mientras lee. Y tiene un riesgo: si los dos archivos no
coinciden (alguien borró un renglón a mano, o el programa se cerró después de escribir el dato
pero antes de actualizar el contador), el `for` lee renglones que no existen o se salta los
últimos. Con un solo archivo y el `while`, el número **siempre** es el real. Así se hace en los
ejercicios 1 a 3 y en el PIA.

## Pruébalo tú

Córrelos en este orden y, después de cada paso, abre `compras.txt` con el Bloc de notas:

| # | Haz esto | Qué debe pasar |
|---|---|---|
| 1 | Corre **leer** antes que nada (todavía no existe `compras.txt`) | `Productos en la lista: 0`: no hay archivo, así que no lee nada |
| 2 | Corre **escribir** con `Leche 2`, `Pan 1`, `Huevo 12` | Aparece `compras.txt` con 3 renglones |
| 3 | Corre **leer** | Muestra los 3 productos: `Productos en la lista: 3` |
| 4 | Corre **agregar** con `Cafe 1` | El archivo tiene 4 renglones: `Cafe 1` quedó al final |
| 5 | Corre **agregar** otra vez con `Azucar 3` | 5 renglones: el archivo **crece** |
| 6 | Corre **cargar** | `Se cargaron 5 productos` y `Total de piezas: 19` |
| 7 | Corre **escribir** otra vez con `Arroz 1`, `Frijol 2`, `Sal 1` | Solo quedan esos 3: el modo normal **borró** los 5 anteriores |
| 8 | Corre **leer** y después **cargar** | Los dos dicen 3 productos; **cargar** da `Total de piezas: 4` |

Los pasos 5 y 7 son la diferencia entre `ios::app` y el modo normal: uno **agrega** y el otro
**empieza de cero**.

## Casos de prueba

Probados el 5 nov 2026 en macOS, compilando con `g++ -std=c++98 -Wall -Wextra` y con
`-std=c++17` (sin advertencias, mismos resultados en ambos), con los datos de la tabla de
*Pruébalo tú*. Los 8 pasos dan lo que dice la columna *Qué debe pasar*. Se supone que el
producto es una sola palabra y la cantidad un número entero.

Además, **cargar** sin `compras.txt` da `Se cargaron 0 productos` y, con un archivo de 17
renglones, carga solo los primeros 15 (`MAX`) sin salirse del arreglo.

## Lo que estos programas no hacen (a propósito)

Son lo mínimo para entender la idea. Los ejercicios 1 a 3 agregan lo que aquí falta:

- **Revisar si el archivo se pudo abrir** (`if(!archivo)`): aquí, si falla, simplemente no
  pasa nada ([ejercicio 1](../ejercicio-1-historico-temperaturas/README.md)).
- **Validar los datos** que escribe el usuario.
- **Avisar si el archivo tiene más renglones de los que caben** en el arreglo (aquí los que
  sobran simplemente no se cargan).
- **Cambiar un renglón** que ya está en el archivo
  ([ejercicio 3](../ejercicio-3-correccion-historico/README.md)).

Para la explicación completa: [4.8 Ficheros en C++](../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md)
[4.9 Modos de apertura](../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md)
y [4.10 Actualización](../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md).

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 5 nov 2026 | Programa 4, **cargar** el archivo en un arreglo de structs con el contador `n`, y por qué no hace falta un archivo contador aparte. | Daniel pidió el caso de leer un archivo de 5 registros para llenar una estructura. |
| 5 nov 2026 | Primera versión: tres programas planos (escribir, agregar y leer) sobre el mismo `compras.txt`. | Un alumno pidió una explicación más simple de archivos antes de los ejercicios con menú y validaciones. |
