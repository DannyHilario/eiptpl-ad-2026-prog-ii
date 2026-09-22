# Ejercicio 5 — Captura de calificaciones en una matriz

*Etapa II — Arreglos · Temas: 2.2 (arreglos bidimensionales), 2.4 (recorrido con `for` anidado) · Solución: `etapa-2-ejercicio-5.cpp` (se escribe en clase)*

## Historia de usuario

**Como** docente, **quiero** capturar las calificaciones de los 3 parciales de
cada alumno de mi grupo y verlas en forma de tabla, **para** revisar de un
vistazo que todas quedaron registradas correctamente.

## Contexto

Hasta ahora cada arreglo guardaba una sola lista de valores (un vector). Aquí
cada alumno tiene **varias** calificaciones, así que los datos forman una tabla:

|  | Parcial 1 | Parcial 2 | Parcial 3 |
|---|---|---|---|
| **Alumno 1** | 80 | 90 | 70 |
| **Alumno 2** | 60 | 75 | 90 |
| **Alumno 3** | 100 | 85 | 95 |
| **Alumno 4** | 50 | 65 | 80 |
| **Alumno 5** | 70 | 70 | 85 |

Esa tabla es una **matriz** `calificaciones[5][3]`: cada **fila** es un alumno y
cada **columna** es un parcial. Como los índices empiezan en 0,
`calificaciones[2][0]` es la calificación del alumno 3 en el parcial 1 (100).

Para recorrer una matriz se usan dos `for`, uno dentro del otro:

- el de **afuera** recorre las filas (alumnos), y
- el de **adentro** recorre las columnas (parciales) de esa fila.

La captura y la impresión usan exactamente el mismo par de ciclos; solo cambia
`cin` por `cout`.

## Criterios de aceptación

- [ ] La cantidad de alumnos (5) y de parciales (3) son constantes con nombre
      (`NUM_ALUMNOS`, `NUM_PARCIALES`), y la matriz se declara con ellas.
- [ ] Captura las calificaciones con dos `for` anidados: el de afuera recorre
      alumnos y el de adentro recorre parciales.
- [ ] Al capturar, indica de qué alumno y de qué parcial es cada calificación.
- [ ] Cada calificación debe estar entre 0 y 100; si no, muestra un error y
      vuelve a pedir **esa misma** calificación (no se salta al siguiente
      parcial).
- [ ] Después de capturar todo, imprime la matriz como tabla: una fila por
      alumno, con sus 3 calificaciones en la misma línea, usando otro par de
      `for` anidados.
- [ ] Todo el programa vive en `main` (todavía sin funciones).
- [ ] Compila sin warnings con `g++ -std=c++17 -Wall`.

## Ejemplo de ejecución

```
CAPTURA DE CALIFICACIONES

Alumno 1
  Parcial 1: 80
  Parcial 2: 90
  Parcial 3: 70
Alumno 2
  Parcial 1: 60
  Parcial 2: 75
  Parcial 3: 150
  ERROR! La calificacion debe estar entre 0 y 100
  Parcial 3: 90
Alumno 3
  Parcial 1: 100
  Parcial 2: 85
  Parcial 3: 95
Alumno 4
  Parcial 1: 50
  Parcial 2: 65
  Parcial 3: 80
Alumno 5
  Parcial 1: 70
  Parcial 2: 70
  Parcial 3: 85

TABLA DE CALIFICACIONES

           P1    P2    P3
Alumno 1   80    90    70
Alumno 2   60    75    90
Alumno 3  100    85    95
Alumno 4   50    65    80
Alumno 5   70    70    85
```

Los mensajes y la alineación de la tabla pueden variar; lo importante es que
cada alumno quede en su propia fila con sus 3 calificaciones.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Captura completa | Las 15 calificaciones de la tabla de arriba | La tabla impresa es idéntica a la capturada, fila por fila |
| 2 | Calificación mayor a 100 | Alumno 2, Parcial 3 = 150 | Error; vuelve a pedir el **Parcial 3 del Alumno 2** |
| 3 | Calificación negativa | cualquier parcial = -5 | Error; vuelve a pedir esa misma calificación |
| 4 | Límites válidos | una calificación = 0 y otra = 100 | Ambas se aceptan |
| 5 | Orden de filas y columnas | Alumno 3: 100, 85, 95 | En la tabla, el 100 aparece en la fila del Alumno 3, columna P1 — no en la fila del Alumno 1 |

**Pista para el caso 5:** si la tabla sale "volteada" (los alumnos como
columnas), revisa qué índice usa el `for` de afuera y cuál el de adentro, y en
qué orden van dentro de `calificaciones[?][?]`.

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 22 sep 2026 | Se creó esta ficha. La solución se escribe en clase. | Primer contacto con matrices: capturar y recorrer una tabla completa, no solo leer una matriz fija como en el [Ejercicio 4](../ejercicio-4-isr-con-matriz/README.md). |

**Siguiente clase:** este mismo programa se va a dividir en funciones, pasando
la matriz como parámetro. Guarda tu solución: vas a partir de ella.
