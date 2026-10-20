# Evidencia 3 — Ocupación del estacionamiento por piso

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 17 — Salinas Diaz Andrea Elizabeth

## Historia de usuario

**Como** administrador del estacionamiento de un centro comercial, **quiero** registrar cada piso con su clave, la fecha de su última señalización y sus 5 mediciones de ocupación, y consultarlo por clave o por mes de señalización, **para** revisar rápido un piso y programar el repintado de los que se señalizaron en un mes.

## Contexto

En la Evidencia 2.2 los 5 datos de cada piso vivían en la matriz `ocupacion` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada piso
será un **registro** completo: su clave, su fecha de señalización, sus 5 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- El estacionamiento tiene como máximo **5 pisos**.
- De cada piso se registra su **clave**, una sola palabra sin espacios (por ejemplo `N1`), y su **fecha de señalización**: la fecha en que se pintó por última vez la señalización del piso, con día, mes y año.
- De cada piso se toman **5 mediciones** de ocupación durante la tarde.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Una medición es válida si está entre **0 y 100%**.
- Un piso se considera **lleno** si el **promedio** de sus 5 mediciones es **mayor o igual a 95%**; si es menor, está **disponible**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
OCUPACION DEL ESTACIONAMIENTO

1.- Registrar un piso
2.- Tabla de pisos
3.- Pisos por mes de senalizacion
4.- Buscar un piso
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de señalización y los 5 datos del siguiente piso y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los pisos registrados: una fila por
  piso, con su clave, su fecha de señalización, sus 5 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los pisos cuya fecha de señalización cae en ese
  mes, de cualquier año, con su clave, su fecha de señalización, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay un piso registrado con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan pisos.** El programa no permite eliminar ni modificar un
piso ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Piso {
    string clave;
    Fecha senalizacion;            // struct anidado: fecha de señalización
    double ocupacion[MEDICIONES];  // los 5 datos de cada piso
    double promedioOcupacion;      // el promedio de los 5 datos
};

Piso pisos[MAX_PISOS];
```

**Un arreglo como campo de un struct.** `ocupacion` es un arreglo de 5 datos que vive
**dentro** de cada piso (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al piso y luego el campo:

| Expresión | Qué es |
|---|---|
| `pisos[1]` | El segundo piso completo (de tipo `Piso`) |
| `pisos[1].clave` | Su clave (de tipo `string`) |
| `pisos[1].senalizacion.mes` | El mes de su fecha de señalización (de tipo `int`) |
| `pisos[1].ocupacion` | Sus 5 datos (un arreglo de `double`) |
| `pisos[1].ocupacion[4]` | Su dato de la columna 5 (Medicion 5), de tipo `double` |
| `pisos[1].promedioOcupacion` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos pisos:

```
                                          ocupacion        
 pisos     clave    senalizacion    [0]  [1]  [2]  [3]  [4]   promedioOcupacion
   [0]     N1       13/2/2024        60   75   82   90   68                  75
   [1]     N2       5/10/2025        96   98  100   94   97                  97
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 5 datos, y en cuanto termina la captura se suman sus 5 datos y se dividen entre 5
y el resultado se guarda en `promedioOcupacion` del **mismo** piso.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioOcupacion`; no vuelven a recorrer los 5 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos pisos hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Piso`.
- [ ] Define `struct Piso` con los campos `clave` (`string`), `senalizacion` (`Fecha`),
      `ocupacion` (arreglo `double` de 5) y `promedioOcupacion` (`double`), antes de `main`.
- [ ] Los pisos se guardan en un **arreglo de structs** `Piso pisos[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos pisos se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada piso se guarda en su campo `promedioOcupacion` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de pisos (5), los datos por piso (5), los límites de un
      dato válido (0 y 100), los límites del año
      (2015 y 2026) y el límite de la clasificación (95)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarOcupacion(double promedioOcupacion)`, que recibe el promedio (no el struct) y regresa
      `"Disponible"` o `"Lleno"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      piso, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los pisos cuyo mes de `senalizacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      piso registrado y muestra **todos** los datos del que coincide: clave,
      fecha de señalización, los 5 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los pisos registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 pisos registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay pisos registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2015 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** medición (no se salta a la
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

Registro del primer piso, con datos fuera de rango:

```
Opcion: 1

PISO 1
  Clave: N1
  Fecha de senalizacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 13
    Mes: 2
    Anio: 2027
    ERROR! El anio debe estar entre 2015 y 2026
    Anio: 2024
  Mediciones
    Medicion 1: 60
    Medicion 2: 105
    ERROR! El dato debe estar entre 0 y 100%
    Medicion 2: 75
    Medicion 3: 82
    Medicion 4: 90
    Medicion 5: 68

Promedio: 75% -> Disponible
```

Después de registrar los 4 pisos de los casos de prueba:

```
Opcion: 2

TABLA DE PISOS

Clave   Fecha          M1   M2   M3   M4   M5   Promedio
N1      13/2/2024      60   75   82   90   68         75   Disponible
N2      5/10/2025      96   98  100   94   97         97   Lleno
N3      28/2/2026      95   95   95   95   95         95   Lleno
N4      19/6/2023      88   92   97   99   94         94   Disponible
```

```
Opcion: 3
Mes (1 a 12): 2

PISOS CON FECHA DE SENALIZACION EN EL MES 2

N1      13/2/2024   Promedio: 75%   Disponible
N3      28/2/2026   Promedio: 95%   Lleno
```

```
Opcion: 4
Clave a buscar: N2

Clave: N2
Fecha de senalizacion: 5/10/2025
Mediciones: M1 96, M2 98, M3 100, M4 94, M5 97
Promedio: 97% -> Lleno
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay pisos registrados; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro del piso 1 | `N1`, 13/2/2024, datos 60, 75, 82, 90, 68 | Promedio 75% → Disponible |
| 3 | Registro del piso 2 | `N2`, 5/10/2025, datos 96, 98, 100, 94, 97 | Promedio 97% → Lleno |
| 4 | Justo en el límite | `N3`, 28/2/2026, datos 95, 95, 95, 95, 95 | Promedio 95% → **Lleno** |
| 5 | Registro del piso 4 | `N4`, 19/6/2023, datos 88, 92, 97, 99, 94 | Promedio 94% → Disponible |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Mes con registros | Opción 3, mes 2 | `N1` (13/2/2024) y `N3` (28/2/2026), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 11 | Aviso de que ningún piso tiene su fecha de señalización en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `N2` | Todos sus datos: 5/10/2025; 96, 98, 100, 94, 97; promedio 97%; Lleno |
| 11 | Búsqueda no encontrada | Opción 4, `N9` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `n2` | Aviso de que no se encontró: `n2` y `N2` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 2014 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 105 o de -1 | Error; vuelve a pedir el dato de esa misma medición |
| 15 | Registro lleno | Se registra `N5`, 9/12/2025, datos 40, 55, 50, 45, 60 (promedio 50, Disponible), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
