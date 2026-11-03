# PIA — Filtro de temperatura en un evento

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 03 — Flores Hidalgo Carolina

## Historia de usuario

**Como** encargado de la entrada de un concierto, **quiero** que los asistentes que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada asistente se volvió un registro dentro de un arreglo de
structs, y ahora los asistentes se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se registran como máximo **8 asistentes** por fila de revisión.
- De cada asistente se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Valeria`), y su **fecha de nacimiento**: la fecha de nacimiento que aparece en su boleto, con día, mes y año. **No puede haber dos asistentes con el mismo nombre.**
- A cada asistente se le toma la temperatura **3 veces**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **1940 y 2026**.
- Una toma es válida si está entre **34 y 42 °C**.
- Un asistente **puede pasar** si el **promedio** de sus 3 tomas es **menor o igual a 37.5 °C**; si no, es **febril y no puede pasar**.
- Todos los asistentes se guardan en el archivo **`asistentes.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
FILTRO DE ACCESO AL EVENTO

1.- Alta de un asistente
2.- Buscar un asistente
3.- Cambiar los datos de un asistente
4.- Desplegar asistentes
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los asistentes de `asistentes.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide el nombre; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de nacimiento y los 3 datos, muestra su promedio y su
  clasificación, y **agrega** el asistente al final de `asistentes.txt`.
- **Opción 2 — Buscar:** pide el nombre y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el nombre; si existe, muestra sus datos actuales, pide sus
  3 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `asistentes.txt` completo. El nombre y la fecha de nacimiento no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los asistentes, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos asistentes hay, el **promedio de temperatura de los asistentes** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los asistentes que ya están registrados. Crea el archivo **`asistentes.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
Valeria 4 5 2001 36.5 36.7 36.6
Jorge 19 1 1998 38.2 38.5 37.9
Paola 27 5 2006 37.5 37.5 37.5
Ruben 11 10 1985 37 37.5 38.5
Elena 2 12 1993 36.2 36.4 36.3
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `Valeria 4 5 2001 36.5 36.7 36.6` | 36.60 °C | Puede pasar |
| 2 | `Jorge 19 1 1998 38.2 38.5 37.9` | 38.20 °C | Febril, no puede pasar |
| 3 | `Paola 27 5 2006 37.5 37.5 37.5` | 37.50 °C | Puede pasar |
| 4 | `Ruben 11 10 1985 37 37.5 38.5` | 37.67 °C | Febril, no puede pasar |
| 5 | `Elena 2 12 1993 36.2 36.4 36.3` | 36.30 °C | Puede pasar |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 asistentes:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Asistente {
    string nombre;
    Fecha nacimiento;            // struct anidado: fecha de nacimiento
    double temperaturas[TOMAS];  // los 3 datos de cada asistente
    double promedioTemperatura;  // el promedio de los 3 datos
};

Asistente asistentes[MAX_ASISTENTES];
int n;    // cuantos asistentes hay en el arreglo
```

**En el archivo**, un renglón por asistente, con los campos separados por un espacio:

```
nombre dia mes anio temperaturas[0] temperaturas[1] temperaturas[2]
```

Por ejemplo, `Valeria 4 5 2001 36.5 36.7 36.6` es el asistente `Valeria`, con fecha de nacimiento 4/5/2001 y
datos 36.5, 36.7, 36.6.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioTemperatura`, y se guarda en el campo `promedioTemperatura`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_ASISTENTES && entrada >> asistentes[n].nombre)`; dentro del `while` se leen la fecha y los 3 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaAsistente` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarAsistentes(Asistente asistentes[])` | Abre `asistentes.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarAsistentes(Asistente asistentes[], int n)` | **Reescribe** `asistentes.txt` completo con los `n` asistentes del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Asistente asistentes[], int n, string nombre)` | Regresa la posición del asistente con ese nombre, o -1 si no está | No |
| `double calcularPromedioTemperatura(double temperaturas[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarTemperatura(double promedioTemperatura)` | Regresa `"Puede pasar"` o `"Febril, no puede pasar"` (la misma de tu Evidencia 3.2) | No |
| `int altaAsistente(Asistente asistentes[], int n)` | **Opción 1.** Registra un asistente nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarAsistente(Asistente asistentes[], int n)` | **Opción 2.** Busca un asistente y muestra todos sus datos | Sí |
| `void cambiarAsistente(Asistente asistentes[], int n)` | **Opción 3.** Cambia los datos de un asistente y reescribe el archivo | Sí |
| `void desplegarAsistentes(Asistente asistentes[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Asistente asistentes[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaAsistente` y `cambiarAsistente` usan `buscarPosicion` y `calcularPromedioTemperatura`, y `cargarAsistentes` usa
`calcularPromedioTemperatura`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Asistente` con los campos
      `nombre` (`string`), `nacimiento` (`Fecha`), `temperaturas` (arreglo `double` de 3) y `promedioTemperatura` (`double`).
- [ ] Los asistentes se guardan en un arreglo de structs `Asistente asistentes[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por asistente (3), los límites de
      un dato (34 y 42), los del año (1940 y 2026), el límite de
      la clasificación (37.5) y el nombre del archivo (`"asistentes.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarAsistentes`, `guardarAsistentes`, `buscarPosicion`, `calcularPromedioTemperatura` y `clasificarTemperatura`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioTemperatura` y se guarda en `promedioTemperatura`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los asistentes del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 asistentes, aunque el archivo tenga más renglones: `n < MAX_ASISTENTES` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del asistente cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 asistentes, avisa que el registro está lleno y no pide nada; si el
      nombre ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      34 y 42 °C. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del asistente (nombre, fecha de nacimiento, los 3 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el nombre no existe; si existe, muestra los datos actuales, pide los
      3 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por asistente, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos asistentes hay, el promedio de temperatura de los asistentes y cuántos hay de cada
      clasificación.
- [ ] Si no hay asistentes registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 asistentes de asistentes.txt

FILTRO DE ACCESO AL EVENTO

1.- Alta de un asistente
2.- Buscar un asistente
3.- Cambiar los datos de un asistente
4.- Desplegar asistentes
5.- Resumen general
6.- Salir

Opcion: 4

ASISTENTES REGISTRADOS

Nombre    Fecha             T1     T2     T3   Promedio
Valeria   4/5/2001       36.50  36.70  36.60      36.60   Puede pasar
Jorge     19/1/1998      38.20  38.50  37.90      38.20   Febril, no puede pasar
Paola     27/5/2006      37.50  37.50  37.50      37.50   Puede pasar
Ruben     11/10/1985     37.00  37.50  38.50      37.67   Febril, no puede pasar
Elena     2/12/1993      36.20  36.40  36.30      36.30   Puede pasar
```

Alta con nombre repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE ASISTENTE
  Nombre: Paola
  ERROR! Ya existe un asistente con ese nombre

Opcion: 1

ALTA DE ASISTENTE
  Nombre: Andres
  Fecha de nacimiento
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 5
    Mes: 5
    Anio: 2001
  Tomas
    Toma 1: 37.35
    Toma 2: 45
    ERROR! El dato debe estar entre 34 y 42 °C
    Toma 2: 37.6
    Toma 3: 37.25

Promedio: 37.40 °C -> Puede pasar
Asistente agregado a asistentes.txt
```

Búsqueda:

```
Opcion: 2
Nombre a buscar: Jorge

Nombre: Jorge
Fecha de nacimiento: 19/1/1998
Tomas: T1 38.20, T2 38.50, T3 37.90
Promedio: 38.20 °C -> Febril, no puede pasar
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN ASISTENTE
  Nombre: Valeria

  Datos actuales: T1 36.50, T2 36.70, T3 36.60  (Promedio 36.60 °C, Puede pasar)
  Datos nuevos
    Toma 1: 38.2
    Toma 2: 38.5
    Toma 3: 37.9

Promedio: 38.20 °C -> Febril, no puede pasar
Se reescribio asistentes.txt con 6 asistentes
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Asistentes registrados: 6
Promedio de temperatura de los asistentes: 37.54 °C
Puede pasar: 3
Febril, no puede pasar: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `asistentes.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `asistentes.txt` en la carpeta | `Se cargaron 0 asistentes`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay asistentes registrados; la 2 y la 3 no piden el nombre |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `Andres`, 5/5/2001, datos 37.35, 37.6, 37.25 | Promedio 37.40 °C → Puede pasar; aparece `asistentes.txt` con un solo renglón: `Andres 5 5 2001 37.35 37.6 37.25` |
| 4 | Carga del archivo inicial | Borrar `asistentes.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 asistentes` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `Valeria` 36.60 (Puede pasar); `Jorge` 38.20 (Febril, no puede pasar); `Paola` 37.50 (Puede pasar); `Ruben` 37.67 (Febril, no puede pasar); `Elena` 36.30 (Puede pasar) |
| 6 | Búsqueda encontrada | Opción 2, `Jorge` | Todos sus datos: 19/1/1998; 38.20, 38.50, 37.90; promedio 38.20 °C → Febril, no puede pasar |
| 7 | Búsqueda no encontrada | Opción 2, `Pedro` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `jorge` | Aviso de que no se encontró: `jorge` y `Jorge` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 asistentes; promedio de temperatura de los asistentes: 37.25 °C; Puede pasar: 3; Febril, no puede pasar: 2 |
| 10 | Nombre repetido | Opción 1, `Paola` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `Andres`: día 0 y 32, mes 13, año 1939 y 2027, un dato de 45 y de 30; después 5/5/2001 y datos 37.35, 37.6, 37.25 | Error en cada dato no válido y lo vuelve a pedir; promedio 37.40 °C → Puede pasar |
| 12 | El alta agrega al final | Abrir `asistentes.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `Andres 5 5 2001 37.35 37.6 37.25` |
| 13 | Cambio de asistente que no existe | Opción 3, `Pedro` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `Valeria`; un dato de 45; después 38.2, 38.5, 37.9 | Muestra sus datos actuales; error con 45 y vuelve a pedir esa misma toma; nuevo promedio 38.20 °C → Febril, no puede pasar |
| 15 | El cambio reescribe el archivo | Abrir `asistentes.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `Valeria 4 5 2001 38.2 38.5 37.9` |
| 16 | Resumen después de los cambios | Opción 5 | 6 asistentes; promedio de temperatura de los asistentes: 37.54 °C; Puede pasar: 3; Febril, no puede pasar: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 asistentes`; la tabla muestra los 6, con `Valeria` ya cambiado y `Andres` al final |
| 18 | Registro lleno | Opción 1 con `Lorena`, 20/1/1998, datos 37.5, 38.5, 37 (37.67, Febril, no puede pasar) y `Camila`, 28/5/2006, datos 36.4, 36.3, 36.2 (36.30, Puede pasar); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el nombre |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `asistentes.txt` (10 en total) y correr el programa | `Se cargaron 8 asistentes`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Filtro de temperatura en un evento)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `asistentes.txt` abierto en el Bloc de notas:

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
