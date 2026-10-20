# Evidencia 3 — Filtro de temperatura en un evento

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 03 — Flores Hidalgo Carolina

## Historia de usuario

**Como** encargado de la entrada de un concierto, **quiero** registrar a cada asistente con su fecha de nacimiento y sus 3 tomas de temperatura, y consultarlo por nombre o por mes de nacimiento, **para** resolver rápido las dudas de un asistente en la entrada y regalar una cortesía a quienes cumplen años en el mes del concierto.

## Contexto

En la Evidencia 2.2 los 3 datos de cada asistente vivían en la matriz `temperaturas` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada asistente
será un **registro** completo: su nombre, su fecha de nacimiento, sus 3 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- Se registran como máximo **5 asistentes** por fila de revisión.
- De cada asistente se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Valeria`), y su **fecha de nacimiento**: la fecha de nacimiento que aparece en su boleto, con día, mes y año.
- A cada asistente se le toma la temperatura **3 veces**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **1940 y 2026**.
- Una toma es válida si está entre **34 y 42 °C**.
- Un asistente **puede pasar** si el **promedio** de sus 3 tomas es **menor o igual a 37.5 °C**; si no, es **febril y no puede pasar**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
FILTRO DE ACCESO AL EVENTO

1.- Registrar un asistente
2.- Tabla de asistentes
3.- Asistentes por mes de nacimiento
4.- Buscar un asistente
5.- Salir
```

- **Opción 1:** pide el nombre, la fecha de nacimiento y los 3 datos del siguiente asistente y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los asistentes registrados: una fila por
  asistente, con su nombre, su fecha de nacimiento, sus 3 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los asistentes cuya fecha de nacimiento cae en ese
  mes, de cualquier año, con su nombre, su fecha de nacimiento, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide el nombre y, si hay un asistente registrado con ese nombre,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan asistentes.** El programa no permite eliminar ni modificar un
asistente ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Asistente {
    string nombre;
    Fecha nacimiento;            // struct anidado: fecha de nacimiento
    double temperaturas[TOMAS];  // los 3 datos de cada asistente
    double promedioTemperatura;  // el promedio de los 3 datos
};

Asistente asistentes[MAX_ASISTENTES];
```

**Un arreglo como campo de un struct.** `temperaturas` es un arreglo de 3 datos que vive
**dentro** de cada asistente (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al asistente y luego el campo:

| Expresión | Qué es |
|---|---|
| `asistentes[1]` | El segundo asistente completo (de tipo `Asistente`) |
| `asistentes[1].nombre` | Su nombre (de tipo `string`) |
| `asistentes[1].nacimiento.mes` | El mes de su fecha de nacimiento (de tipo `int`) |
| `asistentes[1].temperaturas` | Sus 3 datos (un arreglo de `double`) |
| `asistentes[1].temperaturas[2]` | Su dato de la columna 3 (Toma 3), de tipo `double` |
| `asistentes[1].promedioTemperatura` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos asistentes:

```
                                   temperaturas   
 asistentesnombre   nacimiento     [0]   [1]   [2]   promedioTemperatura
   [0]     Valeria  4/5/2001      36.5  36.7  36.6                  36.6
   [1]     Jorge    19/1/1998     38.2  38.5  37.9                  38.2
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el nombre, la fecha y los 3 datos, y en cuanto termina la captura se suman sus 3 datos y se dividen entre 3
y el resultado se guarda en `promedioTemperatura` del **mismo** asistente.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioTemperatura`; no vuelven a recorrer los 3 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos asistentes hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Asistente`.
- [ ] Define `struct Asistente` con los campos `nombre` (`string`), `nacimiento` (`Fecha`),
      `temperaturas` (arreglo `double` de 3) y `promedioTemperatura` (`double`), antes de `main`.
- [ ] Los asistentes se guardan en un **arreglo de structs** `Asistente asistentes[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos asistentes se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada asistente se guarda en su campo `promedioTemperatura` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de asistentes (5), los datos por asistente (3), los límites de un
      dato válido (34 y 42), los límites del año
      (1940 y 2026) y el límite de la clasificación (37.5)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarTemperatura(double promedioTemperatura)`, que recibe el promedio (no el struct) y regresa
      `"Puede pasar"` o `"Febril, no puede pasar"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      asistente, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los asistentes cuyo mes de `nacimiento` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara el nombre escrito con el campo `nombre` de cada
      asistente registrado y muestra **todos** los datos del que coincide: nombre,
      fecha de nacimiento, los 3 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los asistentes registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 asistentes registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay asistentes registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      1940 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 34 y 42; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** toma (no se salta a la
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

Registro del primer asistente, con datos fuera de rango:

```
Opcion: 1

ASISTENTE 1
  Nombre: Valeria
  Fecha de nacimiento
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 4
    Mes: 5
    Anio: 2027
    ERROR! El anio debe estar entre 1940 y 2026
    Anio: 2001
  Tomas
    Toma 1: 36.5
    Toma 2: 45
    ERROR! El dato debe estar entre 34 y 42 °C
    Toma 2: 36.7
    Toma 3: 36.6

Promedio: 36.6 °C -> Puede pasar
```

Después de registrar los 4 asistentes de los casos de prueba:

```
Opcion: 2

TABLA DE ASISTENTES

Nombre    Fecha            T1    T2    T3   Promedio
Valeria   4/5/2001       36.5  36.7  36.6       36.6   Puede pasar
Jorge     19/1/1998      38.2  38.5  37.9       38.2   Febril, no puede pasar
Paola     27/5/2006      37.5  37.5  37.5       37.5   Puede pasar
Ruben     11/10/1985       37  37.5  38.5      37.67   Febril, no puede pasar
```

```
Opcion: 3
Mes (1 a 12): 5

ASISTENTES CON FECHA DE NACIMIENTO EN EL MES 5

Valeria   4/5/2001     Promedio: 36.6 °C   Puede pasar
Paola     27/5/2006    Promedio: 37.5 °C   Puede pasar
```

```
Opcion: 4
Nombre a buscar: Jorge

Nombre: Jorge
Fecha de nacimiento: 19/1/1998
Tomas: T1 38.2, T2 38.5, T3 37.9
Promedio: 38.2 °C -> Febril, no puede pasar
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay asistentes registrados; la opción 3 no pide el mes y la 4 no pide el nombre |
| 2 | Registro del asistente 1 | `Valeria`, 4/5/2001, datos 36.5, 36.7, 36.6 | Promedio 36.6 °C → Puede pasar |
| 3 | Registro del asistente 2 | `Jorge`, 19/1/1998, datos 38.2, 38.5, 37.9 | Promedio 38.2 °C → Febril, no puede pasar |
| 4 | Justo en el límite | `Paola`, 27/5/2006, datos 37.5, 37.5, 37.5 | Promedio 37.5 °C → **Puede pasar** |
| 5 | Registro del asistente 4 | `Ruben`, 11/10/1985, datos 37, 37.5, 38.5 | Promedio 37.67 °C → Febril, no puede pasar |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Mes con registros | Opción 3, mes 5 | `Valeria` (4/5/2001) y `Paola` (27/5/2006), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 11 | Aviso de que ningún asistente tiene su fecha de nacimiento en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `Jorge` | Todos sus datos: 19/1/1998; 38.2, 38.5, 37.9; promedio 38.2 °C; Febril, no puede pasar |
| 11 | Búsqueda no encontrada | Opción 4, `Pedro` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `jorge` | Aviso de que no se encontró: `jorge` y `Jorge` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 1939 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 45 o de 30 | Error; vuelve a pedir el dato de esa misma toma |
| 15 | Registro lleno | Se registra `Elena`, 2/12/1993, datos 36.2, 36.4, 36.3 (promedio 36.3, Puede pasar), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
