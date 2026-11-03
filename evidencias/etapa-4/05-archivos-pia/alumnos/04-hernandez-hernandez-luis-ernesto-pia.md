# PIA — Radares de velocidad en un tramo

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 04 — Hernández Hernández Luis Ernesto

## Historia de usuario

**Como** agente de tránsito de una carretera, **quiero** que los vehículos que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada vehículo se volvió un registro dentro de un arreglo de
structs, y ahora los vehículos se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se registran como máximo **8 vehículos**.
- De cada vehículo se registra su **placa**, una sola palabra sin espacios (por ejemplo `ABC123`), y su **fecha de verificación**: la fecha de su última verificación vehicular, con día, mes y año. **No puede haber dos vehículos con la misma placa.**
- Cada vehículo pasa por **3 radares** a lo largo del tramo.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2015 y 2026**.
- Una velocidad es válida si está entre **0 y 250 km/h**.
- Un vehículo va **dentro del límite** si el **promedio** de sus 3 velocidades es **menor o igual a 80 km/h**; si no, va **en exceso de velocidad**.
- Todos los vehículos se guardan en el archivo **`vehiculos.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
RADARES DEL TRAMO CARRETERO

1.- Alta de un vehiculo
2.- Buscar un vehiculo
3.- Cambiar los datos de un vehiculo
4.- Desplegar vehiculos
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los vehículos de `vehiculos.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide la placa; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de verificación y los 3 datos, muestra su promedio y su
  clasificación, y **agrega** el vehículo al final de `vehiculos.txt`.
- **Opción 2 — Buscar:** pide la placa y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la placa; si existe, muestra sus datos actuales, pide sus
  3 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `vehiculos.txt` completo. La placa y la fecha de verificación no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los vehículos, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos vehículos hay, el **promedio de velocidad de los vehículos** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los vehículos que ya están registrados. Crea el archivo **`vehiculos.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
ABC123 14 4 2025 72 78 75
XYZ789 30 9 2026 95 102 88
MNL456 7 4 2026 80 80 80
RTS321 21 1 2024 85 79 82
GHK852 18 6 2025 110 98 104
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `ABC123 14 4 2025 72 78 75` | 75.00 km/h | Dentro del limite |
| 2 | `XYZ789 30 9 2026 95 102 88` | 95.00 km/h | Exceso de velocidad |
| 3 | `MNL456 7 4 2026 80 80 80` | 80.00 km/h | Dentro del limite |
| 4 | `RTS321 21 1 2024 85 79 82` | 82.00 km/h | Exceso de velocidad |
| 5 | `GHK852 18 6 2025 110 98 104` | 104.00 km/h | Exceso de velocidad |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 vehículos:

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
int n;    // cuantos vehículos hay en el arreglo
```

**En el archivo**, un renglón por vehículo, con los campos separados por un espacio:

```
placa dia mes anio velocidades[0] velocidades[1] velocidades[2]
```

Por ejemplo, `ABC123 14 4 2025 72 78 75` es el vehículo `ABC123`, con fecha de verificación 14/4/2025 y
datos 72, 78, 75.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioVelocidad`, y se guarda en el campo `promedioVelocidad`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_VEHICULOS && entrada >> vehiculos[n].placa)`; dentro del `while` se leen la fecha y los 3 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaVehiculo` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarVehiculos(Vehiculo vehiculos[])` | Abre `vehiculos.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarVehiculos(Vehiculo vehiculos[], int n)` | **Reescribe** `vehiculos.txt` completo con los `n` vehículos del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Vehiculo vehiculos[], int n, string placa)` | Regresa la posición del vehículo con esa placa, o -1 si no está | No |
| `double calcularPromedioVelocidad(double velocidades[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarVelocidad(double promedioVelocidad)` | Regresa `"Dentro del limite"` o `"Exceso de velocidad"` (la misma de tu Evidencia 3.2) | No |
| `int altaVehiculo(Vehiculo vehiculos[], int n)` | **Opción 1.** Registra un vehículo nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarVehiculo(Vehiculo vehiculos[], int n)` | **Opción 2.** Busca un vehículo y muestra todos sus datos | Sí |
| `void cambiarVehiculo(Vehiculo vehiculos[], int n)` | **Opción 3.** Cambia los datos de un vehículo y reescribe el archivo | Sí |
| `void desplegarVehiculos(Vehiculo vehiculos[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Vehiculo vehiculos[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaVehiculo` y `cambiarVehiculo` usan `buscarPosicion` y `calcularPromedioVelocidad`, y `cargarVehiculos` usa
`calcularPromedioVelocidad`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Vehiculo` con los campos
      `placa` (`string`), `verificacion` (`Fecha`), `velocidades` (arreglo `double` de 3) y `promedioVelocidad` (`double`).
- [ ] Los vehículos se guardan en un arreglo de structs `Vehiculo vehiculos[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por vehículo (3), los límites de
      un dato (0 y 250), los del año (2015 y 2026), el límite de
      la clasificación (80) y el nombre del archivo (`"vehiculos.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarVehiculos`, `guardarVehiculos`, `buscarPosicion`, `calcularPromedioVelocidad` y `clasificarVelocidad`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioVelocidad` y se guarda en `promedioVelocidad`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los vehículos del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 vehículos, aunque el archivo tenga más renglones: `n < MAX_VEHICULOS` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del vehículo cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 vehículos, avisa que el registro está lleno y no pide nada; si la
      placa ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 250 km/h. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del vehículo (placa, fecha de verificación, los 3 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la placa no existe; si existe, muestra los datos actuales, pide los
      3 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por vehículo, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos vehículos hay, el promedio de velocidad de los vehículos y cuántos hay de cada
      clasificación.
- [ ] Si no hay vehículos registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 vehiculos de vehiculos.txt

RADARES DEL TRAMO CARRETERO

1.- Alta de un vehiculo
2.- Buscar un vehiculo
3.- Cambiar los datos de un vehiculo
4.- Desplegar vehiculos
5.- Resumen general
6.- Salir

Opcion: 4

VEHICULOS REGISTRADOS

Placa    Fecha             R1      R2      R3   Promedio
ABC123   14/4/2025      72.00   78.00   75.00      75.00   Dentro del limite
XYZ789   30/9/2026      95.00  102.00   88.00      95.00   Exceso de velocidad
MNL456   7/4/2026       80.00   80.00   80.00      80.00   Dentro del limite
RTS321   21/1/2024      85.00   79.00   82.00      82.00   Exceso de velocidad
GHK852   18/6/2025     110.00   98.00  104.00     104.00   Exceso de velocidad
```

Alta con placa repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE VEHICULO
  Placa: MNL456
  ERROR! Ya existe un vehiculo con esa placa

Opcion: 1

ALTA DE VEHICULO
  Placa: JKL159
  Fecha de verificacion
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 15
    Mes: 4
    Anio: 2025
  Radares
    Radar 1: 84
    Radar 2: 300
    ERROR! El dato debe estar entre 0 y 250 km/h
    Radar 2: 90
    Radar 3: 82

Promedio: 85.33 km/h -> Exceso de velocidad
Vehiculo agregado a vehiculos.txt
```

Búsqueda:

```
Opcion: 2
Placa a buscar: XYZ789

Placa: XYZ789
Fecha de verificacion: 30/9/2026
Radares: R1 95.00, R2 102.00, R3 88.00
Promedio: 95.00 km/h -> Exceso de velocidad
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN VEHICULO
  Placa: ABC123

  Datos actuales: R1 72.00, R2 78.00, R3 75.00  (Promedio 75.00 km/h, Dentro del limite)
  Datos nuevos
    Radar 1: 95
    Radar 2: 102
    Radar 3: 88

Promedio: 95.00 km/h -> Exceso de velocidad
Se reescribio vehiculos.txt con 6 vehiculos
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Vehiculos registrados: 6
Promedio de velocidad de los vehiculos: 90.22 km/h
Dentro del limite: 1
Exceso de velocidad: 5
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `vehiculos.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `vehiculos.txt` en la carpeta | `Se cargaron 0 vehiculos`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay vehículos registrados; la 2 y la 3 no piden la placa |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `JKL159`, 15/4/2025, datos 84, 90, 82 | Promedio 85.33 km/h → Exceso de velocidad; aparece `vehiculos.txt` con un solo renglón: `JKL159 15 4 2025 84 90 82` |
| 4 | Carga del archivo inicial | Borrar `vehiculos.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 vehiculos` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `ABC123` 75.00 (Dentro del limite); `XYZ789` 95.00 (Exceso de velocidad); `MNL456` 80.00 (Dentro del limite); `RTS321` 82.00 (Exceso de velocidad); `GHK852` 104.00 (Exceso de velocidad) |
| 6 | Búsqueda encontrada | Opción 2, `XYZ789` | Todos sus datos: 30/9/2026; 95.00, 102.00, 88.00; promedio 95.00 km/h → Exceso de velocidad |
| 7 | Búsqueda no encontrada | Opción 2, `GHK859` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `xyz789` | Aviso de que no se encontró: `xyz789` y `XYZ789` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 vehículos; promedio de velocidad de los vehículos: 87.20 km/h; Dentro del limite: 2; Exceso de velocidad: 3 |
| 10 | Placa repetida | Opción 1, `MNL456` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `JKL159`: día 0 y 32, mes 13, año 2014 y 2027, un dato de 300 y de -10; después 15/4/2025 y datos 84, 90, 82 | Error en cada dato no válido y lo vuelve a pedir; promedio 85.33 km/h → Exceso de velocidad |
| 12 | El alta agrega al final | Abrir `vehiculos.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `JKL159 15 4 2025 84 90 82` |
| 13 | Cambio de vehículo que no existe | Opción 3, `GHK859` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `ABC123`; un dato de 300; después 95, 102, 88 | Muestra sus datos actuales; error con 300 y vuelve a pedir ese mismo radar; nuevo promedio 95.00 km/h → Exceso de velocidad |
| 15 | El cambio reescribe el archivo | Abrir `vehiculos.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `ABC123 14 4 2025 95 102 88` |
| 16 | Resumen después de los cambios | Opción 5 | 6 vehículos; promedio de velocidad de los vehículos: 90.22 km/h; Dentro del limite: 1; Exceso de velocidad: 5 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 vehiculos`; la tabla muestra los 6, con `ABC123` ya cambiado y `JKL159` al final |
| 18 | Registro lleno | Opción 1 con `PQR753`, 28/9/2026, datos 79, 82, 85 (82.00, Exceso de velocidad) y `WXY258`, 8/4/2026, datos 98, 104, 110 (104.00, Exceso de velocidad); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la placa |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `vehiculos.txt` (10 en total) y correr el programa | `Se cargaron 8 vehiculos`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Radares de velocidad en un tramo)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `vehiculos.txt` abierto en el Bloc de notas:

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
| Buscar por placa | [2.6 Búsqueda lineal](../../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y el contador | [3.4](../../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5](../../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo | [4.8 Ficheros en C++](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final con `ios::app` | [4.9 Modos de apertura](../../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un dato del archivo | [4.10 Actualización de archivos secuenciales](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, paso a paso | [Ejercicios de la Etapa IV](../../../../ejercicios/etapa-4-archivos/README.md) |
