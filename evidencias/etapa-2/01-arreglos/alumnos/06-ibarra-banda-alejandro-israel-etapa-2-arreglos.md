# Evidencia 2.2 — Existencias por sucursal

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 06 — Ibarra Banda Alejandro Israel

## Historia de usuario

**Como** encargado de compras de una cadena de tiendas, **quiero** registrar las piezas en existencia de cada producto en las 3 sucursales y consultar cuáles tienen stock bajo, **para** saber qué productos pedirle al proveedor.

## Contexto

En la Evidencia 1 tu programa clasificaba las existencias de cada producto en el momento y las olvidaba. Ahora el almacén tiene **3 sucursales**, así que hay que **guardar** las existencias de cada producto en cada sucursal y sumarlas para saber cuántas piezas hay en total.

Los datos forman una tabla:

|  | Sucursal 1 | Sucursal 2 | Sucursal 3 |
|---|---|---|---|
| **Producto 1** | 25 | 40 | 12 |
| **Producto 2** | 3 | 2 | 4 |
| ... | | | |

**Reglas**

- Se revisan como máximo **8 productos**.
- De cada producto se registran las piezas en existencia de **3 sucursales**.
- Las existencias de una sucursal son válidas si están entre **0 y 500 piezas**.
- Un producto tiene **stock normal** si el **total** de piezas en las 3 sucursales es **mayor a 10**; si es de 10 o menos, tiene **stock bajo**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
CONTROL DE INVENTARIO

1.- Registrar un producto
2.- Reporte general
3.- Tabla de existencias
4.- Salir
```

- **Opción 1:** pide los datos de las 3 sucursales del siguiente producto y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  productos registrados, cuántos quedan como *Stock normal* y cuántos como *Stock bajo*
  (con sus porcentajes), y el promedio de existencias por producto.
- **Opción 3:** muestra la tabla de todos los productos registrados: una
  fila por producto, con sus 3 datos, su total y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan productos.** El programa no permite eliminar ni modificar
un producto ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 8.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `existencias`** guarda lo que el usuario **captura**: los 3 datos de
  cada producto.
- El **vector `totales`** guarda lo que el programa **calcula**: el total de cada
  producto.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del producto 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del producto 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos productos:

```
              existencias                totales
             [0]    [1]    [2]
fila 0        25     40     12     →     [0]  77
fila 1         3      2      4     →     [1]  9
fila 2   (vacía)                         [2]  (vacío)
 ...
fila 7   (vacía)                         [7]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 3 datos del siguiente producto en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 3 datos, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el total?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos productos
quedan en cada clasificación, y la opción 3 imprime cada fila de la matriz con
su total al final.

**¿Por qué no guardar el total como una columna más de la matriz?** Porque
entonces la matriz tendría columnas de dos tipos: 3 que captura el usuario y 1
que calcula el programa. Tendrías que recordar que la columna `[3]` "no
cuenta" al capturar ni al sumar. Con dos arreglos separados, la matriz siempre
se recorre de la columna 0 a la 2, sin excepciones.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de
una sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de arreglos

- [ ] Los datos que captura el usuario se guardan en una **matriz** `double` de
      8 × 3: cada fila es un producto y cada columna una sucursal.
- [ ] El total de cada producto se guarda en un **vector** `double` de 8
      posiciones: el total de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos productos se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de productos (8), los datos por producto (3), los
      límites de un dato válido (0 y 500) y el límite de
      la clasificación (10) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el total del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los productos registrados**, no las
      8 filas de la matriz.
- [ ] Si ya hay 8 productos registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay productos registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 500; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** sucursal (no se salta a
      la siguiente).
- [ ] Los resultados coinciden con **todos** los casos de prueba de este
      enunciado.

**Código fácil de seguir y leer**

- [ ] Todo el programa vive en `main` (sin funciones propias).
- [ ] Nombres de variable descriptivos.
- [ ] Comentarios que expliquen cada sección del programa (captura, reporte,
      tabla, validaciones).
- [ ] Compila y se ejecuta sin errores en Dev-C++.

### Actitudes / Valores (2 puntos) — Entrega

- [ ] Lo entregas en NEXUS, en la evidencia *"2.2 - Evidencia de Aprendizaje 2:
      Laboratorio de Programas"*, antes del **jueves 1 de octubre de 2026 a las
      8:40 p.m.**
- [ ] El archivo es de texto plano, con el nombre `EV2.2_ApellidoNombre.txt`.
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu
      código si se te pregunta.

## Ejemplo de ejecución

```
Opcion: 1

PRODUCTO 1
  Sucursal 1: 25
  Sucursal 2: 600
  ERROR! El dato debe estar entre 0 y 500 piezas
  Sucursal 2: -2
  ERROR! El dato debe estar entre 0 y 500 piezas
  Sucursal 2: 40
  Sucursal 3: 12

Total: 77 piezas -> Stock normal
```

```
Opcion: 3

TABLA DE EXISTENCIAS

                S1    S2    S3   Total
Producto 1      25    40    12      77   Stock normal
Producto 2       3     2     4       9   Stock bajo
Producto 3       4     3     3      10   Stock bajo
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay productos registrados |
| 2 | Registro del producto 1 | Producto 1: 25, 40, 12 | Total 77 → Stock normal |
| 3 | Registro del producto 2 | Producto 2: 3, 2, 4 | Total 9 → Stock bajo |
| 4 | Justo en el límite | Producto 3: 4, 3, 3 | Total 10 → **Stock bajo** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Stock normal: 1 (33.33%); Stock bajo: 2 (66.67%); Promedio de existencias por producto: 32 piezas |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 7 | Dato fuera de rango | Un dato de 600 o de -2 | Error; vuelve a pedir el dato de esa misma sucursal |
| 8 | Registro lleno | Opción 1 con 8 productos ya registrados | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
