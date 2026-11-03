# PIA — Programa (Evidencia 4.2 y Producto Integrador de Aprendizaje)

De manera **individual**, harás **un solo programa** en C++ que junta todo el curso: funciones
(Etapa I), arreglos (Etapa II), estructuras (Etapa III) y archivos (Etapa IV). Es tu programa
de la Evidencia 3.2, **por tercera vez**: ahora los registros se **guardan en un archivo**, se
pueden buscar, cambiar y resumir, y cada opción del menú vive en su propia función.

> **Entrega:** sábado 14 de noviembre de 2026, 10:00 p.m., en NEXUS: el **código** y una
> **bitácora de pruebas en PDF**, los mismos dos archivos en **dos** lugares (ver
> [Forma de entrega](#forma-de-entrega)).
>
> **Así debe verse tu bitácora:** [ejemplo resuelto](ejemplo-resuelto/README.md) · [PDF del ejemplo](ejemplo-resuelto/PIA_HilarioDaniel.pdf)

## El programa, en resumen

Un sistema que guarda hasta **8 registros** (empleados, lotes, vehículos, etc.) en un archivo
de texto y los administra con un menú de 6 opciones:

```
1.- Alta
2.- Buscar
3.- Cambiar los datos
4.- Desplegar
5.- Resumen general
6.- Salir
```

- Al iniciar, el programa **carga** el archivo en un **arreglo de structs**; si el archivo no
  existe, empieza sin registros.
- El **alta** rechaza un identificador repetido y **agrega** el registro nuevo al final del
  archivo (`ios::app`).
- **Cambiar** corrige los datos de un registro y **reescribe** el archivo completo (cargar,
  modificar y reescribir, como en [4.10](../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md)).
- El **resumen general** muestra cuántos registros hay, el promedio general de tu contexto y
  cuántos hay de cada clasificación.
- **Cada opción es una función** que recibe el arreglo de structs y el contador, con los
  nombres y parámetros exactos de tu enunciado. Las funciones de carga, guardado, búsqueda,
  cálculo y clasificación **no** usan `cin` ni `cout`.
- Los resultados se muestran con **2 decimales**.

**Lo que ya está definido.** Cada enunciado trae el contenido inicial del archivo: 5 registros
que creas con el Bloc de notas. Los casos de prueba dependen de ellos.

**Tienes que probar tu programa y demostrarlo.** Además del código entregas una **bitácora de
pruebas en PDF**: capturas de pantalla de tu programa corriendo los 20 casos de prueba, con lo
que esperabas y lo que obtuviste. Qué lleva exactamente está en la sección
*Bitácora de pruebas (PDF)* de tu enunciado, y así debe verse: [ejemplo resuelto](ejemplo-resuelto/README.md)
([PDF](ejemplo-resuelto/PIA_HilarioDaniel.pdf)). El profesor también corre sus propias pruebas sobre
tu código. **Sin el PDF, Habilidades queda en 3 como máximo.**

## Ejemplo resuelto

Antes de armar tu PDF, revisa el **[ejemplo resuelto](ejemplo-resuelto/README.md)**: un caso que no es
de ningún alumno ([su enunciado](ejemplo-resuelto/caso.md)), con su bitácora completa y todas sus
capturas. Así debe verse tu `PIA_ApellidoNombre.pdf`:
**[PDF del ejemplo](ejemplo-resuelto/PIA_HilarioDaniel.pdf)**.

## Tu enunciado

| # | Alumno | Contexto | Enunciado |
|---|---|---|---|
| 01 | Cruz Martinez Cielo Michelle | Registro de puntualidad semanal | [ver](alumnos/01-cruz-martinez-cielo-michelle-pia.md) |
| 02 | Espinosa Saucedo Angel Xavier | Control de calidad por lotes | [ver](alumnos/02-espinosa-saucedo-angel-xavier-pia.md) |
| 03 | Flores Hidalgo Carolina | Filtro de temperatura en un evento | [ver](alumnos/03-flores-hidalgo-carolina-pia.md) |
| 04 | Hernández Hernández Luis Ernesto | Radares de velocidad en un tramo | [ver](alumnos/04-hernandez-hernandez-luis-ernesto-pia.md) |
| 05 | Hernandez Lopez Jose | Consumo eléctrico mensual por semanas | [ver](alumnos/05-hernandez-lopez-jose-pia.md) |
| 06 | Ibarra Banda Alejandro Israel | Existencias por sucursal | [ver](alumnos/06-ibarra-banda-alejandro-israel-pia.md) |
| 07 | Ibarra Martinez Victor Miguel | Monitoreo de ruido industrial | [ver](alumnos/07-ibarra-martinez-victor-miguel-pia.md) |
| 08 | Martinez Rincon Vika Ludivina | Encuesta de satisfacción por cliente | [ver](alumnos/08-martinez-rincon-vika-ludivina-pia.md) |
| 09 | Moreno Mercado Fernando | Batería de laptops durante el día | [ver](alumnos/09-moreno-mercado-fernando-pia.md) |
| 10 | Ordaz Segura Melissa Alejandra | Turbidez del agua por punto de muestreo | [ver](alumnos/10-ordaz-segura-melissa-alejandra-pia.md) |
| 11 | Palacios Moreno Jael Yasmani | Tiempos de atención de soporte técnico | [ver](alumnos/11-palacios-moreno-jael-yasmani-pia.md) |
| 12 | Ramirez Mejorado Jesus Guadalupe | Monitoreo de CO2 en salones | [ver](alumnos/12-ramirez-mejorado-jesus-guadalupe-pia.md) |
| 13 | Rangel Robles Donovan Antonio | Pruebas de tiempo de carga web | [ver](alumnos/13-rangel-robles-donovan-antonio-pia.md) |
| 14 | Rocha Ramirez Tomas De Jesus | Nivel de tanques de gas LP | [ver](alumnos/14-rocha-ramirez-tomas-de-jesus-pia.md) |
| 15 | Rodriguez Martinez Angel Ricardo | Tiempos de entrega por repartidor | [ver](alumnos/15-rodriguez-martinez-angel-ricardo-pia.md) |
| 16 | Roldan Reyes Alexis | Pruebas de resistencia por pieza | [ver](alumnos/16-roldan-reyes-alexis-pia.md) |
| 17 | Salinas Diaz Andrea Elizabeth | Ocupación del estacionamiento por piso | [ver](alumnos/17-salinas-diaz-andrea-elizabeth-pia.md) |
| 18 | Salinas Meza Cesar Eduardo | Consumo de datos móviles por semana | [ver](alumnos/18-salinas-meza-cesar-eduardo-pia.md) |
| 19 | Valles Arriaga Iker Karol | Tiempo de espera por caja | [ver](alumnos/19-valles-arriaga-iker-karol-pia.md) |
| 20 | Vazquez Palacios Angel Daniel | Vibración de maquinaria industrial | [ver](alumnos/20-vazquez-palacios-angel-daniel-pia.md) |

## Material de consulta

Hay dos temas que no vimos en clase y que el PIA necesita. Están escritos para que los
consultes por tu cuenta:

| Para… | Tema |
|---|---|
| Pasar el arreglo de structs a una función, y por qué la función de alta regresa el nuevo contador | [1.5 Paso de parámetros](../../../contenido/etapa-1-funciones/1.5-paso-de-parametros.md) (**nuevo**) |
| Mostrar los resultados con 2 decimales | [1.2 Funciones predefinidas — `<iomanip>`](../../../contenido/etapa-1-funciones/1.2-funciones-predefinidas.md#iomanip--cuántos-decimales-mostrar) (**nuevo**) |
| Buscar un registro por su identificador | [2.6 Búsqueda lineal](../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md) |
| El arreglo de structs y su contador | [3.4 Arreglos de registros](../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md) y [3.5 Estructuras anidadas](../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md) |
| Leer y escribir el archivo sin `eof()` | [4.8 Ficheros en C++](../../../contenido/etapa-4-archivos/4.8-ficheros-en-cpp.md) |
| Agregar al final del archivo | [4.9 Modos de apertura](../../../contenido/etapa-4-archivos/4.9-modos-de-apertura.md) |
| Cambiar un registro del archivo | [4.10 Actualización de archivos secuenciales](../../../contenido/etapa-4-archivos/4.10-actualizacion-de-archivos-secuenciales.md) |
| Un programa parecido, resuelto y explicado paso a paso | [Ejercicios de la Etapa IV](../../../ejercicios/etapa-4-archivos/README.md) |

---

## Entregables

Dos archivos:

| Archivo | Contenido |
|---|---|
| `PIA_ApellidoNombre.txt` | El código fuente en C++ de tu enunciado, como texto plano: NEXUS no acepta cargar archivos `.cpp` |
| `PIA_ApellidoNombre.pdf` | La bitácora de pruebas, con la estructura de la sección *Bitácora de pruebas (PDF)* de tu enunciado. Así debe verse: [ejemplo resuelto](ejemplo-resuelto/README.md) |

El programa debe compilar y ejecutarse sin errores en Dev-C++. **No** se entrega el archivo de
datos (`.txt` de los registros): el profesor prueba tu programa con el archivo inicial de tu
enunciado.

---

## Forma de entrega

- **Modalidad:** individual. Cada alumno entrega su propio archivo.
- **Plataforma:** NEXUS.
- **Fecha y hora límite:** sábado 14 de noviembre de 2026, 10:00 p.m.

El PIA se sube **dos veces**, con **los mismos dos archivos** (el `.txt` y el `.pdf`) en cada
lugar, para que cuente en la Etapa 4 y en el Producto Integrador:

| # | Dónde en NEXUS |
|---|---|
| 1 | Etapa 4 · **4.2 Evidencia de Aprendizaje 4: Programa** |
| 2 | Producto Integrador de Aprendizaje · **Programa** |

Si falta en alguno de los dos lugares, en ese lugar cuenta como no entregado.

Nombra tus archivos así:

```
PIA_ApellidoNombre.txt
PIA_ApellidoNombre.pdf
```

*Ejemplo: `PIA_CruzCielo.txt` y `PIA_CruzCielo.pdf`*

---

## Rúbrica de evaluación

Tu PIA se evalúa **una sola vez**, con esta rúbrica, contra los **criterios de aceptación** de tu
enunciado; la misma calificación cuenta en los dos lugares de NEXUS. Cada criterio de la rúbrica
corresponde a una sección de los criterios de aceptación: si cumples todos los de una sección,
alcanzas el nivel **Evidencia completa** de ese criterio.

| CRITERIO / NIVEL DE DOMINIO | Evidencia completa | Evidencia suficiente | Evidencia débil | Sin evidencia |
|-----------------------------|--------------------|---------------------|-----------------|---------------|
| **Conocimientos** — Identifica, escribe y utiliza adecuadamente estructuras, funciones y archivos. | **3** — Utiliza todos los conceptos aprendidos: cumple todos los criterios de la sección *Conocimientos* de su enunciado (structs, arreglo de structs con contador, constantes con nombre, las 10 funciones con su firma, funciones de carga, guardado, búsqueda, cálculo y clasificación sin `cin` ni `cout`, resultado calculado y guardado en su campo, lectura con `while (entrada >> ...)`, alta con `ios::app` y reescritura con el modo normal). | **2** — Utiliza la mayoría de los conceptos aprendidos: le falta un criterio de la sección *Conocimientos* (por ejemplo, lee con `eof()`, una función tiene otra firma o usa `cout`, o el nombre del archivo no es una constante). | **1** — Utiliza pocos de los conceptos aprendidos: le faltan dos o más criterios de la sección *Conocimientos* (por ejemplo, todo el programa está en `main`, o no usa structs ni funciones). | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Habilidades** — Código estructurado, legible y fácil de comprender, que soluciona el problema planteado manipulando correctamente los archivos. | **5** — El código soluciona cada uno de los requerimientos y/o salidas del problema planteado, es fácil de seguir y leer, hace uso de buenas prácticas de programación y maneja correctamente el archivo: cumple todos los criterios de la sección *Habilidades* de su enunciado (incluida la bitácora de pruebas en PDF) y sus resultados coinciden con todos los casos de prueba. | **4** — El código soluciona parcialmente los requerimientos y/o salidas del problema planteado, tiene poca estructura o no manipula de manera óptima los archivos: le fallan uno o dos criterios de la sección *Habilidades* (por ejemplo, acepta un identificador repetido, no muestra 2 decimales, una validación está incompleta o a la bitácora le falta un caso). | **3** — El código no soluciona la mayoría de los requerimientos y/o salidas del problema planteado, no es fácil de seguir o no manipula archivos: le fallan tres o más criterios de la sección *Habilidades*, el archivo queda dañado o pierde registros, lo guardado no se conserva al volver a abrir el programa, no compila, o **no entregó la bitácora de pruebas en PDF**. | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Actitudes / Valores** — Cumple con la estructura y características de la actividad, y la entrega a tiempo. | **2** — Entregado en tiempo y con buena participación en la elaboración del programa, cumpliendo con las características solicitadas: cumple todos los criterios de la sección *Actitudes / Valores* de su enunciado (los mismos dos archivos en los dos lugares de NEXUS antes de la fecha y hora límite, `.txt` y `.pdf` con el nombre solicitado, y programa elaborado por el propio alumno, que puede explicar su código). | **1** — Entregado fuera de tiempo y/o con participación regular en la elaboración del programa y/o sin cumplir alguna de las características solicitadas. | **0** — Entregado fuera de tiempo y/o con poca participación en la elaboración del programa y/o sin cumplir la mayoría de las características solicitadas (por ejemplo, no puede explicar su propio código). | **0** — No participó en la elaboración de las actividades. |

### Reglas generales

- **Tu programa debe ser de tu enunciado:** con tu contexto, tus structs, tus funciones y tu
  archivo. Un programa de otro contexto cuenta como no entregado.
- **Las capturas deben ser de tu programa.** El profesor corre tu código con los mismos datos de
  tu bitácora: una captura que tu programa no puede producir cuenta
  como evidencia que no elaboraste tú.
- **No hay entregas extemporáneas.** Lo que no esté en NEXUS a la fecha y hora límite no se recibe.
