# Evidencia 3 — Monitoreo de CO2 en salones

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

## Historia de usuario

**Como** coordinador de mantenimiento de una escuela, **quiero** registrar cada salón con su clave, la fecha de su último mantenimiento y sus 4 lecturas de CO2, y consultarlo por clave o por mes de mantenimiento, **para** revisar rápido un salón y programar el mantenimiento de los que se atendieron en un mes.

## Contexto

En la Evidencia 2.2 los 4 datos de cada salón vivían en la matriz `lecturas` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada salón
será un **registro** completo: su clave, su fecha de mantenimiento, sus 4 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- Se revisan como máximo **5 salones**.
- De cada salón se registra su **clave**, una sola palabra sin espacios (por ejemplo `A101`), y su **fecha de mantenimiento**: la fecha del último mantenimiento del aire acondicionado del salón, con día, mes y año.
- A cada salón se le toman **4 lecturas** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- Una lectura es válida si está entre **0 y 5000 ppm**.
- Un salón está en **nivel normal** si el **promedio** de sus 4 lecturas es **menor o igual a 1000 ppm**; si no, **necesita ventilación**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
MONITOREO DE CO2

1.- Registrar un salon
2.- Tabla de salones
3.- Salones por mes de mantenimiento
4.- Buscar un salon
5.- Salir
```

- **Opción 1:** pide la clave, la fecha de mantenimiento y los 4 datos del siguiente salón y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los salones registrados: una fila por
  salón, con su clave, su fecha de mantenimiento, sus 4 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los salones cuya fecha de mantenimiento cae en ese
  mes, de cualquier año, con su clave, su fecha de mantenimiento, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide la clave y, si hay un salón registrado con esa clave,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan salones.** El programa no permite eliminar ni modificar un
salón ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Salon {
    string clave;
    Fecha mantenimiento;        // struct anidado: fecha de mantenimiento
    double lecturas[LECTURAS];  // los 4 datos de cada salón
    double promedioCO2;         // el promedio de los 4 datos
};

Salon salones[MAX_SALONES];
```

**Un arreglo como campo de un struct.** `lecturas` es un arreglo de 4 datos que vive
**dentro** de cada salón (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al salón y luego el campo:

| Expresión | Qué es |
|---|---|
| `salones[1]` | El segundo salón completo (de tipo `Salon`) |
| `salones[1].clave` | Su clave (de tipo `string`) |
| `salones[1].mantenimiento.mes` | El mes de su fecha de mantenimiento (de tipo `int`) |
| `salones[1].lecturas` | Sus 4 datos (un arreglo de `double`) |
| `salones[1].lecturas[3]` | Su dato de la columna 4 (Lectura 4), de tipo `double` |
| `salones[1].promedioCO2` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos salones:

```
                                           lecturas        
 salones   clave    mantenimiento     [0]   [1]   [2]   [3]   promedioCO2
   [0]     A101     22/5/2026         650   720   800   830           750
   [1]     A102     9/1/2025         1100  1250   980  1310          1160
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la clave, la fecha y los 4 datos, y en cuanto termina la captura se suman sus 4 datos y se dividen entre 4
y el resultado se guarda en `promedioCO2` del **mismo** salón.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioCO2`; no vuelven a recorrer los 4 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos salones hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Salon`.
- [ ] Define `struct Salon` con los campos `clave` (`string`), `mantenimiento` (`Fecha`),
      `lecturas` (arreglo `double` de 4) y `promedioCO2` (`double`), antes de `main`.
- [ ] Los salones se guardan en un **arreglo de structs** `Salon salones[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos salones se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada salón se guarda en su campo `promedioCO2` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de salones (5), los datos por salón (4), los límites de un
      dato válido (0 y 5000), los límites del año
      (2020 y 2026) y el límite de la clasificación (1000)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarCO2(double promedioCO2)`, que recibe el promedio (no el struct) y regresa
      `"Nivel normal"` o `"Necesita ventilacion"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      salón, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los salones cuyo mes de `mantenimiento` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara la clave escrita con el campo `clave` de cada
      salón registrado y muestra **todos** los datos del que coincide: clave,
      fecha de mantenimiento, los 4 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los salones registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 salones registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay salones registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2020 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 5000; si no, muestra
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

Registro del primer salón, con datos fuera de rango:

```
Opcion: 1

SALON 1
  Clave: A101
  Fecha de mantenimiento
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 22
    Mes: 5
    Anio: 2027
    ERROR! El anio debe estar entre 2020 y 2026
    Anio: 2026
  Lecturas
    Lectura 1: 650
    Lectura 2: 5200
    ERROR! El dato debe estar entre 0 y 5000 ppm
    Lectura 2: 720
    Lectura 3: 800
    Lectura 4: 830

Promedio: 750 ppm -> Nivel normal
```

Después de registrar los 3 salones de los casos de prueba:

```
Opcion: 2

TABLA DE SALONES

Clave   Fecha           L1    L2    L3    L4   Promedio
A101    22/5/2026      650   720   800   830        750   Nivel normal
A102    9/1/2025      1100  1250   980  1310       1160   Necesita ventilacion
B201    3/5/2025      1000  1000  1000  1000       1000   Nivel normal
```

```
Opcion: 3
Mes (1 a 12): 5

SALONES CON FECHA DE MANTENIMIENTO EN EL MES 5

A101    22/5/2026   Promedio: 750 ppm   Nivel normal
B201    3/5/2025    Promedio: 1000 ppm   Nivel normal
```

```
Opcion: 4
Clave a buscar: A102

Clave: A102
Fecha de mantenimiento: 9/1/2025
Lecturas: L1 1100, L2 1250, L3 980, L4 1310
Promedio: 1160 ppm -> Necesita ventilacion
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay salones registrados; la opción 3 no pide el mes y la 4 no pide la clave |
| 2 | Registro del salón 1 | `A101`, 22/5/2026, datos 650, 720, 800, 830 | Promedio 750 ppm → Nivel normal |
| 3 | Registro del salón 2 | `A102`, 9/1/2025, datos 1100, 1250, 980, 1310 | Promedio 1160 ppm → Necesita ventilacion |
| 4 | Justo en el límite | `B201`, 3/5/2025, datos 1000, 1000, 1000, 1000 | Promedio 1000 ppm → **Nivel normal** |
| 5 | Tabla | Opción 2 después de los casos 2 a 4 | 3 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 6 | Mes con registros | Opción 3, mes 5 | `A101` (22/5/2026) y `B201` (3/5/2025), aunque son de años distintos |
| 7 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún salón tiene su fecha de mantenimiento en ese mes |
| 8 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 9 | Búsqueda encontrada | Opción 4, `A102` | Todos sus datos: 9/1/2025; 1100, 1250, 980, 1310; promedio 1160 ppm; Necesita ventilacion |
| 10 | Búsqueda no encontrada | Opción 4, `C309` | Aviso de que no se encontró |
| 11 | Mayúsculas distintas | Opción 4, `a102` | Aviso de que no se encontró: `a102` y `A102` son textos distintos |
| 12 | Fecha no válida | Día 0 o 32; mes 13; año 2019 o 2027 | Error; vuelve a pedir ese mismo dato |
| 13 | Dato fuera de rango | Un dato de 5200 o de -10 | Error; vuelve a pedir el dato de esa misma lectura |
| 14 | Registro lleno | Se registran `B202`, 14/8/2026, datos 500, 600, 550, 650 (promedio 575, Nivel normal); `C301`, 30/3/2024, datos 1400, 1500, 1200, 1300 (promedio 1350, Necesita ventilacion), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 15 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
