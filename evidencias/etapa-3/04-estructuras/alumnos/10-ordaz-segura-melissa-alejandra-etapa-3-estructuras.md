# Evidencia 3 — Turbidez del agua por punto de muestreo

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 10 — Ordaz Segura Melissa Alejandra

## Historia de usuario

**Como** químico de una planta potabilizadora, **quiero** registrar cada punto de muestreo con su clave, la fecha de su última limpieza y sus 4 muestras de turbidez, y consultarlo por clave o por mes de limpieza, **para** revisar rápido un punto y programar la limpieza de los filtros que se limpiaron en un mes.

## Contexto

En la Evidencia 2.2 los 4 datos de cada punto de muestreo vivían en la matriz `muestras` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada punto de muestreo
será un **registro** completo: su clave, su fecha de limpieza, sus 4 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- La planta revisa como máximo **5 puntos de muestreo**.
- De cada punto de muestreo se registra su **clave**, una sola palabra sin espacios (por ejemplo `PM1`), y su **fecha de limpieza**: la fecha en que se limpiaron por última vez los filtros de ese punto, con día, mes y año.
- De cada punto se toman **4 muestras** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2022 y 2026**.
- Una muestra es válida si su turbidez está entre **0 y 100 NTU**.
- El agua de un punto es **apta** si el **promedio** de sus 4 muestras es **menor o igual a 5 NTU**; si no, **no es apta**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
CALIDAD DEL AGUA

1.- Registrar un punto de muestreo
2.- Tabla de puntos de muestreo
3.- Puntos de muestreo por mes de limpieza
4.- Buscar un punto de muestreo
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de limpieza y los 4 datos del siguiente punto de muestreo y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los puntos de muestreo registrados: una fila por
  punto de muestreo, con su clave, su fecha de limpieza, sus 4 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los puntos de muestreo cuya fecha de limpieza cae en ese
  mes, de cualquier año, con su clave, su fecha de limpieza, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay un punto de muestreo registrado con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan puntos de muestreo.** El programa no permite eliminar ni modificar un
punto de muestreo ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct PuntoMuestreo {
    string clave;
    Fecha limpieza;             // struct anidado: fecha de limpieza
    double muestras[MUESTRAS];  // los 4 datos de cada punto de muestreo
    double promedioTurbidez;    // el promedio de los 4 datos
};

PuntoMuestreo puntos[MAX_PUNTOS];
```

**Un arreglo como campo de un struct.** `muestras` es un arreglo de 4 datos que vive
**dentro** de cada punto de muestreo (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al punto de muestreo y luego el campo:

| Expresión | Qué es |
|---|---|
| `puntos[1]` | El segundo punto de muestreo completo (de tipo `PuntoMuestreo`) |
| `puntos[1].clave` | Su clave (de tipo `string`) |
| `puntos[1].limpieza.mes` | El mes de su fecha de limpieza (de tipo `int`) |
| `puntos[1].muestras` | Sus 4 datos (un arreglo de `double`) |
| `puntos[1].muestras[3]` | Su dato de la columna 4 (Muestra 4), de tipo `double` |
| `puntos[1].promedioTurbidez` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos puntos de muestreo:

```
                                      muestras      
 puntos    clave    limpieza      [0]  [1]  [2]  [3]   promedioTurbidez
   [0]     PM1      6/10/2025     1.2  0.8    2    1               1.25
   [1]     PM2      19/4/2026     7.5    6    9  5.5                  7
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 4 datos, y en cuanto termina la captura se suman sus 4 datos y se dividen entre 4
y el resultado se guarda en `promedioTurbidez` del **mismo** punto de muestreo.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioTurbidez`; no vuelven a recorrer los 4 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos puntos de muestreo hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct PuntoMuestreo`.
- [ ] Define `struct PuntoMuestreo` con los campos `clave` (`string`), `limpieza` (`Fecha`),
      `muestras` (arreglo `double` de 4) y `promedioTurbidez` (`double`), antes de `main`.
- [ ] Los puntos de muestreo se guardan en un **arreglo de structs** `PuntoMuestreo puntos[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos puntos de muestreo se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada punto de muestreo se guarda en su campo `promedioTurbidez` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de puntos de muestreo (5), los datos por punto de muestreo (4), los límites de un
      dato válido (0 y 100), los límites del año
      (2022 y 2026) y el límite de la clasificación (5)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarAgua(double promedioTurbidez)`, que recibe el promedio (no el struct) y regresa
      `"Agua apta"` o `"Agua no apta"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      punto de muestreo, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los puntos de muestreo cuyo mes de `limpieza` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      punto de muestreo registrado y muestra **todos** los datos del que coincide: clave,
      fecha de limpieza, los 4 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los puntos de muestreo registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 puntos de muestreo registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay puntos de muestreo registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2022 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** muestra (no se salta a la
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

Registro del primer punto de muestreo, con datos fuera de rango:

```
Opcion: 1

PUNTO DE MUESTREO 1
  Clave: PM1
  Fecha de limpieza
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 6
    Mes: 10
    Anio: 2027
    ERROR! El anio debe estar entre 2022 y 2026
    Anio: 2025
  Muestras
    Muestra 1: 1.2
    Muestra 2: 120
    ERROR! El dato debe estar entre 0 y 100 NTU
    Muestra 2: 0.8
    Muestra 3: 2
    Muestra 4: 1

Promedio: 1.25 NTU -> Agua apta
```

Después de registrar los 3 puntos de muestreo de los casos de prueba:

```
Opcion: 2

TABLA DE PUNTOS DE MUESTREO

Clave   Fecha           M1   M2   M3   M4   Promedio
PM1     6/10/2025      1.2  0.8    2    1       1.25   Agua apta
PM2     19/4/2026      7.5    6    9  5.5          7   Agua no apta
PM3     13/10/2026       5    5    5    5          5   Agua apta
```

```
Opcion: 3
Mes (1 a 12): 10

PUNTOS DE MUESTREO CON FECHA DE LIMPIEZA EN EL MES 10

PM1     6/10/2025    Promedio: 1.25 NTU   Agua apta
PM3     13/10/2026   Promedio: 5 NTU   Agua apta
```

```
Opcion: 4
Clave a buscar: PM2

Clave: PM2
Fecha de limpieza: 19/4/2026
Muestras: M1 7.5, M2 6, M3 9, M4 5.5
Promedio: 7 NTU -> Agua no apta
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay puntos de muestreo registrados; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro del punto de muestreo 1 | `PM1`, 6/10/2025, datos 1.2, 0.8, 2, 1 | Promedio 1.25 NTU → Agua apta |
| 3 | Registro del punto de muestreo 2 | `PM2`, 19/4/2026, datos 7.5, 6, 9, 5.5 | Promedio 7 NTU → Agua no apta |
| 4 | Justo en el límite | `PM3`, 13/10/2026, datos 5, 5, 5, 5 | Promedio 5 NTU → **Agua apta** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 6 | Mes con registros | Opción 3, mes 10 | `PM1` (6/10/2025) y `PM3` (13/10/2026), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún punto de muestreo tiene su fecha de limpieza en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `PM2` | Todos sus datos: 19/4/2026; 7.5, 6, 9, 5.5; promedio 7 NTU; Agua no apta |
| 10 | Búsqueda no encontrada | Opción 4, `PM9` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `pm2` | Aviso de que no se encontró: `pm2` y `PM2` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 2021 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 120 o de -0.5 | Error; vuelve a pedir el dato de esa misma muestra |
| 14 | Registro lleno | Se registran `PM4`, 2/7/2025, datos 2, 2.5, 3, 1.5 (promedio 2.25, Agua apta); `PM5`, 24/1/2026, datos 12, 8, 10, 14 (promedio 11, Agua no apta), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
