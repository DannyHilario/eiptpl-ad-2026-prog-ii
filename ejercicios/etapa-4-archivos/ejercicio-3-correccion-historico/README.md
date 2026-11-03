# Ejercicio 3 — Corrección del histórico de temperaturas

*Etapa IV — Archivos · Temas: 4.10 (+ 4.8, 4.9 y arreglos de structs de la Etapa III) · Solución: [`etapa-4-ejercicio-3.cpp`](etapa-4-ejercicio-3.cpp) · Anterior: [Ejercicio 2](../ejercicio-2-consulta-historico/README.md)*

## Historia de usuario

**Como** encargado de la estación meteorológica, **quiero** corregir una temperatura
que se capturó mal, **para** que el histórico y sus estadísticas sean correctos sin
tener que borrar el archivo y capturar todo otra vez.

## Contexto

Es el programa del [ejercicio 1](../ejercicio-1-historico-temperaturas/README.md) con
la opción *Ver el histórico* del [ejercicio 2](../ejercicio-2-consulta-historico/README.md)
y una opción nueva: **Corregir una temperatura**.

Agregar era fácil: `ios::app` escribe al final. Pero el renglón que se capturó mal
está **en medio** del archivo, y en un archivo de texto secuencial **un renglón no se
puede cambiar en su lugar**: si `22` pasa a `21.5`, el dato nuevo ocupa más caracteres
y pisaría el renglón siguiente
([4.10](../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md#por-qué-no-se-puede-cambiar-un-dato-en-su-lugar)).
La corrección sigue los tres pasos de 4.10:

| Paso | Qué se hace | Con qué |
|---|---|---|
| 1. Cargar | Se lee el archivo **completo** a un arreglo de structs | `ifstream` + `while (n < MAX_REGISTROS && entrada >> ...)` |
| 2. Modificar | Se cambia la temperatura **en el arreglo**, en memoria | `historico[posicion].Temperatura` |
| 3. Reescribir | Se **vacía** el archivo y se escribe otra vez con todo el arreglo | `ofstream` en modo normal + `for` |

Cada opción usa el archivo de la forma que le conviene:

| Opción | ¿Usa el arreglo? | Cómo usa el archivo |
|---|---|---|
| 1. Agregar | No | `ios::app`: agrega un renglón al final, sin leer nada |
| 2. Ver | No | Lee y muestra renglón por renglón (como el ejercicio 2) |
| 3. Corregir | **Sí** | Carga todo, modifica y reescribe todo (modo normal, `ios::out`) |

| Tema | Dónde se usa |
|---|---|
| 4.10 Cargar, modificar y reescribir | La opción 3 completa |
| 4.9 `ios::app` contra `ios::out` | Agregar usa `ios::app`; reescribir usa el modo normal, que vacía el archivo |
| 4.8 `while (archivo >> ...)` | Ver el histórico y cargar el arreglo |
| 3.4 Arreglos de registros | `Registro historico[MAX_REGISTROS]` con el contador `n` |
| 3.5 Estructuras anidadas y contador con capacidad | `historico[i].FechaRegistro.Dia`; `n` nunca pasa de `MAX_REGISTROS` |

## Antes de correrlo: la carpeta `datos/`

Igual que en los ejercicios 1 y 2: la carpeta `datos/` tiene que existir junto al
programa (en el repo ya viene creada). Para probar, pega en
`datos/historico-temperaturas.txt` el histórico de ejemplo del
[ejercicio 2](../ejercicio-2-consulta-historico/README.md#antes-de-correrlo-la-carpeta-datos).

## Criterios de aceptación

- [ ] Conserva la opción Agregar del ejercicio 1 (con `ios::app`) y la opción Ver del
      ejercicio 2.
- [ ] Menú con `switch`: 1 agregar, 2 ver el histórico, 3 corregir una temperatura,
      4 salir. Una opción distinta muestra un error (`default`). El menú se repite
      hasta elegir 4.
- [ ] Los flujos `entrada` y `salida` se declaran arriba de `main` y se abren y cierran
      a mano, con `clear()` antes de cada `open()`.
- [ ] Define `struct Registro` con un `struct Fecha` anidado y la temperatura.
- [ ] La opción 3 carga el archivo completo en un arreglo de `MAX_REGISTROS` (100)
      registros con un contador `n`, sin escribir nunca fuera del arreglo.
- [ ] Si el archivo tiene más registros de los que caben, muestra un error y **no
      modifica el archivo**.
- [ ] Si el archivo está vacío, lo dice y no pide nada.
- [ ] Muestra la tabla numerada, pide el `#` del registro (de 1 a `n`, con
      validación), muestra su fecha y su temperatura actual y pide la temperatura
      correcta (de -10 a 50, con validación).
- [ ] Reescribe el archivo completo con el modo normal (no `ios::app`): el archivo
      queda con los mismos renglones, en el mismo orden, y solo cambia la temperatura
      corregida.

## Ejemplo de ejecución

Con el histórico de ejemplo, opción 3:

```
Corregir una temperatura

#	Fecha		Temperatura

1	1/10/2026	24.5
2	2/10/2026	22
3	3/10/2026	26
4	4/10/2026	19.5
5	31/10/2026	15
6	1/11/2026	14
7	2/11/2026	-2
8	3/11/2026	12.5

# del registro a corregir (1 a 8): 9
ERROR! Ese registro no existe
# del registro a corregir (1 a 8): 2

Fecha: 2/10/2026
Temperatura actual: 22
Temperatura correcta (-10 a 50): 21.5

Temperatura corregida. Se reescribieron 8 registros en datos/historico-temperaturas.txt

Presiona Enter para volver al menu...
```

El archivo queda igual, salvo el segundo renglón:

```
1 10 2026 24.5
2 10 2026 21.5
3 10 2026 26
...
```

Con un archivo de más de 100 registros:

```
Corregir una temperatura

ERROR! El historico tiene 101 registros y solo caben 100
No se corrige nada para no perder datos
```

## Cómo funciona la corrección, paso por paso

### El registro: un struct con otro struct adentro

```cpp
struct Registro{
    Fecha FechaRegistro;
    double Temperatura;
};

Registro historico[MAX_REGISTROS];
int n;
```

Un `Registro` es **un renglón del archivo completo**: su fecha (un `struct Fecha`, como
en [3.5](../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md)) y su
temperatura. El arreglo `historico` tiene lugar para 100 renglones y `n` dice cuántos
están ocupados de verdad. Para llegar a un dato se va de afuera hacia adentro:

```
historico[3].FechaRegistro.Dia
   │      │       │         └─ el campo
   │      │       └─ la fecha de ese registro
   │      └─ el cuarto registro (posición 3)
   └─ el arreglo
```

### Paso 1. Cargar sin pasarse del arreglo

```cpp
n = 0;
while(n < MAX_REGISTROS && entrada >> historico[n].FechaRegistro.Dia >> historico[n].FechaRegistro.Mes >> historico[n].FechaRegistro.Anio >> historico[n].Temperatura){
    n++;
}
```

Es el `while (archivo >> ...)` del ejercicio 2, con dos diferencias:

**a) La lectura va directo a `historico[n]`.** Cada renglón se guarda en la siguiente
posición libre del arreglo, que es justamente `n`: con 0 registros cargados, el primero
va a `historico[0]`; con 1, el segundo va a `historico[1]`, y así. Después de leer, `n++`
cuenta el registro. Si la lectura falla (el archivo se acabó), `n` **no** aumenta: solo
cuentan los renglones completos.

**b) `n < MAX_REGISTROS` va primero, y eso es importante.** El `&&` revisa de izquierda
a derecha y, si la primera parte ya es falsa, **ya no evalúa la segunda** (no hace
falta: falso `&&` lo que sea es falso). Cuando el arreglo está lleno (`n` vale 100):

| Orden | Qué pasa con `n = 100` |
|---|---|
| `n < MAX_REGISTROS && entrada >> historico[n]...` ✅ | `100 < 100` es falso: el `&&` se detiene y **no se lee** nada |
| `entrada >> historico[n]... && n < MAX_REGISTROS` ❌ | Primero lee en `historico[100]`, que **no existe** (el arreglo va de 0 a 99): se escribe fuera del arreglo |

### Paso 1 (continuación). ¿Quedaron renglones sin cargar?

```cpp
sobrantes = 0;
while(entrada >> fechaLeida.Dia >> fechaLeida.Mes >> fechaLeida.Anio >> temperaturaLeida){
    sobrantes++;
}
entrada.close();
```

El primer `while` se pudo detener por **dos razones distintas**, y el programa necesita
saber cuál fue:

| ¿Por qué se detuvo el primer `while`? | Estado del flujo `entrada` | Qué hace este segundo `while` |
|---|---|---|
| El archivo se acabó (lo normal) | Una lectura ya **falló**. Un flujo que falló se queda fallado: las lecturas siguientes también fallan | No da ni una vuelta: `sobrantes` = 0 |
| El arreglo se llenó (`n` llegó a 100) | Nunca falló: se detuvo antes de leer | Cuenta los renglones que no cupieron: `sobrantes` > 0 |

Los renglones sobrantes se leen en variables sueltas (`fechaLeida`, `temperaturaLeida`)
solo para **contarlos**; no se guardan.

¿Por qué importa? Porque el paso 3 reescribe el archivo **solo con lo que hay en el
arreglo**. Si el archivo tuviera 101 renglones y se reescribiera con los 100 del
arreglo, **el renglón 101 desaparecería**. Por eso, con `sobrantes > 0`, el programa se
niega a corregir: es mejor no corregir que perder datos.

Esta marca de "fallado" es la misma razón por la que, antes de cada `entrada.open(...)`,
va un `entrada.clear()`: la carga anterior (o la opción Ver) dejó el flujo marcado, y
en C++98 ni `close()` ni `open()` borran la marca
([ejercicio 2](../ejercicio-2-consulta-historico/README.md#4-un-solo-flujo-abierto-y-cerrado-en-cada-consulta)).
Sin `clear()`, la segunda corrección de la misma ejecución no cargaría nada y diría que
el histórico está vacío.

`entrada.close()` cierra el archivo **antes** de volver a abrirlo para escribir en el
paso 3. Tener el mismo archivo abierto para leer y para escribir a la vez puede dar
resultados raros, y en Windows incluso puede impedir la escritura.

### Paso 2. Elegir y modificar el registro

```cpp
do{
    cout << "# del registro a corregir (1 a " << n << "): ";
    cin >> numero;
    ...
}while(numero < 1 || numero > n);

posicion = numero - 1;
```

**`numero` y `posicion` son dos cosas distintas.** La tabla numera desde **1** (así
cuenta una persona); el arreglo, desde **0**. El registro `#2` de la tabla está en
`historico[1]`. El rango válido de `numero` (1 a `n`) depende de cuántos renglones se
cargaron, no de `MAX_REGISTROS`: con 8 renglones, el `#9` no existe, aunque
`historico[8]` sí sea una casilla del arreglo (vacía).

```cpp
do{
    cout << "Temperatura correcta (" << TEMP_MIN << " a " << TEMP_MAX << "): ";
    cin >> historico[posicion].Temperatura;
    ...
}while(historico[posicion].Temperatura < TEMP_MIN || historico[posicion].Temperatura > TEMP_MAX);
```

La temperatura nueva se captura **directo en el campo del arreglo**, con la misma
validación de siempre. Hasta aquí, **el archivo no ha cambiado**: el cambio solo existe
en memoria.

### Paso 3. Reescribir el archivo completo

```cpp
salida.clear();
salida.open(ARCHIVO.c_str());   // sin modo: el normal (ios::out), que vacia el archivo

for(i = 0; i < n; i++){
    salida << historico[i].FechaRegistro.Dia << " " << historico[i].FechaRegistro.Mes << " "
           << historico[i].FechaRegistro.Anio << " " << historico[i].Temperatura << endl;
}
salida.close();
```

Aquí se usa **a propósito** lo que en el ejercicio 1 había que evitar: abrir con el modo
normal, que **vacía** el archivo. Ya no es peligroso, porque todo su contenido está en
el arreglo. El `for` vuelve a escribir los `n` registros, en el mismo orden y con el
mismo formato con el que se escribieron (`dia mes anio temperatura`, separados por
espacios), así que las opciones 2 y 3 los siguen leyendo igual.

| Si al reescribir se abriera con... | El archivo de 8 renglones quedaría con |
|---|---|
| Modo normal (`ios::out`) ✅ | 8 renglones: los mismos, con la corrección |
| `ios::app` ❌ | 16 renglones: los 8 viejos (con el error) y debajo los 8 nuevos |

El `for` va hasta `n`, no hasta `MAX_REGISTROS`: las posiciones de `n` en adelante
nunca se llenaron y tienen basura.

### Por qué Agregar no usa el arreglo

Para **agregar** no hace falta cargar nada: `ios::app` escribe al final y lo anterior no
se toca. Cargar, modificar y reescribir solo se necesita cuando hay que cambiar algo que
**ya está** en el archivo. Usar el ciclo de 4.10 también para agregar funcionaría, pero
sería más trabajo para obtener lo mismo, y además limitaría el histórico a 100 renglones.

## Casos de prueba

Probados el 2 nov 2026 en macOS, compilando con `g++ -std=c++98 -Wall -Wextra` y con
`-std=c++17` (sin advertencias, mismas salidas en ambos). "Histórico de ejemplo" es el
del [ejercicio 2](../ejercicio-2-consulta-historico/README.md#antes-de-correrlo-la-carpeta-datos).
Se supone que en los campos numéricos el usuario escribe números (enteros en el `#` y
en la opción).

| # | Caso | Entrada | Salida esperada | Resultado |
|---|---|---|---|---|
| 1 | Corrección normal | Histórico de ejemplo; opción 3: `#` 2, temperatura 21.5; después opción 2 | La tabla y el archivo muestran 21.5 en el renglón 2; los otros 7 renglones no cambian | ✅ |
| 2 | `#` fuera de rango | Opción 3: `#` 0, luego 9, luego 2 | Error dos veces; acepta 2 | ✅ |
| 3 | Temperatura fuera de rango | Temperatura 60, luego -20, luego 21.5 | Error dos veces; acepta 21.5 | ✅ |
| 4 | Límites del `#` y de la temperatura | Opción 3: `#` 8 (el último), temperatura -10 | Se corrige el último renglón con -10 | ✅ |
| 5 | Agregar y luego corregir lo agregado | Después del caso 4: opción 1 (4, 11, 2026, 10); opción 3: `#` 9, temperatura 50 | La tabla muestra 9 registros; el renglón 9 queda con 50 | ✅ |
| 6 | Archivo vacío | `datos/` sin archivo; opción 3 | "El historico esta vacio: no hay nada que corregir"; no pide `#` | ✅ |
| 7 | Arreglo exactamente lleno | Archivo con 100 renglones; opción 3: `#` 100, temperatura 0 | Se corrige; el archivo queda con 100 renglones y solo cambia el último | ✅ |
| 8 | Más renglones de los que caben | Archivo con 101 renglones; opción 3 | "El historico tiene 101 registros y solo caben 100"; el archivo queda **idéntico** | ✅ |

### Limitaciones conocidas

1. **Solo se corrige la temperatura**, no la fecha. Corregir la fecha seguiría los
   mismos tres pasos, con la validación de día, mes y año.
2. **No se puede borrar un renglón.** Se podría hacer en el paso 3: escribir todos los
   registros **menos** ese.
3. **Capacidad de 100 registros** para corregir (un poco más de tres meses de datos
   diarios). Agregar y Ver no tienen límite; para corregir un histórico más grande hay
   que aumentar `MAX_REGISTROS`.
4. **Si el programa se interrumpe** justo entre vaciar el archivo y terminar de
   escribirlo (un apagón, por ejemplo), el histórico se pierde. Los programas
   profesionales escriben primero un archivo nuevo y después lo cambian por el viejo;
   eso queda fuera del curso.
5. Las de los ejercicios 1 y 2: el día se valida del 1 al 31 en cualquier mes, no se
   revisan fechas repetidas y un renglón mal escrito a mano detiene la lectura (en la
   corrección, los renglones posteriores a ese **se perderían** al reescribir).

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 2 nov 2026 | Primera versión: el programa del ejercicio 1 con la opción Ver del ejercicio 2 y la opción Corregir, que carga el archivo en un arreglo de `struct Registro`, modifica una temperatura y reescribe el archivo completo. | Tema 4.10: actualizar un archivo secuencial juntando archivos con los arreglos de structs de la Etapa III. |
| 2 nov 2026 | El menú pasó de `if`/`else if` a `switch`; `entrada` y `salida` se declaran arriba de `main` y se abren a mano con `clear()` + `open()` + `close()`. | Preferencia del curso por `switch` en los menús; sin `clear()`, en C++98 una segunda carga en la misma ejecución no leería nada. |
