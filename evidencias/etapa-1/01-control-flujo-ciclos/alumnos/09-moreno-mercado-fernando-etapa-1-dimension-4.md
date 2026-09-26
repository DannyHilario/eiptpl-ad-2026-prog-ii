# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** 09 — Moreno Mercado Fernando

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Monitoreo de batería de dispositivos

Un centro de cómputo revisa el nivel de batería de sus laptops antes de
prestarlas. Escribe un programa que:

1. Pregunte cuántas laptops se van a revisar (debe ser un número positivo; si
   el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada laptop, pida el porcentaje de batería restante (número entero
   entre 0 y 100).
3. Clasifique la laptop:
   - Si la batería es **menor a 20%**, la laptop tiene **batería baja** y no
     se presta.
   - En caso contrario, tiene **batería suficiente**.
4. Lleva un contador de laptops con batería suficiente y otro con batería
   baja.
5. Al final, muestra un reporte con el total de laptops revisadas, cuántas
   tuvieron batería suficiente y cuántas batería baja.

## Programa 2 — Estacionamiento

Un estacionamiento cobra por hora según el tipo de vehículo: **1) Auto**,
**2) Camioneta**, **3) Tráiler**. Cada tipo tiene una tarifa fija por hora.
Escribe un programa que:

1. Defina en el código, como **constantes**, la tarifa por hora de cada tipo
   de vehículo:
   - Auto: $15.00
   - Camioneta: $22.00
   - Tráiler: $40.00
2. Muestre un menú con los 3 tipos de vehículo más una cuarta opción para
   **cerrar el estacionamiento**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas horas** estuvo estacionado el
   vehículo (número decimal positivo; si es inválido, debe volver a pedirse)
   y usa la tarifa constante correspondiente para calcular el monto de ese
   cobro, acumulándolo en el total de su tipo, además de contar cuántos
   vehículos de ese tipo han salido.
5. El programa debe seguir mostrando el menú y registrando salidas hasta que
   el usuario elija "cerrar el estacionamiento".
6. Al finalizar, muestra un reporte con: vehículos atendidos por tipo,
   vehículos totales atendidos, monto recaudado por tipo (calculado a partir
   de la tarifa constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Las tarifas del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de horas** (debe ser un
  número positivo). Ambos deben volver a pedirse si el valor es inválido, sin
  terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
