# Evidencia 2.2 — Ocupación del estacionamiento por piso

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 17 — Salinas Diaz Andrea Elizabeth

## Historia de usuario

**Como** administrador del estacionamiento de un centro comercial, **quiero** registrar 5 mediciones de ocupación de cada piso durante la tarde y consultar qué pisos suelen estar llenos, **para** decidir en qué pisos poner letreros de "lleno" en las horas pico.

## Contexto

En la Evidencia 1 tu programa clasificaba cada medición de ocupación en el momento y la olvidaba. Ahora el centro comercial quiere saber cómo se comporta **cada piso**, así que hay que **guardar** 5 mediciones de cada piso y decidir con su promedio.

Los datos forman una tabla:

|  | Medición 1 | Medición 2 | Medición 3 | Medición 4 | Medición 5 |
|---|---|---|---|---|---|
| **Piso 1** | 60 | 75 | 82 | 90 | 68 |
| **Piso 2** | 96 | 98 | 100 | 94 | 97 |
| ... | | | | | |

**Reglas**

- El estacionamiento tiene como máximo **5 pisos**.
- De cada piso se toman **5 mediciones** de ocupación durante la tarde.
- Una medición es válida si está entre **0 y 100%**.
- Un piso se considera **lleno** si el **promedio** de sus 5 mediciones es **mayor o igual a 95%**; si es menor, está **disponible**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
OCUPACION DEL ESTACIONAMIENTO

1.- Registrar un piso
2.- Reporte general
3.- Tabla de ocupacion
4.- Salir
```

- **Opción 1:** pide los datos de las 5 mediciones del siguiente piso y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  pisos registrados, cuántos quedan como *Disponible* y cuántos como *Lleno*
  (con sus porcentajes), y el promedio de ocupación del estacionamiento.
- **Opción 3:** muestra la tabla de todos los pisos registrados: una
  fila por piso, con sus 5 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan pisos.** El programa no permite eliminar ni modificar
un piso ya registrado: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar los 5.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `ocupacion`** guarda lo que el usuario **captura**: los 5 datos de
  cada piso.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  piso.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
del piso 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo del piso 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos pisos:

```
                      ocupacion                        promedios
             [0]    [1]    [2]    [3]    [4]
fila 0        60     75     82     90     68     →     [0]  75
fila 1        96     98    100     94     97     →     [1]  97
fila 2   (vacía)                                       [2]  (vacío)
 ...
fila 4   (vacía)                                       [4]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 5 datos del siguiente piso en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 5 datos y se divide entre 5, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántos pisos
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
      5 × 5: cada fila es un piso y cada columna una medición.
- [ ] El promedio de cada piso se guarda en un **vector** `double` de 5
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántos pisos se han registrado; ese mismo
      contador indica en qué fila se guarda el siguiente.
- [ ] El máximo de pisos (5), los datos por piso (5), los
      límites de un dato válido (0 y 100) y el límite de
      la clasificación (95) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo los pisos registrados**, no las
      5 filas de la matriz.
- [ ] Si ya hay 5 pisos registrados, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay pisos registrados, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra un
      error y vuelve a pedir el dato de **esa misma** medición (no se salta a
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

PISO 1
  Medicion 1: 60
  Medicion 2: 105
  ERROR! El dato debe estar entre 0 y 100%
  Medicion 2: -1
  ERROR! El dato debe estar entre 0 y 100%
  Medicion 2: 75
  Medicion 3: 82
  Medicion 4: 90
  Medicion 5: 68

Promedio: 75% -> Disponible
```

```
Opcion: 3

TABLA DE OCUPACION

            M1    M2    M3    M4    M5   Promedio
Piso 1      60    75    82    90    68         75   Disponible
Piso 2      96    98   100    94    97         97   Lleno
Piso 3      95    95    95    95    95         95   Lleno
Piso 4      88    92    97    99    94         94   Disponible
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay pisos registrados |
| 2 | Registro del piso 1 | Piso 1: 60, 75, 82, 90, 68 | Promedio 75 → Disponible |
| 3 | Registro del piso 2 | Piso 2: 96, 98, 100, 94, 97 | Promedio 97 → Lleno |
| 4 | Justo en el límite | Piso 3: 95, 95, 95, 95, 95 | Promedio 95 → **Lleno** |
| 5 | Registro del piso 4 | Piso 4: 88, 92, 97, 99, 94 | Promedio 94 → Disponible |
| 6 | Reporte general | Opción 2 después de los casos 2 a 5 | Total 4; Disponible: 2 (50%); Lleno: 2 (50%); Promedio de ocupación del estacionamiento: 90.25% |
| 7 | Tabla | Opción 3 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Dato fuera de rango | Un dato de 105 o de -1 | Error; vuelve a pedir el dato de esa misma medición |
| 9 | Registro lleno | Opción 1 con 5 pisos ya registrados | Aviso de registro lleno; no pide datos |
| 10 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
