# Ejercicio 2 — Consulta del histórico de temperaturas

*Etapa IV — Archivos · Temas: 4.8 (lectura) · Solución: [`etapa-4-ejercicio-2.cpp`](etapa-4-ejercicio-2.cpp) · Anterior: [Ejercicio 1](../ejercicio-1-historico-temperaturas/README.md) · Siguiente: [Ejercicio 3](../ejercicio-3-correccion-historico/README.md)*

## Historia de usuario

**Como** encargado de la estación meteorológica, **quiero** ver todas las
temperaturas guardadas y, para un mes, cuántas hay, su promedio, la máxima y la
mínima, **para** analizar el clima sin tener que abrir el archivo y hacer las
cuentas a mano.

## Contexto

Es el programa del [ejercicio 1](../ejercicio-1-historico-temperaturas/README.md) con
dos opciones nuevas que **leen** el archivo:

| Opción | Qué hace con el archivo |
|---|---|
| 1. Agregar | **Escribe** un renglón al final (`ofstream` con `ios::app`), igual que en el ejercicio 1 |
| 2. Ver el histórico | **Lee** todos los renglones y los muestra en una tabla numerada |
| 3. Estadísticas de un mes | **Lee** todos los renglones, pero solo **toma en cuenta** los del mes y año pedidos |

El programa **no sabe cuántos renglones tiene el archivo**: puede tener 0, 3 o 300.
Por eso se lee con `while (archivo >> ...)`, que da una vuelta por renglón y se
detiene solo cuando ya no hay datos.

Aquí todavía **no se usa un arreglo**: cada renglón se lee, se usa (se imprime o se
suma) y se olvida al leer el siguiente. Guardar todo el archivo en un arreglo es el
[ejercicio 3](../ejercicio-3-correccion-historico/README.md).

| Tema | Dónde se usa |
|---|---|
| 4.8 Leer con `ifstream` | `entrada.clear(); entrada.open(ARCHIVO.c_str());` en las opciones 2 y 3 |
| 4.8 `while (archivo >> ...)` en lugar de `eof()` | Lee renglón por renglón sin saber cuántos hay |
| 4.9 `ios::app` | La opción 1, sin cambios |
| 3.2 Structs | `fechaLeida.Dia`, `fechaLeida.Mes`, `fechaLeida.Anio`: la lectura va directo a los campos |
| 2.x Acumuladores y contadores | `cantidad`, `suma`, `maxima`, `minima` |
| 1.3 Función pura | `calcularPromedio(suma, cantidad)` |

## Antes de correrlo: la carpeta `datos/`

Igual que en el ejercicio 1: la carpeta `datos/` tiene que existir junto al programa
(en el repo ya viene creada). Para probar sin capturar día por día, crea
`datos/historico-temperaturas.txt` con el Bloc de notas y pega este histórico de
ejemplo, que se usa en los casos de prueba:

```
1 10 2026 24.5
2 10 2026 22
3 10 2026 26
4 10 2026 19.5
31 10 2026 15
1 11 2026 14
2 11 2026 -2
3 11 2026 12.5
```

## Criterios de aceptación

- [ ] Conserva todo lo del ejercicio 1: revisión del archivo al iniciar, opción
      Agregar con validación y escritura con `ios::app`.
- [ ] Menú con `switch`: 1 agregar, 2 ver el histórico, 3 estadísticas de un mes,
      4 salir. Una opción distinta muestra un error (`default`). El menú se repite
      hasta elegir 4.
- [ ] Los flujos `entrada` (`ifstream`) y `salida` (`ofstream`) se declaran arriba de
      `main` y se abren y cierran a mano, con `clear()` antes de cada `open()`.
- [ ] La opción 2 muestra todos los renglones en una tabla numerada desde 1, con la
      fecha como `d/m/aaaa`, y al final cuántos registros hay. Si el archivo está
      vacío, lo dice.
- [ ] La opción 3 pide mes (1 a 12) y año (4 dígitos), con validación, y muestra
      cuántas temperaturas hay de ese mes, su promedio, la máxima y la mínima, cada
      una con su día. Si no hay ninguna, lo dice.
- [ ] Se lee con `while (archivo >> ...)`, no con `eof()`.
- [ ] El promedio se calcula con una función pura `calcularPromedio` que no divide
      entre 0.
- [ ] Lo agregado con la opción 1 aparece en las opciones 2 y 3 sin reiniciar el
      programa.

## Ejemplo de ejecución

Con el histórico de ejemplo, opción 2:

```
Historico completo

#	Fecha		Temperatura

1	1/10/2026	24.5
2	2/10/2026	22
3	3/10/2026	26
4	4/10/2026	19.5
5	31/10/2026	15
6	1/11/2026	14
7	2/11/2026	-2
8	3/11/2026	12.5

Registros: 8

Presiona Enter para volver al menu...
```

Opción 3, octubre de 2026:

```
Estadisticas de un mes

Mes (1 a 12): 10
Anio (4 digitos): 2026

Temperaturas de 10/2026: 5
Promedio: 21.4
Maxima: 26 (dia 3)
Minima: 15 (dia 31)
```

Opción 3, un mes sin datos:

```
Estadisticas de un mes

Mes (1 a 12): 12
Anio (4 digitos): 2026

No hay temperaturas registradas de 12/2026
```

## Cómo funciona la lectura: `while(archivo >> ...)`

```cpp
ifstream entrada;   // arriba de main

...

entrada.clear();
entrada.open(ARCHIVO.c_str());

if(!entrada){
    cout << "ERROR! No se pudo abrir " << ARCHIVO << endl;
}else{
    registros = 0;
    while(entrada >> fechaLeida.Dia >> fechaLeida.Mes >> fechaLeida.Anio >> temperaturaLeida){
        registros++;
        cout << registros << "\t" << fechaLeida.Dia << "/" ... << endl;
    }
    entrada.close();
}
```

### 1. `>>` con un archivo funciona igual que con `cin`

`entrada >> x` toma el siguiente dato del archivo, igual que `cin >> x` toma el
siguiente dato del teclado. Se salta los espacios y los saltos de renglón, y lee hasta
el siguiente espacio. Por eso en el ejercicio 1 se escribieron los campos separados
por `" "`: el formato de escritura y el de lectura son **el mismo**.

### 2. Cuatro `>>` seguidos leen un renglón completo

```cpp
entrada >> fechaLeida.Dia >> fechaLeida.Mes >> fechaLeida.Anio >> temperaturaLeida
```

Se lee de izquierda a derecha: con el renglón `31 10 2026 15`, `Dia` recibe 31, `Mes`
10, `Anio` 2026 y `temperaturaLeida` 15. Es como escribir `cin >> a >> b >> c >> d;`.
Las variables tienen que ir **en el mismo orden** en que están los campos en el
archivo: si se leyera primero la temperatura, el 31 terminaría en `temperaturaLeida`.

Los datos van **directo a los campos del struct**: `fechaLeida.Dia` es un `int` como
cualquier otro y se puede usar con `>>`.

### 3. La lectura como condición del `while`

Igual que un flujo dentro de un `if` (ejercicio 1, paso 4), una **lectura** dentro de
la condición vale verdadero si funcionó y falso si falló. Los cuatro `>>` forman una
sola lectura: es verdadera solo si se pudieron leer **los cuatro** datos.

Con el histórico de ejemplo:

| Vuelta | ¿Hay un renglón completo? | Qué pasa |
|---|---|---|
| 1 a 8 | Sí | La condición es verdadera: se ejecuta el cuerpo del `while` con ese renglón |
| 9 | No: el archivo se acabó | La lectura falla, la condición es falsa y el `while` termina |

No hace falta saber de antemano cuántos renglones hay ni usar `eof()`, que da una
vuelta de más ([4.8](../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md#por-qué-no-usar-eof)).
Si el archivo está vacío, la primera lectura ya falla: el `while` no da ni una vuelta,
`registros` se queda en 0 y el programa dice que el histórico está vacío.

### 4. Un solo flujo, abierto y cerrado en cada consulta

`entrada` se declara **una vez**, arriba de `main`, y las opciones 2 y 3 lo abren y lo
cierran a mano cada vez (por qué se declara arriba y qué hacen `open` y `close` se
explica en el
[ejercicio 1](../ejercicio-1-historico-temperaturas/README.md#el-flujo-se-declara-arriba-y-se-abre-a-mano-clear-open-y-close)).

**Se abre en cada consulta**, no una sola vez al principio. Un flujo de lectura avanza
como un separador de libro: cuando llega al final, se queda ahí. Si se abriera una sola
vez, la segunda consulta ya no leería nada. Al abrirlo en cada consulta:

- la lectura siempre empieza en el **primer renglón**;
- se ven los renglones que la opción 1 agregó **en esta misma ejecución**.

**`clear()` antes de `open()` aquí es indispensable.** El `while` termina **porque una
lectura falló** (paso 3), así que al salir del `while` el flujo queda marcado con error,
y `close()` no borra esa marca. En C++98 (el Dev-C++ del curso), `open()` tampoco la
borra. Sin `clear()`:

| Consulta | Qué pasaría sin `entrada.clear()` |
|---|---|
| 1.ª | Bien: el flujo es nuevo y no tiene marca |
| 2.ª y siguientes | El archivo se abre, pero el flujo sigue marcado: `if(!entrada)` dice "No se pudo abrir" o el `while` no lee nada y el histórico parece **vacío** |

Con compiladores modernos (C++11 en adelante) `open()` ya borra la marca, así que el
error puede **no** aparecer en una computadora y sí en la del salón. `clear()` hace que
el programa funcione igual en todas.

### 5. Por qué hay `fecha` y también `fechaLeida`

`fecha` y `temperatura` guardan lo que **captura el usuario** (opción 1);
`fechaLeida` y `temperaturaLeida`, lo que **viene del archivo** (opciones 2 y 3).
Funcionaría con las mismas variables, pero con nombres distintos se entiende de
dónde viene cada dato.

## Cómo funcionan las estadísticas de un mes

### Filtrar mientras se lee

```cpp
while(entrada >> fechaLeida.Dia >> fechaLeida.Mes >> fechaLeida.Anio >> temperaturaLeida){
    if(fechaLeida.Mes == mesBuscado && fechaLeida.Anio == anioBuscado){
        cantidad++;
        suma += temperaturaLeida;
        ...
    }
}
```

El `while` lee **todos** los renglones (no hay forma de saltar directo a octubre: el
archivo es secuencial, [4.4](../../../contenido/etapa-4-archivos/4.4-tipos-de-ficheros.md)),
pero el `if` deja pasar solo los del mes **y** el año buscados. El año importa: el
10/2025 y el 10/2026 son meses distintos.

### La máxima y la mínima empiezan con el primer renglón del mes

```cpp
if(cantidad == 1){
    maxima = temperaturaLeida;
    diaMaxima = fechaLeida.Dia;
    minima = temperaturaLeida;
    diaMinima = fechaLeida.Dia;
}else{
    if(temperaturaLeida > maxima){ ... }
    if(temperaturaLeida < minima){ ... }
}
```

`cantidad` se acaba de incrementar, así que `cantidad == 1` significa "este es el
**primer** renglón del mes". Ese renglón es, por ahora, la máxima y la mínima a la vez.
Desde el segundo, cada temperatura se compara con lo que va.

¿Por qué no empezar con `maxima = 0` y `minima = 0` y comparar desde el primero?

| Mes | Temperaturas | Con `maxima = 0` y `minima = 0` desde el inicio | Empezando con el primer renglón |
|---|---|---|---|
| Diciembre frío | -5, -3, -8 | Máxima **0**: un valor que no está en el archivo | Máxima -3 ✅ |
| Octubre | 24.5, 22, 26, 19.5, 15 | Mínima **0**: un valor que no está en el archivo | Mínima 15 ✅ |

El `= 0` de antes del `while` está solo para que las variables no queden sin valor:
se reemplaza en cuanto aparece el primer renglón del mes. Si el mes no tiene
renglones, nunca se imprimen.

**Empates:** como se compara con `>` y `<` (no con `>=` y `<=`), si dos días tienen la
misma temperatura máxima se queda el **primero** que aparece en el archivo.

### `calcularPromedio`: una función pura que no divide entre 0

```cpp
double calcularPromedio(double suma, int cantidad){
    if(cantidad == 0){
        return 0;
    }
    return suma / cantidad;
}
```

Recibe los **datos sueltos** (`suma` y `cantidad`), no el archivo. `main` solo la llama
cuando `cantidad > 0`, pero la función se protege sola: una función pura debe dar un
resultado razonable con cualquier dato que reciba, sin depender de quién la llame.

## Casos de prueba

Probados el 2 nov 2026 en macOS, compilando con `g++ -std=c++98 -Wall -Wextra` y con
`-std=c++17` (sin advertencias, mismas salidas en ambos). "Histórico de ejemplo" es el
archivo de la sección *Antes de correrlo*. Se supone que en los campos numéricos el
usuario escribe números (enteros en mes, año y opción).

El caso 10 comprueba que el mismo flujo se puede abrir varias veces. En macOS, `g++`
es clang, que ya borra la marca de error en `open()` aun con `-std=c++98`, así que
ahí el caso pasa con o sin `clear()`. Lo que protege `clear()` es el comportamiento de
compiladores más viejos, como el de Dev-C++; no se pudo probar en este equipo.

| # | Caso | Entrada | Salida esperada | Resultado |
|---|---|---|---|---|
| 1 | Ver el histórico | Histórico de ejemplo; opción 2 | Tabla con los 8 renglones numerados del 1 al 8; "Registros: 8" | ✅ |
| 2 | Estadísticas de un mes completo | Opción 3: 10, 2026 | 5 temperaturas; promedio 21.4; máxima 26 (día 3); mínima 15 (día 31) | ✅ |
| 3 | Mes con una temperatura negativa | Opción 3: 11, 2026 | 3 temperaturas; promedio 8.16667; máxima 14 (día 1); mínima -2 (día 2) | ✅ |
| 4 | Mes sin datos | Opción 3: 12, 2026 | "No hay temperaturas registradas de 12/2026" | ✅ |
| 5 | Mismo mes, otro año | Opción 3: 10, 2025 | "No hay temperaturas registradas de 10/2025" | ✅ |
| 6 | Mes y año fuera de rango | Opción 3: mes 0, 13, luego 10; año 26, luego 2025 | Error dos veces en el mes y una en el año | ✅ |
| 7 | Archivo vacío | `datos/` sin archivo; opciones 2 y 3 (10, 2026) | "El historico esta vacio"; "No hay temperaturas registradas de 10/2026" | ✅ |
| 8 | Lo agregado se ve sin reiniciar | Caso 7, luego opción 1: 7, 10, 2026, 20; opciones 2 y 3 (10, 2026) | Tabla con 1 registro; 1 temperatura, promedio, máxima y mínima 20 (día 7) | ✅ |
| 9 | Empates | Archivo `1 10 2026 20`, `2 10 2026 25`, `3 10 2026 25`, `4 10 2026 20`; opción 3: 10, 2026 | Promedio 22.5; máxima 25 (día 2); mínima 20 (día 1): gana el primero | ✅ |
| 10 | Consultas repetidas con el mismo flujo | Archivo vacío; opción 1 (1, 10, 2026, 20); opción 2 dos veces; opción 3 (10, 2026) dos veces; opción 2 otra vez | Las tres consultas del histórico muestran 1 registro y las dos de estadísticas, 1 temperatura | ✅ |

### Limitaciones conocidas

1. **Un renglón mal escrito detiene la lectura.** Si alguien edita el archivo a mano
   y escribe `2 10 2026 X`, la lectura de ese renglón falla y el `while` termina ahí:
   ese renglón y **todos los siguientes** se ignoran, sin aviso. Con un archivo que
   solo escribe el programa, eso no pasa.
2. **El promedio se muestra con todos sus decimales** (`8.16667`); redondear a uno
   requiere `fixed` y `setprecision` de `<iomanip>` (ver
   [1.2](../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar));
   aquí no se usa a propósito.
3. Las del ejercicio 1: el día se valida del 1 al 31 en cualquier mes y no se revisan
   fechas repetidas (las dos cuentan en las estadísticas).

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 2 nov 2026 | Primera versión: el programa del ejercicio 1 más las opciones Ver el histórico y Estadísticas de un mes, leyendo con `while (archivo >> ...)`. | Tema 4.8: leer un archivo sin saber cuántos renglones tiene, sin `eof()`. |
| 2 nov 2026 | El menú pasó de `if`/`else if` a `switch`; `entrada` y `salida` se declaran arriba de `main` y se abren a mano con `clear()` + `open()` + `close()`. Se agregó el caso de prueba 10. | Preferencia del curso por `switch` en los menús; sin `clear()`, en C++98 la segunda consulta no leería nada. |
