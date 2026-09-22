# Ejercicio 1 — Promedio y reporte de aprobados/reprobados

*Etapa 0 — Repaso · Temas: `for`, `if`/`else`, contadores · Solución: [`etapa-0-ejercicio-1.cpp`](etapa-0-ejercicio-1.cpp)*

## Historia de usuario

**Como** docente, **quiero** capturar las 3 calificaciones de cada alumno de mi
grupo y saber si aprobó, **para** obtener al final cuántos alumnos aprobaron y
cuántos reprobaron sin contarlos a mano.

## Contexto

Cada alumno tiene 3 calificaciones. Su calificación final es el promedio de las
tres, y aprueba si ese promedio es de al menos 70. El programa atiende a un
alumno a la vez y, al terminar con todo el grupo, muestra un reporte con los
totales.

## Criterios de aceptación

- [ ] La calificación mínima aprobatoria (70) es una constante con nombre.
- [ ] Pide cuántos alumnos se van a evaluar.
- [ ] Por cada alumno, con un ciclo `for`, pide sus 3 calificaciones y calcula
      el promedio.
- [ ] Muestra el promedio del alumno y si está APROBADO o REPROBADO.
- [ ] Lleva un contador de aprobados y otro de reprobados.
- [ ] Al terminar el grupo, muestra un reporte final con el total de aprobados
      y el de reprobados.

## Ejemplo de ejecución

```
Introduce la cantidad de alumnos a evaluar: 2

Introduce la primer calificacion: 80
Introduce la segunda calificacion: 90
Introduce la tercera calificacion: 70
El promedio del alumno es: 80
Alumno APROBADO :D
Presiona Enter para continuar...

Introduce la primer calificacion: 50
Introduce la segunda calificacion: 60
Introduce la tercera calificacion: 70
El promedio del alumno es: 60
Alumno REPROBADO :(
Presiona Enter para continuar...

 ********* REPORTE FINAL *********

 Aprobados: 1
 Reprobados: 1
```

## Casos de prueba

| # | Caso | Calificaciones | Salida esperada |
|---|---|---|---|
| 1 | Aprueba | 80, 90, 70 | Promedio 80, APROBADO |
| 2 | Reprueba | 50, 60, 70 | Promedio 60, REPROBADO |
| 3 | Justo en el mínimo | 70, 70, 70 | Promedio 70, APROBADO (70 sí aprueba) |
| 4 | Reporte final | Los casos 1 y 2 en el mismo grupo | Aprobados: 1, Reprobados: 1 |

## Historial de cambios

Cómo fue cambiando la solución de este ejercicio a lo largo del curso.

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 6 ago 2026 | Primera versión: un `for` por alumno que pide 3 calificaciones, calcula el promedio y dice si aprobó o no. | Repaso de ciclos y condicionales de Programación I. |
| 7 ago 2026 | Se agregaron dos contadores (`cantidad_aprobados` y `cantidad_reprobados`) y el reporte final con los totales del grupo. | Repaso de contadores: una variable que empieza en 0 y suma 1 cada vez que ocurre algo. |
| 17 ago 2026 | El archivo se movió a la carpeta de la Etapa 0. | Reorganización por etapas. |
| 20 ago 2026 | Se agregó el `return 0;` que faltaba al final de `main`. | Indica de forma explícita que el programa terminó bien. |
| 4 sep 2026 | Los contadores cambiaron de `float` a `int`. | Un contador solo cuenta enteros: no existen "1.5 alumnos aprobados". |
| 22 sep 2026 | Se quitó la variable `porcentaje_aprobados`, que se declaraba pero nunca se usaba. | `g++ -Wall` avisaba `unused variable 'porcentaje_aprobados'`. |
| 22 sep 2026 | El ejercicio se movió a su propia carpeta y se agregó esta ficha. | Reorganización: cada ejercicio con su enunciado junto a su solución. |
