# Evidencia 2.2 — Radares de velocidad en un tramo

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 04 — Hernández Hernández Luis Ernesto

## Historia de usuario

**Como** agente de tránsito de una carretera, **quiero** registrar la velocidad que cada uno de los 3 radares del tramo le mide a un vehículo y consultar cuáles van en exceso de velocidad, **para** multar con base en todo el tramo y no en un solo punto.

## Contexto

En la Evidencia 1 tu programa clasificaba la velocidad de cada vehículo con **un solo** radar y la olvidaba. Ahora el tramo tiene **3 radares**, y la multa se decide con el promedio de las 3 velocidades medidas. Para eso hay que **guardar** las lecturas.

Los datos forman una tabla:

|  | Radar 1 | Radar 2 | Radar 3 |
|---|---|---|---|
| **Vehículo 1** | 72 | 78 | 75 |
| **Vehículo 2** | 95 | 102 | 88 |
| ... | | | |

**Reglas**

- Se registran como máximo **6 vehículos**.
- Cada vehículo pasa por **3 radares** a lo largo del tramo.
- Una velocidad es válida si está entre **0 y 250 km/h**.
- Un vehículo va **dentro del límite** si el **promedio** de sus 3 velocidades es **menor o igual a 80 km/h**; si no, va **en exceso de velocidad**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
RADARES DEL TRAMO CARRETERO

1.- Registrar un vehiculo
2.- Reporte general
3.- Tabla de velocidades
4.- Salir
```

- **Opción 1:** pide los datos de los 3 radares del siguiente vehículo y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  vehículos registrados, cuántos quedan como *Dentro del limite* y cuántos como *Exceso de velocidad*
  (con sus porcentajes), y el promedio de velocidad de los vehículos.
- **Opción 3:** muestra la tabla de todos los vehículos registrados: una
  fila por vehículo, con sus 3 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan vehículos.** El programa no permite eliminar ni modificar
un vehículo ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 6.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `velocidades`** guarda lo que el usuario **captura**: los 3 datos de
  cada vehículo.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  vehículo.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del vehículo 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del vehículo 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos vehículos:

```
              velocidades                promedios
             [0]    [1]    [2]
fila 0        72     78     75     →     [0]  75
fila 1        95    102     88     →     [1]  95
fila 2   (vacía)                         [2]  (vacío)
 ...
fila 5   (vacía)                         [5]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 3 datos del siguiente vehículo en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 3 datos y se divide entre 3, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos vehículos
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
      6 × 3: cada fila es un vehículo y cada columna un radar.
- [ ] El promedio de cada vehículo se guarda en un **vector** `double` de 6
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos vehículos se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de vehículos (6), los datos por vehículo (3), los
      límites de un dato válido (0 y 250) y el límite de
      la clasificación (80) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los vehículos registrados**, no las
      6 filas de la matriz.
- [ ] Si ya hay 6 vehículos registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay vehículos registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 250; si no, muestra un
      error y vuelve a pedir el dato de **ese mismo** radar (no se salta a
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

Registro del primer vehículo, con dos datos fuera de rango:

```
Opcion: 1

VEHICULO 1
  Radar 1: 72
  Radar 2: 300
  ERROR! El dato debe estar entre 0 y 250 km/h
  Radar 2: -10
  ERROR! El dato debe estar entre 0 y 250 km/h
  Radar 2: 78
  Radar 3: 75

Promedio: 75 km/h -> Dentro del limite
```

Después de registrar los 4 vehículos de los casos de prueba:

```
Opcion: 2

REPORTE GENERAL

Vehiculos registrados: 4
Dentro del limite: 2 (50%)
Exceso de velocidad: 2 (50%)
Promedio de velocidad de los vehiculos: 83 km/h
```

```
Opcion: 3

TABLA DE VELOCIDADES

                R1    R2    R3   Promedio
Vehiculo 1      72    78    75         75   Dentro del limite
Vehiculo 2      95   102    88         95   Exceso de velocidad
Vehiculo 3      80    80    80         80   Dentro del limite
Vehiculo 4      85    79    82         82   Exceso de velocidad
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay vehículos registrados |
| 2 | Registro del vehículo 1 | Vehículo 1: 72, 78, 75 | Promedio 75 → Dentro del limite |
| 3 | Registro del vehículo 2 | Vehículo 2: 95, 102, 88 | Promedio 95 → Exceso de velocidad |
| 4 | Justo en el límite | Vehículo 3: 80, 80, 80 | Promedio 80 → **Dentro del limite** |
| 5 | Registro del vehículo 4 | Vehículo 4: 85, 79, 82 | Promedio 82 → Exceso de velocidad |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; Dentro del limite: 2 (50%); Exceso de velocidad: 2 (50%); Promedio de velocidad de los vehículos: 83 km/h |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Dato fuera de rango | Un dato de 300 o de -10 | Error; vuelve a pedir el dato de ese mismo radar |
| 9 | Registro lleno | Opción 1 con 6 vehículos ya registrados | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
