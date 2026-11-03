# PIA — Pruebas de tiempo de carga web

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 13 — Rangel Robles Donovan Antonio

## Historia de usuario

**Como** líder de un equipo de desarrollo web, **quiero** que las páginas que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada página se volvió un registro dentro de un arreglo de
structs, y ahora las páginas se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se prueban como máximo **8 páginas** del sitio.
- De cada página se registra su **nombre**, una sola palabra sin espacios (por ejemplo `inicio`), y su **fecha de publicación**: la fecha en que la página se publicó en el sitio, con día, mes y año. **No puede haber dos páginas con el mismo nombre.**
- Cada página se prueba **5 veces**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Un tiempo de carga es válido si está entre **0 y 60 segundos**.
- Una página es **rápida** si el **promedio** de sus 5 pruebas es **menor o igual a 3 segundos**; si no, es **lenta**.
- Todas las páginas se guardan en el archivo **`paginas.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
PRUEBAS DE CARGA DEL SITIO WEB

1.- Alta de una pagina
2.- Buscar una pagina
3.- Cambiar los datos de una pagina
4.- Desplegar paginas
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las páginas de `paginas.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide el nombre; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de publicación y los 5 datos, muestra su promedio y su
  clasificación, y **agrega** la página al final de `paginas.txt`.
- **Opción 2 — Buscar:** pide el nombre y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el nombre; si existe, muestra sus datos actuales, pide sus
  5 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `paginas.txt` completo. El nombre y la fecha de publicación no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las páginas, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas páginas hay, el **promedio de tiempo de carga del sitio** (el
  promedio de los promedios de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las páginas que ya están registradas. Crea el archivo **`paginas.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
inicio 18 3 2020 1.5 2 1.8 2.2 2.5
catalogo 6 9 2022 3.5 4 2.8 5.2 4.5
carrito 25 3 2024 3 3 3 3 3
pagos 12 12 2023 2.5 3.5 3 4 3
contacto 4 7 2025 0.5 1 0.8 1.2 1.5
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `inicio 18 3 2020 1.5 2 1.8 2.2 2.5` | 2.00 s | Rapida |
| 2 | `catalogo 6 9 2022 3.5 4 2.8 5.2 4.5` | 4.00 s | Lenta |
| 3 | `carrito 25 3 2024 3 3 3 3 3` | 3.00 s | Rapida |
| 4 | `pagos 12 12 2023 2.5 3.5 3 4 3` | 3.20 s | Lenta |
| 5 | `contacto 4 7 2025 0.5 1 0.8 1.2 1.5` | 1.00 s | Rapida |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 páginas:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Pagina {
    string nombre;
    Fecha publicacion;        // struct anidado: fecha de publicación
    double tiempos[PRUEBAS];  // los 5 datos de cada página
    double promedioTiempo;    // el promedio de los 5 datos
};

Pagina paginas[MAX_PAGINAS];
int n;    // cuantas páginas hay en el arreglo
```

**En el archivo**, un renglón por página, con los campos separados por un espacio:

```
nombre dia mes anio tiempos[0] tiempos[1] tiempos[2] tiempos[3] tiempos[4]
```

Por ejemplo, `inicio 18 3 2020 1.5 2 1.8 2.2 2.5` es la página `inicio`, con fecha de publicación 18/3/2020 y
datos 1.5, 2, 1.8, 2.2, 2.5.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioTiempo`, y se guarda en el campo `promedioTiempo`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_PAGINAS && entrada >> paginas[n].nombre)`; dentro del `while` se leen la fecha y los 5 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaPagina` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarPaginas(Pagina paginas[])` | Abre `paginas.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada una y regresa cuántas cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarPaginas(Pagina paginas[], int n)` | **Reescribe** `paginas.txt` completo con las `n` páginas del arreglo. Regresa cuántas escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Pagina paginas[], int n, string nombre)` | Regresa la posición de la página con ese nombre, o -1 si no está | No |
| `double calcularPromedioTiempo(double tiempos[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarPagina(double promedioTiempo)` | Regresa `"Rapida"` o `"Lenta"` (la misma de tu Evidencia 3.2) | No |
| `int altaPagina(Pagina paginas[], int n)` | **Opción 1.** Registra una página nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarPagina(Pagina paginas[], int n)` | **Opción 2.** Busca una página y muestra todos sus datos | Sí |
| `void cambiarPagina(Pagina paginas[], int n)` | **Opción 3.** Cambia los datos de una página y reescribe el archivo | Sí |
| `void desplegarPaginas(Pagina paginas[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Pagina paginas[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaPagina` y `cambiarPagina` usan `buscarPosicion` y `calcularPromedioTiempo`, y `cargarPaginas` usa
`calcularPromedioTiempo`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Pagina` con los campos
      `nombre` (`string`), `publicacion` (`Fecha`), `tiempos` (arreglo `double` de 5) y `promedioTiempo` (`double`).
- [ ] Las páginas se guardan en un arreglo de structs `Pagina paginas[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por página (5), los límites de
      un dato (0 y 60), los del año (2015 y 2026), el límite de
      la clasificación (3) y el nombre del archivo (`"paginas.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarPaginas`, `guardarPaginas`, `buscarPosicion`, `calcularPromedioTiempo` y `clasificarPagina`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioTiempo` y se guarda en `promedioTiempo`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todas las páginas del archivo y avisa cuántas. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 páginas, aunque el archivo tenga más renglones: `n < MAX_PAGINAS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos de la página cambiada.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 páginas, avisa que el registro está lleno y no pide nada; si el
      nombre ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 60 s. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la página (nombre, fecha de publicación, los 5 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el nombre no existe; si existe, muestra los datos actuales, pide los
      5 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por página, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas páginas hay, el promedio de tiempo de carga del sitio y cuántas hay de cada
      clasificación.
- [ ] Si no hay páginas registradas, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 paginas de paginas.txt

PRUEBAS DE CARGA DEL SITIO WEB

1.- Alta de una pagina
2.- Buscar una pagina
3.- Cambiar los datos de una pagina
4.- Desplegar paginas
5.- Resumen general
6.- Salir

Opcion: 4

PAGINAS REGISTRADAS

Nombre     Fecha            P1    P2    P3    P4    P5   Promedio
inicio     18/3/2020      1.50  2.00  1.80  2.20  2.50       2.00   Rapida
catalogo   6/9/2022       3.50  4.00  2.80  5.20  4.50       4.00   Lenta
carrito    25/3/2024      3.00  3.00  3.00  3.00  3.00       3.00   Rapida
pagos      12/12/2023     2.50  3.50  3.00  4.00  3.00       3.20   Lenta
contacto   4/7/2025       0.50  1.00  0.80  1.20  1.50       1.00   Rapida
```

Alta con nombre repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE PAGINA
  Nombre: carrito
  ERROR! Ya existe una pagina con ese nombre

Opcion: 1

ALTA DE PAGINA
  Nombre: blog
  Fecha de publicacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 19
    Mes: 3
    Anio: 2020
  Pruebas
    Prueba 1: 3
    Prueba 2: 75
    ERROR! El dato debe estar entre 0 y 60 s
    Prueba 2: 3
    Prueba 3: 2.3
    Prueba 4: 3.7
    Prueba 5: 3.5

Promedio: 3.10 s -> Lenta
Pagina agregada a paginas.txt
```

Búsqueda:

```
Opcion: 2
Nombre a buscar: catalogo

Nombre: catalogo
Fecha de publicacion: 6/9/2022
Pruebas: P1 3.50, P2 4.00, P3 2.80, P4 5.20, P5 4.50
Promedio: 4.00 s -> Lenta
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA PAGINA
  Nombre: inicio

  Datos actuales: P1 1.50, P2 2.00, P3 1.80, P4 2.20, P5 2.50  (Promedio 2.00 s, Rapida)
  Datos nuevos
    Prueba 1: 3.5
    Prueba 2: 4
    Prueba 3: 2.8
    Prueba 4: 5.2
    Prueba 5: 4.5

Promedio: 4.00 s -> Lenta
Se reescribio paginas.txt con 6 paginas
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Paginas registradas: 6
Promedio de tiempo de carga del sitio: 3.05 s
Rapida: 2
Lenta: 4
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `paginas.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `paginas.txt` en la carpeta | `Se cargaron 0 paginas`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay páginas registradas; la 2 y la 3 no piden el nombre |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `blog`, 19/3/2020, datos 3, 3, 2.3, 3.7, 3.5 | Promedio 3.10 s → Lenta; aparece `paginas.txt` con un solo renglón: `blog 19 3 2020 3 3 2.3 3.7 3.5` |
| 4 | Carga del archivo inicial | Borrar `paginas.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 paginas` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `inicio` 2.00 (Rapida); `catalogo` 4.00 (Lenta); `carrito` 3.00 (Rapida); `pagos` 3.20 (Lenta); `contacto` 1.00 (Rapida) |
| 6 | Búsqueda encontrada | Opción 2, `catalogo` | Todos sus datos: 6/9/2022; 3.50, 4.00, 2.80, 5.20, 4.50; promedio 4.00 s → Lenta |
| 7 | Búsqueda no encontrada | Opción 2, `ofertas` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `CATALOGO` | Aviso de que no se encontró: `CATALOGO` y `catalogo` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 páginas; promedio de tiempo de carga del sitio: 2.64 s; Rapida: 3; Lenta: 2 |
| 10 | Nombre repetido | Opción 1, `carrito` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `blog`: día 0 y 32, mes 13, año 2014 y 2027, un dato de 75 y de -2; después 19/3/2020 y datos 3, 3, 2.3, 3.7, 3.5 | Error en cada dato no válido y lo vuelve a pedir; promedio 3.10 s → Lenta |
| 12 | El alta agrega al final | Abrir `paginas.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `blog 19 3 2020 3 3 2.3 3.7 3.5` |
| 13 | Cambio de página que no existe | Opción 3, `ofertas` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `inicio`; un dato de 75; después 3.5, 4, 2.8, 5.2, 4.5 | Muestra sus datos actuales; error con 75 y vuelve a pedir esa misma prueba; nuevo promedio 4.00 s → Lenta |
| 15 | El cambio reescribe el archivo | Abrir `paginas.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `inicio 18 3 2020 3.5 4 2.8 5.2 4.5` |
| 16 | Resumen después de los cambios | Opción 5 | 6 páginas; promedio de tiempo de carga del sitio: 3.05 s; Rapida: 2; Lenta: 4 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 paginas`; la tabla muestra los 6, con `inicio` ya cambiada y `blog` al final |
| 18 | Registro lleno | Opción 1 con `ayuda`, 7/9/2022, datos 3.5, 3, 4, 3, 2.5 (3.20, Lenta) y `perfil`, 26/3/2024, datos 1, 0.8, 1.2, 1.5, 0.5 (1.00, Rapida); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el nombre |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `paginas.txt` (10 en total) y correr el programa | `Se cargaron 8 paginas`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Pruebas de tiempo de carga web)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `paginas.txt` abierto en el Bloc de notas:

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
| Buscar por nombre | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
