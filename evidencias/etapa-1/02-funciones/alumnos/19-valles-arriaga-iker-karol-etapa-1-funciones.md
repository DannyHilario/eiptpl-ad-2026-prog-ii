# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Valles Arriaga Iker Karol
**Matrícula:** 2306396

## Programa 2 — Nómina quincenal con descuento por faltas

**Periodo: quincenal.** Una empresa paga a sus empleados por quincena (15
días). Si el número de faltas supera un límite permitido, se le aplica un
descuento adicional sobre su sueldo, además de no pagarle los días que
faltó. Escribe un programa que calcule el sueldo neto quincenal de un
empleado.

El programa debe leer:

- Sueldo diario del empleado.
- Número de faltas en la quincena (0 a 15).

**Importante:** el programa NO debe pedir los "días trabajados" como un dato
aparte — se deducen dentro del programa a partir del número de faltas (la
quincena siempre tiene 15 días).

### Reglas de negocio

- Días de la quincena: 15
- Límite de faltas permitidas: 2
- Descuento adicional por exceder el límite: 10% del sueldo bruto
- Tasa de ISR: 10%

### Cálculo

1. **Días trabajados** = días de la quincena − faltas.
2. **Sueldo bruto** = días trabajados × sueldo diario.
3. **Descuento adicional**: si las faltas superan el límite de faltas
   permitidas, descuento = sueldo bruto × porcentaje de descuento adicional;
   si no, descuento = 0.
4. **Ingreso total** = sueldo bruto − descuento adicional.
5. **ISR** = ingreso total × tasa de ISR.
6. **Sueldo neto** = ingreso total − ISR.

### Prototipos sugeridos

```cpp
int calcularDiasTrabajados(int faltas);
double calcularSueldoBruto(int dias_trabajados, double sueldo_diario);
double calcularDescuentoAdicional(int faltas, double sueldo_bruto);
double calcularISR(double ingreso_total);
double calcularSueldoNeto(double ingreso_total, double isr);
```

Nota que `calcularDescuentoAdicional` necesita **tanto** las faltas (para
saber si superó el límite) **como** el sueldo bruto (para saber sobre qué
monto aplicar el descuento) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para los días de la quincena, el límite de faltas
  permitidas y el porcentaje de descuento adicional, y la tasa de ISR — nada
  de valores hardcode dentro de las funciones.
- Validar que el sueldo diario sea > 0 y que las faltas estén entre 0 y 15
  (repetir captura si no cumple).
- El usuario **solo** captura sueldo diario y número de faltas — nunca los
  días trabajados directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: días trabajados, sueldo bruto, descuento adicional (o
  "no aplica" si fue 0), ISR y sueldo neto.

### Casos de prueba

**Caso 1 — dentro del límite de faltas**
- Entrada: sueldo diario = 380.00, faltas = 1
- Salida esperada: días trabajados = 14, sueldo bruto = 5320.00, descuento
  adicional = 0.00, ISR = 532.00, sueldo neto = 4788.00

**Caso 2 — excede el límite de faltas**
- Entrada: sueldo diario = 380.00, faltas = 4
- Salida esperada: días trabajados = 11, sueldo bruto = 4180.00, descuento
  adicional = 418.00, ISR = 376.20, sueldo neto = 3385.80
