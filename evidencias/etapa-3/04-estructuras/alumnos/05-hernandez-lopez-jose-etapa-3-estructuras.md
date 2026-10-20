# Evidencia 3 — Consumo eléctrico mensual por semanas

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 05 — Hernandez Lopez Jose

## Historia de usuario

**Como** revisor de una compañía de luz, **quiero** registrar cada casa con su número de medidor, su fecha de contratación y su consumo de las 4 semanas, y consultarla por medidor o por mes de contratación, **para** contestar rápido la llamada de un cliente y revisar los contratos que se renuevan cada mes.

## Contexto

En la Evidencia 2.2 los 4 datos de cada casa vivían en la matriz `consumos` y su total
en el vector `totales`, y lo único que los unía era el número de fila. Ahora cada casa
será un **registro** completo: su número de medidor, su fecha de contratación, sus 4 datos y su total viajan
juntos en un `struct`.

**Reglas**

- Se revisan como máximo **5 casas** de la colonia.
- De cada casa se registra su **número de medidor**, una sola palabra sin espacios (por ejemplo `M2041`), y su **fecha de contratación**: la fecha en que se contrató el servicio de luz, con día, mes y año.
- De cada casa se registra el consumo de **4 semanas**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **1990 y 2026**.
- El consumo de una semana es válido si está entre **0 y 200 kWh**.
- Una casa tiene **consumo normal** si el **total** de sus 4 semanas es **menor o igual a 300 kWh**; si no, tiene **alto consumo**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
CONSUMO ELECTRICO DE LA COLONIA

1.- Registrar una casa
2.- Tabla de casas
3.- Casas por mes de contratacion
4.- Buscar una casa
5.- Salir
```

- **Opción 1:** pide el número de medidor, la fecha de contratación y los 4 datos de la siguiente casa y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra la tabla de todas las casas registradas: una fila por
  casa, con su número de medidor, su fecha de contratación, sus 4 datos, su total y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las casas cuya fecha de contratación cae en ese
  mes, de cualquier año, con su número de medidor, su fecha de contratación, su total y su clasificación. Si
  ninguna cumple, lo avisa.
- **Opción 4:** pide el número de medidor y, si hay una casa registrada con ese número de medidor,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan casas.** El programa no permite eliminar ni modificar una
casa ya registrada: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Casa {
    string medidor;
    Fecha contratacion;        // struct anidado: fecha de contratación
    double consumos[SEMANAS];  // los 4 datos de cada casa
    double totalConsumo;       // la suma de los 4 datos
};

Casa casas[MAX_CASAS];
```

**Un arreglo como campo de un struct.** `consumos` es un arreglo de 4 datos que vive
**dentro** de cada casa (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la casa y luego el campo:

| Expresión | Qué es |
|---|---|
| `casas[1]` | La segunda casa completa (de tipo `Casa`) |
| `casas[1].medidor` | Su número de medidor (de tipo `string`) |
| `casas[1].contratacion.mes` | El mes de su fecha de contratación (de tipo `int`) |
| `casas[1].consumos` | Sus 4 datos (un arreglo de `double`) |
| `casas[1].consumos[3]` | Su dato de la columna 4 (Semana 4), de tipo `double` |
| `casas[1].totalConsumo` | Su total (de tipo `double`) |

Por ejemplo, después de registrar dos casas:

```
                                          consumos        
 casas     medidor  contratacion     [0]   [1]   [2]   [3]   totalConsumo
   [0]     M2041    10/7/2010       60.5    72    58  65.5            256
   [1]     M2042    25/3/2019         90  85.5   110    95          380.5
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el número de medidor, la fecha y los 4 datos, y en cuanto termina la captura se suman sus 4 datos
y el resultado se guarda en `totalConsumo` de la **misma** casa.

**¿Para qué guardar el total?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `totalConsumo`; no vuelven a recorrer los 4 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántas casas hay registradas. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
la siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Casa`.
- [ ] Define `struct Casa` con los campos `medidor` (`string`), `contratacion` (`Fecha`),
      `consumos` (arreglo `double` de 4) y `totalConsumo` (`double`), antes de `main`.
- [ ] Las casas se guardan en un **arreglo de structs** `Casa casas[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas casas se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El total de cada casa se guarda en su campo `totalConsumo` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de casas (5), los datos por casa (4), los límites de un
      dato válido (0 y 200), los límites del año
      (1990 y 2026) y el límite de la clasificación (300)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarConsumo(double totalConsumo)`, que recibe el total (no el struct) y regresa
      `"Consumo normal"` o `"Alto consumo"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      casa, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las casas cuyo mes de `contratacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara el número de medidor escrito con el campo `medidor` de cada
      casa registrada y muestra **todos** los datos de la que coincide: número de medidor,
      fecha de contratación, los 4 datos, su total y su clasificación. Si ninguna coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo las casas registradas**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 casas registradas, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay casas registradas, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      1990 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 200; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** semana (no se salta a la
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

Registro de la primera casa, con datos fuera de rango:

```
Opcion: 1

CASA 1
  Numero de medidor: M2041
  Fecha de contratacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 10
    Mes: 7
    Anio: 2027
    ERROR! El anio debe estar entre 1990 y 2026
    Anio: 2010
  Semanas
    Semana 1: 60.5
    Semana 2: 250
    ERROR! El dato debe estar entre 0 y 200 kWh
    Semana 2: 72
    Semana 3: 58
    Semana 4: 65.5

Total: 256 kWh -> Consumo normal
```

Después de registrar las 3 casas de los casos de prueba:

```
Opcion: 2

TABLA DE CASAS

Numero              Fecha           S1    S2    S3    S4   Total
M2041               10/7/2010     60.5    72    58  65.5     256   Consumo normal
M2042               25/3/2019       90  85.5   110    95   380.5   Alto consumo
M2043               5/7/2022        75    75    75    75     300   Consumo normal
```

```
Opcion: 3
Mes (1 a 12): 7

CASAS CON FECHA DE CONTRATACION EN EL MES 7

M2041               10/7/2010   Total: 256 kWh   Consumo normal
M2043               5/7/2022    Total: 300 kWh   Consumo normal
```

```
Opcion: 4
Numero de medidor a buscar: M2042

Numero de medidor: M2042
Fecha de contratacion: 25/3/2019
Semanas: S1 90, S2 85.5, S3 110, S4 95
Total: 380.5 kWh -> Alto consumo
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay casas registradas; la opción 3 no pide el mes y la 4 no pide el número de medidor |
| 2 | Registro de la casa 1 | `M2041`, 10/7/2010, datos 60.5, 72, 58, 65.5 | Total 256 kWh → Consumo normal |
| 3 | Registro de la casa 2 | `M2042`, 25/3/2019, datos 90, 85.5, 110, 95 | Total 380.5 kWh → Alto consumo |
| 4 | Justo en el límite | `M2043`, 5/7/2022, datos 75, 75, 75, 75 | Total 300 kWh → **Consumo normal** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 6 | Mes con registros | Opción 3, mes 7 | `M2041` (10/7/2010) y `M2043` (5/7/2022), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ninguna casa tiene su fecha de contratación en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `M2042` | Todos sus datos: 25/3/2019; 90, 85.5, 110, 95; total 380.5 kWh; Alto consumo |
| 10 | Búsqueda no encontrada | Opción 4, `M2049` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `m2042` | Aviso de que no se encontró: `m2042` y `M2042` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 1989 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 250 o de -5 | Error; vuelve a pedir el dato de esa misma semana |
| 14 | Registro lleno | Se registran `M2044`, 16/11/2005, datos 40, 55, 50, 45 (total 190, Consumo normal); `M2045`, 1/2/2015, datos 120, 95, 88, 102 (total 405, Alto consumo), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
