# Evidencia 3 — Existencias por sucursal

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 06 — Ibarra Banda Alejandro Israel

## Historia de usuario

**Como** encargado de compras de una cadena de tiendas, **quiero** registrar cada producto con su clave, la fecha de su último pedido y sus existencias en las 3 sucursales, y consultarlo por clave o por mes del último pedido, **para** contestar rápido si hay un producto y revisar los pedidos que se hicieron en un mes.

## Contexto

En la Evidencia 2.2 los 3 datos de cada producto vivían en la matriz `existencias` y su total
en el vector `totales`, y lo único que los unía era el número de fila. Ahora cada producto
será un **registro** completo: su clave, su fecha del último pedido, sus 3 datos y su total viajan
juntos en un `struct`.

**Reglas**

- Se revisan como máximo **5 productos**.
- De cada producto se registra su **clave**, una sola palabra sin espacios (por ejemplo `P100`), y su **fecha del último pedido**: la fecha en que se le hizo el último pedido al proveedor, con día, mes y año.
- De cada producto se registran las piezas en existencia de **3 sucursales**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- Las existencias de una sucursal son válidas si están entre **0 y 500 piezas**.
- Un producto tiene **stock normal** si el **total** de piezas en las 3 sucursales es **mayor a 10**; si es de 10 o menos, tiene **stock bajo**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
CONTROL DE INVENTARIO

1.- Registrar un producto
2.- Tabla de productos
3.- Productos por mes de ultimo pedido
4.- Buscar un producto
5.- Salir
```

- **Opción 1:** pide la clave, la fecha del último pedido y los 3 datos del siguiente producto y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra la tabla de todos los productos registrados: una fila por
  producto, con su clave, su fecha del último pedido, sus 3 datos, su total y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los productos cuya fecha del último pedido cae en ese
  mes, de cualquier año, con su clave, su fecha del último pedido, su total y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay un producto registrado con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan productos.** El programa no permite eliminar ni modificar un
producto ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

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
```

**Un arreglo como campo de un struct.** `existencias` es un arreglo de 3 datos que vive
**dentro** de cada producto (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al producto y luego el campo:

| Expresión | Qué es |
|---|---|
| `productos[1]` | El segundo producto completo (de tipo `Producto`) |
| `productos[1].clave` | Su clave (de tipo `string`) |
| `productos[1].ultimoPedido.mes` | El mes de su fecha del último pedido (de tipo `int`) |
| `productos[1].existencias` | Sus 3 datos (un arreglo de `double`) |
| `productos[1].existencias[2]` | Su dato de la columna 3 (Sucursal 3), de tipo `double` |
| `productos[1].totalExistencias` | Su total (de tipo `double`) |

Por ejemplo, después de registrar dos productos:

```
                                    existencias  
 productos clave    ultimoPedido    [0]  [1]  [2]   totalExistencias
   [0]     P100     9/6/2026         25   40   12                 77
   [1]     P200     22/8/2025         3    2    4                  9
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 3 datos, y en cuanto termina la captura se suman sus 3 datos
y el resultado se guarda en `totalExistencias` del **mismo** producto.

**¿Para qué guardar el total?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `totalExistencias`; no vuelven a recorrer los 3 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos productos hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Producto`.
- [ ] Define `struct Producto` con los campos `clave` (`string`), `ultimoPedido` (`Fecha`),
      `existencias` (arreglo `double` de 3) y `totalExistencias` (`double`), antes de `main`.
- [ ] Los productos se guardan en un **arreglo de structs** `Producto productos[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos productos se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El total de cada producto se guarda en su campo `totalExistencias` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de productos (5), los datos por producto (3), los límites de un
      dato válido (0 y 500), los límites del año
      (2020 y 2026) y el límite de la clasificación (10)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarStock(double totalExistencias)`, que recibe el total (no el struct) y regresa
      `"Stock normal"` o `"Stock bajo"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      producto, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los productos cuyo mes de `ultimoPedido` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      producto registrado y muestra **todos** los datos del que coincide: clave,
      fecha del último pedido, los 3 datos, su total y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los productos registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 productos registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay productos registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2020 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 500; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** sucursal (no se salta a la
      siguiente).
- [ ] El mes que se pide en la opción 3 debe estar entre 1 y 12; si no, muestra un
      error y lo vuelve a pedir.
- [ ] Los resultados coinciden con **todos** los casos de prueba de este enunciado.

**Código fácil de seguir y leer**

- [ ] Nombres descriptivos para los structs, sus campos y las variables.
- [ ] Comentarios que expliquen cada sección del programa (structs, menú, registro,
      tabla, filtro por mes, búsqueda, validaciones).
- [ ] Compila y se ejecuta sin errores en Dev-C++.

### Actitudes / Valores (2 puntos) — Entrega

- [ ] Lo entregas en NEXUS, en la evidencia *"3.2 - Evidencia de Aprendizaje 3: Programa"*, antes del
      **jueves 22 de octubre de 2026 a las 7:40 p.m.**
- [ ] El archivo es de texto plano, con el nombre `EV3.2_ApellidoNombre.txt`.
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu código si
      se te pregunta.

## Ejemplo de ejecución

Registro del primer producto, con datos fuera de rango:

```
Opcion: 1

PRODUCTO 1
  Clave: P100
  Fecha del ultimo pedido
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 9
    Mes: 6
    Anio: 2027
    ERROR! El anio debe estar entre 2020 y 2026
    Anio: 2026
  Sucursales
    Sucursal 1: 25
    Sucursal 2: 600
    ERROR! El dato debe estar entre 0 y 500 piezas
    Sucursal 2: 40
    Sucursal 3: 12

Total: 77 piezas -> Stock normal
```

Después de registrar los 3 productos de los casos de prueba:

```
Opcion: 2

TABLA DE PRODUCTOS

Clave   Fecha         S1  S2  S3   Total
P100    9/6/2026      25  40  12      77   Stock normal
P200    22/8/2025      3   2   4       9   Stock bajo
P300    14/6/2025      4   3   3      10   Stock bajo
```

```
Opcion: 3
Mes (1 a 12): 6

PRODUCTOS CON FECHA DEL ULTIMO PEDIDO EN EL MES 6

P100    9/6/2026    Total: 77 piezas   Stock normal
P300    14/6/2025   Total: 10 piezas   Stock bajo
```

```
Opcion: 4
Clave a buscar: P200

Clave: P200
Fecha del ultimo pedido: 22/8/2025
Sucursales: S1 3, S2 2, S3 4
Total: 9 piezas -> Stock bajo
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay productos registrados; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro del producto 1 | `P100`, 9/6/2026, datos 25, 40, 12 | Total 77 piezas → Stock normal |
| 3 | Registro del producto 2 | `P200`, 22/8/2025, datos 3, 2, 4 | Total 9 piezas → Stock bajo |
| 4 | Justo en el límite | `P300`, 14/6/2025, datos 4, 3, 3 | Total 10 piezas → **Stock bajo** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 6 | Mes con registros | Opción 3, mes 6 | `P100` (9/6/2026) y `P300` (14/6/2025), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún producto tiene su fecha del último pedido en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `P200` | Todos sus datos: 22/8/2025; 3, 2, 4; total 9 piezas; Stock bajo |
| 10 | Búsqueda no encontrada | Opción 4, `P509` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `p200` | Aviso de que no se encontró: `p200` y `P200` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 2019 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 600 o de -2 | Error; vuelve a pedir el dato de esa misma sucursal |
| 14 | Registro lleno | Se registran `P400`, 3/1/2026, datos 100, 85, 60 (total 245, Stock normal); `P500`, 28/10/2024, datos 1, 0, 5 (total 6, Stock bajo), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
