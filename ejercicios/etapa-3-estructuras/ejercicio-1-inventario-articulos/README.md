# Ejercicio 1 — Inventario de artículos con un arreglo de structs

*Etapa III — Estructuras · Temas: 3.1–3.4 · Solución: [`etapa-3-ejercicio-1.cpp`](etapa-3-ejercicio-1.cpp)*

## Historia de usuario

**Como** encargado de una papelería, **quiero** capturar el nombre, la marca, el
precio y las unidades de mis artículos, y ver una tabla con el importe de cada
uno, **para** saber cuánto dinero tengo en inventario y cuál es mi artículo más
caro.

## Contexto

En la Etapa II, guardar varios datos de cada artículo obligaba a usar un arreglo
por dato (arreglos paralelos) y cuidar que la posición `i` de todos fuera del
mismo artículo. Con un `struct Articulo` los cuatro datos viajan juntos, y un
solo arreglo `Articulo articulos[N]` guarda todo el inventario:
`articulos[i].PrecioUnitario` se lee "el precio del artículo `i`".

| Tema | Dónde se usa |
|---|---|
| 3.1 Estructuras | `struct Articulo` agrupa nombre, marca, precio y unidades; acceso con el operador punto |
| 3.2 Definición | El `struct` se define antes de `main`; `masCaro = articulos[i];` copia el registro completo de una vez |
| 3.3 Inicialización | `Articulo masCaro = {"", "", 0.0, 0};` inicializa con llaves; los demás registros se capturan desde el teclado |
| 3.4 Arreglos de registros | `Articulo articulos[N]`, recorrido con `for`: primero el índice, luego el campo |

`calcularImporte` es una función pura: recibe los **campos sueltos** (`double`,
`int`), no el struct completo, porque pasar structs a funciones todavía no se ve.

## Criterios de aceptación

- [ ] Define un `struct Articulo` con `Nombre` y `Marca` (`string`),
      `PrecioUnitario` (`double`) y `Unidades` (`int`).
- [ ] Guarda los artículos en un arreglo de structs de tamaño `N` (constante, 3).
- [ ] Captura nombre y marca como una sola palabra cada uno.
- [ ] Si el precio no es mayor que 0, muestra un error y lo vuelve a pedir.
- [ ] Si las unidades no son mayores que 0, muestra un error y las vuelve a pedir.
- [ ] Calcula el importe de cada artículo (`precio × unidades`) con una función
      pura `calcularImporte`.
- [ ] Imprime una tabla con nombre, marca, precio, unidades e importe.
- [ ] Muestra el valor total del inventario y el artículo más caro, que se
      guarda copiando el struct completo.

## Ejemplo de ejecución

Captura (cada artículo en su propia pantalla):

```
Articulo 1


Nombre: Lapiz
Marca: Bic
```

```
Articulo 1: Lapiz Bic

Precio Unitario: $7.5
```

Resultado, después de capturar los 3 artículos:

```
Datos de los articulos

Nombre	Marca	PrecioUnitario	Unidades	Importe

Lapiz	Bic	7.5		10		75
Cuaderno	Scribe	32		3		96
Goma	Pelikan	4.25		20		85

Valor total del inventario: $256
Articulo mas caro: Cuaderno (Scribe) a $32
```

Un dato inválido:

```
Articulo 1: Lapiz Bic

Precio Unitario: $-5
ERROR! El precio debe ser mayor que 0
```

El programa espera Enter, limpia la pantalla y vuelve a pedir el precio.

## Cómo funciona la validación: `cin.ignore` y `cin.get`

```cpp
do{
    system("clear");
    cout << "Precio Unitario: $";
    cin >> articulos[i].PrecioUnitario;

    if(articulos[i].PrecioUnitario <= 0){
        cout << "ERROR! El precio debe ser mayor que 0" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Linea macOS
        cin.get(); // Linea macOS
    }
}while(articulos[i].PrecioUnitario <= 0);
```

El `do-while` repite la captura mientras el dato no sea válido. Las dos líneas
del `if` son una **pausa**: detienen el programa para que el usuario alcance a
leer el `ERROR!` antes de que `system("clear")` borre la pantalla.

Para entenderlas hay que saber que lo que escribe el usuario no llega directo a
la variable. Primero se guarda en un *búfer* (una fila de caracteres en espera),
incluido el Enter (`'\n'`). Si el usuario escribe `-5` y presiona Enter, el búfer
tiene `-5\n`; `cin >>` toma el `-5` y **deja el `\n` en el búfer**.

| Línea | Qué hace | Qué pasa si falta |
|---|---|---|
| `cin.ignore(numeric_limits<streamsize>::max(), '\n');` | Descarta lo que quedó en el búfer hasta el Enter, incluido el Enter. `numeric_limits<streamsize>::max()` significa "todos los caracteres que haya"; por eso se necesita `#include <limits>`. | `cin.get()` encuentra el `\n` que dejó `cin >>`, lo lee al instante y no hay pausa: el mensaje de error aparece y se borra. |
| `cin.get();` | Lee un solo carácter. Como el búfer ya quedó vacío, **espera** a que el usuario presione Enter. | No hay pausa. |

**¿Por qué "Linea macOS"?** En Windows, la pausa se suele hacer con
`system("pause")`, que no existe en macOS. `cin.ignore` + `cin.get` hacen la
pausa en cualquier sistema. Por la misma razón, en Dev-C++ hay que cambiar
`system("clear")` por `system("cls")`.

## Casos de prueba

Probados el 15 oct 2026 en macOS, compilando con `g++ -std=c++98 -Wall -Wextra`
y con `-std=c++17` (sin advertencias, mismos resultados en ambos). Nombre y marca
se capturan como `A x`, `B y`, `C z`, salvo en el caso 1.

Se supone que en el precio y las unidades el usuario escribe números, y en las
unidades, números enteros.

| # | Caso | Entrada | Salida esperada | Resultado |
|---|---|---|---|---|
| 1 | Datos normales | Lapiz Bic 7.5 × 10; Cuaderno Scribe 32 × 3; Goma Pelikan 4.25 × 20 | Importes 75, 96 y 85; total $256; más caro: Cuaderno (Scribe) a $32 | ✅ |
| 2 | Precio en 0 | A: precio 0, luego 10 × 1; B 20 × 2; C 5 × 3 | Error, vuelve a pedir el precio; total $65; más caro: B a $20 | ✅ |
| 3 | Precio negativo | A: precio -5, luego 10 × 1; resto igual al caso 2 | Error y vuelve a pedirlo; total $65 | ✅ |
| 4 | Unidades en 0 | A: 10, unidades 0, luego 4; B 20 × 2; C 5 × 3 | Error y vuelve a pedirlas; importe de A = 40; total $95 | ✅ |
| 5 | Unidades negativas | A: 10, unidades -3, luego 4; resto igual al caso 4 | Error y vuelve a pedirlas; total $95 | ✅ |
| 6 | Precios empatados | A 10 × 1; B 10 × 2; C 5 × 3 | Total $45; más caro: A, el primero, porque se compara con `>` | ✅ |

### Limitaciones conocidas

1. **Nombre y marca son una sola palabra.** `cin >>` corta en el primer espacio:
   `Lapiz adhesivo` guarda `Lapiz` como nombre y `adhesivo` como marca. Leer
   texto con espacios requiere `getline`, que no se usa en esta etapa.
2. **La tabla se desalinea con nombres largos.** Las columnas se separan con
   tabuladores (`\t`); un nombre de más de 7 caracteres empuja las demás columnas.

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 8 oct 2026 | Primera versión: `struct Articulo` y un arreglo de 3 artículos que se capturan y se muestran en una tabla. | Temas 3.1, 3.2 y 3.4: agrupar datos en un struct y guardar varios registros en un arreglo. |
| 15 oct 2026 | Se agregaron el importe con la función pura `calcularImporte`, el total del inventario y el artículo más caro (inicializado con llaves y actualizado copiando el struct completo). Se agregó la constante `N`. | Cubrir 3.3 (inicialización con llaves) y la copia de structs de 3.2; que el programa haga algo con los datos además de mostrarlos. |
| 15 oct 2026 | Validación del precio y las unidades con `do-while`: si no son mayores que 0, muestra un error, hace una pausa con `cin.ignore` + `cin.get` y los vuelve a pedir. | Un precio o unas unidades en 0 o negativos no tienen sentido en un inventario y dan importes falsos. Con el precio mayor que 0, además, el "artículo más caro" nunca queda vacío. |
| 15 oct 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización igual que en la Etapa II: cada ejercicio con su ficha junto a su solución. |
