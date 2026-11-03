# PIA — Pruebas de resistencia por pieza

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 16 — Roldan Reyes Alexis

## Historia de usuario

**Como** técnico de un laboratorio de materiales, **quiero** que las piezas que registro se guarden en un archivo,
y poder buscarlas, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todas.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada pieza se volvió un registro dentro de un arreglo de
structs, y ahora las piezas se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- El laboratorio prueba como máximo **8 piezas** por lote.
- De cada pieza se registra su **número de serie**, una sola palabra sin espacios (por ejemplo `S1001`), y su **fecha de fabricación**: la fecha en que se fabricó la pieza, con día, mes y año. **No puede haber dos piezas con el mismo número de serie.**
- Cada pieza pasa por **3 pruebas** de tensión.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- Una resistencia es válida si está entre **0 y 2000 kg**.
- Una pieza es **aprobada** si el **promedio** de sus 3 pruebas es **mayor o igual a 500 kg**; si no, es **rechazada**.
- Todas las piezas se guardan en el archivo **`piezas.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
LABORATORIO DE RESISTENCIA

1.- Alta de una pieza
2.- Buscar una pieza
3.- Cambiar los datos de una pieza
4.- Desplegar piezas
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga las piezas de `piezas.txt` y avisa cuántas cargó.
- **Opción 1 — Alta:** pide el número de serie; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de fabricación y los 3 datos, muestra su promedio y su
  clasificación, y **agrega** la pieza al final de `piezas.txt`.
- **Opción 2 — Buscar:** pide el número de serie y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide el número de serie; si existe, muestra sus datos actuales, pide sus
  3 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `piezas.txt` completo. El número de serie y la fecha de fabricación no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todas las piezas, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántas piezas hay, el **promedio de resistencia de las piezas** (el
  promedio de los promedios de todas) y cuántas hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estas son las piezas que ya están registradas. Crea el archivo **`piezas.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
S1001 7 11 2024 620 580 610
S1002 24 6 2026 450 520 470
S1003 19 11 2025 500 500 500
S1004 3 2 2024 800 760 840
S1005 15 8 2025 300 350 280
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `S1001 7 11 2024 620 580 610` | 603.33 kg | Aprobada |
| 2 | `S1002 24 6 2026 450 520 470` | 480.00 kg | Rechazada |
| 3 | `S1003 19 11 2025 500 500 500` | 500.00 kg | Aprobada |
| 4 | `S1004 3 2 2024 800 760 840` | 800.00 kg | Aprobada |
| 5 | `S1005 15 8 2025 300 350 280` | 310.00 kg | Rechazada |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 piezas:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Pieza {
    string serie;
    Fecha fabricacion;             // struct anidado: fecha de fabricación
    double resistencias[PRUEBAS];  // los 3 datos de cada pieza
    double promedioResistencia;    // el promedio de los 3 datos
};

Pieza piezas[MAX_PIEZAS];
int n;    // cuantas piezas hay en el arreglo
```

**En el archivo**, un renglón por pieza, con los campos separados por un espacio:

```
serie dia mes anio resistencias[0] resistencias[1] resistencias[2]
```

Por ejemplo, `S1001 7 11 2024 620 580 610` es la pieza `S1001`, con fecha de fabricación 7/11/2024 y
datos 620, 580, 610.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioResistencia`, y se guarda en el campo `promedioResistencia`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_PIEZAS && entrada >> piezas[n].serie)`; dentro del `while` se leen la fecha y los 3 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaPieza` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarPiezas(Pieza piezas[])` | Abre `piezas.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada una y regresa cuántas cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarPiezas(Pieza piezas[], int n)` | **Reescribe** `piezas.txt` completo con las `n` piezas del arreglo. Regresa cuántas escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Pieza piezas[], int n, string serie)` | Regresa la posición de la pieza con ese número de serie, o -1 si no está | No |
| `double calcularPromedioResistencia(double resistencias[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarResistencia(double promedioResistencia)` | Regresa `"Aprobada"` o `"Rechazada"` (la misma de tu Evidencia 3.2) | No |
| `int altaPieza(Pieza piezas[], int n)` | **Opción 1.** Registra una pieza nueva y la agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarPieza(Pieza piezas[], int n)` | **Opción 2.** Busca una pieza y muestra todos sus datos | Sí |
| `void cambiarPieza(Pieza piezas[], int n)` | **Opción 3.** Cambia los datos de una pieza y reescribe el archivo | Sí |
| `void desplegarPiezas(Pieza piezas[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Pieza piezas[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaPieza` y `cambiarPieza` usan `buscarPosicion` y `calcularPromedioResistencia`, y `cargarPiezas` usa
`calcularPromedioResistencia`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Pieza` con los campos
      `serie` (`string`), `fabricacion` (`Fecha`), `resistencias` (arreglo `double` de 3) y `promedioResistencia` (`double`).
- [ ] Las piezas se guardan en un arreglo de structs `Pieza piezas[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por pieza (3), los límites de
      un dato (0 y 2000), los del año (2020 y 2026), el límite de
      la clasificación (500) y el nombre del archivo (`"piezas.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarPiezas`, `guardarPiezas`, `buscarPosicion`, `calcularPromedioResistencia` y `clasificarResistencia`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioResistencia` y se guarda en `promedioResistencia`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todas las piezas del archivo y avisa cuántas. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 piezas, aunque el archivo tenga más renglones: `n < MAX_PIEZAS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos de la pieza cambiada.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 piezas, avisa que el registro está lleno y no pide nada; si el
      número de serie ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 2000 kg. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos de la pieza (número de serie, fecha de fabricación, los 3 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si el número de serie no existe; si existe, muestra los datos actuales, pide los
      3 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por pieza, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántas piezas hay, el promedio de resistencia de las piezas y cuántas hay de cada
      clasificación.
- [ ] Si no hay piezas registradas, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 piezas de piezas.txt

LABORATORIO DE RESISTENCIA

1.- Alta de una pieza
2.- Buscar una pieza
3.- Cambiar los datos de una pieza
4.- Desplegar piezas
5.- Resumen general
6.- Salir

Opcion: 4

PIEZAS REGISTRADAS

Numero   Fecha              P1      P2      P3   Promedio
S1001    7/11/2024      620.00  580.00  610.00     603.33   Aprobada
S1002    24/6/2026      450.00  520.00  470.00     480.00   Rechazada
S1003    19/11/2025     500.00  500.00  500.00     500.00   Aprobada
S1004    3/2/2024       800.00  760.00  840.00     800.00   Aprobada
S1005    15/8/2025      300.00  350.00  280.00     310.00   Rechazada
```

Alta con número de serie repetido y alta con datos no válidos:

```
Opcion: 1

ALTA DE PIEZA
  Numero de serie: S1003
  ERROR! Ya existe una pieza con ese numero de serie

Opcion: 1

ALTA DE PIEZA
  Numero de serie: S1006
  Fecha de fabricacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 8
    Mes: 11
    Anio: 2024
  Pruebas
    Prueba 1: 535
    Prueba 2: 2500
    ERROR! El dato debe estar entre 0 y 2000 kg
    Prueba 2: 550
    Prueba 3: 540

Promedio: 541.67 kg -> Aprobada
Pieza agregada a piezas.txt
```

Búsqueda:

```
Opcion: 2
Numero de serie a buscar: S1002

Numero de serie: S1002
Fecha de fabricacion: 24/6/2026
Pruebas: P1 450.00, P2 520.00, P3 470.00
Promedio: 480.00 kg -> Rechazada
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UNA PIEZA
  Numero de serie: S1001

  Datos actuales: P1 620.00, P2 580.00, P3 610.00  (Promedio 603.33 kg, Aprobada)
  Datos nuevos
    Prueba 1: 450
    Prueba 2: 520
    Prueba 3: 470

Promedio: 480.00 kg -> Rechazada
Se reescribio piezas.txt con 6 piezas
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Piezas registradas: 6
Promedio de resistencia de las piezas: 518.61 kg
Aprobada: 3
Rechazada: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `piezas.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `piezas.txt` en la carpeta | `Se cargaron 0 piezas`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay piezas registradas; la 2 y la 3 no piden el número de serie |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `S1006`, 8/11/2024, datos 535, 550, 540 | Promedio 541.67 kg → Aprobada; aparece `piezas.txt` con un solo renglón: `S1006 8 11 2024 535 550 540` |
| 4 | Carga del archivo inicial | Borrar `piezas.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 piezas` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `S1001` 603.33 (Aprobada); `S1002` 480.00 (Rechazada); `S1003` 500.00 (Aprobada); `S1004` 800.00 (Aprobada); `S1005` 310.00 (Rechazada) |
| 6 | Búsqueda encontrada | Opción 2, `S1002` | Todos sus datos: 24/6/2026; 450.00, 520.00, 470.00; promedio 480.00 kg → Rechazada |
| 7 | Búsqueda no encontrada | Opción 2, `S1009` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `s1002` | Aviso de que no se encontró: `s1002` y `S1002` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 piezas; promedio de resistencia de las piezas: 538.67 kg; Aprobada: 3; Rechazada: 2 |
| 10 | Número de serie repetido | Opción 1, `S1003` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `S1006`: día 0 y 32, mes 13, año 2019 y 2027, un dato de 2500 y de -50; después 8/11/2024 y datos 535, 550, 540 | Error en cada dato no válido y lo vuelve a pedir; promedio 541.67 kg → Aprobada |
| 12 | El alta agrega al final | Abrir `piezas.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `S1006 8 11 2024 535 550 540` |
| 13 | Cambio de pieza que no existe | Opción 3, `S1009` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `S1001`; un dato de 2500; después 450, 520, 470 | Muestra sus datos actuales; error con 2500 y vuelve a pedir esa misma prueba; nuevo promedio 480.00 kg → Rechazada |
| 15 | El cambio reescribe el archivo | Abrir `piezas.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `S1001 7 11 2024 450 520 470` |
| 16 | Resumen después de los cambios | Opción 5 | 6 piezas; promedio de resistencia de las piezas: 518.61 kg; Aprobada: 3; Rechazada: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 piezas`; la tabla muestra los 6, con `S1001` ya cambiada y `S1006` al final |
| 18 | Registro lleno | Opción 1 con `S1007`, 25/6/2026, datos 760, 840, 800 (800.00, Aprobada) y `S1008`, 20/11/2025, datos 350, 280, 300 (310.00, Rechazada); después otra vez la opción 1 | Las dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide el número de serie |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `piezas.txt` (10 en total) y correr el programa | `Se cargaron 8 piezas`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Pruebas de resistencia por pieza)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `piezas.txt` abierto en el Bloc de notas:

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
| Buscar por número de serie | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
