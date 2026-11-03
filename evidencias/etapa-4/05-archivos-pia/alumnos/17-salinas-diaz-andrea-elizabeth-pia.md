# PIA — Ocupación del estacionamiento por piso

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 17 — Salinas Diaz Andrea Elizabeth

## Historia de usuario

**Como** administrador del estacionamiento de un centro comercial, **quiero** que los pisos que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada piso se volvió un registro dentro de un arreglo de
structs, y ahora los pisos se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- El estacionamiento tiene como máximo **8 pisos**.
- De cada piso se registra su **clave**, una sola palabra sin espacios (por ejemplo `N1`), y su **fecha de señalización**: la fecha en que se pintó por última vez la señalización del piso, con día, mes y año. **No puede haber dos pisos con la misma clave.**
- De cada piso se toman **5 mediciones** de ocupación durante la tarde.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Una medición es válida si está entre **0 y 100%**.
- Un piso se considera **lleno** si el **promedio** de sus 5 mediciones es **mayor o igual a 95%**; si es menor, está **disponible**.
- Todos los pisos se guardan en el archivo **`pisos.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
OCUPACION DEL ESTACIONAMIENTO

1.- Alta de un piso
2.- Buscar un piso
3.- Cambiar los datos de un piso
4.- Desplegar pisos
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los pisos de `pisos.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de señalización y los 5 datos, muestra su promedio y su
  clasificación, y **agrega** el piso al final de `pisos.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  5 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `pisos.txt` completo. La clave y la fecha de señalización no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los pisos, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos pisos hay, el **promedio de ocupación del estacionamiento** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los pisos que ya están registrados. Crea el archivo **`pisos.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
N1 13 2 2024 60 75 82 90 68
N2 5 10 2025 96 98 100 94 97
N3 28 2 2026 95 95 95 95 95
N4 19 6 2023 88 92 97 99 94
N5 9 12 2025 40 55 50 45 60
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `N1 13 2 2024 60 75 82 90 68` | 75.00% | Disponible |
| 2 | `N2 5 10 2025 96 98 100 94 97` | 97.00% | Lleno |
| 3 | `N3 28 2 2026 95 95 95 95 95` | 95.00% | Lleno |
| 4 | `N4 19 6 2023 88 92 97 99 94` | 94.00% | Disponible |
| 5 | `N5 9 12 2025 40 55 50 45 60` | 50.00% | Disponible |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 pisos:

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
int n;    // cuantos pisos hay en el arreglo
```

**En el archivo**, un renglón por piso, con los campos separados por un espacio:

```
clave dia mes anio ocupacion[0] ocupacion[1] ocupacion[2] ocupacion[3] ocupacion[4]
```

Por ejemplo, `N1 13 2 2024 60 75 82 90 68` es el piso `N1`, con fecha de señalización 13/2/2024 y
datos 60, 75, 82, 90, 68.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioOcupacion`, y se guarda en el campo `promedioOcupacion`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_PISOS && entrada >> pisos[n].clave)`; dentro del `while` se leen la fecha y los 5 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaPiso` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarPisos(Piso pisos[])` | Abre `pisos.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarPisos(Piso pisos[], int n)` | **Reescribe** `pisos.txt` completo con los `n` pisos del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Piso pisos[], int n, string clave)` | Regresa la posición del piso con esa clave, o -1 si no está | No |
| `double calcularPromedioOcupacion(double ocupacion[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarOcupacion(double promedioOcupacion)` | Regresa `"Disponible"` o `"Lleno"` (la misma de tu Evidencia 3.2) | No |
| `int altaPiso(Piso pisos[], int n)` | **Opción 1.** Registra un piso nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarPiso(Piso pisos[], int n)` | **Opción 2.** Busca un piso y muestra todos sus datos | Sí |
| `void cambiarPiso(Piso pisos[], int n)` | **Opción 3.** Cambia los datos de un piso y reescribe el archivo | Sí |
| `void desplegarPisos(Piso pisos[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Piso pisos[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaPiso` y `cambiarPiso` usan `buscarPosicion` y `calcularPromedioOcupacion`, y `cargarPisos` usa
`calcularPromedioOcupacion`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Piso` con los campos
      `clave` (`string`), `senalizacion` (`Fecha`), `ocupacion` (arreglo `double` de 5) y `promedioOcupacion` (`double`).
- [ ] Los pisos se guardan en un arreglo de structs `Piso pisos[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por piso (5), los límites de
      un dato (0 y 100), los del año (2015 y 2026), el límite de
      la clasificación (95) y el nombre del archivo (`"pisos.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarPisos`, `guardarPisos`, `buscarPosicion`, `calcularPromedioOcupacion` y `clasificarOcupacion`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioOcupacion` y se guarda en `promedioOcupacion`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los pisos del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 pisos, aunque el archivo tenga más renglones: `n < MAX_PISOS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del piso cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 pisos, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 100%. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del piso (clave, fecha de señalización, los 5 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      5 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por piso, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos pisos hay, el promedio de ocupación del estacionamiento y cuántos hay de cada
      clasificación.
- [ ] Si no hay pisos registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 pisos de pisos.txt

OCUPACION DEL ESTACIONAMIENTO

1.- Alta de un piso
2.- Buscar un piso
3.- Cambiar los datos de un piso
4.- Desplegar pisos
5.- Resumen general
6.- Salir

Opcion: 4

PISOS REGISTRADOS

Clave   Fecha             M1      M2      M3      M4      M5   Promedio
N1      13/2/2024      60.00   75.00   82.00   90.00   68.00      75.00   Disponible
N2      5/10/2025      96.00   98.00  100.00   94.00   97.00      97.00   Lleno
N3      28/2/2026      95.00   95.00   95.00   95.00   95.00      95.00   Lleno
N4      19/6/2023      88.00   92.00   97.00   99.00   94.00      94.00   Disponible
N5      9/12/2025      40.00   55.00   50.00   45.00   60.00      50.00   Disponible
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE PISO
  Clave: N3
  ERROR! Ya existe un piso con esa clave

Opcion: 1

ALTA DE PISO
  Clave: N6
  Fecha de senalizacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 14
    Mes: 2
    Anio: 2024
  Mediciones
    Medicion 1: 78
    Medicion 2: 105
    ERROR! El dato debe estar entre 0 y 100%
    Medicion 2: 87
    Medicion 3: 91
    Medicion 4: 92
    Medicion 5: 83

Promedio: 86.20% -> Disponible
Piso agregado a pisos.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: N2

Clave: N2
Fecha de senalizacion: 5/10/2025
Mediciones: M1 96.00, M2 98.00, M3 100.00, M4 94.00, M5 97.00
Promedio: 97.00% -> Lleno
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN PISO
  Clave: N1

  Datos actuales: M1 60.00, M2 75.00, M3 82.00, M4 90.00, M5 68.00  (Promedio 75.00%, Disponible)
  Datos nuevos
    Medicion 1: 96
    Medicion 2: 98
    Medicion 3: 100
    Medicion 4: 94
    Medicion 5: 97

Promedio: 97.00% -> Lleno
Se reescribio pisos.txt con 6 pisos
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Pisos registrados: 6
Promedio de ocupacion del estacionamiento: 86.53%
Disponible: 3
Lleno: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `pisos.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `pisos.txt` en la carpeta | `Se cargaron 0 pisos`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay pisos registrados; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `N6`, 14/2/2024, datos 78, 87, 91, 92, 83 | Promedio 86.20% → Disponible; aparece `pisos.txt` con un solo renglón: `N6 14 2 2024 78 87 91 92 83` |
| 4 | Carga del archivo inicial | Borrar `pisos.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 pisos` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `N1` 75.00 (Disponible); `N2` 97.00 (Lleno); `N3` 95.00 (Lleno); `N4` 94.00 (Disponible); `N5` 50.00 (Disponible) |
| 6 | Búsqueda encontrada | Opción 2, `N2` | Todos sus datos: 5/10/2025; 96.00, 98.00, 100.00, 94.00, 97.00; promedio 97.00% → Lleno |
| 7 | Búsqueda no encontrada | Opción 2, `N9` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `n2` | Aviso de que no se encontró: `n2` y `N2` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 pisos; promedio de ocupación del estacionamiento: 82.20%; Disponible: 3; Lleno: 2 |
| 10 | Clave repetida | Opción 1, `N3` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `N6`: día 0 y 32, mes 13, año 2014 y 2027, un dato de 105 y de -1; después 14/2/2024 y datos 78, 87, 91, 92, 83 | Error en cada dato no válido y lo vuelve a pedir; promedio 86.20% → Disponible |
| 12 | El alta agrega al final | Abrir `pisos.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `N6 14 2 2024 78 87 91 92 83` |
| 13 | Cambio de piso que no existe | Opción 3, `N9` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `N1`; un dato de 105; después 96, 98, 100, 94, 97 | Muestra sus datos actuales; error con 105 y vuelve a pedir esa misma medición; nuevo promedio 97.00% → Lleno |
| 15 | El cambio reescribe el archivo | Abrir `pisos.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `N1 13 2 2024 96 98 100 94 97` |
| 16 | Resumen después de los cambios | Opción 5 | 6 pisos; promedio de ocupación del estacionamiento: 86.53%; Disponible: 3; Lleno: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 pisos`; la tabla muestra los 6, con `N1` ya cambiado y `N6` al final |
| 18 | Registro lleno | Opción 1 con `N7`, 6/10/2025, datos 92, 97, 99, 94, 88 (94.00, Disponible) y `N8`, 28/2/2026, datos 55, 50, 45, 60, 40 (50.00, Disponible); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `pisos.txt` (10 en total) y correr el programa | `Se cargaron 8 pisos`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Ocupacion del estacionamiento por piso)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `pisos.txt` abierto en el Bloc de notas:

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
