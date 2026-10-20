# Evidencia 3 — Pruebas de resistencia por pieza

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 16 — Roldan Reyes Alexis

## Historia de usuario

**Como** técnico de un laboratorio de materiales, **quiero** registrar cada pieza con su número de serie, su fecha de fabricación y sus 3 pruebas de tensión, y consultarla por número de serie o por mes de fabricación, **para** rastrear rápido una pieza reclamada y revisar las piezas fabricadas en un mes con problemas.

## Contexto

En la Evidencia 2.2 los 3 datos de cada pieza vivían en la matriz `resistencias` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada pieza
será un **registro** completo: su número de serie, su fecha de fabricación, sus 3 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- El laboratorio prueba como máximo **5 piezas** por lote.
- De cada pieza se registra su **número de serie**, una sola palabra sin espacios (por ejemplo `S1001`), y su **fecha de fabricación**: la fecha en que se fabricó la pieza, con día, mes y año.
- Cada pieza pasa por **3 pruebas** de tensión.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- Una resistencia es válida si está entre **0 y 2000 kg**.
- Una pieza es **aprobada** si el **promedio** de sus 3 pruebas es **mayor o igual a 500 kg**; si no, es **rechazada**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
LABORATORIO DE RESISTENCIA

1.- Registrar una pieza
2.- Tabla de piezas
3.- Piezas por mes de fabricacion
4.- Buscar una pieza
5.- Salir
```

- **Opción 1:** pide el número de serie, la fecha de fabricación y los 3 datos de la siguiente pieza y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todas las piezas registradas: una fila por
  pieza, con su número de serie, su fecha de fabricación, sus 3 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las piezas cuya fecha de fabricación cae en ese
  mes, de cualquier año, con su número de serie, su fecha de fabricación, su promedio y su clasificación. Si
  ninguna cumple, lo avisa.
- **Opción 4:** pide el número de serie y, si hay una pieza registrada con ese número de serie,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan piezas.** El programa no permite eliminar ni modificar una
pieza ya registrada: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Pieza {
    string serie;
    Fecha fabricacion;             // struct anidado: fecha de fabricación
    double resistencias[PRUEBAS];  // los 3 datos de cada pieza
    double promedioResistencia;    // el promedio de los 3 datos
};

Pieza piezas[MAX_PIEZAS];
```

**Un arreglo como campo de un struct.** `resistencias` es un arreglo de 3 datos que vive
**dentro** de cada pieza (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la pieza y luego el campo:

| Expresión | Qué es |
|---|---|
| `piezas[1]` | La segunda pieza completa (de tipo `Pieza`) |
| `piezas[1].serie` | Su número de serie (de tipo `string`) |
| `piezas[1].fabricacion.mes` | El mes de su fecha de fabricación (de tipo `int`) |
| `piezas[1].resistencias` | Sus 3 datos (un arreglo de `double`) |
| `piezas[1].resistencias[2]` | Su dato de la columna 3 (Prueba 3), de tipo `double` |
| `piezas[1].promedioResistencia` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos piezas:

```
                                   resistencias 
 piezas    serie    fabricacion    [0]  [1]  [2]   promedioResistencia
   [0]     S1001    7/11/2024      620  580  610                603.33
   [1]     S1002    24/6/2026      450  520  470                   480
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el número de serie, la fecha y los 3 datos, y en cuanto termina la captura se suman sus 3 datos y se dividen entre 3
y el resultado se guarda en `promedioResistencia` de la **misma** pieza.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioResistencia`; no vuelven a recorrer los 3 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántas piezas hay registradas. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
la siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Pieza`.
- [ ] Define `struct Pieza` con los campos `serie` (`string`), `fabricacion` (`Fecha`),
      `resistencias` (arreglo `double` de 3) y `promedioResistencia` (`double`), antes de `main`.
- [ ] Las piezas se guardan en un **arreglo de structs** `Pieza piezas[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas piezas se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El promedio de cada pieza se guarda en su campo `promedioResistencia` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de piezas (5), los datos por pieza (3), los límites de un
      dato válido (0 y 2000), los límites del año
      (2020 y 2026) y el límite de la clasificación (500)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarResistencia(double promedioResistencia)`, que recibe el promedio (no el struct) y regresa
      `"Aprobada"` o `"Rechazada"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      pieza, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las piezas cuyo mes de `fabricacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara el número de serie escrito con el campo `serie` de cada
      pieza registrada y muestra **todos** los datos de la que coincide: número de serie,
      fecha de fabricación, los 3 datos, su promedio y su clasificación. Si ninguna coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo las piezas registradas**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 piezas registradas, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay piezas registradas, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2020 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 2000; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** prueba (no se salta a la
      siguiente).
- [ ] El mes que se pide en la opción 3 debe estar entre 1 y 12; si no, muestra un
      error y lo vuelve a pedir.
- [ ] Los resultados coinciden con **todos** los casos de prueba de este enunciado.

**Código fácil de seguir y leer**

- [ ] Nombres descriptivos para los structs, sus campos y las variables.
- [ ] Comentarios que expliquen cada sección del programa (structs, menú, registro,
      tabla, filtro por mes, búsqueda, validaciones).
- [ ] Compila y se ejecuta sin errores en Dev-C++.

### Actitudes / Valores (2 puntos) — Entrega

- [ ] Lo entregas en NEXUS, en la evidencia *"3.2 - Evidencia de Aprendizaje 3: Programa"*, antes del
      **jueves 22 de octubre de 2026 a las 7:40 p.m.**
- [ ] El archivo es de texto plano, con el nombre `EV3.2_ApellidoNombre.txt`.
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu código si
      se te pregunta.

## Ejemplo de ejecución

Registro de la primera pieza, con datos fuera de rango:

```
Opcion: 1

PIEZA 1
  Numero de serie: S1001
  Fecha de fabricacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 7
    Mes: 11
    Anio: 2027
    ERROR! El anio debe estar entre 2020 y 2026
    Anio: 2024
  Pruebas
    Prueba 1: 620
    Prueba 2: 2500
    ERROR! El dato debe estar entre 0 y 2000 kg
    Prueba 2: 580
    Prueba 3: 610

Promedio: 603.33 kg -> Aprobada
```

Después de registrar las 3 piezas de los casos de prueba:

```
Opcion: 2

TABLA DE PIEZAS

Numero            Fecha           P1   P2   P3   Promedio
S1001             7/11/2024      620  580  610     603.33   Aprobada
S1002             24/6/2026      450  520  470        480   Rechazada
S1003             19/11/2025     500  500  500        500   Aprobada
```

```
Opcion: 3
Mes (1 a 12): 11

PIEZAS CON FECHA DE FABRICACION EN EL MES 11

S1001             7/11/2024    Promedio: 603.33 kg   Aprobada
S1003             19/11/2025   Promedio: 500 kg   Aprobada
```

```
Opcion: 4
Numero de serie a buscar: S1002

Numero de serie: S1002
Fecha de fabricacion: 24/6/2026
Pruebas: P1 450, P2 520, P3 470
Promedio: 480 kg -> Rechazada
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay piezas registradas; la opción 3 no pide el mes y la 4 no pide el número de serie |
| 2 | Registro de la pieza 1 | `S1001`, 7/11/2024, datos 620, 580, 610 | Promedio 603.33 kg → Aprobada |
| 3 | Registro de la pieza 2 | `S1002`, 24/6/2026, datos 450, 520, 470 | Promedio 480 kg → Rechazada |
| 4 | Justo en el límite | `S1003`, 19/11/2025, datos 500, 500, 500 | Promedio 500 kg → **Aprobada** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 6 | Mes con registros | Opción 3, mes 11 | `S1001` (7/11/2024) y `S1003` (19/11/2025), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ninguna pieza tiene su fecha de fabricación en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `S1002` | Todos sus datos: 24/6/2026; 450, 520, 470; promedio 480 kg; Rechazada |
| 10 | Búsqueda no encontrada | Opción 4, `S1009` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `s1002` | Aviso de que no se encontró: `s1002` y `S1002` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 2019 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 2500 o de -50 | Error; vuelve a pedir el dato de esa misma prueba |
| 14 | Registro lleno | Se registran `S1004`, 3/2/2024, datos 800, 760, 840 (promedio 800, Aprobada); `S1005`, 15/8/2025, datos 300, 350, 280 (promedio 310, Rechazada), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
