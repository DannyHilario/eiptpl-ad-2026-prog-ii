# Etapa 0 — Repaso (ejercicios)

Resumen a alto nivel de cada ejercicio: qué resuelve y qué conceptos de repaso
cubre, sin repetir el código completo (eso ya vive en el `.cpp` correspondiente).

Esta etapa es previa a funciones — todo vive en un solo `main()`, con
condicionales (`if`/`else`, `switch`) y ciclos (`for`, `while`/`do-while`),
validación de datos, contadores y acumuladores. No aplica todavía la regla de
"funciones puras sin `cin`/`cout`" que sí sigue [Etapa I](../etapa-1-funciones/README.md).

---

## Ejercicio 1 — Promedio y reporte de aprobados/reprobados

`etapa-0-ejercicio-1.cpp` — **completo**.

Lee un grupo de `N` alumnos, cada uno con 3 calificaciones, calcula su promedio
y lo clasifica como aprobado/reprobado contra `CALIFICACION_MINIMA` (constante,
70). Al final imprime el conteo total de aprobados y reprobados.

Repasa: `for` controlado por contador, condicional simple `if`/`else`,
acumuladores (`cantidad_aprobados`, `cantidad_reprobados`).

---

## Ejercicio 2 — Menú de cajas registradoras

`etapa-0-ejercicio-2.cpp` — **completo**.

Simula el corte de turno de 3 cajas: en cada transacción el usuario elige una
caja (1-3) o finaliza el turno (4), captura el efectivo cobrado, y el programa
va acumulando efectivo y contando clientes por caja. Al finalizar, imprime el
reporte total por caja y el gran total.

Repasa: menú controlado por `do-while` + `switch`, validación de rango de
opción, múltiples contadores/acumuladores en paralelo (uno por caja).

---

## Ejercicio 3 — Estadísticas de temperaturas

`etapa-0-ejercicio-3.cpp` — **incompleto, pendiente de terminar**.

Enunciado: leer `N` temperaturas (validando que `N` sea positivo) y calcular
estadísticas del grupo — por ejemplo máxima, mínima y promedio.

Estado actual: solo valida `N` y repite un ciclo `for` que imprime
"Ejecucion I", pero **no lee las temperaturas ni calcula nada todavía** — el
`cin` de cada temperatura y la lógica de máximo/mínimo/acumulador para el
promedio faltan por escribir dentro del mismo `for`.
