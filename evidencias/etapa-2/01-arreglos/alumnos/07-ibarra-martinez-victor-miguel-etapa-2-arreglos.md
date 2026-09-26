# Evidencia 2.2 — Monitoreo de ruido industrial

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 07 — Ibarra Martinez Victor Miguel

## Historia de usuario

**Como** supervisor de seguridad de una planta industrial, **quiero** registrar varias lecturas de ruido de cada máquina durante el día y consultar cuáles superan la norma, **para** decidir a qué máquinas darles mantenimiento primero.

## Contexto

En la Evidencia 1 tu programa clasificaba cada lectura de ruido en el momento y la olvidaba. Ahora la planta necesita **guardar** las lecturas para poder consultarlas después: cada máquina se mide 4 veces al día.

Los datos forman una tabla:

|  | Lectura 1 | Lectura 2 | Lectura 3 | Lectura 4 |
|---|---|---|---|---|
| **Máquina 1** | 82 | 88 | 79 | 85 |
| **Máquina 2** | 90 | 92 | 87 | 95 |
| ... | | | | |

**Reglas**

- La planta tiene como máximo **6 máquinas**.
- Cada máquina se mide **4 veces** al día.
- Una lectura es válida si está entre **0 y 140 dB**.
- Una máquina está **dentro de la norma** si el **promedio** de sus 4 lecturas es **menor o igual a 85 dB**; si no, **excede la norma**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
MONITOREO DE RUIDO INDUSTRIAL

1.- Registrar una maquina
2.- Reporte general
3.- Tabla de lecturas
4.- Salir
```

- **Opción 1:** pide los datos de las 4 lecturas de la siguiente máquina y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  máquinas registradas, cuántas quedan como *Dentro de la norma* y cuántas como *Excede la norma*
  (con sus porcentajes), y el promedio general de ruido de la planta.
- **Opción 3:** muestra la tabla de todas las máquinas registradas: una
  fila por máquina, con sus 4 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan máquinas.** El programa no permite eliminar ni modificar
una máquina ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 6.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `lecturas`** guarda lo que el usuario **captura**: los 4 datos de
  cada máquina.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  máquina.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la máquina 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la máquina 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos máquinas:

```
                   lecturas                     promedios
             [0]    [1]    [2]    [3]
fila 0        82     88     79     85     →     [0]  83.5
fila 1        90     92     87     95     →     [1]  91
fila 2   (vacía)                                [2]  (vacío)
 ...
fila 5   (vacía)                                [5]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 4 datos de la siguiente máquina en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 4 datos y se divide entre 4, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas máquinas
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
      6 × 4: cada fila es una máquina y cada columna una lectura.
- [ ] El promedio de cada máquina se guarda en un **vector** `double` de 6
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas máquinas se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de máquinas (6), los datos por máquina (4), los
      límites de un dato válido (0 y 140) y el límite de
      la clasificación (85) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las máquinas registradas**, no las
      6 filas de la matriz.
- [ ] Si ya hay 6 máquinas registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay máquinas registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 140; si no, muestra un
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
  Lectura 1: 82
  Lectura 2: 150
  ERROR! El dato debe estar entre 0 y 140 dB
  Lectura 2: -5
  ERROR! El dato debe estar entre 0 y 140 dB
  Lectura 2: 88
  Lectura 3: 79
  Lectura 4: 85

Promedio: 83.5 dB -> Dentro de la norma
```

Después de registrar las 3 máquinas de los casos de prueba:

```
Opcion: 2

REPORTE GENERAL

Maquinas registradas: 3
Dentro de la norma: 2 (66.67%)
Excede la norma: 1 (33.33%)
Promedio general de ruido de la planta: 86.5 dB
```

```
Opcion: 3

TABLA DE LECTURAS

               L1    L2    L3    L4   Promedio
Maquina 1      82    88    79    85       83.5   Dentro de la norma
Maquina 2      90    92    87    95         91   Excede la norma
Maquina 3      85    85    85    85         85   Dentro de la norma
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay máquinas registradas |
| 2 | Registro de la máquina 1 | Máquina 1: 82, 88, 79, 85 | Promedio 83.5 → Dentro de la norma |
| 3 | Registro de la máquina 2 | Máquina 2: 90, 92, 87, 95 | Promedio 91 → Excede la norma |
| 4 | Justo en el límite | Máquina 3: 85, 85, 85, 85 | Promedio 85 → **Dentro de la norma** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Dentro de la norma: 2 (66.67%); Excede la norma: 1 (33.33%); Promedio general de ruido de la planta: 86.5 dB |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Dato fuera de rango | Un dato de 150 o de -5 | Error; vuelve a pedir el dato de esa misma lectura |
| 8 | Registro lleno | Opción 1 con 6 máquinas ya registradas | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
