# PIA — Encuesta de satisfacción por cliente

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 08 — Martinez Rincon Vika Ludivina

## Historia de usuario

**Como** gerente de un restaurante, **quiero** que los clientes que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada cliente se volvió un registro dentro de un arreglo de
structs, y ahora los clientes se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se capturan como máximo **8 clientes** por turno.
- De cada cliente se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Carmen`), y su **fecha de visita**: la fecha en que visitó el restaurante y contestó la encuesta, con día, mes y año. **No puede haber dos clientes con el mismo nombre.**
- Cada cliente responde **5 preguntas**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2024 y 2026**.
- Una respuesta es válida si está entre **1 y 10**.
- Un cliente quedó **satisfecho** si el **promedio** de sus 5 respuestas es **mayor o igual a 8**; si no, quedó **insatisfecho**.
- Todos los clientes se guardan en el archivo **`clientes.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
ENCUESTA DE SATISFACCION

1.- Alta de un cliente
2.- Buscar un cliente
3.- Cambiar los datos de un cliente
4.- Desplegar clientes
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los clientes de `clientes.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide el nombre; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de visita y los 5 datos, muestra su promedio y su
  clasificación, y **agrega** el cliente al final de `clientes.txt`.
- **Opción 2 — Buscar:** pide el nombre y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el nombre; si existe, muestra sus datos actuales, pide sus
  5 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `clientes.txt` completo. El nombre y la fecha de visita no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los clientes, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos clientes hay, el **promedio de calificación del restaurante** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los clientes que ya están registrados. Crea el archivo **`clientes.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
Carmen 8 8 2025 9 10 8 9 9
Hugo 14 2 2026 6 7 5 8 6
Lucia 23 8 2026 8 8 8 8 8
Raul 30 11 2025 10 9 7 6 7
Teresa 5 4 2026 10 10 9 10 10
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `Carmen 8 8 2025 9 10 8 9 9` | 9.00 | Satisfecho |
| 2 | `Hugo 14 2 2026 6 7 5 8 6` | 6.40 | Insatisfecho |
| 3 | `Lucia 23 8 2026 8 8 8 8 8` | 8.00 | Satisfecho |
| 4 | `Raul 30 11 2025 10 9 7 6 7` | 7.80 | Insatisfecho |
| 5 | `Teresa 5 4 2026 10 10 9 10 10` | 9.80 | Satisfecho |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 clientes:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Cliente {
    string nombre;
    Fecha visita;                  // struct anidado: fecha de visita
    double respuestas[PREGUNTAS];  // los 5 datos de cada cliente
    double promedioCalificacion;   // el promedio de los 5 datos
};

Cliente clientes[MAX_CLIENTES];
int n;    // cuantos clientes hay en el arreglo
```

**En el archivo**, un renglón por cliente, con los campos separados por un espacio:

```
nombre dia mes anio respuestas[0] respuestas[1] respuestas[2] respuestas[3] respuestas[4]
```

Por ejemplo, `Carmen 8 8 2025 9 10 8 9 9` es el cliente `Carmen`, con fecha de visita 8/8/2025 y
datos 9, 10, 8, 9, 9.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioCalificacion`, y se guarda en el campo `promedioCalificacion`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_CLIENTES && entrada >> clientes[n].nombre)`; dentro del `while` se leen la fecha y los 5 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaCliente` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarClientes(Cliente clientes[])` | Abre `clientes.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarClientes(Cliente clientes[], int n)` | **Reescribe** `clientes.txt` completo con los `n` clientes del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Cliente clientes[], int n, string nombre)` | Regresa la posición del cliente con ese nombre, o -1 si no está | No |
| `double calcularPromedioCalificacion(double respuestas[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarSatisfaccion(double promedioCalificacion)` | Regresa `"Satisfecho"` o `"Insatisfecho"` (la misma de tu Evidencia 3.2) | No |
| `int altaCliente(Cliente clientes[], int n)` | **Opción 1.** Registra un cliente nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarCliente(Cliente clientes[], int n)` | **Opción 2.** Busca un cliente y muestra todos sus datos | Sí |
| `void cambiarCliente(Cliente clientes[], int n)` | **Opción 3.** Cambia los datos de un cliente y reescribe el archivo | Sí |
| `void desplegarClientes(Cliente clientes[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Cliente clientes[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaCliente` y `cambiarCliente` usan `buscarPosicion` y `calcularPromedioCalificacion`, y `cargarClientes` usa
`calcularPromedioCalificacion`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Cliente` con los campos
      `nombre` (`string`), `visita` (`Fecha`), `respuestas` (arreglo `double` de 5) y `promedioCalificacion` (`double`).
- [ ] Los clientes se guardan en un arreglo de structs `Cliente clientes[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por cliente (5), los límites de
      un dato (1 y 10), los del año (2024 y 2026), el límite de
      la clasificación (8) y el nombre del archivo (`"clientes.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarClientes`, `guardarClientes`, `buscarPosicion`, `calcularPromedioCalificacion` y `clasificarSatisfaccion`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioCalificacion` y se guarda en `promedioCalificacion`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los clientes del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 clientes, aunque el archivo tenga más renglones: `n < MAX_CLIENTES` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del cliente cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 clientes, avisa que el registro está lleno y no pide nada; si el
      nombre ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      1 y 10. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del cliente (nombre, fecha de visita, los 5 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el nombre no existe; si existe, muestra los datos actuales, pide los
      5 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por cliente, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos clientes hay, el promedio de calificación del restaurante y cuántos hay de cada
      clasificación.
- [ ] Si no hay clientes registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 clientes de clientes.txt

ENCUESTA DE SATISFACCION

1.- Alta de un cliente
2.- Buscar un cliente
3.- Cambiar los datos de un cliente
4.- Desplegar clientes
5.- Resumen general
6.- Salir

Opcion: 4

CLIENTES REGISTRADOS

Nombre    Fecha            Com    Rap    Ate    Lim    Pre   Promedio
Carmen    8/8/2025        9.00  10.00   8.00   9.00   9.00       9.00   Satisfecho
Hugo      14/2/2026       6.00   7.00   5.00   8.00   6.00       6.40   Insatisfecho
Lucia     23/8/2026       8.00   8.00   8.00   8.00   8.00       8.00   Satisfecho
Raul      30/11/2025     10.00   9.00   7.00   6.00   7.00       7.80   Insatisfecho
Teresa    5/4/2026       10.00  10.00   9.00  10.00  10.00       9.80   Satisfecho
```

Alta con nombre repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE CLIENTE
  Nombre: Lucia
  ERROR! Ya existe un cliente con ese nombre

Opcion: 1

ALTA DE CLIENTE
  Nombre: Alberto
  Fecha de visita
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 9
    Mes: 8
    Anio: 2025
  Preguntas
    Comida: 8
    Rapidez: 11
    ERROR! El dato debe estar entre 1 y 10
    Rapidez: 9
    Atencion: 7
    Limpieza: 9
    Precio: 8

Promedio: 8.20 -> Satisfecho
Cliente agregado a clientes.txt
```

Búsqueda:

```
Opcion: 2
Nombre a buscar: Hugo

Nombre: Hugo
Fecha de visita: 14/2/2026
Preguntas: Com 6.00, Rap 7.00, Ate 5.00, Lim 8.00, Pre 6.00
Promedio: 6.40 -> Insatisfecho
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN CLIENTE
  Nombre: Carmen

  Datos actuales: Com 9.00, Rap 10.00, Ate 8.00, Lim 9.00, Pre 9.00  (Promedio 9.00, Satisfecho)
  Datos nuevos
    Comida: 6
    Rapidez: 7
    Atencion: 5
    Limpieza: 8
    Precio: 6

Promedio: 6.40 -> Insatisfecho
Se reescribio clientes.txt con 6 clientes
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Clientes registrados: 6
Promedio de calificacion del restaurante: 7.77
Satisfecho: 3
Insatisfecho: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `clientes.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `clientes.txt` en la carpeta | `Se cargaron 0 clientes`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay clientes registrados; la 2 y la 3 no piden el nombre |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `Alberto`, 9/8/2025, datos 8, 9, 7, 9, 8 | Promedio 8.20 → Satisfecho; aparece `clientes.txt` con un solo renglón: `Alberto 9 8 2025 8 9 7 9 8` |
| 4 | Carga del archivo inicial | Borrar `clientes.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 clientes` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `Carmen` 9.00 (Satisfecho); `Hugo` 6.40 (Insatisfecho); `Lucia` 8.00 (Satisfecho); `Raul` 7.80 (Insatisfecho); `Teresa` 9.80 (Satisfecho) |
| 6 | Búsqueda encontrada | Opción 2, `Hugo` | Todos sus datos: 14/2/2026; 6.00, 7.00, 5.00, 8.00, 6.00; promedio 6.40 → Insatisfecho |
| 7 | Búsqueda no encontrada | Opción 2, `Pedro` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `hugo` | Aviso de que no se encontró: `hugo` y `Hugo` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 clientes; promedio de calificación del restaurante: 8.20; Satisfecho: 3; Insatisfecho: 2 |
| 10 | Nombre repetido | Opción 1, `Lucia` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `Alberto`: día 0 y 32, mes 13, año 2023 y 2027, un dato de 11 y de 0; después 9/8/2025 y datos 8, 9, 7, 9, 8 | Error en cada dato no válido y lo vuelve a pedir; promedio 8.20 → Satisfecho |
| 12 | El alta agrega al final | Abrir `clientes.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `Alberto 9 8 2025 8 9 7 9 8` |
| 13 | Cambio de cliente que no existe | Opción 3, `Pedro` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `Carmen`; un dato de 11; después 6, 7, 5, 8, 6 | Muestra sus datos actuales; error con 11 y vuelve a pedir esa misma pregunta; nuevo promedio 6.40 → Insatisfecho |
| 15 | El cambio reescribe el archivo | Abrir `clientes.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `Carmen 8 8 2025 6 7 5 8 6` |
| 16 | Resumen después de los cambios | Opción 5 | 6 clientes; promedio de calificación del restaurante: 7.77; Satisfecho: 3; Insatisfecho: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 clientes`; la tabla muestra los 6, con `Carmen` ya cambiado y `Alberto` al final |
| 18 | Registro lleno | Opción 1 con `Silvia`, 15/2/2026, datos 9, 7, 6, 7, 10 (7.80, Insatisfecho) y `Gabriel`, 24/8/2026, datos 10, 9, 10, 10, 10 (9.80, Satisfecho); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el nombre |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `clientes.txt` (10 en total) y correr el programa | `Se cargaron 8 clientes`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Encuesta de satisfaccion por cliente)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `clientes.txt` abierto en el Bloc de notas:

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
