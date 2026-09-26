# Evidencia 2.2 — Monitoreo de CO2 en salones

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

## Historia de usuario

**Como** coordinador de mantenimiento de una escuela, **quiero** registrar 4 lecturas de CO2 de cada salón durante el día y consultar cuáles necesitan ventilarse, **para** decidir en qué salones instalar ventiladores primero.

## Contexto

En la Evidencia 1 tu programa clasificaba **una sola** lectura de CO2 por salón y la olvidaba. Pero el CO2 sube y baja durante el día, así que ahora a cada salón se le toman **4 lecturas** y se decide con el promedio. Para eso hay que **guardar** las lecturas.

Los datos forman una tabla:

|  | Lectura 1 | Lectura 2 | Lectura 3 | Lectura 4 |
|---|---|---|---|---|
| **Salón 1** | 650 | 720 | 800 | 830 |
| **Salón 2** | 1100 | 1250 | 980 | 1310 |
| ... | | | | |

**Reglas**

- Se revisan como máximo **8 salones**.
- A cada salón se le toman **4 lecturas** al día.
- Una lectura es válida si está entre **0 y 5000 ppm**.
- Un salón está en **nivel normal** si el **promedio** de sus 4 lecturas es **menor o igual a 1000 ppm**; si no, **necesita ventilación**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
MONITOREO DE CO2

1.- Registrar un salon
2.- Reporte general
3.- Tabla de lecturas
4.- Salir
```

- **Opción 1:** pide los datos de las 4 lecturas del siguiente salón y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  salones registrados, cuántos quedan como *Nivel normal* y cuántos como *Necesita ventilacion*
  (con sus porcentajes), y el promedio de CO2 de la escuela.
- **Opción 3:** muestra la tabla de todos los salones registrados: una
  fila por salón, con sus 4 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan salones.** El programa no permite eliminar ni modificar
un salón ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 8.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `lecturas`** guarda lo que el usuario **captura**: los 4 datos de
  cada salón.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  salón.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del salón 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del salón 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos salones:

```
                   lecturas                     promedios
             [0]    [1]    [2]    [3]
fila 0       650    720    800    830     →     [0]  750
fila 1      1100   1250    980   1310     →     [1]  1160
fila 2   (vacía)                                [2]  (vacío)
 ...
fila 7   (vacía)                                [7]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 4 datos del siguiente salón en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 4 datos y se divide entre 4, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos salones
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
      8 × 4: cada fila es un salón y cada columna una lectura.
- [ ] El promedio de cada salón se guarda en un **vector** `double` de 8
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos salones se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de salones (8), los datos por salón (4), los
      límites de un dato válido (0 y 5000) y el límite de
      la clasificación (1000) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los salones registrados**, no las
      8 filas de la matriz.
- [ ] Si ya hay 8 salones registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay salones registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 5000; si no, muestra un
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

```
Opcion: 1

SALON 1
  Lectura 1: 650
  Lectura 2: 5200
  ERROR! El dato debe estar entre 0 y 5000 ppm
  Lectura 2: -10
  ERROR! El dato debe estar entre 0 y 5000 ppm
  Lectura 2: 720
  Lectura 3: 800
  Lectura 4: 830

Promedio: 750 ppm -> Nivel normal
```

```
Opcion: 3

TABLA DE LECTURAS

             L1    L2    L3    L4   Promedio
Salon 1     650   720   800   830        750   Nivel normal
Salon 2    1100  1250   980  1310       1160   Necesita ventilacion
Salon 3    1000  1000  1000  1000       1000   Nivel normal
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay salones registrados |
| 2 | Registro del salón 1 | Salón 1: 650, 720, 800, 830 | Promedio 750 → Nivel normal |
| 3 | Registro del salón 2 | Salón 2: 1100, 1250, 980, 1310 | Promedio 1160 → Necesita ventilacion |
| 4 | Justo en el límite | Salón 3: 1000, 1000, 1000, 1000 | Promedio 1000 → **Nivel normal** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Nivel normal: 2 (66.67%); Necesita ventilacion: 1 (33.33%); Promedio de CO2 de la escuela: 970 ppm |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Dato fuera de rango | Un dato de 5200 o de -10 | Error; vuelve a pedir el dato de esa misma lectura |
| 8 | Registro lleno | Opción 1 con 8 salones ya registrados | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
