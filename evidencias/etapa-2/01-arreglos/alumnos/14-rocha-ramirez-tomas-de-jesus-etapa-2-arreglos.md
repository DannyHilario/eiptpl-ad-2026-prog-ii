# Evidencia 2.2 — Nivel de tanques de gas LP

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 14 — Rocha Ramirez Tomas De Jesus

## Historia de usuario

**Como** programador de rutas de una empresa de gas LP, **quiero** registrar 3 lecturas del sensor de cada tanque durante el día y consultar cuáles tienen nivel bajo, **para** programar las pipas solo a los clientes que de verdad lo necesitan.

## Contexto

En la Evidencia 1 tu programa clasificaba **una sola** lectura de nivel por tanque y la olvidaba. Pero el sensor a veces falla, así que ahora cada tanque se lee **3 veces** al día (mañana, tarde y noche) y se decide con el promedio. Para eso hay que **guardar** las lecturas.

Los datos forman una tabla:

|  | Lectura 1 | Lectura 2 | Lectura 3 |
|---|---|---|---|
| **Tanque 1** | 45 | 44 | 46 |
| **Tanque 2** | 12 | 10 | 11 |
| ... | | | |

**Reglas**

- Se revisan como máximo **8 tanques**.
- Cada tanque se lee **3 veces** al día.
- Una lectura es válida si está entre **0 y 100%**.
- Un tanque tiene **nivel normal** si el **promedio** de sus 3 lecturas es **mayor o igual a 15%**; si no, tiene **nivel bajo** y hay que reabastecerlo.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
NIVEL DE TANQUES DE GAS

1.- Registrar un tanque
2.- Reporte general
3.- Tabla de niveles
4.- Salir
```

- **Opción 1:** pide los datos de las 3 lecturas del siguiente tanque y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  tanques registrados, cuántos quedan como *Nivel normal* y cuántos como *Nivel bajo*
  (con sus porcentajes), y el promedio de nivel de los tanques.
- **Opción 3:** muestra la tabla de todos los tanques registrados: una
  fila por tanque, con sus 3 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan tanques.** El programa no permite eliminar ni modificar
un tanque ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 8.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `niveles`** guarda lo que el usuario **captura**: los 3 datos de
  cada tanque.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  tanque.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del tanque 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del tanque 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos tanques:

```
                niveles                  promedios
             [0]    [1]    [2]
fila 0        45     44     46     →     [0]  45
fila 1        12     10     11     →     [1]  11
fila 2   (vacía)                         [2]  (vacío)
 ...
fila 7   (vacía)                         [7]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 3 datos del siguiente tanque en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 3 datos y se divide entre 3, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos tanques
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
      8 × 3: cada fila es un tanque y cada columna una lectura.
- [ ] El promedio de cada tanque se guarda en un **vector** `double` de 8
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos tanques se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de tanques (8), los datos por tanque (3), los
      límites de un dato válido (0 y 100) y el límite de
      la clasificación (15) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los tanques registrados**, no las
      8 filas de la matriz.
- [ ] Si ya hay 8 tanques registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay tanques registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra un
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
      8:40 p.m.**
- [ ] El archivo es de texto plano, con el nombre `EV2.2_ApellidoNombre.txt`.
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu
      código si se te pregunta.

## Ejemplo de ejecución

```
Opcion: 1

TANQUE 1
  Lectura 1: 45
  Lectura 2: 110
  ERROR! El dato debe estar entre 0 y 100%
  Lectura 2: -4
  ERROR! El dato debe estar entre 0 y 100%
  Lectura 2: 44
  Lectura 3: 46

Promedio: 45% -> Nivel normal
```

```
Opcion: 3

TABLA DE NIVELES

              L1    L2    L3   Promedio
Tanque 1      45    44    46         45   Nivel normal
Tanque 2      12    10    11         11   Nivel bajo
Tanque 3      15    15    15         15   Nivel normal
Tanque 4      14    16    14      14.67   Nivel bajo
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay tanques registrados |
| 2 | Registro del tanque 1 | Tanque 1: 45, 44, 46 | Promedio 45 → Nivel normal |
| 3 | Registro del tanque 2 | Tanque 2: 12, 10, 11 | Promedio 11 → Nivel bajo |
| 4 | Justo en el límite | Tanque 3: 15, 15, 15 | Promedio 15 → **Nivel normal** |
| 5 | Registro del tanque 4 | Tanque 4: 14, 16, 14 | Promedio 14.67 → Nivel bajo |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; Nivel normal: 2 (50%); Nivel bajo: 2 (50%); Promedio de nivel de los tanques: 21.42% |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Dato fuera de rango | Un dato de 110 o de -4 | Error; vuelve a pedir el dato de esa misma lectura |
| 9 | Registro lleno | Opción 1 con 8 tanques ya registrados | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
