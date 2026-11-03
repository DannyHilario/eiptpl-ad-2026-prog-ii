# PIA — Tiempos de atención de soporte técnico

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 11 — Palacios Moreno Jael Yasmani

## Historia de usuario

**Como** coordinador de un centro de soporte técnico, **quiero** que los técnicos que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada técnico se volvió un registro dentro de un arreglo de
structs, y ahora los técnicos se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- El centro tiene como máximo **8 técnicos**.
- De cada técnico se registra su **nombre**, una sola palabra sin espacios (por ejemplo `Oscar`), y su **fecha de ingreso**: la fecha en que entró a trabajar al centro de soporte, con día, mes y año. **No puede haber dos técnicos con el mismo nombre.**
- De cada técnico se registran las horas de sus últimos **5 tickets**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2005 y 2026**.
- Un tiempo es válido si está entre **0 y 168 horas** (una semana).
- Un técnico está **dentro de SLA** si el **promedio** de sus 5 tickets es **menor o igual a 24 horas**; si no, está **fuera de SLA**.
- Todos los técnicos se guardan en el archivo **`tecnicos.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
SOPORTE TECNICO

1.- Alta de un tecnico
2.- Buscar un tecnico
3.- Cambiar los datos de un tecnico
4.- Desplegar tecnicos
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los técnicos de `tecnicos.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide el nombre; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de ingreso y los 5 datos, muestra su promedio y su
  clasificación, y **agrega** el técnico al final de `tecnicos.txt`.
- **Opción 2 — Buscar:** pide el nombre y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el nombre; si existe, muestra sus datos actuales, pide sus
  5 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `tecnicos.txt` completo. El nombre y la fecha de ingreso no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los técnicos, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos técnicos hay, el **promedio de tiempo de resolución del equipo** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los técnicos que ya están registrados. Crea el archivo **`tecnicos.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
Oscar 1 6 2019 4 12.5 8 20 3.5
Brenda 15 9 2023 30 26 48 12 19
Ivan 10 6 2024 24 24 24 24 24
Karla 27 2 2012 36 20 30 28 16
Mario 8 11 2021 10 14 8 12 6
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `Oscar 1 6 2019 4 12.5 8 20 3.5` | 9.60 horas | Dentro de SLA |
| 2 | `Brenda 15 9 2023 30 26 48 12 19` | 27.00 horas | Fuera de SLA |
| 3 | `Ivan 10 6 2024 24 24 24 24 24` | 24.00 horas | Dentro de SLA |
| 4 | `Karla 27 2 2012 36 20 30 28 16` | 26.00 horas | Fuera de SLA |
| 5 | `Mario 8 11 2021 10 14 8 12 6` | 10.00 horas | Dentro de SLA |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 técnicos:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Tecnico {
    string nombre;
    Fecha ingreso;          // struct anidado: fecha de ingreso
    double horas[TICKETS];  // los 5 datos de cada técnico
    double promedioHoras;   // el promedio de los 5 datos
};

Tecnico tecnicos[MAX_TECNICOS];
int n;    // cuantos técnicos hay en el arreglo
```

**En el archivo**, un renglón por técnico, con los campos separados por un espacio:

```
nombre dia mes anio horas[0] horas[1] horas[2] horas[3] horas[4]
```

Por ejemplo, `Oscar 1 6 2019 4 12.5 8 20 3.5` es el técnico `Oscar`, con fecha de ingreso 1/6/2019 y
datos 4, 12.5, 8, 20, 3.5.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioHoras`, y se guarda en el campo `promedioHoras`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_TECNICOS && entrada >> tecnicos[n].nombre)`; dentro del `while` se leen la fecha y los 5 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaTecnico` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarTecnicos(Tecnico tecnicos[])` | Abre `tecnicos.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarTecnicos(Tecnico tecnicos[], int n)` | **Reescribe** `tecnicos.txt` completo con los `n` técnicos del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Tecnico tecnicos[], int n, string nombre)` | Regresa la posición del técnico con ese nombre, o -1 si no está | No |
| `double calcularPromedioHoras(double horas[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarAtencion(double promedioHoras)` | Regresa `"Dentro de SLA"` o `"Fuera de SLA"` (la misma de tu Evidencia 3.2) | No |
| `int altaTecnico(Tecnico tecnicos[], int n)` | **Opción 1.** Registra un técnico nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarTecnico(Tecnico tecnicos[], int n)` | **Opción 2.** Busca un técnico y muestra todos sus datos | Sí |
| `void cambiarTecnico(Tecnico tecnicos[], int n)` | **Opción 3.** Cambia los datos de un técnico y reescribe el archivo | Sí |
| `void desplegarTecnicos(Tecnico tecnicos[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Tecnico tecnicos[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaTecnico` y `cambiarTecnico` usan `buscarPosicion` y `calcularPromedioHoras`, y `cargarTecnicos` usa
`calcularPromedioHoras`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Tecnico` con los campos
      `nombre` (`string`), `ingreso` (`Fecha`), `horas` (arreglo `double` de 5) y `promedioHoras` (`double`).
- [ ] Los técnicos se guardan en un arreglo de structs `Tecnico tecnicos[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por técnico (5), los límites de
      un dato (0 y 168), los del año (2005 y 2026), el límite de
      la clasificación (24) y el nombre del archivo (`"tecnicos.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarTecnicos`, `guardarTecnicos`, `buscarPosicion`, `calcularPromedioHoras` y `clasificarAtencion`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioHoras` y se guarda en `promedioHoras`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los técnicos del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 técnicos, aunque el archivo tenga más renglones: `n < MAX_TECNICOS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del técnico cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 técnicos, avisa que el registro está lleno y no pide nada; si el
      nombre ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 168 horas. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del técnico (nombre, fecha de ingreso, los 5 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el nombre no existe; si existe, muestra los datos actuales, pide los
      5 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por técnico, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos técnicos hay, el promedio de tiempo de resolución del equipo y cuántos hay de cada
      clasificación.
- [ ] Si no hay técnicos registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
      datos o de mostrar la tabla o el resumen.
- [ ] La opción del menú debe estar entre 1 y 6; si no, muestra un error y vuelve a mostrar el menú.
- [ ] Los números con decimales se muestran con 2 decimales.
- [ ] Los resultados coinciden con **todos** los casos de prueba.

**Documenta sus pruebas** ([bitácora en PDF](#bitácora-de-pruebas-pdf))

- [ ] Entregas el PDF con la estructura pedida: portada y los 20 casos.
- [ ] Cada uno de los 20 casos tiene su captura (y la del Bloc de notas en los casos 3, 4, 12, 15 y 19) y
      su tabla de resultado esperado, obtenido y si coincide.
- [ ] Las capturas son de **tu** programa: el profesor lo corre con los mismos datos y debe dar lo mismo.

**Sin el PDF, Habilidades queda en 3 como máximo**, aunque el código cumpla todo lo demás.

**Código fácil de seguir y leer**

- [ ] Nombres descriptivos y comentarios que expliquen cada función y cada parte del programa.
- [ ] Compila y se ejecuta sin errores en Dev-C++.

### Actitudes / Valores (2 puntos) — Entrega

- [ ] Subes **los mismos dos archivos** en NEXUS en los **dos** lugares: *"4.2 Evidencia de Aprendizaje 4: Programa"* y
      *"Producto Integrador de Aprendizaje · Programa"*, antes del **sábado 14 de noviembre de 2026 a las 10:00 p.m.**
- [ ] El código va en texto plano, con el nombre `PIA_ApellidoNombre.txt`, y la bitácora en
      `PIA_ApellidoNombre.pdf` (así debe verse: [ejemplo resuelto](../ejemplo-resuelto/README.md)).
- [ ] El programa lo elaboraste tú: puedes explicar cualquier parte de tu código si se te pregunta.

## Ejemplo de ejecución

Al iniciar con el archivo inicial, y la opción 4:

```
Se cargaron 5 tecnicos de tecnicos.txt

SOPORTE TECNICO

1.- Alta de un tecnico
2.- Buscar un tecnico
3.- Cambiar los datos de un tecnico
4.- Desplegar tecnicos
5.- Resumen general
6.- Salir

Opcion: 4

TECNICOS REGISTRADOS

Nombre   Fecha            T1     T2     T3     T4     T5   Promedio
Oscar    1/6/2019       4.00  12.50   8.00  20.00   3.50       9.60   Dentro de SLA
Brenda   15/9/2023     30.00  26.00  48.00  12.00  19.00      27.00   Fuera de SLA
Ivan     10/6/2024     24.00  24.00  24.00  24.00  24.00      24.00   Dentro de SLA
Karla    27/2/2012     36.00  20.00  30.00  28.00  16.00      26.00   Fuera de SLA
Mario    8/11/2021     10.00  14.00   8.00  12.00   6.00      10.00   Dentro de SLA
```

Alta con nombre repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE TECNICO
  Nombre: Ivan
  ERROR! Ya existe un tecnico con ese nombre

Opcion: 1

ALTA DE TECNICO
  Nombre: Nadia
  Fecha de ingreso
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 2
    Mes: 6
    Anio: 2019
  Tickets
    Ticket 1: 17
    Ticket 2: 200
    ERROR! El dato debe estar entre 0 y 168 horas
    Ticket 2: 19.25
    Ticket 3: 28
    Ticket 4: 16
    Ticket 5: 11.25

Promedio: 18.30 horas -> Dentro de SLA
Tecnico agregado a tecnicos.txt
```

Búsqueda:

```
Opcion: 2
Nombre a buscar: Brenda

Nombre: Brenda
Fecha de ingreso: 15/9/2023
Tickets: T1 30.00, T2 26.00, T3 48.00, T4 12.00, T5 19.00
Promedio: 27.00 horas -> Fuera de SLA
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN TECNICO
  Nombre: Oscar

  Datos actuales: T1 4.00, T2 12.50, T3 8.00, T4 20.00, T5 3.50  (Promedio 9.60 horas, Dentro de SLA)
  Datos nuevos
    Ticket 1: 30
    Ticket 2: 26
    Ticket 3: 48
    Ticket 4: 12
    Ticket 5: 19

Promedio: 27.00 horas -> Fuera de SLA
Se reescribio tecnicos.txt con 6 tecnicos
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Tecnicos registrados: 6
Promedio de tiempo de resolucion del equipo: 22.05 horas
Dentro de SLA: 3
Fuera de SLA: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `tecnicos.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `tecnicos.txt` en la carpeta | `Se cargaron 0 tecnicos`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay técnicos registrados; la 2 y la 3 no piden el nombre |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `Nadia`, 2/6/2019, datos 17, 19.25, 28, 16, 11.25 | Promedio 18.30 horas → Dentro de SLA; aparece `tecnicos.txt` con un solo renglón: `Nadia 2 6 2019 17 19.25 28 16 11.25` |
| 4 | Carga del archivo inicial | Borrar `tecnicos.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 tecnicos` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `Oscar` 9.60 (Dentro de SLA); `Brenda` 27.00 (Fuera de SLA); `Ivan` 24.00 (Dentro de SLA); `Karla` 26.00 (Fuera de SLA); `Mario` 10.00 (Dentro de SLA) |
| 6 | Búsqueda encontrada | Opción 2, `Brenda` | Todos sus datos: 15/9/2023; 30.00, 26.00, 48.00, 12.00, 19.00; promedio 27.00 horas → Fuera de SLA |
| 7 | Búsqueda no encontrada | Opción 2, `Pedro` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `brenda` | Aviso de que no se encontró: `brenda` y `Brenda` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 técnicos; promedio de tiempo de resolución del equipo: 19.32 horas; Dentro de SLA: 3; Fuera de SLA: 2 |
| 10 | Nombre repetido | Opción 1, `Ivan` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `Nadia`: día 0 y 32, mes 13, año 2004 y 2027, un dato de 200 y de -1; después 2/6/2019 y datos 17, 19.25, 28, 16, 11.25 | Error en cada dato no válido y lo vuelve a pedir; promedio 18.30 horas → Dentro de SLA |
| 12 | El alta agrega al final | Abrir `tecnicos.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `Nadia 2 6 2019 17 19.25 28 16 11.25` |
| 13 | Cambio de técnico que no existe | Opción 3, `Pedro` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `Oscar`; un dato de 200; después 30, 26, 48, 12, 19 | Muestra sus datos actuales; error con 200 y vuelve a pedir ese mismo ticket; nuevo promedio 27.00 horas → Fuera de SLA |
| 15 | El cambio reescribe el archivo | Abrir `tecnicos.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `Oscar 1 6 2019 30 26 48 12 19` |
| 16 | Resumen después de los cambios | Opción 5 | 6 técnicos; promedio de tiempo de resolución del equipo: 22.05 horas; Dentro de SLA: 3; Fuera de SLA: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 tecnicos`; la tabla muestra los 6, con `Oscar` ya cambiado y `Nadia` al final |
| 18 | Registro lleno | Opción 1 con `Felipe`, 16/9/2023, datos 20, 30, 28, 16, 36 (26.00, Fuera de SLA) y `Lorena`, 11/6/2024, datos 14, 8, 12, 6, 10 (10.00, Dentro de SLA); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el nombre |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `tecnicos.txt` (10 en total) y correr el programa | `Se cargaron 8 tecnicos`; el programa no falla ni escribe fuera del arreglo |
| 20 | Opción inválida | Opción 0 o 7 | Error; vuelve a mostrar el menú |

## Bitácora de pruebas (PDF)

Además del código entregas un **PDF con las pruebas que tú corriste**: capturas de pantalla de
tu programa funcionando. El profesor también corre sus propias pruebas sobre tu código; la
bitácora demuestra que **tú** lo ejecutaste y comprobaste cada resultado.

**Mira el [ejemplo resuelto](../ejemplo-resuelto/README.md)**: una bitácora completa de un contexto que
no es de ningún alumno, con todas sus capturas ([en PDF](../ejemplo-resuelto/PIA_HilarioDaniel.pdf)).

**Las capturas son imágenes** de la ventana completa de la consola (o del Bloc de notas), con la
tecla Impr Pant o con la Herramienta Recortes (Windows + Shift + S). El texto copiado y pegado no
cuenta como captura.

**Estructura del PDF**, con estos títulos y en este orden:

```
Portada
    Nombre completo, número y contexto (Tiempos de atencion de soporte tecnico)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `tecnicos.txt` abierto en el Bloc de notas:

| Caso | Captura del Bloc de notas |
|---|---|
| 3 | El archivo que creó el alta: un solo renglón |
| 4 | El archivo inicial que creaste, con sus 5 renglones |
| 12 | Los 6 renglones después del alta |
| 15 | Los 6 renglones después del cambio |
| 19 | Los 10 renglones, con los 2 que agregaste a mano |

Cada apartado lleva su captura y debajo esta tabla:

| Resultado esperado | Resultado obtenido | ¿Coincide? |
|---|---|---|
| Lo que dice la columna *Salida esperada* | Lo que mostró tu programa | Sí / No |

Si un caso **no coincide**, pon "No" y explica qué salió distinto. Documentar con honestidad una
falla no te baja más de lo que ya baja la falla; poner "Sí" en algo que tu programa no hace, sí.

## Material de consulta

| Para… | Tema |
|---|---|
| Pasar el arreglo de structs a una función y regresar el nuevo `n` | [1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md) |
| Mostrar 2 decimales | [1.2 — `<iomanip>`](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar) |
| Buscar por nombre | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
