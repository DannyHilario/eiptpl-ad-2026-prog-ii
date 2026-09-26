# Evidencia 2.2 — Tiempo de espera por caja

*Etapa II — Arreglos · Laboratorio de Programas · Entrega: jueves 1 de octubre de 2026, 8:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 19 — Valles Arriaga Iker Karol

## Historia de usuario

**Como** gerente de un supermercado, **quiero** registrar el tiempo de espera de 5 clientes en cada caja y consultar en cuáles la espera es excesiva, **para** decidir a qué cajas mandar un cajero de apoyo.

## Contexto

En la Evidencia 1 tu programa clasificaba la espera de cada cliente en el momento y la olvidaba. Ahora el supermercado quiere evaluar cada **caja**, así que hay que **guardar** el tiempo de espera de 5 clientes por caja y decidir con su promedio.

Los datos forman una tabla:

|  | Cliente 1 | Cliente 2 | Cliente 3 | Cliente 4 | Cliente 5 |
|---|---|---|---|---|---|
| **Caja 1** | 5 | 8 | 6.5 | 9 | 4.5 |
| **Caja 2** | 12 | 15 | 9 | 18 | 11 |
| ... | | | | | |

**Reglas**

- El supermercado tiene como máximo **6 cajas**.
- En cada caja se mide la espera de **5 clientes**.
- Un tiempo de espera es válido si está entre **0 y 120 minutos**.
- Una caja tiene **espera aceptable** si el **promedio** de sus 5 clientes es **menor o igual a 10 minutos**; si no, tiene **espera excesiva**.

El programa se controla con este menú, y solo termina cuando el usuario elige
la opción 4:

```
TIEMPO DE ESPERA EN CAJAS

1.- Registrar una caja
2.- Reporte general
3.- Tabla de esperas
4.- Salir
```

- **Opción 1:** pide los datos de los 5 clientes de la siguiente caja y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra un reporte con lo registrado hasta el momento: total de
  cajas registradas, cuántas quedan como *Espera aceptable* y cuántas como *Espera excesiva*
  (con sus porcentajes), y el promedio de tiempo de espera del supermercado.
- **Opción 3:** muestra la tabla de todas las cajas registradas: una
  fila por caja, con sus 5 datos, su promedio y su clasificación.
- **Opción 4:** termina el programa.

**Solo se agregan cajas.** El programa no permite eliminar ni modificar
una caja ya registrada: cada vez que eliges la opción 1 se ocupa la
siguiente fila libre, hasta llenar las 6.

## Cómo se organizan los datos

Tu programa usa **dos arreglos que trabajan juntos**:

- La **matriz `esperas`** guarda lo que el usuario **captura**: los 5 datos de
  cada caja.
- El **vector `promedios`** guarda lo que el programa **calcula**: el promedio de cada
  caja.

La fila de la matriz y la posición del vector **se corresponden**: todo lo
de la caja 1 está en la fila `0` de la matriz y en la posición `0` del
vector; todo lo de la caja 2, en la fila `1` y en la posición `1`, y así.

Por ejemplo, después de registrar dos cajas:

```
                       esperas                         promedios
             [0]    [1]    [2]    [3]    [4]
fila 0         5      8    6.5      9    4.5     →     [0]  6.6
fila 1        12     15      9     18     11     →     [1]  13
fila 2   (vacía)                                       [2]  (vacío)
 ...
fila 5   (vacía)                                       [5]  (vacío)
```

**¿Cuándo se llena cada uno?** Los dos se llenan en la **opción 1**, uno detrás
del otro:

1. Primero se capturan los 5 datos de la siguiente caja en su fila de la matriz.
2. En cuanto termina esa fila, se suman sus 5 datos y se divide entre 5, y el resultado se guarda en la **misma
   posición** del vector.

**¿Para qué sirve guardar el promedio?** Para no calcularlo otra vez. Las opciones
2 y 3 **leen** el vector: la opción 2 lo recorre para contar cuántas cajas
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
      6 × 5: cada fila es una caja y cada columna un cliente.
- [ ] El promedio de cada caja se guarda en un **vector** `double` de 6
      posiciones: el promedio de la fila `i` de la matriz va en la posición `i`
      del vector.
- [ ] Un contador lleva cuántas cajas se han registrado; ese mismo
      contador indica en qué fila se guarda la siguiente.
- [ ] El máximo de cajas (6), los datos por caja (5), los
      límites de un dato válido (0 y 120) y el límite de
      la clasificación (10) son constantes con nombre. La matriz y
      el vector se declaran con esas constantes.
- [ ] Las opciones 2 y 3 **leen** el promedio del vector; no lo vuelven a calcular.

### Habilidades (5 puntos) — Almacenar, leer y validar los datos

**Almacena y lee correctamente**

- [ ] La tabla de la opción 3 muestra exactamente los datos capturados, cada
      uno en la fila y la columna que le corresponde.
- [ ] Las opciones 2 y 3 recorren **solo las cajas registradas**, no las
      6 filas de la matriz.
- [ ] Si ya hay 6 cajas registradas, la opción 1 avisa que el registro
      está lleno y **no** guarda nada fuera de la matriz.
- [ ] Si todavía no hay cajas registradas, las opciones 2 y 3 muestran un
      aviso en lugar del reporte o la tabla.
- [ ] La opción del menú debe estar entre 1 y 4; si no, muestra un error y
      vuelve a pedirla.
- [ ] Cada dato debe estar entre 0 y 120; si no, muestra un
      error y vuelve a pedir el dato de **ese mismo** cliente (no se salta a
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

CAJA 1
  Cliente 1: 5
  Cliente 2: 150
  ERROR! El dato debe estar entre 0 y 120 min
  Cliente 2: -2
  ERROR! El dato debe estar entre 0 y 120 min
  Cliente 2: 8
  Cliente 3: 6.5
  Cliente 4: 9
  Cliente 5: 4.5

Promedio: 6.6 min -> Espera aceptable
```

```
Opcion: 3

TABLA DE ESPERAS

            C1    C2    C3    C4    C5   Promedio
Caja 1       5     8   6.5     9   4.5        6.6   Espera aceptable
Caja 2      12    15     9    18    11         13   Espera excesiva
Caja 3      10    10    10    10    10         10   Espera aceptable
Caja 4      14    12    16    10    13         13   Espera excesiva
Caja 5      20    25    11     9    15         16   Espera excesiva
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y
los cálculos sean correctos.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Reporte sin datos | Opción 2 o 3 antes de registrar | Aviso de que no hay cajas registradas |
| 2 | Registro de la caja 1 | Caja 1: 5, 8, 6.5, 9, 4.5 | Promedio 6.6 → Espera aceptable |
| 3 | Registro de la caja 2 | Caja 2: 12, 15, 9, 18, 11 | Promedio 13 → Espera excesiva |
| 4 | Justo en el límite | Caja 3: 10, 10, 10, 10, 10 | Promedio 10 → **Espera aceptable** |
| 5 | Registro de la caja 4 | Caja 4: 14, 12, 16, 10, 13 | Promedio 13 → Espera excesiva |
| 6 | Registro de la caja 5 | Caja 5: 20, 25, 11, 9, 15 | Promedio 16 → Espera excesiva |
| 7 | Reporte general | Opción 2 después de los casos 2 a 6 | Total 5; Espera aceptable: 2 (40%); Espera excesiva: 3 (60%); Promedio de tiempo de espera del supermercado: 11.72 min |
| 8 | Tabla | Opción 3 después de los casos 2 a 6 | 5 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 9 | Dato fuera de rango | Un dato de 150 o de -2 | Error; vuelve a pedir el dato de ese mismo cliente |
| 10 | Registro lleno | Opción 1 con 6 cajas ya registradas | Aviso de registro lleno; no pide datos |
| 11 | Opción inválida | Opción 0 o 5 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales (por ejemplo `66.6667` en vez de `66.67`).
