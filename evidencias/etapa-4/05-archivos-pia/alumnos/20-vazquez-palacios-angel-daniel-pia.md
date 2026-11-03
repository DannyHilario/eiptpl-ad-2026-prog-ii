# PIA — Vibración de maquinaria industrial

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 20 — Vazquez Palacios Angel Daniel

## Historia de usuario

**Como** jefe de mantenimiento de una planta industrial, **quiero** que las máquinas que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada máquina se volvió un registro dentro de un arreglo de
structs, y ahora las máquinas se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- La planta tiene como máximo **8 máquinas** en monitoreo.
- De cada máquina se registra su **clave**, una sola palabra sin espacios (por ejemplo `CNC01`), y su **fecha de mantenimiento**: la fecha del último mantenimiento de la máquina, con día, mes y año. **No puede haber dos máquinas con la misma clave.**
- Cada máquina se mide **3 veces** por turno.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2018 y 2026**.
- Una lectura es válida si está entre **0 y 50 mm/s**.
- Una máquina está en **estado normal** si el **promedio** de sus 3 lecturas es **menor o igual a 4.5 mm/s**; si no, está en **estado de alerta**.
- Todas las máquinas se guardan en el archivo **`maquinas.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
MONITOREO DE VIBRACION

1.- Alta de una maquina
2.- Buscar una maquina
3.- Cambiar los datos de una maquina
4.- Desplegar maquinas
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las máquinas de `maquinas.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de mantenimiento y los 3 datos, muestra su promedio y su
  clasificación, y **agrega** la máquina al final de `maquinas.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  3 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `maquinas.txt` completo. La clave y la fecha de mantenimiento no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las máquinas, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas máquinas hay, el **promedio de vibración de la planta** (el
  promedio de los promedios de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las máquinas que ya están registradas. Crea el archivo **`maquinas.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
CNC01 5 7 2025 2.5 3 2
CNC02 18 2 2026 6 5.5 7
CNC03 22 7 2026 4.5 4.5 4.5
CNC04 9 10 2024 5 4 6
CNC05 30 4 2025 1.5 2 1
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `CNC01 5 7 2025 2.5 3 2` | 2.50 mm/s | Estado normal |
| 2 | `CNC02 18 2 2026 6 5.5 7` | 6.17 mm/s | Estado de alerta |
| 3 | `CNC03 22 7 2026 4.5 4.5 4.5` | 4.50 mm/s | Estado normal |
| 4 | `CNC04 9 10 2024 5 4 6` | 5.00 mm/s | Estado de alerta |
| 5 | `CNC05 30 4 2025 1.5 2 1` | 1.50 mm/s | Estado normal |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 máquinas:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Maquina {
    string clave;
    Fecha mantenimiento;           // struct anidado: fecha de mantenimiento
    double vibraciones[LECTURAS];  // los 3 datos de cada máquina
    double promedioVibracion;      // el promedio de los 3 datos
};

Maquina maquinas[MAX_MAQUINAS];
int n;    // cuantas máquinas hay en el arreglo
```

**En el archivo**, un renglón por máquina, con los campos separados por un espacio:

```
clave dia mes anio vibraciones[0] vibraciones[1] vibraciones[2]
```

Por ejemplo, `CNC01 5 7 2025 2.5 3 2` es la máquina `CNC01`, con fecha de mantenimiento 5/7/2025 y
datos 2.5, 3, 2.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioVibracion`, y se guarda en el campo `promedioVibracion`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_MAQUINAS && entrada >> maquinas[n].clave)`; dentro del `while` se leen la fecha y los 3 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaMaquina` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarMaquinas(Maquina maquinas[])` | Abre `maquinas.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada una y regresa cuántas cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarMaquinas(Maquina maquinas[], int n)` | **Reescribe** `maquinas.txt` completo con las `n` máquinas del arreglo. Regresa cuántas escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Maquina maquinas[], int n, string clave)` | Regresa la posición de la máquina con esa clave, o -1 si no está | No |
| `double calcularPromedioVibracion(double vibraciones[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarVibracion(double promedioVibracion)` | Regresa `"Estado normal"` o `"Estado de alerta"` (la misma de tu Evidencia 3.2) | No |
| `int altaMaquina(Maquina maquinas[], int n)` | **Opción 1.** Registra una máquina nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarMaquina(Maquina maquinas[], int n)` | **Opción 2.** Busca una máquina y muestra todos sus datos | Sí |
| `void cambiarMaquina(Maquina maquinas[], int n)` | **Opción 3.** Cambia los datos de una máquina y reescribe el archivo | Sí |
| `void desplegarMaquinas(Maquina maquinas[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Maquina maquinas[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaMaquina` y `cambiarMaquina` usan `buscarPosicion` y `calcularPromedioVibracion`, y `cargarMaquinas` usa
`calcularPromedioVibracion`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Maquina` con los campos
      `clave` (`string`), `mantenimiento` (`Fecha`), `vibraciones` (arreglo `double` de 3) y `promedioVibracion` (`double`).
- [ ] Las máquinas se guardan en un arreglo de structs `Maquina maquinas[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por máquina (3), los límites de
      un dato (0 y 50), los del año (2018 y 2026), el límite de
      la clasificación (4.5) y el nombre del archivo (`"maquinas.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarMaquinas`, `guardarMaquinas`, `buscarPosicion`, `calcularPromedioVibracion` y `clasificarVibracion`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioVibracion` y se guarda en `promedioVibracion`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todas las máquinas del archivo y avisa cuántas. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 máquinas, aunque el archivo tenga más renglones: `n < MAX_MAQUINAS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos de la máquina cambiada.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 máquinas, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 50 mm/s. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la máquina (clave, fecha de mantenimiento, los 3 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      3 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por máquina, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas máquinas hay, el promedio de vibración de la planta y cuántas hay de cada
      clasificación.
- [ ] Si no hay máquinas registradas, las opciones 2 a 5 muestran un aviso en lugar de pedir
      datos o de mostrar la tabla o el resumen.
- [ ] La opción del menú debe estar entre 1 y 6; si no, muestra un error y vuelve a mostrar el menú.
- [ ] Los números con decimales se muestran con 2 decimales.
- [ ] Los resultados coinciden con **todos** los casos de prueba.

**Documenta sus pruebas** ([bitácora en PDF](#bitácora-de-pruebas-pdf))

- [ ] Entregas el PDF con la estructura pedida: portada y los 20 casos.
- [ ] Cada uno de los 20 casos tiene su captura (y la del Bloc de notas en los casos 3, 4, 12, 15 y 19) y
      su tabla de resultado esperado, obtenido y si coincide.
- [ ] Las capturas son de **tu** programa: el profesor lo corre con los mismos datos y debe dar lo mismo.

**Sin el PDF, Habilidades queda en 3 como máximo**, aunque el código cumpla todo lo demás.

**Código fácil de seguir y leer**

- [ ] Nombres descriptivos y comentarios que expliquen cada función y cada parte del programa.
- [ ] Compila y se ejecuta sin errores en Dev-C++.

### Actitudes / Valores (2 puntos) — Entrega

- [ ] Subes **los mismos dos archivos** en NEXUS en los **dos** lugares: *"4.2 Evidencia de Aprendizaje 4: Programa"* y
      *"Producto Integrador de Aprendizaje · Programa"*, antes del **sábado 14 de noviembre de 2026 a las 10:00 p.m.**
- [ ] El código va en texto plano, con el nombre `PIA_ApellidoNombre.txt`, y la bitácora en
      `PIA_ApellidoNombre.pdf` (así debe verse: [ejemplo resuelto](../ejemplo-resuelto/README.md)).
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu código si se te pregunta.

## Ejemplo de ejecución

Al iniciar con el archivo inicial, y la opción 4:

```
Se cargaron 5 maquinas de maquinas.txt

MONITOREO DE VIBRACION

1.- Alta de una maquina
2.- Buscar una maquina
3.- Cambiar los datos de una maquina
4.- Desplegar maquinas
5.- Resumen general
6.- Salir

Opcion: 4

MAQUINAS REGISTRADAS

Clave   Fecha           L1    L2    L3   Promedio
CNC01   5/7/2025      2.50  3.00  2.00       2.50   Estado normal
CNC02   18/2/2026     6.00  5.50  7.00       6.17   Estado de alerta
CNC03   22/7/2026     4.50  4.50  4.50       4.50   Estado normal
CNC04   9/10/2024     5.00  4.00  6.00       5.00   Estado de alerta
CNC05   30/4/2025     1.50  2.00  1.00       1.50   Estado normal
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE MAQUINA
  Clave: CNC03
  ERROR! Ya existe una maquina con esa clave

Opcion: 1

ALTA DE MAQUINA
  Clave: CNC06
  Fecha de mantenimiento
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 6
    Mes: 7
    Anio: 2025
  Lecturas
    Lectura 1: 4.25
    Lectura 2: 60
    ERROR! El dato debe estar entre 0 y 50 mm/s
    Lectura 2: 4.25
    Lectura 3: 4.5

Promedio: 4.33 mm/s -> Estado normal
Maquina agregada a maquinas.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: CNC02

Clave: CNC02
Fecha de mantenimiento: 18/2/2026
Lecturas: L1 6.00, L2 5.50, L3 7.00
Promedio: 6.17 mm/s -> Estado de alerta
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA MAQUINA
  Clave: CNC01

  Datos actuales: L1 2.50, L2 3.00, L3 2.00  (Promedio 2.50 mm/s, Estado normal)
  Datos nuevos
    Lectura 1: 6
    Lectura 2: 5.5
    Lectura 3: 7

Promedio: 6.17 mm/s -> Estado de alerta
Se reescribio maquinas.txt con 6 maquinas
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Maquinas registradas: 6
Promedio de vibracion de la planta: 4.61 mm/s
Estado normal: 3
Estado de alerta: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `maquinas.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `maquinas.txt` en la carpeta | `Se cargaron 0 maquinas`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay máquinas registradas; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `CNC06`, 6/7/2025, datos 4.25, 4.25, 4.5 | Promedio 4.33 mm/s → Estado normal; aparece `maquinas.txt` con un solo renglón: `CNC06 6 7 2025 4.25 4.25 4.5` |
| 4 | Carga del archivo inicial | Borrar `maquinas.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 maquinas` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `CNC01` 2.50 (Estado normal); `CNC02` 6.17 (Estado de alerta); `CNC03` 4.50 (Estado normal); `CNC04` 5.00 (Estado de alerta); `CNC05` 1.50 (Estado normal) |
| 6 | Búsqueda encontrada | Opción 2, `CNC02` | Todos sus datos: 18/2/2026; 6.00, 5.50, 7.00; promedio 6.17 mm/s → Estado de alerta |
| 7 | Búsqueda no encontrada | Opción 2, `CNC09` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `cnc02` | Aviso de que no se encontró: `cnc02` y `CNC02` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 máquinas; promedio de vibración de la planta: 3.93 mm/s; Estado normal: 3; Estado de alerta: 2 |
| 10 | Clave repetida | Opción 1, `CNC03` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `CNC06`: día 0 y 32, mes 13, año 2017 y 2027, un dato de 60 y de -1; después 6/7/2025 y datos 4.25, 4.25, 4.5 | Error en cada dato no válido y lo vuelve a pedir; promedio 4.33 mm/s → Estado normal |
| 12 | El alta agrega al final | Abrir `maquinas.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `CNC06 6 7 2025 4.25 4.25 4.5` |
| 13 | Cambio de máquina que no existe | Opción 3, `CNC09` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `CNC01`; un dato de 60; después 6, 5.5, 7 | Muestra sus datos actuales; error con 60 y vuelve a pedir esa misma lectura; nuevo promedio 6.17 mm/s → Estado de alerta |
| 15 | El cambio reescribe el archivo | Abrir `maquinas.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `CNC01 5 7 2025 6 5.5 7` |
| 16 | Resumen después de los cambios | Opción 5 | 6 máquinas; promedio de vibración de la planta: 4.61 mm/s; Estado normal: 3; Estado de alerta: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 maquinas`; la tabla muestra los 6, con `CNC01` ya cambiada y `CNC06` al final |
| 18 | Registro lleno | Opción 1 con `CNC07`, 19/2/2026, datos 4, 6, 5 (5.00, Estado de alerta) y `CNC08`, 23/7/2026, datos 2, 1, 1.5 (1.50, Estado normal); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `maquinas.txt` (10 en total) y correr el programa | `Se cargaron 8 maquinas`; el programa no falla ni escribe fuera del arreglo |
| 20 | Opción inválida | Opción 0 o 7 | Error; vuelve a mostrar el menú |

## Bitácora de pruebas (PDF)

Además del código entregas un **PDF con las pruebas que tú corriste**: capturas de pantalla de
tu programa funcionando. El profesor también corre sus propias pruebas sobre tu código; la
bitácora demuestra que **tú** lo ejecutaste y comprobaste cada resultado.

**Mira el [ejemplo resuelto](../ejemplo-resuelto/README.md)**: una bitácora completa de un contexto que
no es de ningún alumno, con todas sus capturas ([en PDF](../ejemplo-resuelto/PIA_HilarioDaniel.pdf)).

**Las capturas son imágenes** de la ventana completa de la consola (o del Bloc de notas), con la
tecla Impr Pant o con la Herramienta Recortes (Windows + Shift + S). El texto copiado y pegado no
cuenta como captura.

**Estructura del PDF**, con estos títulos y en este orden:

```
Portada
    Nombre completo, número y contexto (Vibracion de maquinaria industrial)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `maquinas.txt` abierto en el Bloc de notas:

| Caso | Captura del Bloc de notas |
|---|---|
| 3 | El archivo que creó el alta: un solo renglón |
| 4 | El archivo inicial que creaste, con sus 5 renglones |
| 12 | Los 6 renglones después del alta |
| 15 | Los 6 renglones después del cambio |
| 19 | Los 10 renglones, con los 2 que agregaste a mano |

Cada apartado lleva su captura y debajo esta tabla:

| Resultado esperado | Resultado obtenido | ¿Coincide? |
|---|---|---|
| Lo que dice la columna *Salida esperada* | Lo que mostró tu programa | Sí / No |

Si un caso **no coincide**, pon "No" y explica qué salió distinto. Documentar con honestidad una
falla no te baja más de lo que ya baja la falla; poner "Sí" en algo que tu programa no hace, sí.

## Material de consulta

| Para… | Tema |
|---|---|
| Pasar el arreglo de structs a una función y regresar el nuevo `n` | [1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md) |
| Mostrar 2 decimales | [1.2 — `<iomanip>`](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar) |
| Buscar por clave | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
