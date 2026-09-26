# Evidencia 2.2 — Vibración de maquinaria industrial

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 20 — Vazquez Palacios Angel Daniel

## Historia de usuario

**Como** jefe de mantenimiento de una planta industrial, **quiero** registrar 3 lecturas de vibración de cada máquina y consultar cuáles están en estado de alerta, **para** programar el mantenimiento antes de que una máquina falle.

## Contexto

En la Evidencia 1 tu programa clasificaba **una sola** lectura de vibración por máquina y la olvidaba. Ahora cada máquina se mide **3 veces** por turno y se decide con el promedio, así que hay que **guardar** las lecturas.

Los datos forman una tabla:

|  | Lectura 1 | Lectura 2 | Lectura 3 |
|---|---|---|---|
| **Máquina 1** | 2.5 | 3 | 2 |
| **Máquina 2** | 6 | 5.5 | 7 |
| ... | | | |

**Reglas**

- La planta tiene como máximo **7 máquinas** en monitoreo.
- Cada máquina se mide **3 veces** por turno.
- Una lectura es válida si está entre **0 y 50 mm/s**.
- Una máquina está en **estado normal** si el **promedio** de sus 3 lecturas es **menor o igual a 4.5 mm/s**; si no, está en **estado de alerta**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
MONITOREO DE VIBRACION

1.- Registrar una maquina
2.- Reporte general
3.- Tabla de vibraciones
4.- Salir
```

- **Opción 1:** pide los datos de las 3 lecturas de la siguiente máquina y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  máquinas registradas, cuántas quedan como *Estado normal* y cuántas como *Estado de alerta*
  (con sus porcentajes), y el promedio de vibración de la planta.
- **Opción 3:** muestra la tabla de todas las máquinas registradas: una
  fila por máquina, con sus 3 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan máquinas.** El programa no permite eliminar ni modificar
una máquina ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 7.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `vibraciones`** guarda lo que el usuario **captura**: los 3 datos de
  cada máquina.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  máquina.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la máquina 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la máquina 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos máquinas:

```
              vibraciones                promedios
             [0]    [1]    [2]
fila 0       2.5      3      2     →     [0]  2.5
fila 1         6    5.5      7     →     [1]  6.17
fila 2   (vacía)                         [2]  (vacío)
 ...
fila 6   (vacía)                         [6]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 3 datos de la siguiente máquina en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 3 datos y se divide entre 3, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas máquinas
quedan en cada clasificación, y la opción 3 imprime cada fila de la matriz con
su promedio al final.

**¿Por qué no guardar el promedio como una columna más de la matriz?** Porque
entonces la matriz tendría columnas de dos tipos: 3 que captura el usuario y 1
que calcula el programa. Tendrías que recordar que la columna `[3]` "no
cuenta" al capturar ni al sumar. Con dos arreglos separados, la matriz siempre
se recorre de la columna 0 a la 2, sin excepciones.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de
una sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de arreglos

- [ ] Los datos que captura el usuario se guardan en una **matriz** `double` de
      7 × 3: cada fila es una máquina y cada columna una lectura.
- [ ] El promedio de cada máquina se guarda en un **vector** `double` de 7
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas máquinas se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de máquinas (7), los datos por máquina (3), los
      límites de un dato válido (0 y 50) y el límite de
      la clasificación (4.5) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las máquinas registradas**, no las
      7 filas de la matriz.
- [ ] Si ya hay 7 máquinas registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay máquinas registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 50; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** lectura (no se salta a
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

Registro de la primera máquina, con dos datos fuera de rango:

```
Opcion: 1

MAQUINA 1
  Lectura 1: 2.5
  Lectura 2: 60
  ERROR! El dato debe estar entre 0 y 50 mm/s
  Lectura 2: -1
  ERROR! El dato debe estar entre 0 y 50 mm/s
  Lectura 2: 3
  Lectura 3: 2

Promedio: 2.5 mm/s -> Estado normal
```

Después de registrar las 4 máquinas de los casos de prueba:

```
Opcion: 2

REPORTE GENERAL

Maquinas registradas: 4
Estado normal: 2 (50%)
Estado de alerta: 2 (50%)
Promedio de vibracion de la planta: 4.54 mm/s
```

```
Opcion: 3

TABLA DE VIBRACIONES

               L1    L2    L3   Promedio
Maquina 1     2.5     3     2        2.5   Estado normal
Maquina 2       6   5.5     7       6.17   Estado de alerta
Maquina 3     4.5   4.5   4.5        4.5   Estado normal
Maquina 4       5     4     6          5   Estado de alerta
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay máquinas registradas |
| 2 | Registro de la máquina 1 | Máquina 1: 2.5, 3, 2 | Promedio 2.5 → Estado normal |
| 3 | Registro de la máquina 2 | Máquina 2: 6, 5.5, 7 | Promedio 6.17 → Estado de alerta |
| 4 | Justo en el límite | Máquina 3: 4.5, 4.5, 4.5 | Promedio 4.5 → **Estado normal** |
| 5 | Registro de la máquina 4 | Máquina 4: 5, 4, 6 | Promedio 5 → Estado de alerta |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; Estado normal: 2 (50%); Estado de alerta: 2 (50%); Promedio de vibración de la planta: 4.54 mm/s |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Dato fuera de rango | Un dato de 60 o de -1 | Error; vuelve a pedir el dato de esa misma lectura |
| 9 | Registro lleno | Opción 1 con 7 máquinas ya registradas | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
