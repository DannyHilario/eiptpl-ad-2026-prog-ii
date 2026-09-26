# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 02 — Espinosa Saucedo Angel Xavier

## Programa 2 — Comisión de ventas con bono por meta

**Periodo: quincenal.** Una empresa paga a sus vendedores una comisión fija
sobre lo que venden en la quincena, más un bono extra si superan una meta
quincenal de ventas. Escribe un programa que calcule el pago neto quincenal
de un vendedor.

El programa debe leer:

- Monto vendido en la quincena (pesos).

### Reglas de negocio

- Porcentaje de comisión: 8% del monto vendido
- Meta quincenal de ventas: $50,000.00
- Bono por meta: 10% de la comisión
- Tasa de ISR: 10%

### Cálculo

1. **Comisión** = monto vendido × porcentaje de comisión.
2. **Bono por meta**: si el monto vendido **supera** la meta quincenal de
   ventas, el vendedor recibe un bono adicional igual al porcentaje de bono
   aplicado sobre su comisión; si no la supera, el bono es 0. (Es una
   condición de umbral, no una tabla de rangos: solo hay "llegó a la meta" o
   "no llegó".)
3. **Ingreso total** = comisión + bono.
4. **ISR** = ingreso total × tasa de ISR.
5. **Pago neto** = ingreso total − ISR.

### Prototipos sugeridos

```cpp
double calcularComision(double monto_vendido, double porcentaje_comision);
double calcularBono(double monto_vendido, double comision);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);
```

Nota que `calcularBono` necesita **tanto** el monto vendido (para saber si
superó la meta) **como** la comisión (para saber sobre qué monto calcular el
bono) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para el porcentaje de comisión, la meta de ventas, el
  porcentaje de bono y la tasa de ISR — nada de valores hardcode dentro de
  las funciones.
- Validar que el monto vendido sea > 0 (repetir captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: comisión, bono (o "no aplica" si fue 0), ISR y pago neto.

### Casos de prueba

Usa estos valores para verificar tu programa (no muestran cómo resolverlo,
solo el resultado esperado):

**Caso 1 — no alcanza la meta**
- Entrada: monto vendido = 40000.00
- Salida esperada: comisión = 3200.00, bono = 0.00, ISR = 320.00,
  pago neto = 2880.00

**Caso 2 — supera la meta**
- Entrada: monto vendido = 70000.00
- Salida esperada: comisión = 5600.00, bono = 560.00, ISR = 616.00,
  pago neto = 5544.00
