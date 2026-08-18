# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Rocha Ramirez Tomas De Jesus
**Matrícula:** 2306976

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Nivel de tanques de gas

Una empresa de gas LP revisa el nivel de llenado de varios tanques
estacionarios de sus clientes. Escribe un programa que:

1. Pregunte cuántos tanques se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada tanque, pida su nivel de llenado en porcentaje (número
   decimal).
3. Clasifique el tanque:
   - Si el nivel es **menor a 15%**, el tanque tiene **nivel bajo** y debe
     programarse para reabastecerse.
   - En caso contrario, tiene **nivel normal**.
4. Lleva un contador de tanques con nivel normal y otro con nivel bajo.
5. Al final, muestra un reporte con el total de tanques revisados, cuántos
   tuvieron nivel normal y cuántos nivel bajo.

## Programa 2 — Autolavado

Un autolavado cobra un precio fijo por servicio según el tipo de vehículo:
**1) Auto**, **2) Camioneta**, **3) Camión**. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio del lavado para cada
   tipo de vehículo:
   - Auto: $80.00
   - Camioneta: $110.00
   - Camión: $180.00
2. Muestre un menú con los 3 tipos de vehículo más una cuarta opción para
   **cerrar el turno**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", usa el precio constante correspondiente al
   tipo de vehículo elegido para acumular el total de ese servicio, además de
   contar cuántos lavados de ese tipo se han hecho.
5. El programa debe seguir mostrando el menú y registrando lavados hasta que
   el usuario elija "cerrar el turno".
6. Al finalizar, muestra un reporte con: lavados hechos por tipo de
   vehículo, lavados totales, monto recaudado por tipo (calculado a partir
   del precio constante) y monto total del turno.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar la **opción del menú** (debe estar entre 1
  y 4); si el ejercicio pide además una cantidad numérica (piezas, litros,
  horas, etc.), esa cantidad también debe validarse. Ambos deben volver a
  pedirse si el valor es inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
