# Etapa I — Funciones (ejercicios)

Cada ejercicio vive en su propia carpeta, con su ficha (`README.md`: historia de
usuario, criterios de aceptación, casos de prueba e historial de cambios) y su
solución (`.cpp`).

**Regla de diseño que siguen (o deben seguir) todos los ejercicios de esta etapa:**
las funciones que hacen el cálculo son "puras" — reciben datos, regresan un
resultado, y **no leen con `cin` ni escriben con `cout`**. Toda la interacción con
el usuario (captura, validación, impresión del resultado) vive en `main()`. Esto
es a propósito: separa "qué calcula el programa" de "cómo se comunica con el
usuario", que es la idea central de dividir en funciones.

**Segunda regla de diseño:** si un dato se puede **derivar** de otro que ya se
capturó, no se vuelve a pedir por separado — se calcula dentro de una función
a partir del dato original. Pedir ambos como capturas independientes abre la
puerta a que el usuario introduzca valores que no cuadran entre sí (por
ejemplo, "días de retraso" como dato suelto, sin relación con los "días
totales de uso" ya capturados). Esto aplica tanto a los ejercicios de esta
carpeta como a los enunciados personalizados de la
[Evidencia 1.1](../../evidencias/etapa-1/02-funciones/descripcion.md).

| # | Ejercicio | Temas | Estado de la solución |
|---|---|---|---|
| 1 | [Sueldo por hora con impuesto](ejercicio-1-sueldo-por-hora/README.md) | 1.1–1.3 | Completa |
| 2 | [Sueldo semanal con ISR por rangos](ejercicio-2-isr-por-rangos/README.md) | 1.1–1.3 | Completa |
| 3 | Facturación con descuento por volumen e IVA | 1.1–1.3 | Enunciado en la [Evidencia 1.1](../../evidencias/etapa-1/02-funciones/descripcion.md) (Programa 1) — no está aquí para no tener dos fuentes de verdad |
