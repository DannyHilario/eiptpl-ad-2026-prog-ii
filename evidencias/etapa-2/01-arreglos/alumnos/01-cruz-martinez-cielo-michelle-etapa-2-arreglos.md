# Evidencia 2.2 — Registro de puntualidad semanal

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 01 — Cruz Martinez Cielo Michelle

## Historia de usuario

**Como** encargado de recursos humanos de una escuela, **quiero** registrar los minutos de retardo de cada empleado durante los 5 días de la semana y consultar quiénes acumulan demasiados, **para** saber a quién hablarle antes de que se convierta en un problema.

## Contexto

En la Evidencia 1 tu programa clasificaba la hora de entrada de cada empleado en el momento (puntual o tarde) y la olvidaba. Ahora la escuela necesita **guardar** los retardos de toda la semana para decidir con el total acumulado, no con un solo día.

Los datos forman una tabla:

|  | Día 1 | Día 2 | Día 3 | Día 4 | Día 5 |
|---|---|---|---|---|---|
| **Empleado 1** | 0 | 5 | 0 | 3 | 2 |
| **Empleado 2** | 10 | 15 | 0 | 20 | 5 |
| ... | | | | | |

**Reglas**

- La escuela registra como máximo **8 empleados**.
- De cada empleado se registran los **minutos de retardo de 5 días** (lunes a viernes). Un `0` significa que ese día llegó a tiempo.
- Los minutos de retardo de un día son válidos si están entre **0 y 120**.
- Un empleado es **puntual** si el **total** de sus minutos de retardo en la semana es **menor o igual a 15**; si no, queda **con retardos**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
REGISTRO DE PUNTUALIDAD

1.- Registrar un empleado
2.- Reporte general
3.- Tabla de retardos
4.- Salir
```

- **Opción 1:** pide los datos de los 5 días del siguiente empleado y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  empleados registrados, cuántos quedan como *Puntual* y cuántos como *Con retardos*
  (con sus porcentajes), y el promedio de minutos de retardo por empleado.
- **Opción 3:** muestra la tabla de todos los empleados registrados: una
  fila por empleado, con sus 5 datos, su total y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan empleados.** El programa no permite eliminar ni modificar
un empleado ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 8.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `retardos`** guarda lo que el usuario **captura**: los 5 datos de
  cada empleado.
- El **vector `totales`** guarda lo que el programa **calcula**: el total de cada
  empleado.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del empleado 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del empleado 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos empleados:

```
                       retardos                        totales
             [0]    [1]    [2]    [3]    [4]
fila 0         0      5      0      3      2     →     [0]  10
fila 1        10     15      0     20      5     →     [1]  50
fila 2   (vacía)                                       [2]  (vacío)
 ...
fila 7   (vacía)                                       [7]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 5 datos del siguiente empleado en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 5 datos, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el total?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos empleados
quedan en cada clasificación, y la opción 3 imprime cada fila de la matriz con
su total al final.

**¿Por qué no guardar el total como una columna más de la matriz?** Porque
entonces la matriz tendría columnas de dos tipos: 5 que captura el usuario y 1
que calcula el programa. Tendrías que recordar que la columna `[5]` "no
cuenta" al capturar ni al sumar. Con dos arreglos separados, la matriz siempre
se recorre de la columna 0 a la 4, sin excepciones.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de
una sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de arreglos

- [ ] Los datos que captura el usuario se guardan en una **matriz** `double` de
      8 × 5: cada fila es un empleado y cada columna un día.
- [ ] El total de cada empleado se guarda en un **vector** `double` de 8
      posiciones: el total de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos empleados se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de empleados (8), los datos por empleado (5), los
      límites de un dato válido (0 y 120) y el límite de
      la clasificación (15) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el total del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los empleados registrados**, no las
      8 filas de la matriz.
- [ ] Si ya hay 8 empleados registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay empleados registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 120; si no, muestra un
      error y vuelve a pedir el dato de **ese mismo** día (no se salta a
      la siguiente).
- [ ] Los resultados coinciden con **todos** los casos de prueba de este
      enunciado.

**Código fácil de seguir y leer**

- [ ] Todo el programa vive en `main` (sin funciones propias).
- [ ] Nombres de variable descriptivos.
- [ ] Comentarios que expliquen cada sección del programa (captura, reporte,
      tabla, validaciones).
- [ ] Compila y se ejecuta sin errores en Dev-C++.

### Actitudes / Valores (2 puntos) — Entrega

- [ ] Lo entregas en NEXUS, en la evidencia *"2.2 - Evidencia de Aprendizaje 2:
      Laboratorio de Programas"*, antes del **jueves 1 de octubre de 2026 a las
      8:40 p.m.**
- [ ] El archivo es de texto plano, con el nombre `EV2.2_ApellidoNombre.txt`.
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu
      código si se te pregunta.

## Ejemplo de ejecución

```
Opcion: 1

EMPLEADO 1
  Dia 1: 0
  Dia 2: 150
  ERROR! El dato debe estar entre 0 y 120 min
  Dia 2: -3
  ERROR! El dato debe estar entre 0 y 120 min
  Dia 2: 5
  Dia 3: 0
  Dia 4: 3
  Dia 5: 2

Total: 10 min -> Puntual
```

```
Opcion: 3

TABLA DE RETARDOS

                D1    D2    D3    D4    D5   Total
Empleado 1       0     5     0     3     2      10   Puntual
Empleado 2      10    15     0    20     5      50   Con retardos
Empleado 3       5     5     5     0     0      15   Puntual
Empleado 4       0     0     0     0     0       0   Puntual
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay empleados registrados |
| 2 | Registro del empleado 1 | Empleado 1: 0, 5, 0, 3, 2 | Total 10 → Puntual |
| 3 | Registro del empleado 2 | Empleado 2: 10, 15, 0, 20, 5 | Total 50 → Con retardos |
| 4 | Justo en el límite | Empleado 3: 5, 5, 5, 0, 0 | Total 15 → **Puntual** |
| 5 | Registro del empleado 4 | Empleado 4: 0, 0, 0, 0, 0 | Total 0 → Puntual |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; Puntual: 3 (75%); Con retardos: 1 (25%); Promedio de minutos de retardo por empleado: 18.75 min |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 8 | Dato fuera de rango | Un dato de 150 o de -3 | Error; vuelve a pedir el dato de ese mismo día |
| 9 | Registro lleno | Opción 1 con 8 empleados ya registrados | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
