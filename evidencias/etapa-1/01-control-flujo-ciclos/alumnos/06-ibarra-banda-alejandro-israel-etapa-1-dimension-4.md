# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 06 — Ibarra Banda Alejandro Israel

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Control de inventario

Un almacén revisa las existencias de varios productos para saber cuáles
necesitan reabastecerse. Escribe un programa que:

1. Pregunte cuántos productos se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada producto, pida la cantidad de piezas en existencia (número
   entero).
3. Clasifique el producto:
   - Si la existencia es **menor o igual a 10 piezas**, el producto está en
     **stock bajo**.
   - En caso contrario, tiene **stock normal**.
4. Lleva un contador de productos con stock normal y otro de productos con
   stock bajo.
5. Al final, muestra un reporte con el total de productos revisados, cuántos
   tuvieron stock normal y cuántos stock bajo.

## Programa 2 — Centro de fotocopiado

Un centro de fotocopiado cobra por página según el tipo de copia:
**1) Blanco y negro**, **2) Color**, **3) Tamaño oficio**. Cada tipo tiene un
precio fijo por página. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio por página de cada
   tipo de copia:
   - Blanco y negro: $1.00
   - Color: $3.50
   - Tamaño oficio: $1.50
2. Muestre un menú con los 3 tipos de copia más una cuarta opción para
   **cerrar la caja**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas páginas** se van a copiar
   (número entero positivo; si es inválido, debe volver a pedirse) y usa el
   precio constante correspondiente para calcular el monto de ese trabajo,
   acumulándolo en el total de su tipo, además de contar cuántas páginas de
   ese tipo se han copiado.
5. El programa debe seguir mostrando el menú y registrando trabajos hasta que
   el usuario elija "cerrar la caja".
6. Al finalizar, muestra un reporte con: páginas copiadas por tipo, páginas
   totales copiadas, monto recaudado por tipo (calculado a partir del precio
   constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de páginas** (debe ser
  un número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
