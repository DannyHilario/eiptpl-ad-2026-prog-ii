# PIA — Control de calidad por lotes

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 02 — Espinosa Saucedo Angel Xavier

## Historia de usuario

**Como** inspector de calidad de una fábrica de piezas metálicas, **quiero** que los lotes que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada lote se volvió un registro dentro de un arreglo de
structs, y ahora los lotes se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- La fábrica registra como máximo **8 lotes** por turno.
- De cada lote se registra su **clave**, una sola palabra sin espacios (por ejemplo `L101`), y su **fecha de producción**: la fecha en que se fabricó el lote, con día, mes y año. **No puede haber dos lotes con la misma clave.**
- De cada lote se revisan **4 piezas** de muestra.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- La desviación de una pieza es válida si está entre **0 y 50 gramos**.
- Un lote está **dentro de tolerancia** si el **promedio** de la desviación de sus 4 piezas es **menor o igual a 5 g**; si no, está **fuera de tolerancia**.
- Todos los lotes se guardan en el archivo **`lotes.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
CONTROL DE CALIDAD POR LOTES

1.- Alta de un lote
2.- Buscar un lote
3.- Cambiar los datos de un lote
4.- Desplegar lotes
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los lotes de `lotes.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de producción y los 4 datos, muestra su promedio y su
  clasificación, y **agrega** el lote al final de `lotes.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  4 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `lotes.txt` completo. La clave y la fecha de producción no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los lotes, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos lotes hay, el **promedio de desviación de todos los lotes** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los lotes que ya están registrados. Crea el archivo **`lotes.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
L101 3 2 2026 1.5 2 3 0.5
L102 17 5 2025 6 8 4.5 9.5
L103 21 2 2025 5 5 5 5
L104 8 9 2026 2 3.5 1 4.5
L105 12 7 2024 9 7 6 8
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `L101 3 2 2026 1.5 2 3 0.5` | 1.75 g | Dentro de tolerancia |
| 2 | `L102 17 5 2025 6 8 4.5 9.5` | 7.00 g | Fuera de tolerancia |
| 3 | `L103 21 2 2025 5 5 5 5` | 5.00 g | Dentro de tolerancia |
| 4 | `L104 8 9 2026 2 3.5 1 4.5` | 2.75 g | Dentro de tolerancia |
| 5 | `L105 12 7 2024 9 7 6 8` | 7.50 g | Fuera de tolerancia |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 lotes:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Lote {
    string clave;
    Fecha produccion;             // struct anidado: fecha de producción
    double desviaciones[PIEZAS];  // los 4 datos de cada lote
    double promedioDesviacion;    // el promedio de los 4 datos
};

Lote lotes[MAX_LOTES];
int n;    // cuantos lotes hay en el arreglo
```

**En el archivo**, un renglón por lote, con los campos separados por un espacio:

```
clave dia mes anio desviaciones[0] desviaciones[1] desviaciones[2] desviaciones[3]
```

Por ejemplo, `L101 3 2 2026 1.5 2 3 0.5` es el lote `L101`, con fecha de producción 3/2/2026 y
datos 1.5, 2, 3, 0.5.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioDesviacion`, y se guarda en el campo `promedioDesviacion`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_LOTES && entrada >> lotes[n].clave)`; dentro del `while` se leen la fecha y los 4 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaLote` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarLotes(Lote lotes[])` | Abre `lotes.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarLotes(Lote lotes[], int n)` | **Reescribe** `lotes.txt` completo con los `n` lotes del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Lote lotes[], int n, string clave)` | Regresa la posición del lote con esa clave, o -1 si no está | No |
| `double calcularPromedioDesviacion(double desviaciones[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarLote(double promedioDesviacion)` | Regresa `"Dentro de tolerancia"` o `"Fuera de tolerancia"` (la misma de tu Evidencia 3.2) | No |
| `int altaLote(Lote lotes[], int n)` | **Opción 1.** Registra un lote nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarLote(Lote lotes[], int n)` | **Opción 2.** Busca un lote y muestra todos sus datos | Sí |
| `void cambiarLote(Lote lotes[], int n)` | **Opción 3.** Cambia los datos de un lote y reescribe el archivo | Sí |
| `void desplegarLotes(Lote lotes[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Lote lotes[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaLote` y `cambiarLote` usan `buscarPosicion` y `calcularPromedioDesviacion`, y `cargarLotes` usa
`calcularPromedioDesviacion`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Lote` con los campos
      `clave` (`string`), `produccion` (`Fecha`), `desviaciones` (arreglo `double` de 4) y `promedioDesviacion` (`double`).
- [ ] Los lotes se guardan en un arreglo de structs `Lote lotes[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por lote (4), los límites de
      un dato (0 y 50), los del año (2020 y 2026), el límite de
      la clasificación (5) y el nombre del archivo (`"lotes.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarLotes`, `guardarLotes`, `buscarPosicion`, `calcularPromedioDesviacion` y `clasificarLote`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioDesviacion` y se guarda en `promedioDesviacion`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los lotes del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 lotes, aunque el archivo tenga más renglones: `n < MAX_LOTES` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del lote cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 lotes, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 50 g. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del lote (clave, fecha de producción, los 4 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      4 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por lote, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos lotes hay, el promedio de desviación de todos los lotes y cuántos hay de cada
      clasificación.
- [ ] Si no hay lotes registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 lotes de lotes.txt

CONTROL DE CALIDAD POR LOTES

1.- Alta de un lote
2.- Buscar un lote
3.- Cambiar los datos de un lote
4.- Desplegar lotes
5.- Resumen general
6.- Salir

Opcion: 4

LOTES REGISTRADOS

Clave   Fecha           P1    P2    P3    P4   Promedio
L101    3/2/2026      1.50  2.00  3.00  0.50       1.75   Dentro de tolerancia
L102    17/5/2025     6.00  8.00  4.50  9.50       7.00   Fuera de tolerancia
L103    21/2/2025     5.00  5.00  5.00  5.00       5.00   Dentro de tolerancia
L104    8/9/2026      2.00  3.50  1.00  4.50       2.75   Dentro de tolerancia
L105    12/7/2024     9.00  7.00  6.00  8.00       7.50   Fuera de tolerancia
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE LOTE
  Clave: L103
  ERROR! Ya existe un lote con esa clave

Opcion: 1

ALTA DE LOTE
  Clave: L106
  Fecha de produccion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 4
    Mes: 2
    Anio: 2026
  Piezas
    Pieza 1: 3.75
    Pieza 2: 60
    ERROR! El dato debe estar entre 0 y 50 g
    Pieza 2: 5
    Pieza 3: 3.75
    Pieza 4: 5

Promedio: 4.38 g -> Dentro de tolerancia
Lote agregado a lotes.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: L102

Clave: L102
Fecha de produccion: 17/5/2025
Piezas: P1 6.00, P2 8.00, P3 4.50, P4 9.50
Promedio: 7.00 g -> Fuera de tolerancia
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN LOTE
  Clave: L101

  Datos actuales: P1 1.50, P2 2.00, P3 3.00, P4 0.50  (Promedio 1.75 g, Dentro de tolerancia)
  Datos nuevos
    Pieza 1: 6
    Pieza 2: 8
    Pieza 3: 4.5
    Pieza 4: 9.5

Promedio: 7.00 g -> Fuera de tolerancia
Se reescribio lotes.txt con 6 lotes
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Lotes registrados: 6
Promedio de desviacion de todos los lotes: 5.60 g
Dentro de tolerancia: 3
Fuera de tolerancia: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `lotes.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `lotes.txt` en la carpeta | `Se cargaron 0 lotes`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay lotes registrados; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `L106`, 4/2/2026, datos 3.75, 5, 3.75, 5 | Promedio 4.38 g → Dentro de tolerancia; aparece `lotes.txt` con un solo renglón: `L106 4 2 2026 3.75 5 3.75 5` |
| 4 | Carga del archivo inicial | Borrar `lotes.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 lotes` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `L101` 1.75 (Dentro de tolerancia); `L102` 7.00 (Fuera de tolerancia); `L103` 5.00 (Dentro de tolerancia); `L104` 2.75 (Dentro de tolerancia); `L105` 7.50 (Fuera de tolerancia) |
| 6 | Búsqueda encontrada | Opción 2, `L102` | Todos sus datos: 17/5/2025; 6.00, 8.00, 4.50, 9.50; promedio 7.00 g → Fuera de tolerancia |
| 7 | Búsqueda no encontrada | Opción 2, `L109` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `l102` | Aviso de que no se encontró: `l102` y `L102` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 lotes; promedio de desviación de todos los lotes: 4.80 g; Dentro de tolerancia: 3; Fuera de tolerancia: 2 |
| 10 | Clave repetida | Opción 1, `L103` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `L106`: día 0 y 32, mes 13, año 2019 y 2027, un dato de 60 y de -1; después 4/2/2026 y datos 3.75, 5, 3.75, 5 | Error en cada dato no válido y lo vuelve a pedir; promedio 4.38 g → Dentro de tolerancia |
| 12 | El alta agrega al final | Abrir `lotes.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `L106 4 2 2026 3.75 5 3.75 5` |
| 13 | Cambio de lote que no existe | Opción 3, `L109` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `L101`; un dato de 60; después 6, 8, 4.5, 9.5 | Muestra sus datos actuales; error con 60 y vuelve a pedir esa misma pieza; nuevo promedio 7.00 g → Fuera de tolerancia |
| 15 | El cambio reescribe el archivo | Abrir `lotes.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `L101 3 2 2026 6 8 4.5 9.5` |
| 16 | Resumen después de los cambios | Opción 5 | 6 lotes; promedio de desviación de todos los lotes: 5.60 g; Dentro de tolerancia: 3; Fuera de tolerancia: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 lotes`; la tabla muestra los 6, con `L101` ya cambiado y `L106` al final |
| 18 | Registro lleno | Opción 1 con `L107`, 18/5/2025, datos 3.5, 1, 4.5, 2 (2.75, Dentro de tolerancia) y `L108`, 22/2/2025, datos 7, 6, 8, 9 (7.50, Fuera de tolerancia); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `lotes.txt` (10 en total) y correr el programa | `Se cargaron 8 lotes`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Control de calidad por lotes)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `lotes.txt` abierto en el Bloc de notas:

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
