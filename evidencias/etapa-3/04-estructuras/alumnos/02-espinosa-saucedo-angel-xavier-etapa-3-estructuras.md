# Evidencia 3 — Control de calidad por lotes

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 02 — Espinosa Saucedo Angel Xavier

## Historia de usuario

**Como** inspector de calidad de una fábrica de piezas metálicas, **quiero** registrar cada lote con su clave, su fecha de producción y la desviación de sus 4 piezas de muestra, y consultarlo por clave o por mes de producción, **para** rastrear rápido un lote reclamado y revisar todos los lotes fabricados en un mes con problemas.

## Contexto

En la Evidencia 2.2 los 4 datos de cada lote vivían en la matriz `desviaciones` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada lote
será un **registro** completo: su clave, su fecha de producción, sus 4 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- La fábrica registra como máximo **5 lotes** por turno.
- De cada lote se registra su **clave**, una sola palabra sin espacios (por ejemplo `L101`), y su **fecha de producción**: la fecha en que se fabricó el lote, con día, mes y año.
- De cada lote se revisan **4 piezas** de muestra.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- La desviación de una pieza es válida si está entre **0 y 50 gramos**.
- Un lote está **dentro de tolerancia** si el **promedio** de la desviación de sus 4 piezas es **menor o igual a 5 g**; si no, está **fuera de tolerancia**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
CONTROL DE CALIDAD POR LOTES

1.- Registrar un lote
2.- Tabla de lotes
3.- Lotes por mes de produccion
4.- Buscar un lote
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de producción y los 4 datos del siguiente lote y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los lotes registrados: una fila por
  lote, con su clave, su fecha de producción, sus 4 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los lotes cuya fecha de producción cae en ese
  mes, de cualquier año, con su clave, su fecha de producción, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay un lote registrado con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan lotes.** El programa no permite eliminar ni modificar un
lote ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Lote {
    string clave;
    Fecha produccion;             // struct anidado: fecha de producción
    double desviaciones[PIEZAS];  // los 4 datos de cada lote
    double promedioDesviacion;    // el promedio de los 4 datos
};

Lote lotes[MAX_LOTES];
```

**Un arreglo como campo de un struct.** `desviaciones` es un arreglo de 4 datos que vive
**dentro** de cada lote (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al lote y luego el campo:

| Expresión | Qué es |
|---|---|
| `lotes[1]` | El segundo lote completo (de tipo `Lote`) |
| `lotes[1].clave` | Su clave (de tipo `string`) |
| `lotes[1].produccion.mes` | El mes de su fecha de producción (de tipo `int`) |
| `lotes[1].desviaciones` | Sus 4 datos (un arreglo de `double`) |
| `lotes[1].desviaciones[3]` | Su dato de la columna 4 (Pieza 4), de tipo `double` |
| `lotes[1].promedioDesviacion` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos lotes:

```
                                    desviaciones    
 lotes     clave    produccion    [0]  [1]  [2]  [3]   promedioDesviacion
   [0]     L101     3/2/2026      1.5    2    3  0.5                 1.75
   [1]     L102     17/5/2025       6    8  4.5  9.5                    7
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 4 datos, y en cuanto termina la captura se suman sus 4 datos y se dividen entre 4
y el resultado se guarda en `promedioDesviacion` del **mismo** lote.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioDesviacion`; no vuelven a recorrer los 4 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos lotes hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Lote`.
- [ ] Define `struct Lote` con los campos `clave` (`string`), `produccion` (`Fecha`),
      `desviaciones` (arreglo `double` de 4) y `promedioDesviacion` (`double`), antes de `main`.
- [ ] Los lotes se guardan en un **arreglo de structs** `Lote lotes[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos lotes se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada lote se guarda en su campo `promedioDesviacion` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de lotes (5), los datos por lote (4), los límites de un
      dato válido (0 y 50), los límites del año
      (2020 y 2026) y el límite de la clasificación (5)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarLote(double promedioDesviacion)`, que recibe el promedio (no el struct) y regresa
      `"Dentro de tolerancia"` o `"Fuera de tolerancia"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      lote, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los lotes cuyo mes de `produccion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      lote registrado y muestra **todos** los datos del que coincide: clave,
      fecha de producción, los 4 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los lotes registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 lotes registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay lotes registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2020 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 50; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** pieza (no se salta a la
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

Registro del primer lote, con datos fuera de rango:

```
Opcion: 1

LOTE 1
  Clave: L101
  Fecha de produccion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 3
    Mes: 2
    Anio: 2027
    ERROR! El anio debe estar entre 2020 y 2026
    Anio: 2026
  Piezas
    Pieza 1: 1.5
    Pieza 2: 60
    ERROR! El dato debe estar entre 0 y 50 g
    Pieza 2: 2
    Pieza 3: 3
    Pieza 4: 0.5

Promedio: 1.75 g -> Dentro de tolerancia
```

Después de registrar los 3 lotes de los casos de prueba:

```
Opcion: 2

TABLA DE LOTES

Clave   Fecha          P1   P2   P3   P4   Promedio
L101    3/2/2026      1.5    2    3  0.5       1.75   Dentro de tolerancia
L102    17/5/2025       6    8  4.5  9.5          7   Fuera de tolerancia
L103    21/2/2025       5    5    5    5          5   Dentro de tolerancia
```

```
Opcion: 3
Mes (1 a 12): 2

LOTES CON FECHA DE PRODUCCION EN EL MES 2

L101    3/2/2026    Promedio: 1.75 g   Dentro de tolerancia
L103    21/2/2025   Promedio: 5 g   Dentro de tolerancia
```

```
Opcion: 4
Clave a buscar: L102

Clave: L102
Fecha de produccion: 17/5/2025
Piezas: P1 6, P2 8, P3 4.5, P4 9.5
Promedio: 7 g -> Fuera de tolerancia
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay lotes registrados; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro del lote 1 | `L101`, 3/2/2026, datos 1.5, 2, 3, 0.5 | Promedio 1.75 g → Dentro de tolerancia |
| 3 | Registro del lote 2 | `L102`, 17/5/2025, datos 6, 8, 4.5, 9.5 | Promedio 7 g → Fuera de tolerancia |
| 4 | Justo en el límite | `L103`, 21/2/2025, datos 5, 5, 5, 5 | Promedio 5 g → **Dentro de tolerancia** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 6 | Mes con registros | Opción 3, mes 2 | `L101` (3/2/2026) y `L103` (21/2/2025), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún lote tiene su fecha de producción en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `L102` | Todos sus datos: 17/5/2025; 6, 8, 4.5, 9.5; promedio 7 g; Fuera de tolerancia |
| 10 | Búsqueda no encontrada | Opción 4, `L109` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `l102` | Aviso de que no se encontró: `l102` y `L102` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 2019 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 60 o de -1 | Error; vuelve a pedir el dato de esa misma pieza |
| 14 | Registro lleno | Se registran `L104`, 8/9/2026, datos 2, 3.5, 1, 4.5 (promedio 2.75, Dentro de tolerancia); `L105`, 12/7/2024, datos 9, 7, 6, 8 (promedio 7.5, Fuera de tolerancia), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
