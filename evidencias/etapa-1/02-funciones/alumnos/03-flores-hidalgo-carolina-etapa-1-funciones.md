# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 03 — Flores Hidalgo Carolina

## Programa 2 — Plan de streaming con cargo por pantallas adicionales

**Periodo: mensual.** Una plataforma de streaming cobra un plan base mensual
que incluye un número fijo de pantallas simultáneas. Si el cliente contrata
más pantallas de las incluidas, se cobra un cargo extra por cada pantalla
adicional. Escribe un programa que calcule el total a pagar del mes.

El programa debe leer:

- Número total de pantallas contratadas este mes (entero ≥ 1).

**Importante:** el programa NO debe pedir "pantallas adicionales" como un
dato aparte — se deduce dentro del programa a partir del total de pantallas
contratadas.

### Reglas de negocio

- Pantallas incluidas en el plan base: 2
- Costo del plan base: $199.00
- Tarifa por pantalla adicional: $49.00
- Tasa de IVA: 16%

### Cálculo

1. **Pantallas adicionales** = si el total de pantallas contratadas supera
   las pantallas incluidas en el plan base, la diferencia; si no, 0.
2. **Cargo adicional** = pantallas adicionales × tarifa por pantalla
   adicional.
3. **Subtotal** = costo del plan base + cargo adicional.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
int calcularPantallasAdicionales(int pantallas_totales);
double calcularSubtotal(int pantallas_adicionales);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para las pantallas incluidas en el plan, el costo del
  plan base, la tarifa por pantalla adicional y la tasa de IVA — nada de
  valores hardcode dentro de las funciones.
- Validar que el número de pantallas contratadas sea ≥ 1 (repetir captura si
  no cumple).
- El usuario **solo** captura el total de pantallas — nunca las adicionales
  directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: pantallas adicionales, subtotal, IVA y total a pagar.

### Casos de prueba

**Caso 1 — sin pantallas adicionales**
- Entrada: pantallas totales = 2
- Salida esperada: pantallas adicionales = 0, subtotal = 199.00, IVA = 31.84,
  total a pagar = 230.84

**Caso 2 — con pantallas adicionales**
- Entrada: pantallas totales = 5
- Salida esperada: pantallas adicionales = 3, subtotal = 346.00, IVA = 55.36,
  total a pagar = 401.36
