# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

## Programa 2 — Lavado de autos a domicilio con paquete semanal

**Periodo: semanal.** Un servicio de lavado de autos a domicilio cobra un
paquete semanal que incluye un número fijo de autos. Si el cliente lava más
autos de los incluidos, se cobra un cargo extra por cada auto adicional.
Escribe un programa que calcule el total a pagar de la semana.

El programa debe leer:

- Número de autos lavados en la semana.

**Importante:** el programa NO debe pedir los "autos excedentes" como un
dato aparte — se deducen dentro del programa a partir de los autos lavados.

### Reglas de negocio

- Autos incluidos en el paquete semanal: 10
- Costo del paquete semanal: $600.00
- Tarifa por auto excedente: $45.00
- Tasa de IVA: 16%

### Cálculo

1. **Autos excedentes** = si los autos lavados superan los autos incluidos
   en el paquete semanal, la diferencia; si no, 0.
2. **Cargo excedente** = autos excedentes × tarifa por auto excedente.
3. **Subtotal** = costo del paquete semanal + cargo excedente.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
int calcularAutosExcedentes(int autos_lavados);
double calcularSubtotal(int autos_excedentes);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para los autos incluidos en el paquete, el costo del
  paquete semanal, la tarifa por auto excedente y la tasa de IVA — nada de
  valores hardcode dentro de las funciones.
- Validar que los autos lavados sean ≥ 0 (repetir captura si no cumple).
- El usuario **solo** captura los autos lavados — nunca los excedentes
  directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: autos excedentes, subtotal, IVA y total a pagar.

### Casos de prueba

**Caso 1 — dentro del paquete**
- Entrada: autos lavados = 8
- Salida esperada: autos excedentes = 0, subtotal = 600.00, IVA = 96.00,
  total a pagar = 696.00

**Caso 2 — con autos excedentes**
- Entrada: autos lavados = 14
- Salida esperada: autos excedentes = 4, subtotal = 780.00, IVA = 124.80,
  total a pagar = 904.80
