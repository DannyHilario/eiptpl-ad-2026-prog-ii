# Evidencia 2.2 — Consumo de datos móviles por semana

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 18 — Salinas Meza Cesar Eduardo

## Historia de usuario

**Como** analista de una compañía telefónica, **quiero** registrar el consumo de datos de cada línea en las 4 semanas del mes y consultar cuáles exceden su plan de 5 GB, **para** ofrecerles un plan más grande a los clientes que lo necesitan.

## Contexto

En la Evidencia 1 tu programa clasificaba el consumo mensual de cada línea en el momento y lo olvidaba. Ahora el sistema reporta el consumo **por semana**, así que hay que **guardar** las 4 semanas de cada línea y sumarlas para obtener el consumo del mes.

Los datos forman una tabla:

|  | Semana 1 | Semana 2 | Semana 3 | Semana 4 |
|---|---|---|---|---|
| **Línea 1** | 0.75 | 1.25 | 1 | 0.5 |
| **Línea 2** | 2 | 1.5 | 1.25 | 1.75 |
| ... | | | | |

**Reglas**

- Se revisan como máximo **8 líneas**.
- De cada línea se registra el consumo de **4 semanas**.
- El consumo de una semana es válido si está entre **0 y 50 GB**.
- Una línea está **dentro del plan** si el **total** de sus 4 semanas es **menor o igual a 5 GB**; si no, **excede el plan**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
CONSUMO DE DATOS MOVILES

1.- Registrar una linea
2.- Reporte general
3.- Tabla de consumos
4.- Salir
```

- **Opción 1:** pide los datos de las 4 semanas de la siguiente línea y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  líneas registradas, cuántas quedan como *Dentro del plan* y cuántas como *Excede el plan*
  (con sus porcentajes), y el promedio de consumo por línea.
- **Opción 3:** muestra la tabla de todas las líneas registradas: una
  fila por línea, con sus 4 datos, su total y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan líneas.** El programa no permite eliminar ni modificar
una línea ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 8.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `consumos`** guarda lo que el usuario **captura**: los 4 datos de
  cada línea.
- El **vector `totales`** guarda lo que el programa **calcula**: el total de cada
  línea.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la línea 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la línea 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos líneas:

```
                   consumos                     totales
             [0]    [1]    [2]    [3]
fila 0      0.75   1.25      1    0.5     →     [0]  3.5
fila 1         2    1.5   1.25   1.75     →     [1]  6.5
fila 2   (vacía)                                [2]  (vacío)
 ...
fila 7   (vacía)                                [7]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 4 datos de la siguiente línea en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 4 datos, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el total?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas líneas
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
      8 × 4: cada fila es una línea y cada columna una semana.
- [ ] El total de cada línea se guarda en un **vector** `double` de 8
      posiciones: el total de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas líneas se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de líneas (8), los datos por línea (4), los
      límites de un dato válido (0 y 50) y el límite de
      la clasificación (5) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el total del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las líneas registradas**, no las
      8 filas de la matriz.
- [ ] Si ya hay 8 líneas registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay líneas registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 50; si no, muestra un
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
      8:40 p.m.**
- [ ] El archivo es de texto plano, con el nombre `EV2.2_ApellidoNombre.txt`.
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu
      código si se te pregunta.

## Ejemplo de ejecución

```
Opcion: 1

LINEA 1
  Semana 1: 0.75
  Semana 2: 60
  ERROR! El dato debe estar entre 0 y 50 GB
  Semana 2: -1
  ERROR! El dato debe estar entre 0 y 50 GB
  Semana 2: 1.25
  Semana 3: 1
  Semana 4: 0.5

Total: 3.5 GB -> Dentro del plan
```

```
Opcion: 3

TABLA DE CONSUMOS

             S1    S2    S3    S4   Total
Linea 1    0.75  1.25     1   0.5     3.5   Dentro del plan
Linea 2       2   1.5  1.25  1.75     6.5   Excede el plan
Linea 3    1.25  1.25  1.25  1.25       5   Dentro del plan
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay líneas registradas |
| 2 | Registro de la línea 1 | Línea 1: 0.75, 1.25, 1, 0.5 | Total 3.5 → Dentro del plan |
| 3 | Registro de la línea 2 | Línea 2: 2, 1.5, 1.25, 1.75 | Total 6.5 → Excede el plan |
| 4 | Justo en el límite | Línea 3: 1.25, 1.25, 1.25, 1.25 | Total 5 → **Dentro del plan** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Dentro del plan: 2 (66.67%); Excede el plan: 1 (33.33%); Promedio de consumo por línea: 5 GB |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 7 | Dato fuera de rango | Un dato de 60 o de -1 | Error; vuelve a pedir el dato de esa misma semana |
| 8 | Registro lleno | Opción 1 con 8 líneas ya registradas | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
