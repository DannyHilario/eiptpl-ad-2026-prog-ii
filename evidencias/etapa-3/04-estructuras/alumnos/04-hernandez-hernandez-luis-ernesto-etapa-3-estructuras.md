# Evidencia 3 — Radares de velocidad en un tramo

*Etapa III — Estructuras · Evidencia de Aprendizaje 3: Programa · Entrega: jueves 22 de octubre de 2026, 7:40 p.m. · [Instrucciones generales y rúbrica](../descripcion.md)*

**Alumno:** 04 — Hernández Hernández Luis Ernesto

## Historia de usuario

**Como** agente de tránsito de una carretera, **quiero** registrar cada vehículo con su placa, su fecha de verificación y las velocidades de los 3 radares, y consultarlo por placa o por mes de verificación, **para** atender rápido a un conductor que pregunta por su multa y avisar a quienes les toca verificar en un mes.

## Contexto

En la Evidencia 2.2 los 3 datos de cada vehículo vivían en la matriz `velocidades` y su promedio
en el vector `promedios`, y lo único que los unía era el número de fila. Ahora cada vehículo
será un **registro** completo: su placa, su fecha de verificación, sus 3 datos y su promedio viajan
juntos en un `struct`.

**Reglas**

- Se registran como máximo **5 vehículos**.
- De cada vehículo se registra su **placa**, una sola palabra sin espacios (por ejemplo `ABC123`), y su **fecha de verificación**: la fecha de su última verificación vehicular, con día, mes y año.
- Cada vehículo pasa por **3 radares** a lo largo del tramo.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Una velocidad es válida si está entre **0 y 250 km/h**.
- Un vehículo va **dentro del límite** si el **promedio** de sus 3 velocidades es **menor o igual a 80 km/h**; si no, va **en exceso de velocidad**.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 5:

```
RADARES DEL TRAMO CARRETERO

1.- Registrar un vehiculo
2.- Tabla de vehiculos
3.- Vehiculos por mes de verificacion
4.- Buscar un vehiculo
5.- Salir
```

- **Opción 1:** pide la placa, la fecha de verificación y los 3 datos del siguiente vehículo y, al
  terminar, muestra su promedio y su clasificación.
- **Opción 2:** muestra la tabla de todos los vehículos registrados: una fila por
  vehículo, con su placa, su fecha de verificación, sus 3 datos, su promedio y su clasificación.
- **Opción 3:** pide un mes (1 a 12) y muestra los vehículos cuya fecha de verificación cae en ese
  mes, de cualquier año, con su placa, su fecha de verificación, su promedio y su clasificación. Si
  ninguno cumple, lo avisa.
- **Opción 4:** pide la placa y, si hay un vehículo registrado con esa placa,
  muestra **todos** sus datos; si no, avisa que no se encontró.
- **Opción 5:** termina el programa.

**Solo se agregan vehículos.** El programa no permite eliminar ni modificar un
vehículo ya registrado: cada vez que eliges la opción 1 se ocupa la siguiente
posición libre del arreglo, hasta llenar las 5.

## Cómo se organizan los datos

Tu programa usa **dos structs**, uno dentro del otro, y **un arreglo de structs**:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Vehiculo {
    string placa;
    Fecha verificacion;           // struct anidado: fecha de verificación
    double velocidades[RADARES];  // los 3 datos de cada vehículo
    double promedioVelocidad;     // el promedio de los 3 datos
};

Vehiculo vehiculos[MAX_VEHICULOS];
```

**Un arreglo como campo de un struct.** `velocidades` es un arreglo de 3 datos que vive
**dentro** de cada vehículo (ver
[3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md#un-arreglo-dentro-de-un-struct)).
Se usa igual que cualquier arreglo, pero primero se elige al vehículo y luego el campo:

| Expresión | Qué es |
|---|---|
| `vehiculos[1]` | El segundo vehículo completo (de tipo `Vehiculo`) |
| `vehiculos[1].placa` | Su placa (de tipo `string`) |
| `vehiculos[1].verificacion.mes` | El mes de su fecha de verificación (de tipo `int`) |
| `vehiculos[1].velocidades` | Sus 3 datos (un arreglo de `double`) |
| `vehiculos[1].velocidades[2]` | Su dato de la columna 3 (Radar 3), de tipo `double` |
| `vehiculos[1].promedioVelocidad` | Su promedio (de tipo `double`) |

Por ejemplo, después de registrar dos vehículos:

```
                                    velocidades  
 vehiculos placa    verificacion    [0]  [1]  [2]   promedioVelocidad
   [0]     ABC123   14/4/2025        72   78   75                  75
   [1]     XYZ789   30/9/2026        95  102   88                  95
   [2]     (libre)
   [3]     (libre)
   [4]     (libre)
```

**¿Cuándo se llena cada campo?** Todos se llenan en la **opción 1**: primero se
capturan la placa, la fecha y los 3 datos, y en cuanto termina la captura se suman sus 3 datos y se dividen entre 3
y el resultado se guarda en `promedioVelocidad` del **mismo** vehículo.

**¿Para qué guardar el promedio?** Para no calcularlo otra vez. Las opciones 2, 3 y 4
**leen** `promedioVelocidad`; no vuelven a recorrer los 3 datos para calcularlo.

**¿Para qué sirve el contador?** Igual que en la Evidencia 2.2, un contador lleva
cuántos vehículos hay registrados. Si hay `n`, ocupan las posiciones `0` a `n - 1`,
el siguiente se guarda en la posición `n`, y las opciones 2, 3 y 4 recorren solo
hasta `n - 1`.

## Criterios de aceptación

Están agrupados según los tres criterios de la
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Uso de estructuras

- [ ] Define `struct Fecha` con los campos `dia`, `mes` y `anio` (`int`), **antes**
      de `struct Vehiculo`.
- [ ] Define `struct Vehiculo` con los campos `placa` (`string`), `verificacion` (`Fecha`),
      `velocidades` (arreglo `double` de 3) y `promedioVelocidad` (`double`), antes de `main`.
- [ ] Los vehículos se guardan en un **arreglo de structs** `Vehiculo vehiculos[5]`,
      declarado con la constante del máximo.
- [ ] Un contador lleva cuántos vehículos se han registrado; ese mismo contador
      indica en qué posición del arreglo se guarda el siguiente.
- [ ] El promedio de cada vehículo se guarda en su campo `promedioVelocidad` al registrarlo, y
      las opciones 2, 3 y 4 lo **leen** de ahí; no lo vuelven a calcular.
- [ ] El máximo de vehículos (5), los datos por vehículo (3), los límites de un
      dato válido (0 y 250), los límites del año
      (2015 y 2026) y el límite de la clasificación (80)
      son constantes con nombre.
- [ ] La clasificación la decide una función **pura**
      `string clasificarVelocidad(double promedioVelocidad)`, que recibe el promedio (no el struct) y regresa
      `"Dentro del limite"` o `"Exceso de velocidad"`, sin `cin` ni `cout`.

### Habilidades (5 puntos) — Almacenar, consultar y validar los registros

**Almacena y consulta correctamente**

- [ ] La tabla de la opción 2 muestra exactamente los datos capturados de cada
      vehículo, en el orden en que se registraron.
- [ ] La opción 3 muestra **solo** los vehículos cuyo mes de `verificacion` es el mes
      pedido, sin importar el año, y avisa si no hay ninguno.
- [ ] La opción 4 compara la placa escrita con el campo `placa` de cada
      vehículo registrado y muestra **todos** los datos del que coincide: placa,
      fecha de verificación, los 3 datos, su promedio y su clasificación. Si ninguno coincide,
      avisa que no se encontró.
- [ ] Las opciones 2, 3 y 4 recorren **solo los vehículos registrados**, no las
      5 posiciones del arreglo.
- [ ] Si ya hay 5 vehículos registrados, la opción 1 avisa que el registro
      está lleno y **no** pide datos ni guarda nada fuera del arreglo.
- [ ] Si todavía no hay vehículos registrados, las opciones 2, 3 y 4 muestran un
      aviso en lugar de la tabla o de pedir datos.

**Valida los datos**

- [ ] La opción del menú debe estar entre 1 y 5; si no, muestra un error y vuelve
      a mostrar el menú.
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año entre
      2015 y 2026; si alguno no es válido, muestra un error y vuelve a
      pedir **ese mismo** dato.
- [ ] Cada dato debe estar entre 0 y 250; si no, muestra
      un error y vuelve a pedir el dato de **ese mismo** radar (no se salta a la
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

Registro del primer vehículo, con datos fuera de rango:

```
Opcion: 1

VEHICULO 1
  Placa: ABC123
  Fecha de verificacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 14
    Mes: 4
    Anio: 2027
    ERROR! El anio debe estar entre 2015 y 2026
    Anio: 2025
  Radares
    Radar 1: 72
    Radar 2: 300
    ERROR! El dato debe estar entre 0 y 250 km/h
    Radar 2: 78
    Radar 3: 75

Promedio: 75 km/h -> Dentro del limite
```

Después de registrar los 4 vehículos de los casos de prueba:

```
Opcion: 2

TABLA DE VEHICULOS

Placa    Fecha          R1   R2   R3   Promedio
ABC123   14/4/2025      72   78   75         75   Dentro del limite
XYZ789   30/9/2026      95  102   88         95   Exceso de velocidad
MNL456   7/4/2026       80   80   80         80   Dentro del limite
RTS321   21/1/2024      85   79   82         82   Exceso de velocidad
```

```
Opcion: 3
Mes (1 a 12): 4

VEHICULOS CON FECHA DE VERIFICACION EN EL MES 4

ABC123   14/4/2025   Promedio: 75 km/h   Dentro del limite
MNL456   7/4/2026    Promedio: 80 km/h   Dentro del limite
```

```
Opcion: 4
Placa a buscar: XYZ789

Placa: XYZ789
Fecha de verificacion: 30/9/2026
Radares: R1 95, R2 102, R3 88
Promedio: 95 km/h -> Exceso de velocidad
```

Los mensajes y la alineación pueden variar; lo importante es que los datos y los
cálculos sean correctos.

## Casos de prueba

Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Consultas sin datos | Opción 2, 3 o 4 antes de registrar | Aviso de que no hay vehículos registrados; la opción 3 no pide el mes y la 4 no pide la placa |
| 2 | Registro del vehículo 1 | `ABC123`, 14/4/2025, datos 72, 78, 75 | Promedio 75 km/h → Dentro del limite |
| 3 | Registro del vehículo 2 | `XYZ789`, 30/9/2026, datos 95, 102, 88 | Promedio 95 km/h → Exceso de velocidad |
| 4 | Justo en el límite | `MNL456`, 7/4/2026, datos 80, 80, 80 | Promedio 80 km/h → **Dentro del limite** |
| 5 | Registro del vehículo 4 | `RTS321`, 21/1/2024, datos 85, 79, 82 | Promedio 82 km/h → Exceso de velocidad |
| 6 | Tabla | Opción 2 después de los casos 2 a 5 | 4 filas, en el orden en que se registraron, con sus datos, su promedio y su clasificación |
| 7 | Mes con registros | Opción 3, mes 4 | `ABC123` (14/4/2025) y `MNL456` (7/4/2026), aunque son de años distintos |
| 8 | Mes sin registros | Opción 3, mes 12 | Aviso de que ningún vehículo tiene su fecha de verificación en ese mes |
| 9 | Mes no válido | Opción 3, mes 13 o 0 | Error; vuelve a pedir el mes |
| 10 | Búsqueda encontrada | Opción 4, `XYZ789` | Todos sus datos: 30/9/2026; 95, 102, 88; promedio 95 km/h; Exceso de velocidad |
| 11 | Búsqueda no encontrada | Opción 4, `GHK859` | Aviso de que no se encontró |
| 12 | Mayúsculas distintas | Opción 4, `xyz789` | Aviso de que no se encontró: `xyz789` y `XYZ789` son textos distintos |
| 13 | Fecha no válida | Día 0 o 32; mes 13; año 2014 o 2027 | Error; vuelve a pedir ese mismo dato |
| 14 | Dato fuera de rango | Un dato de 300 o de -10 | Error; vuelve a pedir el dato de ese mismo radar |
| 15 | Registro lleno | Se registra `GHK852`, 18/6/2025, datos 110, 98, 104 (promedio 104, Exceso de velocidad), y después otra vez la opción 1 | Aviso de registro lleno; no pide datos |
| 16 | Opción inválida | Opción 0 o 6 | Error; vuelve a mostrar el menú |
