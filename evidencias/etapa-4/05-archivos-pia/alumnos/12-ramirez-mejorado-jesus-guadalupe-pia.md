# PIA — Monitoreo de CO2 en salones

*Etapa IV — Archivos · Evidencia 4.2 y Producto Integrador de Aprendizaje · Entrega: sábado 14 de noviembre de 2026, 10:00 p.m. · [Instrucciones generales y rúbrica](../descripcion.md) · [Ejemplo resuelto de la bitácora](../ejemplo-resuelto/README.md)*

**Alumno:** 12 — Ramirez Mejorado Jesus Guadalupe

## Historia de usuario

**Como** coordinador de mantenimiento de una escuela, **quiero** que los salones que registro se guarden en un archivo,
y poder buscarlos, corregir sus datos y ver un resumen general, **para** no perder el
registro cada vez que se cierra el programa y tener a la mano el estado de todos.

## Contexto

Es tu programa de la Evidencia 3.2, **por tercera vez**: en la 2.2 los datos vivían en una
matriz y un vector, en la 3.2 cada salón se volvió un registro dentro de un arreglo de
structs, y ahora los salones se **guardan en un archivo**. Al cerrar el programa ya no se
pierde nada: la próxima vez que lo abras, carga lo que había.

**Reglas**

- Se revisan como máximo **8 salones**.
- De cada salón se registra su **clave**, una sola palabra sin espacios (por ejemplo `A101`), y su **fecha de mantenimiento**: la fecha del último mantenimiento del aire acondicionado del salón, con día, mes y año. **No puede haber dos salones con la misma clave.**
- A cada salón se le toman **4 lecturas** al día.
- Una fecha es válida si el día está entre **1 y 31**, el mes entre **1 y 12** y el año entre **2020 y 2026**.
- Una lectura es válida si está entre **0 y 5000 ppm**.
- Un salón está en **nivel normal** si el **promedio** de sus 4 lecturas es **menor o igual a 1000 ppm**; si no, **necesita ventilación**.
- Todos los salones se guardan en el archivo **`salones.txt`**, que vive en la misma carpeta que tu programa.

El programa se controla con este menú, y solo termina cuando el usuario elige la
opción 6:

```
MONITOREO DE CO2

1.- Alta de un salon
2.- Buscar un salon
3.- Cambiar los datos de un salon
4.- Desplegar salones
5.- Resumen general
6.- Salir
```

- **Al iniciar** (antes del menú), carga los salones de `salones.txt` y avisa cuántos cargó.
- **Opción 1 — Alta:** pide la clave; si ya existe, muestra un error y regresa al menú
  sin pedir nada más. Si no existe, pide la fecha de mantenimiento y los 4 datos, muestra su promedio y su
  clasificación, y **agrega** el salón al final de `salones.txt`.
- **Opción 2 — Buscar:** pide la clave y muestra **todos** sus datos, o avisa que no se encontró.
- **Opción 3 — Cambiar:** pide la clave; si existe, muestra sus datos actuales, pide sus
  4 datos **nuevos**, recalcula su promedio, muestra su nueva clasificación y **reescribe**
  `salones.txt` completo. La clave y la fecha de mantenimiento no cambian.
- **Opción 4 — Desplegar:** muestra la tabla de todos los salones, en el orden del archivo.
- **Opción 5 — Resumen general:** muestra cuántos salones hay, el **promedio de CO2 de la escuela** (el
  promedio de los promedios de todos) y cuántos hay de cada clasificación.
- **Opción 6:** termina el programa.

Todos los números con decimales se muestran con **2 decimales** (`7.50`, `75.00`), con
`fixed` y `setprecision` ([1.2](../../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar)).

## Lo que ya está definido

Estos son los salones que ya están registrados. Crea el archivo **`salones.txt`** con el Bloc
de notas, en la carpeta de tu programa, con **exactamente** estos 5 renglones. Los casos de
prueba dependen de ellos.

```
A101 22 5 2026 650 720 800 830
A102 9 1 2025 1100 1250 980 1310
B201 3 5 2025 1000 1000 1000 1000
B202 14 8 2026 500 600 550 650
C301 30 3 2024 1400 1500 1200 1300
```

Así se lee cada renglón:

| # | Renglón | Promedio | Clasificación |
|---|---|---|---|
| 1 | `A101 22 5 2026 650 720 800 830` | 750.00 ppm | Nivel normal |
| 2 | `A102 9 1 2025 1100 1250 980 1310` | 1160.00 ppm | Necesita ventilacion |
| 3 | `B201 3 5 2025 1000 1000 1000 1000` | 1000.00 ppm | Nivel normal |
| 4 | `B202 14 8 2026 500 600 550 650` | 575.00 ppm | Nivel normal |
| 5 | `C301 30 3 2024 1400 1500 1200 1300` | 1350.00 ppm | Necesita ventilacion |

## Cómo se organizan los datos

**En memoria**, igual que en la 3.2, pero con lugar para 8 salones:

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
int n;    // cuantos salones hay en el arreglo
```

**En el archivo**, un renglón por salón, con los campos separados por un espacio:

```
clave dia mes anio lecturas[0] lecturas[1] lecturas[2] lecturas[3]
```

Por ejemplo, `A101 22 5 2026 650 720 800 830` es el salón `A101`, con fecha de mantenimiento 22/5/2026 y
datos 650, 720, 800, 830.

**El promedio no se guarda en el archivo**: se **calcula** al cargar cada renglón, al dar de alta
y al cambiar los datos, con `calcularPromedioCO2`, y se guarda en el campo `promedioCO2`. Las opciones
2, 4 y 5 lo **leen** de ahí.

**Cuándo se toca el archivo**

| Momento | Qué se hace | Cómo ([4.8](../../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) a [4.10](../../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)) |
|---|---|---|
| Al iniciar | Se **carga** todo el archivo en el arreglo | `ifstream` y `while (n < MAX_SALONES && entrada >> salones[n].clave)`; dentro del `while` se leen la fecha y los 4 datos |
| Opción 1 | Se **agrega** un renglón al final | `ofstream` con `ios::app` |
| Opción 3 | Se **reescribe** el archivo completo con el arreglo | `ofstream` en su modo normal, que vacía el archivo |
| Opciones 2, 4 y 5 | Nada: trabajan con el arreglo | — |

### Las funciones

Cada opción del menú vive en su **propia función**, y `main` solo carga el archivo, muestra el
menú (con `switch`) y llama a la función de la opción elegida. Cómo se pasa un arreglo de
structs a una función, por qué no lleva `&` y por qué `altaSalon` regresa el nuevo `n`, está en
[1.5 Paso de parámetros](../../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md#un-arreglo-de-structs-como-parámetro).

Las funciones deben llamarse **exactamente** así y recibir estos parámetros, con estos tipos:

| Función | Qué hace | ¿Usa `cin` o `cout`? |
|---|---|---|
| `int cargarSalones(Salon salones[])` | Abre `salones.txt`, carga sus renglones en el arreglo (como máximo 8), calcula el promedio de cada uno y regresa cuántos cargó. Si el archivo no existe, regresa 0 | No |
| `int guardarSalones(Salon salones[], int n)` | **Reescribe** `salones.txt` completo con los `n` salones del arreglo. Regresa cuántos escribió, o -1 si no pudo abrir el archivo | No |
| `int buscarPosicion(Salon salones[], int n, string clave)` | Regresa la posición del salón con esa clave, o -1 si no está | No |
| `double calcularPromedioCO2(double lecturas[], int cantidad)` | Regresa el promedio de los datos del arreglo | No |
| `string clasificarCO2(double promedioCO2)` | Regresa `"Nivel normal"` o `"Necesita ventilacion"` (la misma de tu Evidencia 3.2) | No |
| `int altaSalon(Salon salones[], int n)` | **Opción 1.** Registra un salón nuevo y lo agrega al final del archivo. Regresa el nuevo `n` | Sí |
| `void consultarSalon(Salon salones[], int n)` | **Opción 2.** Busca un salón y muestra todos sus datos | Sí |
| `void cambiarSalon(Salon salones[], int n)` | **Opción 3.** Cambia los datos de un salón y reescribe el archivo | Sí |
| `void desplegarSalones(Salon salones[], int n)` | **Opción 4.** Muestra la tabla | Sí |
| `void mostrarResumen(Salon salones[], int n)` | **Opción 5.** Muestra el resumen general | Sí |

Las cinco primeras **no** usan `cin` ni `cout`: las usan las funciones de opción. Por ejemplo,
`altaSalon` y `cambiarSalon` usan `buscarPosicion` y `calcularPromedioCO2`, y `cargarSalones` usa
`calcularPromedioCO2`. Puedes agregar otras funciones si te ayudan.

## Criterios de aceptación

Están agrupados según los tres criterios de las
[rúbrica](../descripcion.md#rúbrica-de-evaluación). Si cumples **todos** los de una
sección, alcanzas el nivel **Evidencia completa** de ese criterio.

### Conocimientos (3 puntos) — Estructuras, funciones y archivos

- [ ] Define `struct Fecha` (`dia`, `mes`, `anio`) y, después, `struct Salon` con los campos
      `clave` (`string`), `mantenimiento` (`Fecha`), `lecturas` (arreglo `double` de 4) y `promedioCO2` (`double`).
- [ ] Los salones se guardan en un arreglo de structs `Salon salones[8]` con un contador `n`.
- [ ] Son constantes con nombre: el máximo (8), los datos por salón (4), los límites de
      un dato (0 y 5000), los del año (2020 y 2026), el límite de
      la clasificación (1000) y el nombre del archivo (`"salones.txt"`).
- [ ] Tiene las **10 funciones** de la tabla, con esos nombres, parámetros y tipos. `main` solo
      carga, muestra el menú con `switch` y llama a las funciones.
- [ ] `cargarSalones`, `guardarSalones`, `buscarPosicion`, `calcularPromedioCO2` y `clasificarCO2`
      no usan `cin` ni `cout`.
- [ ] El promedio se calcula **solo** con `calcularPromedioCO2` y se guarda en `promedioCO2`; las opciones 2, 4
      y 5 lo leen de ese campo.
- [ ] Lee el archivo con `while (... entrada >> ...)`, no con `eof()`; agrega con `ios::app` y
      reescribe con el modo normal.

### Habilidades (5 puntos) — Manejo del archivo y solución del problema

**Maneja el archivo correctamente**

- [ ] Al iniciar carga todos los salones del archivo y avisa cuántos. Si el archivo no
      existe, empieza con 0, sin error.
- [ ] La carga no pasa de 8 salones, aunque el archivo tenga más renglones: `n < MAX_SALONES` se
      revisa **antes** de leer.
- [ ] El alta agrega **un** renglón al final, con el formato de arriba, sin borrar los anteriores.
- [ ] El cambio reescribe el archivo completo: quedan los mismos renglones, en el mismo orden, y
      solo cambian los datos del salón cambiado.
- [ ] Lo registrado y lo cambiado sigue ahí al cerrar y volver a abrir el programa.

**Soluciona cada requerimiento**

- [ ] Alta: si ya hay 8 salones, avisa que el registro está lleno y no pide nada; si la
      clave ya existe, muestra un error y no pide la fecha ni los datos.
- [ ] Alta y cambio: el día, el mes y el año se validan con sus rangos; cada dato debe estar entre
      0 y 5000 ppm. Si un dato no es válido, muestra un error y vuelve a pedir
      **ese mismo** dato.
- [ ] Buscar muestra **todos** los datos del salón (clave, fecha de mantenimiento, los 4 datos, promedio y
      clasificación) o avisa que no se encontró.
- [ ] Cambiar avisa si la clave no existe; si existe, muestra los datos actuales, pide los
      4 nuevos, recalcula el promedio y muestra la nueva clasificación.
- [ ] Desplegar muestra una fila por salón, en el orden del archivo, con todos sus datos.
- [ ] El resumen muestra cuántos salones hay, el promedio de CO2 de la escuela y cuántos hay de cada
      clasificación.
- [ ] Si no hay salones registrados, las opciones 2 a 5 muestran un aviso en lugar de pedir
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
Se cargaron 5 salones de salones.txt

MONITOREO DE CO2

1.- Alta de un salon
2.- Buscar un salon
3.- Cambiar los datos de un salon
4.- Desplegar salones
5.- Resumen general
6.- Salir

Opcion: 4

SALONES REGISTRADOS

Clave   Fecha              L1       L2       L3       L4   Promedio
A101    22/5/2026      650.00   720.00   800.00   830.00     750.00   Nivel normal
A102    9/1/2025      1100.00  1250.00   980.00  1310.00    1160.00   Necesita ventilacion
B201    3/5/2025      1000.00  1000.00  1000.00  1000.00    1000.00   Nivel normal
B202    14/8/2026      500.00   600.00   550.00   650.00     575.00   Nivel normal
C301    30/3/2024     1400.00  1500.00  1200.00  1300.00    1350.00   Necesita ventilacion
```

Alta con clave repetida y alta con datos no válidos:

```
Opcion: 1

ALTA DE SALON
  Clave: B201
  ERROR! Ya existe un salon con esa clave

Opcion: 1

ALTA DE SALON
  Clave: C302
  Fecha de mantenimiento
    Dia: 32
    ERROR! El dia debe estar entre 1 y 31
    Dia: 23
    Mes: 5
    Anio: 2026
  Lecturas
    Lectura 1: 875
    Lectura 2: 5200
    ERROR! El dato debe estar entre 0 y 5000 ppm
    Lectura 2: 985
    Lectura 3: 890
    Lectura 4: 1070

Promedio: 955.00 ppm -> Nivel normal
Salon agregado a salones.txt
```

Búsqueda:

```
Opcion: 2
Clave a buscar: A102

Clave: A102
Fecha de mantenimiento: 9/1/2025
Lecturas: L1 1100.00, L2 1250.00, L3 980.00, L4 1310.00
Promedio: 1160.00 ppm -> Necesita ventilacion
```

Cambio de datos:

```
Opcion: 3

CAMBIAR LOS DATOS DE UN SALON
  Clave: A101

  Datos actuales: L1 650.00, L2 720.00, L3 800.00, L4 830.00  (Promedio 750.00 ppm, Nivel normal)
  Datos nuevos
    Lectura 1: 1100
    Lectura 2: 1250
    Lectura 3: 980
    Lectura 4: 1310

Promedio: 1160.00 ppm -> Necesita ventilacion
Se reescribio salones.txt con 6 salones
```

Resumen, después del alta y el cambio:

```
Opcion: 5

RESUMEN GENERAL

Salones registrados: 6
Promedio de CO2 de la escuela: 1033.33 ppm
Nivel normal: 3
Necesita ventilacion: 3
```

Los mensajes y la alineación pueden variar; lo importante es que los datos, los cálculos y el
archivo sean correctos.

## Casos de prueba

Ejecútalos en orden. Los casos 1 a 3 parten **sin** `salones.txt`; desde el caso 4 se parte del
archivo inicial. Se supone que en los datos numéricos se escriben números.

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Sin archivo | Correr el programa sin `salones.txt` en la carpeta | `Se cargaron 0 salones`; sin error |
| 2 | Consultas sin registros | Sin archivo: opciones 2, 3, 4 y 5 | Cada una avisa que no hay salones registrados; la 2 y la 3 no piden la clave |
| 3 | El alta crea el archivo | Sin archivo: opción 1 con `C302`, 23/5/2026, datos 875, 985, 890, 1070 | Promedio 955.00 ppm → Nivel normal; aparece `salones.txt` con un solo renglón: `C302 23 5 2026 875 985 890 1070` |
| 4 | Carga del archivo inicial | Borrar `salones.txt`, crear el [archivo inicial](#lo-que-ya-está-definido) y correr el programa | `Se cargaron 5 salones` |
| 5 | Desplegar | Opción 4 | Los 5, en el orden del archivo: `A101` 750.00 (Nivel normal); `A102` 1160.00 (Necesita ventilacion); `B201` 1000.00 (Nivel normal); `B202` 575.00 (Nivel normal); `C301` 1350.00 (Necesita ventilacion) |
| 6 | Búsqueda encontrada | Opción 2, `A102` | Todos sus datos: 9/1/2025; 1100.00, 1250.00, 980.00, 1310.00; promedio 1160.00 ppm → Necesita ventilacion |
| 7 | Búsqueda no encontrada | Opción 2, `C309` | Aviso de que no se encontró |
| 8 | Mayúsculas distintas | Opción 2, `a102` | Aviso de que no se encontró: `a102` y `A102` son textos distintos |
| 9 | Resumen inicial | Opción 5 | 5 salones; promedio de CO2 de la escuela: 967.00 ppm; Nivel normal: 3; Necesita ventilacion: 2 |
| 10 | Clave repetida | Opción 1, `B201` | Error; **no** pide la fecha ni los datos y el archivo no cambia |
| 11 | Alta con datos no válidos | Opción 1, `C302`: día 0 y 32, mes 13, año 2019 y 2027, un dato de 5200 y de -10; después 23/5/2026 y datos 875, 985, 890, 1070 | Error en cada dato no válido y lo vuelve a pedir; promedio 955.00 ppm → Nivel normal |
| 12 | El alta agrega al final | Abrir `salones.txt` con el Bloc de notas | 6 renglones: los 5 iniciales sin cambios y al final `C302 23 5 2026 875 985 890 1070` |
| 13 | Cambio de salón que no existe | Opción 3, `C309` | Aviso de que no se encontró; no pide datos |
| 14 | Cambio de datos | Opción 3, `A101`; un dato de 5200; después 1100, 1250, 980, 1310 | Muestra sus datos actuales; error con 5200 y vuelve a pedir esa misma lectura; nuevo promedio 1160.00 ppm → Necesita ventilacion |
| 15 | El cambio reescribe el archivo | Abrir `salones.txt` con el Bloc de notas | 6 renglones en el mismo orden; solo cambió el primero: `A101 22 5 2026 1100 1250 980 1310` |
| 16 | Resumen después de los cambios | Opción 5 | 6 salones; promedio de CO2 de la escuela: 1033.33 ppm; Nivel normal: 3; Necesita ventilacion: 3 |
| 17 | Lo guardado no se pierde | Salir (opción 6), volver a correr el programa y elegir la opción 4 | `Se cargaron 6 salones`; la tabla muestra los 6, con `A101` ya cambiado y `C302` al final |
| 18 | Registro lleno | Opción 1 con `D401`, 10/1/2025, datos 600, 550, 650, 500 (575.00, Nivel normal) y `D402`, 4/5/2025, datos 1500, 1200, 1300, 1400 (1350.00, Necesita ventilacion); después otra vez la opción 1 | Los dos se registran (8 en total); la tercera alta avisa que el registro está lleno y no pide la clave |
| 19 | Archivo con más renglones de los que caben | Agregar a mano 2 renglones más al final de `salones.txt` (10 en total) y correr el programa | `Se cargaron 8 salones`; el programa no falla ni escribe fuera del arreglo |
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
    Nombre completo, número y contexto (Monitoreo de CO2 en salones)

Pruebas
    Un apartado por cada caso de la tabla de Casos de prueba: del Caso 1 al Caso 20, en orden
```

**Documentas los 20 casos** de la tabla de *Casos de prueba*: córrelos en orden, como dice esa
tabla, y en cada uno toma la captura de la consola. En los casos que tocan el archivo agrega
también la captura de `salones.txt` abierto en el Bloc de notas:

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
