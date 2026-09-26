# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 09 — Moreno Mercado Fernando

## Programa 2 — Comisión de ventas con penalización por devoluciones

**Periodo: quincenal.** Una tienda paga a sus vendedores una comisión sobre
lo que venden en la quincena. Si el número de productos devueltos supera un
límite permitido, se le descuenta un porcentaje de su comisión como
penalización. Escribe un programa que calcule el pago neto quincenal de un
vendedor.

El programa debe leer:

- Monto vendido en la quincena (pesos).
- Número de productos devueltos en la quincena.

### Reglas de negocio

- Porcentaje de comisión: 8% del monto vendido
- Límite de devoluciones permitidas: 3
- Penalización por exceder el límite: 15% de la comisión
- Tasa de ISR: 10%

### Cálculo

1. **Comisión** = monto vendido × porcentaje de comisión.
2. **Penalización**: si los productos devueltos superan el límite de
   devoluciones permitidas, penalización = comisión × porcentaje de
   penalización; si no, penalización = 0.
3. **Ingreso total** = comisión − penalización.
4. **ISR** = ingreso total × tasa de ISR.
5. **Pago neto** = ingreso total − ISR.

### Prototipos sugeridos

```cpp
double calcularComision(double monto_vendido);
double calcularPenalizacion(int devoluciones, double comision);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);
```

Nota que `calcularPenalizacion` necesita **tanto** el número de devoluciones
(para saber si superó el límite) **como** la comisión (para saber sobre qué
monto aplicar el porcentaje) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para el porcentaje de comisión, el límite de
  devoluciones permitidas, el porcentaje de penalización y la tasa de ISR —
  nada de valores hardcode dentro de las funciones.
- Validar que el monto vendido sea > 0 y las devoluciones ≥ 0 (repetir
  captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: comisión, penalización (o "no aplica" si fue 0), ISR y
  pago neto.

### Casos de prueba

**Caso 1 — dentro del límite de devoluciones**
- Entrada: monto vendido = 60000.00, devoluciones = 2
- Salida esperada: comisión = 4800.00, penalización = 0.00, ISR = 480.00,
  pago neto = 4320.00

**Caso 2 — excede el límite de devoluciones**
- Entrada: monto vendido = 60000.00, devoluciones = 5
- Salida esperada: comisión = 4800.00, penalización = 720.00, ISR = 408.00,
  pago neto = 3672.00
