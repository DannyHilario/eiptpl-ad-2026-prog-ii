# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Entregas de paquetería

Una empresa de paquetería promete entregar sus envíos en un máximo de 3 días.
Escribe un programa que:

1. Pregunte cuántos envíos se van a revisar (debe ser un número positivo; si
   el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada envío, pida cuántos días tardó en entregarse (número entero).
3. Clasifique el envío:
   - Si tardó **más de 3 días**, se considera **entrega retrasada**.
   - En caso contrario, se considera **entrega a tiempo**.
4. Lleva un contador de entregas a tiempo y otro de entregas retrasadas.
5. Al final, muestra un reporte con el total de envíos revisados, cuántos
   llegaron a tiempo y cuántos con retraso.

## Programa 2 — Envíos de paquetería

Una empresa de paquetería cobra un precio fijo por envío según su
categoría: **1) Documento**, **2) Paquete chico**, **3) Paquete grande**.
Escribe un programa que:

1. Defina en el código, como **constantes**, el precio de envío de cada
   categoría:
   - Documento: $65.00
   - Paquete chico: $120.00
   - Paquete grande: $210.00
2. Muestre un menú con las 3 categorías más una cuarta opción para **cerrar
   el mostrador**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos envíos** de esa categoría se
   están registrando (número entero positivo; si es inválido, debe volver a
   pedirse) y usa el precio constante correspondiente para calcular el monto
   de esos envíos, acumulándolo en el total de su categoría, además de
   contar cuántos envíos de esa categoría se han registrado.
5. El programa debe seguir mostrando el menú y registrando envíos hasta que
   el usuario elija "cerrar el mostrador".
6. Al finalizar, muestra un reporte con: envíos registrados por categoría,
   envíos totales, monto recaudado por categoría (calculado a partir del
   precio constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de envíos** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
