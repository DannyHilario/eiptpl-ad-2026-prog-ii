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
