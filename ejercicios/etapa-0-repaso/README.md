# Etapa 0 — Repaso (ejercicios)

Cada ejercicio vive en su propia carpeta, con su ficha (`README.md`: historia de
usuario, criterios de aceptación, casos de prueba e historial de cambios) y su
solución (`.cpp`).

Esta etapa es previa a funciones — todo vive en un solo `main()`, con
condicionales (`if`/`else`, `switch`) y ciclos (`for`, `while`/`do-while`),
validación de datos, contadores y acumuladores. No aplica todavía la regla de
"funciones puras sin `cin`/`cout`" que sí sigue [Etapa I](../etapa-1-funciones/README.md).

| # | Ejercicio | Temas | Estado de la solución |
|---|---|---|---|
| 1 | [Promedio y reporte de aprobados/reprobados](ejercicio-1-promedio-aprobados/README.md) | `for`, `if`/`else`, contadores | Completa |
| 2 | [Menú de cajas registradoras](ejercicio-2-cajas-registradoras/README.md) | `do...while`, `switch`, acumuladores | Completa |
| 3 | [Clasificador de temperaturas](ejercicio-3-temperaturas/README.md) | validación, `if`/`else if`, acumuladores | Incompleta |

Estos ejercicios corresponden al
[Laboratorio de repaso](../../contenido/etapa-0-repaso/02-laboratorio-repaso.md)
de `contenido/`, pero no son idénticos: el Ejercicio 1 de clase usa 3
calificaciones por alumno, mientras que el laboratorio pide una sola
calificación final y el porcentaje de aprobación.

## Pendientes en las soluciones

- **Ejercicio 3:** solo valida la cantidad de días; falta pedir, validar,
  clasificar y acumular cada temperatura, y el reporte final.
