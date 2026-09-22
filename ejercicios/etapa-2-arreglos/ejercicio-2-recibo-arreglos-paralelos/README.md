# Ejercicio 2 — Recibo de pago con arreglos paralelos

*Etapa II — Arreglos · Temas: 2.1–2.3 · Solución: [`etapa-2-ejercicio-2.cpp`](etapa-2-ejercicio-2.cpp)*

## Historia de usuario

**Como** cajero de una farmacia, **quiero** escribir la clave de un artículo y
la cantidad, y obtener un recibo con la descripción, el precio y el total,
**para** cobrar sin tener que buscar el precio a mano.

## Contexto

La farmacia maneja 3 artículos:

| Clave | Descripción | Precio unitario |
|---|---|---|
| 1 | Paracetamol | $45.00 |
| 2 | Gel antibacterial | $38.00 |
| 3 | Cubrebocas | $25.50 |

Esto se podría resolver con un `switch` de 3 casos, repitiendo el mismo cálculo
en cada uno. Con dos arreglos **paralelos** — uno de precios y uno de
descripciones, donde la posición `I` de ambos corresponde al mismo artículo — la
clave sirve directamente para encontrar el dato: el artículo con clave `1` está
en la posición `0`, el de clave `2` en la posición `1`, y así.

## Criterios de aceptación

- [ ] Guarda los precios en un arreglo `double` y las descripciones en un
      arreglo `string`, ambos de tamaño `TOTAL_ARTICULOS` (constante, 3) e
      inicializados en la declaración.
- [ ] Pide la clave del artículo y la cantidad de artículos.
- [ ] Si la clave no está entre 1 y 3, muestra un mensaje de error y la vuelve a
      pedir — nunca accede al arreglo con una posición inválida.
- [ ] Obtiene precio y descripción con el índice `clave - 1`, sin usar `switch`
      ni `if` por cada artículo.
- [ ] Calcula el total como `precio unitario × cantidad`.
- [ ] Imprime un recibo con: clave y descripción, precio unitario, cantidad y
      total a pagar.

## Ejemplo de ejecución

```
Clave del articulo (1 a 3): 2
Cantidad de articulos: 3

 RECIBO DE PAGO

Articulo: 2 | Gel antibacterial
Precio unitario: $38
Cantidad: 3

TOTAL A PAGAR: $114

__________________________________
GRACIAS POR SU COMPRA
```

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Primer artículo | clave = 1, cantidad = 2 | Paracetamol, $45, total $90 |
| 2 | Artículo intermedio | clave = 2, cantidad = 3 | Gel antibacterial, $38, total $114 |
| 3 | Precio con decimales | clave = 3, cantidad = 4 | Cubrebocas, $25.5, total $102 |
| 4 | Clave mayor al rango | clave = 4 | Mensaje de error y vuelve a pedir la clave |
| 5 | Clave cero o negativa | clave = 0 | Mensaje de error y vuelve a pedir la clave |

## Historial de cambios

Cómo fue cambiando la solución de este ejercicio a lo largo del curso.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 15 sep 2026 | Primera versión: dos arreglos paralelos (`precio_unitario` y `descripcion_articulo`) consultados con `clave_articulo - 1`. El `switch` de 3 casos que resolvía lo mismo quedó en un comentario, para comparar ambas formas. | Tema 2.3: un arreglo inicializado en la declaración funciona como tabla de consulta y evita repetir código por cada caso. |
| 17 sep 2026 | Limpieza: se quitaron líneas en blanco sobrantes al final del archivo. | Sin cambios en el funcionamiento. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
| 22 sep 2026 | Se agregó la validación de la clave con `do...while`: si no está entre 1 y 3, muestra `ERROR! Clave de articulo no valida.` y la vuelve a pedir. El tamaño de los arreglos y el límite de la validación usan la constante `TOTAL_ARTICULOS`. | Antes, con clave 4 el programa leía fuera del arreglo e imprimía basura, por ejemplo `Precio unitario: $-3.38968e+240`. C++ no revisa los límites de un arreglo (tema 2.2): validar el índice le toca al programador. |
