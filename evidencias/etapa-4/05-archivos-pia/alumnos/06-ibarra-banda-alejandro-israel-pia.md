# PIA — Existencias por sucursal

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 06 — Ibarra Banda Alejandro Israel

## Historia de usuario

**Como** encargado de compras de una cadena de tiendas, **quiero** que los productos que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada producto se volvió un registro dentro de un arreglo de
structs, y ahora los productos se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se revisan como máximo **8 productos**.
- De cada producto se registra su **clave**, una sola palabra sin espacios (por ejemplo `P100`), y su **fecha del último pedido**: la fecha en que se le hizo el último pedido al proveedor, con día, mes y año. **No puede haber dos productos con la misma clave.**
- De cada producto se registran las piezas en existencia de **3 sucursales**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- Las existencias de una sucursal son válidas si están entre **0 y 500 piezas**.
- Un producto tiene **stock normal** si el **total** de piezas en las 3 sucursales es **mayor a 10**; si es de 10 o menos, tiene **stock bajo**.
- Todos los productos se guardan en el archivo **`productos.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
CONTROL DE INVENTARIO

1.- Alta de un producto
2.- Buscar un producto
3.- Cambiar los datos de un producto
4.- Desplegar productos
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los productos de `productos.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha del último pedido y los 3 datos, muestra su total y su
  clasificación, y **agrega** el producto al final de `productos.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  3 datos **nuevos**, recalcula su total, muestra su nueva clasificación y **reescribe**
  `productos.txt` completo. La clave y la fecha del último pedido no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los productos, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos productos hay, el **promedio de existencias por producto** (el
  promedio de los totales de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los productos que ya están registrados. Crea el archivo **`productos.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
P100 9 6 2026 25 40 12
P200 22 8 2025 3 2 4
P300 14 6 2025 4 3 3
P400 3 1 2026 100 85 60
P500 28 10 2024 1 0 5
```

Así se lee cada renglón:

| # | Renglón | Total | Clasificación |
|---|---|---|---|
| 1 | `P100 9 6 2026 25 40 12` | 77.00 piezas | Stock normal |
| 2 | `P200 22 8 2025 3 2 4` | 9.00 piezas | Stock bajo |
| 3 | `P300 14 6 2025 4 3 3` | 10.00 piezas | Stock bajo |
| 4 | `P400 3 1 2026 100 85 60` | 245.00 piezas | Stock normal |
| 5 | `P500 28 10 2024 1 0 5` | 6.00 piezas | Stock bajo |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 productos:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Producto {
    string clave;
    Fecha ultimoPedido;              // struct anidado: fecha del último pedido
    double existencias[SUCURSALES];  // los 3 datos de cada producto
    double totalExistencias;         // la suma de los 3 datos
};

Producto productos[MAX_PRODUCTOS];
int n;    // cuantos productos hay en el arreglo
```

**En el archivo**, un renglón por producto, con los campos separados por un espacio:

```
clave dia mes anio existencias[0] existencias[1] existencias[2]
```

Por ejemplo, `P100 9 6 2026 25 40 12` es el producto `P100`, con fecha del último pedido 9/6/2026 y
datos 25, 40, 12.

**El total no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularTotalExistencias`, y se guarda en el campo `totalExistencias`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_PRODUCTOS && entrada >> productos[n].clave)`; dentro del `while` se leen la fecha y los 3 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaProducto` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarProductos(Producto productos[])` | Abre `productos.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el total de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarProductos(Producto productos[], int n)` | **Reescribe** `productos.txt` completo con los `n` productos del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Producto productos[], int n, string clave)` | Regresa la posición del producto con esa clave, o -1 si no está | No |
| `double calcularTotalExistencias(double existencias[], int cantidad)` | Regresa la suma de los datos del arreglo | No |
| `string clasificarStock(double totalExistencias)` | Regresa `"Stock normal"` o `"Stock bajo"` (la misma de tu Evidencia 3.2) | No |
| `int altaProducto(Producto productos[], int n)` | **Opción 1.** Registra un producto nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarProducto(Producto productos[], int n)` | **Opción 2.** Busca un producto y muestra todos sus datos | Sí |
| `void cambiarProducto(Producto productos[], int n)` | **Opción 3.** Cambia los datos de un producto y reescribe el archivo | Sí |
| `void desplegarProductos(Producto productos[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Producto productos[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaProducto` y `cambiarProducto` usan `buscarPosicion` y `calcularTotalExistencias`, y `cargarProductos` usa
`calcularTotalExistencias`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Producto` con los campos
      `clave` (`string`), `ultimoPedido` (`Fecha`), `existencias` (arreglo `double` de 3) y `totalExistencias` (`double`).
- [ ] Los productos se guardan en un arreglo de structs `Producto productos[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por producto (3), los límites de
      un dato (0 y 500), los del año (2020 y 2026), el límite de
      la clasificación (10) y el nombre del archivo (`"productos.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarProductos`, `guardarProductos`, `buscarPosicion`, `calcularTotalExistencias` y `clasificarStock`
      no usan `cin` ni `cout`.
- [ ] El total se calcula **solo** con `calcularTotalExistencias` y se guarda en `totalExistencias`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los productos del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 productos, aunque el archivo tenga más renglones: `n < MAX_PRODUCTOS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del producto cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 productos, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 500 piezas. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del producto (clave, fecha del último pedido, los 3 datos, total y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      3 nuevos, recalcula el total y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por producto, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos productos hay, el promedio de existencias por producto y cuántos hay de cada
      clasificación.
- [ ] Si no hay productos registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 productos de productos.txt

CONTROL DE INVENTARIO

1.- Alta de un producto
2.- Buscar un producto
3.- Cambiar los datos de un producto
4.- Desplegar productos
5.- Resumen general
6.- Salir

Opcion: 4

PRODUCTOS REGISTRADOS

Clave   Fecha              S1      S2      S3    Total
P100    9/6/2026        25.00   40.00   12.00    77.00   Stock normal
P200    22/8/2025        3.00    2.00    4.00     9.00   Stock bajo
P300    14/6/2025        4.00    3.00    3.00    10.00   Stock bajo
P400    3/1/2026       100.00   85.00   60.00   245.00   Stock normal
P500    28/10/2024       1.00    0.00    5.00     6.00   Stock bajo
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE PRODUCTO
  Clave: P300
  ERROR! Ya existe un producto con esa clave

Opcion: 1

ALTA DE PRODUCTO
  Clave: P600
  Fecha del ultimo pedido
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 10
    Mes: 6
    Anio: 2026
  Sucursales
    Sucursal 1: 14
    Sucursal 2: 600
    ERROR! El dato debe estar entre 0 y 500 piezas
    Sucursal 2: 21
    Sucursal 3: 8

Total: 43.00 piezas -> Stock normal
Producto agregado a productos.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: P200

Clave: P200
Fecha del ultimo pedido: 22/8/2025
Sucursales: S1 3.00, S2 2.00, S3 4.00
Total: 9.00 piezas -> Stock bajo
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN PRODUCTO
  Clave: P100

  Datos actuales: S1 25.00, S2 40.00, S3 12.00  (Total 77.00 piezas, Stock normal)
  Datos nuevos
    Sucursal 1: 3
    Sucursal 2: 2
    Sucursal 3: 4

Total: 9.00 piezas -> Stock bajo
Se reescribio productos.txt con 6 productos
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Productos registrados: 6
Promedio de existencias por producto: 53.67 piezas
Stock normal: 2
Stock bajo: 4
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `productos.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `productos.txt` en la carpeta | `Se cargaron 0 productos`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay productos registrados; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `P600`, 10/6/2026, datos 14, 21, 8 | Total 43.00 piezas → Stock normal; aparece `productos.txt` con un solo renglón: `P600 10 6 2026 14 21 8` |
| 4 | Carga del archivo inicial | Borrar `productos.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 productos` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `P100` 77.00 (Stock normal); `P200` 9.00 (Stock bajo); `P300` 10.00 (Stock bajo); `P400` 245.00 (Stock normal); `P500` 6.00 (Stock bajo) |
| 6 | Búsqueda encontrada | Opción 2, `P200` | Todos sus datos: 22/8/2025; 3.00, 2.00, 4.00; total 9.00 piezas → Stock bajo |
| 7 | Búsqueda no encontrada | Opción 2, `P509` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `p200` | Aviso de que no se encontró: `p200` y `P200` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 productos; promedio de existencias por producto: 69.40 piezas; Stock normal: 2; Stock bajo: 3 |
| 10 | Clave repetida | Opción 1, `P300` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `P600`: día 0 y 32, mes 13, año 2019 y 2027, un dato de 600 y de -2; después 10/6/2026 y datos 14, 21, 8 | Error en cada dato no válido y lo vuelve a pedir; total 43.00 piezas → Stock normal |
| 12 | El alta agrega al final | Abrir `productos.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `P600 10 6 2026 14 21 8` |
| 13 | Cambio de producto que no existe | Opción 3, `P509` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `P100`; un dato de 600; después 3, 2, 4 | Muestra sus datos actuales; error con 600 y vuelve a pedir esa misma sucursal; nuevo total 9.00 piezas → Stock bajo |
| 15 | El cambio reescribe el archivo | Abrir `productos.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `P100 9 6 2026 3 2 4` |
| 16 | Resumen después de los cambios | Opción 5 | 6 productos; promedio de existencias por producto: 53.67 piezas; Stock normal: 2; Stock bajo: 4 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 productos`; la tabla muestra los 6, con `P100` ya cambiado y `P600` al final |
| 18 | Registro lleno | Opción 1 con `P700`, 23/8/2025, datos 85, 60, 100 (245.00, Stock normal) y `P800`, 15/6/2025, datos 0, 5, 1 (6.00, Stock bajo); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `productos.txt` (10 en total) y correr el programa | `Se cargaron 8 productos`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Existencias por sucursal)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `productos.txt` abierto en el Bloc de notas:

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
