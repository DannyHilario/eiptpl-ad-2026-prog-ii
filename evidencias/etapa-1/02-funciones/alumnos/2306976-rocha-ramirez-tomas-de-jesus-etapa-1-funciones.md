# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Rocha Ramirez Tomas De Jesus
**Matrícula:** 2306976

## Programa 2 — Renta de bodega con recargo por peso excedente

**Periodo: mensual.** Una empresa renta espacio de bodega por metro
cuadrado. La renta incluye un límite de peso almacenado; si el cliente
almacena más peso del incluido, se cobra un recargo extra por cada kilo
excedente. Escribe un programa que calcule el total a pagar del mes.

El programa debe leer:

- Metros cuadrados rentados.
- Peso almacenado en kilos.

**Importante:** el programa NO debe pedir el "peso excedente" como un dato
aparte — se deduce dentro del programa a partir del peso almacenado.

### Reglas de negocio

- Tarifa por m2: $45.00
- Peso incluido sin costo extra: 5,000 kg
- Tarifa por kg excedente: $0.80
- Tasa de IVA: 16%

### Cálculo

1. **Costo de renta** = metros cuadrados × tarifa por m2.
2. **Peso excedente** = si el peso almacenado supera el peso incluido sin
   costo extra, la diferencia; si no, 0.
3. **Recargo** = peso excedente × tarifa por kg excedente.
4. **Subtotal** = costo de renta + recargo.
5. **IVA** = subtotal × tasa de IVA.
6. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
double calcularCostoRenta(double metros_cuadrados);
double calcularPesoExcedente(double peso_almacenado);
double calcularRecargo(double peso_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para la tarifa por m2, el peso incluido, la tarifa
  por kilo excedente y la tasa de IVA — nada de valores hardcode dentro de
  las funciones.
- Validar que los metros cuadrados y el peso almacenado sean ≥ 0 (repetir
  captura si no cumple).
- El usuario **solo** captura metros cuadrados y peso almacenado — nunca el
  peso excedente directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: costo de renta, peso excedente, recargo, IVA y total a
  pagar.

### Casos de prueba

**Caso 1 — dentro del límite de peso**
- Entrada: metros cuadrados = 50, peso almacenado = 4000 kg
- Salida esperada: costo de renta = 2250.00, peso excedente = 0, recargo =
  0.00, IVA = 360.00, total a pagar = 2610.00

**Caso 2 — con peso excedente**
- Entrada: metros cuadrados = 50, peso almacenado = 6500 kg
- Salida esperada: costo de renta = 2250.00, peso excedente = 1500, recargo
  = 1200.00, IVA = 552.00, total a pagar = 4002.00
