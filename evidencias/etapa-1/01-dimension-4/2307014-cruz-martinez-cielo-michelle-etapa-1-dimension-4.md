# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Cruz Martinez Cielo Michelle
**Matrícula:** 2307014

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Registro de asistencia

Una escuela quiere llevar el registro de entrada de sus empleados durante un
turno. Escribe un programa que:

1. Pregunte cuántos empleados se van a registrar en el turno (debe ser un
   número positivo; si el usuario introduce un valor inválido, debe volver a
   pedirlo).
2. Para cada empleado, pida la hora de entrada en formato de 24 horas como un
   solo número entero (por ejemplo, `815` para las 8:15, `1430` para las
   14:30).
3. Clasifique la entrada:
   - Si la hora es **menor o igual a 800** (8:00 am), el empleado llegó
     **puntual**.
   - Si es mayor, llegó **tarde**.
4. Lleva un contador de puntuales y otro de personas con retardo.
5. Al final, muestra un reporte con el total de empleados registrados, cuántos
   llegaron puntuales y cuántos con retardo.

## Programa 2 — Caseta de cobro

Una caseta de cobro en carretera tiene 3 casetas activas al mismo tiempo, cada
una para un tipo de vehículo distinto: **1) Automóvil**, **2) Autobús**,
**3) Camión de carga**. La caseta ya tiene definida una tarifa fija por tipo de
vehículo; el operador solo registra qué tipo de vehículo pasó, no cobra montos
distintos cada vez. Escribe un programa que:

1. Defina en el código, como **constantes**, la tarifa de cada tipo de
   vehículo:
   - Automóvil: $45.00
   - Autobús: $90.00
   - Camión de carga: $150.00
2. Muestre un menú con las 3 opciones de tipo de vehículo más una cuarta
   opción para **finalizar el turno**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "finalizar", usa la tarifa constante correspondiente al
   tipo de vehículo elegido para acumular el total de esa caseta, además de
   contar cuántos vehículos de ese tipo han pasado.
5. El programa debe seguir mostrando el menú y registrando vehículos hasta que
   el usuario elija "finalizar turno".
6. Al finalizar, muestra un reporte con: cantidad de vehículos por tipo,
   cantidad total de vehículos, efectivo cobrado por tipo (calculado a partir
   de la tarifa constante) y efectivo total del turno.

## Requisitos técnicos (ambos programas)

- Las tarifas/precios del Programa 2 se definen como constantes dentro del
  código; **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y, si el ejercicio pide una cantidad
  (piezas, litros, horas, etc.), esa **cantidad** (debe ser un número
  positivo). Ambos deben volver a pedirse si el valor es inválido, sin
  terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
