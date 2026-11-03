# Ejercicio 1 — Histórico de temperaturas

*Etapa IV — Archivos · Temas: 4.8–4.9 · Solución: [`etapa-4-ejercicio-1.cpp`](etapa-4-ejercicio-1.cpp) · Siguiente: [Ejercicio 2](../ejercicio-2-consulta-historico/README.md)*

## Historia de usuario

**Como** encargado de una estación meteorológica escolar, **quiero** capturar la
temperatura promedio de cada día y que quede guardada en un archivo, **para** que
el registro no se pierda al cerrar el programa y siga creciendo día con día.

## Contexto

Hasta la Etapa III, todo lo capturado se perdía al terminar el programa. Ahora cada
temperatura se escribe en `datos/historico-temperaturas.txt`, un renglón por día:

```
1 10 2026 24.5
2 10 2026 22
3 10 2026 26
```

Cada renglón es un **registro** con cuatro **campos** separados por un espacio: día,
mes, año y temperatura ([4.2](../../../contenido/etapa-4-archivos/4.2-jerarquia-de-datos.md)).
Un histórico **crece**: lo nuevo se agrega al final y lo anterior nunca se borra. Por
eso se abre con `ios::app`.

| Tema | Dónde se usa |
|---|---|
| 4.8 Escribir con `ofstream` | `salida << fecha.Dia << " " << ... << endl;` |
| 4.8 Comprobar la apertura | `if(!salida)`, `if(prueba)`, `if(!nuevo)` |
| 4.8 Nombre en un `string` | `ARCHIVO.c_str()` y `ruta.c_str()` |
| 4.8 Dónde queda el archivo | Ruta relativa `datos/...`: la carpeta `datos/` junto al programa |
| 4.9 `ios::app` | Agregar cada temperatura al final sin borrar el histórico |
| 4.9 `ios::out` | Crear el archivo vacío la primera vez, en `prepararArchivo` |
| 4.9 `ifstream` falla si no existe | Usado a propósito para **preguntar** si el archivo existe |
| 3.2 Structs | `struct Fecha` agrupa día, mes y año |

Este programa solo **escribe**. Leer el histórico es el
[ejercicio 2](../ejercicio-2-consulta-historico/README.md) y corregir un renglón es el
[ejercicio 3](../ejercicio-3-correccion-historico/README.md).

## Antes de correrlo: la carpeta `datos/`

El programa abre `datos/historico-temperaturas.txt`, una **ruta relativa**: la carpeta
`datos/` se busca junto al programa (en Dev-C++, donde está el `.exe`, que normalmente
es la carpeta del `.cpp`). `ofstream` puede **crear un archivo**, pero **no una
carpeta**: si `datos/` no existe, el programa avisa y termina.

En el repo, la carpeta ya viene creada con un `README.md` adentro (git no guarda
carpetas vacías). El archivo `.txt` no se sube al repo: lo crea el programa la
primera vez.

## Criterios de aceptación

- [ ] Al iniciar, revisa el archivo **sin borrar nada**: si existe lo dice; si no
      existe lo crea vacío y lo dice; si no se puede crear, muestra un error y
      termina con `return 1`.
- [ ] Muestra un menú con `switch`: 1 agregar temperatura, 2 salir. Una opción
      distinta muestra un error (`default`). El menú se repite hasta elegir 2.
- [ ] El flujo de escritura se declara arriba de `main` y se abre y cierra a mano
      (`clear()`, `open()`, `close()`) cada vez que se agrega una temperatura.
- [ ] Pide día (1 a 31), mes (1 a 12), año (4 dígitos) y temperatura (de -10 a 50).
      Si un dato está fuera de rango, muestra un error y lo vuelve a pedir.
- [ ] Agrega un renglón `dia mes anio temperatura` **al final** del archivo; lo que ya
      estaba se conserva, también entre una ejecución y otra.
- [ ] Los límites de la temperatura son constantes con nombre (`TEMP_MIN` y
      `TEMP_MAX`).
- [ ] `prepararArchivo` no usa `cin` ni `cout`: regresa un código y `main` decide
      qué mensaje mostrar.

## Ejemplo de ejecución

Primera vez (la carpeta `datos/` existe, el archivo todavía no):

```
Se creo el archivo vacio datos/historico-temperaturas.txt

Presiona Enter para continuar...
```

```
HISTORICO DE TEMPERATURAS

1. Agregar una nueva temperatura
2. Salir

Opcion: 1
```

```
Nueva temperatura

Dia (1 a 31): 32
ERROR! Dia no valido
Dia (1 a 31): 5
Mes (1 a 12): 11
Anio (4 digitos): 2026
Temperatura promedio del dia (-10 a 50): 51
ERROR! Temperatura fuera de rango
Temperatura promedio del dia (-10 a 50): 18.5

Temperatura guardada en datos/historico-temperaturas.txt

Presiona Enter para volver al menu...
```

`datos/historico-temperaturas.txt` queda con un renglón:

```
5 11 2026 18.5
```

En la siguiente ejecución el programa dice `El archivo datos/historico-temperaturas.txt
ya existe`, y cada temperatura nueva se agrega **debajo** de la anterior.

Sin la carpeta `datos/`:

```
ERROR! No se pudo crear datos/historico-temperaturas.txt (existe la carpeta datos/?)
```

## Cómo funciona `prepararArchivo`, línea por línea

```cpp
int prepararArchivo(string ruta){

    ifstream prueba(ruta.c_str());

    if(prueba){
        prueba.close();
        return YA_EXISTE;
    }

    ofstream nuevo(ruta.c_str());

    if(!nuevo){
        return NO_SE_PUDO_CREAR;
    }

    nuevo.close();
    return CREADO;
}
```

Es una función corta, pero junta varias cosas que se ven por primera vez. Se explican
en el orden en que ocurren.

### 1. Una función que contesta con un código

`prepararArchivo` tiene que contestar algo con **tres** respuestas posibles: el archivo
ya existía, se acaba de crear o no se pudo crear. Una función regresa un solo valor, así
que cada situación se representa con un número:

```cpp
const int YA_EXISTE = 0;
const int CREADO = 1;
const int NO_SE_PUDO_CREAR = -1;
```

Es la misma idea que el `-1` de la búsqueda lineal
([2.6](../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md)), que significa "no
lo encontré". Con **constantes con nombre**, `main` se lee como una frase
(`if(estado == CREADO)`) en lugar de un número mágico (`if(estado == 1)`). Usar un
número negativo para el error es una costumbre, no una regla: lo importante es que los
tres valores sean distintos.

La función **no imprime nada**: es la regla de las funciones de la Etapa I (los
cálculos y las revisiones van en funciones; la plática con el usuario va en `main`).
`main` recibe el código en `estado` y decide qué mensaje mostrar.

### 2. El parámetro `string ruta` y `.c_str()`

La función recibe el nombre del archivo como `string`, así que sirve para cualquier
archivo, no solo para el histórico. En C++98 (el Dev-C++ del curso), `ifstream` y
`ofstream` no aceptan un `string` directamente: `.c_str()` entrega su texto en el
formato antiguo que esperan
([4.8](../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md#si-el-nombre-del-archivo-está-en-un-string)).

### 3. `ifstream` para **preguntar** si el archivo existe

```cpp
ifstream prueba(ruta.c_str());
```

C++98 no tiene una instrucción "¿existe este archivo?". El truco es intentar abrirlo
**para leer**: `ifstream` solo abre archivos que ya existen y **nunca crea ni borra
nada** ([4.9](../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md), modo
`ios::in`). Si se pudo abrir, el archivo existe; si no, no existe. Aquí no se lee ni un
dato: el flujo `prueba` solo se usa para hacer la pregunta.

### 4. Un flujo dentro de un `if`

```cpp
if(prueba){
```

Hasta ahora, la condición de un `if` era una comparación (`x > 0`). Un flujo de archivo
también se puede poner como condición, solo: vale **verdadero si se abrió bien** y
**falso si falló**. `if(prueba)` se lee "si se pudo abrir" y `if(!nuevo)`, con el `!`
de negación, "si **no** se pudo abrir". Es lo mismo que `if(!archivo)` de
[4.8](../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md).

### 5. Varios `return` en una función

```cpp
    if(prueba){
        prueba.close();
        return YA_EXISTE;
    }

    ofstream nuevo(ruta.c_str());
```

`return` **termina la función en ese momento** y regresa el valor; lo que sigue ya no
se ejecuta. Por eso no hace falta un `else`: si el archivo existe, la función se va con
`YA_EXISTE` y nunca llega al `ofstream`. Si el programa llega a la línea del `ofstream`,
es porque el archivo **no** existe. Antes del `return` se cierra `prueba`, porque ya no
se necesita.

### 6. Crear el archivo vacío con `ofstream`

```cpp
ofstream nuevo(ruta.c_str());
```

`ofstream` en su modo normal (`ios::out`) crea el archivo si no existe y, **si
existe, lo vacía**. Aquí es seguro porque el paso 3 ya comprobó que no existe: no hay
nada que borrar. Abrirlo y cerrarlo, sin escribir nada, deja un archivo vacío en el
disco.

### 7. ¿Cuándo falla la creación?

```cpp
if(!nuevo){
    return NO_SE_PUDO_CREAR;
}
```

Casi siempre, porque **no existe la carpeta `datos/`**: `ofstream` crea archivos, no
carpetas. También puede fallar por falta de permisos o porque la memoria USB se retiró.

### 8. Por qué el orden importa

| Si se hiciera... | Qué pasaría con un histórico de 300 días |
|---|---|
| Primero `ifstream` (pregunta), luego `ofstream` solo si no existe | Nada: el histórico se conserva |
| Directamente `ofstream nuevo(ruta.c_str());` "para asegurarse de que exista" | **Se borran los 300 días**: el modo normal vacía el archivo |

### 9. ¿Hace falta esta función?

`ofstream` con `ios::app` también crea el archivo si no existe, así que la opción 1
funcionaría sin `prepararArchivo`. La función sirve para **avisar desde el principio**:
si falta la carpeta, el usuario se entera antes de capturar, no después de escribir día,
mes, año y temperatura. Además, el programa sabe si es la primera vez que se usa.

## El flujo se declara arriba y se abre a mano: `clear`, `open` y `close`

En 4.8 el flujo se declara y se abre en la misma línea:
`ofstream archivo("tabla7.txt");`. Aquí se separan los dos pasos: el flujo se
**declara una vez**, arriba de `main`, junto con las demás variables, y se **abre y
cierra a mano** cada vez que se agrega una temperatura:

```cpp
ofstream salida;    // arriba de main: declarar no abre nada todavia

...

salida.clear();
salida.open(ARCHIVO.c_str(), ios::app);

if(!salida){
    cout << ... "ERROR! No se pudo abrir" ...
}else{
    salida << fecha.Dia << " " << ... << endl;
    salida.close();
}
```

| Instrucción | Qué hace |
|---|---|
| `ofstream salida;` | Crea la variable del flujo, **sin archivo**: todavía no apunta a nada |
| `salida.open(nombre, modo)` | Abre el archivo con ese modo. Es lo mismo que pasaba al escribir `ofstream salida(nombre, modo);`, pero en otro momento |
| `salida.close()` | Cierra el archivo y pasa al disco lo que quedaba en el buffer. El flujo queda **libre** para abrirse otra vez |
| `salida.clear()` | Borra la **marca de error** del flujo (se explica abajo) |

**¿Por qué se declara arriba?** Por el `switch` del menú (siguiente sección): un `case`
no puede declarar una variable que se inicializa, como `ofstream salida(...)`, sin
encerrarse entre llaves. Con el flujo declarado arriba, cada `case` solo lo abre y lo
cierra.

**¿Por qué `clear()` antes de `open()`?** Un flujo que falla queda **marcado con
error**, y `close()` no quita esa marca. En el estándar de C++98, que es el del Dev-C++
del curso, `open()` tampoco la quitaba (se corrigió en C++11). Si un intento falla
(por ejemplo, porque alguien borró la carpeta `datos/` con el programa abierto) y el
siguiente sí abre el archivo, el flujo seguiría marcado: `if(!salida)` diría que hubo
error y no se escribiría nada. `clear()` deja el flujo limpio antes de cada apertura.
Con el flujo de **lectura** del ejercicio 2 esto pasa **siempre**, no solo con errores
raros, porque la lectura termina precisamente cuando falla.

**El archivo se abre y se cierra en cada temperatura**, no una sola vez al principio.
Así, cada dato queda guardado en el disco en cuanto se captura: si el programa se cierra
de golpe, lo anterior ya está a salvo.

## El menú con `switch`

```cpp
switch(opcion){

    case 1:
        ...
        break;

    case 2:
        break;  // salir: no hay nada que hacer aqui; el do-while termina

    default:
        cout << "ERROR! Opcion no valida" << endl;
}
```

- Cada `case` termina con `break`; sin él, el programa **seguiría** con el código del
  `case` siguiente.
- `case 2` (Salir) está vacío a propósito: si no existiera, el 2 caería en `default` y
  mostraría "Opcion no valida". El que termina el programa es el `do-while`, con
  `while(opcion != 2)`.
- `default` atiende cualquier otro número.

Si en un `case` se declarara un flujo y se abriera en la misma línea, el programa no
compilaría:

```cpp
case 1:
    ofstream salida(ARCHIVO.c_str(), ios::app);
    ...
    break;
case 2:     // error: jump to case label / crosses initialization of 'std::ofstream salida'
```

Todo el `switch` es **un solo bloque**: al saltar al `case 2`, la variable `salida` del
`case 1` ya "existe", pero se brincó la línea que la abre, y C++ no lo permite. Con la
declaración arriba de `main`, el problema desaparece.

## Otros detalles del programa

**El formato del renglón.** `salida << fecha.Dia << " " << fecha.Mes << " " <<
fecha.Anio << " " << temperatura << endl;` escribe los campos separados por **espacios**
y termina el registro con `endl` (salto de renglón). Ese formato no es un adorno: es el
que permite leer después con `entrada >> dia >> mes >> anio >> temperatura`
(ejercicio 2), porque `>>` usa los espacios y los saltos de renglón para separar un
dato del siguiente. Sin los `" "`, el 5 de noviembre quedaría `5112026` y ya no se
podría separar.

**`ios::app` contra el modo normal.** `salida.open(ARCHIVO.c_str(), ios::app);` abre
para escribir **al final**. Sin `ios::app`, cada temperatura nueva vaciaría el archivo
y el histórico tendría siempre un solo renglón: el último.

**`prepararArchivo` sí declara y abre en la misma línea** (`ifstream prueba(...)`,
`ofstream nuevo(...)`), como en 4.8. Ahí no hay `switch` y cada flujo se usa una sola
vez, así que no hace falta separar los pasos.

**`return 1;` en `main`.** Un `return` dentro de `main` termina el programa. Por
costumbre, `0` significa "terminó bien" y otro número, "terminó con un error".

**`cin.get()` solo, al iniciar.** La pausa del menú usa `cin.ignore` + `cin.get`
porque `cin >>` deja un Enter en el búfer (ver el
[ejercicio 1 de la Etapa III](../../etapa-3-estructuras/ejercicio-1-inventario-articulos/README.md#cómo-funciona-la-validación-cinignore-y-cinget)).
La pausa del inicio ocurre **antes** de cualquier `cin >>`: el búfer está vacío y basta
con `cin.get()`.

**En Dev-C++ (Windows)**, cambiar `system("clear")` por `system("cls")`. Las líneas
marcadas `// Linea macOS` funcionan igual en Windows.

## Casos de prueba

Probados el 2 nov 2026 en macOS, compilando con `g++ -std=c++98 -Wall -Wextra` y con
`-std=c++17` (sin advertencias, mismas salidas en ambos). Se supone que en los campos
numéricos el usuario escribe números (enteros en día, mes, año y opción).

| # | Caso | Entrada | Salida esperada | Resultado |
|---|---|---|---|---|
| 1 | Primera ejecución | `datos/` vacía; opción 1: 5, 11, 2026, 18.5 | "Se creo el archivo vacio"; el archivo queda con `5 11 2026 18.5` | ✅ |
| 2 | El histórico se conserva | Archivo con 8 renglones; opción 1: 31, 12, 2026, -10 | "ya existe"; el renglón nuevo queda como el 9.º, los 8 anteriores intactos | ✅ |
| 3 | Día fuera de rango | Día 0, luego 32, luego 31 | Error dos veces; acepta 31 | ✅ |
| 4 | Mes fuera de rango | Mes 13, luego 0, luego 12 | Error dos veces; acepta 12 | ✅ |
| 5 | Año sin 4 dígitos | Año 26, luego 20260, luego 2026 | Error dos veces; acepta 2026 | ✅ |
| 6 | Temperatura fuera de rango | -11, luego 51, luego -10 | Error dos veces; acepta -10 (límite exacto) | ✅ |
| 7 | Límite superior | Temperatura 50 | Se acepta y se guarda `50` | ✅ |
| 8 | Opción no válida | Opción 7 | Error y vuelve al menú | ✅ |
| 9 | Sin carpeta `datos/` | Correr el programa donde no existe `datos/` | Mensaje de error y termina con código 1, sin mostrar el menú | ✅ |

### Limitaciones conocidas

1. **La validación del día es sencilla:** acepta del 1 al 31 en cualquier mes (no
   detecta un 31 de abril).
2. **No revisa fechas repetidas:** se puede capturar dos veces el mismo día. Los dos
   renglones quedan en el archivo; el ejercicio 3 permite corregir cualquiera de ellos.
3. **No crea la carpeta `datos/`:** crear carpetas desde C++98 depende del sistema
   operativo y no se ve en el curso.

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 29 oct 2026 | Primera versión, hecha en clase: menú, captura de fecha y temperatura, `prepararArchivo` y escritura con `ios::app`. | Temas 4.8 y 4.9: escribir un archivo y agregar sin borrar. |
| 2 nov 2026 | El ejercicio se movió a su propia carpeta con esta ficha; `datos/` lleva un `README.md` para que exista al clonar el repo; se validó la temperatura (de -10 a 50, con `TEMP_MIN` y `TEMP_MAX`, como en 4.9); se comentaron a detalle `prepararArchivo` y el formato del renglón. | Seguir la estructura de las demás etapas; sin la carpeta, el programa no corría en un clon nuevo; una temperatura imposible ensuciaría las estadísticas del ejercicio 2. |
| 2 nov 2026 | El menú pasó de `if`/`else if` a `switch`; el flujo `salida` se declara arriba de `main` y se abre a mano con `clear()` + `open()` + `close()`. | Preferencia del curso por `switch` en los menús; un `case` no puede declarar un flujo inicializado, y en C++98 `open()` no borra la marca de error de un intento anterior. |
