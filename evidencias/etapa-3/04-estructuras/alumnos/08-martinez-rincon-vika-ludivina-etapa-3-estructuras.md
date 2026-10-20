# Evidencia 3 — Encuesta de satisfacción por cliente

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 08 — Martinez Rincon Vika Ludivina

## Historia de usuario

**Como** gerente de un restaurante, **quiero** registrar a cada cliente con su fecha de visita y sus 5 respuestas, y consultarlo por nombre o por mes de visita, **para** darle seguimiento a un cliente y comparar las encuestas de cada mes.

## Contexto

En la Evidencia 2.2 los 5 datos de cada cliente vivían en la matriz `respuestas` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada cliente
será un **registro** completo: su nombre, su fecha de visita, sus 5 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- Se capturan como máximo **5 clientes** por turno.
- De cada cliente se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Carmen`), y su **fecha de visita**: la fecha en que visitó el restaurante y contestó la encuesta, con día, mes y año.
- Cada cliente responde **5 preguntas**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2024 y 2026**.
- Una respuesta es válida si está entre **1 y 10**.
- Un cliente quedó **satisfecho** si el **promedio** de sus 5 respuestas es **mayor o igual a 8**; si no, quedó **insatisfecho**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
ENCUESTA DE SATISFACCION

1.- Registrar un cliente
2.- Tabla de clientes
3.- Clientes por mes de visita
4.- Buscar un cliente
5.- Salir
```

- **Opción 1:** pide el nombre, la fecha de visita y los 5 datos del siguiente cliente y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los clientes registrados: una fila por
  cliente, con su nombre, su fecha de visita, sus 5 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los clientes cuya fecha de visita cae en ese
  mes, de cualquier año, con su nombre, su fecha de visita, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide el nombre y, si hay un cliente registrado con ese nombre,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan clientes.** El programa no permite eliminar ni modificar un
cliente ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Cliente {
    string nombre;
    Fecha visita;                  // struct anidado: fecha de visita
    double respuestas[PREGUNTAS];  // los 5 datos de cada cliente
    double promedioCalificacion;   // el promedio de los 5 datos
};

Cliente clientes[MAX_CLIENTES];
```

**Un arreglo como campo de un struct.** `respuestas` es un arreglo de 5 datos que vive
**dentro** de cada cliente (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al cliente y luego el campo:

| Expresión | Qué es |
|---|---|
| `clientes[1]` | El segundo cliente completo (de tipo `Cliente`) |
| `clientes[1].nombre` | Su nombre (de tipo `string`) |
| `clientes[1].visita.mes` | El mes de su fecha de visita (de tipo `int`) |
| `clientes[1].respuestas` | Sus 5 datos (un arreglo de `double`) |
| `clientes[1].respuestas[4]` | Su dato de la columna 5 (Precio), de tipo `double` |
| `clientes[1].promedioCalificacion` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos clientes:

```
                                        respuestas       
 clientes  nombre   visita        [0]  [1]  [2]  [3]  [4]   promedioCalificacion
   [0]     Carmen   8/8/2025        9   10    8    9    9                      9
   [1]     Hugo     14/2/2026       6    7    5    8    6                    6.4
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el nombre, la fecha y los 5 datos, y en cuanto termina la captura se suman sus 5 datos y se dividen entre 5
y el resultado se guarda en `promedioCalificacion` del **mismo** cliente.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioCalificacion`; no vuelven a recorrer los 5 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos clientes hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Cliente`.
- [ ] Define `struct Cliente` con los campos `nombre` (`string`), `visita` (`Fecha`),
      `respuestas` (arreglo `double` de 5) y `promedioCalificacion` (`double`), antes de `main`.
- [ ] Los clientes se guardan en un **arreglo de structs** `Cliente clientes[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos clientes se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada cliente se guarda en su campo `promedioCalificacion` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de clientes (5), los datos por cliente (5), los límites de un
      dato válido (1 y 10), los límites del año
      (2024 y 2026) y el límite de la clasificación (8)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarSatisfaccion(double promedioCalificacion)`, que recibe el promedio (no el struct) y regresa
      `"Satisfecho"` o `"Insatisfecho"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      cliente, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los clientes cuyo mes de `visita` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara el nombre escrito con el campo `nombre` de cada
      cliente registrado y muestra **todos** los datos del que coincide: nombre,
      fecha de visita, los 5 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los clientes registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 clientes registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay clientes registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2024 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 1 y 10; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** pregunta (no se salta a la
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

Registro del primer cliente, con datos fuera de rango:

```
Opcion: 1

CLIENTE 1
  Nombre: Carmen
  Fecha de visita
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 8
    Mes: 8
    Anio: 2027
    ERROR! El anio debe estar entre 2024 y 2026
    Anio: 2025
  Preguntas
    Comida: 9
    Rapidez: 11
    ERROR! El dato debe estar entre 1 y 10
    Rapidez: 10
    Atencion: 8
    Limpieza: 9
    Precio: 9

Promedio: 9 -> Satisfecho
```

Después de registrar los 5 clientes de los casos de prueba:

```
Opcion: 2

TABLA DE CLIENTES

Nombre   Fecha          Com  Rap  Ate  Lim  Pre   Promedio
Carmen   8/8/2025         9   10    8    9    9          9   Satisfecho
Hugo     14/2/2026        6    7    5    8    6        6.4   Insatisfecho
Lucia    23/8/2026        8    8    8    8    8          8   Satisfecho
Raul     30/11/2025      10    9    7    6    7        7.8   Insatisfecho
Teresa   5/4/2026        10   10    9   10   10        9.8   Satisfecho
```

```
Opcion: 3
Mes (1 a 12): 8

CLIENTES CON FECHA DE VISITA EN EL MES 8

Carmen   8/8/2025     Promedio: 9   Satisfecho
Lucia    23/8/2026    Promedio: 8   Satisfecho
```

```
Opcion: 4
Nombre a buscar: Hugo

Nombre: Hugo
Fecha de visita: 14/2/2026
Preguntas: Com 6, Rap 7, Ate 5, Lim 8, Pre 6
Promedio: 6.4 -> Insatisfecho
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay clientes registrados; la opción 3 no pide el mes y la 4 no pide el nombre |
| 2 | Registro del cliente 1 | `Carmen`, 8/8/2025, datos 9, 10, 8, 9, 9 | Promedio 9 → Satisfecho |
| 3 | Registro del cliente 2 | `Hugo`, 14/2/2026, datos 6, 7, 5, 8, 6 | Promedio 6.4 → Insatisfecho |
| 4 | Justo en el límite | `Lucia`, 23/8/2026, datos 8, 8, 8, 8, 8 | Promedio 8 → **Satisfecho** |
| 5 | Registro del cliente 4 | `Raul`, 30/11/2025, datos 10, 9, 7, 6, 7 | Promedio 7.8 → Insatisfecho |
| 6 | Registro del cliente 5 | `Teresa`, 5/4/2026, datos 10, 10, 9, 10, 10 | Promedio 9.8 → Satisfecho |
| 7 | Tabla | Opción 2 después de los casos 2 a 6 | 5 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Mes con registros | Opción 3, mes 8 | `Carmen` (8/8/2025) y `Lucia` (23/8/2026), aunque son de años distintos |
| 9 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún cliente tiene su fecha de visita en ese mes |
| 10 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 11 | Búsqueda encontrada | Opción 4, `Hugo` | Todos sus datos: 14/2/2026; 6, 7, 5, 8, 6; promedio 6.4; Insatisfecho |
| 12 | Búsqueda no encontrada | Opción 4, `Pedro` | Aviso de que no se encontró |
| 13 | Mayúsculas distintas | Opción 4, `hugo` | Aviso de que no se encontró: `hugo` y `Hugo` son textos distintos |
| 14 | Fecha no válida | Día 0 o 32; mes 13; año 2023 o 2027 | Error; vuelve a pedir ese mismo dato |
| 15 | Dato fuera de rango | Un dato de 11 o de 0 | Error; vuelve a pedir el dato de esa misma pregunta |
| 16 | Registro lleno | Opción 1 con 5 clientes ya registrados | Aviso de registro lleno; no pide datos |
| 17 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
