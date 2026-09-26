# Evidencia 2.2 — Pruebas de resistencia por pieza

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 16 — Roldan Reyes Alexis

## Historia de usuario

**Como** técnico de un laboratorio de materiales, **quiero** registrar el resultado de 3 pruebas de tensión por pieza y consultar cuáles se aprueban, **para** liberar solo las piezas que de verdad soportan la carga.

## Contexto

En la Evidencia 1 tu programa aprobaba o rechazaba cada pieza con **una sola** prueba y la olvidaba. Ahora el laboratorio hace **3 pruebas** por pieza y decide con el promedio, así que hay que **guardar** los resultados.

Los datos forman una tabla:

|  | Prueba 1 | Prueba 2 | Prueba 3 |
|---|---|---|---|
| **Pieza 1** | 620 | 580 | 610 |
| **Pieza 2** | 450 | 520 | 470 |
| ... | | | |

**Reglas**

- El laboratorio prueba como máximo **5 piezas** por lote.
- Cada pieza pasa por **3 pruebas** de tensión.
- Una resistencia es válida si está entre **0 y 2000 kg**.
- Una pieza es **aprobada** si el **promedio** de sus 3 pruebas es **mayor o igual a 500 kg**; si no, es **rechazada**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
LABORATORIO DE RESISTENCIA

1.- Registrar una pieza
2.- Reporte general
3.- Tabla de resistencias
4.- Salir
```

- **Opción 1:** pide los datos de las 3 pruebas de la siguiente pieza y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  piezas registradas, cuántas quedan como *Aprobada* y cuántas como *Rechazada*
  (con sus porcentajes), y el promedio de resistencia de las piezas.
- **Opción 3:** muestra la tabla de todas las piezas registradas: una
  fila por pieza, con sus 3 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan piezas.** El programa no permite eliminar ni modificar
una pieza ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `resistencias`** guarda lo que el usuario **captura**: los 3 datos de
  cada pieza.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  pieza.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la pieza 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la pieza 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos piezas:

```
              resistencias               promedios
             [0]    [1]    [2]
fila 0       620    580    610     →     [0]  603.33
fila 1       450    520    470     →     [1]  480
fila 2   (vacía)                         [2]  (vacío)
 ...
fila 4   (vacía)                         [4]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 3 datos de la siguiente pieza en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 3 datos y se divide entre 3, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas piezas
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
      5 × 3: cada fila es una pieza y cada columna una prueba.
- [ ] El promedio de cada pieza se guarda en un **vector** `double` de 5
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas piezas se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de piezas (5), los datos por pieza (3), los
      límites de un dato válido (0 y 2000) y el límite de
      la clasificación (500) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las piezas registradas**, no las
      5 filas de la matriz.
- [ ] Si ya hay 5 piezas registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay piezas registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 2000; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** prueba (no se salta a
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

PIEZA 1
  Prueba 1: 620
  Prueba 2: 2500
  ERROR! El dato debe estar entre 0 y 2000 kg
  Prueba 2: -50
  ERROR! El dato debe estar entre 0 y 2000 kg
  Prueba 2: 580
  Prueba 3: 610

Promedio: 603.33 kg -> Aprobada
```

```
Opcion: 3

TABLA DE RESISTENCIAS

             P1    P2    P3   Promedio
Pieza 1     620   580   610     603.33   Aprobada
Pieza 2     450   520   470        480   Rechazada
Pieza 3     500   500   500        500   Aprobada
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay piezas registradas |
| 2 | Registro de la pieza 1 | Pieza 1: 620, 580, 610 | Promedio 603.33 → Aprobada |
| 3 | Registro de la pieza 2 | Pieza 2: 450, 520, 470 | Promedio 480 → Rechazada |
| 4 | Justo en el límite | Pieza 3: 500, 500, 500 | Promedio 500 → **Aprobada** |
| 5 | Reporte general | Opción 2 después de los casos 2 a 4 | Total 3; Aprobada: 2 (66.67%); Rechazada: 1 (33.33%); Promedio de resistencia de las piezas: 527.78 kg |
| 6 | Tabla | Opción 3 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Dato fuera de rango | Un dato de 2500 o de -50 | Error; vuelve a pedir el dato de esa misma prueba |
| 8 | Registro lleno | Opción 1 con 5 piezas ya registradas | Aviso de registro lleno; no pide datos |
| 9 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
