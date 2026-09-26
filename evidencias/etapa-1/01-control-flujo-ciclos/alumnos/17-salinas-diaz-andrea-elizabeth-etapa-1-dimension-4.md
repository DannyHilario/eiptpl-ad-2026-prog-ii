# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 17 — Salinas Diaz Andrea Elizabeth

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Sensor de ocupación de estacionamiento

Un centro comercial mide, en distintos momentos del día, el porcentaje de
ocupación de su estacionamiento. Escribe un programa que:

1. Pregunte cuántas mediciones se van a revisar (debe ser un número
   positivo; si el usuario introduce un valor inválido, debe volver a
   pedirlo).
2. Para cada medición, pida el porcentaje de ocupación registrado (número
   decimal entre 0 y 100).
3. Clasifique la medición:
   - Si la ocupación es **mayor o igual a 95%**, el estacionamiento se
     considera **lleno**.
   - En caso contrario, se considera **disponible**.
4. Lleva un contador de mediciones con estacionamiento disponible y otro con
   estacionamiento lleno.
5. Al final, muestra un reporte con el total de mediciones revisadas,
   cuántas mostraron estacionamiento disponible y cuántas lleno.

## Programa 2 — Terminal de autobuses foráneos

Una terminal vende boletos de autobús foráneo hacia 3 destinos:
**1) Destino A**, **2) Destino B**, **3) Destino C**. Cada destino tiene un
precio de boleto fijo. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio del boleto para cada
   destino:
   - Destino A: $180.00
   - Destino B: $320.00
   - Destino C: $450.00
2. Muestre un menú con los 3 destinos más una cuarta opción para **cerrar
   la taquilla**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos boletos** hacia ese destino se
   están comprando (número entero positivo; si es inválido, debe volver a
   pedirse) y usa el precio constante correspondiente para calcular el monto
   de esa venta, acumulándolo en el total de su destino, además de contar
   cuántos boletos hacia ese destino se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que
   el usuario elija "cerrar la taquilla".
6. Al finalizar, muestra un reporte con: boletos vendidos por destino,
   boletos totales vendidos, monto recaudado por destino (calculado a partir
   del precio constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de boletos** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
