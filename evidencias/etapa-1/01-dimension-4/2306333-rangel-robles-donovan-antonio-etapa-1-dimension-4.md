# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Rangel Robles Donovan Antonio
**Matrícula:** 2306333

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Tiempo de carga de páginas web

Un equipo de desarrollo revisa el tiempo de carga de varias páginas de un
sitio web. Escribe un programa que:

1. Pregunte cuántas páginas se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada página, pida su tiempo de carga en segundos (número decimal).
3. Clasifique la página:
   - Si el tiempo es **mayor a 3 segundos**, la página se considera
     **lenta**.
   - En caso contrario, se considera **rápida**.
4. Lleva un contador de páginas rápidas y otro de páginas lentas.
5. Al final, muestra un reporte con el total de páginas revisadas, cuántas
   fueron rápidas y cuántas lentas.

## Programa 2 — Cafetería

Una cafetería vende 3 tipos de bebida caliente: **1) Café americano**,
**2) Capuchino**, **3) Chocolate**. Cada bebida tiene un precio unitario
fijo. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio de cada bebida:
   - Café americano: $28.00
   - Capuchino: $38.00
   - Chocolate: $35.00
2. Muestre un menú con las 3 bebidas más una cuarta opción para **cerrar la
   caja**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas tazas** de esa bebida se están
   comprando (número entero positivo; si es inválido, debe volver a
   pedirse) y usa el precio constante correspondiente para calcular el monto
   de esa venta, acumulándolo en el total de su tipo, además de contar
   cuántas tazas de ese tipo se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que
   el usuario elija "cerrar la caja".
6. Al finalizar, muestra un reporte con: tazas vendidas por tipo de bebida,
   tazas totales vendidas, monto recaudado por tipo (calculado a partir del
   precio constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de tazas** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
