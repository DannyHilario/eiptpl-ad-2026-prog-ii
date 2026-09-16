# Etapa II — Arreglos (ejercicios)

Resumen a alto nivel de cada ejercicio: qué resuelve y qué muestra de arreglos,
sin repetir el código completo (eso ya vive en el `.cpp` correspondiente).

---

## Ejercicio 1 — Captura e impresión de un arreglo

`etapa-2-ejercicio-1.cpp` — **completo**.

Captura hasta 10 enteros en un arreglo y los vuelve a imprimir, usando dos
ciclos `for` separados (uno para capturar, otro para imprimir) en vez de hacer
ambas cosas en el mismo ciclo — para dejar claro que son dos pasos
independientes sobre el mismo arreglo.

- Valida que la cantidad a capturar esté entre 0 y 10 (tamaño del arreglo)
  antes de entrar al ciclo de captura.
- El comentario "FORMA MANUAL" al inicio muestra cómo se vería capturar/imprimir
  un solo elemento accediendo directo al índice (`numeros[0]`), como contraste
  con el ciclo que recorre todo el arreglo.

---

## Ejercicio 2 — Recibo de pago con arreglos paralelos

`etapa-2-ejercicio-2.cpp` — **completo, pendiente un ajuste**.

Calcula el total a pagar de un artículo a partir de su clave, usando dos
arreglos paralelos indexados por `clave_articulo - 1`: uno de precios
(`precio_unitario`) y uno de descripciones (`descripcion_articulo`). El
comentario muestra la alternativa con `switch` que este enfoque reemplaza —
un arreglo evita repetir el mismo `case` tres veces para precio y descripción.

**Pendiente:** no valida que `clave_articulo` esté en el rango 1–3. Una clave
fuera de rango (0, negativa o mayor a 3) accede al arreglo fuera de sus
límites, lo cual es comportamiento indefinido en C++ (no un error controlado).
Falta el mismo tipo de `do...while` de validación que ya usa el ejercicio 1.
