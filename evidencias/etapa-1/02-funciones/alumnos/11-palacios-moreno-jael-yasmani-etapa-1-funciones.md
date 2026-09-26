# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 11 — Palacios Moreno Jael Yasmani

## Programa 2 — Colegiatura con recargo por pago atrasado

**Periodo: mensual.** Una escuela cobra una colegiatura mensual fija. Si el
pago se hace después de la fecha límite, se cobra un recargo proporcional a
los días de atraso. Escribe un programa que calcule el total a pagar de la
colegiatura del mes.

El programa debe leer:

- Días de atraso en el pago (0 si se pagó a tiempo, dentro de la fecha
  límite).

*Nota: aquí no se maneja el día calendario real en que se pagó — este curso
no ha visto tipos de dato para fechas. Los días de atraso ya vienen contados
como un número entero simple, no hay que calcularlos a partir de una fecha.*

### Reglas de negocio

- Monto de la colegiatura: $2,500.00
- Recargo por día de atraso: 2% de la colegiatura
- Esta colegiatura no lleva IVA.

### Cálculo

1. **Recargo** = monto de la colegiatura × recargo por día de atraso × días
   de atraso.
2. **Total a pagar** = monto de la colegiatura + recargo.

### Prototipos sugeridos

```cpp
double calcularRecargo(int dias_atraso);
double calcularTotal(double recargo);
```

### Requisitos técnicos

- Constantes con nombre para el monto de la colegiatura y el porcentaje de
  recargo por día de atraso — nada de valores hardcode dentro de las
  funciones.
- Validar que los días de atraso sean ≥ 0 (repetir captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: recargo aplicado y total a pagar.

### Casos de prueba

**Caso 1 — pago a tiempo**
- Entrada: días de atraso = 0
- Salida esperada: recargo = 0.00, total a pagar = 2500.00

**Caso 2 — pago atrasado**
- Entrada: días de atraso = 5
- Salida esperada: recargo = 250.00, total a pagar = 2750.00
