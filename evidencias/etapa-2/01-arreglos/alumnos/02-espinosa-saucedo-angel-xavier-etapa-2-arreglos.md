# Evidencia 2.2 — Control de calidad por lotes

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 02 — Espinosa Saucedo Angel Xavier

## Historia de usuario

**Como** inspector de calidad de una fábrica de piezas metálicas, **quiero** registrar cuánto se desvía del peso ideal cada pieza de muestra de un lote y consultar qué lotes quedan fuera de tolerancia, **para** detener a tiempo los lotes defectuosos.

## Contexto

En la Evidencia 1 tu programa revisaba el peso de cada pieza en el momento (dentro o fuera de 495–505 g) y lo olvidaba. Ahora la fábrica necesita **guardar** los datos de cada lote: de cada lote se toman 4 piezas de muestra y se anota cuántos gramos se desvía cada una del peso ideal de 500 g (una pieza de 497 g o de 503 g se desvía 3 g).

Los datos forman una tabla:

|  | Pieza 1 | Pieza 2 | Pieza 3 | Pieza 4 |
|---|---|---|---|---|
| **Lote 1** | 1.5 | 2 | 3 | 0.5 |
| **Lote 2** | 6 | 8 | 4.5 | 9.5 |
| ... | | | | |

**Reglas**

- La fábrica registra como máximo **7 lotes** por turno.
- De cada lote se revisan **4 piezas** de muestra.
- La desviación de una pieza es válida si está entre **0 y 50 gramos**.
- Un lote está **dentro de tolerancia** si el **promedio** de la desviación de sus 4 piezas es **menor o igual a 5 g**; si no, está **fuera de tolerancia**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
CONTROL DE CALIDAD POR LOTES

1.- Registrar un lote
2.- Reporte general
3.- Tabla de desviaciones
4.- Salir
```

- **Opción 1:** pide los datos de las 4 piezas del siguiente lote y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  lotes registrados, cuántos quedan como *Dentro de tolerancia* y cuántos como *Fuera de tolerancia*
  (con sus porcentajes), y el promedio de desviación de todos los lotes.
- **Opción 3:** muestra la tabla de todos los lotes registrados: una
  fila por lote, con sus 4 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan lotes.** El programa no permite eliminar ni modificar
un lote ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 7.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `desviaciones`** guarda lo que el usuario **captura**: los 4 datos de
  cada lote.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  lote.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del lote 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del lote 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos lotes:

```
                 desviaciones                   promedios
             [0]    [1]    [2]    [3]
fila 0       1.5      2      3    0.5     →     [0]  1.75
fila 1         6      8    4.5    9.5     →     [1]  7
fila 2   (vacía)                                [2]  (vacío)
 ...
fila 6   (vacía)                                [6]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 4 datos del siguiente lote en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 4 datos y se divide entre 4, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos lotes
quedan en cada clasificación, y la opción 3 imprime cada fila de la matriz con
su promedio al final.

**¿Por qué no guardar el promedio como una columna más de la matriz?** Porque
entonces la matriz tendría columnas de dos tipos: 4 que captura el usuario y 1
que calcula el programa. Tendrías que recordar que la columna `[4]` "no
cuenta" al capturar ni al sumar. Con dos arreglos separados, la matriz siempre
se recorre de la columna 0 a la 3, sin excepciones.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de
una sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de arreglos

- [ ] Los datos que captura el usuario se guardan en una **matriz** `double` de
      7 × 4: cada fila es un lote y cada columna una pieza.
- [ ] El promedio de cada lote se guarda en un **vector** `double` de 7
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos lotes se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de lotes (7), los datos por lote (4), los
      límites de un dato válido (0 y 50) y el límite de
      la clasificación (5) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los lotes registrados**, no las
      7 filas de la matriz.
- [ ] Si ya hay 7 lotes registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay lotes registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 50; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** pieza (no se salta a
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
      7:40 p.m.**
- [ ] El archivo es de texto plano, con el nombre `EV2.2_ApellidoNombre.txt`.
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu
      código si se te pregunta.

## Ejemplo de ejecución

Registro del primer lote, con dos datos fuera de rango:

```
Opcion: 1

LOTE 1
  Pieza 1: 1.5
  Pieza 2: 60
  ERROR! El dato debe estar entre 0 y 50 g
  Pieza 2: -1
  ERROR! El dato debe estar entre 0 y 50 g
  Pieza 2: 2
  Pieza 3: 3
  Pieza 4: 0.5

Promedio: 1.75 g -> Dentro de tolerancia
```

Después de registrar los 3 lotes de los casos de prueba:

```
Opcion: 2

REPORTE GENERAL

Lotes registrados: 3
Dentro de tolerancia: 2 (66.67%)
Fuera de tolerancia: 1 (33.33%)
Promedio de desviacion de todos los lotes: 4.58 g
```

```
Opcion: 3

TABLA DE DESVIACIONES

            P1    P2    P3    P4   Promedio
Lote 1     1.5     2     3   0.5       1.75   Dentro de tolerancia
Lote 2       6     8   4.5   9.5          7   Fuera de tolerancia
Lote 3       5     5     5     5          5   Dentro de tolerancia
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay lotes registrados |
| 2 | Registro del lote 1 | Lote 1: 1.5, 2, 3, 0.5 | Promedio 1.75 → Dentro de tolerancia |
| 3 | Registro del lote 2 | Lote 2: 6, 8, 4.5, 9.5 | Promedio 7 → Fuera de tolerancia |
| 4 | Justo en el límite | Lote 3: 5, 5, 5, 5 | Promedio 5 → **Dentro de tolerancia** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Dentro de tolerancia: 2 (66.67%); Fuera de tolerancia: 1 (33.33%); Promedio de desviación de todos los lotes: 4.58 g |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Dato fuera de rango | Un dato de 60 o de -1 | Error; vuelve a pedir el dato de esa misma pieza |
| 8 | Registro lleno | Opción 1 con 7 lotes ya registrados | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
