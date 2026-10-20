# Evidencia 3 — Registro de puntualidad semanal

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 01 — Cruz Martinez Cielo Michelle

## Historia de usuario

**Como** encargado de recursos humanos de una escuela, **quiero** registrar a cada empleado con su fecha de ingreso y sus minutos de retardo de la semana, y consultarlo por nombre o por mes de ingreso, **para** tener en un solo lugar todo lo de cada empleado y preparar los reconocimientos por aniversario de trabajo.

## Contexto

En la Evidencia 2.2 los 5 datos de cada empleado vivían en la matriz `retardos` y su total
en el vector `totales`, y lo único que los unía era el número de fila. Ahora cada empleado
será un **registro** completo: su nombre, su fecha de ingreso, sus 5 datos y su total viajan
juntos en un `struct`.

**Reglas**

- La escuela registra como máximo **5 empleados**.
- De cada empleado se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Sofia`), y su **fecha de ingreso**: la fecha en que entró a trabajar a la escuela, con día, mes y año.
- De cada empleado se registran los **minutos de retardo de 5 días** (lunes a viernes). Un `0` significa que ese día llegó a tiempo.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **1990 y 2026**.
- Los minutos de retardo de un día son válidos si están entre **0 y 120**.
- Un empleado es **puntual** si el **total** de sus minutos de retardo en la semana es **menor o igual a 15**; si no, queda **con retardos**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
REGISTRO DE PUNTUALIDAD

1.- Registrar un empleado
2.- Tabla de empleados
3.- Empleados por mes de ingreso
4.- Buscar un empleado
5.- Salir
```

- **Opción 1:** pide el nombre, la fecha de ingreso y los 5 datos del siguiente empleado y, al
  terminar, muestra su total y su clasificación.
- **Opción 2:** muestra la tabla de todos los empleados registrados: una fila por
  empleado, con su nombre, su fecha de ingreso, sus 5 datos, su total y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los empleados cuya fecha de ingreso cae en ese
  mes, de cualquier año, con su nombre, su fecha de ingreso, su total y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide el nombre y, si hay un empleado registrado con ese nombre,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan empleados.** El programa no permite eliminar ni modificar un
empleado ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Empleado {
    string nombre;
    Fecha ingreso;          // struct anidado: fecha de ingreso
    double retardos[DIAS];  // los 5 datos de cada empleado
    double totalRetardos;   // la suma de los 5 datos
};

Empleado empleados[MAX_EMPLEADOS];
```

**Un arreglo como campo de un struct.** `retardos` es un arreglo de 5 datos que vive
**dentro** de cada empleado (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al empleado y luego el campo:

| Expresión | Qué es |
|---|---|
| `empleados[1]` | El segundo empleado completo (de tipo `Empleado`) |
| `empleados[1].nombre` | Su nombre (de tipo `string`) |
| `empleados[1].ingreso.mes` | El mes de su fecha de ingreso (de tipo `int`) |
| `empleados[1].retardos` | Sus 5 datos (un arreglo de `double`) |
| `empleados[1].retardos[4]` | Su dato de la columna 5 (Viernes), de tipo `double` |
| `empleados[1].totalRetardos` | Su total (de tipo `double`) |

Por ejemplo, después de registrar dos empleados:

```
                                         retardos        
 empleados nombre   ingreso       [0]  [1]  [2]  [3]  [4]   totalRetardos
   [0]     Sofia    15/3/2018       0    5    0    3    2              10
   [1]     Diego    2/8/2021       10   15    0   20    5              50
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el nombre, la fecha y los 5 datos, y en cuanto termina la captura se suman sus 5 datos
y el resultado se guarda en `totalRetardos` del **mismo** empleado.

**¿Para qué guardar el total?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `totalRetardos`; no vuelven a recorrer los 5 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos empleados hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Empleado`.
- [ ] Define `struct Empleado` con los campos `nombre` (`string`), `ingreso` (`Fecha`),
      `retardos` (arreglo `double` de 5) y `totalRetardos` (`double`), antes de `main`.
- [ ] Los empleados se guardan en un **arreglo de structs** `Empleado empleados[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos empleados se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El total de cada empleado se guarda en su campo `totalRetardos` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de empleados (5), los datos por empleado (5), los límites de un
      dato válido (0 y 120), los límites del año
      (1990 y 2026) y el límite de la clasificación (15)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarPuntualidad(double totalRetardos)`, que recibe el total (no el struct) y regresa
      `"Puntual"` o `"Con retardos"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      empleado, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los empleados cuyo mes de `ingreso` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara el nombre escrito con el campo `nombre` de cada
      empleado registrado y muestra **todos** los datos del que coincide: nombre,
      fecha de ingreso, los 5 datos, su total y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los empleados registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 empleados registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay empleados registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      1990 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 120; si no, muestra
      un error y vuelve a pedir el dato de **ese mismo** día (no se salta a la
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

Registro del primer empleado, con datos fuera de rango:

```
Opcion: 1

EMPLEADO 1
  Nombre: Sofia
  Fecha de ingreso
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 15
    Mes: 3
    Anio: 2027
    ERROR! El anio debe estar entre 1990 y 2026
    Anio: 2018
  Dias
    Lunes: 0
    Martes: 150
    ERROR! El dato debe estar entre 0 y 120 min
    Martes: 5
    Miercoles: 0
    Jueves: 3
    Viernes: 2

Total: 10 min -> Puntual
```

Después de registrar los 4 empleados de los casos de prueba:

```
Opcion: 2

TABLA DE EMPLEADOS

Nombre   Fecha          L   M   M   J   V   Total
Sofia    15/3/2018      0   5   0   3   2      10   Puntual
Diego    2/8/2021      10  15   0  20   5      50   Con retardos
Ana      20/3/2023      5   5   5   0   0      15   Puntual
Luis     9/11/2015      0   0   0   0   0       0   Puntual
```

```
Opcion: 3
Mes (1 a 12): 3

EMPLEADOS CON FECHA DE INGRESO EN EL MES 3

Sofia    15/3/2018   Total: 10 min   Puntual
Ana      20/3/2023   Total: 15 min   Puntual
```

```
Opcion: 4
Nombre a buscar: Diego

Nombre: Diego
Fecha de ingreso: 2/8/2021
Dias: L 10, M 15, M 0, J 20, V 5
Total: 50 min -> Con retardos
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay empleados registrados; la opción 3 no pide el mes y la 4 no pide el nombre |
| 2 | Registro del empleado 1 | `Sofia`, 15/3/2018, datos 0, 5, 0, 3, 2 | Total 10 min → Puntual |
| 3 | Registro del empleado 2 | `Diego`, 2/8/2021, datos 10, 15, 0, 20, 5 | Total 50 min → Con retardos |
| 4 | Justo en el límite | `Ana`, 20/3/2023, datos 5, 5, 5, 0, 0 | Total 15 min → **Puntual** |
| 5 | Registro del empleado 4 | `Luis`, 9/11/2015, datos 0, 0, 0, 0, 0 | Total 0 min → Puntual |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su total y su clasificación |
| 7 | Mes con registros | Opción 3, mes 3 | `Sofia` (15/3/2018) y `Ana` (20/3/2023), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún empleado tiene su fecha de ingreso en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `Diego` | Todos sus datos: 2/8/2021; 10, 15, 0, 20, 5; total 50 min; Con retardos |
| 11 | Búsqueda no encontrada | Opción 4, `Pedro` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `diego` | Aviso de que no se encontró: `diego` y `Diego` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 1989 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 150 o de -3 | Error; vuelve a pedir el dato de ese mismo día |
| 15 | Registro lleno | Se registra `Marta`, 30/6/2019, datos 20, 30, 0, 0, 0 (total 50, Con retardos), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
