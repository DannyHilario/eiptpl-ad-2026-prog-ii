# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 17 — Salinas Diaz Andrea Elizabeth

## Programa 2 — Renta de local comercial con recargo por consumo eléctrico

**Periodo: mensual.** Un centro comercial renta locales con una renta base
mensual que incluye un límite de consumo eléctrico. Si el local consume más
kWh de los incluidos, se cobra un recargo extra por cada kWh excedente.
Escribe un programa que calcule el total a pagar del mes.

El programa debe leer:

- Consumo eléctrico del mes en kWh.

**Importante:** el programa NO debe pedir el "consumo excedente" como un
dato aparte — se deduce dentro del programa a partir del consumo del mes.

### Reglas de negocio

- kWh incluidos en la renta: 500
- Renta base mensual: $8,000.00
- Tarifa por kWh excedente: $3.50
- Tasa de IVA: 16%

### Cálculo

1. **kWh excedentes** = si el consumo supera los kWh incluidos en la renta,
   la diferencia; si no, 0.
2. **Recargo** = kWh excedentes × tarifa por kWh excedente.
3. **Subtotal** = renta base mensual + recargo.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
double calcularKwhExcedente(double consumo_kwh);
double calcularSubtotal(double kwh_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para los kWh incluidos, la renta base, la tarifa por
  kWh excedente y la tasa de IVA — nada de valores hardcode dentro de las
  funciones.
- Validar que el consumo eléctrico sea ≥ 0 (repetir captura si no cumple).
- El usuario **solo** captura el consumo del mes — nunca el excedente
  directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: kWh excedentes, subtotal, IVA y total a pagar.

### Casos de prueba

**Caso 1 — dentro del límite**
- Entrada: consumo = 400 kWh
- Salida esperada: kWh excedentes = 0, subtotal = 8000.00, IVA = 1280.00,
  total a pagar = 9280.00

**Caso 2 — con consumo excedente**
- Entrada: consumo = 700 kWh
- Salida esperada: kWh excedentes = 200, subtotal = 8700.00, IVA = 1392.00,
  total a pagar = 10092.00
