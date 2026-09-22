# Etapa II — Arreglos (ejercicios)

Cada ejercicio vive en su propia carpeta, con su ficha (`README.md`: historia de
usuario, criterios de aceptación y casos de prueba) y su solución (`.cpp`).

| # | Ejercicio | Temas | Estado de la solución |
|---|---|---|---|
| 1 | [Captura e impresión de un arreglo](ejercicio-1-captura-impresion/README.md) | 2.1–2.4 | Completa |
| 2 | [Recibo de pago con arreglos paralelos](ejercicio-2-recibo-arreglos-paralelos/README.md) | 2.1–2.3 | Pendiente: validar clave |
| 3 | [Sueldo semanal con ISR usando arreglos](ejercicio-3-isr-con-arreglos/README.md) | 2.2–2.3 + funciones | Completa |
| 4 | [Sueldo semanal con ISR usando una matriz](ejercicio-4-isr-con-matriz/README.md) | 2.2–2.3 (matrices) + funciones | Completa |

## Pendientes en las soluciones

- **Ejercicio 2:** no valida que la clave esté entre 1 y 3. Con una clave fuera
  de rango lee fuera de los límites del arreglo (comportamiento indefinido): con
  clave 4 el recibo imprime basura, por ejemplo `Precio unitario: $-3.38968e+240`.
  Falta el mismo `do...while` de validación que usa el ejercicio 1.
