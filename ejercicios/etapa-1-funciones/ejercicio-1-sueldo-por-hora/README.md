# Ejercicio 1 — Sueldo por hora con impuesto

*Etapa I — Funciones · Temas: 1.1–1.3 · Solución: [`etapa-1-ejercicio-1.cpp`](etapa-1-ejercicio-1.cpp)*

## Historia de usuario

**Como** encargado de nómina, **quiero** capturar la tarifa por hora y las horas
trabajadas de cada empleado, y ver su sueldo bruto, el impuesto retenido y su
sueldo neto, **para** calcular la nómina de todo el personal de una sola vez.

## Contexto

Cada empleado cobra por hora trabajada. A todos se les retiene el mismo
impuesto, un porcentaje fijo sobre el sueldo bruto. Por política de la empresa,
nadie puede registrar más de un máximo de horas por periodo.

**Reglas de negocio**

| Concepto | Valor |
|---|---|
| Tasa de impuesto | 16% del sueldo bruto |
| Máximo de horas trabajadas | 80 |

**Cálculo**

1. Sueldo bruto = horas trabajadas × tarifa por hora.
2. Impuesto = sueldo bruto × tasa de impuesto.
3. Sueldo neto = sueldo bruto − impuesto.

## Criterios de aceptación

- [ ] La tasa de impuesto y el máximo de horas son constantes con nombre
      (`TASA_IMPUESTO`, `HORAS_MAXIMAS_PERMITIDAS`), no números escritos dentro
      de las funciones.
- [ ] Usa estas funciones, sin `cin` ni `cout` dentro de ellas:
      - `double calcularSueldoBruto(double horas_trabajadas, double tarifa_x_hora)`
      - `double calcularImpuesto(double sueldo_bruto)`
      - `double calcularSueldoNeto(double sueldo_bruto, double impuesto)`
- [ ] Pide la cantidad de empleados; si es menor a 1, muestra un error y la
      vuelve a pedir.
- [ ] Por cada empleado pide la tarifa por hora; si es negativa, muestra un
      error y la vuelve a pedir.
- [ ] Por cada empleado pide las horas trabajadas; si son negativas o mayores al
      máximo, muestra un error que diga cuál es el máximo (tomado de la
      constante, no escrito a mano) y las vuelve a pedir.
- [ ] Por cada empleado imprime sueldo bruto, impuesto retenido y sueldo neto.

## Ejemplo de ejecución

```
Introduce la cantidad de empleados:
2

Empleado 1
Tarifa por hora:
100
Horas trabajadas:
40

Sueldo bruto: 4000
Impuesto retenido: 640
Sueldo neto: 3360

Empleado 2
Tarifa por hora:
50
Horas trabajadas:
45

Sueldo bruto: 2250
Impuesto retenido: 360
Sueldo neto: 1890
```

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Cálculo normal | tarifa = 100, horas = 40 | bruto 4000, impuesto 640, neto 3360 |
| 2 | Otro empleado | tarifa = 50, horas = 45 | bruto 2250, impuesto 360, neto 1890 |
| 3 | Justo en el máximo | tarifa = 10, horas = 80 | bruto 800, impuesto 128, neto 672 |
| 4 | Horas arriba del máximo | horas = 90 | `ERROR! Las horas trabajadas no son válidas. El máximo es 80 horas.`; vuelve a pedir las horas |
| 5 | Tarifa negativa | tarifa = -5 | `ERROR! La tarifa no puede ser negativa`; vuelve a pedirla |
| 6 | Cantidad de empleados negativa | cantidad = -1 | `ERROR! No hay trabajadores disponibles`; vuelve a pedirla |
| 7 | Cero empleados | cantidad = 0 | Mismo error; vuelve a pedirla |

## Historial de cambios

Cómo fue cambiando la solución de este ejercicio a lo largo del curso.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 20 ago 2026 | Primera versión: exactamente 3 empleados, con variables separadas para cada uno (`horas1`, `tarifa1`, `horas2`...), y una sola función `procesarSalarioEmpleado` que calculaba **e imprimía** todo. | Primer programa con una función definida por el usuario (tema 1.3): prototipo, definición y llamada. |
| 24 ago 2026 | Cambio grande: la función única se dividió en tres funciones que solo calculan y regresan un valor (`calcularSueldoBruto`, `calcularImpuesto`, `calcularSueldoNeto`). Ahora `main` se encarga de toda la captura y la impresión. Los 3 empleados fijos se reemplazaron por un `for` para N empleados, y se agregaron validaciones y la constante `HORAS_MAXIMAS_PERMITIDAS`. | Una función que imprime solo sirve para ese programa; una que regresa un valor se puede reutilizar. Con un ciclo, el programa funciona para cualquier número de empleados sin repetir código. |
| 4 sep 2026 | `TASA_IMPUESTO` cambió de `float` a `double`. | `double` tiene más precisión para montos de dinero. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
| 22 sep 2026 | El mensaje de error de horas ahora imprime la constante `HORAS_MAXIMAS_PERMITIDAS` en lugar del número 60 escrito a mano (que además estaba mal: la constante vale 80). La validación de la cantidad de empleados ahora también rechaza 0. | Si el mensaje repite un número a mano, se desfasa en cuanto cambia la constante; usando la constante, el mensaje siempre dice la verdad. Con 0 empleados el programa terminaba sin hacer nada. |
