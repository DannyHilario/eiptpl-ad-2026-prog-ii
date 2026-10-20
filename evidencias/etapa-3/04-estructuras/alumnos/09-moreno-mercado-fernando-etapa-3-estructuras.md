# Evidencia 3 — Batería de laptops durante el día

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 09 — Moreno Mercado Fernando

## Historia de usuario

**Como** encargado del centro de cómputo, **quiero** registrar cada laptop con su clave, su fecha de compra y la carga al terminar cada una de las 4 clases, y consultarla por clave o por mes de compra, **para** revisar rápido una laptop y saber cuáles cumplen otro año de garantía en un mes.

## Contexto

En la Evidencia 2.2 los 4 datos de cada laptop vivían en la matriz `cargas` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada laptop
será un **registro** completo: su clave, su fecha de compra, sus 4 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- El centro de cómputo presta como máximo **5 laptops**.
- De cada laptop se registra su **clave**, una sola palabra sin espacios (por ejemplo `LAP01`), y su **fecha de compra**: la fecha en que la escuela compró la laptop, con día, mes y año.
- De cada laptop se registra la carga restante al terminar **4 clases**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2018 y 2026**.
- Una carga es válida si está entre **0 y 100%**.
- Una laptop tiene **batería suficiente** si el **promedio** de sus 4 cargas es **mayor o igual a 20%**; si no, tiene **batería baja**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
PRESTAMO DE LAPTOPS

1.- Registrar una laptop
2.- Tabla de laptops
3.- Laptops por mes de compra
4.- Buscar una laptop
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de compra y los 4 datos de la siguiente laptop y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todas las laptops registradas: una fila por
  laptop, con su clave, su fecha de compra, sus 4 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las laptops cuya fecha de compra cae en ese
  mes, de cualquier año, con su clave, su fecha de compra, su promedio y su clasificación. Si
  ninguna cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay una laptop registrada con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan laptops.** El programa no permite eliminar ni modificar una
laptop ya registrada: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Laptop {
    string clave;
    Fecha compra;           // struct anidado: fecha de compra
    double cargas[CLASES];  // los 4 datos de cada laptop
    double promedioCarga;   // el promedio de los 4 datos
};

Laptop laptops[MAX_LAPTOPS];
```

**Un arreglo como campo de un struct.** `cargas` es un arreglo de 4 datos que vive
**dentro** de cada laptop (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la laptop y luego el campo:

| Expresión | Qué es |
|---|---|
| `laptops[1]` | La segunda laptop completa (de tipo `Laptop`) |
| `laptops[1].clave` | Su clave (de tipo `string`) |
| `laptops[1].compra.mes` | El mes de su fecha de compra (de tipo `int`) |
| `laptops[1].cargas` | Sus 4 datos (un arreglo de `double`) |
| `laptops[1].cargas[3]` | Su dato de la columna 4 (Clase 4), de tipo `double` |
| `laptops[1].promedioCarga` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos laptops:

```
                                       cargas       
 laptops   clave    compra        [0]  [1]  [2]  [3]   promedioCarga
   [0]     LAP01    20/1/2023      80   65   50   35            57.5
   [1]     LAP02    11/8/2024      30   18   10    5           15.75
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 4 datos, y en cuanto termina la captura se suman sus 4 datos y se dividen entre 4
y el resultado se guarda en `promedioCarga` de la **misma** laptop.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioCarga`; no vuelven a recorrer los 4 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántas laptops hay registradas. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
la siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Laptop`.
- [ ] Define `struct Laptop` con los campos `clave` (`string`), `compra` (`Fecha`),
      `cargas` (arreglo `double` de 4) y `promedioCarga` (`double`), antes de `main`.
- [ ] Las laptops se guardan en un **arreglo de structs** `Laptop laptops[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas laptops se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El promedio de cada laptop se guarda en su campo `promedioCarga` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de laptops (5), los datos por laptop (4), los límites de un
      dato válido (0 y 100), los límites del año
      (2018 y 2026) y el límite de la clasificación (20)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarBateria(double promedioCarga)`, que recibe el promedio (no el struct) y regresa
      `"Bateria suficiente"` o `"Bateria baja"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      laptop, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las laptops cuyo mes de `compra` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      laptop registrada y muestra **todos** los datos de la que coincide: clave,
      fecha de compra, los 4 datos, su promedio y su clasificación. Si ninguna coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo las laptops registradas**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 laptops registradas, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay laptops registradas, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2018 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 100; si no, muestra
      un error y vuelve a pedir el dato de **esa misma** clase (no se salta a la
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

Registro de la primera laptop, con datos fuera de rango:

```
Opcion: 1

LAPTOP 1
  Clave: LAP01
  Fecha de compra
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 20
    Mes: 1
    Anio: 2027
    ERROR! El anio debe estar entre 2018 y 2026
    Anio: 2023
  Clases
    Clase 1: 80
    Clase 2: 101
    ERROR! El dato debe estar entre 0 y 100%
    Clase 2: 65
    Clase 3: 50
    Clase 4: 35

Promedio: 57.5% -> Bateria suficiente
```

Después de registrar las 3 laptops de los casos de prueba:

```
Opcion: 2

TABLA DE LAPTOPS

Clave   Fecha         C1  C2  C3  C4   Promedio
LAP01   20/1/2023     80  65  50  35       57.5   Bateria suficiente
LAP02   11/8/2024     30  18  10   5      15.75   Bateria baja
LAP03   5/1/2025      20  20  20  20         20   Bateria suficiente
```

```
Opcion: 3
Mes (1 a 12): 1

LAPTOPS CON FECHA DE COMPRA EN EL MES 1

LAP01   20/1/2023   Promedio: 57.5%   Bateria suficiente
LAP03   5/1/2025    Promedio: 20%   Bateria suficiente
```

```
Opcion: 4
Clave a buscar: LAP02

Clave: LAP02
Fecha de compra: 11/8/2024
Clases: C1 30, C2 18, C3 10, C4 5
Promedio: 15.75% -> Bateria baja
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay laptops registradas; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro de la laptop 1 | `LAP01`, 20/1/2023, datos 80, 65, 50, 35 | Promedio 57.5% → Bateria suficiente |
| 3 | Registro de la laptop 2 | `LAP02`, 11/8/2024, datos 30, 18, 10, 5 | Promedio 15.75% → Bateria baja |
| 4 | Justo en el límite | `LAP03`, 5/1/2025, datos 20, 20, 20, 20 | Promedio 20% → **Bateria suficiente** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 6 | Mes con registros | Opción 3, mes 1 | `LAP01` (20/1/2023) y `LAP03` (5/1/2025), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ninguna laptop tiene su fecha de compra en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `LAP02` | Todos sus datos: 11/8/2024; 30, 18, 10, 5; promedio 15.75%; Bateria baja |
| 10 | Búsqueda no encontrada | Opción 4, `LAP09` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `lap02` | Aviso de que no se encontró: `lap02` y `LAP02` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 2017 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 101 o de -1 | Error; vuelve a pedir el dato de esa misma clase |
| 14 | Registro lleno | Se registran `LAP04`, 17/6/2022, datos 95, 90, 70, 61 (promedio 79, Bateria suficiente); `LAP05`, 29/10/2025, datos 25, 15, 10, 6 (promedio 14, Bateria baja), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
