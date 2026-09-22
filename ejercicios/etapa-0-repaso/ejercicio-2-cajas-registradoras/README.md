# Ejercicio 2 — Menú de cajas registradoras

*Etapa 0 — Repaso · Temas: `do...while`, `switch`, contadores y acumuladores · Solución: [`etapa-0-ejercicio-2.cpp`](etapa-0-ejercicio-2.cpp)*

## Historia de usuario

**Como** gerente de una tienda con 3 cajas, **quiero** registrar cada cobro
indicando en qué caja se hizo, **para** obtener al cerrar el turno cuánto
efectivo y cuántos clientes atendió cada caja y la tienda completa.

## Contexto

Durante el turno, cada vez que una caja cobra, se elige esa caja en un menú y
se captura el efectivo cobrado. El menú se repite hasta que se elige
"Finalizar turno", y entonces se muestra el reporte del turno.

Para cada caja hacen falta dos variables:

- un **contador** de clientes (suma 1 por cada cobro), y
- un **acumulador** de efectivo (suma el monto de cada cobro).

## Criterios de aceptación

- [ ] Muestra un menú con 4 opciones: Caja 1, Caja 2, Caja 3 y Finalizar turno,
      junto con el número de transacción actual.
- [ ] Si la opción no está entre 1 y 4, muestra un error y vuelve a mostrar el
      menú.
- [ ] Si se eligió una caja (1–3), pide el efectivo cobrado y lo suma al
      acumulador de esa caja; también suma 1 a su contador de clientes. Usa un
      `switch` para decidir qué caja actualizar.
- [ ] Si se eligió Finalizar turno (4), no pide efectivo.
- [ ] El menú se repite con `do...while` hasta que se elige la opción 4.
- [ ] El reporte final muestra, por caja y en total, los clientes atendidos y
      el efectivo cobrado.

## Ejemplo de ejecución

```
********** MENU PRINCIPAL **********

Numero de Transaccion: 1

Opcion 1: Caja 1
Opcion 2: Caja 2
Opcion 3: Caja 3
Opcion 4: Finalizar Turno

Introduce una opcion: 1
Introduce el efectivo cobrado: 50

   (... transacción 2: caja 2, $30 ...)
   (... transacción 3: caja 1, $20 ...)

Introduce una opcion: 4

********** REPORTE FINAL **********

Clientes Caja 1: 2
Clientes Caja 2: 1
Clientes Caja 3: 0
Clientes TOTALES: 3

Efectivo Caja 1: 70
Efectivo Caja 2: 30
Efectivo Caja 3: 0
Efectivo TOTAL: 100
```

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Turno normal | Caja 1 $50, Caja 2 $30, Caja 1 $20, Finalizar | Caja 1: 2 clientes, $70 · Caja 2: 1 cliente, $30 · Caja 3: 0, $0 · Total: 3 clientes, $100 |
| 2 | Opción inválida | opción = 5 | `ERROR. Valor no permitido` y vuelve a mostrar el menú (el número de transacción no avanza) |
| 3 | Turno sin cobros | Finalizar de inmediato | Todas las cajas y el total en 0 |

## Historial de cambios

Cómo fue cambiando la solución de este ejercicio a lo largo del curso.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 10 ago 2026 | Primer avance: el menú con `do...while`, la validación de la opción y un `switch` cuyos casos solo imprimían un mensaje temporal. | Construir primero la estructura del menú y probar que funciona, antes de meter la lógica de cada caja. |
| 13 ago 2026 | Se completó: contador y acumulador por cada caja, número de transacción en el menú, captura del efectivo (solo si no se eligió Finalizar) y reporte final con totales. | Repaso de contadores y acumuladores trabajando en paralelo. |
| 17 ago 2026 | El archivo se movió a la carpeta de la Etapa 0. | Reorganización por etapas. |
| 4 sep 2026 | Los montos de efectivo cambiaron de `float` a `double`. | `double` tiene más precisión para montos de dinero. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
