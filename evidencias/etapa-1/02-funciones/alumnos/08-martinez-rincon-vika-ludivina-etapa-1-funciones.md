# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 08 — Martinez Rincon Vika Ludivina

## Programa 2 — Plan de telefonía celular con datos incluidos

**Periodo: mensual.** Una compañía telefónica cobra un plan mensual que
incluye un límite de gigabytes (GB) de datos. Si el cliente consume más GB de
los incluidos, se cobra un cargo extra por cada GB excedente. Escribe un
programa que calcule el total a pagar del mes.

El programa debe leer:

- GB de datos consumidos en el mes.

**Importante:** el programa NO debe pedir los "GB excedentes" como un dato
aparte — se deducen dentro del programa a partir de los GB consumidos.

### Reglas de negocio

- GB incluidos en el plan: 10
- Costo del plan base: $299.00
- Tarifa por GB excedente: $25.00
- Tasa de IVA: 16%

### Cálculo

1. **GB excedentes** = si los GB consumidos superan los GB incluidos en el
   plan, la diferencia; si no, 0.
2. **Cargo excedente** = GB excedentes × tarifa por GB excedente.
3. **Subtotal** = costo del plan base + cargo excedente.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
double calcularGbExcedente(double gb_consumidos);
double calcularSubtotal(double gb_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para los GB incluidos en el plan, el costo del plan
  base, la tarifa por GB excedente y la tasa de IVA — nada de valores
  hardcode dentro de las funciones.
- Validar que los GB consumidos sean ≥ 0 (repetir captura si no cumple).
- El usuario **solo** captura los GB consumidos — nunca los excedentes
  directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: GB excedentes, subtotal, IVA y total a pagar.

### Casos de prueba

**Caso 1 — dentro del límite**
- Entrada: GB consumidos = 8
- Salida esperada: GB excedentes = 0, subtotal = 299.00, IVA = 47.84, total
  a pagar = 346.84

**Caso 2 — con excedente**
- Entrada: GB consumidos = 14
- Salida esperada: GB excedentes = 4, subtotal = 399.00, IVA = 63.84, total
  a pagar = 462.84
