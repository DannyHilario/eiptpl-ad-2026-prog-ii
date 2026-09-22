# Ejercicio 2 — Sueldo semanal con ISR por rangos

*Etapa I — Funciones · Temas: 1.1–1.3 · Solución: [`etapa-1-ejercicio-2.cpp`](etapa-1-ejercicio-2.cpp)*

## Historia de usuario

**Como** encargado de nómina, **quiero** capturar el sueldo diario de un
empleado y obtener su recibo semanal con el ISR ya descontado, **para** saber
cuánto le voy a pagar realmente.

## Contexto

El ISR no es un porcentaje fijo como en el
[Ejercicio 1](../ejercicio-1-sueldo-por-hora/README.md): depende de en qué
rango de la tabla cae el sueldo. Cada rango tiene una cuota fija, y además se
cobra un porcentaje sobre lo que el sueldo **excede** el límite inferior de su
rango.

**Tabla de ISR semanal**

| Rango | Límite inferior | Límite superior | Cuota fija | % sobre el excedente |
|---|---|---|---|---|
| 1 | $0.01 | $750.00 | $45.00 | 2.57% |
| 2 | $750.01 | $2,340.00 | $119.00 | 12% |
| 3 | $2,340.01 | en adelante | $514.00 | 22.54% |

**Cálculo**

1. Sueldo bruto = sueldo diario × 7.
2. Identificar en qué rango cae el sueldo bruto.
3. Excedente = sueldo bruto − límite inferior del rango.
4. ISR = excedente × porcentaje del rango + cuota fija del rango.
5. Sueldo neto = sueldo bruto − ISR.

**Ejemplo del cálculo (rango 2):** sueldo diario $200 → bruto $1,400 → cae en
el rango 2 → excedente = 1400 − 750.01 = 649.99 → ISR = 649.99 × 0.12 + 119 =
$197.00 → neto = $1,203.00.

## Criterios de aceptación

- [ ] Cada dato de la tabla es una constante con nombre (por ejemplo
      `LIMITE_INFERIOR_RANGO_1`, `CUOTA_FIJA_RANGO_2`), igual que `DIAS_SEMANA`
      — ningún número de la tabla aparece escrito dentro de las funciones.
- [ ] Usa estas funciones, sin `cin` ni `cout` dentro de ellas:
      - `double calcularSueldoBruto(double sueldo_diario)`
      - `double calcularISR(double sueldo_bruto)`
      - `double calcularSueldoNeto(double sueldo_bruto, double isr)`
- [ ] `calcularISR` identifica el rango con `if`/`else if`.
- [ ] Si el sueldo diario es menor a $0.01, muestra un error y lo vuelve a pedir.
- [ ] Imprime: sueldo diario, sueldo bruto, ISR y sueldo neto.
- [ ] Compila sin warnings con `g++ -std=c++17 -Wall`.

## Ejemplo de ejecución

```
Introduce el sueldo diario del empleado: 500

RECIBO SEMANAL

Sueldo diario: 500
Sueldo bruto: 3500
ISR: -775.462
Sueldo neto: 2724.54
```

## Casos de prueba

Los montos están redondeados a 2 decimales; `cout` sin formato puede mostrar
más o menos decimales (por ejemplo `62.9897` en vez de `62.99`).

| # | Caso | Sueldo diario | Sueldo bruto | ISR | Sueldo neto |
|---|---|---|---|---|---|
| 1 | Rango 1 | 100 | 700.00 | 62.99 | 637.01 |
| 2 | Rango 2 | 200 | 1400.00 | 197.00 | 1203.00 |
| 3 | Rango 2 (otro) | 400 | 2800.00 | 617.68 | 2182.32 |
| 4 | Rango 3 | 500 | 3500.00 | 775.46 | 2724.54 |
| 5 | Sueldo inválido | 0 | — | — | `ERROR! Salario no valido` y vuelve a pedirlo |

## Historial de cambios

Cómo fue cambiando la solución de este ejercicio a lo largo del curso.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 21 ago 2026 | Primera versión: validación del sueldo diario y todo el cálculo del ISR dentro de `main`, con los números de la tabla escritos directo en la fórmula (`0.0257`, `45`, `750`...). | Resolver el problema primero, sin preocuparse todavía por la estructura. |
| 24 ago 2026 | El cálculo se separó en tres funciones: `calcularSueldoBruto`, `calcularISR` y `calcularSueldoNeto`. `main` solo captura, llama a las funciones e imprime. | Tema 1.3: prototipo, definición y llamada; separar "qué se calcula" de "cómo se muestra". |
| 4 sep 2026 | Cada número de la tabla pasó a una constante con nombre (`LIMITE_INFERIOR_RANGO_1`, `CUOTA_FIJA_RANGO_2`...), igual que `DIAS_SEMANA = 7`. | Evitar "números mágicos": al leer `CUOTA_FIJA_RANGO_2` se entiende qué es; al leer `119`, no. |
| 4 sep 2026 | `float` cambió a `double` en todo el programa. | `double` tiene más precisión para montos de dinero. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
| 22 sep 2026 | Se quitó la variable `excedente`, que se declaraba en `main` pero nunca se usaba. | `g++ -Wall` avisaba `unused variable 'excedente'`: el excedente se calcula dentro de `calcularISR`, no en `main`. |

**Este programa sigue creciendo en la Etapa II:** las 13 constantes se agrupan
en arreglos en el
[Ejercicio 3 de arreglos](../../etapa-2-arreglos/ejercicio-3-isr-con-arreglos/README.md),
y en una matriz en el
[Ejercicio 4](../../etapa-2-arreglos/ejercicio-4-isr-con-matriz/README.md).
