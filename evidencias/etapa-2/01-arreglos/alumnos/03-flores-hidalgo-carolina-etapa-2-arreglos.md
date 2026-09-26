# Evidencia 2.2 — Filtro de temperatura en un evento

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 03 — Flores Hidalgo Carolina

## Historia de usuario

**Como** encargado de la entrada de un concierto, **quiero** registrar tres tomas de temperatura de cada asistente y consultar quiénes no pueden pasar, **para** no rechazar a nadie por una sola lectura equivocada del termómetro.

## Contexto

En la Evidencia 1 tu programa decidía con **una sola** toma de temperatura por asistente y la olvidaba. Pero un termómetro puede fallar, así que ahora a cada asistente se le toma la temperatura **3 veces** y se decide con el promedio. Para eso hay que **guardar** las tomas.

Los datos forman una tabla:

|  | Toma 1 | Toma 2 | Toma 3 |
|---|---|---|---|
| **Asistente 1** | 36.5 | 36.7 | 36.6 |
| **Asistente 2** | 38.2 | 38.5 | 37.9 |
| ... | | | |

**Reglas**

- Se registran como máximo **8 asistentes** por fila de revisión.
- A cada asistente se le toma la temperatura **3 veces**.
- Una toma es válida si está entre **34 y 42 °C**.
- Un asistente **puede pasar** si el **promedio** de sus 3 tomas es **menor o igual a 37.5 °C**; si no, es **febril y no puede pasar**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
FILTRO DE ACCESO AL EVENTO

1.- Registrar un asistente
2.- Reporte general
3.- Tabla de temperaturas
4.- Salir
```

- **Opción 1:** pide los datos de las 3 tomas del siguiente asistente y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  asistentes registrados, cuántos quedan como *Puede pasar* y cuántos como *Febril, no puede pasar*
  (con sus porcentajes), y el promedio de temperatura de los asistentes.
- **Opción 3:** muestra la tabla de todos los asistentes registrados: una
  fila por asistente, con sus 3 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan asistentes.** El programa no permite eliminar ni modificar
un asistente ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 8.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `temperaturas`** guarda lo que el usuario **captura**: los 3 datos de
  cada asistente.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  asistente.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del asistente 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del asistente 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos asistentes:

```
              temperaturas               promedios
             [0]    [1]    [2]
fila 0      36.5   36.7   36.6     →     [0]  36.6
fila 1      38.2   38.5   37.9     →     [1]  38.2
fila 2   (vacía)                         [2]  (vacío)
 ...
fila 7   (vacía)                         [7]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 3 datos del siguiente asistente en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 3 datos y se divide entre 3, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos asistentes
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
      8 × 3: cada fila es un asistente y cada columna una toma.
- [ ] El promedio de cada asistente se guarda en un **vector** `double` de 8
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos asistentes se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de asistentes (8), los datos por asistente (3), los
      límites de un dato válido (34 y 42) y el límite de
      la clasificación (37.5) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los asistentes registrados**, no las
      8 filas de la matriz.
- [ ] Si ya hay 8 asistentes registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay asistentes registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 34 y 42; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** toma (no se salta a
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

ASISTENTE 1
  Toma 1: 36.5
  Toma 2: 45
  ERROR! El dato debe estar entre 34 y 42 °C
  Toma 2: 30
  ERROR! El dato debe estar entre 34 y 42 °C
  Toma 2: 36.7
  Toma 3: 36.6

Promedio: 36.6 °C -> Puede pasar
```

```
Opcion: 3

TABLA DE TEMPERATURAS

                 T1    T2    T3   Promedio
Asistente 1    36.5  36.7  36.6       36.6   Puede pasar
Asistente 2    38.2  38.5  37.9       38.2   Febril, no puede pasar
Asistente 3    37.5  37.5  37.5       37.5   Puede pasar
Asistente 4      37  37.5  38.5      37.67   Febril, no puede pasar
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay asistentes registrados |
| 2 | Registro del asistente 1 | Asistente 1: 36.5, 36.7, 36.6 | Promedio 36.6 → Puede pasar |
| 3 | Registro del asistente 2 | Asistente 2: 38.2, 38.5, 37.9 | Promedio 38.2 → Febril, no puede pasar |
| 4 | Justo en el límite | Asistente 3: 37.5, 37.5, 37.5 | Promedio 37.5 → **Puede pasar** |
| 5 | Registro del asistente 4 | Asistente 4: 37, 37.5, 38.5 | Promedio 37.67 → Febril, no puede pasar |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; Puede pasar: 2 (50%); Febril, no puede pasar: 2 (50%); Promedio de temperatura de los asistentes: 37.49 °C |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Dato fuera de rango | Un dato de 45 o de 30 | Error; vuelve a pedir el dato de esa misma toma |
| 9 | Registro lleno | Opción 1 con 8 asistentes ya registrados | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
