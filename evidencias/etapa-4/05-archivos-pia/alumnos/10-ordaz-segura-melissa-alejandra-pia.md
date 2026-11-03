# PIA — Turbidez del agua por punto de muestreo

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 10 — Ordaz Segura Melissa Alejandra

## Historia de usuario

**Como** químico de una planta potabilizadora, **quiero** que los puntos de muestreo que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada punto de muestreo se volvió un registro dentro de un arreglo de
structs, y ahora los puntos de muestreo se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- La planta revisa como máximo **8 puntos de muestreo**.
- De cada punto de muestreo se registra su **clave**, una sola palabra sin espacios (por ejemplo `PM1`), y su **fecha de limpieza**: la fecha en que se limpiaron por última vez los filtros de ese punto, con día, mes y año. **No puede haber dos puntos de muestreo con la misma clave.**
- De cada punto se toman **4 muestras** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2022 y 2026**.
- Una muestra es válida si su turbidez está entre **0 y 100 NTU**.
- El agua de un punto es **apta** si el **promedio** de sus 4 muestras es **menor o igual a 5 NTU**; si no, **no es apta**.
- Todos los puntos de muestreo se guardan en el archivo **`puntos.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
CALIDAD DEL AGUA

1.- Alta de un punto de muestreo
2.- Buscar un punto de muestreo
3.- Cambiar los datos de un punto de muestreo
4.- Desplegar puntos de muestreo
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los puntos de muestreo de `puntos.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de limpieza y los 4 datos, muestra su promedio y su
  clasificación, y **agrega** el punto de muestreo al final de `puntos.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  4 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `puntos.txt` completo. La clave y la fecha de limpieza no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los puntos de muestreo, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos puntos de muestreo hay, el **promedio de turbidez de la red** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los puntos de muestreo que ya están registrados. Crea el archivo **`puntos.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
PM1 6 10 2025 1.2 0.8 2 1
PM2 19 4 2026 7.5 6 9 5.5
PM3 13 10 2026 5 5 5 5
PM4 2 7 2025 2 2.5 3 1.5
PM5 24 1 2026 12 8 10 14
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `PM1 6 10 2025 1.2 0.8 2 1` | 1.25 NTU | Agua apta |
| 2 | `PM2 19 4 2026 7.5 6 9 5.5` | 7.00 NTU | Agua no apta |
| 3 | `PM3 13 10 2026 5 5 5 5` | 5.00 NTU | Agua apta |
| 4 | `PM4 2 7 2025 2 2.5 3 1.5` | 2.25 NTU | Agua apta |
| 5 | `PM5 24 1 2026 12 8 10 14` | 11.00 NTU | Agua no apta |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 puntos de muestreo:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct PuntoMuestreo {
    string clave;
    Fecha limpieza;             // struct anidado: fecha de limpieza
    double muestras[MUESTRAS];  // los 4 datos de cada punto de muestreo
    double promedioTurbidez;    // el promedio de los 4 datos
};

PuntoMuestreo puntos[MAX_PUNTOS];
int n;    // cuantos puntos de muestreo hay en el arreglo
```

**En el archivo**, un renglón por punto de muestreo, con los campos separados por un espacio:

```
clave dia mes anio muestras[0] muestras[1] muestras[2] muestras[3]
```

Por ejemplo, `PM1 6 10 2025 1.2 0.8 2 1` es el punto de muestreo `PM1`, con fecha de limpieza 6/10/2025 y
datos 1.2, 0.8, 2, 1.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioTurbidez`, y se guarda en el campo `promedioTurbidez`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_PUNTOS && entrada >> puntos[n].clave)`; dentro del `while` se leen la fecha y los 4 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaPuntoMuestreo` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarPuntos(PuntoMuestreo puntos[])` | Abre `puntos.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarPuntos(PuntoMuestreo puntos[], int n)` | **Reescribe** `puntos.txt` completo con los `n` puntos de muestreo del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(PuntoMuestreo puntos[], int n, string clave)` | Regresa la posición del punto de muestreo con esa clave, o -1 si no está | No |
| `double calcularPromedioTurbidez(double muestras[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarAgua(double promedioTurbidez)` | Regresa `"Agua apta"` o `"Agua no apta"` (la misma de tu Evidencia 3.2) | No |
| `int altaPuntoMuestreo(PuntoMuestreo puntos[], int n)` | **Opción 1.** Registra un punto de muestreo nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarPuntoMuestreo(PuntoMuestreo puntos[], int n)` | **Opción 2.** Busca un punto de muestreo y muestra todos sus datos | Sí |
| `void cambiarPuntoMuestreo(PuntoMuestreo puntos[], int n)` | **Opción 3.** Cambia los datos de un punto de muestreo y reescribe el archivo | Sí |
| `void desplegarPuntos(PuntoMuestreo puntos[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(PuntoMuestreo puntos[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaPuntoMuestreo` y `cambiarPuntoMuestreo` usan `buscarPosicion` y `calcularPromedioTurbidez`, y `cargarPuntos` usa
`calcularPromedioTurbidez`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct PuntoMuestreo` con los campos
      `clave` (`string`), `limpieza` (`Fecha`), `muestras` (arreglo `double` de 4) y `promedioTurbidez` (`double`).
- [ ] Los puntos de muestreo se guardan en un arreglo de structs `PuntoMuestreo puntos[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por punto de muestreo (4), los límites de
      un dato (0 y 100), los del año (2022 y 2026), el límite de
      la clasificación (5) y el nombre del archivo (`"puntos.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarPuntos`, `guardarPuntos`, `buscarPosicion`, `calcularPromedioTurbidez` y `clasificarAgua`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioTurbidez` y se guarda en `promedioTurbidez`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los puntos de muestreo del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 puntos de muestreo, aunque el archivo tenga más renglones: `n < MAX_PUNTOS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del punto de muestreo cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 puntos de muestreo, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 100 NTU. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del punto de muestreo (clave, fecha de limpieza, los 4 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      4 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por punto de muestreo, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos puntos de muestreo hay, el promedio de turbidez de la red y cuántos hay de cada
      clasificación.
- [ ] Si no hay puntos de muestreo registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 puntos de muestreo de puntos.txt

CALIDAD DEL AGUA

1.- Alta de un punto de muestreo
2.- Buscar un punto de muestreo
3.- Cambiar los datos de un punto de muestreo
4.- Desplegar puntos de muestreo
5.- Resumen general
6.- Salir

Opcion: 4

PUNTOS DE MUESTREO REGISTRADOS

Clave   Fecha             M1     M2     M3     M4   Promedio
PM1     6/10/2025       1.20   0.80   2.00   1.00       1.25   Agua apta
PM2     19/4/2026       7.50   6.00   9.00   5.50       7.00   Agua no apta
PM3     13/10/2026      5.00   5.00   5.00   5.00       5.00   Agua apta
PM4     2/7/2025        2.00   2.50   3.00   1.50       2.25   Agua apta
PM5     24/1/2026      12.00   8.00  10.00  14.00      11.00   Agua no apta
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE PUNTO DE MUESTREO
  Clave: PM3
  ERROR! Ya existe un punto de muestreo con esa clave

Opcion: 1

ALTA DE PUNTO DE MUESTREO
  Clave: PM6
  Fecha de limpieza
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 7
    Mes: 10
    Anio: 2025
  Muestras
    Muestra 1: 4.35
    Muestra 2: 120
    ERROR! El dato debe estar entre 0 y 100 NTU
    Muestra 2: 3.4
    Muestra 3: 5.5
    Muestra 4: 3.25

Promedio: 4.12 NTU -> Agua apta
Punto de muestreo agregado a puntos.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: PM2

Clave: PM2
Fecha de limpieza: 19/4/2026
Muestras: M1 7.50, M2 6.00, M3 9.00, M4 5.50
Promedio: 7.00 NTU -> Agua no apta
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN PUNTO DE MUESTREO
  Clave: PM1

  Datos actuales: M1 1.20, M2 0.80, M3 2.00, M4 1.00  (Promedio 1.25 NTU, Agua apta)
  Datos nuevos
    Muestra 1: 7.5
    Muestra 2: 6
    Muestra 3: 9
    Muestra 4: 5.5

Promedio: 7.00 NTU -> Agua no apta
Se reescribio puntos.txt con 6 puntos de muestreo
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Puntos de muestreo registrados: 6
Promedio de turbidez de la red: 6.06 NTU
Agua apta: 3
Agua no apta: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `puntos.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `puntos.txt` en la carpeta | `Se cargaron 0 puntos de muestreo`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay puntos de muestreo registrados; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `PM6`, 7/10/2025, datos 4.35, 3.4, 5.5, 3.25 | Promedio 4.12 NTU → Agua apta; aparece `puntos.txt` con un solo renglón: `PM6 7 10 2025 4.35 3.4 5.5 3.25` |
| 4 | Carga del archivo inicial | Borrar `puntos.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 puntos de muestreo` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `PM1` 1.25 (Agua apta); `PM2` 7.00 (Agua no apta); `PM3` 5.00 (Agua apta); `PM4` 2.25 (Agua apta); `PM5` 11.00 (Agua no apta) |
| 6 | Búsqueda encontrada | Opción 2, `PM2` | Todos sus datos: 19/4/2026; 7.50, 6.00, 9.00, 5.50; promedio 7.00 NTU → Agua no apta |
| 7 | Búsqueda no encontrada | Opción 2, `PM9` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `pm2` | Aviso de que no se encontró: `pm2` y `PM2` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 puntos de muestreo; promedio de turbidez de la red: 5.30 NTU; Agua apta: 3; Agua no apta: 2 |
| 10 | Clave repetida | Opción 1, `PM3` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `PM6`: día 0 y 32, mes 13, año 2021 y 2027, un dato de 120 y de -0.5; después 7/10/2025 y datos 4.35, 3.4, 5.5, 3.25 | Error en cada dato no válido y lo vuelve a pedir; promedio 4.12 NTU → Agua apta |
| 12 | El alta agrega al final | Abrir `puntos.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `PM6 7 10 2025 4.35 3.4 5.5 3.25` |
| 13 | Cambio de punto de muestreo que no existe | Opción 3, `PM9` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `PM1`; un dato de 120; después 7.5, 6, 9, 5.5 | Muestra sus datos actuales; error con 120 y vuelve a pedir esa misma muestra; nuevo promedio 7.00 NTU → Agua no apta |
| 15 | El cambio reescribe el archivo | Abrir `puntos.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `PM1 6 10 2025 7.5 6 9 5.5` |
| 16 | Resumen después de los cambios | Opción 5 | 6 puntos de muestreo; promedio de turbidez de la red: 6.06 NTU; Agua apta: 3; Agua no apta: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 puntos de muestreo`; la tabla muestra los 6, con `PM1` ya cambiado y `PM6` al final |
| 18 | Registro lleno | Opción 1 con `PM7`, 20/4/2026, datos 2.5, 3, 1.5, 2 (2.25, Agua apta) y `PM8`, 14/10/2026, datos 8, 10, 14, 12 (11.00, Agua no apta); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `puntos.txt` (10 en total) y correr el programa | `Se cargaron 8 puntos de muestreo`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Turbidez del agua por punto de muestreo)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `puntos.txt` abierto en el Bloc de notas:

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
