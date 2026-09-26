# Evidencia 2.2 — Laboratorio de Programas (Arreglos)

De manera **individual**, resolverás **un programa** en C++ que guarda datos
en arreglos y los consulta después, retomando lo visto en la Etapa II:
matrices, vectores, recorrido con `for` (y `for` anidado), constantes para el
tamaño de los arreglos y validación de índices.

Todo el grupo resuelve **el mismo programa**, pero cada alumno lo hace sobre
un contexto distinto: el mismo que tuviste en el Programa 1 de la Evidencia 1,
que ahora evoluciona para **guardar** sus datos en lugar de olvidarlos.

## El programa, en resumen

Un sistema que registra varios datos de cada elemento (máquinas, salones,
empleados, etc.) y los consulta con un menú de 4 opciones:

```
1.- Registrar un elemento
2.- Reporte general
3.- Tabla de datos
4.- Salir
```

- Los datos que captura el usuario se guardan en una **matriz**: una fila por
  elemento y una columna por dato.
- El resultado de cada elemento (su promedio o su total, según tu contexto) se
  guarda en un **vector**, en la misma posición que su fila en la matriz.
- Un **contador** lleva cuántos elementos se han registrado y, al mismo
  tiempo, indica en qué fila va el siguiente.
- Solo se pueden **agregar** elementos, hasta llenar la matriz. No se
  eliminan ni se modifican.
- Todo el programa vive en `main`, sin funciones propias.

Los detalles (tamaños, rangos válidos, reglas de clasificación, criterios de
aceptación y casos de prueba) están en tu enunciado personalizado.

## Enunciados por alumno

| # | Alumno | Contexto | Enunciado |
|---|---|---|---|
| 01 | Cruz Martinez Cielo Michelle | Registro de puntualidad semanal | [ver](alumnos/01-cruz-martinez-cielo-michelle-etapa-2-arreglos.md) |
| 02 | Espinosa Saucedo Angel Xavier | Control de calidad por lotes | [ver](alumnos/02-espinosa-saucedo-angel-xavier-etapa-2-arreglos.md) |
| 03 | Flores Hidalgo Carolina | Filtro de temperatura en un evento | [ver](alumnos/03-flores-hidalgo-carolina-etapa-2-arreglos.md) |
| 04 | Hernández Hernández Luis Ernesto | Radares de velocidad en un tramo | [ver](alumnos/04-hernandez-hernandez-luis-ernesto-etapa-2-arreglos.md) |
| 05 | Hernandez Lopez Jose | Consumo eléctrico mensual por semanas | [ver](alumnos/05-hernandez-lopez-jose-etapa-2-arreglos.md) |
| 06 | Ibarra Banda Alejandro Israel | Existencias por sucursal | [ver](alumnos/06-ibarra-banda-alejandro-israel-etapa-2-arreglos.md) |
| 07 | Ibarra Martinez Victor Miguel | Monitoreo de ruido industrial | [ver](alumnos/07-ibarra-martinez-victor-miguel-etapa-2-arreglos.md) |
| 08 | Martinez Rincon Vika Ludivina | Encuesta de satisfacción por cliente | [ver](alumnos/08-martinez-rincon-vika-ludivina-etapa-2-arreglos.md) |
| 09 | Moreno Mercado Fernando | Batería de laptops durante el día | [ver](alumnos/09-moreno-mercado-fernando-etapa-2-arreglos.md) |
| 10 | Ordaz Segura Melissa Alejandra | Turbidez del agua por punto de muestreo | [ver](alumnos/10-ordaz-segura-melissa-alejandra-etapa-2-arreglos.md) |
| 11 | Palacios Moreno Jael Yasmani | Tiempos de atención de soporte técnico | [ver](alumnos/11-palacios-moreno-jael-yasmani-etapa-2-arreglos.md) |
| 12 | Ramirez Mejorado Jesus Guadalupe | Monitoreo de CO2 en salones | [ver](alumnos/12-ramirez-mejorado-jesus-guadalupe-etapa-2-arreglos.md) |
| 13 | Rangel Robles Donovan Antonio | Pruebas de tiempo de carga web | [ver](alumnos/13-rangel-robles-donovan-antonio-etapa-2-arreglos.md) |
| 14 | Rocha Ramirez Tomas De Jesus | Nivel de tanques de gas LP | [ver](alumnos/14-rocha-ramirez-tomas-de-jesus-etapa-2-arreglos.md) |
| 15 | Rodriguez Martinez Angel Ricardo | Tiempos de entrega por repartidor | [ver](alumnos/15-rodriguez-martinez-angel-ricardo-etapa-2-arreglos.md) |
| 16 | Roldan Reyes Alexis | Pruebas de resistencia por pieza | [ver](alumnos/16-roldan-reyes-alexis-etapa-2-arreglos.md) |
| 17 | Salinas Diaz Andrea Elizabeth | Ocupación del estacionamiento por piso | [ver](alumnos/17-salinas-diaz-andrea-elizabeth-etapa-2-arreglos.md) |
| 18 | Salinas Meza Cesar Eduardo | Consumo de datos móviles por semana | [ver](alumnos/18-salinas-meza-cesar-eduardo-etapa-2-arreglos.md) |
| 19 | Valles Arriaga Iker Karol | Tiempo de espera por caja | [ver](alumnos/19-valles-arriaga-iker-karol-etapa-2-arreglos.md) |
| 20 | Vazquez Palacios Angel Daniel | Vibración de maquinaria industrial | [ver](alumnos/20-vazquez-palacios-angel-daniel-etapa-2-arreglos.md) |

---

## Entregables

Un archivo de código fuente en C++ con la solución de tu enunciado
personalizado. Guárdalo como texto plano (`.txt`) — NEXUS no acepta cargar
archivos `.cpp`.

El programa debe compilar y ejecutarse sin errores en Dev-C++.

---

## Forma de Entrega

- **Modalidad:** Individual. Cada alumno entrega su propio archivo.
- **Plataforma:** NEXUS. Carga tu archivo en la evidencia
  *"2.2 - Evidencia de Aprendizaje 2: Laboratorio de Programas"*.
- Nombra tu archivo de la siguiente forma:

```
EV2.2_ApellidoNombre.txt
```

*Ejemplo: `EV2.2_CruzCielo.txt`*

- **Fecha de entrega:** Jueves 1 de octubre de 2026.
- **Hora límite:** 8:40 p.m.

---

## Rúbrica de Evaluación

Cada criterio de la rúbrica corresponde a una sección de los **criterios de
aceptación** de tu enunciado. Si cumples todos los criterios de una sección,
alcanzas el nivel **Evidencia completa** de ese criterio.

| CRITERIO / NIVEL DE DOMINIO | Evidencia completa | Evidencia suficiente | Evidencia débil | Sin evidencia |
|-----------------------------|--------------------|---------------------|-----------------|---------------|
| **Conocimientos** — Relaciona los contenidos de la etapa con las actividades solicitadas. | **3** — Identifica todos los conceptos aprendidos en los temas de arreglos: cumple todos los criterios de la sección *Conocimientos* de su enunciado (matriz para los datos capturados, vector con el resultado de cada elemento en la misma posición que su fila, contador como índice de la siguiente fila, tamaños y límites como constantes, y reportes que leen el resultado del vector). | **2** — Identifica la mayoría de los conceptos aprendidos en los temas de arreglos: le falta un criterio de la sección *Conocimientos* (por ejemplo, declara un tamaño con un número escrito directamente en lugar de una constante, o vuelve a calcular el resultado en lugar de leerlo del vector). | **1** — Identifica pocos de los conceptos aprendidos en los temas de arreglos: le faltan dos o más criterios de la sección *Conocimientos* (por ejemplo, usa variables sueltas en lugar de la matriz o del vector, o confunde filas con columnas). | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Habilidades** — Soluciona todas las actividades planteadas utilizando de manera correcta los arreglos. | **5** — El código es fácil de seguir y leer, agrega comentarios de forma adecuada, almacena y lee de manera correcta los elementos de un arreglo y hace uso de buenas prácticas de programación: cumple todos los criterios de la sección *Habilidades* de su enunciado y sus resultados coinciden con todos los casos de prueba. | **4** — El código funciona, pero es poco claro, con pocos comentarios, o no almacena o lee de manera correcta los elementos del arreglo en algún caso: le fallan uno o dos criterios de la sección *Habilidades* (por ejemplo, recorre las filas vacías de la matriz, no avisa cuando no hay registros, o una validación está incompleta). | **3** — El código funciona solo en parte, sin estructura, no es claro, es difícil de comprender y no almacena ni lee de manera correcta los elementos de un arreglo: le fallan tres o más criterios de la sección *Habilidades*, guarda datos en la fila o columna equivocada, escribe fuera de la matriz al pasar el máximo, sus resultados no coinciden con los casos de prueba, o no compila. | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Actitudes / Valores** — Cumple con la estructura y características de la actividad. | **2** — Entregado en tiempo y con buena participación en la elaboración de la actividad, cumpliendo con las características solicitadas: cumple todos los criterios de la sección *Actitudes / Valores* de su enunciado (entrega en NEXUS antes de la fecha y hora límite, archivo `.txt` con el nombre solicitado, y programa elaborado por el propio alumno, que puede explicar su código). | **1** — Entregado fuera de tiempo y/o con participación regular en la elaboración y/o sin cumplir alguna de las características solicitadas (por ejemplo, archivo mal nombrado o en otro formato). | **0** — Entregado fuera de tiempo y/o con poca participación en la elaboración y/o sin cumplir la mayoría de las características solicitadas (por ejemplo, no puede explicar su propio código). | **0** — No participó en la elaboración de la actividad. |
