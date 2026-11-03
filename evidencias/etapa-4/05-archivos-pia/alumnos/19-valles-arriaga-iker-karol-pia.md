# PIA — Tiempo de espera por caja

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 19 — Valles Arriaga Iker Karol

## Historia de usuario

**Como** gerente de un supermercado, **quiero** que las cajas que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada caja se volvió un registro dentro de un arreglo de
structs, y ahora las cajas se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- El supermercado tiene como máximo **8 cajas**.
- De cada caja se registra su **clave**, una sola palabra sin espacios (por ejemplo `CJ1`), y su **fecha de instalación**: la fecha en que se instaló la terminal de cobro de la caja, con día, mes y año. **No puede haber dos cajas con la misma clave.**
- En cada caja se mide la espera de **5 clientes**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Un tiempo de espera es válido si está entre **0 y 120 minutos**.
- Una caja tiene **espera aceptable** si el **promedio** de sus 5 clientes es **menor o igual a 10 minutos**; si no, tiene **espera excesiva**.
- Todas las cajas se guardan en el archivo **`cajas.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
TIEMPO DE ESPERA EN CAJAS

1.- Alta de una caja
2.- Buscar una caja
3.- Cambiar los datos de una caja
4.- Desplegar cajas
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las cajas de `cajas.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de instalación y los 5 datos, muestra su promedio y su
  clasificación, y **agrega** la caja al final de `cajas.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  5 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `cajas.txt` completo. La clave y la fecha de instalación no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las cajas, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas cajas hay, el **promedio de tiempo de espera del supermercado** (el
  promedio de los promedios de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las cajas que ya están registradas. Crea el archivo **`cajas.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
CJ1 26 8 2021 5 8 6.5 9 4.5
CJ2 2 3 2023 12 15 9 18 11
CJ3 14 8 2024 10 10 10 10 10
CJ4 10 11 2019 14 12 16 10 13
CJ5 19 5 2025 20 25 11 9 15
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `CJ1 26 8 2021 5 8 6.5 9 4.5` | 6.60 min | Espera aceptable |
| 2 | `CJ2 2 3 2023 12 15 9 18 11` | 13.00 min | Espera excesiva |
| 3 | `CJ3 14 8 2024 10 10 10 10 10` | 10.00 min | Espera aceptable |
| 4 | `CJ4 10 11 2019 14 12 16 10 13` | 13.00 min | Espera excesiva |
| 5 | `CJ5 19 5 2025 20 25 11 9 15` | 16.00 min | Espera excesiva |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 cajas:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Caja {
    string clave;
    Fecha instalacion;         // struct anidado: fecha de instalación
    double esperas[CLIENTES];  // los 5 datos de cada caja
    double promedioEspera;     // el promedio de los 5 datos
};

Caja cajas[MAX_CAJAS];
int n;    // cuantas cajas hay en el arreglo
```

**En el archivo**, un renglón por caja, con los campos separados por un espacio:

```
clave dia mes anio esperas[0] esperas[1] esperas[2] esperas[3] esperas[4]
```

Por ejemplo, `CJ1 26 8 2021 5 8 6.5 9 4.5` es la caja `CJ1`, con fecha de instalación 26/8/2021 y
datos 5, 8, 6.5, 9, 4.5.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioEspera`, y se guarda en el campo `promedioEspera`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_CAJAS && entrada >> cajas[n].clave)`; dentro del `while` se leen la fecha y los 5 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaCaja` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarCajas(Caja cajas[])` | Abre `cajas.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada una y regresa cuántas cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarCajas(Caja cajas[], int n)` | **Reescribe** `cajas.txt` completo con las `n` cajas del arreglo. Regresa cuántas escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Caja cajas[], int n, string clave)` | Regresa la posición de la caja con esa clave, o -1 si no está | No |
| `double calcularPromedioEspera(double esperas[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarEspera(double promedioEspera)` | Regresa `"Espera aceptable"` o `"Espera excesiva"` (la misma de tu Evidencia 3.2) | No |
| `int altaCaja(Caja cajas[], int n)` | **Opción 1.** Registra una caja nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarCaja(Caja cajas[], int n)` | **Opción 2.** Busca una caja y muestra todos sus datos | Sí |
| `void cambiarCaja(Caja cajas[], int n)` | **Opción 3.** Cambia los datos de una caja y reescribe el archivo | Sí |
| `void desplegarCajas(Caja cajas[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Caja cajas[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaCaja` y `cambiarCaja` usan `buscarPosicion` y `calcularPromedioEspera`, y `cargarCajas` usa
`calcularPromedioEspera`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Caja` con los campos
      `clave` (`string`), `instalacion` (`Fecha`), `esperas` (arreglo `double` de 5) y `promedioEspera` (`double`).
- [ ] Las cajas se guardan en un arreglo de structs `Caja cajas[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por caja (5), los límites de
      un dato (0 y 120), los del año (2015 y 2026), el límite de
      la clasificación (10) y el nombre del archivo (`"cajas.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarCajas`, `guardarCajas`, `buscarPosicion`, `calcularPromedioEspera` y `clasificarEspera`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioEspera` y se guarda en `promedioEspera`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todas las cajas del archivo y avisa cuántas. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 cajas, aunque el archivo tenga más renglones: `n < MAX_CAJAS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos de la caja cambiada.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 cajas, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 120 min. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la caja (clave, fecha de instalación, los 5 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      5 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por caja, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas cajas hay, el promedio de tiempo de espera del supermercado y cuántas hay de cada
      clasificación.
- [ ] Si no hay cajas registradas, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 cajas de cajas.txt

TIEMPO DE ESPERA EN CAJAS

1.- Alta de una caja
2.- Buscar una caja
3.- Cambiar los datos de una caja
4.- Desplegar cajas
5.- Resumen general
6.- Salir

Opcion: 4

CAJAS REGISTRADAS

Clave   Fecha             C1     C2     C3     C4     C5   Promedio
CJ1     26/8/2021       5.00   8.00   6.50   9.00   4.50       6.60   Espera aceptable
CJ2     2/3/2023       12.00  15.00   9.00  18.00  11.00      13.00   Espera excesiva
CJ3     14/8/2024      10.00  10.00  10.00  10.00  10.00      10.00   Espera aceptable
CJ4     10/11/2019     14.00  12.00  16.00  10.00  13.00      13.00   Espera excesiva
CJ5     19/5/2025      20.00  25.00  11.00   9.00  15.00      16.00   Espera excesiva
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE CAJA
  Clave: CJ3
  ERROR! Ya existe una caja con esa clave

Opcion: 1

ALTA DE CAJA
  Clave: CJ6
  Fecha de instalacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 27
    Mes: 8
    Anio: 2021
  Clientes
    Cliente 1: 8.5
    Cliente 2: 150
    ERROR! El dato debe estar entre 0 y 120 min
    Cliente 2: 11.5
    Cliente 3: 7.75
    Cliente 4: 13.5
    Cliente 5: 7.75

Promedio: 9.80 min -> Espera aceptable
Caja agregada a cajas.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: CJ2

Clave: CJ2
Fecha de instalacion: 2/3/2023
Clientes: C1 12.00, C2 15.00, C3 9.00, C4 18.00, C5 11.00
Promedio: 13.00 min -> Espera excesiva
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA CAJA
  Clave: CJ1

  Datos actuales: C1 5.00, C2 8.00, C3 6.50, C4 9.00, C5 4.50  (Promedio 6.60 min, Espera aceptable)
  Datos nuevos
    Cliente 1: 12
    Cliente 2: 15
    Cliente 3: 9
    Cliente 4: 18
    Cliente 5: 11

Promedio: 13.00 min -> Espera excesiva
Se reescribio cajas.txt con 6 cajas
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Cajas registradas: 6
Promedio de tiempo de espera del supermercado: 12.47 min
Espera aceptable: 2
Espera excesiva: 4
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `cajas.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `cajas.txt` en la carpeta | `Se cargaron 0 cajas`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay cajas registradas; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `CJ6`, 27/8/2021, datos 8.5, 11.5, 7.75, 13.5, 7.75 | Promedio 9.80 min → Espera aceptable; aparece `cajas.txt` con un solo renglón: `CJ6 27 8 2021 8.5 11.5 7.75 13.5 7.75` |
| 4 | Carga del archivo inicial | Borrar `cajas.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 cajas` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `CJ1` 6.60 (Espera aceptable); `CJ2` 13.00 (Espera excesiva); `CJ3` 10.00 (Espera aceptable); `CJ4` 13.00 (Espera excesiva); `CJ5` 16.00 (Espera excesiva) |
| 6 | Búsqueda encontrada | Opción 2, `CJ2` | Todos sus datos: 2/3/2023; 12.00, 15.00, 9.00, 18.00, 11.00; promedio 13.00 min → Espera excesiva |
| 7 | Búsqueda no encontrada | Opción 2, `CJ9` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `cj2` | Aviso de que no se encontró: `cj2` y `CJ2` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 cajas; promedio de tiempo de espera del supermercado: 11.72 min; Espera aceptable: 2; Espera excesiva: 3 |
| 10 | Clave repetida | Opción 1, `CJ3` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `CJ6`: día 0 y 32, mes 13, año 2014 y 2027, un dato de 150 y de -2; después 27/8/2021 y datos 8.5, 11.5, 7.75, 13.5, 7.75 | Error en cada dato no válido y lo vuelve a pedir; promedio 9.80 min → Espera aceptable |
| 12 | El alta agrega al final | Abrir `cajas.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `CJ6 27 8 2021 8.5 11.5 7.75 13.5 7.75` |
| 13 | Cambio de caja que no existe | Opción 3, `CJ9` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `CJ1`; un dato de 150; después 12, 15, 9, 18, 11 | Muestra sus datos actuales; error con 150 y vuelve a pedir ese mismo cliente; nuevo promedio 13.00 min → Espera excesiva |
| 15 | El cambio reescribe el archivo | Abrir `cajas.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `CJ1 26 8 2021 12 15 9 18 11` |
| 16 | Resumen después de los cambios | Opción 5 | 6 cajas; promedio de tiempo de espera del supermercado: 12.47 min; Espera aceptable: 2; Espera excesiva: 4 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 cajas`; la tabla muestra los 6, con `CJ1` ya cambiada y `CJ6` al final |
| 18 | Registro lleno | Opción 1 con `CJ7`, 3/3/2023, datos 12, 16, 10, 13, 14 (13.00, Espera excesiva) y `CJ8`, 15/8/2024, datos 25, 11, 9, 15, 20 (16.00, Espera excesiva); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `cajas.txt` (10 en total) y correr el programa | `Se cargaron 8 cajas`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Tiempo de espera por caja)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `cajas.txt` abierto en el Bloc de notas:

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
