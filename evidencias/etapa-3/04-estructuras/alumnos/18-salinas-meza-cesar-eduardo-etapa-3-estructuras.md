# Evidencia 3 — Consumo de datos móviles por semana

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 18 — Salinas Meza Cesar Eduardo

## Historia de usuario

**Como** analista de una compañía telefónica, **quiero** registrar cada línea con su número, su fecha de contratación y su consumo de las 4 semanas, y consultarla por número o por mes de contratación, **para** atender rápido a un cliente y ofrecer el cambio de plan en el mes en que cumple años su contrato.

## Contexto

En la Evidencia 2.2 los 4 datos de cada línea vivían en la matriz `consumos` y su total
en el vector `totales`, y lo único que los unía era el número de fila. Ahora cada línea
será un **registro** completo: su número de teléfono, su fecha de contratación, sus 4 datos y su total viajan
juntos en un `struct`.

**Reglas**

- Se revisan como máximo **5 líneas**.
- De cada línea se registra su **número de teléfono**, una sola palabra sin espacios (por ejemplo `8110000001`), y su **fecha de contratación**: la fecha en que el cliente contrató la línea, con día, mes y año.
- De cada línea se registra el consumo de **4 semanas**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2010 y 2026**.
- El consumo de una semana es válido si está entre **0 y 50 GB**.
- Una línea está **dentro del plan** si el **total** de sus 4 semanas es **menor o igual a 5 GB**; si no, **excede el plan**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
CONSUMO DE DATOS MOVILES

1.- Registrar una linea
2.- Tabla de lineas
3.- Lineas por mes de contratacion
4.- Buscar una linea
5.- Salir
```

- **Opción 1:** pide el número de teléfono, la fecha de contratación y los 4 datos de la siguiente línea y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra la tabla de todas las líneas registradas: una fila por
  línea, con su número de teléfono, su fecha de contratación, sus 4 datos, su total y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las líneas cuya fecha de contratación cae en ese
  mes, de cualquier año, con su número de teléfono, su fecha de contratación, su total y su clasificación. Si
  ninguna cumple, lo avisa.
- **Opción 4:** pide el número de teléfono y, si hay una línea registrada con ese número de teléfono,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan líneas.** El programa no permite eliminar ni modificar una
línea ya registrada: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Linea {
    string numero;
    Fecha contratacion;        // struct anidado: fecha de contratación
    double consumos[SEMANAS];  // los 4 datos de cada línea
    double totalConsumo;       // la suma de los 4 datos
};

Linea lineas[MAX_LINEAS];
```

**Un arreglo como campo de un struct.** `consumos` es un arreglo de 4 datos que vive
**dentro** de cada línea (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la línea y luego el campo:

| Expresión | Qué es |
|---|---|
| `lineas[1]` | La segunda línea completa (de tipo `Linea`) |
| `lineas[1].numero` | Su número de teléfono (de tipo `string`) |
| `lineas[1].contratacion.mes` | El mes de su fecha de contratación (de tipo `int`) |
| `lineas[1].consumos` | Sus 4 datos (un arreglo de `double`) |
| `lineas[1].consumos[3]` | Su dato de la columna 4 (Semana 4), de tipo `double` |
| `lineas[1].totalConsumo` | Su total (de tipo `double`) |

Por ejemplo, después de registrar dos líneas:

```
                                             consumos        
 lineas    numero      contratacion     [0]   [1]   [2]   [3]   totalConsumo
   [0]     8110000001  30/1/2022       0.75  1.25     1   0.5            3.5
   [1]     8110000002  12/5/2019          2   1.5  1.25  1.75            6.5
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el número de teléfono, la fecha y los 4 datos, y en cuanto termina la captura se suman sus 4 datos
y el resultado se guarda en `totalConsumo` de la **misma** línea.

**¿Para qué guardar el total?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `totalConsumo`; no vuelven a recorrer los 4 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántas líneas hay registradas. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
la siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Linea`.
- [ ] Define `struct Linea` con los campos `numero` (`string`), `contratacion` (`Fecha`),
      `consumos` (arreglo `double` de 4) y `totalConsumo` (`double`), antes de `main`.
- [ ] Las líneas se guardan en un **arreglo de structs** `Linea lineas[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas líneas se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El total de cada línea se guarda en su campo `totalConsumo` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de líneas (5), los datos por línea (4), los límites de un
      dato válido (0 y 50), los límites del año
      (2010 y 2026) y el límite de la clasificación (5)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarPlan(double totalConsumo)`, que recibe el total (no el struct) y regresa
      `"Dentro del plan"` o `"Excede el plan"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      línea, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las líneas cuyo mes de `contratacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara el número de teléfono escrito con el campo `numero` de cada
      línea registrada y muestra **todos** los datos de la que coincide: número de teléfono,
      fecha de contratación, los 4 datos, su total y su clasificación. Si ninguna coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo las líneas registradas**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 líneas registradas, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay líneas registradas, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2010 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 50; si no, muestra
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

Registro de la primera línea, con datos fuera de rango:

```
Opcion: 1

LINEA 1
  Numero de telefono: 8110000001
  Fecha de contratacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 30
    Mes: 1
    Anio: 2027
    ERROR! El anio debe estar entre 2010 y 2026
    Anio: 2022
  Semanas
    Semana 1: 0.75
    Semana 2: 60
    ERROR! El dato debe estar entre 0 y 50 GB
    Semana 2: 1.25
    Semana 3: 1
    Semana 4: 0.5

Total: 3.5 GB -> Dentro del plan
```

Después de registrar las 3 líneas de los casos de prueba:

```
Opcion: 2

TABLA DE LINEAS

Numero               Fecha           S1    S2    S3    S4   Total
8110000001           30/1/2022     0.75  1.25     1   0.5     3.5   Dentro del plan
8110000002           12/5/2019        2   1.5  1.25  1.75     6.5   Excede el plan
8110000003           17/1/2025     1.25  1.25  1.25  1.25       5   Dentro del plan
```

```
Opcion: 3
Mes (1 a 12): 1

LINEAS CON FECHA DE CONTRATACION EN EL MES 1

8110000001           30/1/2022   Total: 3.5 GB   Dentro del plan
8110000003           17/1/2025   Total: 5 GB   Dentro del plan
```

```
Opcion: 4
Numero de telefono a buscar: 8110000002

Numero de telefono: 8110000002
Fecha de contratacion: 12/5/2019
Semanas: S1 2, S2 1.5, S3 1.25, S4 1.75
Total: 6.5 GB -> Excede el plan
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay líneas registradas; la opción 3 no pide el mes y la 4 no pide el número de teléfono |
| 2 | Registro de la línea 1 | `8110000001`, 30/1/2022, datos 0.75, 1.25, 1, 0.5 | Total 3.5 GB → Dentro del plan |
| 3 | Registro de la línea 2 | `8110000002`, 12/5/2019, datos 2, 1.5, 1.25, 1.75 | Total 6.5 GB → Excede el plan |
| 4 | Justo en el límite | `8110000003`, 17/1/2025, datos 1.25, 1.25, 1.25, 1.25 | Total 5 GB → **Dentro del plan** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 6 | Mes con registros | Opción 3, mes 1 | `8110000001` (30/1/2022) y `8110000003` (17/1/2025), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ninguna línea tiene su fecha de contratación en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `8110000002` | Todos sus datos: 12/5/2019; 2, 1.5, 1.25, 1.75; total 6.5 GB; Excede el plan |
| 10 | Búsqueda no encontrada | Opción 4, `8110000009` | Aviso de que no se encontró |
| 11 | Identificador incompleto | Opción 4, `811000000` | Aviso de que no se encontró: `811000000` no es igual a `8110000002` |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 2009 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 60 o de -1 | Error; vuelve a pedir el dato de esa misma semana |
| 14 | Registro lleno | Se registran `8110000004`, 4/9/2023, datos 0.5, 0.25, 0.75, 0.5 (total 2, Dentro del plan); `8110000005`, 21/11/2020, datos 3, 2.5, 4, 3.5 (total 13, Excede el plan), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
