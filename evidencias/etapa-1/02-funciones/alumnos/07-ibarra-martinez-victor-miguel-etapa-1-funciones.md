# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 07 — Ibarra Martinez Victor Miguel

## Programa 2 — Servicio de mensajería con kilos incluidos

**Periodo: mensual.** Una empresa de mensajería cobra un plan mensual que
incluye un límite de kilos enviados. Si el cliente envía más kilos de los
incluidos, se cobra un cargo extra por cada kilo excedente. Escribe un
programa que calcule el total a pagar del mes.

El programa debe leer:

- Kilos enviados en el mes.

**Importante:** el programa NO debe pedir los "kilos excedentes" como un
dato aparte — se deducen dentro del programa a partir de los kilos enviados.

### Reglas de negocio

- Kilos incluidos en el plan: 100
- Costo del plan base: $800.00
- Tarifa por kilo excedente: $12.00
- Tasa de IVA: 16%

### Cálculo

1. **Kilos excedentes** = si los kilos enviados superan los kilos incluidos
   en el plan, la diferencia; si no, 0.
2. **Cargo excedente** = kilos excedentes × tarifa por kilo excedente.
3. **Subtotal** = costo del plan base + cargo excedente.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
int calcularKilosExcedente(int kilos_enviados);
double calcularSubtotal(int kilos_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para los kilos incluidos en el plan, el costo del
  plan base, la tarifa por kilo excedente y la tasa de IVA — nada de valores
  hardcode dentro de las funciones.
- Validar que los kilos enviados sean ≥ 0 (repetir captura si no cumple).
- El usuario **solo** captura los kilos enviados — nunca los excedentes
  directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: kilos excedentes, subtotal, IVA y total a pagar.

### Casos de prueba

**Caso 1 — dentro del límite**
- Entrada: kilos enviados = 80
- Salida esperada: kilos excedentes = 0, subtotal = 800.00, IVA = 128.00,
  total a pagar = 928.00

**Caso 2 — con excedente**
- Entrada: kilos enviados = 150
- Salida esperada: kilos excedentes = 50, subtotal = 1400.00, IVA = 224.00,
  total a pagar = 1624.00
