# Ejercicio 4 — Sueldo semanal con ISR usando una matriz

*Etapa II — Arreglos · Temas: 2.2–2.3 (arreglos bidimensionales) + funciones (Etapa I) · Solución: [`etapa-2-ejercicio-4.cpp`](etapa-2-ejercicio-4.cpp)*

## Historia de usuario

**Como** encargado de nómina, **quiero** capturar el sueldo diario de un
empleado y obtener su recibo semanal con el ISR ya descontado, **para** saber
cuánto le voy a pagar realmente.

## Contexto

Es el mismo problema del
[Ejercicio 3](../ejercicio-3-isr-con-arreglos/README.md), pero en lugar de 4
arreglos separados (uno por columna), la tabla completa se guarda en **una sola
matriz** de 3 filas × 4 columnas: cada fila es un rango y cada columna es un
dato del rango. Así la matriz en el código se ve igual que la tabla en papel.

**Tabla de ISR semanal**

| Rango (fila) | [0] Límite inferior | [1] Límite superior | [2] Cuota fija | [3] % sobre el excedente |
|---|---|---|---|---|
| 1 → `[0]` | $0.01 | $750.00 | $45.00 | 2.57% |
| 2 → `[1]` | $750.01 | $2,340.00 | $119.00 | 12% |
| 3 → `[2]` | $2,340.01 | en adelante | $514.00 | 22.54% |

El cálculo es el mismo del Ejercicio 3: sueldo bruto = diario × 7; ISR =
(bruto − límite inferior) × porcentaje + cuota fija; neto = bruto − ISR.

## Criterios de aceptación

- [ ] Guarda la tabla en una matriz global `const double` de `[3][4]`,
      inicializada en la declaración, con una fila por rango.
- [ ] Usa las mismas tres funciones del Ejercicio 3, sin `cin` ni `cout` dentro
      de ellas: `calcularSueldoBruto`, `calcularISR`, `calcularSueldoNeto`.
- [ ] `calcularISR` obtiene el índice de la fila y lee límite, cuota y
      porcentaje como `matriz[fila][columna]` — una sola fórmula para los tres
      rangos.
- [ ] Si el sueldo diario es menor al límite inferior del rango 1, muestra un
      error y lo vuelve a pedir.
- [ ] Imprime: sueldo diario, sueldo bruto, ISR y sueldo neto.
- [ ] Compila sin warnings con `g++ -std=c++17 -Wall`.

## Ejemplo de ejecución

```
Introduce el sueldo diario del empleado: 200

RECIBO SEMANAL

Sueldo diario: 200
Sueldo bruto: 1400
ISR: -196.999
Sueldo neto: 1203
```

## Casos de prueba

Mismos casos que el Ejercicio 3 — deben dar exactamente los mismos resultados.

| # | Caso | Sueldo diario | Sueldo bruto | ISR | Sueldo neto |
|---|---|---|---|---|---|
| 1 | Rango 1 | 100 | 700.00 | 62.99 | 637.01 |
| 2 | Rango 2 | 200 | 1400.00 | 197.00 | 1203.00 |
| 3 | Rango 3 | 500 | 3500.00 | 775.46 | 2724.54 |
| 4 | Sueldo inválido | 0 | — | — | `ERROR! Salario no valido` y vuelve a pedirlo |

## Historial de cambios

Es el último paso del programa de ISR, que ya pasó por tres versiones: primero
todo en `main`, luego con funciones y constantes
([Etapa I, Ej. 2](../../etapa-1-funciones/ejercicio-2-isr-por-rangos/README.md)),
y después con arreglos ([Ejercicio 3](../ejercicio-3-isr-con-arreglos/README.md)).
En esas fichas está el historial completo.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 17 sep 2026 | **Nace este ejercicio:** los 4 arreglos del Ejercicio 3 se convirtieron en una sola matriz `MATRIZ_TABLA_ISR[3][4]`, con una fila por rango y una columna por dato. | Matrices (2.2–2.3): una tabla de varias columnas se guarda como un arreglo de dos dimensiones. |
| 17 sep 2026 | Se corrigió un bug durante el cambio: la fórmula usaba las columnas al revés (multiplicaba por la cuota fija y sumaba el porcentaje). Se detectó porque los resultados no coincidían con los del Ejercicio 3 con las mismas entradas. | Con una matriz es fácil equivocarse de columna: `[2]` y `[3]` no dicen qué contienen. Por eso sirve comparar contra una versión que ya funcionaba. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
| 22 sep 2026 | Se quitó la variable `excedente`, que se declaraba en `main` pero nunca se usaba (venía copiada desde la Etapa I). | `g++ -Wall` avisaba `unused variable 'excedente'`. |
