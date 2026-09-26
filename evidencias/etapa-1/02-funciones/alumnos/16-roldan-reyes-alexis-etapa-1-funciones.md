# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Roldan Reyes Alexis
**Matrícula:** 2253898

## Programa 2 — Vendedor de seguros con bono por pólizas

**Periodo: quincenal.** Una aseguradora paga a sus vendedores una comisión
fija por cada póliza vendida en la quincena. Si el número de pólizas
vendidas supera una meta, reciben un bono adicional sobre su comisión.
Escribe un programa que calcule el pago neto quincenal de un vendedor.

El programa debe leer:

- Número de pólizas vendidas en la quincena.

### Reglas de negocio

- Comisión por póliza: $350.00
- Meta quincenal de pólizas: 10
- Bono por superar la meta: 12% de la comisión
- Tasa de ISR: 10%

### Cálculo

1. **Comisión** = pólizas vendidas × comisión por póliza.
2. **Bono**: si las pólizas vendidas superan la meta quincenal, bono =
   comisión × porcentaje de bono; si no, bono = 0.
3. **Ingreso total** = comisión + bono.
4. **ISR** = ingreso total × tasa de ISR.
5. **Pago neto** = ingreso total − ISR.

### Prototipos sugeridos

```cpp
double calcularComision(int polizas_vendidas);
double calcularBono(int polizas_vendidas, double comision);
double calcularISR(double ingreso_total);
double calcularPagoNeto(double ingreso_total, double isr);
```

Nota que `calcularBono` necesita **tanto** las pólizas vendidas (para saber
si superó la meta) **como** la comisión (para saber sobre qué monto calcular
el bono) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para la comisión por póliza, la meta quincenal de
  pólizas y el porcentaje de bono, y la tasa de ISR — nada de valores
  hardcode dentro de las funciones.
- Validar que las pólizas vendidas sean ≥ 0 (repetir captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: comisión, bono (o "no aplica" si fue 0), ISR y pago
  neto.

### Casos de prueba

**Caso 1 — no alcanza la meta**
- Entrada: pólizas vendidas = 7
- Salida esperada: comisión = 2450.00, bono = 0.00, ISR = 245.00, pago neto
  = 2205.00

**Caso 2 — supera la meta**
- Entrada: pólizas vendidas = 13
- Salida esperada: comisión = 4550.00, bono = 546.00, ISR = 509.60, pago
  neto = 4586.40
