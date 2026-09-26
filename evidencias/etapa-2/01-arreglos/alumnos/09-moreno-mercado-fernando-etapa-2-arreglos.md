# Evidencia 2.2 — Batería de laptops durante el día

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 09 — Moreno Mercado Fernando

## Historia de usuario

**Como** encargado del centro de cómputo, **quiero** registrar la carga de batería de cada laptop al terminar cada una de las 4 clases del día y consultar cuáles tienen batería baja, **para** mandar a revisión las baterías que ya no aguantan.

## Contexto

En la Evidencia 1 tu programa revisaba la batería de cada laptop **una sola vez**, antes de prestarla, y la olvidaba. Ahora el centro de cómputo quiere saber qué tan bien aguanta cada batería durante el día, así que hay que **guardar** la carga que le queda al terminar cada una de las 4 clases.

Los datos forman una tabla:

|  | Clase 1 | Clase 2 | Clase 3 | Clase 4 |
|---|---|---|---|---|
| **Laptop 1** | 80 | 65 | 50 | 35 |
| **Laptop 2** | 30 | 18 | 10 | 5 |
| ... | | | | |

**Reglas**

- El centro de cómputo presta como máximo **7 laptops**.
- De cada laptop se registra la carga restante al terminar **4 clases**.
- Una carga es válida si está entre **0 y 100%**.
- Una laptop tiene **batería suficiente** si el **promedio** de sus 4 cargas es **mayor o igual a 20%**; si no, tiene **batería baja**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
PRESTAMO DE LAPTOPS

1.- Registrar una laptop
2.- Reporte general
3.- Tabla de cargas
4.- Salir
```

- **Opción 1:** pide los datos de las 4 clases de la siguiente laptop y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  laptops registradas, cuántas quedan como *Bateria suficiente* y cuántas como *Bateria baja*
  (con sus porcentajes), y el promedio de carga de las laptops.
- **Opción 3:** muestra la tabla de todas las laptops registradas: una
  fila por laptop, con sus 4 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan laptops.** El programa no permite eliminar ni modificar
una laptop ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 7.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `cargas`** guarda lo que el usuario **captura**: los 4 datos de
  cada laptop.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  laptop.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la laptop 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la laptop 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos laptops:

```
                    cargas                      promedios
             [0]    [1]    [2]    [3]
fila 0        80     65     50     35     →     [0]  57.5
fila 1        30     18     10      5     →     [1]  15.75
fila 2   (vacía)                                [2]  (vacío)
 ...
fila 6   (vacía)                                [6]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 4 datos de la siguiente laptop en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 4 datos y se divide entre 4, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas laptops
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
      7 × 4: cada fila es una laptop y cada columna una clase.
- [ ] El promedio de cada laptop se guarda en un **vector** `double` de 7
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas laptops se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de laptops (7), los datos por laptop (4), los
      límites de un dato válido (0 y 100) y el límite de
      la clasificación (20) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las laptops registradas**, no las
      7 filas de la matriz.
- [ ] Si ya hay 7 laptops registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay laptops registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** clase (no se salta a
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

LAPTOP 1
  Clase 1: 80
  Clase 2: 101
  ERROR! El dato debe estar entre 0 y 100%
  Clase 2: -1
  ERROR! El dato debe estar entre 0 y 100%
  Clase 2: 65
  Clase 3: 50
  Clase 4: 35

Promedio: 57.5% -> Bateria suficiente
```

```
Opcion: 3

TABLA DE CARGAS

              C1    C2    C3    C4   Promedio
Laptop 1      80    65    50    35       57.5   Bateria suficiente
Laptop 2      30    18    10     5      15.75   Bateria baja
Laptop 3      20    20    20    20         20   Bateria suficiente
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay laptops registradas |
| 2 | Registro de la laptop 1 | Laptop 1: 80, 65, 50, 35 | Promedio 57.5 → Bateria suficiente |
| 3 | Registro de la laptop 2 | Laptop 2: 30, 18, 10, 5 | Promedio 15.75 → Bateria baja |
| 4 | Justo en el límite | Laptop 3: 20, 20, 20, 20 | Promedio 20 → **Bateria suficiente** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Bateria suficiente: 2 (66.67%); Bateria baja: 1 (33.33%); Promedio de carga de las laptops: 31.08% |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Dato fuera de rango | Un dato de 101 o de -1 | Error; vuelve a pedir el dato de esa misma clase |
| 8 | Registro lleno | Opción 1 con 7 laptops ya registradas | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
