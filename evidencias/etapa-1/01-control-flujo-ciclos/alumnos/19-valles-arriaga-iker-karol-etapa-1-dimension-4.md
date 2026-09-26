# Evidencia — Etapa 1, Dimensión 4 (Aplicación)

**Alumno:** Valles Arriaga Iker Karol
**Matrícula:** 2306396

Esta evidencia consta de **dos programas independientes** en C++. Ambos retoman
lo visto en control de flujo y control de ciclos (condicionales, `switch`,
`for`, `while`/`do-while`, validación de datos, contadores y acumuladores).
Cada programa debe compilar y ejecutarse sin errores, y mostrar un reporte
final legible.

## Programa 1 — Tiempo de espera en caja

Un supermercado mide el tiempo de espera de varios clientes en la fila de
caja. Escribe un programa que:

1. Pregunte cuántos clientes se van a revisar (debe ser un número positivo;
   si el usuario introduce un valor inválido, debe volver a pedirlo).
2. Para cada cliente, pida el tiempo que esperó en fila, en minutos (número
   decimal).
3. Clasifique la espera:
   - Si el tiempo es **mayor a 10 minutos**, la espera se considera
     **excesiva**.
   - En caso contrario, se considera **aceptable**.
4. Lleva un contador de esperas aceptables y otro de esperas excesivas.
5. Al final, muestra un reporte con el total de clientes revisados, cuántos
   tuvieron espera aceptable y cuántos espera excesiva.

## Programa 2 — Renta de canchas deportivas

Un centro deportivo renta canchas por hora según la disciplina:
**1) Fútbol**, **2) Básquetbol**, **3) Tenis**. Cada disciplina tiene una
tarifa fija por hora. Escribe un programa que:

1. Defina en el código, como **constantes**, la tarifa por hora de cada
   cancha:
   - Fútbol: $250.00
   - Básquetbol: $180.00
   - Tenis: $150.00
2. Muestre un menú con las 3 disciplinas más una cuarta opción para
   **cerrar el módulo**.
3. Valide que la opción introducida esté entre 1 y 4; si no, muestre un error
   y vuelva a pedir la opción (sin salir del programa).
4. Si la opción no es "cerrar", pida **cuántas horas** se va a rentar la
   cancha (número decimal positivo; si es inválido, debe volver a pedirse) y
   usa la tarifa constante correspondiente para calcular el monto de esa
   renta, acumulándolo en el total de su disciplina, además de contar
   cuántas rentas de esa disciplina se han hecho.
5. El programa debe seguir mostrando el menú y registrando rentas hasta que
   el usuario elija "cerrar el módulo".
6. Al finalizar, muestra un reporte con: rentas hechas por disciplina,
   rentas totales, monto recaudado por disciplina (calculado a partir de la
   tarifa constante) y monto total del día.

## Requisitos técnicos (ambos programas)

- Las tarifas del Programa 2 se definen como constantes dentro del código;
  **no se le piden al usuario**.
- En el Programa 2 debes validar dos datos numéricos distintos: la **opción
  del menú** (debe estar entre 1 y 4) y la **cantidad de horas** (debe ser un
  número positivo). Ambos deben volver a pedirse si el valor es inválido, sin
  terminar el programa.
- Usa nombres de variable descriptivos y constantes donde aplique.
