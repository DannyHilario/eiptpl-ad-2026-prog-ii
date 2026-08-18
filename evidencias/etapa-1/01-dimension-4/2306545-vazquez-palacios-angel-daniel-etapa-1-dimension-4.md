# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Vazquez Palacios Angel Daniel
**Matrícula:** 2306545

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Vibración en maquinaria industrial

Una planta industrial mide la vibración de varias máquinas para detectar
posibles fallas mecánicas. Escribe un programa que:

1. Pregunte cuántas máquinas se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada máquina, pida el nivel de vibración registrado en mm/s (número
   decimal).
3. Clasifique la máquina:
   - Si la vibración es **mayor a 4.5 mm/s**, la máquina entra en **estado
     de alerta**.
   - En caso contrario, está en **estado normal**.
4. Lleva un contador de máquinas en estado normal y otro en estado de
   alerta.
5. Al final, muestra un reporte con el total de máquinas revisadas, cuántas
   estuvieron en estado normal y cuántas en alerta.

## Programa 2 — Museo

Un museo vende boletos de entrada según el tipo de visitante: **1) Niño**,
**2) Adulto**, **3) Adulto mayor**. Cada tipo tiene un precio de boleto
fijo. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio del boleto para cada
   tipo de visitante:
   - Niño: $30.00
   - Adulto: $60.00
   - Adulto mayor: $25.00
2. Muestre un menú con los 3 tipos de visitante más una cuarta opción para
   **cerrar la taquilla**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos boletos** de ese tipo se están
   comprando (número entero positivo; si es inválido, debe volver a
   pedirse) y usa el precio constante correspondiente para calcular el monto
   de esa venta, acumulándolo en el total de su tipo, además de contar
   cuántos boletos de ese tipo se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que
   el usuario elija "cerrar la taquilla".
6. Al finalizar, muestra un reporte con: boletos vendidos por tipo de
   visitante, boletos totales vendidos, monto recaudado por tipo (calculado
   a partir del precio constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de boletos** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
