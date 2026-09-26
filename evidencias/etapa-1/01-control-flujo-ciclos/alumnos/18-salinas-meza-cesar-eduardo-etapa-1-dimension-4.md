# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Salinas Meza Cesar Eduardo
**Matrícula:** 2306493

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Consumo de datos móviles

Una compañía telefónica revisa el consumo mensual de datos de varias líneas
con un plan de 5 GB. Escribe un programa que:

1. Pregunte cuántas líneas se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada línea, pida el consumo de datos del mes en GB (número decimal).
3. Clasifique la línea:
   - Si el consumo es **mayor a 5 GB**, la línea **excede el plan**.
   - En caso contrario, está **dentro del plan**.
4. Lleva un contador de líneas dentro del plan y otro de líneas que lo
   exceden.
5. Al final, muestra un reporte con el total de líneas revisadas, cuántas
   estuvieron dentro del plan y cuántas lo excedieron.

## Programa 2 — Recargas de tiempo aire

Una tienda vende recargas de tiempo aire con 3 planes: **1) Plan básico**,
**2) Plan intermedio**, **3) Plan premium**. Cada plan tiene un precio fijo
de recarga. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio de cada plan:
   - Plan básico: $50.00
   - Plan intermedio: $100.00
   - Plan premium: $200.00
2. Muestre un menú con los 3 planes más una cuarta opción para **cerrar la
   caja**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", usa el precio constante correspondiente al
   plan elegido para acumular el total de ese plan, además de contar cuántas
   recargas de ese plan se han hecho.
5. El programa debe seguir mostrando el menú y registrando recargas hasta
   que el usuario elija "cerrar la caja".
6. Al finalizar, muestra un reporte con: recargas hechas por plan, recargas
   totales, monto recaudado por plan (calculado a partir del precio
   constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar la **opción del menú** (debe estar entre 1
  y 4); si el ejercicio pide además una cantidad numérica (piezas, litros,
  horas, etc.), esa cantidad también debe validarse. Ambos deben volver a
  pedirse si el valor es inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
