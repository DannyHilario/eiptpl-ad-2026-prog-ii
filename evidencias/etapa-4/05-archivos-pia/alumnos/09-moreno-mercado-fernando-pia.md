# PIA — Batería de laptops durante el día

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 09 — Moreno Mercado Fernando

## Historia de usuario

**Como** encargado del centro de cómputo, **quiero** que las laptops que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada laptop se volvió un registro dentro de un arreglo de
structs, y ahora las laptops se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- El centro de cómputo presta como máximo **8 laptops**.
- De cada laptop se registra su **clave**, una sola palabra sin espacios (por ejemplo `LAP01`), y su **fecha de compra**: la fecha en que la escuela compró la laptop, con día, mes y año. **No puede haber dos laptops con la misma clave.**
- De cada laptop se registra la carga restante al terminar **4 clases**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2018 y 2026**.
- Una carga es válida si está entre **0 y 100%**.
- Una laptop tiene **batería suficiente** si el **promedio** de sus 4 cargas es **mayor o igual a 20%**; si no, tiene **batería baja**.
- Todas las laptops se guardan en el archivo **`laptops.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
PRESTAMO DE LAPTOPS

1.- Alta de una laptop
2.- Buscar una laptop
3.- Cambiar los datos de una laptop
4.- Desplegar laptops
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las laptops de `laptops.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de compra y los 4 datos, muestra su promedio y su
  clasificación, y **agrega** la laptop al final de `laptops.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  4 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `laptops.txt` completo. La clave y la fecha de compra no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las laptops, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas laptops hay, el **promedio de carga de las laptops** (el
  promedio de los promedios de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las laptops que ya están registradas. Crea el archivo **`laptops.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
LAP01 20 1 2023 80 65 50 35
LAP02 11 8 2024 30 18 10 5
LAP03 5 1 2025 20 20 20 20
LAP04 17 6 2022 95 90 70 61
LAP05 29 10 2025 25 15 10 6
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `LAP01 20 1 2023 80 65 50 35` | 57.50% | Bateria suficiente |
| 2 | `LAP02 11 8 2024 30 18 10 5` | 15.75% | Bateria baja |
| 3 | `LAP03 5 1 2025 20 20 20 20` | 20.00% | Bateria suficiente |
| 4 | `LAP04 17 6 2022 95 90 70 61` | 79.00% | Bateria suficiente |
| 5 | `LAP05 29 10 2025 25 15 10 6` | 14.00% | Bateria baja |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 laptops:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Laptop {
    string clave;
    Fecha compra;           // struct anidado: fecha de compra
    double cargas[CLASES];  // los 4 datos de cada laptop
    double promedioCarga;   // el promedio de los 4 datos
};

Laptop laptops[MAX_LAPTOPS];
int n;    // cuantas laptops hay en el arreglo
```

**En el archivo**, un renglón por laptop, con los campos separados por un espacio:

```
clave dia mes anio cargas[0] cargas[1] cargas[2] cargas[3]
```

Por ejemplo, `LAP01 20 1 2023 80 65 50 35` es la laptop `LAP01`, con fecha de compra 20/1/2023 y
datos 80, 65, 50, 35.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioCarga`, y se guarda en el campo `promedioCarga`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_LAPTOPS && entrada >> laptops[n].clave)`; dentro del `while` se leen la fecha y los 4 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaLaptop` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarLaptops(Laptop laptops[])` | Abre `laptops.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada una y regresa cuántas cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarLaptops(Laptop laptops[], int n)` | **Reescribe** `laptops.txt` completo con las `n` laptops del arreglo. Regresa cuántas escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Laptop laptops[], int n, string clave)` | Regresa la posición de la laptop con esa clave, o -1 si no está | No |
| `double calcularPromedioCarga(double cargas[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarBateria(double promedioCarga)` | Regresa `"Bateria suficiente"` o `"Bateria baja"` (la misma de tu Evidencia 3.2) | No |
| `int altaLaptop(Laptop laptops[], int n)` | **Opción 1.** Registra una laptop nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarLaptop(Laptop laptops[], int n)` | **Opción 2.** Busca una laptop y muestra todos sus datos | Sí |
| `void cambiarLaptop(Laptop laptops[], int n)` | **Opción 3.** Cambia los datos de una laptop y reescribe el archivo | Sí |
| `void desplegarLaptops(Laptop laptops[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Laptop laptops[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaLaptop` y `cambiarLaptop` usan `buscarPosicion` y `calcularPromedioCarga`, y `cargarLaptops` usa
`calcularPromedioCarga`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Laptop` con los campos
      `clave` (`string`), `compra` (`Fecha`), `cargas` (arreglo `double` de 4) y `promedioCarga` (`double`).
- [ ] Las laptops se guardan en un arreglo de structs `Laptop laptops[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por laptop (4), los límites de
      un dato (0 y 100), los del año (2018 y 2026), el límite de
      la clasificación (20) y el nombre del archivo (`"laptops.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarLaptops`, `guardarLaptops`, `buscarPosicion`, `calcularPromedioCarga` y `clasificarBateria`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioCarga` y se guarda en `promedioCarga`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todas las laptops del archivo y avisa cuántas. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 laptops, aunque el archivo tenga más renglones: `n < MAX_LAPTOPS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos de la laptop cambiada.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 laptops, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 100%. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la laptop (clave, fecha de compra, los 4 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      4 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por laptop, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas laptops hay, el promedio de carga de las laptops y cuántas hay de cada
      clasificación.
- [ ] Si no hay laptops registradas, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 laptops de laptops.txt

PRESTAMO DE LAPTOPS

1.- Alta de una laptop
2.- Buscar una laptop
3.- Cambiar los datos de una laptop
4.- Desplegar laptops
5.- Resumen general
6.- Salir

Opcion: 4

LAPTOPS REGISTRADAS

Clave   Fecha             C1     C2     C3     C4   Promedio
LAP01   20/1/2023      80.00  65.00  50.00  35.00      57.50   Bateria suficiente
LAP02   11/8/2024      30.00  18.00  10.00   5.00      15.75   Bateria baja
LAP03   5/1/2025       20.00  20.00  20.00  20.00      20.00   Bateria suficiente
LAP04   17/6/2022      95.00  90.00  70.00  61.00      79.00   Bateria suficiente
LAP05   29/10/2025     25.00  15.00  10.00   6.00      14.00   Bateria baja
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE LAPTOP
  Clave: LAP03
  ERROR! Ya existe una laptop con esa clave

Opcion: 1

ALTA DE LAPTOP
  Clave: LAP06
  Fecha de compra
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 21
    Mes: 1
    Anio: 2023
  Clases
    Clase 1: 55
    Clase 2: 101
    ERROR! El dato debe estar entre 0 y 100%
    Clase 2: 42
    Clase 3: 30
    Clase 4: 20

Promedio: 36.75% -> Bateria suficiente
Laptop agregada a laptops.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: LAP02

Clave: LAP02
Fecha de compra: 11/8/2024
Clases: C1 30.00, C2 18.00, C3 10.00, C4 5.00
Promedio: 15.75% -> Bateria baja
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA LAPTOP
  Clave: LAP01

  Datos actuales: C1 80.00, C2 65.00, C3 50.00, C4 35.00  (Promedio 57.50%, Bateria suficiente)
  Datos nuevos
    Clase 1: 30
    Clase 2: 18
    Clase 3: 10
    Clase 4: 5

Promedio: 15.75% -> Bateria baja
Se reescribio laptops.txt con 6 laptops
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Laptops registradas: 6
Promedio de carga de las laptops: 30.21%
Bateria suficiente: 3
Bateria baja: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `laptops.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `laptops.txt` en la carpeta | `Se cargaron 0 laptops`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay laptops registradas; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `LAP06`, 21/1/2023, datos 55, 42, 30, 20 | Promedio 36.75% → Bateria suficiente; aparece `laptops.txt` con un solo renglón: `LAP06 21 1 2023 55 42 30 20` |
| 4 | Carga del archivo inicial | Borrar `laptops.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 laptops` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `LAP01` 57.50 (Bateria suficiente); `LAP02` 15.75 (Bateria baja); `LAP03` 20.00 (Bateria suficiente); `LAP04` 79.00 (Bateria suficiente); `LAP05` 14.00 (Bateria baja) |
| 6 | Búsqueda encontrada | Opción 2, `LAP02` | Todos sus datos: 11/8/2024; 30.00, 18.00, 10.00, 5.00; promedio 15.75% → Bateria baja |
| 7 | Búsqueda no encontrada | Opción 2, `LAP09` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `lap02` | Aviso de que no se encontró: `lap02` y `LAP02` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 laptops; promedio de carga de las laptops: 37.25%; Bateria suficiente: 3; Bateria baja: 2 |
| 10 | Clave repetida | Opción 1, `LAP03` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `LAP06`: día 0 y 32, mes 13, año 2017 y 2027, un dato de 101 y de -1; después 21/1/2023 y datos 55, 42, 30, 20 | Error en cada dato no válido y lo vuelve a pedir; promedio 36.75% → Bateria suficiente |
| 12 | El alta agrega al final | Abrir `laptops.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `LAP06 21 1 2023 55 42 30 20` |
| 13 | Cambio de laptop que no existe | Opción 3, `LAP09` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `LAP01`; un dato de 101; después 30, 18, 10, 5 | Muestra sus datos actuales; error con 101 y vuelve a pedir esa misma clase; nuevo promedio 15.75% → Bateria baja |
| 15 | El cambio reescribe el archivo | Abrir `laptops.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `LAP01 20 1 2023 30 18 10 5` |
| 16 | Resumen después de los cambios | Opción 5 | 6 laptops; promedio de carga de las laptops: 30.21%; Bateria suficiente: 3; Bateria baja: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 laptops`; la tabla muestra los 6, con `LAP01` ya cambiada y `LAP06` al final |
| 18 | Registro lleno | Opción 1 con `LAP07`, 12/8/2024, datos 90, 70, 61, 95 (79.00, Bateria suficiente) y `LAP08`, 6/1/2025, datos 15, 10, 6, 25 (14.00, Bateria baja); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `laptops.txt` (10 en total) y correr el programa | `Se cargaron 8 laptops`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Bateria de laptops durante el dia)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `laptops.txt` abierto en el Bloc de notas:

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
