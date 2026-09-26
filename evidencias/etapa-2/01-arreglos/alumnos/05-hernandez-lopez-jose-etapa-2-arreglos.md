# Evidencia 2.2 — Consumo eléctrico mensual por semanas

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 05 — Hernandez Lopez Jose

## Historia de usuario

**Como** revisor de una compañía de luz, **quiero** registrar el consumo de cada casa en las 4 semanas del mes y consultar cuáles tienen alto consumo, **para** avisarles a tiempo a los clientes que podrían pagar una tarifa más cara.

## Contexto

En la Evidencia 1 tu programa clasificaba el consumo mensual de cada casa en el momento y lo olvidaba. Ahora el medidor reporta el consumo **por semana**, así que hay que **guardar** las 4 semanas de cada casa y sumarlas para obtener el consumo del mes.

Los datos forman una tabla:

|  | Semana 1 | Semana 2 | Semana 3 | Semana 4 |
|---|---|---|---|---|
| **Casa 1** | 60.5 | 72 | 58 | 65.5 |
| **Casa 2** | 90 | 85.5 | 110 | 95 |
| ... | | | | |

**Reglas**

- Se revisan como máximo **6 casas** de la colonia.
- De cada casa se registra el consumo de **4 semanas**.
- El consumo de una semana es válido si está entre **0 y 200 kWh**.
- Una casa tiene **consumo normal** si el **total** de sus 4 semanas es **menor o igual a 300 kWh**; si no, tiene **alto consumo**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
CONSUMO ELECTRICO DE LA COLONIA

1.- Registrar una casa
2.- Reporte general
3.- Tabla de consumos
4.- Salir
```

- **Opción 1:** pide los datos de las 4 semanas de la siguiente casa y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  casas registradas, cuántas quedan como *Consumo normal* y cuántas como *Alto consumo*
  (con sus porcentajes), y el promedio de consumo por casa.
- **Opción 3:** muestra la tabla de todas las casas registradas: una
  fila por casa, con sus 4 datos, su total y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan casas.** El programa no permite eliminar ni modificar
una casa ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 6.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `consumos`** guarda lo que el usuario **captura**: los 4 datos de
  cada casa.
- El **vector `totales`** guarda lo que el programa **calcula**: el total de cada
  casa.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la casa 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la casa 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos casas:

```
                   consumos                     totales
             [0]    [1]    [2]    [3]
fila 0      60.5     72     58   65.5     →     [0]  256
fila 1        90   85.5    110     95     →     [1]  380.5
fila 2   (vacía)                                [2]  (vacío)
 ...
fila 5   (vacía)                                [5]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 4 datos de la siguiente casa en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 4 datos, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el total?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas casas
quedan en cada clasificación, y la opción 3 imprime cada fila de la matriz con
su total al final.

**¿Por qué no guardar el total como una columna más de la matriz?** Porque
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
      6 × 4: cada fila es una casa y cada columna una semana.
- [ ] El total de cada casa se guarda en un **vector** `double` de 6
      posiciones: el total de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas casas se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de casas (6), los datos por casa (4), los
      límites de un dato válido (0 y 200) y el límite de
      la clasificación (300) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el total del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las casas registradas**, no las
      6 filas de la matriz.
- [ ] Si ya hay 6 casas registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay casas registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 200; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** semana (no se salta a
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

Registro de la primera casa, con dos datos fuera de rango:

```
Opcion: 1

CASA 1
  Semana 1: 60.5
  Semana 2: 250
  ERROR! El dato debe estar entre 0 y 200 kWh
  Semana 2: -5
  ERROR! El dato debe estar entre 0 y 200 kWh
  Semana 2: 72
  Semana 3: 58
  Semana 4: 65.5

Total: 256 kWh -> Consumo normal
```

Después de registrar las 3 casas de los casos de prueba:

```
Opcion: 2

REPORTE GENERAL

Casas registradas: 3
Consumo normal: 2 (66.67%)
Alto consumo: 1 (33.33%)
Promedio de consumo por casa: 312.17 kWh
```

```
Opcion: 3

TABLA DE CONSUMOS

            S1    S2    S3    S4   Total
Casa 1    60.5    72    58  65.5     256   Consumo normal
Casa 2      90  85.5   110    95   380.5   Alto consumo
Casa 3      75    75    75    75     300   Consumo normal
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay casas registradas |
| 2 | Registro de la casa 1 | Casa 1: 60.5, 72, 58, 65.5 | Total 256 → Consumo normal |
| 3 | Registro de la casa 2 | Casa 2: 90, 85.5, 110, 95 | Total 380.5 → Alto consumo |
| 4 | Justo en el límite | Casa 3: 75, 75, 75, 75 | Total 300 → **Consumo normal** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Consumo normal: 2 (66.67%); Alto consumo: 1 (33.33%); Promedio de consumo por casa: 312.17 kWh |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 7 | Dato fuera de rango | Un dato de 250 o de -5 | Error; vuelve a pedir el dato de esa misma semana |
| 8 | Registro lleno | Opción 1 con 6 casas ya registradas | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
