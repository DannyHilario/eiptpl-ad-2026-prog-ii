# Evidencia 3 — Nivel de tanques de gas LP

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 14 — Rocha Ramirez Tomas De Jesus

## Historia de usuario

**Como** programador de rutas de una empresa de gas LP, **quiero** registrar cada tanque con su clave, la fecha de su última recarga y sus 3 lecturas de nivel, y consultarlo por clave o por mes de recarga, **para** contestar rápido a un cliente y revisar los tanques que se recargaron en un mes.

## Contexto

En la Evidencia 2.2 los 3 datos de cada tanque vivían en la matriz `niveles` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada tanque
será un **registro** completo: su clave, su fecha de recarga, sus 3 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- Se revisan como máximo **5 tanques**.
- De cada tanque se registra su **clave**, una sola palabra sin espacios (por ejemplo `TQ10`), y su **fecha de recarga**: la fecha en que se recargó el tanque por última vez, con día, mes y año.
- Cada tanque se lee **3 veces** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2024 y 2026**.
- Una lectura es válida si está entre **0 y 100%**.
- Un tanque tiene **nivel normal** si el **promedio** de sus 3 lecturas es **mayor o igual a 15%**; si no, tiene **nivel bajo** y hay que reabastecerlo.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
NIVEL DE TANQUES DE GAS

1.- Registrar un tanque
2.- Tabla de tanques
3.- Tanques por mes de recarga
4.- Buscar un tanque
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de recarga y los 3 datos del siguiente tanque y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los tanques registrados: una fila por
  tanque, con su clave, su fecha de recarga, sus 3 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los tanques cuya fecha de recarga cae en ese
  mes, de cualquier año, con su clave, su fecha de recarga, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay un tanque registrado con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan tanques.** El programa no permite eliminar ni modificar un
tanque ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Tanque {
    string clave;
    Fecha recarga;             // struct anidado: fecha de recarga
    double niveles[LECTURAS];  // los 3 datos de cada tanque
    double promedioNivel;      // el promedio de los 3 datos
};

Tanque tanques[MAX_TANQUES];
```

**Un arreglo como campo de un struct.** `niveles` es un arreglo de 3 datos que vive
**dentro** de cada tanque (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al tanque y luego el campo:

| Expresión | Qué es |
|---|---|
| `tanques[1]` | El segundo tanque completo (de tipo `Tanque`) |
| `tanques[1].clave` | Su clave (de tipo `string`) |
| `tanques[1].recarga.mes` | El mes de su fecha de recarga (de tipo `int`) |
| `tanques[1].niveles` | Sus 3 datos (un arreglo de `double`) |
| `tanques[1].niveles[2]` | Su dato de la columna 3 (Noche), de tipo `double` |
| `tanques[1].promedioNivel` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos tanques:

```
                                    niveles    
 tanques   clave    recarga       [0]  [1]  [2]   promedioNivel
   [0]     TQ10     2/9/2025       45   44   46              45
   [1]     TQ20     16/7/2026      12   10   11              11
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 3 datos, y en cuanto termina la captura se suman sus 3 datos y se dividen entre 3
y el resultado se guarda en `promedioNivel` del **mismo** tanque.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioNivel`; no vuelven a recorrer los 3 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos tanques hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Tanque`.
- [ ] Define `struct Tanque` con los campos `clave` (`string`), `recarga` (`Fecha`),
      `niveles` (arreglo `double` de 3) y `promedioNivel` (`double`), antes de `main`.
- [ ] Los tanques se guardan en un **arreglo de structs** `Tanque tanques[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos tanques se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada tanque se guarda en su campo `promedioNivel` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de tanques (5), los datos por tanque (3), los límites de un
      dato válido (0 y 100), los límites del año
      (2024 y 2026) y el límite de la clasificación (15)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarNivel(double promedioNivel)`, que recibe el promedio (no el struct) y regresa
      `"Nivel normal"` o `"Nivel bajo"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      tanque, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los tanques cuyo mes de `recarga` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      tanque registrado y muestra **todos** los datos del que coincide: clave,
      fecha de recarga, los 3 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los tanques registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 tanques registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay tanques registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2024 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** lectura (no se salta a la
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

Registro del primer tanque, con datos fuera de rango:

```
Opcion: 1

TANQUE 1
  Clave: TQ10
  Fecha de recarga
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 2
    Mes: 9
    Anio: 2027
    ERROR! El anio debe estar entre 2024 y 2026
    Anio: 2025
  Lecturas
    Manana: 45
    Tarde: 110
    ERROR! El dato debe estar entre 0 y 100%
    Tarde: 44
    Noche: 46

Promedio: 45% -> Nivel normal
```

Después de registrar los 4 tanques de los casos de prueba:

```
Opcion: 2

TABLA DE TANQUES

Clave   Fecha         Man  Tar  Noc   Promedio
TQ10    2/9/2025       45   44   46         45   Nivel normal
TQ20    16/7/2026      12   10   11         11   Nivel bajo
TQ30    21/9/2026      15   15   15         15   Nivel normal
TQ40    8/3/2025       14   16   14      14.67   Nivel bajo
```

```
Opcion: 3
Mes (1 a 12): 9

TANQUES CON FECHA DE RECARGA EN EL MES 9

TQ10    2/9/2025    Promedio: 45%   Nivel normal
TQ30    21/9/2026   Promedio: 15%   Nivel normal
```

```
Opcion: 4
Clave a buscar: TQ20

Clave: TQ20
Fecha de recarga: 16/7/2026
Lecturas: Man 12, Tar 10, Noc 11
Promedio: 11% -> Nivel bajo
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay tanques registrados; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro del tanque 1 | `TQ10`, 2/9/2025, datos 45, 44, 46 | Promedio 45% → Nivel normal |
| 3 | Registro del tanque 2 | `TQ20`, 16/7/2026, datos 12, 10, 11 | Promedio 11% → Nivel bajo |
| 4 | Justo en el límite | `TQ30`, 21/9/2026, datos 15, 15, 15 | Promedio 15% → **Nivel normal** |
| 5 | Registro del tanque 4 | `TQ40`, 8/3/2025, datos 14, 16, 14 | Promedio 14.67% → Nivel bajo |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Mes con registros | Opción 3, mes 9 | `TQ10` (2/9/2025) y `TQ30` (21/9/2026), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún tanque tiene su fecha de recarga en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `TQ20` | Todos sus datos: 16/7/2026; 12, 10, 11; promedio 11%; Nivel bajo |
| 11 | Búsqueda no encontrada | Opción 4, `TQ59` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `tq20` | Aviso de que no se encontró: `tq20` y `TQ20` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 2023 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 110 o de -4 | Error; vuelve a pedir el dato de esa misma lectura |
| 15 | Registro lleno | Se registra `TQ50`, 27/1/2026, datos 80, 78, 76 (promedio 78, Nivel normal), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
