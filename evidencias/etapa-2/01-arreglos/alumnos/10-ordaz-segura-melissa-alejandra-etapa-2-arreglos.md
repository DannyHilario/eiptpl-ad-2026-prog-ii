# Evidencia 2.2 — Turbidez del agua por punto de muestreo

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 10 — Ordaz Segura Melissa Alejandra

## Historia de usuario

**Como** químico de una planta potabilizadora, **quiero** registrar la turbidez de 4 muestras de agua por punto de muestreo y consultar qué puntos no son aptos, **para** saber en qué zonas de la red hay que revisar los filtros.

## Contexto

En la Evidencia 1 tu programa revisaba el pH de cada muestra en el momento y lo olvidaba. Además del pH, la planta mide la **turbidez** del agua (qué tan turbia está, en NTU): entre más baja, más limpia. Ahora hay que **guardar** 4 muestras de cada punto de la red y decidir con su promedio.

Los datos forman una tabla:

|  | Muestra 1 | Muestra 2 | Muestra 3 | Muestra 4 |
|---|---|---|---|---|
| **Punto de muestreo 1** | 1.2 | 0.8 | 2 | 1 |
| **Punto de muestreo 2** | 7.5 | 6 | 9 | 5.5 |
| ... | | | | |

**Reglas**

- La planta revisa como máximo **5 puntos de muestreo**.
- De cada punto se toman **4 muestras** al día.
- Una muestra es válida si su turbidez está entre **0 y 100 NTU**.
- El agua de un punto es **apta** si el **promedio** de sus 4 muestras es **menor o igual a 5 NTU**; si no, **no es apta**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
CALIDAD DEL AGUA

1.- Registrar un punto de muestreo
2.- Reporte general
3.- Tabla de muestras
4.- Salir
```

- **Opción 1:** pide los datos de las 4 muestras del siguiente punto de muestreo y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  puntos de muestreo registrados, cuántos quedan como *Agua apta* y cuántos como *Agua no apta*
  (con sus porcentajes), y el promedio de turbidez de la red.
- **Opción 3:** muestra la tabla de todos los puntos de muestreo registrados: una
  fila por punto de muestreo, con sus 4 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan puntos de muestreo.** El programa no permite eliminar ni modificar
un punto de muestreo ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 5.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `muestras`** guarda lo que el usuario **captura**: los 4 datos de
  cada punto de muestreo.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  punto de muestreo.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del punto de muestreo 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del punto de muestreo 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos puntos de muestreo:

```
                   muestras                     promedios
             [0]    [1]    [2]    [3]
fila 0       1.2    0.8      2      1     →     [0]  1.25
fila 1       7.5      6      9    5.5     →     [1]  7
fila 2   (vacía)                                [2]  (vacío)
 ...
fila 4   (vacía)                                [4]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 4 datos del siguiente punto de muestreo en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 4 datos y se divide entre 4, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos puntos de muestreo
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
      5 × 4: cada fila es un punto de muestreo y cada columna una muestra.
- [ ] El promedio de cada punto de muestreo se guarda en un **vector** `double` de 5
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos puntos de muestreo se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de puntos de muestreo (5), los datos por punto de muestreo (4), los
      límites de un dato válido (0 y 100) y el límite de
      la clasificación (5) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los puntos de muestreo registrados**, no las
      5 filas de la matriz.
- [ ] Si ya hay 5 puntos de muestreo registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay puntos de muestreo registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** muestra (no se salta a
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

Registro del primer punto de muestreo, con dos datos fuera de rango:

```
Opcion: 1

PUNTO DE MUESTREO 1
  Muestra 1: 1.2
  Muestra 2: 120
  ERROR! El dato debe estar entre 0 y 100 NTU
  Muestra 2: -0.5
  ERROR! El dato debe estar entre 0 y 100 NTU
  Muestra 2: 0.8
  Muestra 3: 2
  Muestra 4: 1

Promedio: 1.25 NTU -> Agua apta
```

Después de registrar los 3 puntos de muestreo de los casos de prueba:

```
Opcion: 2

REPORTE GENERAL

Puntos de muestreo registrados: 3
Agua apta: 2 (66.67%)
Agua no apta: 1 (33.33%)
Promedio de turbidez de la red: 4.42 NTU
```

```
Opcion: 3

TABLA DE MUESTRAS

                         M1    M2    M3    M4   Promedio
Punto de muestreo 1     1.2   0.8     2     1       1.25   Agua apta
Punto de muestreo 2     7.5     6     9   5.5          7   Agua no apta
Punto de muestreo 3       5     5     5     5          5   Agua apta
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay puntos de muestreo registrados |
| 2 | Registro del punto de muestreo 1 | Punto de muestreo 1: 1.2, 0.8, 2, 1 | Promedio 1.25 → Agua apta |
| 3 | Registro del punto de muestreo 2 | Punto de muestreo 2: 7.5, 6, 9, 5.5 | Promedio 7 → Agua no apta |
| 4 | Justo en el límite | Punto de muestreo 3: 5, 5, 5, 5 | Promedio 5 → **Agua apta** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Agua apta: 2 (66.67%); Agua no apta: 1 (33.33%); Promedio de turbidez de la red: 4.42 NTU |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Dato fuera de rango | Un dato de 120 o de -0.5 | Error; vuelve a pedir el dato de esa misma muestra |
| 8 | Registro lleno | Opción 1 con 5 puntos de muestreo ya registrados | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
