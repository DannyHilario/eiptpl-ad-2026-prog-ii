# Ejercicio 7 — Registro de calificaciones con menú

*Etapa II — Arreglos · Temas: 2.2 (matrices), 2.4 (recorrido con `for`) + vector paralelo · Solución: `etapa-2-ejercicio-7.cpp` (se escribe en clase)*

## Historia de usuario

**Como** docente, **quiero** registrar las calificaciones de los 3 parciales de
mis alumnos conforme me las van entregando y consultar en cualquier momento
cuántos van aprobados, **para** detectar a tiempo a quién hay que apoyar.

## Contexto

Es la continuación del
[Ejercicio 5](../ejercicio-5-matriz-calificaciones/README.md). Ahí el programa
capturaba a los 5 alumnos de una sola vez y al final imprimía la tabla. Ahora
el programa se controla con un **menú** y los alumnos se registran **uno a la
vez**, cuando el usuario lo decide:

```
REGISTRO DE CALIFICACIONES

1.- Registrar un alumno
2.- Reporte del grupo
3.- Tabla de calificaciones
4.- Salir
```

- **Opción 1:** pide las 3 calificaciones del siguiente alumno y, al terminar,
  muestra su promedio y si está *Aprobado* o *Reprobado*.
- **Opción 2:** muestra el total de alumnos registrados, cuántos van aprobados y
  cuántos reprobados (con sus porcentajes), y el promedio del grupo.
- **Opción 3:** muestra la tabla de los alumnos registrados: una fila por
  alumno, con sus 3 calificaciones, su promedio y su resultado.
- **Opción 4:** termina el programa. Es la única forma de salir.

**Reglas:** como máximo 5 alumnos; cada calificación está entre 0 y 100; un
alumno aprueba si su promedio es **mayor o igual a 70**. Solo se agregan
alumnos: no se eliminan ni se modifican.

Esta es la misma estructura que vas a usar en tu
[Evidencia 2.2](../../../evidencias/etapa-2/03-arreglos/descripcion.md): cambian
el contexto, los tamaños y las reglas, pero el menú, los arreglos y las
validaciones son los mismos.

## Cómo se organizan los datos

El programa usa **dos arreglos que trabajan juntos** y un **contador**:

- La **matriz `calificaciones[5][3]`** guarda lo que el usuario captura: una fila
  por alumno y una columna por parcial.
- El **vector `promedios[5]`** guarda lo que el programa calcula: el promedio de
  la fila `i` va en la posición `i`.
- El **contador `registrados`** dice cuántos alumnos hay y, al mismo tiempo, en
  qué fila va el siguiente.

Después de registrar dos alumnos:

```
                calificaciones                  promedios
             [0]      [1]      [2]
fila 0        80       90       70      →      [0]  80
fila 1        60       65       55      →      [1]  60
fila 2    (vacía)                              [2]  (vacío)
fila 3    (vacía)                              [3]  (vacío)
fila 4    (vacía)                              [4]  (vacío)

registrados = 2   → el siguiente alumno se guarda en la fila 2
```

**Qué cambia respecto al Ejercicio 5:**

- El `for` de afuera ya no recorre a los 5 alumnos: la opción 1 captura **una
  sola fila**, la que indica `registrados`, y después le suma 1.
- Las opciones 2 y 3 recorren **solo hasta `registrados`**, no las 5 filas: las
  filas vacías tienen basura (tema 2.2).
- El promedio se calcula **una vez**, al capturar, y se guarda en el vector; las
  opciones 2 y 3 solo lo **leen**.

## Criterios de aceptación

- [ ] `MAX_ALUMNOS` (5), `PARCIALES` (3), los límites de una calificación (0 y
      100) y la mínima aprobatoria (70) son constantes con nombre. La matriz y el
      vector se declaran con ellas.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada calificación debe estar entre 0 y 100; si no, muestra un error y
      vuelve a pedir **esa misma** calificación.
- [ ] Si ya hay 5 alumnos registrados, la opción 1 avisa que el registro está
      lleno y no guarda nada fuera de la matriz.
- [ ] Si todavía no hay alumnos registrados, las opciones 2 y 3 muestran un aviso
      en lugar del reporte o la tabla.
- [ ] Las opciones 2 y 3 recorren solo los alumnos registrados y leen el promedio
      del vector.
- [ ] Todo el programa vive en `main` (sin funciones propias).
- [ ] Compila sin warnings con `g++ -std=c++17 -Wall`.

## Ejemplo de ejecución

```
Opcion: 1

ALUMNO 1
  Parcial 1: 80
  Parcial 2: 150
  ERROR! La calificacion debe estar entre 0 y 100
  Parcial 2: 90
  Parcial 3: 70

Promedio: 80 -> Aprobado
```

Después de registrar los 3 alumnos de los casos de prueba:

```
Opcion: 2

REPORTE DEL GRUPO

Alumnos registrados: 3
Aprobados: 2 (66.67%)
Reprobados: 1 (33.33%)
Promedio del grupo: 70
```

```
Opcion: 3

TABLA DE CALIFICACIONES

             P1    P2    P3   Promedio
Alumno 1     80    90    70         80   Aprobado
Alumno 2     60    65    55         60   Reprobado
Alumno 3     70    70    70         70   Aprobado
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay alumnos registrados |
| 2 | Registro normal | Alumno 1: 80, 90, 70 | Promedio 80 → Aprobado |
| 3 | Reprobado | Alumno 2: 60, 65, 55 | Promedio 60 → Reprobado |
| 4 | Justo en el límite | Alumno 3: 70, 70, 70 | Promedio 70 → **Aprobado** |
| 5 | Reporte | Opción 2 después de los casos 2 a 4 | Total 3; aprobados 2 (66.67%); reprobados 1 (33.33%); promedio del grupo 70 |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | Las 3 filas en el orden en que se registraron, con su promedio y resultado |
| 7 | Calificación fuera de rango | 150 o -5 | Error; vuelve a pedir ese mismo parcial |
| 8 | Registro lleno | Opción 1 con 5 alumnos ya registrados | Aviso de registro lleno; no pide calificaciones |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los porcentajes están redondeados a 2 decimales; `cout` sin formato puede
mostrar `66.6667`.

**Pista para el caso 8:** si al registrar al sexto alumno el programa sigue
pidiendo calificaciones, revisa que la opción 1 compare `registrados` contra
`MAX_ALUMNOS` **antes** de capturar. Sin esa revisión, se escribe en la fila 5,
que no existe.

## Autocheck

**¿Por qué el contador `registrados` sirve también como índice de la fila?**
Porque las filas se llenan en orden desde la 0: si hay 2 alumnos registrados,
ocupan las filas 0 y 1, y la siguiente libre es justamente la 2.

**¿Por qué las opciones 2 y 3 no recorren hasta `MAX_ALUMNOS`?**
Porque las filas que todavía no se capturan tienen basura: el reporte contaría
alumnos que no existen y la tabla imprimiría valores sin sentido.

**¿Qué ganamos al guardar el promedio en un vector en vez de calcularlo cada
vez?**
Se calcula una sola vez, al capturar, y las opciones 2 y 3 solo lo leen. Además,
la matriz guarda solo lo que capturó el usuario: sus columnas siempre son los 3
parciales.

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 28 sep 2026 | Se creó esta ficha. La solución se escribe en clase. | Ejemplo guiado de la estructura de la Evidencia 2.2 (menú, matriz, vector paralelo y contador), a partir del Ejercicio 5. |
