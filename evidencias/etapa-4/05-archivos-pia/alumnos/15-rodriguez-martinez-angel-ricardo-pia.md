# PIA — Tiempos de entrega por repartidor

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

## Historia de usuario

**Como** gerente de operaciones de una empresa de paquetería, **quiero** que los repartidores que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada repartidor se volvió un registro dentro de un arreglo de
structs, y ahora los repartidores se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- La empresa tiene como máximo **8 repartidores**.
- De cada repartidor se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Ernesto`), y su **fecha de ingreso**: la fecha en que entró a trabajar a la paquetería, con día, mes y año. **No puede haber dos repartidores con el mismo nombre.**
- De cada repartidor se registran los días de entrega de sus últimos **5 envíos**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2010 y 2026**.
- Los días de entrega de un envío son válidos si están entre **0 y 30** (0 = se entregó el mismo día).
- Un repartidor entrega **a tiempo** si el **promedio** de sus 5 envíos es **menor o igual a 3 días**; si no, entrega **con retraso**.
- Todos los repartidores se guardan en el archivo **`repartidores.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
ENTREGAS DE PAQUETERIA

1.- Alta de un repartidor
2.- Buscar un repartidor
3.- Cambiar los datos de un repartidor
4.- Desplegar repartidores
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los repartidores de `repartidores.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide el nombre; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de ingreso y los 5 datos, muestra su promedio y su
  clasificación, y **agrega** el repartidor al final de `repartidores.txt`.
- **Opción 2 — Buscar:** pide el nombre y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el nombre; si existe, muestra sus datos actuales, pide sus
  5 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `repartidores.txt` completo. El nombre y la fecha de ingreso no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los repartidores, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos repartidores hay, el **promedio de días de entrega de la empresa** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los repartidores que ya están registrados. Crea el archivo **`repartidores.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
Ernesto 11 4 2021 2 1 3 2 2
Fabiola 29 8 2016 4 5 3 6 2
Gerardo 6 4 2024 3 3 3 3 3
Irma 13 1 2019 1 2 1 1 0
Noe 22 10 2025 5 4 6 3 7
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `Ernesto 11 4 2021 2 1 3 2 2` | 2.00 días | A tiempo |
| 2 | `Fabiola 29 8 2016 4 5 3 6 2` | 4.00 días | Con retraso |
| 3 | `Gerardo 6 4 2024 3 3 3 3 3` | 3.00 días | A tiempo |
| 4 | `Irma 13 1 2019 1 2 1 1 0` | 1.00 días | A tiempo |
| 5 | `Noe 22 10 2025 5 4 6 3 7` | 5.00 días | Con retraso |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 repartidores:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Repartidor {
    string nombre;
    Fecha ingreso;        // struct anidado: fecha de ingreso
    double dias[ENVIOS];  // los 5 datos de cada repartidor
    double promedioDias;  // el promedio de los 5 datos
};

Repartidor repartidores[MAX_REPARTIDORES];
int n;    // cuantos repartidores hay en el arreglo
```

**En el archivo**, un renglón por repartidor, con los campos separados por un espacio:

```
nombre dia mes anio dias[0] dias[1] dias[2] dias[3] dias[4]
```

Por ejemplo, `Ernesto 11 4 2021 2 1 3 2 2` es el repartidor `Ernesto`, con fecha de ingreso 11/4/2021 y
datos 2, 1, 3, 2, 2.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioDias`, y se guarda en el campo `promedioDias`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_REPARTIDORES && entrada >> repartidores[n].nombre)`; dentro del `while` se leen la fecha y los 5 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaRepartidor` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarRepartidores(Repartidor repartidores[])` | Abre `repartidores.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarRepartidores(Repartidor repartidores[], int n)` | **Reescribe** `repartidores.txt` completo con los `n` repartidores del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Repartidor repartidores[], int n, string nombre)` | Regresa la posición del repartidor con ese nombre, o -1 si no está | No |
| `double calcularPromedioDias(double dias[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarEntrega(double promedioDias)` | Regresa `"A tiempo"` o `"Con retraso"` (la misma de tu Evidencia 3.2) | No |
| `int altaRepartidor(Repartidor repartidores[], int n)` | **Opción 1.** Registra un repartidor nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarRepartidor(Repartidor repartidores[], int n)` | **Opción 2.** Busca un repartidor y muestra todos sus datos | Sí |
| `void cambiarRepartidor(Repartidor repartidores[], int n)` | **Opción 3.** Cambia los datos de un repartidor y reescribe el archivo | Sí |
| `void desplegarRepartidores(Repartidor repartidores[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Repartidor repartidores[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaRepartidor` y `cambiarRepartidor` usan `buscarPosicion` y `calcularPromedioDias`, y `cargarRepartidores` usa
`calcularPromedioDias`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Repartidor` con los campos
      `nombre` (`string`), `ingreso` (`Fecha`), `dias` (arreglo `double` de 5) y `promedioDias` (`double`).
- [ ] Los repartidores se guardan en un arreglo de structs `Repartidor repartidores[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por repartidor (5), los límites de
      un dato (0 y 30), los del año (2010 y 2026), el límite de
      la clasificación (3) y el nombre del archivo (`"repartidores.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarRepartidores`, `guardarRepartidores`, `buscarPosicion`, `calcularPromedioDias` y `clasificarEntrega`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioDias` y se guarda en `promedioDias`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los repartidores del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 repartidores, aunque el archivo tenga más renglones: `n < MAX_REPARTIDORES` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del repartidor cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 repartidores, avisa que el registro está lleno y no pide nada; si el
      nombre ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 30 días. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del repartidor (nombre, fecha de ingreso, los 5 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el nombre no existe; si existe, muestra los datos actuales, pide los
      5 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por repartidor, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos repartidores hay, el promedio de días de entrega de la empresa y cuántos hay de cada
      clasificación.
- [ ] Si no hay repartidores registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 repartidores de repartidores.txt

ENTREGAS DE PAQUETERIA

1.- Alta de un repartidor
2.- Buscar un repartidor
3.- Cambiar los datos de un repartidor
4.- Desplegar repartidores
5.- Resumen general
6.- Salir

Opcion: 4

REPARTIDORES REGISTRADOS

Nombre    Fecha            E1    E2    E3    E4    E5   Promedio
Ernesto   11/4/2021      2.00  1.00  3.00  2.00  2.00       2.00   A tiempo
Fabiola   29/8/2016      4.00  5.00  3.00  6.00  2.00       4.00   Con retraso
Gerardo   6/4/2024       3.00  3.00  3.00  3.00  3.00       3.00   A tiempo
Irma      13/1/2019      1.00  2.00  1.00  1.00  0.00       1.00   A tiempo
Noe       22/10/2025     5.00  4.00  6.00  3.00  7.00       5.00   Con retraso
```

Alta con nombre repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE REPARTIDOR
  Nombre: Gerardo
  ERROR! Ya existe un repartidor con ese nombre

Opcion: 1

ALTA DE REPARTIDOR
  Nombre: Rocio
  Fecha de ingreso
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 12
    Mes: 4
    Anio: 2021
  Envios
    Envio 1: 4
    Envio 2: 45
    ERROR! El dato debe estar entre 0 y 30 dias
    Envio 2: 3
    Envio 3: 3
    Envio 4: 4
    Envio 5: 2

Promedio: 3.20 dias -> Con retraso
Repartidor agregado a repartidores.txt
```

Búsqueda:

```
Opcion: 2
Nombre a buscar: Fabiola

Nombre: Fabiola
Fecha de ingreso: 29/8/2016
Envios: E1 4.00, E2 5.00, E3 3.00, E4 6.00, E5 2.00
Promedio: 4.00 dias -> Con retraso
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN REPARTIDOR
  Nombre: Ernesto

  Datos actuales: E1 2.00, E2 1.00, E3 3.00, E4 2.00, E5 2.00  (Promedio 2.00 dias, A tiempo)
  Datos nuevos
    Envio 1: 4
    Envio 2: 5
    Envio 3: 3
    Envio 4: 6
    Envio 5: 2

Promedio: 4.00 dias -> Con retraso
Se reescribio repartidores.txt con 6 repartidores
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Repartidores registrados: 6
Promedio de dias de entrega de la empresa: 3.37 dias
A tiempo: 2
Con retraso: 4
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `repartidores.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `repartidores.txt` en la carpeta | `Se cargaron 0 repartidores`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay repartidores registrados; la 2 y la 3 no piden el nombre |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `Rocio`, 12/4/2021, datos 4, 3, 3, 4, 2 | Promedio 3.20 días → Con retraso; aparece `repartidores.txt` con un solo renglón: `Rocio 12 4 2021 4 3 3 4 2` |
| 4 | Carga del archivo inicial | Borrar `repartidores.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 repartidores` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `Ernesto` 2.00 (A tiempo); `Fabiola` 4.00 (Con retraso); `Gerardo` 3.00 (A tiempo); `Irma` 1.00 (A tiempo); `Noe` 5.00 (Con retraso) |
| 6 | Búsqueda encontrada | Opción 2, `Fabiola` | Todos sus datos: 29/8/2016; 4.00, 5.00, 3.00, 6.00, 2.00; promedio 4.00 días → Con retraso |
| 7 | Búsqueda no encontrada | Opción 2, `Pedro` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `fabiola` | Aviso de que no se encontró: `fabiola` y `Fabiola` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 repartidores; promedio de días de entrega de la empresa: 3.00 días; A tiempo: 3; Con retraso: 2 |
| 10 | Nombre repetido | Opción 1, `Gerardo` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `Rocio`: día 0 y 32, mes 13, año 2009 y 2027, un dato de 45 y de -1; después 12/4/2021 y datos 4, 3, 3, 4, 2 | Error en cada dato no válido y lo vuelve a pedir; promedio 3.20 días → Con retraso |
| 12 | El alta agrega al final | Abrir `repartidores.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `Rocio 12 4 2021 4 3 3 4 2` |
| 13 | Cambio de repartidor que no existe | Opción 3, `Pedro` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `Ernesto`; un dato de 45; después 4, 5, 3, 6, 2 | Muestra sus datos actuales; error con 45 y vuelve a pedir ese mismo envío; nuevo promedio 4.00 días → Con retraso |
| 15 | El cambio reescribe el archivo | Abrir `repartidores.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `Ernesto 11 4 2021 4 5 3 6 2` |
| 16 | Resumen después de los cambios | Opción 5 | 6 repartidores; promedio de días de entrega de la empresa: 3.37 días; A tiempo: 2; Con retraso: 4 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 repartidores`; la tabla muestra los 6, con `Ernesto` ya cambiado y `Rocio` al final |
| 18 | Registro lleno | Opción 1 con `Saul`, 28/8/2016, datos 2, 1, 1, 0, 1 (1.00, A tiempo) y `Ximena`, 7/4/2024, datos 4, 6, 3, 7, 5 (5.00, Con retraso); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el nombre |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `repartidores.txt` (10 en total) y correr el programa | `Se cargaron 8 repartidores`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Tiempos de entrega por repartidor)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `repartidores.txt` abierto en el Bloc de notas:

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
