# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 10 — Ordaz Segura Melissa Alejandra

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Control de calidad del agua

Una planta potabilizadora revisa el pH de varias muestras de agua tomadas
durante el día. Escribe un programa que:

1. Pregunte cuántas muestras se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada muestra, pida su nivel de pH (número decimal).
3. Clasifique la muestra:
   - Si el pH está entre **6.5 y 8.5** (inclusive), la muestra está **dentro
     de rango normal**.
   - En cualquier otro caso, está **fuera de rango**.
4. Lleva un contador de muestras dentro de rango normal y otro de muestras
   fuera de rango.
5. Al final, muestra un reporte con el total de muestras revisadas, cuántas
   quedaron dentro de rango y cuántas fuera.

## Programa 2 — Panadería

Una panadería vende 3 tipos de pieza: **1) Bolillo**, **2) Concha**,
**3) Dona**. Cada pieza tiene un precio unitario fijo. Escribe un programa
que:

1. Defina en el código, como **constantes**, el precio unitario de cada
   pieza:
   - Bolillo: $3.50
   - Concha: $12.00
   - Dona: $15.00
2. Muestre un menú con las 3 piezas más una cuarta opción para **cerrar la
   caja**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas piezas** de ese tipo se están
   comprando (número entero positivo; si es inválido, debe volver a pedirse)
   y usa el precio constante correspondiente para calcular el monto de esa
   venta, acumulándolo en el total de su tipo, además de contar cuántas
   piezas de ese tipo se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que
   el usuario elija "cerrar la caja".
6. Al finalizar, muestra un reporte con: piezas vendidas por tipo, piezas
   totales vendidas, monto recaudado por tipo (calculado a partir del precio
   constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de piezas** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
