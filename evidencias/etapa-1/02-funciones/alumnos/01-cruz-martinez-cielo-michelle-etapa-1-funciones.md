# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Cruz Martinez Cielo Michelle
**Matrícula:** 2307014

## Programa 2 — Renta de equipo con recargo por retraso

**Periodo: semanal.** Una empresa renta equipo de construcción por periodos
semanales: la renta se contrata siempre por una semana completa (7 días), sin
importar cuántos días lo use el cliente. Si el cliente devuelve el equipo
después de esa semana, se le cobra un recargo proporcional a los días de
retraso. Escribe un programa que calcule el costo total de una renta semanal.

El programa debe leer:

- Días totales que el cliente tuvo el equipo en su poder (puede ser más de 7
  si lo devolvió tarde).
- Tarifa diaria del equipo (pesos por día).

**Importante:** el programa NO debe pedirle al usuario los días de retraso
por separado — eso abriría la puerta a que capture un valor que no cuadra con
los días totales (por ejemplo, decir que usó el equipo 3 días pero que se
retrasó 5). Los días de retraso se **deducen** dentro del programa a partir de
los días totales: si los días totales exceden 7, el retraso es la diferencia;
si no exceden 7, el retraso es 0.

### Reglas de negocio

- Días incluidos por semana de renta: 7
- Recargo por día de retraso: 3% del costo de renta
- Tasa de IVA: 16%

### Cálculo

1. **Costo de renta** = días incluidos por semana × tarifa diaria (la semana
   completa siempre se cobra, se use o no por completo).
2. **Días de retraso** = si los días totales superan los días incluidos por
   semana, la diferencia; si no, 0.
3. **Recargo por retraso** = costo de renta × recargo por día de retraso ×
   días de retraso. Es decir, cada día de retraso encarece el recargo total
   sobre el costo de renta (no es una tabla de rangos, es proporcional a los
   días de retraso).
4. **Base gravable** = costo de renta + recargo.
5. **IVA** = base gravable × tasa de IVA.
6. **Total a pagar** = base gravable + IVA.

### Prototipos sugeridos

```cpp
double calcularCostoRenta(double tarifa_diaria);
int calcularDiasRetraso(int dias_totales);
double calcularRecargo(int dias_retraso, double costo_renta);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);
```

Nota que `calcularRecargo` necesita **tanto** los días de retraso (para saber
cuánto multiplicar) **como** el costo de renta (para saber sobre qué monto
aplicar el porcentaje) — son dos parámetros, no uno. Y que `calcularDiasRetraso`
es la única función responsable de decidir si hubo retraso y de cuánto —
ninguna otra parte del programa debe repetir esa lógica.

### Requisitos técnicos

- Constante con nombre para el porcentaje de recargo por día de retraso y
  para la tasa de IVA — nada de valores hardcode dentro de las funciones.
- Validar que los días totales y la tarifa diaria sean > 0 (repetir captura
  si no cumple). No hay límite superior para los días totales: un valor mayor
  a 7 es válido y representa un retraso.
- El usuario **solo** captura días totales y tarifa diaria — nunca los días
  de retraso directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: costo de renta, días de retraso, recargo aplicado, IVA y
  total a pagar.

### Casos de prueba

Usa estos valores para verificar tu programa (no muestran cómo resolverlo,
solo el resultado esperado):

**Caso 1 — sin retraso**
- Entrada: días totales = 5, tarifa diaria = 500.00
- Salida esperada: costo de renta = 3500.00, días de retraso = 0, recargo =
  0.00, IVA = 560.00, total a pagar = 4060.00

**Caso 2 — con retraso**
- Entrada: días totales = 10, tarifa diaria = 350.00
- Salida esperada: costo de renta = 2450.00, días de retraso = 3, recargo =
  220.50, IVA = 427.28, total a pagar = 3097.78
