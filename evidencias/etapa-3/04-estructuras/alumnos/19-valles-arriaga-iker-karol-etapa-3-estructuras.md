# Evidencia 3 — Tiempo de espera por caja

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 19 — Valles Arriaga Iker Karol

## Historia de usuario

**Como** gerente de un supermercado, **quiero** registrar cada caja con su clave, la fecha de instalación de su terminal y la espera de 5 clientes, y consultarla por clave o por mes de instalación, **para** revisar rápido una caja y programar el mantenimiento de las terminales instaladas en un mes.

## Contexto

En la Evidencia 2.2 los 5 datos de cada caja vivían en la matriz `esperas` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada caja
será un **registro** completo: su clave, su fecha de instalación, sus 5 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- El supermercado tiene como máximo **5 cajas**.
- De cada caja se registra su **clave**, una sola palabra sin espacios (por ejemplo `CJ1`), y su **fecha de instalación**: la fecha en que se instaló la terminal de cobro de la caja, con día, mes y año.
- En cada caja se mide la espera de **5 clientes**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Un tiempo de espera es válido si está entre **0 y 120 minutos**.
- Una caja tiene **espera aceptable** si el **promedio** de sus 5 clientes es **menor o igual a 10 minutos**; si no, tiene **espera excesiva**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
TIEMPO DE ESPERA EN CAJAS

1.- Registrar una caja
2.- Tabla de cajas
3.- Cajas por mes de instalacion
4.- Buscar una caja
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de instalación y los 5 datos de la siguiente caja y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todas las cajas registradas: una fila por
  caja, con su clave, su fecha de instalación, sus 5 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las cajas cuya fecha de instalación cae en ese
  mes, de cualquier año, con su clave, su fecha de instalación, su promedio y su clasificación. Si
  ninguna cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay una caja registrada con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan cajas.** El programa no permite eliminar ni modificar una
caja ya registrada: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Caja {
    string clave;
    Fecha instalacion;         // struct anidado: fecha de instalación
    double esperas[CLIENTES];  // los 5 datos de cada caja
    double promedioEspera;     // el promedio de los 5 datos
};

Caja cajas[MAX_CAJAS];
```

**Un arreglo como campo de un struct.** `esperas` es un arreglo de 5 datos que vive
**dentro** de cada caja (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la caja y luego el campo:

| Expresión | Qué es |
|---|---|
| `cajas[1]` | La segunda caja completa (de tipo `Caja`) |
| `cajas[1].clave` | Su clave (de tipo `string`) |
| `cajas[1].instalacion.mes` | El mes de su fecha de instalación (de tipo `int`) |
| `cajas[1].esperas` | Sus 5 datos (un arreglo de `double`) |
| `cajas[1].esperas[4]` | Su dato de la columna 5 (Cliente 5), de tipo `double` |
| `cajas[1].promedioEspera` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos cajas:

```
                                          esperas         
 cajas     clave    instalacion    [0]  [1]  [2]  [3]  [4]   promedioEspera
   [0]     CJ1      26/8/2021        5    8  6.5    9  4.5              6.6
   [1]     CJ2      2/3/2023        12   15    9   18   11               13
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 5 datos, y en cuanto termina la captura se suman sus 5 datos y se dividen entre 5
y el resultado se guarda en `promedioEspera` de la **misma** caja.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioEspera`; no vuelven a recorrer los 5 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántas cajas hay registradas. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
la siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Caja`.
- [ ] Define `struct Caja` con los campos `clave` (`string`), `instalacion` (`Fecha`),
      `esperas` (arreglo `double` de 5) y `promedioEspera` (`double`), antes de `main`.
- [ ] Las cajas se guardan en un **arreglo de structs** `Caja cajas[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas cajas se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El promedio de cada caja se guarda en su campo `promedioEspera` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de cajas (5), los datos por caja (5), los límites de un
      dato válido (0 y 120), los límites del año
      (2015 y 2026) y el límite de la clasificación (10)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarEspera(double promedioEspera)`, que recibe el promedio (no el struct) y regresa
      `"Espera aceptable"` o `"Espera excesiva"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      caja, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las cajas cuyo mes de `instalacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      caja registrada y muestra **todos** los datos de la que coincide: clave,
      fecha de instalación, los 5 datos, su promedio y su clasificación. Si ninguna coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo las cajas registradas**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 cajas registradas, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay cajas registradas, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2015 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 120; si no, muestra
      un error y vuelve a pedir el dato de **ese mismo** cliente (no se salta a la
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

Registro de la primera caja, con datos fuera de rango:

```
Opcion: 1

CAJA 1
  Clave: CJ1
  Fecha de instalacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 26
    Mes: 8
    Anio: 2027
    ERROR! El anio debe estar entre 2015 y 2026
    Anio: 2021
  Clientes
    Cliente 1: 5
    Cliente 2: 150
    ERROR! El dato debe estar entre 0 y 120 min
    Cliente 2: 8
    Cliente 3: 6.5
    Cliente 4: 9
    Cliente 5: 4.5

Promedio: 6.6 min -> Espera aceptable
```

Después de registrar las 5 cajas de los casos de prueba:

```
Opcion: 2

TABLA DE CAJAS

Clave   Fecha           C1   C2   C3   C4   C5   Promedio
CJ1     26/8/2021        5    8  6.5    9  4.5        6.6   Espera aceptable
CJ2     2/3/2023        12   15    9   18   11         13   Espera excesiva
CJ3     14/8/2024       10   10   10   10   10         10   Espera aceptable
CJ4     10/11/2019      14   12   16   10   13         13   Espera excesiva
CJ5     19/5/2025       20   25   11    9   15         16   Espera excesiva
```

```
Opcion: 3
Mes (1 a 12): 8

CAJAS CON FECHA DE INSTALACION EN EL MES 8

CJ1     26/8/2021    Promedio: 6.6 min   Espera aceptable
CJ3     14/8/2024    Promedio: 10 min   Espera aceptable
```

```
Opcion: 4
Clave a buscar: CJ2

Clave: CJ2
Fecha de instalacion: 2/3/2023
Clientes: C1 12, C2 15, C3 9, C4 18, C5 11
Promedio: 13 min -> Espera excesiva
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay cajas registradas; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro de la caja 1 | `CJ1`, 26/8/2021, datos 5, 8, 6.5, 9, 4.5 | Promedio 6.6 min → Espera aceptable |
| 3 | Registro de la caja 2 | `CJ2`, 2/3/2023, datos 12, 15, 9, 18, 11 | Promedio 13 min → Espera excesiva |
| 4 | Justo en el límite | `CJ3`, 14/8/2024, datos 10, 10, 10, 10, 10 | Promedio 10 min → **Espera aceptable** |
| 5 | Registro de la caja 4 | `CJ4`, 10/11/2019, datos 14, 12, 16, 10, 13 | Promedio 13 min → Espera excesiva |
| 6 | Registro de la caja 5 | `CJ5`, 19/5/2025, datos 20, 25, 11, 9, 15 | Promedio 16 min → Espera excesiva |
| 7 | Tabla | Opción 2 después de los casos 2 a 6 | 5 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Mes con registros | Opción 3, mes 8 | `CJ1` (26/8/2021) y `CJ3` (14/8/2024), aunque son de años distintos |
| 9 | Mes sin registros | Opción 3, mes 12 | Aviso de que ninguna caja tiene su fecha de instalación en ese mes |
| 10 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 11 | Búsqueda encontrada | Opción 4, `CJ2` | Todos sus datos: 2/3/2023; 12, 15, 9, 18, 11; promedio 13 min; Espera excesiva |
| 12 | Búsqueda no encontrada | Opción 4, `CJ9` | Aviso de que no se encontró |
| 13 | Mayúsculas distintas | Opción 4, `cj2` | Aviso de que no se encontró: `cj2` y `CJ2` son textos distintos |
| 14 | Fecha no válida | Día 0 o 32; mes 13; año 2014 o 2027 | Error; vuelve a pedir ese mismo dato |
| 15 | Dato fuera de rango | Un dato de 150 o de -2 | Error; vuelve a pedir el dato de ese mismo cliente |
| 16 | Registro lleno | Opción 1 con 5 cajas ya registradas | Aviso de registro lleno; no pide datos |
| 17 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
