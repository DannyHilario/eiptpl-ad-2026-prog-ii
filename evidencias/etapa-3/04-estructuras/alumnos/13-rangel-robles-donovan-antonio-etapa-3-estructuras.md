# Evidencia 3 — Pruebas de tiempo de carga web

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 13 — Rangel Robles Donovan Antonio

## Historia de usuario

**Como** líder de un equipo de desarrollo web, **quiero** registrar cada página con su nombre, su fecha de publicación y sus 5 tiempos de carga, y consultarla por nombre o por mes de publicación, **para** revisar rápido una página y comparar las páginas publicadas en un mismo mes.

## Contexto

En la Evidencia 2.2 los 5 datos de cada página vivían en la matriz `tiempos` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada página
será un **registro** completo: su nombre, su fecha de publicación, sus 5 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- Se prueban como máximo **5 páginas** del sitio.
- De cada página se registra su **nombre**, una sola palabra sin espacios (por ejemplo `inicio`), y su **fecha de publicación**: la fecha en que la página se publicó en el sitio, con día, mes y año.
- Cada página se prueba **5 veces**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Un tiempo de carga es válido si está entre **0 y 60 segundos**.
- Una página es **rápida** si el **promedio** de sus 5 pruebas es **menor o igual a 3 segundos**; si no, es **lenta**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
PRUEBAS DE CARGA DEL SITIO WEB

1.- Registrar una pagina
2.- Tabla de paginas
3.- Paginas por mes de publicacion
4.- Buscar una pagina
5.- Salir
```

- **Opción 1:** pide el nombre, la fecha de publicación y los 5 datos de la siguiente página y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todas las páginas registradas: una fila por
  página, con su nombre, su fecha de publicación, sus 5 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las páginas cuya fecha de publicación cae en ese
  mes, de cualquier año, con su nombre, su fecha de publicación, su promedio y su clasificación. Si
  ninguna cumple, lo avisa.
- **Opción 4:** pide el nombre y, si hay una página registrada con ese nombre,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan páginas.** El programa no permite eliminar ni modificar una
página ya registrada: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Pagina {
    string nombre;
    Fecha publicacion;        // struct anidado: fecha de publicación
    double tiempos[PRUEBAS];  // los 5 datos de cada página
    double promedioTiempo;    // el promedio de los 5 datos
};

Pagina paginas[MAX_PAGINAS];
```

**Un arreglo como campo de un struct.** `tiempos` es un arreglo de 5 datos que vive
**dentro** de cada página (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la página y luego el campo:

| Expresión | Qué es |
|---|---|
| `paginas[1]` | La segunda página completa (de tipo `Pagina`) |
| `paginas[1].nombre` | Su nombre (de tipo `string`) |
| `paginas[1].publicacion.mes` | El mes de su fecha de publicación (de tipo `int`) |
| `paginas[1].tiempos` | Sus 5 datos (un arreglo de `double`) |
| `paginas[1].tiempos[4]` | Su dato de la columna 5 (Prueba 5), de tipo `double` |
| `paginas[1].promedioTiempo` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos páginas:

```
                                           tiempos         
 paginas   nombre    publicacion    [0]  [1]  [2]  [3]  [4]   promedioTiempo
   [0]     inicio    18/3/2020      1.5    2  1.8  2.2  2.5                2
   [1]     catalogo  6/9/2022       3.5    4  2.8  5.2  4.5                4
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan el nombre, la fecha y los 5 datos, y en cuanto termina la captura se suman sus 5 datos y se dividen entre 5
y el resultado se guarda en `promedioTiempo` de la **misma** página.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioTiempo`; no vuelven a recorrer los 5 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántas páginas hay registradas. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
la siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Pagina`.
- [ ] Define `struct Pagina` con los campos `nombre` (`string`), `publicacion` (`Fecha`),
      `tiempos` (arreglo `double` de 5) y `promedioTiempo` (`double`), antes de `main`.
- [ ] Las páginas se guardan en un **arreglo de structs** `Pagina paginas[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas páginas se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El promedio de cada página se guarda en su campo `promedioTiempo` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de páginas (5), los datos por página (5), los límites de un
      dato válido (0 y 60), los límites del año
      (2015 y 2026) y el límite de la clasificación (3)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarPagina(double promedioTiempo)`, que recibe el promedio (no el struct) y regresa
      `"Rapida"` o `"Lenta"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      página, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las páginas cuyo mes de `publicacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara el nombre escrito con el campo `nombre` de cada
      página registrada y muestra **todos** los datos de la que coincide: nombre,
      fecha de publicación, los 5 datos, su promedio y su clasificación. Si ninguna coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo las páginas registradas**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 páginas registradas, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay páginas registradas, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2015 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 60; si no, muestra
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

Registro de la primera página, con datos fuera de rango:

```
Opcion: 1

PAGINA 1
  Nombre: inicio
  Fecha de publicacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 18
    Mes: 3
    Anio: 2027
    ERROR! El anio debe estar entre 2015 y 2026
    Anio: 2020
  Pruebas
    Prueba 1: 1.5
    Prueba 2: 75
    ERROR! El dato debe estar entre 0 y 60 s
    Prueba 2: 2
    Prueba 3: 1.8
    Prueba 4: 2.2
    Prueba 5: 2.5

Promedio: 2 s -> Rapida
```

Después de registrar las 5 páginas de los casos de prueba:

```
Opcion: 2

TABLA DE PAGINAS

Nombre     Fecha           P1   P2   P3   P4   P5   Promedio
inicio     18/3/2020      1.5    2  1.8  2.2  2.5          2   Rapida
catalogo   6/9/2022       3.5    4  2.8  5.2  4.5          4   Lenta
carrito    25/3/2024        3    3    3    3    3          3   Rapida
pagos      12/12/2023     2.5  3.5    3    4    3        3.2   Lenta
contacto   4/7/2025       0.5    1  0.8  1.2  1.5          1   Rapida
```

```
Opcion: 3
Mes (1 a 12): 3

PAGINAS CON FECHA DE PUBLICACION EN EL MES 3

inicio     18/3/2020    Promedio: 2 s   Rapida
carrito    25/3/2024    Promedio: 3 s   Rapida
```

```
Opcion: 4
Nombre a buscar: catalogo

Nombre: catalogo
Fecha de publicacion: 6/9/2022
Pruebas: P1 3.5, P2 4, P3 2.8, P4 5.2, P5 4.5
Promedio: 4 s -> Lenta
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay páginas registradas; la opción 3 no pide el mes y la 4 no pide el nombre |
| 2 | Registro de la página 1 | `inicio`, 18/3/2020, datos 1.5, 2, 1.8, 2.2, 2.5 | Promedio 2 s → Rapida |
| 3 | Registro de la página 2 | `catalogo`, 6/9/2022, datos 3.5, 4, 2.8, 5.2, 4.5 | Promedio 4 s → Lenta |
| 4 | Justo en el límite | `carrito`, 25/3/2024, datos 3, 3, 3, 3, 3 | Promedio 3 s → **Rapida** |
| 5 | Registro de la página 4 | `pagos`, 12/12/2023, datos 2.5, 3.5, 3, 4, 3 | Promedio 3.2 s → Lenta |
| 6 | Registro de la página 5 | `contacto`, 4/7/2025, datos 0.5, 1, 0.8, 1.2, 1.5 | Promedio 1 s → Rapida |
| 7 | Tabla | Opción 2 después de los casos 2 a 6 | 5 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 8 | Mes con registros | Opción 3, mes 3 | `inicio` (18/3/2020) y `carrito` (25/3/2024), aunque son de años distintos |
| 9 | Mes sin registros | Opción 3, mes 11 | Aviso de que ninguna página tiene su fecha de publicación en ese mes |
| 10 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 11 | Búsqueda encontrada | Opción 4, `catalogo` | Todos sus datos: 6/9/2022; 3.5, 4, 2.8, 5.2, 4.5; promedio 4 s; Lenta |
| 12 | Búsqueda no encontrada | Opción 4, `ofertas` | Aviso de que no se encontró |
| 13 | Mayúsculas distintas | Opción 4, `CATALOGO` | Aviso de que no se encontró: `CATALOGO` y `catalogo` son textos distintos |
| 14 | Fecha no válida | Día 0 o 32; mes 13; año 2014 o 2027 | Error; vuelve a pedir ese mismo dato |
| 15 | Dato fuera de rango | Un dato de 75 o de -2 | Error; vuelve a pedir el dato de esa misma prueba |
| 16 | Registro lleno | Opción 1 con 5 páginas ya registradas | Aviso de registro lleno; no pide datos |
| 17 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
