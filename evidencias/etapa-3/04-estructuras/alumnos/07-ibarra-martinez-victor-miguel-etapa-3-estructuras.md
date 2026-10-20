# Evidencia 3 — Monitoreo de ruido industrial

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 07 — Ibarra Martinez Victor Miguel

## Historia de usuario

**Como** supervisor de seguridad de una planta industrial, **quiero** registrar cada máquina con su clave, su fecha de instalación y sus 4 lecturas de ruido, y consultarla por clave o por mes de instalación, **para** revisar rápido una máquina y programar el mantenimiento anual de las que se instalaron en un mes.

## Contexto

En la Evidencia 2.2 los 4 datos de cada máquina vivían en la matriz `lecturas` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada máquina
será un **registro** completo: su clave, su fecha de instalación, sus 4 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- La planta tiene como máximo **5 máquinas**.
- De cada máquina se registra su **clave**, una sola palabra sin espacios (por ejemplo `MQ01`), y su **fecha de instalación**: la fecha en que se instaló la máquina en la planta, con día, mes y año.
- Cada máquina se mide **4 veces** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2000 y 2026**.
- Una lectura es válida si está entre **0 y 140 dB**.
- Una máquina está **dentro de la norma** si el **promedio** de sus 4 lecturas es **menor o igual a 85 dB**; si no, **excede la norma**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
MONITOREO DE RUIDO INDUSTRIAL

1.- Registrar una maquina
2.- Tabla de maquinas
3.- Maquinas por mes de instalacion
4.- Buscar una maquina
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de instalación y los 4 datos de la siguiente máquina y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todas las máquinas registradas: una fila por
  máquina, con su clave, su fecha de instalación, sus 4 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra las máquinas cuya fecha de instalación cae en ese
  mes, de cualquier año, con su clave, su fecha de instalación, su promedio y su clasificación. Si
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
    Fecha instalacion;          // struct anidado: fecha de instalación
    double lecturas[LECTURAS];  // los 4 datos de cada máquina
    double promedioRuido;       // el promedio de los 4 datos
};

Maquina maquinas[MAX_MAQUINAS];
```

**Un arreglo como campo de un struct.** `lecturas` es un arreglo de 4 datos que vive
**dentro** de cada máquina (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige a la máquina y luego el campo:

| Expresión | Qué es |
|---|---|
| `maquinas[1]` | La segunda máquina completa (de tipo `Maquina`) |
| `maquinas[1].clave` | Su clave (de tipo `string`) |
| `maquinas[1].instalacion.mes` | El mes de su fecha de instalación (de tipo `int`) |
| `maquinas[1].lecturas` | Sus 4 datos (un arreglo de `double`) |
| `maquinas[1].lecturas[3]` | Su dato de la columna 4 (Lectura 4), de tipo `double` |
| `maquinas[1].promedioRuido` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos máquinas:

```
                                       lecturas      
 maquinas  clave    instalacion    [0]  [1]  [2]  [3]   promedioRuido
   [0]     MQ01     12/9/2015       82   88   79   85            83.5
   [1]     MQ02     3/3/2020        90   92   87   95              91
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 4 datos, y en cuanto termina la captura se suman sus 4 datos y se dividen entre 4
y el resultado se guarda en `promedioRuido` de la **misma** máquina.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioRuido`; no vuelven a recorrer los 4 datos para calcularlo.

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
- [ ] Define `struct Maquina` con los campos `clave` (`string`), `instalacion` (`Fecha`),
      `lecturas` (arreglo `double` de 4) y `promedioRuido` (`double`), antes de `main`.
- [ ] Las máquinas se guardan en un **arreglo de structs** `Maquina maquinas[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántas máquinas se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda la siguiente.
- [ ] El promedio de cada máquina se guarda en su campo `promedioRuido` al registrarla, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de máquinas (5), los datos por máquina (4), los límites de un
      dato válido (0 y 140), los límites del año
      (2000 y 2026) y el límite de la clasificación (85)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarRuido(double promedioRuido)`, que recibe el promedio (no el struct) y regresa
      `"Dentro de la norma"` o `"Excede la norma"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      máquina, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** las máquinas cuyo mes de `instalacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguna.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      máquina registrada y muestra **todos** los datos de la que coincide: clave,
      fecha de instalación, los 4 datos, su promedio y su clasificación. Si ninguna coincide,
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
      2000 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 140; si no, muestra
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
  Clave: MQ01
  Fecha de instalacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 12
    Mes: 9
    Anio: 2027
    ERROR! El anio debe estar entre 2000 y 2026
    Anio: 2015
  Lecturas
    Lectura 1: 82
    Lectura 2: 150
    ERROR! El dato debe estar entre 0 y 140 dB
    Lectura 2: 88
    Lectura 3: 79
    Lectura 4: 85

Promedio: 83.5 dB -> Dentro de la norma
```

Después de registrar las 3 máquinas de los casos de prueba:

```
Opcion: 2

TABLA DE MAQUINAS

Clave   Fecha         L1  L2  L3  L4   Promedio
MQ01    12/9/2015     82  88  79  85       83.5   Dentro de la norma
MQ02    3/3/2020      90  92  87  95         91   Excede la norma
MQ03    28/9/2022     85  85  85  85         85   Dentro de la norma
```

```
Opcion: 3
Mes (1 a 12): 9

MAQUINAS CON FECHA DE INSTALACION EN EL MES 9

MQ01    12/9/2015   Promedio: 83.5 dB   Dentro de la norma
MQ03    28/9/2022   Promedio: 85 dB   Dentro de la norma
```

```
Opcion: 4
Clave a buscar: MQ02

Clave: MQ02
Fecha de instalacion: 3/3/2020
Lecturas: L1 90, L2 92, L3 87, L4 95
Promedio: 91 dB -> Excede la norma
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay máquinas registradas; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro de la máquina 1 | `MQ01`, 12/9/2015, datos 82, 88, 79, 85 | Promedio 83.5 dB → Dentro de la norma |
| 3 | Registro de la máquina 2 | `MQ02`, 3/3/2020, datos 90, 92, 87, 95 | Promedio 91 dB → Excede la norma |
| 4 | Justo en el límite | `MQ03`, 28/9/2022, datos 85, 85, 85, 85 | Promedio 85 dB → **Dentro de la norma** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 6 | Mes con registros | Opción 3, mes 9 | `MQ01` (12/9/2015) y `MQ03` (28/9/2022), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 11 | Aviso de que ninguna máquina tiene su fecha de instalación en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `MQ02` | Todos sus datos: 3/3/2020; 90, 92, 87, 95; promedio 91 dB; Excede la norma |
| 10 | Búsqueda no encontrada | Opción 4, `MQ09` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `mq02` | Aviso de que no se encontró: `mq02` y `MQ02` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 1999 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 150 o de -5 | Error; vuelve a pedir el dato de esa misma lectura |
| 14 | Registro lleno | Se registran `MQ04`, 6/12/2010, datos 70, 75, 72, 79 (promedio 74, Dentro de la norma); `MQ05`, 19/5/2018, datos 100, 98, 104, 94 (promedio 99, Excede la norma), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
