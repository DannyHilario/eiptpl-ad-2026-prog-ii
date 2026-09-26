# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Vazquez Palacios Angel Daniel
**Matrícula:** 2306545

## Programa 2 — Renta de equipo de cómputo con recargo por meses de atraso

**Periodo: mensual.** Una empresa renta equipo de cómputo por contratos de
un mes. Si el cliente conserva el equipo más tiempo del contratado, se cobra
un recargo proporcional a los meses de atraso. Escribe un programa que
calcule el total a pagar de la renta.

El programa debe leer:

- Total de meses que el cliente tuvo el equipo en su poder (puede ser más
  de 1 si lo devolvió tarde).

**Importante:** el programa NO debe pedir los "meses de atraso" como un dato
aparte — se deducen dentro del programa a partir del total de meses.

### Reglas de negocio

- Meses incluidos en el contrato: 1
- Renta mensual: $1,200.00
- Recargo por mes de atraso: 6% de la renta mensual
- Tasa de IVA: 16%

### Cálculo

1. **Meses de atraso** = si el total de meses supera los meses incluidos en
   el contrato, la diferencia; si no, 0.
2. **Recargo** = renta mensual × recargo por mes de atraso × meses de
   atraso.
3. **Subtotal** = renta mensual + recargo.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
int calcularMesesAtraso(int total_meses);
double calcularRecargo(int meses_atraso);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para la renta mensual y el porcentaje de recargo por
  mes de atraso, y la tasa de IVA — nada de valores hardcode dentro de las
  funciones.
- Validar que el total de meses sea ≥ 1 (repetir captura si no cumple). No
  hay límite superior: un valor mayor a 1 es válido y representa atraso.
- El usuario **solo** captura el total de meses — nunca los meses de atraso
  directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: meses de atraso, recargo, IVA y total a pagar.

### Casos de prueba

**Caso 1 — sin atraso**
- Entrada: total de meses = 1
- Salida esperada: meses de atraso = 0, recargo = 0.00, IVA = 192.00, total
  a pagar = 1392.00

**Caso 2 — con atraso**
- Entrada: total de meses = 3
- Salida esperada: meses de atraso = 2, recargo = 144.00, IVA = 215.04,
  total a pagar = 1559.04
