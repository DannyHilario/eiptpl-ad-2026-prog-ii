# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Hernandez Lopez Jose
**Matrícula:** 2306741

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Monitoreo de consumo eléctrico

Una compañía de luz revisa el consumo mensual de varias casas de una colonia.
Escribe un programa que:

1. Pregunte cuántas casas se van a revisar (debe ser un número positivo; si
   el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada casa, pida su consumo del mes en kWh (número decimal).
3. Clasifique la casa:
   - Si el consumo es **mayor a 300 kWh**, se considera **alto consumo**.
   - En caso contrario, se considera **consumo normal**.
4. Lleva un contador de casas con consumo normal y otro de casas con alto
   consumo.
5. Al final, muestra un reporte con el total de casas revisadas, cuántas
   tuvieron consumo normal y cuántas alto consumo.

## Programa 2 — Farmacia

Una farmacia vende 3 productos de mostrador con precio fijo:
**1) Paracetamol (caja)**, **2) Gel antibacterial**, **3) Cubrebocas
(paquete)**. Escribe un programa que:

1. Defina en el código, como **constantes**, el precio unitario de cada
   producto:
   - Paracetamol (caja): $45.00
   - Gel antibacterial: $38.00
   - Cubrebocas (paquete): $25.00
2. Muestre un menú con los 3 productos más una cuarta opción para **cerrar
   la caja**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas piezas** de ese producto se
   están comprando (número entero positivo; si es inválido, debe volver a
   pedirse) y usa el precio constante correspondiente para calcular el monto
   de esa venta, acumulándolo en el total de su producto, además de contar
   cuántas piezas de ese producto se han vendido.
5. El programa debe seguir mostrando el menú y registrando ventas hasta que el
   usuario elija "cerrar la caja".
6. Al finalizar, muestra un reporte con: piezas vendidas por producto,
   cantidad total de piezas vendidas, monto recaudado por producto
   (calculado a partir del precio constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Los precios del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de piezas** (debe ser un
  número entero positivo). Ambos deben volver a pedirse si el valor es
  inválido, sin terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
