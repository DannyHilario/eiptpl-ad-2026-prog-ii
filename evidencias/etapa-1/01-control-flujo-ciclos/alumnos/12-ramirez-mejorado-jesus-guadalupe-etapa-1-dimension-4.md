# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Monitoreo de CO2 en un aula

Una escuela mide el nivel de CO2 en varias aulas para saber cuáles necesitan
ventilarse. Escribe un programa que:

1. Pregunte cuántas aulas se van a revisar (debe ser un número positivo; si
   el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada aula, pida el nivel de CO2 medido en ppm (número decimal).
3. Clasifique el aula:
   - Si el nivel es **mayor a 1000 ppm**, el aula **excede el límite** y
     necesita ventilarse.
   - En caso contrario, está en **nivel normal**.
4. Lleva un contador de aulas en nivel normal y otro de aulas que exceden el
   límite.
5. Al final, muestra un reporte con el total de aulas revisadas, cuántas
   estuvieron en nivel normal y cuántas excedieron el límite.

## Programa 2 — Taller mecánico

Un taller mecánico ofrece cambio de aceite según el tipo de vehículo:
**1) Auto**, **2) Camioneta**, **3) Motocicleta**. Cada tipo tiene un precio
fijo por servicio. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio del servicio para
   cada tipo de vehículo:
   - Auto: $350.00
   - Camioneta: $480.00
   - Motocicleta: $220.00
2. Muestre un menú con los 3 tipos de vehículo más una cuarta opción para
   **cerrar el turno**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", usa el precio constante correspondiente al
   tipo de vehículo elegido para acumular el total de ese servicio, además de
   contar cuántos servicios de ese tipo se han hecho.
5. El programa debe seguir mostrando el menú y registrando servicios hasta
   que el usuario elija "cerrar el turno".
6. Al finalizar, muestra un reporte con: servicios hechos por tipo de
   vehículo, servicios totales, monto recaudado por tipo (calculado a partir
   del precio constante) y monto total del turno.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar la **opción del menú** (debe estar entre 1
  y 4); si el ejercicio pide además una cantidad numérica (piezas, litros,
  horas, etc.), esa cantidad también debe validarse. Ambos deben volver a
  pedirse si el valor es inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
