# Evidencia 2.2 — Encuesta de satisfacción por cliente

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 08 — Martinez Rincon Vika Ludivina

## Historia de usuario

**Como** gerente de un restaurante, **quiero** registrar las respuestas de cada cliente a las 5 preguntas de la encuesta y consultar cuántos quedaron satisfechos, **para** saber si el servicio está mejorando.

## Contexto

En la Evidencia 1 cada encuesta era **una sola** calificación, que tu programa clasificaba en el momento y olvidaba. Ahora la encuesta tiene **5 preguntas** (comida, rapidez, atención, limpieza y precio), así que hay que **guardar** las 5 respuestas de cada cliente y decidir con su promedio.

Los datos forman una tabla:

|  | Pregunta 1 | Pregunta 2 | Pregunta 3 | Pregunta 4 | Pregunta 5 |
|---|---|---|---|---|---|
| **Cliente 1** | 9 | 10 | 8 | 9 | 9 |
| **Cliente 2** | 6 | 7 | 5 | 8 | 6 |
| ... | | | | | |

**Reglas**

- Se capturan como máximo **8 clientes** por turno.
- Cada cliente responde **5 preguntas**.
- Una respuesta es válida si está entre **1 y 10**.
- Un cliente quedó **satisfecho** si el **promedio** de sus 5 respuestas es **mayor o igual a 8**; si no, quedó **insatisfecho**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
ENCUESTA DE SATISFACCION

1.- Registrar un cliente
2.- Reporte general
3.- Tabla de respuestas
4.- Salir
```

- **Opción 1:** pide los datos de las 5 preguntas del siguiente cliente y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  clientes registrados, cuántos quedan como *Satisfecho* y cuántos como *Insatisfecho*
  (con sus porcentajes), y el promedio de calificación del restaurante.
- **Opción 3:** muestra la tabla de todos los clientes registrados: una
  fila por cliente, con sus 5 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan clientes.** El programa no permite eliminar ni modificar
un cliente ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 8.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `respuestas`** guarda lo que el usuario **captura**: los 5 datos de
  cada cliente.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  cliente.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del cliente 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del cliente 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos clientes:

```
                      respuestas                       promedios
             [0]    [1]    [2]    [3]    [4]
fila 0         9     10      8      9      9     →     [0]  9
fila 1         6      7      5      8      6     →     [1]  6.4
fila 2   (vacía)                                       [2]  (vacío)
 ...
fila 7   (vacía)                                       [7]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 5 datos del siguiente cliente en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 5 datos y se divide entre 5, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos clientes
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
      8 × 5: cada fila es un cliente y cada columna una pregunta.
- [ ] El promedio de cada cliente se guarda en un **vector** `double` de 8
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos clientes se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de clientes (8), los datos por cliente (5), los
      límites de un dato válido (1 y 10) y el límite de
      la clasificación (8) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los clientes registrados**, no las
      8 filas de la matriz.
- [ ] Si ya hay 8 clientes registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay clientes registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 1 y 10; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** pregunta (no se salta a
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

CLIENTE 1
  Pregunta 1: 9
  Pregunta 2: 11
  ERROR! El dato debe estar entre 1 y 10
  Pregunta 2: 0
  ERROR! El dato debe estar entre 1 y 10
  Pregunta 2: 10
  Pregunta 3: 8
  Pregunta 4: 9
  Pregunta 5: 9

Promedio: 9 -> Satisfecho
```

```
Opcion: 3

TABLA DE RESPUESTAS

               P1    P2    P3    P4    P5   Promedio
Cliente 1       9    10     8     9     9          9   Satisfecho
Cliente 2       6     7     5     8     6        6.4   Insatisfecho
Cliente 3       8     8     8     8     8          8   Satisfecho
Cliente 4      10     9     7     6     7        7.8   Insatisfecho
Cliente 5      10    10     9    10    10        9.8   Satisfecho
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay clientes registrados |
| 2 | Registro del cliente 1 | Cliente 1: 9, 10, 8, 9, 9 | Promedio 9 → Satisfecho |
| 3 | Registro del cliente 2 | Cliente 2: 6, 7, 5, 8, 6 | Promedio 6.4 → Insatisfecho |
| 4 | Justo en el límite | Cliente 3: 8, 8, 8, 8, 8 | Promedio 8 → **Satisfecho** |
| 5 | Registro del cliente 4 | Cliente 4: 10, 9, 7, 6, 7 | Promedio 7.8 → Insatisfecho |
| 6 | Registro del cliente 5 | Cliente 5: 10, 10, 9, 10, 10 | Promedio 9.8 → Satisfecho |
| 7 | Reporte general | Opción 2 después de los casos 2 a 6 | Total 5; Satisfecho: 3 (60%); Insatisfecho: 2 (40%); Promedio de calificación del restaurante: 8.2 |
| 8 | Tabla | Opción 3 después de los casos 2 a 6 | 5 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 9 | Dato fuera de rango | Un dato de 11 o de 0 | Error; vuelve a pedir el dato de esa misma pregunta |
| 10 | Registro lleno | Opción 1 con 8 clientes ya registrados | Aviso de registro lleno; no pide datos |
| 11 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
