# Ejercicio 3 — Sueldo semanal con ISR usando arreglos

*Etapa II — Arreglos · Temas: 2.2–2.3 + funciones (Etapa I) · Solución: [`etapa-2-ejercicio-3.cpp`](etapa-2-ejercicio-3.cpp)*

## Historia de usuario

**Como** encargado de nómina, **quiero** capturar el sueldo diario de un
empleado y obtener su recibo semanal con el ISR ya descontado, **para** saber
cuánto le voy a pagar realmente.

## Contexto

Es el mismo problema del
[Ejercicio 2 de la Etapa I](../../etapa-1-funciones/ejercicio-2-isr-por-rangos/README.md),
pero ahí cada dato de la tabla era una constante suelta (`CUOTA_FIJA_RANGO_1`,
`CUOTA_FIJA_RANGO_2`, ...). Aquí cada **columna** de la tabla se guarda en un
arreglo constante, y el número de rango se convierte en el índice para leer los
tres datos que se necesitan.

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

## Criterios de aceptación

- [ ] Guarda límites inferiores, límites superiores, cuotas fijas y porcentajes
      en arreglos `const double` globales (uno por columna de la tabla).
- [ ] `DIAS_SEMANA` es una constante con nombre, no un 7 escrito en el cálculo.
- [ ] Usa estas funciones, sin `cin` ni `cout` dentro de ellas:
      - `double calcularSueldoBruto(double sueldo_diario)`
      - `double calcularISR(double sueldo_bruto)`
      - `double calcularSueldoNeto(double sueldo_bruto, double isr)`
- [ ] `calcularISR` decide el rango con `if`/`else if` y después calcula el ISR
      con **una sola** fórmula que usa el índice del rango — no repite la
      fórmula tres veces.
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
| 3 | Rango 3 | 500 | 3500.00 | 775.46 | 2724.54 |
| 4 | Sueldo inválido | 0 | — | — | `ERROR! Salario no valido` y vuelve a pedirlo |

Los resultados deben ser **idénticos** a los del Ejercicio 2 de la Etapa I con
las mismas entradas: cambió cómo se guardan los datos, no el cálculo.

## Historial de cambios

Este ejercicio no empezó de cero: es el mismo programa de ISR, que fue creciendo
conforme avanzaba el curso. Los primeros renglones son la historia del
[Ejercicio 2 de la Etapa I](../../etapa-1-funciones/ejercicio-2-isr-por-rangos/README.md),
del que se copió.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 21 ago 2026 | *(Etapa I, Ej. 2)* Primera versión: todo el cálculo dentro de `main`, con los números de la tabla escritos directo en la fórmula (`0.0257`, `45`, `750`...). | Resolver el problema primero, sin preocuparse todavía por la estructura. |
| 24 ago 2026 | *(Etapa I, Ej. 2)* El cálculo se separó en tres funciones: `calcularSueldoBruto`, `calcularISR` y `calcularSueldoNeto`. | Tema 1.3: dividir el programa en funciones. |
| 4 sep 2026 | *(Etapa I, Ej. 2)* Los números de la tabla pasaron a constantes con nombre (`CUOTA_FIJA_RANGO_1`...), 13 en total, y `float` pasó a `double`. | Evitar "números mágicos": un nombre dice qué significa cada valor. |
| 17 sep 2026 | **Nace este ejercicio:** las 13 constantes se agruparon en 4 arreglos, uno por columna de la tabla (`LIMITE_INFERIOR[3]`, `CUOTA_FIJA[3]`...). `calcularISR` ahora solo decide el número de rango y aplica **una** fórmula con ese índice, en lugar de repetirla 3 veces. | Tema 2.3: un arreglo agrupa datos del mismo tipo que se usan igual. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
| 22 sep 2026 | Se quitó la variable `excedente`, que se declaraba en `main` pero nunca se usaba (venía copiada desde la Etapa I). | `g++ -Wall` avisaba `unused variable 'excedente'`. |

**Siguiente paso:** el [Ejercicio 4](../ejercicio-4-isr-con-matriz/README.md)
junta estos 4 arreglos en una sola matriz.
