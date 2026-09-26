# Evidencia 1.1 — Programa 2 (personalizado)

**Alumno:** 05 — Hernandez Lopez Jose

## Programa 2 — Renta de auto semanal con kilometraje incluido

**Periodo: semanal.** Una agencia renta autos por semana. La renta incluye
un límite de kilómetros recorridos; si el cliente se pasa de ese límite, se
cobra un cargo extra por cada kilómetro excedente. Escribe un programa que
calcule el total a pagar de la renta semanal.

El programa debe leer:

- Tarifa diaria del auto (pesos por día).
- Kilómetros recorridos durante la semana.

**Importante:** el programa NO debe pedir los "kilómetros excedentes" como
un dato aparte — se deducen dentro del programa a partir de los kilómetros
recorridos.

### Reglas de negocio

- Días incluidos por semana de renta: 7
- Km incluidos por semana: 700
- Tarifa por km excedente: $3.00
- Tasa de IVA: 16%

### Cálculo

1. **Costo de renta** = días incluidos por semana × tarifa diaria (la
   semana completa siempre se cobra).
2. **Kilómetros excedentes** = si los km recorridos superan los km incluidos
   por semana, la diferencia; si no, 0.
3. **Recargo** = kilómetros excedentes × tarifa por km excedente.
4. **Subtotal** = costo de renta + recargo.
5. **IVA** = subtotal × tasa de IVA.
6. **Total a pagar** = subtotal + IVA.

### Prototipos sugeridos

```cpp
double calcularCostoRenta(double tarifa_diaria);
int calcularKmExcedente(int km_recorridos);
double calcularRecargo(int km_excedente);
double calcularIVA(double subtotal);
double calcularTotal(double subtotal, double iva);
```

### Requisitos técnicos

- Constantes con nombre para los km incluidos en la semana, la tarifa por km
  excedente y la tasa de IVA — nada de valores hardcode dentro de las
  funciones.
- Validar que la tarifa diaria y los km recorridos sean ≥ 0 (repetir captura
  si no cumple). No hay límite superior para los km recorridos.
- El usuario **solo** captura tarifa diaria y km recorridos — nunca los km
  excedentes directamente.
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()`
  interactúa con el usuario.
- Mostrar al final: costo de renta, km excedentes, recargo, IVA y total a
  pagar.

### Casos de prueba

**Caso 1 — sin exceder el kilometraje**
- Entrada: tarifa diaria = 600.00, km recorridos = 500
- Salida esperada: costo de renta = 4200.00, km excedentes = 0, recargo =
  0.00, IVA = 672.00, total a pagar = 4872.00

**Caso 2 — con kilometraje excedente**
- Entrada: tarifa diaria = 600.00, km recorridos = 900
- Salida esperada: costo de renta = 4200.00, km excedentes = 200, recargo =
  600.00, IVA = 768.00, total a pagar = 5568.00
