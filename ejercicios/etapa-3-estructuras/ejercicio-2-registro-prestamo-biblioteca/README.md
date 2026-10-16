# Ejercicio 2 — Registro de préstamos de una biblioteca

*Etapa III — Estructuras · Temas: 3.3–3.5 · Solución: [`etapa-3-ejercicio-2.cpp`](etapa-3-ejercicio-2.cpp)*

## Historia de usuario

**Como** encargado de la biblioteca, **quiero** registrar cada préstamo con el
nombre del socio, el libro y las fechas de préstamo y devolución, **para** saber
quién tiene cada libro y cuándo lo tiene que regresar.

## Contexto

Una fecha son tres datos (día, mes y año), y cada préstamo lleva **dos** fechas.
En lugar de seis campos sueltos (`FechaPrestamo_Dia`, `FechaPrestamo_Mes`, …), se
define un `struct Fecha` y se usa dos veces dentro de `struct Prestamo`: es una
**estructura anidada** (tema 3.5).

El programa tiene un menú con dos opciones que llenan dos arreglos distintos,
para comparar las dos formas de darle valores a un arreglo de structs:

| | Opción 1: inicializar | Opción 2: capturar |
|---|---|---|
| ¿Quién escribe los datos? | El programador, en el código | El usuario, al correr el programa |
| ¿Cuándo se conocen? | Antes de compilar | Hasta que el programa corre |
| ¿Cómo se escriben? | Con llaves: `{1, "Juan", "Matematicas", {12, 10, 2026}, {16, 10, 2026}}` | Con `cin >>`, campo por campo |
| ¿Se validan? | No hace falta: el programador ya los revisó | Sí: el usuario puede escribir una fecha imposible |
| ¿Cambian entre una ejecución y otra? | No | Sí |

| Tema | Dónde se usa |
|---|---|
| 3.2 Definición | `Fecha` y `Prestamo` se definen antes de `main`, `Fecha` primero |
| 3.3 Inicialización | El arreglo `inicializados` se llena con llaves dentro de llaves |
| 3.4 Arreglos de registros | `inicializados[i]` y `capturados[i]`, recorridos con `for` |
| 3.5 Estructuras anidadas | `capturados[i].FechaPrestamo.Dia`: índice, préstamo, fecha y campo |

`fechaComoNumero` convierte una fecha a un número `aaaammdd` (12/10/2026 →
`20261012`) para poder comparar dos fechas con `<`, como en
[3.5](../../../contenido/etapa-3-estructuras/3.5-estructuras-anidadas.md). Es una
función pura y recibe campos sueltos (`int`), no el struct.

## Criterios de aceptación

- [ ] Define `struct Fecha` (día, mes y año) y `struct Prestamo` (número, socio,
      libro, fecha de préstamo y fecha de devolución) antes de `main`.
- [ ] Muestra un menú: 1 mostrar préstamos inicializados, 2 capturar préstamos,
      3 salir. Una opción distinta muestra un error. El menú se repite hasta
      elegir 3.
- [ ] La opción 1 muestra una tabla con los 4 préstamos inicializados con llaves.
- [ ] La opción 2 captura 3 préstamos en **otro** arreglo y después los muestra en
      su propia tabla. El número de préstamo se asigna solo (1, 2, 3).
- [ ] El día debe estar entre 1 y 31, el mes entre 1 y 12 y el año debe tener 4
      dígitos; si no, muestra un error y lo vuelve a pedir.
- [ ] Si la fecha de devolución queda antes de la de préstamo, muestra un error y
      vuelve a pedir la fecha de devolución completa. Devolver el mismo día sí
      se permite.
- [ ] Después de cada opción espera Enter antes de volver al menú.

## Ejemplo de ejecución

```
PRESTAMOS DE LA BIBLIOTECA

1. Mostrar prestamos inicializados
2. Capturar prestamos
3. Salir

Opcion: 1
```

```
Prestamos inicializados en el programa

NumeroPrestamo	Nombre	Libro		FechaPrestamo		FechaDevolucion

1		Juan	Matematicas	12/10/2026		16/10/2026
2		Pedro	Espanol III	13/10/2026		16/10/2026
3		Luis	Geometria	14/10/2026		16/10/2026
4		Carlos	Ingles II	13/10/2026		19/10/2026

Presiona Enter para volver al menu...
```

Captura de una devolución anterior al préstamo:

```
Fecha de prestamo
  Dia (1 a 31): 10
  Mes (1 a 12): 10
  Anio (4 digitos): 2026

Fecha de devolucion
  Dia (1 a 31): 9
  Mes (1 a 12): 10
  Anio (4 digitos): 2026
  ERROR! La devolucion no puede ser antes del prestamo

Fecha de devolucion
  Dia (1 a 31):
```

## Casos de prueba

Probados el 15 oct 2026 en macOS, compilando con `g++ -std=c++98 -Wall -Wextra`
y con `-std=c++17` (sin advertencias, mismos resultados en ambos). Se supone que
en los campos numéricos el usuario escribe números enteros.

| # | Caso | Entrada | Salida esperada | Resultado |
|---|---|---|---|---|
| 1 | Datos inicializados | Opción 1 | Tabla con Juan, Pedro, Luis y Carlos, fechas con año de 4 dígitos | ✅ |
| 2 | Captura normal | Opción 2: Ana Fisica 1/10/2026 → 5/10/2026; Beto Quimica 20/10/2026 → 27/10/2026; Caro Historia 28/10/2026 → 4/11/2026 | Tabla con los 3 préstamos, numerados 1, 2 y 3 | ✅ |
| 3 | Día fuera de rango | Día 0, luego 32, luego 1 | Error dos veces; acepta 1 | ✅ |
| 4 | Mes fuera de rango | Mes 13, luego 0, luego 10 | Error dos veces; acepta 10 | ✅ |
| 5 | Año sin 4 dígitos | Año 26, luego 2026 | Error; acepta 2026 | ✅ |
| 6 | Devolución antes del préstamo | Préstamo 10/10/2026, devolución 9/10/2026 | Error y vuelve a pedir la fecha de devolución completa | ✅ |
| 7 | Devolución el mismo día | Préstamo 10/10/2026, devolución 10/10/2026 | Se acepta | ✅ |
| 8 | Devolución en otro año | Préstamo 31/12/2026, devolución 1/1/2026 (error) y luego 2/1/2027 | Error con 1/1/2026; acepta 2/1/2027 | ✅ |
| 9 | Opción no válida | Opción 7, luego 0 | Error dos veces y vuelve al menú | ✅ |
| 10 | Salir | Opción 3 | Termina sin pedir Enter | ✅ |

### Limitaciones conocidas

1. **La validación del día es sencilla:** acepta del 1 al 31 en cualquier mes, así
   que no detecta un 31 de abril ni un 30 de febrero.
2. **Socio y libro son una sola palabra** al capturar, porque `cin >>` corta en el
   espacio. Al inicializar sí se pueden escribir con espacios (`"Espanol III"`).
3. **La tabla se desalinea con libros cortos.** El encabezado deja dos tabuladores
   para la columna del libro, pensados para nombres de 8 letras o más; con
   `Fisica` o `Quimica` las fechas se recorren a la izquierda.
4. **Los capturados se pierden** al volver a elegir la opción 2 (se capturan otra
   vez desde el préstamo 1) y al salir del programa. Guardarlos es tema de la
   Etapa IV.

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 15 oct 2026 | Primera versión: un préstamo (`Prestamo1`) llenado campo por campo y después un arreglo de 4 préstamos inicializado con llaves, con `struct Fecha` anidada. | Temas 3.3 a 3.5: inicializar un arreglo de structs con structs anidados. |
| 15 oct 2026 | Los structs se movieron antes de `main`. Se agregó el menú con dos tablas: préstamos inicializados y préstamos capturados con validación de día, mes, año y orden de las fechas. El año pasó a 4 dígitos. Se quitaron los acentos de los textos y los bloques comentados de la versión anterior. | La definición del struct va antes de `main` (tema 3.2); comparar inicializar contra capturar; con año de 4 dígitos las fechas se comparan bien al cambiar de siglo; los acentos se ven mal en la consola de Dev-C++. |
