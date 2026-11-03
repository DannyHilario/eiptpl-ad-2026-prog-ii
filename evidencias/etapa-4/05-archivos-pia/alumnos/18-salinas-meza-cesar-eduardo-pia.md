# PIA — Consumo de datos móviles por semana

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 18 — Salinas Meza Cesar Eduardo

## Historia de usuario

**Como** analista de una compañía telefónica, **quiero** que las líneas que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada línea se volvió un registro dentro de un arreglo de
structs, y ahora las líneas se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se revisan como máximo **8 líneas**.
- De cada línea se registra su **número de teléfono**, una sola palabra sin espacios (por ejemplo `8110000001`), y su **fecha de contratación**: la fecha en que el cliente contrató la línea, con día, mes y año. **No puede haber dos líneas con el mismo número de teléfono.**
- De cada línea se registra el consumo de **4 semanas**.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2010 y 2026**.
- El consumo de una semana es válido si está entre **0 y 50 GB**.
- Una línea está **dentro del plan** si el **total** de sus 4 semanas es **menor o igual a 5 GB**; si no, **excede el plan**.
- Todas las líneas se guardan en el archivo **`lineas.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
CONSUMO DE DATOS MOVILES

1.- Alta de una linea
2.- Buscar una linea
3.- Cambiar los datos de una linea
4.- Desplegar lineas
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las líneas de `lineas.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide el número de teléfono; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de contratación y los 4 datos, muestra su total y su
  clasificación, y **agrega** la línea al final de `lineas.txt`.
- **Opción 2 — Buscar:** pide el número de teléfono y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el número de teléfono; si existe, muestra sus datos actuales, pide sus
  4 datos **nuevos**, recalcula su total, muestra su nueva clasificación y **reescribe**
  `lineas.txt` completo. El número de teléfono y la fecha de contratación no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las líneas, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas líneas hay, el **promedio de consumo por línea** (el
  promedio de los totales de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las líneas que ya están registradas. Crea el archivo **`lineas.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
8110000001 30 1 2022 0.75 1.25 1 0.5
8110000002 12 5 2019 2 1.5 1.25 1.75
8110000003 17 1 2025 1.25 1.25 1.25 1.25
8110000004 4 9 2023 0.5 0.25 0.75 0.5
8110000005 21 11 2020 3 2.5 4 3.5
```

Así se lee cada renglón:

| # | Renglón | Total | Clasificación |
|---|---|---|---|
| 1 | `8110000001 30 1 2022 0.75 1.25 1 0.5` | 3.50 GB | Dentro del plan |
| 2 | `8110000002 12 5 2019 2 1.5 1.25 1.75` | 6.50 GB | Excede el plan |
| 3 | `8110000003 17 1 2025 1.25 1.25 1.25 1.25` | 5.00 GB | Dentro del plan |
| 4 | `8110000004 4 9 2023 0.5 0.25 0.75 0.5` | 2.00 GB | Dentro del plan |
| 5 | `8110000005 21 11 2020 3 2.5 4 3.5` | 13.00 GB | Excede el plan |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 líneas:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Linea {
    string numero;
    Fecha contratacion;        // struct anidado: fecha de contratación
    double consumos[SEMANAS];  // los 4 datos de cada línea
    double totalConsumo;       // la suma de los 4 datos
};

Linea lineas[MAX_LINEAS];
int n;    // cuantas líneas hay en el arreglo
```

**En el archivo**, un renglón por línea, con los campos separados por un espacio:

```
numero dia mes anio consumos[0] consumos[1] consumos[2] consumos[3]
```

Por ejemplo, `8110000001 30 1 2022 0.75 1.25 1 0.5` es la línea `8110000001`, con fecha de contratación 30/1/2022 y
datos 0.75, 1.25, 1, 0.5.

**El total no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularTotalConsumo`, y se guarda en el campo `totalConsumo`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_LINEAS && entrada >> lineas[n].numero)`; dentro del `while` se leen la fecha y los 4 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaLinea` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarLineas(Linea lineas[])` | Abre `lineas.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el total de cada una y regresa cuántas cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarLineas(Linea lineas[], int n)` | **Reescribe** `lineas.txt` completo con las `n` líneas del arreglo. Regresa cuántas escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Linea lineas[], int n, string numero)` | Regresa la posición de la línea con ese número de teléfono, o -1 si no está | No |
| `double calcularTotalConsumo(double consumos[], int cantidad)` | Regresa la suma de los datos del arreglo | No |
| `string clasificarPlan(double totalConsumo)` | Regresa `"Dentro del plan"` o `"Excede el plan"` (la misma de tu Evidencia 3.2) | No |
| `int altaLinea(Linea lineas[], int n)` | **Opción 1.** Registra una línea nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarLinea(Linea lineas[], int n)` | **Opción 2.** Busca una línea y muestra todos sus datos | Sí |
| `void cambiarLinea(Linea lineas[], int n)` | **Opción 3.** Cambia los datos de una línea y reescribe el archivo | Sí |
| `void desplegarLineas(Linea lineas[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Linea lineas[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaLinea` y `cambiarLinea` usan `buscarPosicion` y `calcularTotalConsumo`, y `cargarLineas` usa
`calcularTotalConsumo`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Linea` con los campos
      `numero` (`string`), `contratacion` (`Fecha`), `consumos` (arreglo `double` de 4) y `totalConsumo` (`double`).
- [ ] Las líneas se guardan en un arreglo de structs `Linea lineas[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por línea (4), los límites de
      un dato (0 y 50), los del año (2010 y 2026), el límite de
      la clasificación (5) y el nombre del archivo (`"lineas.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarLineas`, `guardarLineas`, `buscarPosicion`, `calcularTotalConsumo` y `clasificarPlan`
      no usan `cin` ni `cout`.
- [ ] El total se calcula **solo** con `calcularTotalConsumo` y se guarda en `totalConsumo`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todas las líneas del archivo y avisa cuántas. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 líneas, aunque el archivo tenga más renglones: `n < MAX_LINEAS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos de la línea cambiada.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 líneas, avisa que el registro está lleno y no pide nada; si el
      número de teléfono ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 50 GB. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la línea (número de teléfono, fecha de contratación, los 4 datos, total y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el número de teléfono no existe; si existe, muestra los datos actuales, pide los
      4 nuevos, recalcula el total y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por línea, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas líneas hay, el promedio de consumo por línea y cuántas hay de cada
      clasificación.
- [ ] Si no hay líneas registradas, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 lineas de lineas.txt

CONSUMO DE DATOS MOVILES

1.- Alta de una linea
2.- Buscar una linea
3.- Cambiar los datos de una linea
4.- Desplegar lineas
5.- Resumen general
6.- Salir

Opcion: 4

LINEAS REGISTRADAS

Numero       Fecha            S1    S2    S3    S4   Total
8110000001   30/1/2022      0.75  1.25  1.00  0.50    3.50   Dentro del plan
8110000002   12/5/2019      2.00  1.50  1.25  1.75    6.50   Excede el plan
8110000003   17/1/2025      1.25  1.25  1.25  1.25    5.00   Dentro del plan
8110000004   4/9/2023       0.50  0.25  0.75  0.50    2.00   Dentro del plan
8110000005   21/11/2020     3.00  2.50  4.00  3.50   13.00   Excede el plan
```

Alta con número de teléfono repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE LINEA
  Numero de telefono: 8110000003
  ERROR! Ya existe una linea con ese numero de telefono

Opcion: 1

ALTA DE LINEA
  Numero de telefono: 8110000006
  Fecha de contratacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 28
    Mes: 1
    Anio: 2022
  Semanas
    Semana 1: 1.88
    Semana 2: 60
    ERROR! El dato debe estar entre 0 y 50 GB
    Semana 2: 1.38
    Semana 3: 1.12
    Semana 4: 1.12

Total: 5.50 GB -> Excede el plan
Linea agregada a lineas.txt
```

Búsqueda:

```
Opcion: 2
Numero de telefono a buscar: 8110000002

Numero de telefono: 8110000002
Fecha de contratacion: 12/5/2019
Semanas: S1 2.00, S2 1.50, S3 1.25, S4 1.75
Total: 6.50 GB -> Excede el plan
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA LINEA
  Numero de telefono: 8110000001

  Datos actuales: S1 0.75, S2 1.25, S3 1.00, S4 0.50  (Total 3.50 GB, Dentro del plan)
  Datos nuevos
    Semana 1: 2
    Semana 2: 1.5
    Semana 3: 1.25
    Semana 4: 1.75

Total: 6.50 GB -> Excede el plan
Se reescribio lineas.txt con 6 lineas
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Lineas registradas: 6
Promedio de consumo por linea: 6.42 GB
Dentro del plan: 2
Excede el plan: 4
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `lineas.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `lineas.txt` en la carpeta | `Se cargaron 0 lineas`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay líneas registradas; la 2 y la 3 no piden el número de teléfono |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `8110000006`, 28/1/2022, datos 1.88, 1.38, 1.12, 1.12 | Total 5.50 GB → Excede el plan; aparece `lineas.txt` con un solo renglón: `8110000006 28 1 2022 1.88 1.38 1.12 1.12` |
| 4 | Carga del archivo inicial | Borrar `lineas.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 lineas` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `8110000001` 3.50 (Dentro del plan); `8110000002` 6.50 (Excede el plan); `8110000003` 5.00 (Dentro del plan); `8110000004` 2.00 (Dentro del plan); `8110000005` 13.00 (Excede el plan) |
| 6 | Búsqueda encontrada | Opción 2, `8110000002` | Todos sus datos: 12/5/2019; 2.00, 1.50, 1.25, 1.75; total 6.50 GB → Excede el plan |
| 7 | Búsqueda no encontrada | Opción 2, `8110000009` | Aviso de que no se encontró |
| 8 | Identificador incompleto | Opción 2, `811000000` | Aviso de que no se encontró: `811000000` no es igual a `8110000002` |
| 9 | Resumen inicial | Opción 5 | 5 líneas; promedio de consumo por línea: 6.00 GB; Dentro del plan: 3; Excede el plan: 2 |
| 10 | Número de teléfono repetido | Opción 1, `8110000003` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `8110000006`: día 0 y 32, mes 13, año 2009 y 2027, un dato de 60 y de -1; después 28/1/2022 y datos 1.88, 1.38, 1.12, 1.12 | Error en cada dato no válido y lo vuelve a pedir; total 5.50 GB → Excede el plan |
| 12 | El alta agrega al final | Abrir `lineas.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `8110000006 28 1 2022 1.88 1.38 1.12 1.12` |
| 13 | Cambio de línea que no existe | Opción 3, `8110000009` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `8110000001`; un dato de 60; después 2, 1.5, 1.25, 1.75 | Muestra sus datos actuales; error con 60 y vuelve a pedir esa misma semana; nuevo total 6.50 GB → Excede el plan |
| 15 | El cambio reescribe el archivo | Abrir `lineas.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `8110000001 30 1 2022 2 1.5 1.25 1.75` |
| 16 | Resumen después de los cambios | Opción 5 | 6 líneas; promedio de consumo por línea: 6.42 GB; Dentro del plan: 2; Excede el plan: 4 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 lineas`; la tabla muestra los 6, con `8110000001` ya cambiada y `8110000006` al final |
| 18 | Registro lleno | Opción 1 con `8110000007`, 13/5/2019, datos 0.25, 0.75, 0.5, 0.5 (2.00, Dentro del plan) y `8110000008`, 18/1/2025, datos 2.5, 4, 3.5, 3 (13.00, Excede el plan); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el número de teléfono |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `lineas.txt` (10 en total) y correr el programa | `Se cargaron 8 lineas`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Consumo de datos moviles por semana)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `lineas.txt` abierto en el Bloc de notas:

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
| Buscar por número de teléfono | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
