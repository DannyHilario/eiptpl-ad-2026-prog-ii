# Evidencia 3 — Tiempos de entrega por repartidor

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 15 — Rodriguez Martinez Angel Ricardo

## Historia de usuario

**Como** gerente de operaciones de una empresa de paquetería, **quiero** registrar a cada repartidor con su fecha de ingreso y los días de entrega de sus últimos 5 envíos, y consultarlo por nombre o por mes de ingreso, **para** revisar rápido a un repartidor y preparar sus evaluaciones por aniversario de trabajo.

## Contexto

En la Evidencia 2.2 los 5 datos de cada repartidor vivían en la matriz `dias` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada repartidor
será un **registro** completo: su nombre, su fecha de ingreso, sus 5 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- La empresa tiene como máximo **5 repartidores**.
- De cada repartidor se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Ernesto`), y su **fecha de ingreso**: la fecha en que entró a trabajar a la paquetería, con día, mes y año.
- De cada repartidor se registran los días de entrega de sus últimos **5 envíos**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2010 y 2026**.
- Los días de entrega de un envío son válidos si están entre **0 y 30** (0 = se entregó el mismo día).
- Un repartidor entrega **a tiempo** si el **promedio** de sus 5 envíos es **menor o igual a 3 días**; si no, entrega **con retraso**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
ENTREGAS DE PAQUETERIA

1.- Registrar un repartidor
2.- Tabla de repartidores
3.- Repartidores por mes de ingreso
4.- Buscar un repartidor
5.- Salir
```

- **Opción 1:** pide el nombre, la fecha de ingreso y los 5 datos del siguiente repartidor y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los repartidores registrados: una fila por
  repartidor, con su nombre, su fecha de ingreso, sus 5 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los repartidores cuya fecha de ingreso cae en ese
  mes, de cualquier año, con su nombre, su fecha de ingreso, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide el nombre y, si hay un repartidor registrado con ese nombre,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan repartidores.** El programa no permite eliminar ni modificar un
repartidor ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Repartidor {
    string nombre;
    Fecha ingreso;        // struct anidado: fecha de ingreso
    double dias[ENVIOS];  // los 5 datos de cada repartidor
    double promedioDias;  // el promedio de los 5 datos
};

Repartidor repartidores[MAX_REPARTIDORES];
```

**Un arreglo como campo de un struct.** `dias` es un arreglo de 5 datos que vive
**dentro** de cada repartidor (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al repartidor y luego el campo:

| Expresión | Qué es |
|---|---|
| `repartidores[1]` | El segundo repartidor completo (de tipo `Repartidor`) |
| `repartidores[1].nombre` | Su nombre (de tipo `string`) |
| `repartidores[1].ingreso.mes` | El mes de su fecha de ingreso (de tipo `int`) |
| `repartidores[1].dias` | Sus 5 datos (un arreglo de `double`) |
| `repartidores[1].dias[4]` | Su dato de la columna 5 (Envio 5), de tipo `double` |
| `repartidores[1].promedioDias` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos repartidores:

```
                                           dias          
 repartidoresnombre   ingreso       [0]  [1]  [2]  [3]  [4]   promedioDias
   [0]     Ernesto  11/4/2021       2    1    3    2    2              2
   [1]     Fabiola  29/8/2016       4    5    3    6    2              4
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el nombre, la fecha y los 5 datos, y en cuanto termina la captura se suman sus 5 datos y se dividen entre 5
y el resultado se guarda en `promedioDias` del **mismo** repartidor.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioDias`; no vuelven a recorrer los 5 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos repartidores hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Repartidor`.
- [ ] Define `struct Repartidor` con los campos `nombre` (`string`), `ingreso` (`Fecha`),
      `dias` (arreglo `double` de 5) y `promedioDias` (`double`), antes de `main`.
- [ ] Los repartidores se guardan en un **arreglo de structs** `Repartidor repartidores[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos repartidores se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada repartidor se guarda en su campo `promedioDias` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de repartidores (5), los datos por repartidor (5), los límites de un
      dato válido (0 y 30), los límites del año
      (2010 y 2026) y el límite de la clasificación (3)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarEntrega(double promedioDias)`, que recibe el promedio (no el struct) y regresa
      `"A tiempo"` o `"Con retraso"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      repartidor, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los repartidores cuyo mes de `ingreso` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara el nombre escrito con el campo `nombre` de cada
      repartidor registrado y muestra **todos** los datos del que coincide: nombre,
      fecha de ingreso, los 5 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los repartidores registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 repartidores registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay repartidores registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2010 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 30; si no, muestra
      un error y vuelve a pedir el dato de **ese mismo** envío (no se salta a la
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

Registro del primer repartidor, con datos fuera de rango:

```
Opcion: 1

REPARTIDOR 1
  Nombre: Ernesto
  Fecha de ingreso
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 11
    Mes: 4
    Anio: 2027
    ERROR! El anio debe estar entre 2010 y 2026
    Anio: 2021
  Envios
    Envio 1: 2
    Envio 2: 45
    ERROR! El dato debe estar entre 0 y 30 dias
    Envio 2: 1
    Envio 3: 3
    Envio 4: 2
    Envio 5: 2

Promedio: 2 dias -> A tiempo
```

Después de registrar los 4 repartidores de los casos de prueba:

```
Opcion: 2

TABLA DE REPARTIDORES

Nombre    Fecha         E1  E2  E3  E4  E5   Promedio
Ernesto   11/4/2021      2   1   3   2   2          2   A tiempo
Fabiola   29/8/2016      4   5   3   6   2          4   Con retraso
Gerardo   6/4/2024       3   3   3   3   3          3   A tiempo
Irma      13/1/2019      1   2   1   1   0          1   A tiempo
```

```
Opcion: 3
Mes (1 a 12): 4

REPARTIDORES CON FECHA DE INGRESO EN EL MES 4

Ernesto   11/4/2021   Promedio: 2 dias   A tiempo
Gerardo   6/4/2024    Promedio: 3 dias   A tiempo
```

```
Opcion: 4
Nombre a buscar: Fabiola

Nombre: Fabiola
Fecha de ingreso: 29/8/2016
Envios: E1 4, E2 5, E3 3, E4 6, E5 2
Promedio: 4 dias -> Con retraso
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay repartidores registrados; la opción 3 no pide el mes y la 4 no pide el nombre |
| 2 | Registro del repartidor 1 | `Ernesto`, 11/4/2021, datos 2, 1, 3, 2, 2 | Promedio 2 días → A tiempo |
| 3 | Registro del repartidor 2 | `Fabiola`, 29/8/2016, datos 4, 5, 3, 6, 2 | Promedio 4 días → Con retraso |
| 4 | Justo en el límite | `Gerardo`, 6/4/2024, datos 3, 3, 3, 3, 3 | Promedio 3 días → **A tiempo** |
| 5 | Registro del repartidor 4 | `Irma`, 13/1/2019, datos 1, 2, 1, 1, 0 | Promedio 1 días → A tiempo |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Mes con registros | Opción 3, mes 4 | `Ernesto` (11/4/2021) y `Gerardo` (6/4/2024), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún repartidor tiene su fecha de ingreso en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `Fabiola` | Todos sus datos: 29/8/2016; 4, 5, 3, 6, 2; promedio 4 días; Con retraso |
| 11 | Búsqueda no encontrada | Opción 4, `Pedro` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `fabiola` | Aviso de que no se encontró: `fabiola` y `Fabiola` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 2009 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 45 o de -1 | Error; vuelve a pedir el dato de ese mismo envío |
| 15 | Registro lleno | Se registra `Noe`, 22/10/2025, datos 5, 4, 6, 3, 7 (promedio 5, Con retraso), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
