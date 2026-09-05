# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Hernández Hernández Luis Ernesto
**Matrícula:** 2306996

## Programa 2 — Recibo de agua doméstica por rangos de consumo

**Periodo: mensual.** El organismo de agua cobra el recibo mensual según el
consumo en metros cúbicos (m3), con una tabla de tres rangos (cuota fija +
tarifa sobre el excedente del rango). Escribe un programa que calcule el
total a pagar del recibo.

El programa debe leer:

- Consumo del mes en m3.

### Reglas de negocio

| Consumo (m3) | Cargo |
|---|---|
| 0 – 10 | $90.00 fijo |
| 10.01 – 30 | $90.00 + (consumo − 10) × $9.00 |
| 30.01 en adelante | $270.00 + (consumo − 30) × $14.00 |

- Tasa de IVA: 16%

### Cálculo

1. **Cargo por consumo** = el que corresponda según la tabla de rangos de
   consumo en m3.
2. **IVA** = cargo por consumo × tasa de IVA.
3. **Total a pagar** = cargo por consumo + IVA.

### Prototipos sugeridos

```cpp
double calcularCargoConsumo(double consumo_m3);
double calcularIVA(double cargo_consumo);
double calcularTotal(double cargo_consumo, double iva);
```

### Requisitos técnicos

- Constantes con nombre para los límites de rango, las cuotas fijas y las
  tarifas por m3 excedente de cada rango, y la tasa de IVA — nada de valores
  hardcode dentro de las funciones.
- Validar que el consumo sea ≥ 0 (repetir captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: cargo por consumo, IVA y total a pagar.

### Casos de prueba

**Caso 1 — rango 1**
- Entrada: consumo = 8 m3
- Salida esperada: cargo por consumo = 90.00, IVA = 14.40, total a pagar = 104.40

**Caso 2 — rango 3**
- Entrada: consumo = 45 m3
- Salida esperada: cargo por consumo = 480.00, IVA = 76.80, total a pagar = 556.80
