# PIA — Nivel de tanques de gas LP

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 14 — Rocha Ramirez Tomas De Jesus

## Historia de usuario

**Como** programador de rutas de una empresa de gas LP, **quiero** que los tanques que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada tanque se volvió un registro dentro de un arreglo de
structs, y ahora los tanques se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se revisan como máximo **8 tanques**.
- De cada tanque se registra su **clave**, una sola palabra sin espacios (por ejemplo `TQ10`), y su **fecha de recarga**: la fecha en que se recargó el tanque por última vez, con día, mes y año. **No puede haber dos tanques con la misma clave.**
- Cada tanque se lee **3 veces** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2024 y 2026**.
- Una lectura es válida si está entre **0 y 100%**.
- Un tanque tiene **nivel normal** si el **promedio** de sus 3 lecturas es **mayor o igual a 15%**; si no, tiene **nivel bajo** y hay que reabastecerlo.
- Todos los tanques se guardan en el archivo **`tanques.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
NIVEL DE TANQUES DE GAS

1.- Alta de un tanque
2.- Buscar un tanque
3.- Cambiar los datos de un tanque
4.- Desplegar tanques
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los tanques de `tanques.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de recarga y los 3 datos, muestra su promedio y su
  clasificación, y **agrega** el tanque al final de `tanques.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  3 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `tanques.txt` completo. La clave y la fecha de recarga no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los tanques, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos tanques hay, el **promedio de nivel de los tanques** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los tanques que ya están registrados. Crea el archivo **`tanques.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
TQ10 2 9 2025 45 44 46
TQ20 16 7 2026 12 10 11
TQ30 21 9 2026 15 15 15
TQ40 8 3 2025 14 16 14
TQ50 27 1 2026 80 78 76
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `TQ10 2 9 2025 45 44 46` | 45.00% | Nivel normal |
| 2 | `TQ20 16 7 2026 12 10 11` | 11.00% | Nivel bajo |
| 3 | `TQ30 21 9 2026 15 15 15` | 15.00% | Nivel normal |
| 4 | `TQ40 8 3 2025 14 16 14` | 14.67% | Nivel bajo |
| 5 | `TQ50 27 1 2026 80 78 76` | 78.00% | Nivel normal |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 tanques:

```cpp
struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Tanque {
    string clave;
    Fecha recarga;             // struct anidado: fecha de recarga
    double niveles[LECTURAS];  // los 3 datos de cada tanque
    double promedioNivel;      // el promedio de los 3 datos
};

Tanque tanques[MAX_TANQUES];
int n;    // cuantos tanques hay en el arreglo
```

**En el archivo**, un renglón por tanque, con los campos separados por un espacio:

```
clave dia mes anio niveles[0] niveles[1] niveles[2]
```

Por ejemplo, `TQ10 2 9 2025 45 44 46` es el tanque `TQ10`, con fecha de recarga 2/9/2025 y
datos 45, 44, 46.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioNivel`, y se guarda en el campo `promedioNivel`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_TANQUES && entrada >> tanques[n].clave)`; dentro del `while` se leen la fecha y los 3 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaTanque` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarTanques(Tanque tanques[])` | Abre `tanques.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarTanques(Tanque tanques[], int n)` | **Reescribe** `tanques.txt` completo con los `n` tanques del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Tanque tanques[], int n, string clave)` | Regresa la posición del tanque con esa clave, o -1 si no está | No |
| `double calcularPromedioNivel(double niveles[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarNivel(double promedioNivel)` | Regresa `"Nivel normal"` o `"Nivel bajo"` (la misma de tu Evidencia 3.2) | No |
| `int altaTanque(Tanque tanques[], int n)` | **Opción 1.** Registra un tanque nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarTanque(Tanque tanques[], int n)` | **Opción 2.** Busca un tanque y muestra todos sus datos | Sí |
| `void cambiarTanque(Tanque tanques[], int n)` | **Opción 3.** Cambia los datos de un tanque y reescribe el archivo | Sí |
| `void desplegarTanques(Tanque tanques[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Tanque tanques[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaTanque` y `cambiarTanque` usan `buscarPosicion` y `calcularPromedioNivel`, y `cargarTanques` usa
`calcularPromedioNivel`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Tanque` con los campos
      `clave` (`string`), `recarga` (`Fecha`), `niveles` (arreglo `double` de 3) y `promedioNivel` (`double`).
- [ ] Los tanques se guardan en un arreglo de structs `Tanque tanques[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por tanque (3), los límites de
      un dato (0 y 100), los del año (2024 y 2026), el límite de
      la clasificación (15) y el nombre del archivo (`"tanques.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarTanques`, `guardarTanques`, `buscarPosicion`, `calcularPromedioNivel` y `clasificarNivel`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioNivel` y se guarda en `promedioNivel`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los tanques del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 tanques, aunque el archivo tenga más renglones: `n < MAX_TANQUES` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del tanque cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 tanques, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 100%. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del tanque (clave, fecha de recarga, los 3 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      3 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por tanque, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos tanques hay, el promedio de nivel de los tanques y cuántos hay de cada
      clasificación.
- [ ] Si no hay tanques registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 tanques de tanques.txt

NIVEL DE TANQUES DE GAS

1.- Alta de un tanque
2.- Buscar un tanque
3.- Cambiar los datos de un tanque
4.- Desplegar tanques
5.- Resumen general
6.- Salir

Opcion: 4

TANQUES REGISTRADOS

Clave   Fecha           Man    Tar    Noc   Promedio
TQ10    2/9/2025      45.00  44.00  46.00      45.00   Nivel normal
TQ20    16/7/2026     12.00  10.00  11.00      11.00   Nivel bajo
TQ30    21/9/2026     15.00  15.00  15.00      15.00   Nivel normal
TQ40    8/3/2025      14.00  16.00  14.00      14.67   Nivel bajo
TQ50    27/1/2026     80.00  78.00  76.00      78.00   Nivel normal
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE TANQUE
  Clave: TQ30
  ERROR! Ya existe un tanque con esa clave

Opcion: 1

ALTA DE TANQUE
  Clave: TQ60
  Fecha de recarga
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 3
    Mes: 9
    Anio: 2025
  Lecturas
    Manana: 29
    Tarde: 110
    ERROR! El dato debe estar entre 0 y 100%
    Tarde: 27
    Noche: 29

Promedio: 28.33% -> Nivel normal
Tanque agregado a tanques.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: TQ20

Clave: TQ20
Fecha de recarga: 16/7/2026
Lecturas: Man 12.00, Tar 10.00, Noc 11.00
Promedio: 11.00% -> Nivel bajo
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN TANQUE
  Clave: TQ10

  Datos actuales: Man 45.00, Tar 44.00, Noc 46.00  (Promedio 45.00%, Nivel normal)
  Datos nuevos
    Manana: 12
    Tarde: 10
    Noche: 11

Promedio: 11.00% -> Nivel bajo
Se reescribio tanques.txt con 6 tanques
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Tanques registrados: 6
Promedio de nivel de los tanques: 26.33%
Nivel normal: 3
Nivel bajo: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `tanques.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `tanques.txt` en la carpeta | `Se cargaron 0 tanques`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay tanques registrados; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `TQ60`, 3/9/2025, datos 29, 27, 29 | Promedio 28.33% → Nivel normal; aparece `tanques.txt` con un solo renglón: `TQ60 3 9 2025 29 27 29` |
| 4 | Carga del archivo inicial | Borrar `tanques.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 tanques` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `TQ10` 45.00 (Nivel normal); `TQ20` 11.00 (Nivel bajo); `TQ30` 15.00 (Nivel normal); `TQ40` 14.67 (Nivel bajo); `TQ50` 78.00 (Nivel normal) |
| 6 | Búsqueda encontrada | Opción 2, `TQ20` | Todos sus datos: 16/7/2026; 12.00, 10.00, 11.00; promedio 11.00% → Nivel bajo |
| 7 | Búsqueda no encontrada | Opción 2, `TQ59` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `tq20` | Aviso de que no se encontró: `tq20` y `TQ20` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 tanques; promedio de nivel de los tanques: 32.73%; Nivel normal: 3; Nivel bajo: 2 |
| 10 | Clave repetida | Opción 1, `TQ30` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `TQ60`: día 0 y 32, mes 13, año 2023 y 2027, un dato de 110 y de -4; después 3/9/2025 y datos 29, 27, 29 | Error en cada dato no válido y lo vuelve a pedir; promedio 28.33% → Nivel normal |
| 12 | El alta agrega al final | Abrir `tanques.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `TQ60 3 9 2025 29 27 29` |
| 13 | Cambio de tanque que no existe | Opción 3, `TQ59` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `TQ10`; un dato de 110; después 12, 10, 11 | Muestra sus datos actuales; error con 110 y vuelve a pedir esa misma lectura; nuevo promedio 11.00% → Nivel bajo |
| 15 | El cambio reescribe el archivo | Abrir `tanques.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `TQ10 2 9 2025 12 10 11` |
| 16 | Resumen después de los cambios | Opción 5 | 6 tanques; promedio de nivel de los tanques: 26.33%; Nivel normal: 3; Nivel bajo: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 tanques`; la tabla muestra los 6, con `TQ10` ya cambiado y `TQ60` al final |
| 18 | Registro lleno | Opción 1 con `TQ70`, 17/7/2026, datos 16, 14, 14 (14.67, Nivel bajo) y `TQ80`, 22/9/2026, datos 78, 76, 80 (78.00, Nivel normal); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `tanques.txt` (10 en total) y correr el programa | `Se cargaron 8 tanques`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Nivel de tanques de gas LP)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `tanques.txt` abierto en el Bloc de notas:

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
| Buscar por clave | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
