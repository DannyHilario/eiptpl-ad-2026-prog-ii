# Ejercicio 3 — Clasificador de temperaturas

*Etapa 0 — Repaso · Temas: validación con `do...while`, `if`/`else if`, contadores y acumuladores · Solución: [`etapa-0-ejercicio-3.cpp`](etapa-0-ejercicio-3.cpp) (incompleta)*

## Historia de usuario

**Como** encargado de una estación meteorológica, **quiero** registrar la
temperatura de varios días y ver cuántos fueron fríos, templados o calurosos,
**para** conocer el clima del periodo y su temperatura promedio.

## Contexto

Cada temperatura se clasifica en una de tres categorías:

| Categoría | Rango |
|---|---|
| Frío | menor a 15 °C |
| Templado | de 15 °C a 25 °C (incluye ambos extremos) |
| Caluroso | mayor a 25 °C |

Además, hay dos datos que se deben validar antes de usarlos:

- **La cantidad de días debe ser positiva.** Con 0 o menos días no hay nada que
  registrar, y el promedio dividiría entre cero.
- **Ninguna temperatura puede ser menor a −273.15 °C** (el cero absoluto). Es el
  límite físico: una lectura menor no es un día "muy frío", es un dato
  imposible, y se rechaza antes de clasificarlo.

## Criterios de aceptación

- [ ] Pide la cantidad de días; si es 0 o negativa, muestra un error y la vuelve
      a pedir, **antes** de entrar al ciclo de captura.
- [ ] Por cada día (ciclo `for`), pide la temperatura; si es menor a −273.15,
      muestra un error y la vuelve a pedir para ese mismo día.
- [ ] El cero absoluto es una constante con nombre.
- [ ] Clasifica cada temperatura válida con `if`/`else if` y suma 1 al contador
      de su categoría.
- [ ] Acumula las temperaturas para calcular el promedio.
- [ ] Al final muestra cuántos días fueron fríos, templados y calurosos, y la
      temperatura promedio.

## Ejemplo de ejecución

```
Introduce la cantidad de temperaturas: -2
ERROR. Valor no permitido. La cantidad de temperaturas debe ser un numero positivo
Introduce la cantidad de temperaturas: 3

Temperatura del dia 1: -300
ERROR. Esa temperatura esta por debajo del cero absoluto (-273.15 C)
Temperatura del dia 1: 12
Temperatura del dia 2: 28
Temperatura del dia 3: 9

********* REPORTE FINAL *********

Dias frios: 2
Dias templados: 0
Dias calurosos: 1

Temperatura promedio: 16.33
```

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Cantidad inválida | días = -2, luego 0 | Error en ambos; vuelve a pedir la cantidad |
| 2 | Temperatura imposible | -300 | Error de cero absoluto; vuelve a pedir la temperatura del mismo día |
| 3 | Justo en el cero absoluto | -273.15 | Se acepta y cuenta como día frío |
| 4 | Grupo mixto | 12, 28, 9 | Fríos 2, templados 0, calurosos 1, promedio 16.33 |
| 5 | Límites de "Templado" | 15, 25 | Ambos cuentan como templados |
| 6 | Justo afuera de los límites | 14.9, 25.1 | Uno frío y uno caluroso |

## Historial de cambios

Cómo fue cambiando la solución de este ejercicio a lo largo del curso.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 14 ago 2026 | Primer avance: la validación de la cantidad de días con `do...while`, y un `for` que por ahora solo imprime `Ejecucion 1`, `Ejecucion 2`... | Construir y probar primero la validación y el ciclo, antes de meter la lógica de cada día. |
| 17 ago 2026 | El archivo se movió a la carpeta de la Etapa 0. | Reorganización por etapas. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |

**Pendiente:** la solución está incompleta. Solo cumple el primer criterio
(validar la cantidad de días). Dentro del `for` falta pedir cada temperatura,
validarla contra el cero absoluto, clasificarla y acumularla, y falta el
reporte final. Es buen ejercicio para terminarlo tú.
