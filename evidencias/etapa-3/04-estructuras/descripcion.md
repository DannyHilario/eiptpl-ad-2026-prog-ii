# Evidencia 3.2 — Programa (Estructuras)

De manera **individual**, resolverás **un programa** en C++ que guarda registros en un
**arreglo de estructuras** y los consulta después, retomando lo visto en la Etapa III:
definición de structs, structs anidados, un arreglo como campo de un struct, arreglos de
registros, el contador de registros y funciones puras.

Todo el grupo resuelve **el mismo programa**, pero cada alumno lo hace sobre su propio
contexto: el mismo que tuviste en la Evidencia 2.2, que ahora evoluciona para guardar cada
elemento como un **registro** completo en lugar de repartirlo entre una matriz y un vector.

## El programa, en resumen

Un sistema que guarda hasta **5 registros** (empleados, lotes, laptops, etc.) y los
consulta con un menú de 5 opciones:

```
1.- Registrar un elemento
2.- Tabla de elementos
3.- Elementos por mes
4.- Buscar un elemento
5.- Salir
```

- Cada elemento es un `struct` con un **identificador** (`string`), una **fecha** (un
  `struct Fecha` anidado), sus **datos** (un arreglo dentro del struct) y su **resultado**
  (su promedio o su total, según tu contexto).
- Los elementos se guardan en un **arreglo de structs** de 5 posiciones, y un
  **contador** lleva cuántos hay e indica en qué posición va el siguiente.
- La opción 3 muestra los registros cuya fecha cae en un mes dado, y la opción 4 busca un
  registro por su identificador y muestra todos sus datos.
- La clasificación de cada elemento la decide una **función pura** que recibe el
  resultado, no el struct.
- Solo se pueden **agregar** registros, hasta llenar el arreglo. No se eliminan ni se
  modifican.

Los nombres exactos de los structs, sus campos y la función, además de los rangos válidos,
la regla de clasificación, los criterios de aceptación y los casos de prueba, están en tu
enunciado personalizado. Antes de empezar repasa
[3.4 Arreglos de registros](../../../contenido/etapa-3-estructuras/3.4-arreglos-de-registros.md)
(incluida la sección *Un arreglo dentro de un struct*) y
[3.5 Estructuras anidadas](../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md).

## Enunciados por alumno

| # | Alumno | Contexto | Enunciado |
|---|---|---|---|
| 01 | Cruz Martinez Cielo Michelle | Registro de puntualidad semanal | [ver](alumnos/01-cruz-martinez-cielo-michelle-etapa-3-estructuras.md) |
| 02 | Espinosa Saucedo Angel Xavier | Control de calidad por lotes | [ver](alumnos/02-espinosa-saucedo-angel-xavier-etapa-3-estructuras.md) |
| 03 | Flores Hidalgo Carolina | Filtro de temperatura en un evento | [ver](alumnos/03-flores-hidalgo-carolina-etapa-3-estructuras.md) |
| 04 | Hernández Hernández Luis Ernesto | Radares de velocidad en un tramo | [ver](alumnos/04-hernandez-hernandez-luis-ernesto-etapa-3-estructuras.md) |
| 05 | Hernandez Lopez Jose | Consumo eléctrico mensual por semanas | [ver](alumnos/05-hernandez-lopez-jose-etapa-3-estructuras.md) |
| 06 | Ibarra Banda Alejandro Israel | Existencias por sucursal | [ver](alumnos/06-ibarra-banda-alejandro-israel-etapa-3-estructuras.md) |
| 07 | Ibarra Martinez Victor Miguel | Monitoreo de ruido industrial | [ver](alumnos/07-ibarra-martinez-victor-miguel-etapa-3-estructuras.md) |
| 08 | Martinez Rincon Vika Ludivina | Encuesta de satisfacción por cliente | [ver](alumnos/08-martinez-rincon-vika-ludivina-etapa-3-estructuras.md) |
| 09 | Moreno Mercado Fernando | Batería de laptops durante el día | [ver](alumnos/09-moreno-mercado-fernando-etapa-3-estructuras.md) |
| 10 | Ordaz Segura Melissa Alejandra | Turbidez del agua por punto de muestreo | [ver](alumnos/10-ordaz-segura-melissa-alejandra-etapa-3-estructuras.md) |
| 11 | Palacios Moreno Jael Yasmani | Tiempos de atención de soporte técnico | [ver](alumnos/11-palacios-moreno-jael-yasmani-etapa-3-estructuras.md) |
| 12 | Ramirez Mejorado Jesus Guadalupe | Monitoreo de CO2 en salones | [ver](alumnos/12-ramirez-mejorado-jesus-guadalupe-etapa-3-estructuras.md) |
| 13 | Rangel Robles Donovan Antonio | Pruebas de tiempo de carga web | [ver](alumnos/13-rangel-robles-donovan-antonio-etapa-3-estructuras.md) |
| 14 | Rocha Ramirez Tomas De Jesus | Nivel de tanques de gas LP | [ver](alumnos/14-rocha-ramirez-tomas-de-jesus-etapa-3-estructuras.md) |
| 15 | Rodriguez Martinez Angel Ricardo | Tiempos de entrega por repartidor | [ver](alumnos/15-rodriguez-martinez-angel-ricardo-etapa-3-estructuras.md) |
| 16 | Roldan Reyes Alexis | Pruebas de resistencia por pieza | [ver](alumnos/16-roldan-reyes-alexis-etapa-3-estructuras.md) |
| 17 | Salinas Diaz Andrea Elizabeth | Ocupación del estacionamiento por piso | [ver](alumnos/17-salinas-diaz-andrea-elizabeth-etapa-3-estructuras.md) |
| 18 | Salinas Meza Cesar Eduardo | Consumo de datos móviles por semana | [ver](alumnos/18-salinas-meza-cesar-eduardo-etapa-3-estructuras.md) |
| 19 | Valles Arriaga Iker Karol | Tiempo de espera por caja | [ver](alumnos/19-valles-arriaga-iker-karol-etapa-3-estructuras.md) |
| 20 | Vazquez Palacios Angel Daniel | Vibración de maquinaria industrial | [ver](alumnos/20-vazquez-palacios-angel-daniel-etapa-3-estructuras.md) |

---

## Entregables

Un archivo de código fuente en C++ con la solución de tu enunciado personalizado.
Guárdalo como texto plano (`.txt`) — NEXUS no acepta cargar archivos `.cpp`.

El programa debe compilar y ejecutarse sin errores en Dev-C++.

---

## Forma de Entrega

- **Modalidad:** Individual. Cada alumno entrega su propio archivo.
- **Plataforma:** NEXUS. Carga tu archivo en la evidencia
  *"3.2 - Evidencia de Aprendizaje 3: Programa"*.
- Nombra tu archivo de la siguiente forma:

```
EV3.2_ApellidoNombre.txt
```

*Ejemplo: `EV3.2_CruzCielo.txt`*

- **Fecha de entrega:** Jueves 22 de octubre de 2026.
- **Hora límite:** 7:40 p.m.

---

## Rúbrica de Evaluación

Cada criterio de la rúbrica corresponde a una sección de los **criterios de aceptación**
de tu enunciado. Si cumples todos los criterios de una sección, alcanzas el nivel
**Evidencia completa** de ese criterio.

| CRITERIO / NIVEL DE DOMINIO | Evidencia completa | Evidencia suficiente | Evidencia débil | Sin evidencia |
|-----------------------------|--------------------|---------------------|-----------------|---------------|
| **Conocimientos** — Relaciona los contenidos de la etapa con las actividades solicitadas. | **3** — Identifica todos los conceptos aprendidos en los temas de estructuras: cumple todos los criterios de la sección *Conocimientos* de su enunciado (`struct Fecha` anidado en el struct del elemento, arreglo como campo del struct, arreglo de structs, contador como índice del siguiente registro, resultado guardado en su campo y leído de ahí, constantes con nombre y función pura de clasificación). | **2** — Identifica la mayoría de los conceptos aprendidos en los temas de estructuras: le falta un criterio de la sección *Conocimientos* (por ejemplo, guarda la fecha en tres campos sueltos en lugar de un `struct Fecha`, vuelve a calcular el resultado en lugar de leerlo de su campo, o la función de clasificación recibe el struct completo o usa `cout`). | **1** — Identifica pocos de los conceptos aprendidos en los temas de estructuras: le faltan dos o más criterios de la sección *Conocimientos* (por ejemplo, usa arreglos paralelos o una matriz en lugar del arreglo de structs, o no usa structs). | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Habilidades** — Soluciona todas las actividades planteadas utilizando de manera correcta las estructuras. | **5** — El código soluciona adecuadamente cada uno de los requerimientos y salidas del problema planteado, es fácil de seguir y leer, los nombres de las estructuras y sus campos son descriptivos y hace uso de buenas prácticas de programación: cumple todos los criterios de la sección *Habilidades* de su enunciado y sus resultados coinciden con todos los casos de prueba. | **4** — El código soluciona parcialmente los requerimientos o salidas del problema planteado, es poco claro o con pocos comentarios: le fallan uno o dos criterios de la sección *Habilidades* (por ejemplo, recorre las posiciones libres del arreglo, no avisa cuando no hay registros, el filtro por mes también compara el año, o una validación está incompleta). | **3** — El código no soluciona la mayoría de los requerimientos o salidas solicitadas: le fallan tres o más criterios de la sección *Habilidades*, guarda un dato en el registro o el campo equivocado, escribe fuera del arreglo al pasar el máximo, sus resultados no coinciden con los casos de prueba, o no compila. | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Actitudes / Valores** — Cumple con la estructura y características de la actividad. | **2** — Entregado en tiempo y con buena participación en la elaboración de la actividad, cumpliendo con las características solicitadas: cumple todos los criterios de la sección *Actitudes / Valores* de su enunciado (entrega en NEXUS antes de la fecha y hora límite, archivo `.txt` con el nombre solicitado, y programa elaborado por el propio alumno, que puede explicar su código). | **1** — Entregado fuera de tiempo y/o con participación regular en la elaboración y/o sin cumplir alguna de las características solicitadas (por ejemplo, archivo en otro formato). | **0** — Entregado fuera de tiempo y/o con poca participación en la elaboración y/o sin cumplir la mayoría de las características solicitadas (por ejemplo, no puede explicar su propio código). | **0** — No participó en la elaboración de la actividad. |
