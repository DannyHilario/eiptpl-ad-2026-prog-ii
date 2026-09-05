# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Flores Hidalgo Carolina
**Matrícula:** 2254340

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Filtro de acceso a un evento

En la entrada de un concierto se toma la temperatura corporal de cada
asistente antes de dejarlo pasar. Escribe un programa que:

1. Pregunte cuántos asistentes se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada asistente, pida su temperatura corporal en grados Celsius
   (número decimal).
3. Clasifique al asistente:
   - Si la temperatura es **mayor a 37.5 °C**, se considera **febril** y no
     puede pasar.
   - En caso contrario, se considera **normal** y puede pasar.
4. Lleva un contador de asistentes con temperatura normal y otro de
   asistentes febriles.
5. Al final, muestra un reporte con el total de personas revisadas, cuántas
   pasaron con temperatura normal y cuántas fueron detectadas como febriles.

## Programa 2 — Despacho en gasolinera

Una gasolinera despacha 3 tipos de combustible: **1) Magna**,
**2) Premium**, **3) Diésel**. Cada combustible tiene un precio fijo por
litro. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio por litro de cada
   combustible:
   - Magna: $23.50
   - Premium: $25.80
   - Diésel: $26.20
2. Muestre un menú con las 3 opciones de combustible más una cuarta opción
   para **cerrar el turno**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos litros** se van a despachar
   (número decimal positivo; si es inválido, debe volver a pedirse) y usa el
   precio constante correspondiente para calcular el monto de ese despacho,
   acumulándolo en el total de su tipo de combustible, además de contar
   cuántos despachos de ese tipo se han hecho.
5. El programa debe seguir mostrando el menú y registrando despachos hasta que
   el usuario elija "cerrar el turno".
6. Al finalizar, muestra un reporte con: litros despachados por tipo de
   combustible, cantidad total de despachos, efectivo recaudado por tipo
   (calculado a partir del precio constante) y efectivo total del turno.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de litros** (debe ser un
  número positivo). Ambos deben volver a pedirse si el valor es inválido, sin
  terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
