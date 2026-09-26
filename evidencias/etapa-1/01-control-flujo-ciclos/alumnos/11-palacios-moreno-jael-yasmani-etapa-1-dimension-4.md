# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 11 — Palacios Moreno Jael Yasmani

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Soporte técnico

Un centro de soporte técnico revisa el tiempo que tardó en atender varios
tickets abiertos por los usuarios. Escribe un programa que:

1. Pregunte cuántos tickets se van a revisar (debe ser un número positivo; si
   el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada ticket, pida las horas que tardó en resolverse (número
   decimal).
3. Clasifique el ticket:
   - Si tardó **más de 24 horas**, quedó **fuera de SLA**.
   - En caso contrario, quedó **dentro de SLA**.
4. Lleva un contador de tickets dentro de SLA y otro de tickets fuera de
   SLA.
5. Al final, muestra un reporte con el total de tickets revisados, cuántos
   quedaron dentro de SLA y cuántos fuera.

## Programa 2 — Lavandería

Una lavandería cobra por kilogramo según el tipo de prenda: **1) Ropa
normal**, **2) Ropa delicada**, **3) Edredón**. Cada tipo tiene un precio
fijo por kilogramo. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio por kilogramo de cada
   tipo de prenda:
   - Ropa normal: $18.00
   - Ropa delicada: $28.00
   - Edredón: $35.00
2. Muestre un menú con los 3 tipos de prenda más una cuarta opción para
   **cerrar el mostrador**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántos kilogramos** se van a lavar
   (número decimal positivo; si es inválido, debe volver a pedirse) y usa el
   precio constante correspondiente para calcular el monto de ese servicio,
   acumulándolo en el total de su tipo, además de contar cuántos servicios de
   ese tipo se han hecho.
5. El programa debe seguir mostrando el menú y registrando servicios hasta
   que el usuario elija "cerrar el mostrador".
6. Al finalizar, muestra un reporte con: servicios hechos por tipo de
   prenda, servicios totales, monto recaudado por tipo (calculado a partir
   del precio constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de kilogramos** (debe
  ser un número positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
