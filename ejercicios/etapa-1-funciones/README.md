# Etapa I — Funciones (ejercicios)

Resumen a alto nivel de cada ejercicio: qué resuelve, qué funciones usa y por qué,
sin repetir el código completo (eso ya vive en el `.cpp` correspondiente).

**Regla de diseño que siguen (o deben seguir) todos los ejercicios de esta etapa:**
las funciones que hacen el cálculo son "puras" — reciben datos, regresan un
resultado, y **no leen con `cin` ni escriben con `cout`**. Todo la interacción con
el usuario (captura, validación, impresión del resultado) vive en `main()`. Esto
es a propósito: separa "qué calcula el programa" de "cómo se comunica con el
usuario", que es la idea central de dividir en funciones.

**Segunda regla de diseño:** si un dato se puede **derivar** de otro que ya se
capturó, no se vuelve a pedir por separado — se calcula dentro de una función
a partir del dato original. Pedir ambos como capturas independientes abre la
puerta a que el usuario introduzca valores que no cuadran entre sí (por
ejemplo, "días de retraso" como dato suelto, sin relación con los "días
totales de uso" ya capturados). Esto aplica tanto a los ejercicios de este
archivo como a los enunciados personalizados de la
[Evidencia 1.1](../../evidencias/etapa-1/02-funciones/descripcion.md).

---

## Ejercicio 1 — Sueldo por hora con impuesto

`etapa-1-ejercicio-1.cpp` — **completo**.

Calcula el sueldo neto de varios empleados a partir de sus horas trabajadas y su
tarifa por hora, aplicando una tasa de impuesto fija.

- `calcularSueldoBruto(horas_trabajadas, tarifa_x_hora)` — `horas × tarifa`.
- `calcularImpuesto(sueldo_bruto)` — aplica `TASA_IMPUESTO` (constante, 16%).
- `calcularSueldoNeto(sueldo_bruto, impuesto)` — `bruto − impuesto`.

`main()` valida cantidad de empleados, tarifa y horas (máximo `HORAS_MAXIMAS_PERMITIDAS`,
constante), y repite el ciclo por cada empleado.

Ya usa constantes (`TASA_IMPUESTO`, `HORAS_MAXIMAS_PERMITIDAS`) en vez de valores
hardcode — es el ejemplo a seguir para el ejercicio 2.

---

## Ejercicio 2 — Sueldo semanal con ISR por rangos

`etapa-1-ejercicio-2.cpp` — **completo, pendiente un ajuste**.

Calcula el sueldo neto semanal de un empleado a partir de su sueldo diario,
aplicando ISR según una tabla de tres rangos (cuota fija + porcentaje sobre
excedente).

- `calcularSueldoBruto(sueldo_diario)` — `sueldo_diario × 7`.
- `calcularISR(sueldo_bruto)` — identifica el rango y aplica cuota fija +
  porcentaje sobre el excedente.
- `calcularSueldoNeto(sueldo_bruto, isr)` — `bruto − isr`.

**Pendiente:** los límites de rango, cuotas fijas y porcentajes de la tabla de ISR
están hardcode dentro de `calcularISR` (`750`, `2340`, `45`, `119`, `514`, `0.0257`,
`0.12`, `0.2254`). Deben pasar a ser constantes con nombre, igual que en el
ejercicio 1 — además de más legible, es justo lo que pide la rúbrica de la
evidencia 1 ("uso de constantes para el catálogo/tarifas").

---

## Ejercicio 3 — Facturación con descuento por volumen e IVA

Este ejercicio es el Programa 1 (común) de la
[Evidencia 1.1](../../evidencias/etapa-1/02-funciones/descripcion.md) — el
enunciado completo vive ahí, no aquí, para no tener dos fuentes de verdad.
