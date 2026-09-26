# Evidencia 2.2 — Tiempos de entrega por repartidor

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

## Historia de usuario

**Como** gerente de operaciones de una empresa de paquetería, **quiero** registrar cuántos días tardó cada repartidor en entregar sus últimos 5 envíos y consultar quiénes entregan con retraso, **para** reforzar las rutas que no cumplen la promesa de entrega.

## Contexto

En la Evidencia 1 tu programa clasificaba cada envío en el momento y lo olvidaba. Ahora la empresa quiere evaluar a cada **repartidor**, así que hay que **guardar** los días de entrega de sus últimos 5 envíos y decidir con su promedio.

Los datos forman una tabla:

|  | Envío 1 | Envío 2 | Envío 3 | Envío 4 | Envío 5 |
|---|---|---|---|---|---|
| **Repartidor 1** | 2 | 1 | 3 | 2 | 2 |
| **Repartidor 2** | 4 | 5 | 3 | 6 | 2 |
| ... | | | | | |

**Reglas**

- La empresa tiene como máximo **6 repartidores**.
- De cada repartidor se registran los días de entrega de sus últimos **5 envíos**.
- Los días de entrega de un envío son válidos si están entre **0 y 30** (0 = se entregó el mismo día).
- Un repartidor entrega **a tiempo** si el **promedio** de sus 5 envíos es **menor o igual a 3 días**; si no, entrega **con retraso**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
ENTREGAS DE PAQUETERIA

1.- Registrar un repartidor
2.- Reporte general
3.- Tabla de dias de entrega
4.- Salir
```

- **Opción 1:** pide los datos de los 5 envíos del siguiente repartidor y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  repartidores registrados, cuántos quedan como *A tiempo* y cuántos como *Con retraso*
  (con sus porcentajes), y el promedio de días de entrega de la empresa.
- **Opción 3:** muestra la tabla de todos los repartidores registrados: una
  fila por repartidor, con sus 5 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan repartidores.** El programa no permite eliminar ni modificar
un repartidor ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 6.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `dias`** guarda lo que el usuario **captura**: los 5 datos de
  cada repartidor.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  repartidor.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del repartidor 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del repartidor 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos repartidores:

```
                         dias                          promedios
             [0]    [1]    [2]    [3]    [4]
fila 0         2      1      3      2      2     →     [0]  2
fila 1         4      5      3      6      2     →     [1]  4
fila 2   (vacía)                                       [2]  (vacío)
 ...
fila 5   (vacía)                                       [5]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 5 datos del siguiente repartidor en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 5 datos y se divide entre 5, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos repartidores
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
      6 × 5: cada fila es un repartidor y cada columna un envío.
- [ ] El promedio de cada repartidor se guarda en un **vector** `double` de 6
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos repartidores se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de repartidores (6), los datos por repartidor (5), los
      límites de un dato válido (0 y 30) y el límite de
      la clasificación (3) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los repartidores registrados**, no las
      6 filas de la matriz.
- [ ] Si ya hay 6 repartidores registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay repartidores registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 30; si no, muestra un
      error y vuelve a pedir el dato de **ese mismo** envío (no se salta a
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

REPARTIDOR 1
  Envio 1: 2
  Envio 2: 45
  ERROR! El dato debe estar entre 0 y 30 dias
  Envio 2: -1
  ERROR! El dato debe estar entre 0 y 30 dias
  Envio 2: 1
  Envio 3: 3
  Envio 4: 2
  Envio 5: 2

Promedio: 2 dias -> A tiempo
```

```
Opcion: 3

TABLA DE DIAS DE ENTREGA

                  E1    E2    E3    E4    E5   Promedio
Repartidor 1       2     1     3     2     2          2   A tiempo
Repartidor 2       4     5     3     6     2          4   Con retraso
Repartidor 3       3     3     3     3     3          3   A tiempo
Repartidor 4       1     2     1     1     0          1   A tiempo
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay repartidores registrados |
| 2 | Registro del repartidor 1 | Repartidor 1: 2, 1, 3, 2, 2 | Promedio 2 → A tiempo |
| 3 | Registro del repartidor 2 | Repartidor 2: 4, 5, 3, 6, 2 | Promedio 4 → Con retraso |
| 4 | Justo en el límite | Repartidor 3: 3, 3, 3, 3, 3 | Promedio 3 → **A tiempo** |
| 5 | Registro del repartidor 4 | Repartidor 4: 1, 2, 1, 1, 0 | Promedio 1 → A tiempo |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; A tiempo: 3 (75%); Con retraso: 1 (25%); Promedio de días de entrega de la empresa: 2.5 días |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Dato fuera de rango | Un dato de 45 o de -1 | Error; vuelve a pedir el dato de ese mismo envío |
| 9 | Registro lleno | Opción 1 con 6 repartidores ya registrados | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
