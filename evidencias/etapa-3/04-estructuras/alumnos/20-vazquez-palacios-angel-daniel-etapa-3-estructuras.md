# Evidencia 3 — Vibración de maquinaria industrial

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 20 — Vazquez Palacios Angel Daniel

## Historia de usuario

**Como** jefe de mantenimiento de una planta industrial, **quiero** registrar cada máquina con su clave, la fecha de su último mantenimiento y sus 3 lecturas de vibración, y consultarla por clave o por mes de mantenimiento, **para** revisar rápido una máquina y programar el siguiente mantenimiento de las que se atendieron en un mes.

## Contexto

En la Evidencia 2.2 los 3 datos de cada máquina vivían en la matriz `vibraciones` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada máquina
será un **registro** completo: su clave, su fecha de mantenimiento, sus 3 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- La planta tiene como máximo **5 máquinas** en monitoreo.
- De cada máquina se registra su **clave**, una sola palabra sin espacios (por ejemplo `CNC01`), y su **fecha de mantenimiento**: la fecha del último mantenimiento de la máquina, con día, mes y año.
- Cada máquina se mide **3 veces** por turno.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2018 y 2026**.
- Una lectura es válida si está entre **0 y 50 mm/s**.
- Una máquina está en **estado normal** si el **promedio** de sus 3 lecturas es **menor o igual a 4.5 mm/s**; si no, está en **estado de alerta**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
MONITOREO DE VIBRACION

1.- Registrar una maquina
2.- Tabla de maquinas
3.- Maquinas por mes de mantenimiento
4.- Buscar una maquina
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de mantenimiento y los 3 datos de la siguiente máquina y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todas las máquinas registradas: una fila por
  máquina, con su clave, su fecha de mantenimiento, sus 3 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las máquinas cuya fecha de mantenimiento cae en ese
  mes, de cualquier año, con su clave, su fecha de mantenimiento, su promedio y su clasificación. Si
  ninguna cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay una máquina registrada con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan máquinas.** El programa no permite eliminar ni modificar una
máquina ya registrada: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Maquina {
    string clave;
    Fecha mantenimiento;           // struct anidado: fecha de mantenimiento
    double vibraciones[LECTURAS];  // los 3 datos de cada máquina
    double promedioVibracion;      // el promedio de los 3 datos
};

Maquina maquinas[MAX_MAQUINAS];
```

**Un arreglo como campo de un struct.** `vibraciones` es un arreglo de 3 datos que vive
**dentro** de cada máquina (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la máquina y luego el campo:

| Expresión | Qué es |
|---|---|
| `maquinas[1]` | La segunda máquina completa (de tipo `Maquina`) |
| `maquinas[1].clave` | Su clave (de tipo `string`) |
| `maquinas[1].mantenimiento.mes` | El mes de su fecha de mantenimiento (de tipo `int`) |
| `maquinas[1].vibraciones` | Sus 3 datos (un arreglo de `double`) |
| `maquinas[1].vibraciones[2]` | Su dato de la columna 3 (Lectura 3), de tipo `double` |
| `maquinas[1].promedioVibracion` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos máquinas:

```
                                     vibraciones  
 maquinas  clave    mantenimiento    [0]  [1]  [2]   promedioVibracion
   [0]     CNC01    5/7/2025         2.5    3    2                 2.5
   [1]     CNC02    18/2/2026          6  5.5    7                6.17
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 3 datos, y en cuanto termina la captura se suman sus 3 datos y se dividen entre 3
y el resultado se guarda en `promedioVibracion` de la **misma** máquina.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioVibracion`; no vuelven a recorrer los 3 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántas máquinas hay registradas. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
la siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Maquina`.
- [ ] Define `struct Maquina` con los campos `clave` (`string`), `mantenimiento` (`Fecha`),
      `vibraciones` (arreglo `double` de 3) y `promedioVibracion` (`double`), antes de `main`.
- [ ] Las máquinas se guardan en un **arreglo de structs** `Maquina maquinas[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas máquinas se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El promedio de cada máquina se guarda en su campo `promedioVibracion` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de máquinas (5), los datos por máquina (3), los límites de un
      dato válido (0 y 50), los límites del año
      (2018 y 2026) y el límite de la clasificación (4.5)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarVibracion(double promedioVibracion)`, que recibe el promedio (no el struct) y regresa
      `"Estado normal"` o `"Estado de alerta"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      máquina, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las máquinas cuyo mes de `mantenimiento` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      máquina registrada y muestra **todos** los datos de la que coincide: clave,
      fecha de mantenimiento, los 3 datos, su promedio y su clasificación. Si ninguna coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo las máquinas registradas**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 máquinas registradas, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay máquinas registradas, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2018 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 50; si no, muestra
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

Registro de la primera máquina, con datos fuera de rango:

```
Opcion: 1

MAQUINA 1
  Clave: CNC01
  Fecha de mantenimiento
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 5
    Mes: 7
    Anio: 2027
    ERROR! El anio debe estar entre 2018 y 2026
    Anio: 2025
  Lecturas
    Lectura 1: 2.5
    Lectura 2: 60
    ERROR! El dato debe estar entre 0 y 50 mm/s
    Lectura 2: 3
    Lectura 3: 2

Promedio: 2.5 mm/s -> Estado normal
```

Después de registrar las 4 máquinas de los casos de prueba:

```
Opcion: 2

TABLA DE MAQUINAS

Clave   Fecha          L1   L2   L3   Promedio
CNC01   5/7/2025      2.5    3    2        2.5   Estado normal
CNC02   18/2/2026       6  5.5    7       6.17   Estado de alerta
CNC03   22/7/2026     4.5  4.5  4.5        4.5   Estado normal
CNC04   9/10/2024       5    4    6          5   Estado de alerta
```

```
Opcion: 3
Mes (1 a 12): 7

MAQUINAS CON FECHA DE MANTENIMIENTO EN EL MES 7

CNC01   5/7/2025    Promedio: 2.5 mm/s   Estado normal
CNC03   22/7/2026   Promedio: 4.5 mm/s   Estado normal
```

```
Opcion: 4
Clave a buscar: CNC02

Clave: CNC02
Fecha de mantenimiento: 18/2/2026
Lecturas: L1 6, L2 5.5, L3 7
Promedio: 6.17 mm/s -> Estado de alerta
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay máquinas registradas; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro de la máquina 1 | `CNC01`, 5/7/2025, datos 2.5, 3, 2 | Promedio 2.5 mm/s → Estado normal |
| 3 | Registro de la máquina 2 | `CNC02`, 18/2/2026, datos 6, 5.5, 7 | Promedio 6.17 mm/s → Estado de alerta |
| 4 | Justo en el límite | `CNC03`, 22/7/2026, datos 4.5, 4.5, 4.5 | Promedio 4.5 mm/s → **Estado normal** |
| 5 | Registro de la máquina 4 | `CNC04`, 9/10/2024, datos 5, 4, 6 | Promedio 5 mm/s → Estado de alerta |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Mes con registros | Opción 3, mes 7 | `CNC01` (5/7/2025) y `CNC03` (22/7/2026), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 12 | Aviso de que ninguna máquina tiene su fecha de mantenimiento en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `CNC02` | Todos sus datos: 18/2/2026; 6, 5.5, 7; promedio 6.17 mm/s; Estado de alerta |
| 11 | Búsqueda no encontrada | Opción 4, `CNC09` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `cnc02` | Aviso de que no se encontró: `cnc02` y `CNC02` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 2017 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 60 o de -1 | Error; vuelve a pedir el dato de esa misma lectura |
| 15 | Registro lleno | Se registra `CNC05`, 30/4/2025, datos 1.5, 2, 1 (promedio 1.5, Estado normal), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |

Los resultados están redondeados a 2 decimales; `cout` sin formato puede mostrar más o menos decimales.
