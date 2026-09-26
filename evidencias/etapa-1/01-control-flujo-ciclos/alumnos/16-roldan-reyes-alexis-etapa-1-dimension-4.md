# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 16 — Roldan Reyes Alexis

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Prueba de resistencia de material

Un laboratorio prueba la resistencia a la tensión de varias piezas
metálicas antes de aprobarlas para su uso. Escribe un programa que:

1. Pregunte cuántas piezas se van a probar (debe ser un número positivo; si
   el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada pieza, pida la resistencia registrada en la prueba, en
   kilogramos (número decimal).
3. Clasifique la pieza:
   - Si la resistencia es **menor a 500 kg**, la pieza es **rechazada**.
   - En caso contrario, la pieza es **aprobada**.
4. Lleva un contador de piezas aprobadas y otro de piezas rechazadas.
5. Al final, muestra un reporte con el total de piezas probadas, cuántas
   fueron aprobadas y cuántas rechazadas.

## Programa 2 — Renta de disfraces

Una tienda de disfraces cobra por día de renta según el tipo de disfraz:
**1) Sencillo**, **2) Elaborado**, **3) Premium**. Cada tipo tiene una
tarifa fija por día. Escribe un programa que:

1. Defina en el código, como **constantes**, la tarifa por día de cada tipo
   de disfraz:
   - Sencillo: $80.00
   - Elaborado: $150.00
   - Premium: $280.00
2. Muestre un menú con los 3 tipos de disfraz más una cuarta opción para
   **cerrar el mostrador**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos días** se va a rentar el
   disfraz (número entero positivo; si es inválido, debe volver a pedirse) y
   usa la tarifa constante correspondiente para calcular el monto de esa
   renta, acumulándolo en el total de su tipo, además de contar cuántas
   rentas de ese tipo se han hecho.
5. El programa debe seguir mostrando el menú y registrando rentas hasta que
   el usuario elija "cerrar el mostrador".
6. Al finalizar, muestra un reporte con: rentas hechas por tipo de disfraz,
   rentas totales, monto recaudado por tipo (calculado a partir de la
   tarifa constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Las tarifas del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de días** (debe ser un
  número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
