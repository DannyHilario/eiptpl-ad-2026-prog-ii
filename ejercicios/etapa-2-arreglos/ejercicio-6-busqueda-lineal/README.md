# Ejercicio 6 — Búsqueda lineal en una función

*Etapa II — Arreglos · Temas: 2.6 (búsqueda lineal) + funciones (arreglo como parámetro) · Solución: `etapa-2-ejercicio-6.cpp` (se escribe en clase)*

## Historia de usuario

**Como** encargado de un inventario de 50 números de folio, **quiero** teclear un
folio y que el programa me diga en qué posición de la lista está, **para** no
tener que revisarla a mano uno por uno.

## Contexto

En [2.6 Búsqueda lineal](../../../contenido/etapa-2-arreglos/2.6-busqueda-lineal.md)
la búsqueda se hizo dentro de `main`, con una bandera y `break`. Aquí la misma
idea se mueve a **su propia función**, que recibe el arreglo como parámetro y
**regresa** el índice donde encontró el valor:

```cpp
int busquedaLineal(const int arreglo[], int tamanio, int clave);
```

- **`const int arreglo[]`**: la función recibe *dónde está* el arreglo original,
  no una copia. El `[]` va vacío porque el tamaño no viaja con el arreglo; por eso
  se pasa aparte en `tamanio`. El `const` es porque buscar solo **lee** el
  arreglo: si por error la función intenta cambiar un elemento, el programa no
  compila.
- **`return i`**: en cuanto encuentra el valor, la función termina en ese mismo
  instante y regresa el índice. No hace falta `break` ni bandera.
- **`return -1`**: va **después** del `for`. Solo se llega ahí si el ciclo revisó
  todo el arreglo sin encontrar nada, y `-1` no puede ser un índice real.

La función regresa el **índice** (empieza en 0); `main` es quien decide mostrarle
al usuario la **posición** (empieza en 1). Un dato curioso: esa posición es
también el número de comparaciones que hizo la búsqueda para encontrarlo.

## Datos

Usa exactamente este arreglo (así los casos de prueba de abajo funcionan igual
para todos). No se captura: se escribe en el código.

```cpp
int folios[TAMANIO] = {
    34, 71,  8, 56, 19, 92, 45, 27, 63, 11,
    80,  3, 58, 27, 94, 40, 16, 75, 52, 88,
     7, 69, 31, 27, 99, 14, 47, 85, 22, 60,
    38, 77,  5, 91, 50, 26, 66, 13, 82, 44,
    97, 29, 61, 18, 73, 36, 54, 10, 89, 65
};
```

## Criterios de aceptación

- [ ] El tamaño del arreglo (50) es una constante con nombre (`TAMANIO`) y el
      arreglo se declara con ella.
- [ ] La búsqueda está en una función con este prototipo exacto:
      `int busquedaLineal(const int arreglo[], int tamanio, int clave);`
- [ ] La función **no** usa `cin` ni `cout`: solo busca y regresa el índice, o
      `-1` si no lo encontró.
- [ ] La función deja de buscar en cuanto encuentra el valor (`return` dentro del
      `if`).
- [ ] `main` pide el folio a buscar, llama a la función y muestra la
      **posición** (índice + 1) o un mensaje de que no se encontró.
- [ ] Si el folio aparece más de una vez, se reporta la **primera** aparición.
- [ ] Compila sin warnings con `g++ -std=c++17 -Wall`.

## Ejemplo de ejecución

```
BUSQUEDA DE FOLIOS

Folio a buscar: 50
El folio 50 esta en la posicion 35
```

```
BUSQUEDA DE FOLIOS

Folio a buscar: 100
El folio 100 no esta en la lista
```

Los mensajes pueden variar; lo importante es que la posición sea la correcta.

## Casos de prueba

| # | Caso | Entrada | Salida esperada |
|---|---|---|---|
| 1 | Primer elemento | `34` | Posición 1 |
| 2 | Último elemento | `65` | Posición 50 |
| 3 | A la mitad | `50` | Posición 35 |
| 4 | Folio repetido | `27` (aparece 3 veces) | Posición 8 — la primera aparición, no la 14 ni la 24 |
| 5 | No está | `100` | Mensaje de que no se encontró |
| 6 | Negativo | `-8` | Mensaje de que no se encontró (no truena ni muestra "posición 0") |

**Pista para el caso 3:** si el caso 1 funciona pero el 3 dice "no se
encontró", revisa dónde quedó tu `return -1`. Si está en un `else` dentro del
`for`, la función se rinde en cuanto el **primer** elemento no coincide y nunca
llega a revisar el resto.

## Autocheck

**¿Por qué el `return -1` no puede ir en un `else` dentro del `for`?**
Porque un `return` termina la función completa. Con el `else`, la función
regresaría `-1` en la primera vuelta en que el elemento no coincide, sin revisar
los demás.

**¿Qué pasaría si el prototipo dijera `int arreglo[50]` en lugar de `int arreglo[]`?**
Nada: como parámetro, el compilador ignora ese número. La función solo recibe
dónde empieza el arreglo; el tamaño real lo conoce por `tamanio`.

**Si buscas un folio que no está, ¿cuántas comparaciones hace la función?**
50: tiene que revisar todo el arreglo para estar segura de que no está.

## Historial de cambios

| Fecha | Qué cambió | Por qué |
|---|---|---|
| 24 sep 2026 | Se creó esta ficha. La solución se escribe en clase. | Primer ejercicio que pasa un arreglo a una función y regresa un resultado, usando el mismo patrón que el ejemplo del manual en 2.6. |
