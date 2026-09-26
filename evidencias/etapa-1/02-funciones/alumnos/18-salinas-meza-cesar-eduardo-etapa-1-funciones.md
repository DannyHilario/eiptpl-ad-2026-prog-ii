# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 18 — Salinas Meza Cesar Eduardo

## Programa 2 — Freelance con bono por horas trabajadas

**Periodo: semanal.** Un freelancer cobra por hora trabajada en la semana.
Si supera un umbral de horas, recibe un bono adicional. Escribe un programa
que calcule el pago neto semanal.

El programa debe leer:

- Horas trabajadas en la semana.

### Reglas de negocio

- Tarifa por hora: $180.00
- Umbral semanal de horas: 35
- Bono por superar el umbral: 8% del pago base
- Tasa de ISR: 10%

### Cálculo

1. **Pago base** = horas trabajadas × tarifa por hora.
2. **Bono**: si las horas trabajadas superan el umbral semanal, bono = pago
   base × porcentaje de bono; si no, bono = 0.
3. **Ingreso total** = pago base + bono.
4. **ISR** = ingreso total × tasa de ISR.
5. **Pago neto** = ingreso total − ISR.

### Prototipos sugeridos

```cpp
double calcularPagoBase(double horas_trabajadas);
double calcularBono(double horas_trabajadas, double pago_base);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);
```

Nota que `calcularBono` necesita **tanto** las horas trabajadas (para saber
si superó el umbral) **como** el pago base (para saber sobre qué monto
calcular el bono) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para la tarifa por hora, el umbral semanal de horas
  y el porcentaje de bono, y la tasa de ISR — nada de valores hardcode
  dentro de las funciones.
- Validar que las horas trabajadas sean ≥ 0 (repetir captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: pago base, bono (o "no aplica" si fue 0), ISR y pago
  neto.

### Casos de prueba

**Caso 1 — no alcanza el umbral**
- Entrada: horas trabajadas = 30
- Salida esperada: pago base = 5400.00, bono = 0.00, ISR = 540.00, pago
  neto = 4860.00

**Caso 2 — supera el umbral**
- Entrada: horas trabajadas = 40
- Salida esperada: pago base = 7200.00, bono = 576.00, ISR = 777.60, pago
  neto = 6998.40
