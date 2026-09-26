# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 07 — Ibarra Martinez Victor Miguel

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Monitoreo de ruido industrial

Una fábrica mide el nivel de ruido en distintos puntos de la planta durante
un turno. Escribe un programa que:

1. Pregunte cuántos puntos de medición se van a revisar (debe ser un número
   positivo; si el usuario introduce un valor inválido, debe volver a
   pedirlo).
2. Para cada punto, pida el nivel de ruido en decibeles (número decimal).
3. Clasifique la medición:
   - Si el nivel es **mayor a 85 dB**, el punto **excede el límite
     permitido**.
   - En caso contrario, está **dentro del límite permitido**.
4. Lleva un contador de puntos dentro del límite y otro de puntos que lo
   exceden.
5. Al final, muestra un reporte con el total de puntos medidos, cuántos
   estuvieron dentro del límite y cuántos lo excedieron.

## Programa 2 — Renta de bicicletas

Un módulo de renta de bicicletas urbanas cobra por hora según el tipo de
bicicleta: **1) Urbana**, **2) Montaña**, **3) Eléctrica**. Cada tipo tiene
una tarifa fija por hora. Escribe un programa que:

1. Defina en el código, como **constantes**, la tarifa por hora de cada tipo
   de bicicleta:
   - Urbana: $20.00
   - Montaña: $30.00
   - Eléctrica: $45.00
2. Muestre un menú con los 3 tipos de bicicleta más una cuarta opción para
   **cerrar el módulo**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas horas** se va a rentar la
   bicicleta (número decimal positivo; si es inválido, debe volver a
   pedirse) y usa la tarifa constante correspondiente para calcular el monto
   de esa renta, acumulándolo en el total de su tipo, además de contar
   cuántas rentas de ese tipo se han hecho.
5. El programa debe seguir mostrando el menú y registrando rentas hasta que
   el usuario elija "cerrar el módulo".
6. Al finalizar, muestra un reporte con: rentas hechas por tipo de
   bicicleta, rentas totales, monto recaudado por tipo (calculado a partir
   de la tarifa constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Las tarifas del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de horas** (debe ser un
  número positivo). Ambos deben volver a pedirse si el valor es inválido, sin
  terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
