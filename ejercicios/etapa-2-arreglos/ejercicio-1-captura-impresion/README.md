# Ejercicio 1 — Captura e impresión de un arreglo

*Etapa II — Arreglos · Temas: 2.1–2.4 · Solución: [`etapa-2-ejercicio-1.cpp`](etapa-2-ejercicio-1.cpp)*

## Historia de usuario

**Como** usuario, **quiero** capturar una lista de hasta 10 números enteros y
después verla completa en pantalla, **para** confirmar que los valores quedaron
guardados tal como los escribí.

## Contexto

Es el primer contacto con un arreglo: guardar varios valores bajo un solo nombre
y recorrerlos con un `for`. La captura y la impresión son dos pasos separados
sobre el mismo arreglo — primero se llena completo, y solo después se imprime.

## Criterios de aceptación

- [ ] Declara un arreglo de enteros de tamaño 10.
- [ ] Pide cuántos números se van a capturar. Si la cantidad es menor a 0 o
      mayor a 10, muestra un mensaje de error y la vuelve a pedir.
- [ ] Captura los números con un ciclo `for`, indicando el número de elemento
      (`Elemento 1:`, `Elemento 2:`, ...).
- [ ] Imprime los números con **otro** ciclo `for`, distinto al de captura.
- [ ] Solo recorre la cantidad capturada, no las 10 posiciones del arreglo.

## Ejemplo de ejecución

```
Introduce la cantidad de numeros a capturar
Max 10
Cantidad: 3

CAPTURA DEL ARREGLO

Elemento 1: 7
Elemento 2: -2
Elemento 3: 15

IMPRESION DEL ARREGLO

Elemento 1: 7
Elemento 2: -2
Elemento 3: 15
```

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Captura normal | cantidad = 3; números 7, -2, 15 | Imprime `7`, `-2`, `15` en ese orden |
| 2 | Cantidad mayor al tamaño | cantidad = 11 | `ERROR! Cantidad no permitida.` y vuelve a pedir la cantidad |
| 3 | Cantidad negativa | cantidad = -1 | Mismo error; vuelve a pedir la cantidad |
| 4 | Cantidad cero | cantidad = 0 | No pide ningún número; la impresión sale vacía |
| 5 | Arreglo lleno | cantidad = 10 | Pide y luego imprime los 10 elementos |

## Historial de cambios

Cómo fue cambiando la solución de este ejercicio a lo largo del curso.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 15 sep 2026 | Primera versión: arreglo `int numeros[10]`, validación de la cantidad con `do...while`, un `for` para capturar y otro para imprimir. Incluye un comentario "FORMA MANUAL" que muestra cómo sería capturar un solo elemento con `numeros[0]`. | Primer ejercicio de arreglos (2.1–2.4): pasar de variables sueltas a un solo nombre con índice. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
| 22 sep 2026 | En el comentario "FORMA MANUAL" faltaba un `<<` en `cout << "El elemento 1 es: "`. | Dentro del comentario no afectaba, pero si alguien lo descomentaba, no compilaba. |
