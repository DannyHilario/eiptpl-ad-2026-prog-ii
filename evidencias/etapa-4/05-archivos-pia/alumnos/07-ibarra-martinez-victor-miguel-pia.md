# PIA — Monitoreo de ruido industrial

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 07 — Ibarra Martinez Victor Miguel

## Historia de usuario

**Como** supervisor de seguridad de una planta industrial, **quiero** que las máquinas que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada máquina se volvió un registro dentro de un arreglo de
structs, y ahora las máquinas se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- La planta tiene como máximo **8 máquinas**.
- De cada máquina se registra su **clave**, una sola palabra sin espacios (por ejemplo `MQ01`), y su **fecha de instalación**: la fecha en que se instaló la máquina en la planta, con día, mes y año. **No puede haber dos máquinas con la misma clave.**
- Cada máquina se mide **4 veces** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2000 y 2026**.
- Una lectura es válida si está entre **0 y 140 dB**.
- Una máquina está **dentro de la norma** si el **promedio** de sus 4 lecturas es **menor o igual a 85 dB**; si no, **excede la norma**.
- Todas las máquinas se guardan en el archivo **`maquinas.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
MONITOREO DE RUIDO INDUSTRIAL

1.- Alta de una maquina
2.- Buscar una maquina
3.- Cambiar los datos de una maquina
4.- Desplegar maquinas
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las máquinas de `maquinas.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de instalación y los 4 datos, muestra su promedio y su
  clasificación, y **agrega** la máquina al final de `maquinas.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  4 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `maquinas.txt` completo. La clave y la fecha de instalación no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las máquinas, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas máquinas hay, el **promedio general de ruido de la planta** (el
  promedio de los promedios de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las máquinas que ya están registradas. Crea el archivo **`maquinas.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
MQ01 12 9 2015 82 88 79 85
MQ02 3 3 2020 90 92 87 95
MQ03 28 9 2022 85 85 85 85
MQ04 6 12 2010 70 75 72 79
MQ05 19 5 2018 100 98 104 94
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `MQ01 12 9 2015 82 88 79 85` | 83.50 dB | Dentro de la norma |
| 2 | `MQ02 3 3 2020 90 92 87 95` | 91.00 dB | Excede la norma |
| 3 | `MQ03 28 9 2022 85 85 85 85` | 85.00 dB | Dentro de la norma |
| 4 | `MQ04 6 12 2010 70 75 72 79` | 74.00 dB | Dentro de la norma |
| 5 | `MQ05 19 5 2018 100 98 104 94` | 99.00 dB | Excede la norma |

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
    Fecha instalacion;          // struct anidado: fecha de instalación
    double lecturas[LECTURAS];  // los 4 datos de cada máquina
    double promedioRuido;       // el promedio de los 4 datos
};

Maquina maquinas[MAX_MAQUINAS];
int n;    // cuantas máquinas hay en el arreglo
```

**En el archivo**, un renglón por máquina, con los campos separados por un espacio:

```
clave dia mes anio lecturas[0] lecturas[1] lecturas[2] lecturas[3]
```

Por ejemplo, `MQ01 12 9 2015 82 88 79 85` es la máquina `MQ01`, con fecha de instalación 12/9/2015 y
datos 82, 88, 79, 85.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioRuido`, y se guarda en el campo `promedioRuido`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_MAQUINAS && entrada >> maquinas[n].clave)`; dentro del `while` se leen la fecha y los 4 datos |
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
| `double calcularPromedioRuido(double lecturas[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarRuido(double promedioRuido)` | Regresa `"Dentro de la norma"` o `"Excede la norma"` (la misma de tu Evidencia 3.2) | No |
| `int altaMaquina(Maquina maquinas[], int n)` | **Opción 1.** Registra una máquina nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarMaquina(Maquina maquinas[], int n)` | **Opción 2.** Busca una máquina y muestra todos sus datos | Sí |
| `void cambiarMaquina(Maquina maquinas[], int n)` | **Opción 3.** Cambia los datos de una máquina y reescribe el archivo | Sí |
| `void desplegarMaquinas(Maquina maquinas[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Maquina maquinas[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaMaquina` y `cambiarMaquina` usan `buscarPosicion` y `calcularPromedioRuido`, y `cargarMaquinas` usa
`calcularPromedioRuido`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Maquina` con los campos
      `clave` (`string`), `instalacion` (`Fecha`), `lecturas` (arreglo `double` de 4) y `promedioRuido` (`double`).
- [ ] Las máquinas se guardan en un arreglo de structs `Maquina maquinas[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por máquina (4), los límites de
      un dato (0 y 140), los del año (2000 y 2026), el límite de
      la clasificación (85) y el nombre del archivo (`"maquinas.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarMaquinas`, `guardarMaquinas`, `buscarPosicion`, `calcularPromedioRuido` y `clasificarRuido`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioRuido` y se guarda en `promedioRuido`; las opciones 2, 4
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
      0 y 140 dB. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la máquina (clave, fecha de instalación, los 4 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      4 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por máquina, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas máquinas hay, el promedio general de ruido de la planta y cuántas hay de cada
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

MONITOREO DE RUIDO INDUSTRIAL

1.- Alta de una maquina
2.- Buscar una maquina
3.- Cambiar los datos de una maquina
4.- Desplegar maquinas
5.- Resumen general
6.- Salir

Opcion: 4

MAQUINAS REGISTRADAS

Clave   Fecha             L1      L2      L3      L4   Promedio
MQ01    12/9/2015      82.00   88.00   79.00   85.00      83.50   Dentro de la norma
MQ02    3/3/2020       90.00   92.00   87.00   95.00      91.00   Excede la norma
MQ03    28/9/2022      85.00   85.00   85.00   85.00      85.00   Dentro de la norma
MQ04    6/12/2010      70.00   75.00   72.00   79.00      74.00   Dentro de la norma
MQ05    19/5/2018     100.00   98.00  104.00   94.00      99.00   Excede la norma
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE MAQUINA
  Clave: MQ03
  ERROR! Ya existe una maquina con esa clave

Opcion: 1

ALTA DE MAQUINA
  Clave: MQ06
  Fecha de instalacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 13
    Mes: 9
    Anio: 2015
  Lecturas
    Lectura 1: 86
    Lectura 2: 150
    ERROR! El dato debe estar entre 0 y 140 dB
    Lectura 2: 90
    Lectura 3: 83
    Lectura 4: 90

Promedio: 87.25 dB -> Excede la norma
Maquina agregada a maquinas.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: MQ02

Clave: MQ02
Fecha de instalacion: 3/3/2020
Lecturas: L1 90.00, L2 92.00, L3 87.00, L4 95.00
Promedio: 91.00 dB -> Excede la norma
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA MAQUINA
  Clave: MQ01

  Datos actuales: L1 82.00, L2 88.00, L3 79.00, L4 85.00  (Promedio 83.50 dB, Dentro de la norma)
  Datos nuevos
    Lectura 1: 90
    Lectura 2: 92
    Lectura 3: 87
    Lectura 4: 95

Promedio: 91.00 dB -> Excede la norma
Se reescribio maquinas.txt con 6 maquinas
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Maquinas registradas: 6
Promedio general de ruido de la planta: 87.88 dB
Dentro de la norma: 2
Excede la norma: 4
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
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `MQ06`, 13/9/2015, datos 86, 90, 83, 90 | Promedio 87.25 dB → Excede la norma; aparece `maquinas.txt` con un solo renglón: `MQ06 13 9 2015 86 90 83 90` |
| 4 | Carga del archivo inicial | Borrar `maquinas.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 maquinas` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `MQ01` 83.50 (Dentro de la norma); `MQ02` 91.00 (Excede la norma); `MQ03` 85.00 (Dentro de la norma); `MQ04` 74.00 (Dentro de la norma); `MQ05` 99.00 (Excede la norma) |
| 6 | Búsqueda encontrada | Opción 2, `MQ02` | Todos sus datos: 3/3/2020; 90.00, 92.00, 87.00, 95.00; promedio 91.00 dB → Excede la norma |
| 7 | Búsqueda no encontrada | Opción 2, `MQ09` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `mq02` | Aviso de que no se encontró: `mq02` y `MQ02` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 máquinas; promedio general de ruido de la planta: 86.50 dB; Dentro de la norma: 3; Excede la norma: 2 |
| 10 | Clave repetida | Opción 1, `MQ03` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `MQ06`: día 0 y 32, mes 13, año 1999 y 2027, un dato de 150 y de -5; después 13/9/2015 y datos 86, 90, 83, 90 | Error en cada dato no válido y lo vuelve a pedir; promedio 87.25 dB → Excede la norma |
| 12 | El alta agrega al final | Abrir `maquinas.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `MQ06 13 9 2015 86 90 83 90` |
| 13 | Cambio de máquina que no existe | Opción 3, `MQ09` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `MQ01`; un dato de 150; después 90, 92, 87, 95 | Muestra sus datos actuales; error con 150 y vuelve a pedir esa misma lectura; nuevo promedio 91.00 dB → Excede la norma |
| 15 | El cambio reescribe el archivo | Abrir `maquinas.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `MQ01 12 9 2015 90 92 87 95` |
| 16 | Resumen después de los cambios | Opción 5 | 6 máquinas; promedio general de ruido de la planta: 87.88 dB; Dentro de la norma: 2; Excede la norma: 4 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 maquinas`; la tabla muestra los 6, con `MQ01` ya cambiada y `MQ06` al final |
| 18 | Registro lleno | Opción 1 con `MQ07`, 4/3/2020, datos 75, 72, 79, 70 (74.00, Dentro de la norma) y `MQ08`, 28/9/2022, datos 98, 104, 94, 100 (99.00, Excede la norma); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
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
    Nombre completo, número y contexto (Monitoreo de ruido industrial)

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
