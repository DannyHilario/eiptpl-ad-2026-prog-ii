# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** Ordaz Segura Melissa Alejandra
**Matrícula:** 2306833

## Programa 2 — Tienda departamental con descuento por compras acumuladas

**Periodo: quincenal.** Una tienda aplica un descuento por cliente frecuente
según el total de compras acumuladas en la quincena: 2% de descuento por
cada $1,000.00 de compras, pero nunca más del 20% en total (hay un tope
máximo). Escribe un programa que calcule el total a pagar.

El programa debe leer:

- Monto de compras acumuladas en la quincena (pesos).

### Reglas de negocio

- Descuento por cada $1,000.00 de compras: 2%
- Tope máximo de descuento: 20%
- Tasa de IVA: 16%

### Cálculo

1. **Porcentaje de descuento** = descuento por cada $1,000 × (monto
   acumulado entre $1,000.00, parte entera), sin exceder nunca el tope
   máximo de descuento.
2. **Descuento** = monto acumulado × porcentaje de descuento.
3. **Subtotal** = monto acumulado − descuento.
4. **IVA** = subtotal × tasa de IVA.
5. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
double calcularPorcentajeDescuento(double monto_acumulado);
double calcularSubtotal(double monto_acumulado, double porcentaje_descuento);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

Nota que `calcularSubtotal` necesita **tanto** el monto acumulado (para saber
sobre qué base aplicar el descuento) **como** el porcentaje de descuento ya
calculado — son dos parámetros, no uno. Para obtener "cada $1,000 completos"
dentro de `calcularPorcentajeDescuento`, convierte el monto entre 1000 a
entero (por ejemplo con `static_cast<int>`) antes de multiplicar por el 2%, y
usa una condición para no exceder el tope del 20%.

### Requisitos técnicos

- Constantes con nombre para el porcentaje de descuento por cada $1,000, el
  tope máximo de descuento y la tasa de IVA — nada de valores hardcode
  dentro de las funciones.
- Validar que el monto acumulado sea > 0 (repetir captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: porcentaje de descuento aplicado, descuento en pesos,
  IVA y total a pagar.

### Casos de prueba

**Caso 1 — descuento sin llegar al tope**
- Entrada: monto acumulado = 4000.00
- Salida esperada: porcentaje de descuento = 8%, descuento = 320.00, IVA =
  588.80, total a pagar = 4268.80

**Caso 2 — descuento topado al máximo**
- Entrada: monto acumulado = 15000.00
- Salida esperada: porcentaje de descuento = 20% (aunque 15 × 2% = 30%, se
  aplica el tope), descuento = 3000.00, IVA = 1920.00, total a pagar =
  13920.00
