# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 08 — Martinez Rincon Vika Ludivina

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Encuesta de satisfacción

Un restaurante aplica una encuesta de satisfacción a sus clientes al final
del servicio. Escribe un programa que:

1. Pregunte cuántas encuestas se van a capturar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada encuesta, pida la calificación otorgada por el cliente en una
   escala de 1 a 10 (número entero).
3. Clasifique la encuesta:
   - Si la calificación es **mayor o igual a 8**, el cliente quedó
     **satisfecho**.
   - En caso contrario, quedó **insatisfecho**.
4. Lleva un contador de clientes satisfechos y otro de insatisfechos.
5. Al final, muestra un reporte con el total de encuestas capturadas, cuántos
   clientes quedaron satisfechos y cuántos insatisfechos.

## Programa 2 — Taquilla de cine

La taquilla de un cine vende 3 tipos de boleto: **1) General**, **2) VIP**,
**3) Sala 3D**. Cada tipo de boleto tiene un precio fijo. Escribe un
programa que:

1. Defina en el código, como **constantes**, el precio de cada tipo de
   boleto:
   - General: $65.00
   - VIP: $110.00
   - Sala 3D: $95.00
2. Muestre un menú con los 3 tipos de boleto más una cuarta opción para
   **cerrar la taquilla**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos boletos** de ese tipo se están
   comprando (número entero positivo; si es inválido, debe volver a pedirse)
   y usa el precio constante correspondiente para calcular el monto de esa
   venta, acumulándolo en el total de su tipo, además de contar cuántos
   boletos de ese tipo se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que
   el usuario elija "cerrar la taquilla".
6. Al finalizar, muestra un reporte con: boletos vendidos por tipo, boletos
   totales vendidos, monto recaudado por tipo (calculado a partir del precio
   constante) y monto total de la función.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de boletos** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
