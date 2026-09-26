# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 02 — Espinosa Saucedo Angel Xavier

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Control de calidad en línea de producción

Una fábrica revisa el peso de piezas metálicas que salen de una línea de
producción. Escribe un programa que:

1. Pregunte cuántas piezas se van a inspeccionar en el lote (debe ser un
   número positivo; si el usuario introduce un valor inválido, debe volver a
   pedirlo).
2. Para cada pieza, pida su peso en gramos (número decimal).
3. Clasifique la pieza:
   - Si el peso está entre **495 y 505 gramos** (inclusive), la pieza está
     **dentro de tolerancia**.
   - En cualquier otro caso, está **fuera de tolerancia**.
4. Lleva un contador de piezas dentro de tolerancia y otro de piezas fuera de
   tolerancia.
5. Al final, muestra un reporte con el total de piezas inspeccionadas, cuántas
   quedaron dentro de tolerancia y cuántas fuera.

## Programa 2 — Máquina expendedora de bebidas

Una máquina expendedora vende 3 tipos de bebida: **1) Agua**,
**2) Refresco**, **3) Jugo**. Cada tipo de bebida tiene un precio unitario
fijo. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio unitario de cada
   bebida:
   - Agua: $12.00
   - Refresco: $18.00
   - Jugo: $22.00
2. Muestre un menú con las 3 opciones de bebida más una cuarta opción para
   **cerrar la máquina** (fin del día).
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas piezas** de esa bebida se
   están comprando (debe ser un número entero positivo; si es inválido, debe
   volver a pedirse) y usa el precio constante correspondiente para calcular
   el monto de esa venta, acumulándolo en el total de su tipo, además de
   contar cuántas piezas de ese tipo se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que el
   usuario elija "cerrar la máquina".
6. Al finalizar, muestra un reporte con: piezas vendidas por tipo de bebida,
   piezas totales vendidas, efectivo recaudado por tipo (calculado a partir
   del precio constante) y efectivo total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de piezas** (debe ser un
  número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
