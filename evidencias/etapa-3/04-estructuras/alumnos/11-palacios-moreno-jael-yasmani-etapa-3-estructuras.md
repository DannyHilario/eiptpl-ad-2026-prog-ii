# Evidencia 3 — Tiempos de atención de soporte técnico

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 11 — Palacios Moreno Jael Yasmani

## Historia de usuario

**Como** coordinador de un centro de soporte técnico, **quiero** registrar a cada técnico con su fecha de ingreso y las horas de sus últimos 5 tickets, y consultarlo por nombre o por mes de ingreso, **para** revisar rápido el desempeño de un técnico y preparar sus evaluaciones por aniversario de trabajo.

## Contexto

En la Evidencia 2.2 los 5 datos de cada técnico vivían en la matriz `horas` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada técnico
será un **registro** completo: su nombre, su fecha de ingreso, sus 5 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- El centro tiene como máximo **5 técnicos**.
- De cada técnico se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Oscar`), y su **fecha de ingreso**: la fecha en que entró a trabajar al centro de soporte, con día, mes y año.
- De cada técnico se registran las horas de sus últimos **5 tickets**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2005 y 2026**.
- Un tiempo es válido si está entre **0 y 168 horas** (una semana).
- Un técnico está **dentro de SLA** si el **promedio** de sus 5 tickets es **menor o igual a 24 horas**; si no, está **fuera de SLA**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
SOPORTE TECNICO

1.- Registrar un tecnico
2.- Tabla de tecnicos
3.- Tecnicos por mes de ingreso
4.- Buscar un tecnico
5.- Salir
```

- **Opción 1:** pide el nombre, la fecha de ingreso y los 5 datos del siguiente técnico y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los técnicos registrados: una fila por
  técnico, con su nombre, su fecha de ingreso, sus 5 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los técnicos cuya fecha de ingreso cae en ese
  mes, de cualquier año, con su nombre, su fecha de ingreso, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide el nombre y, si hay un técnico registrado con ese nombre,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan técnicos.** El programa no permite eliminar ni modificar un
técnico ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Tecnico {
    string nombre;
    Fecha ingreso;          // struct anidado: fecha de ingreso
    double horas[TICKETS];  // los 5 datos de cada técnico
    double promedioHoras;   // el promedio de los 5 datos
};

Tecnico tecnicos[MAX_TECNICOS];
```

**Un arreglo como campo de un struct.** `horas` es un arreglo de 5 datos que vive
**dentro** de cada técnico (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al técnico y luego el campo:

| Expresión | Qué es |
|---|---|
| `tecnicos[1]` | El segundo técnico completo (de tipo `Tecnico`) |
| `tecnicos[1].nombre` | Su nombre (de tipo `string`) |
| `tecnicos[1].ingreso.mes` | El mes de su fecha de ingreso (de tipo `int`) |
| `tecnicos[1].horas` | Sus 5 datos (un arreglo de `double`) |
| `tecnicos[1].horas[4]` | Su dato de la columna 5 (Ticket 5), de tipo `double` |
| `tecnicos[1].promedioHoras` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos técnicos:

```
                                            horas             
 tecnicos  nombre   ingreso        [0]   [1]   [2]   [3]   [4]   promedioHoras
   [0]     Oscar    1/6/2019         4  12.5     8    20   3.5             9.6
   [1]     Brenda   15/9/2023       30    26    48    12    19              27
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el nombre, la fecha y los 5 datos, y en cuanto termina la captura se suman sus 5 datos y se dividen entre 5
y el resultado se guarda en `promedioHoras` del **mismo** técnico.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioHoras`; no vuelven a recorrer los 5 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos técnicos hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Tecnico`.
- [ ] Define `struct Tecnico` con los campos `nombre` (`string`), `ingreso` (`Fecha`),
      `horas` (arreglo `double` de 5) y `promedioHoras` (`double`), antes de `main`.
- [ ] Los técnicos se guardan en un **arreglo de structs** `Tecnico tecnicos[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos técnicos se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada técnico se guarda en su campo `promedioHoras` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de técnicos (5), los datos por técnico (5), los límites de un
      dato válido (0 y 168), los límites del año
      (2005 y 2026) y el límite de la clasificación (24)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarAtencion(double promedioHoras)`, que recibe el promedio (no el struct) y regresa
      `"Dentro de SLA"` o `"Fuera de SLA"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      técnico, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los técnicos cuyo mes de `ingreso` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara el nombre escrito con el campo `nombre` de cada
      técnico registrado y muestra **todos** los datos del que coincide: nombre,
      fecha de ingreso, los 5 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los técnicos registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 técnicos registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay técnicos registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2005 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 168; si no, muestra
      un error y vuelve a pedir el dato de **ese mismo** ticket (no se salta a la
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

Registro del primer técnico, con datos fuera de rango:

```
Opcion: 1

TECNICO 1
  Nombre: Oscar
  Fecha de ingreso
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 1
    Mes: 6
    Anio: 2027
    ERROR! El anio debe estar entre 2005 y 2026
    Anio: 2019
  Tickets
    Ticket 1: 4
    Ticket 2: 200
    ERROR! El dato debe estar entre 0 y 168 horas
    Ticket 2: 12.5
    Ticket 3: 8
    Ticket 4: 20
    Ticket 5: 3.5

Promedio: 9.6 horas -> Dentro de SLA
```

Después de registrar los 4 técnicos de los casos de prueba:

```
Opcion: 2

TABLA DE TECNICOS

Nombre   Fecha           T1    T2    T3    T4    T5   Promedio
Oscar    1/6/2019         4  12.5     8    20   3.5        9.6   Dentro de SLA
Brenda   15/9/2023       30    26    48    12    19         27   Fuera de SLA
Ivan     10/6/2024       24    24    24    24    24         24   Dentro de SLA
Karla    27/2/2012       36    20    30    28    16         26   Fuera de SLA
```

```
Opcion: 3
Mes (1 a 12): 6

TECNICOS CON FECHA DE INGRESO EN EL MES 6

Oscar    1/6/2019    Promedio: 9.6 horas   Dentro de SLA
Ivan     10/6/2024   Promedio: 24 horas   Dentro de SLA
```

```
Opcion: 4
Nombre a buscar: Brenda

Nombre: Brenda
Fecha de ingreso: 15/9/2023
Tickets: T1 30, T2 26, T3 48, T4 12, T5 19
Promedio: 27 horas -> Fuera de SLA
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay técnicos registrados; la opción 3 no pide el mes y la 4 no pide el nombre |
| 2 | Registro del técnico 1 | `Oscar`, 1/6/2019, datos 4, 12.5, 8, 20, 3.5 | Promedio 9.6 horas → Dentro de SLA |
| 3 | Registro del técnico 2 | `Brenda`, 15/9/2023, datos 30, 26, 48, 12, 19 | Promedio 27 horas → Fuera de SLA |
| 4 | Justo en el límite | `Ivan`, 10/6/2024, datos 24, 24, 24, 24, 24 | Promedio 24 horas → **Dentro de SLA** |
| 5 | Registro del técnico 4 | `Karla`, 27/2/2012, datos 36, 20, 30, 28, 16 | Promedio 26 horas → Fuera de SLA |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Mes con registros | Opción 3, mes 6 | `Oscar` (1/6/2019) y `Ivan` (10/6/2024), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún técnico tiene su fecha de ingreso en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `Brenda` | Todos sus datos: 15/9/2023; 30, 26, 48, 12, 19; promedio 27 horas; Fuera de SLA |
| 11 | Búsqueda no encontrada | Opción 4, `Pedro` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `brenda` | Aviso de que no se encontró: `brenda` y `Brenda` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 2004 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 200 o de -1 | Error; vuelve a pedir el dato de ese mismo ticket |
| 15 | Registro lleno | Se registra `Mario`, 8/11/2021, datos 10, 14, 8, 12, 6 (promedio 10, Dentro de SLA), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
