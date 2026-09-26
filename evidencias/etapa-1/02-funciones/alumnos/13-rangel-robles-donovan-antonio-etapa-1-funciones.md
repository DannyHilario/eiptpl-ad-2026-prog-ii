# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 13 — Rangel Robles Donovan Antonio

## Programa 2 — Taller mecánico con recargo por refacciones costosas

**Periodo: semanal.** Un taller mecánico cobra por hora de mano de obra más
el costo de las refacciones usadas en el servicio. Si el monto de
refacciones supera un límite, se cobra un recargo administrativo adicional
sobre ese monto. Escribe un programa que calcule el total a pagar de un
servicio.

El programa debe leer:

- Horas de mano de obra.
- Monto de refacciones usadas (pesos).

### Reglas de negocio

- Tarifa por hora de mano de obra: $250.00
- Límite de refacciones sin recargo: $1,000.00
- Recargo administrativo por exceder el límite: 5% del monto de refacciones
- Tasa de IVA: 16%

### Cálculo

1. **Costo de mano de obra** = horas × tarifa por hora de mano de obra.
2. **Recargo por refacciones**: si el monto de refacciones supera el límite
   de refacciones sin recargo, recargo = monto de refacciones × porcentaje
   de recargo; si no, recargo = 0.
3. **Subtotal** = costo de mano de obra + monto de refacciones + recargo.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
double calcularCostoManoObra(double horas);
double calcularRecargoRefacciones(double monto_refacciones);
double calcularSubtotal(double costo_mano_obra, double monto_refacciones, double recargo);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para la tarifa por hora de mano de obra, el límite
  de refacciones sin recargo, el porcentaje de recargo y la tasa de IVA —
  nada de valores hardcode dentro de las funciones.
- Validar que las horas y el monto de refacciones sean ≥ 0 (repetir captura
  si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: costo de mano de obra, recargo (o "no aplica" si fue 0),
  IVA y total a pagar.

### Casos de prueba

**Caso 1 — refacciones dentro del límite**
- Entrada: horas = 3, monto de refacciones = 800.00
- Salida esperada: costo de mano de obra = 750.00, recargo = 0.00, IVA =
  248.00, total a pagar = 1798.00

**Caso 2 — refacciones que superan el límite**
- Entrada: horas = 3, monto de refacciones = 1500.00
- Salida esperada: costo de mano de obra = 750.00, recargo = 75.00, IVA =
  372.00, total a pagar = 2697.00
