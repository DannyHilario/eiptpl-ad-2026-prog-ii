# Laboratorio de repaso — Programación I

*Anterior: [Repaso: estructuras de control y ciclos](01-estructuras-de-control.md) — Siguiente: [1.1 Funciones](../etapa-1-funciones/1.1-funciones.md)*

3 ejercicios para repasar antes de empezar Funciones. Ninguno es puramente
secuencial — combinan `if`/`switch` con al menos un ciclo. No hay solución aquí a
propósito — escríbelos y compílalos tú mismo. Ninguno requiere arreglos (todavía no
los hemos visto); resuélvelos acumulando en variables sencillas mientras avanza el
ciclo.

## 1. Reporte de grupo

Pide cuántos alumnos tiene el grupo (`N`). Para cada uno, lee su calificación final
y decide con un `if` si aprobó (≥ 70) o reprobó. Al terminar de leer los `N`
alumnos, muestra el total de aprobados, el total de reprobados, y el porcentaje de
aprobación del grupo completo.

**Ejemplo de ejecución:**
```
Cuantos alumnos tiene el grupo: 3
Calificacion del alumno 1: 85
Calificacion del alumno 2: 60
Calificacion del alumno 3: 95

Total aprobados: 2
Total reprobados: 1
Porcentaje de aprobacion: 66.67%
```

## 2. Cajero con tres cajas

Menú con 4 opciones: Caja 1, Caja 2, Caja 3, y Finalizar turno. Cada vez que el
usuario elige una caja, pide el monto cobrado y lo acumula en el total de esa caja
(necesitas una variable de total y una de contador de clientes por cada caja — 6
variables en total). Al elegir "Finalizar turno", muestra el efectivo y la cantidad
de clientes de cada caja, y los totales generales (suma de las tres).

**Ejemplo de ejecución:**
```
1. Caja 1
2. Caja 2
3. Caja 3
4. Finalizar turno
Opcion: 1
Monto cobrado: 50

1. Caja 1
2. Caja 2
3. Caja 3
4. Finalizar turno
Opcion: 2
Monto cobrado: 30

1. Caja 1
2. Caja 2
3. Caja 3
4. Finalizar turno
Opcion: 1
Monto cobrado: 20

1. Caja 1
2. Caja 2
3. Caja 3
4. Finalizar turno
Opcion: 4

Caja 1: $70.00, 2 clientes
Caja 2: $30.00, 1 cliente
Caja 3: $0.00, 0 clientes
TOTAL: $100.00, 3 clientes
```

## 3. Clasificador de temperaturas de la semana

Pide cuántos días se van a registrar (`N`), validando que sea positivo (si el
usuario da un valor ≤ 0, debe pedirlo de nuevo hasta que lo capture correcto). Para
cada uno de los `N` días, lee la temperatura y valida que no esté por debajo del
cero absoluto (-273.15 °C) — cualquier temperatura menor a ese límite físico es
imposible y se debe rechazar y volver a pedir. Ya con una temperatura válida,
clasifícala con `if`/`else if` en Frío (< 15 °C), Templado (15-25 °C) o Caluroso
(> 25 °C), acumulando un contador por categoría. Al terminar de leer los `N` días,
muestra el conteo de cada categoría y el promedio de temperatura de la semana.

Dos validaciones numéricas obligatorias en este ejercicio:

- **`N` positivo:** un número de días negativo o cero no tiene sentido para el
  ciclo que va a leer temperaturas — hay que atraparlo *antes* de entrar al ciclo
  principal, con su propio ciclo de validación que repita la pregunta hasta que el
  valor sea mayor a 0.
- **Cero absoluto (-273.15 °C):** es el límite físico real por debajo del cual no
  puede existir ninguna temperatura en la escala Celsius (equivale a 0 Kelvin).
  Cualquier lectura menor es un dato inválido, no solo un valor "poco común" — a
  diferencia de Frío/Templado/Caluroso (que son categorías dentro de un rango
  normal), esta validación descarta un valor físicamente imposible antes de
  siquiera clasificarlo. Va dentro del ciclo de los `N` días, con su propio ciclo
  de validación por cada temperatura leída.

**Ejemplo de ejecución:**
```
Cuantos dias se van a registrar: -2
ERROR. La cantidad de dias debe ser positiva
Cuantos dias se van a registrar: 3

Temperatura del dia 1: -300
ERROR. Esa temperatura esta por debajo del cero absoluto (-273.15 C)
Temperatura del dia 1: 12
Temperatura del dia 2: 28
Temperatura del dia 3: 9

********* REPORTE DE LA SEMANA *********

Dias frios: 2
Dias templados: 0
Dias calurosos: 1

Temperatura promedio: 16.33
```
