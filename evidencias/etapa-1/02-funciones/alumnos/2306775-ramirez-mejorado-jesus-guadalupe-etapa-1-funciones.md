# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Ramirez Mejorado Jesus Guadalupe
**Matrícula:** 2306775

## Programa 2 — Pago por llamadas atendidas en call center

**Periodo: semanal.** Un call center paga a sus agentes por cada llamada
atendida en la semana. Si el agente supera una meta semanal de llamadas,
recibe un bono adicional. Escribe un programa que calcule el pago neto
semanal de un agente.

El programa debe leer:

- Número de llamadas atendidas en la semana.

### Reglas de negocio

- Tarifa por llamada: $8.00
- Meta semanal de llamadas: 200
- Bono por superar la meta: 10% del pago base
- Tasa de ISR: 10%

### Cálculo

1. **Pago base** = llamadas atendidas × tarifa por llamada.
2. **Bono**: si las llamadas atendidas superan la meta semanal, bono = pago
   base × porcentaje de bono; si no, bono = 0.
3. **Ingreso total** = pago base + bono.
4. **ISR** = ingreso total × tasa de ISR.
5. **Pago neto** = ingreso total − ISR.

### Prototipos sugeridos

```cpp
double calcularPagoBase(int llamadas_atendidas);
double calcularBono(int llamadas_atendidas, double pago_base);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);
```

Nota que `calcularBono` necesita **tanto** las llamadas atendidas (para saber
si superó la meta) **como** el pago base (para saber sobre qué monto calcular
el bono) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para la tarifa por llamada, la meta semanal de
  llamadas y el porcentaje de bono, y la tasa de ISR — nada de valores
  hardcode dentro de las funciones.
- Validar que las llamadas atendidas sean ≥ 0 (repetir captura si no
  cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: pago base, bono (o "no aplica" si fue 0), ISR y pago
  neto.

### Casos de prueba

**Caso 1 — no alcanza la meta**
- Entrada: llamadas atendidas = 150
- Salida esperada: pago base = 1200.00, bono = 0.00, ISR = 120.00, pago neto
  = 1080.00

**Caso 2 — supera la meta**
- Entrada: llamadas atendidas = 250
- Salida esperada: pago base = 2000.00, bono = 200.00, ISR = 220.00, pago
  neto = 1980.00
