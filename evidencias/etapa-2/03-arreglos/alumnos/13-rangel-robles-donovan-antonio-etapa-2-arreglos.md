# Evidencia 2.2 — Pruebas de tiempo de carga web

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 13 — Rangel Robles Donovan Antonio

## Historia de usuario

**Como** líder de un equipo de desarrollo web, **quiero** registrar el tiempo de carga de cada página en 5 pruebas y consultar cuáles son lentas, **para** decidir qué páginas optimizar primero.

## Contexto

En la Evidencia 1 tu programa medía cada página **una sola vez** y la olvidaba. Pero el tiempo de carga cambia según la red, así que ahora cada página se prueba **5 veces** y se decide con el promedio. Para eso hay que **guardar** los tiempos.

Los datos forman una tabla:

|  | Prueba 1 | Prueba 2 | Prueba 3 | Prueba 4 | Prueba 5 |
|---|---|---|---|---|---|
| **Página 1** | 1.5 | 2 | 1.8 | 2.2 | 2.5 |
| **Página 2** | 3.5 | 4 | 2.8 | 5.2 | 4.5 |
| ... | | | | | |

**Reglas**

- Se prueban como máximo **7 páginas** del sitio.
- Cada página se prueba **5 veces**.
- Un tiempo de carga es válido si está entre **0 y 60 segundos**.
- Una página es **rápida** si el **promedio** de sus 5 pruebas es **menor o igual a 3 segundos**; si no, es **lenta**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
PRUEBAS DE CARGA DEL SITIO WEB

1.- Registrar una pagina
2.- Reporte general
3.- Tabla de tiempos
4.- Salir
```

- **Opción 1:** pide los datos de las 5 pruebas de la siguiente página y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  páginas registradas, cuántas quedan como *Rapida* y cuántas como *Lenta*
  (con sus porcentajes), y el promedio de tiempo de carga del sitio.
- **Opción 3:** muestra la tabla de todas las páginas registradas: una
  fila por página, con sus 5 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan páginas.** El programa no permite eliminar ni modificar
una página ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 7.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `tiempos`** guarda lo que el usuario **captura**: los 5 datos de
  cada página.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  página.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la página 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la página 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos páginas:

```
                       tiempos                         promedios
             [0]    [1]    [2]    [3]    [4]
fila 0       1.5      2    1.8    2.2    2.5     →     [0]  2
fila 1       3.5      4    2.8    5.2    4.5     →     [1]  4
fila 2   (vacía)                                       [2]  (vacío)
 ...
fila 6   (vacía)                                       [6]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 5 datos de la siguiente página en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 5 datos y se divide entre 5, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas páginas
quedan en cada clasificación, y la opción 3 imprime cada fila de la matriz con
su promedio al final.

**¿Por qué no guardar el promedio como una columna más de la matriz?** Porque
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
      7 × 5: cada fila es una página y cada columna una prueba.
- [ ] El promedio de cada página se guarda en un **vector** `double` de 7
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas páginas se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de páginas (7), los datos por página (5), los
      límites de un dato válido (0 y 60) y el límite de
      la clasificación (3) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las páginas registradas**, no las
      7 filas de la matriz.
- [ ] Si ya hay 7 páginas registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay páginas registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 60; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** prueba (no se salta a
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

Registro de la primera página, con dos datos fuera de rango:

```
Opcion: 1

PAGINA 1
  Prueba 1: 1.5
  Prueba 2: 75
  ERROR! El dato debe estar entre 0 y 60 s
  Prueba 2: -2
  ERROR! El dato debe estar entre 0 y 60 s
  Prueba 2: 2
  Prueba 3: 1.8
  Prueba 4: 2.2
  Prueba 5: 2.5

Promedio: 2 s -> Rapida
```

Después de registrar las 5 páginas de los casos de prueba:

```
Opcion: 2

REPORTE GENERAL

Paginas registradas: 5
Rapida: 3 (60%)
Lenta: 2 (40%)
Promedio de tiempo de carga del sitio: 2.64 s
```

```
Opcion: 3

TABLA DE TIEMPOS

              P1    P2    P3    P4    P5   Promedio
Pagina 1     1.5     2   1.8   2.2   2.5          2   Rapida
Pagina 2     3.5     4   2.8   5.2   4.5          4   Lenta
Pagina 3       3     3     3     3     3          3   Rapida
Pagina 4     2.5   3.5     3     4     3        3.2   Lenta
Pagina 5     0.5     1   0.8   1.2   1.5          1   Rapida
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay páginas registradas |
| 2 | Registro de la página 1 | Página 1: 1.5, 2, 1.8, 2.2, 2.5 | Promedio 2 → Rapida |
| 3 | Registro de la página 2 | Página 2: 3.5, 4, 2.8, 5.2, 4.5 | Promedio 4 → Lenta |
| 4 | Justo en el límite | Página 3: 3, 3, 3, 3, 3 | Promedio 3 → **Rapida** |
| 5 | Registro de la página 4 | Página 4: 2.5, 3.5, 3, 4, 3 | Promedio 3.2 → Lenta |
| 6 | Registro de la página 5 | Página 5: 0.5, 1, 0.8, 1.2, 1.5 | Promedio 1 → Rapida |
| 7 | Reporte general | Opción 2 después de los casos 2 a 6 | Total 5; Rapida: 3 (60%); Lenta: 2 (40%); Promedio de tiempo de carga del sitio: 2.64 s |
| 8 | Tabla | Opción 3 después de los casos 2 a 6 | 5 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 9 | Dato fuera de rango | Un dato de 75 o de -2 | Error; vuelve a pedir el dato de esa misma prueba |
| 10 | Registro lleno | Opción 1 con 7 páginas ya registradas | Aviso de registro lleno; no pide datos |
| 11 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
