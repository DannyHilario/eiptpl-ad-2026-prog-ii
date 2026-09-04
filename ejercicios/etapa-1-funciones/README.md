# Etapa I — Funciones (ejercicios)

Resumen a alto nivel de cada ejercicio: qué resuelve, qué funciones usa y por qué,
sin repetir el código completo (eso ya vive en el `.cpp` correspondiente).

**Regla de diseño que siguen (o deben seguir) todos los ejercicios de esta etapa:**
las funciones que hacen el cálculo son "puras" — reciben datos, regresan un
resultado, y **no leen con `cin` ni escriben con `cout`**. Todo la interacción con
el usuario (captura, validación, impresión del resultado) vive en `main()`. Esto
es a propósito: separa "qué calcula el programa" de "cómo se comunica con el
usuario", que es la idea central de dividir en funciones.

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

`etapa-1-ejercicio-3.cpp` — **propuesto, pendiente de resolver en clase**.

### Enunciado

Escribe un programa que calcule el total a pagar de una compra, considerando
descuento por volumen (a mayor cantidad comprada, mayor porcentaje de descuento)
e IVA.

El programa debe leer, para una compra:

- Cantidad de piezas compradas.
- Precio unitario.

Y calcular:

1. **Subtotal** = cantidad × precio unitario.
2. **Descuento**, según la siguiente tabla de rangos por cantidad de piezas:

   | Piezas compradas | Descuento sobre el subtotal |
   |---|---|
   | 1 – 9 | 0% |
   | 10 – 49 | 5% |
   | 50 en adelante | 12% |

3. **Base gravable** = subtotal − descuento.
4. **IVA** = base gravable × 16%.
5. **Total a pagar** = base gravable + IVA.

### Prototipos sugeridos

```cpp
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);
```

Nota que `calcularDescuento` necesita **tanto** la cantidad (para saber en qué
rango cae) **como** el subtotal (para saber sobre qué monto aplicar el
porcentaje) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para los límites de rango, los porcentajes de descuento
  y la tasa de IVA — nada de valores hardcode dentro de las funciones (mismo
  criterio que se está corrigiendo en el ejercicio 2).
- Validar que cantidad > 0 y precio unitario > 0 (repetir captura si no cumple,
  igual que en los ejercicios 1 y 2).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()` interactúa
  con el usuario.
- Mostrar al final: subtotal, descuento aplicado, IVA y total a pagar.

### Por qué este ejercicio

Reutiliza el mismo patrón de "tabla de rangos con excedente/porcentaje" del
ejercicio 2 (para reforzarlo en un contexto distinto: compras, no nómina), pero
suma una función con **dos parámetros** que dependen entre sí (`cantidad` y
`subtotal`), y una cadena de 4 funciones en vez de 3 — un paso más hacia programas
con más funciones colaborando entre sí.
