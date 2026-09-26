# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 04 — Hernández Hernández Luis Ernesto

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Radar de velocidad

Un radar de carretera registra la velocidad de los vehículos que pasan por un
tramo con límite de 80 km/h. Escribe un programa que:

1. Pregunte cuántos vehículos se van a registrar (debe ser un número
   positivo; si el usuario introduce un valor inválido, debe volver a
   pedirlo).
2. Para cada vehículo, pida su velocidad en km/h (número decimal).
3. Clasifique al vehículo:
   - Si la velocidad es **mayor a 80 km/h**, el vehículo va **en exceso de
     velocidad**.
   - En caso contrario, va **dentro del límite**.
4. Lleva un contador de vehículos dentro del límite y otro de vehículos en
   exceso de velocidad.
5. Al final, muestra un reporte con el total de vehículos registrados,
   cuántos iban dentro del límite y cuántos en exceso de velocidad.

## Programa 2 — Taquilla de estadio

La taquilla de un estadio vende 3 tipos de entrada: **1) General**,
**2) Preferente**, **3) Palco**. Cada tipo de entrada tiene un precio fijo.
Escribe un programa que:

1. Defina en el código, como **constantes**, el precio de cada tipo de
   entrada:
   - General: $150.00
   - Preferente: $350.00
   - Palco: $800.00
2. Muestre un menú con las 3 opciones de entrada más una cuarta opción para
   **cerrar la taquilla**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos boletos** de ese tipo se están
   comprando (número entero positivo; si es inválido, debe volver a pedirse)
   y usa el precio constante correspondiente para calcular el monto de esa
   venta, acumulándolo en el total de su tipo, además de contar cuántos
   boletos de ese tipo se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que el
   usuario elija "cerrar la taquilla".
6. Al finalizar, muestra un reporte con: boletos vendidos por tipo de
   entrada, cantidad total de boletos vendidos, efectivo recaudado por tipo
   (calculado a partir del precio constante) y efectivo total del evento.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de boletos** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
