# Repaso: estructuras de control y ciclos

*Siguiente: [Laboratorio de repaso](02-laboratorio-repaso.md)*

Repaso rápido de lo visto en Programación I, antes de entrar a Funciones. Todos los
ejemplos de este archivo compilan y corren tal cual con `g++ -std=c++17 -Wall`
(ver [COMPILACION.md](../../COMPILACION.md)).

## `if`

Ejecuta un bloque de código **solo si** una condición es verdadera. Si la condición
es falsa, el bloque simplemente se salta y el programa sigue después de él.

```cpp
#include <iostream>
using namespace std;

int main() {
    int edad;
    cout << "Edad: ";
    cin >> edad;

    if (edad >= 18) {
        cout << "Eres mayor de edad" << endl;
    }

    return 0;
}
```

**Ejemplo de ejecución (edad = 15):**
```
Edad: 15
```
(no imprime nada más, porque la condición fue falsa)

## `if`/`else`

Agrega un bloque alternativo que se ejecuta **cuando la condición es falsa**. Entre
`if` y `else` siempre se ejecuta exactamente uno de los dos bloques, nunca ambos y
nunca ninguno.

```cpp
#include <iostream>
using namespace std;

int main() {
    int edad;
    cout << "Edad: ";
    cin >> edad;

    if (edad >= 18) {
        cout << "Eres mayor de edad" << endl;
    } else {
        cout << "Eres menor de edad" << endl;
    }

    return 0;
}
```

**Ejemplo de ejecución:**
```
Edad: 15
Eres menor de edad
```

## `if` anidado (y `else if`)

Un `if` anidado es un `if` **dentro** de otro `if` (o de su `else`) — sirve cuando
la segunda decisión solo tiene sentido si la primera ya se cumplió. `else if` es el
caso más común de anidamiento: encadena varias condiciones excluyentes sin tener que
indentar un bloque dentro de otro.

```cpp
#include <iostream>
using namespace std;

int main() {
    double calificacion;
    cout << "Calificacion: ";
    cin >> calificacion;

    if (calificacion >= 6) {
        cout << "Aprobado";
        if (calificacion >= 9) {
            cout << " con Excelencia";
        } else if (calificacion >= 8) {
            cout << " con Bien";
        }
        cout << endl;
    } else {
        cout << "No aprobado" << endl;
    }

    return 0;
}
```

**Ejemplos de ejecución:**
```
Calificacion: 9.5
Aprobado con Excelencia
```
```
Calificacion: 7
Aprobado
```
```
Calificacion: 5
No aprobado
```

El anidamiento real aquí es el `if (calificacion >= 9) ... else if (calificacion >=
8)` que vive **dentro** del bloque del primer `if` — solo se evalúa si ya se sabe
que la calificación aprueba. Con 7, la calificación aprueba pero no cae en ninguno de
los dos casos internos, así que solo se imprime "Aprobado".

## `for`

Ciclo pensado para cuando **sabes de antemano cuántas veces** quieres repetir algo.
Tiene tres partes separadas por `;`: inicialización (se ejecuta una sola vez, al
principio), condición (se revisa antes de cada vuelta) e incremento (se ejecuta al
final de cada vuelta).

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 5; i++) {
        cout << "Vuelta numero " << i << endl;
    }

    return 0;
}
```

**Ejemplo de ejecución:**
```
Vuelta numero 1
Vuelta numero 2
Vuelta numero 3
Vuelta numero 4
Vuelta numero 5
```

## `while`

Ciclo que repite un bloque **mientras** una condición sea verdadera, revisándola
**antes** de cada vuelta. A diferencia del `for`, no tiene una estructura fija de
inicio/incremento — es la opción natural cuando no sabes de antemano cuántas veces
se va a repetir (por ejemplo, hasta que el usuario escriba un valor centinela).

```cpp
#include <iostream>
using namespace std;

int main() {
    int numero;
    cout << "Escribe numeros positivos, 0 para terminar" << endl;
    cout << "Numero: ";
    cin >> numero;

    while (numero != 0) {
        cout << "Recibi: " << numero << endl;
        cout << "Numero: ";
        cin >> numero;
    }

    cout << "Terminaste la lista" << endl;

    return 0;
}
```

**Ejemplo de ejecución:**
```
Escribe numeros positivos, 0 para terminar
Numero: 5
Recibi: 5
Numero: 3
Recibi: 3
Numero: 8
Recibi: 8
Numero: 0
Terminaste la lista
```

Nota la variable `numero`: se lee **una vez antes del ciclo** (para poder evaluar la
condición la primera vez) y **otra vez al final del bloque** (para poder evaluarla de
nuevo en la siguiente vuelta). Olvidar cualquiera de las dos lecturas es el error más
común con `while` — sin la de adentro, el ciclo nunca termina (ciclo infinito).

## `do while`

Como `while`, pero revisa la condición **después** de ejecutar el bloque — por eso el
bloque se ejecuta **al menos una vez**, siempre. Es la opción natural para menús: el
menú se tiene que mostrar mínimo una vez, sin importar qué elija el usuario.

```cpp
#include <iostream>
using namespace std;

int main() {
    int opcion;

    do {
        cout << endl;
        cout << "1. Saludar" << endl;
        cout << "2. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Hola!" << endl;
        }
    } while (opcion != 2);

    cout << "Adios" << endl;

    return 0;
}
```

**Ejemplo de ejecución:**
```

1. Saludar
2. Salir
Opcion: 1
Hola!

1. Saludar
2. Salir
Opcion: 1
Hola!

1. Saludar
2. Salir
Opcion: 2
Adios
```

**`while` vs. `do while`:** en un `while`, si la condición es falsa desde el
principio, el bloque nunca se ejecuta. En un `do while`, el bloque **siempre** se
ejecuta al menos una vez, porque la condición se revisa hasta el final.

## Contadores y acumuladores

Estas dos variables casi siempre aparecen junto con un ciclo:

- **Contador**: cuenta cuántas veces pasó algo. Siempre suma (o resta) una
  **cantidad fija**, típicamente 1, con `contador++` o `contador = contador + 1`.
- **Acumulador**: va sumando (o multiplicando) **valores que cambian** en cada
  vuelta — normalmente lo que el usuario acaba de capturar — con
  `acumulador = acumulador + valor`.

Ambos se **inicializan antes del ciclo** (contador y acumulador en 0, o en 1 si el
acumulador es para una multiplicación) y se actualizan **dentro** del ciclo, en cada
vuelta.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Cuantos numeros vas a capturar: ";
    cin >> n;

    int contadorPositivos = 0;
    int suma = 0;

    for (int i = 1; i <= n; i++) {
        int numero;
        cout << "Numero " << i << ": ";
        cin >> numero;

        suma = suma + numero;

        if (numero > 0) {
            contadorPositivos++;
        }
    }

    double promedio = (double) suma / n;

    cout << endl;
    cout << "Suma total: " << suma << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Cantidad de positivos: " << contadorPositivos << endl;

    return 0;
}
```

**Ejemplo de ejecución (n = 4, con los números 5, -2, 8, -1):**
```
Cuantos numeros vas a capturar: 4
Numero 1: 5
Numero 2: -2
Numero 3: 8
Numero 4: -1

Suma total: 10
Promedio: 2.5
Cantidad de positivos: 2
```

Aquí `suma` es un **acumulador** (suma un valor distinto en cada vuelta, el número
que se acaba de leer) y `contadorPositivos` es un **contador** (suma siempre 1, y
solo cuando se cumple la condición `numero > 0`). El `(double)` antes de `suma / n`
es necesario porque `suma` y `n` son `int`: sin él, la división sería entera y
truncaría el resultado (por ejemplo, `10 / 4` daría `2` en vez de `2.5`).

## Autocheck

**¿Por qué un `for` es buena opción cuando ya sabes cuántas veces quieres repetir
algo, en vez de un `while`?**

Porque el `for` reúne inicialización, condición e incremento en una sola línea, lo
que hace más difícil olvidar alguna de las tres partes. Con `while` es más fácil
olvidar el incremento y terminar con un ciclo infinito.

**Si necesitas mostrar un menú que se repita hasta que el usuario elija "Salir",
¿usarías `while` o `do while`? ¿Por qué?**

`do while`, porque el menú se debe mostrar al menos una vez antes de poder
preguntarle al usuario qué quiere hacer — la condición de salida depende de una
opción que todavía no se ha leído la primera vez.

**En el ejemplo de contadores y acumuladores, ¿qué pasaría si `suma` no se
inicializara en 0 antes del ciclo?**

`suma` empezaría con basura (un valor indefinido de la memoria), y el resultado de
`suma total` sería incorrecto — el ciclo suma correctamente los números leídos, pero
sobre un punto de partida equivocado.
