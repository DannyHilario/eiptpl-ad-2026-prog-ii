# PIA — Consumo eléctrico mensual por semanas

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 05 — Hernandez Lopez Jose

## Historia de usuario

**Como** revisor de una compañía de luz, **quiero** que las casas que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada casa se volvió un registro dentro de un arreglo de
structs, y ahora las casas se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se revisan como máximo **8 casas** de la colonia.
- De cada casa se registra su **número de medidor**, una sola palabra sin espacios (por ejemplo `M2041`), y su **fecha de contratación**: la fecha en que se contrató el servicio de luz, con día, mes y año. **No puede haber dos casas con el mismo número de medidor.**
- De cada casa se registra el consumo de **4 semanas**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **1990 y 2026**.
- El consumo de una semana es válido si está entre **0 y 200 kWh**.
- Una casa tiene **consumo normal** si el **total** de sus 4 semanas es **menor o igual a 300 kWh**; si no, tiene **alto consumo**.
- Todas las casas se guardan en el archivo **`casas.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
CONSUMO ELECTRICO DE LA COLONIA

1.- Alta de una casa
2.- Buscar una casa
3.- Cambiar los datos de una casa
4.- Desplegar casas
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las casas de `casas.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide el número de medidor; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de contratación y los 4 datos, muestra su total y su
  clasificación, y **agrega** la casa al final de `casas.txt`.
- **Opción 2 — Buscar:** pide el número de medidor y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el número de medidor; si existe, muestra sus datos actuales, pide sus
  4 datos **nuevos**, recalcula su total, muestra su nueva clasificación y **reescribe**
  `casas.txt` completo. El número de medidor y la fecha de contratación no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las casas, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas casas hay, el **promedio de consumo por casa** (el
  promedio de los totales de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las casas que ya están registradas. Crea el archivo **`casas.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
M2041 10 7 2010 60.5 72 58 65.5
M2042 25 3 2019 90 85.5 110 95
M2043 5 7 2022 75 75 75 75
M2044 16 11 2005 40 55 50 45
M2045 1 2 2015 120 95 88 102
```

Así se lee cada renglón:

| # | Renglón | Total | Clasificación |
|---|---|---|---|
| 1 | `M2041 10 7 2010 60.5 72 58 65.5` | 256.00 kWh | Consumo normal |
| 2 | `M2042 25 3 2019 90 85.5 110 95` | 380.50 kWh | Alto consumo |
| 3 | `M2043 5 7 2022 75 75 75 75` | 300.00 kWh | Consumo normal |
| 4 | `M2044 16 11 2005 40 55 50 45` | 190.00 kWh | Consumo normal |
| 5 | `M2045 1 2 2015 120 95 88 102` | 405.00 kWh | Alto consumo |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 casas:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Casa {
    string medidor;
    Fecha contratacion;        // struct anidado: fecha de contratación
    double consumos[SEMANAS];  // los 4 datos de cada casa
    double totalConsumo;       // la suma de los 4 datos
};

Casa casas[MAX_CASAS];
int n;    // cuantas casas hay en el arreglo
```

**En el archivo**, un renglón por casa, con los campos separados por un espacio:

```
medidor dia mes anio consumos[0] consumos[1] consumos[2] consumos[3]
```

Por ejemplo, `M2041 10 7 2010 60.5 72 58 65.5` es la casa `M2041`, con fecha de contratación 10/7/2010 y
datos 60.5, 72, 58, 65.5.

**El total no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularTotalConsumo`, y se guarda en el campo `totalConsumo`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_CASAS && entrada >> casas[n].medidor)`; dentro del `while` se leen la fecha y los 4 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaCasa` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarCasas(Casa casas[])` | Abre `casas.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el total de cada una y regresa cuántas cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarCasas(Casa casas[], int n)` | **Reescribe** `casas.txt` completo con las `n` casas del arreglo. Regresa cuántas escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Casa casas[], int n, string medidor)` | Regresa la posición de la casa con ese número de medidor, o -1 si no está | No |
| `double calcularTotalConsumo(double consumos[], int cantidad)` | Regresa la suma de los datos del arreglo | No |
| `string clasificarConsumo(double totalConsumo)` | Regresa `"Consumo normal"` o `"Alto consumo"` (la misma de tu Evidencia 3.2) | No |
| `int altaCasa(Casa casas[], int n)` | **Opción 1.** Registra una casa nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarCasa(Casa casas[], int n)` | **Opción 2.** Busca una casa y muestra todos sus datos | Sí |
| `void cambiarCasa(Casa casas[], int n)` | **Opción 3.** Cambia los datos de una casa y reescribe el archivo | Sí |
| `void desplegarCasas(Casa casas[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Casa casas[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaCasa` y `cambiarCasa` usan `buscarPosicion` y `calcularTotalConsumo`, y `cargarCasas` usa
`calcularTotalConsumo`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Casa` con los campos
      `medidor` (`string`), `contratacion` (`Fecha`), `consumos` (arreglo `double` de 4) y `totalConsumo` (`double`).
- [ ] Las casas se guardan en un arreglo de structs `Casa casas[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por casa (4), los límites de
      un dato (0 y 200), los del año (1990 y 2026), el límite de
      la clasificación (300) y el nombre del archivo (`"casas.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarCasas`, `guardarCasas`, `buscarPosicion`, `calcularTotalConsumo` y `clasificarConsumo`
      no usan `cin` ni `cout`.
- [ ] El total se calcula **solo** con `calcularTotalConsumo` y se guarda en `totalConsumo`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todas las casas del archivo y avisa cuántas. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 casas, aunque el archivo tenga más renglones: `n < MAX_CASAS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos de la casa cambiada.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 casas, avisa que el registro está lleno y no pide nada; si el
      número de medidor ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 200 kWh. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la casa (número de medidor, fecha de contratación, los 4 datos, total y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el número de medidor no existe; si existe, muestra los datos actuales, pide los
      4 nuevos, recalcula el total y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por casa, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas casas hay, el promedio de consumo por casa y cuántas hay de cada
      clasificación.
- [ ] Si no hay casas registradas, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 casas de casas.txt

CONSUMO ELECTRICO DE LA COLONIA

1.- Alta de una casa
2.- Buscar una casa
3.- Cambiar los datos de una casa
4.- Desplegar casas
5.- Resumen general
6.- Salir

Opcion: 4

CASAS REGISTRADAS

Numero   Fecha              S1      S2      S3      S4    Total
M2041    10/7/2010       60.50   72.00   58.00   65.50   256.00   Consumo normal
M2042    25/3/2019       90.00   85.50  110.00   95.00   380.50   Alto consumo
M2043    5/7/2022        75.00   75.00   75.00   75.00   300.00   Consumo normal
M2044    16/11/2005      40.00   55.00   50.00   45.00   190.00   Consumo normal
M2045    1/2/2015       120.00   95.00   88.00  102.00   405.00   Alto consumo
```

Alta con número de medidor repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE CASA
  Numero de medidor: M2043
  ERROR! Ya existe una casa con ese numero de medidor

Opcion: 1

ALTA DE CASA
  Numero de medidor: M2046
  Fecha de contratacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 11
    Mes: 7
    Anio: 2010
  Semanas
    Semana 1: 75.25
    Semana 2: 250
    ERROR! El dato debe estar entre 0 y 200 kWh
    Semana 2: 78.75
    Semana 3: 84
    Semana 4: 80.25

Total: 318.25 kWh -> Alto consumo
Casa agregada a casas.txt
```

Búsqueda:

```
Opcion: 2
Numero de medidor a buscar: M2042

Numero de medidor: M2042
Fecha de contratacion: 25/3/2019
Semanas: S1 90.00, S2 85.50, S3 110.00, S4 95.00
Total: 380.50 kWh -> Alto consumo
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA CASA
  Numero de medidor: M2041

  Datos actuales: S1 60.50, S2 72.00, S3 58.00, S4 65.50  (Total 256.00 kWh, Consumo normal)
  Datos nuevos
    Semana 1: 90
    Semana 2: 85.5
    Semana 3: 110
    Semana 4: 95

Total: 380.50 kWh -> Alto consumo
Se reescribio casas.txt con 6 casas
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Casas registradas: 6
Promedio de consumo por casa: 329.04 kWh
Consumo normal: 2
Alto consumo: 4
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `casas.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `casas.txt` en la carpeta | `Se cargaron 0 casas`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay casas registradas; la 2 y la 3 no piden el número de medidor |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `M2046`, 11/7/2010, datos 75.25, 78.75, 84, 80.25 | Total 318.25 kWh → Alto consumo; aparece `casas.txt` con un solo renglón: `M2046 11 7 2010 75.25 78.75 84 80.25` |
| 4 | Carga del archivo inicial | Borrar `casas.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 casas` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `M2041` 256.00 (Consumo normal); `M2042` 380.50 (Alto consumo); `M2043` 300.00 (Consumo normal); `M2044` 190.00 (Consumo normal); `M2045` 405.00 (Alto consumo) |
| 6 | Búsqueda encontrada | Opción 2, `M2042` | Todos sus datos: 25/3/2019; 90.00, 85.50, 110.00, 95.00; total 380.50 kWh → Alto consumo |
| 7 | Búsqueda no encontrada | Opción 2, `M2049` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `m2042` | Aviso de que no se encontró: `m2042` y `M2042` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 casas; promedio de consumo por casa: 306.30 kWh; Consumo normal: 3; Alto consumo: 2 |
| 10 | Número de medidor repetido | Opción 1, `M2043` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `M2046`: día 0 y 32, mes 13, año 1989 y 2027, un dato de 250 y de -5; después 11/7/2010 y datos 75.25, 78.75, 84, 80.25 | Error en cada dato no válido y lo vuelve a pedir; total 318.25 kWh → Alto consumo |
| 12 | El alta agrega al final | Abrir `casas.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `M2046 11 7 2010 75.25 78.75 84 80.25` |
| 13 | Cambio de casa que no existe | Opción 3, `M2049` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `M2041`; un dato de 250; después 90, 85.5, 110, 95 | Muestra sus datos actuales; error con 250 y vuelve a pedir esa misma semana; nuevo total 380.50 kWh → Alto consumo |
| 15 | El cambio reescribe el archivo | Abrir `casas.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `M2041 10 7 2010 90 85.5 110 95` |
| 16 | Resumen después de los cambios | Opción 5 | 6 casas; promedio de consumo por casa: 329.04 kWh; Consumo normal: 2; Alto consumo: 4 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 casas`; la tabla muestra los 6, con `M2041` ya cambiada y `M2046` al final |
| 18 | Registro lleno | Opción 1 con `M2047`, 26/3/2019, datos 55, 50, 45, 40 (190.00, Consumo normal) y `M2048`, 6/7/2022, datos 95, 88, 102, 120 (405.00, Alto consumo); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el número de medidor |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `casas.txt` (10 en total) y correr el programa | `Se cargaron 8 casas`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Consumo electrico mensual por semanas)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `casas.txt` abierto en el Bloc de notas:

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
| Buscar por número de medidor | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
