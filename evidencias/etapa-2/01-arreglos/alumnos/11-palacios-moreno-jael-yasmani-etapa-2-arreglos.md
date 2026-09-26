# Evidencia 2.2 — Tiempos de atención de soporte técnico

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 11 — Palacios Moreno Jael Yasmani

## Historia de usuario

**Como** coordinador de un centro de soporte técnico, **quiero** registrar cuántas horas tardó cada técnico en resolver sus últimos 5 tickets y consultar quiénes están fuera de SLA, **para** repartir mejor la carga de trabajo.

## Contexto

En la Evidencia 1 tu programa clasificaba cada ticket en el momento y lo olvidaba. Ahora la coordinación quiere evaluar a cada **técnico**, así que hay que **guardar** el tiempo de sus últimos 5 tickets y decidir con su promedio.

Los datos forman una tabla:

|  | Ticket 1 | Ticket 2 | Ticket 3 | Ticket 4 | Ticket 5 |
|---|---|---|---|---|---|
| **Técnico 1** | 4 | 12.5 | 8 | 20 | 3.5 |
| **Técnico 2** | 30 | 26 | 48 | 12 | 19 |
| ... | | | | | |

**Reglas**

- El centro tiene como máximo **6 técnicos**.
- De cada técnico se registran las horas de sus últimos **5 tickets**.
- Un tiempo es válido si está entre **0 y 168 horas** (una semana).
- Un técnico está **dentro de SLA** si el **promedio** de sus 5 tickets es **menor o igual a 24 horas**; si no, está **fuera de SLA**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
SOPORTE TECNICO

1.- Registrar un tecnico
2.- Reporte general
3.- Tabla de horas
4.- Salir
```

- **Opción 1:** pide los datos de los 5 tickets del siguiente técnico y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  técnicos registrados, cuántos quedan como *Dentro de SLA* y cuántos como *Fuera de SLA*
  (con sus porcentajes), y el promedio de tiempo de resolución del equipo.
- **Opción 3:** muestra la tabla de todos los técnicos registrados: una
  fila por técnico, con sus 5 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan técnicos.** El programa no permite eliminar ni modificar
un técnico ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 6.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `horas`** guarda lo que el usuario **captura**: los 5 datos de
  cada técnico.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  técnico.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del técnico 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del técnico 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos técnicos:

```
                        horas                          promedios
             [0]    [1]    [2]    [3]    [4]
fila 0         4   12.5      8     20    3.5     →     [0]  9.6
fila 1        30     26     48     12     19     →     [1]  27
fila 2   (vacía)                                       [2]  (vacío)
 ...
fila 5   (vacía)                                       [5]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 5 datos del siguiente técnico en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 5 datos y se divide entre 5, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos técnicos
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
      6 × 5: cada fila es un técnico y cada columna un ticket.
- [ ] El promedio de cada técnico se guarda en un **vector** `double` de 6
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos técnicos se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de técnicos (6), los datos por técnico (5), los
      límites de un dato válido (0 y 168) y el límite de
      la clasificación (24) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los técnicos registrados**, no las
      6 filas de la matriz.
- [ ] Si ya hay 6 técnicos registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay técnicos registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 168; si no, muestra un
      error y vuelve a pedir el dato de **ese mismo** ticket (no se salta a
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

TECNICO 1
  Ticket 1: 4
  Ticket 2: 200
  ERROR! El dato debe estar entre 0 y 168 horas
  Ticket 2: -1
  ERROR! El dato debe estar entre 0 y 168 horas
  Ticket 2: 12.5
  Ticket 3: 8
  Ticket 4: 20
  Ticket 5: 3.5

Promedio: 9.6 horas -> Dentro de SLA
```

```
Opcion: 3

TABLA DE HORAS

               T1    T2    T3    T4    T5   Promedio
Tecnico 1       4  12.5     8    20   3.5        9.6   Dentro de SLA
Tecnico 2      30    26    48    12    19         27   Fuera de SLA
Tecnico 3      24    24    24    24    24         24   Dentro de SLA
Tecnico 4      36    20    30    28    16         26   Fuera de SLA
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay técnicos registrados |
| 2 | Registro del técnico 1 | Técnico 1: 4, 12.5, 8, 20, 3.5 | Promedio 9.6 → Dentro de SLA |
| 3 | Registro del técnico 2 | Técnico 2: 30, 26, 48, 12, 19 | Promedio 27 → Fuera de SLA |
| 4 | Justo en el límite | Técnico 3: 24, 24, 24, 24, 24 | Promedio 24 → **Dentro de SLA** |
| 5 | Registro del técnico 4 | Técnico 4: 36, 20, 30, 28, 16 | Promedio 26 → Fuera de SLA |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; Dentro de SLA: 2 (50%); Fuera de SLA: 2 (50%); Promedio de tiempo de resolución del equipo: 21.65 horas |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Dato fuera de rango | Un dato de 200 o de -1 | Error; vuelve a pedir el dato de ese mismo ticket |
| 9 | Registro lleno | Opción 1 con 6 técnicos ya registrados | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
