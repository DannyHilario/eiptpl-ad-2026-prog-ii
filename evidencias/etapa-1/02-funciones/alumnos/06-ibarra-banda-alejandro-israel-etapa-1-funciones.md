# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 06 — Ibarra Banda Alejandro Israel

## Programa 2 — Nómina quincenal con bono por asistencia perfecta

**Periodo: quincenal.** Una empresa paga a sus empleados por quincena (15
días). Si el empleado no tuvo ninguna falta en la quincena, recibe un bono de
puntualidad; si tuvo al menos una falta, no recibe el bono. Escribe un
programa que calcule el sueldo neto quincenal de un empleado.

El programa debe leer:

- Sueldo diario del empleado.
- Número de faltas en la quincena (0 a 15).

**Importante:** el programa NO debe pedir los "días trabajados" como un dato
aparte — se deducen dentro del programa a partir del número de faltas
(la quincena siempre tiene 15 días).

### Reglas de negocio

- Días de la quincena: 15
- Bono de puntualidad (si 0 faltas): 5% del sueldo bruto
- Tasa de ISR: 10%

### Cálculo

1. **Días trabajados** = días de la quincena − faltas.
2. **Sueldo bruto** = días trabajados × sueldo diario.
3. **Bono de puntualidad**: si faltas = 0, bono = sueldo bruto × porcentaje
   de bono de puntualidad; si no, bono = 0.
4. **Ingreso total** = sueldo bruto + bono.
5. **ISR** = ingreso total × tasa de ISR.
6. **Sueldo neto** = ingreso total − ISR.

### Prototipos sugeridos

```cpp
int calcularDiasTrabajados(int faltas);
double calcularSueldoBruto(int dias_trabajados, double sueldo_diario);
double calcularBono(int faltas, double sueldo_bruto);
double calcularISR(double ingreso_total);
double calcularSueldoNeto(double ingreso_total, double isr);
```

### Requisitos técnicos

- Constantes con nombre para los días de la quincena, el porcentaje de bono
  de puntualidad y la tasa de ISR — nada de valores hardcode dentro de las
  funciones.
- Validar que el sueldo diario sea > 0 y que las faltas estén entre 0 y 15
  (repetir captura si no cumple).
- El usuario **solo** captura sueldo diario y número de faltas — nunca los
  días trabajados directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: días trabajados, sueldo bruto, bono, ISR y sueldo neto.

### Casos de prueba

**Caso 1 — asistencia perfecta**
- Entrada: sueldo diario = 400.00, faltas = 0
- Salida esperada: días trabajados = 15, sueldo bruto = 6000.00, bono =
  300.00, ISR = 630.00, sueldo neto = 5670.00

**Caso 2 — con faltas**
- Entrada: sueldo diario = 400.00, faltas = 2
- Salida esperada: días trabajados = 13, sueldo bruto = 5200.00, bono =
  0.00, ISR = 520.00, sueldo neto = 4680.00
