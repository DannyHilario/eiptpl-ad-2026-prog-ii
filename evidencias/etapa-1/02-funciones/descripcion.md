# Evidencia 1.1 — Laboratorio de Programas (Funciones)

De manera **individual**, resolverás dos programas en C++ que retoman lo visto
en funciones (prototipo, definición, llamada), paso de parámetros, funciones
"puras" (sin `cin`/`cout`) y uso de constantes con nombre en vez de valores
hardcode.

## Programa 1 — Facturación con descuento por volumen e IVA (común)

Este programa es el mismo para todo el grupo.

Escribe un programa que calcule el total a pagar de una compra, considerando
descuento por volumen (a mayor cantidad comprada, mayor porcentaje de descuento)
e IVA.

El programa debe leer, para una compra:

- Cantidad de piezas compradas.
- Precio unitario.

### Reglas de negocio

| Piezas compradas | Descuento sobre el subtotal |
|---|---|
| 1 – 9 | 0% |
| 10 – 49 | 5% |
| 50 en adelante | 12% |

- Tasa de IVA: 16%

### Cálculo

1. **Subtotal** = cantidad × precio unitario.
2. **Descuento** = subtotal × el porcentaje que corresponda según la tabla
   de rangos por cantidad de piezas.
3. **Base gravable** = subtotal − descuento.
4. **IVA** = base gravable × tasa de IVA.
5. **Total a pagar** = base gravable + IVA.

### Prototipos sugeridos

```cpp
double calcularSubtotal(int cantidad, double precio_unitario);
double calcularDescuento(int cantidad, double subtotal);
double calcularIVA(double base_gravable);
double calcularTotal(double base_gravable, double iva);
```

Nota que `calcularDescuento` necesita **tanto** la cantidad (para saber en qué
rango cae) **como** el subtotal (para saber sobre qué monto aplicar el
porcentaje) — son dos parámetros, no uno.

### Requisitos técnicos

- Constantes con nombre para los límites de rango, los porcentajes de descuento
  y la tasa de IVA — nada de valores hardcode dentro de las funciones.
- Validar que cantidad > 0 y precio unitario > 0 (repetir captura si no cumple).
- Ninguna función de cálculo debe usar `cin` ni `cout` — solo `main()` interactúa
  con el usuario.
- Mostrar al final: subtotal, descuento aplicado, IVA y total a pagar.

### Casos de prueba

Usa estos valores para verificar tu programa (no muestran cómo resolverlo,
solo el resultado esperado):

**Caso 1 — sin descuento (rango 1)**
- Entrada: cantidad = 5, precio unitario = 100.00
- Salida esperada: subtotal = 500.00, descuento = 0.00, IVA = 80.00, total a
  pagar = 580.00

**Caso 2 — con descuento (rango 3)**
- Entrada: cantidad = 60, precio unitario = 50.00
- Salida esperada: subtotal = 3000.00, descuento = 360.00, IVA = 422.40,
  total a pagar = 3062.40

## Programa 2 — personalizado por alumno

Cada alumno tiene un enunciado distinto (mismo nivel de dificultad y mismos
requisitos técnicos, mecánica de cálculo y contexto distintos), con su propio
periodo de tiempo (semanal, quincenal o mensual, según el caso). Busca tu
archivo en la tabla de abajo:

| Matrícula | Nombre del alumno | Enunciado | Estado |
|---|---|---|---|
| 2307014 | Cruz Martinez Cielo Michelle | [ver](alumnos/2307014-cruz-martinez-cielo-michelle-etapa-1-funciones.md) | ✅ listo |
| 2306378 | Espinosa Saucedo Angel Xavier | [ver](alumnos/2306378-espinosa-saucedo-angel-xavier-etapa-1-funciones.md) | ✅ listo |
| 2254340 | Flores Hidalgo Carolina | [ver](alumnos/2254340-flores-hidalgo-carolina-etapa-1-funciones.md) | ✅ listo |
| 2306996 | Hernández Hernández Luis Ernesto | [ver](alumnos/2306996-hernandez-hernandez-luis-ernesto-etapa-1-funciones.md) | ✅ listo |
| 2306741 | Hernandez Lopez Jose | [ver](alumnos/2306741-hernandez-lopez-jose-etapa-1-funciones.md) | ✅ listo |
| 2306732 | Ibarra Banda Alejandro Israel | [ver](alumnos/2306732-ibarra-banda-alejandro-israel-etapa-1-funciones.md) | ✅ listo |
| 2306447 | Ibarra Martinez Victor Miguel | [ver](alumnos/2306447-ibarra-martinez-victor-miguel-etapa-1-funciones.md) | ✅ listo |
| 2306862 | Martinez Rincon Vika Ludivina | [ver](alumnos/2306862-martinez-rincon-vika-ludivina-etapa-1-funciones.md) | ✅ listo |
| 2253747 | Moreno Mercado Fernando | [ver](alumnos/2253747-moreno-mercado-fernando-etapa-1-funciones.md) | ✅ listo |
| 2306833 | Ordaz Segura Melissa Alejandra | [ver](alumnos/2306833-ordaz-segura-melissa-alejandra-etapa-1-funciones.md) | ✅ listo |
| 2254253 | Palacios Moreno Jael Yasmani | [ver](alumnos/2254253-palacios-moreno-jael-yasmani-etapa-1-funciones.md) | ✅ listo |
| 2306775 | Ramirez Mejorado Jesus Guadalupe | [ver](alumnos/2306775-ramirez-mejorado-jesus-guadalupe-etapa-1-funciones.md) | ✅ listo |
| 2306333 | Rangel Robles Donovan Antonio | [ver](alumnos/2306333-rangel-robles-donovan-antonio-etapa-1-funciones.md) | ✅ listo |
| 2306976 | Rocha Ramirez Tomas De Jesus | [ver](alumnos/2306976-rocha-ramirez-tomas-de-jesus-etapa-1-funciones.md) | ✅ listo |
| 2253859 | Rodriguez Martinez Angel Ricardo | [ver](alumnos/2253859-rodriguez-martinez-angel-ricardo-etapa-1-funciones.md) | ✅ listo |
| 2253898 | Roldan Reyes Alexis | [ver](alumnos/2253898-roldan-reyes-alexis-etapa-1-funciones.md) | ✅ listo |
| 2306466 | Salinas Diaz Andrea Elizabeth | [ver](alumnos/2306466-salinas-diaz-andrea-elizabeth-etapa-1-funciones.md) | ✅ listo |
| 2306493 | Salinas Meza Cesar Eduardo | [ver](alumnos/2306493-salinas-meza-cesar-eduardo-etapa-1-funciones.md) | ✅ listo |
| 2306396 | Valles Arriaga Iker Karol | [ver](alumnos/2306396-valles-arriaga-iker-karol-etapa-1-funciones.md) | ✅ listo |
| 2306545 | Vazquez Palacios Angel Daniel | [ver](alumnos/2306545-vazquez-palacios-angel-daniel-etapa-1-funciones.md) | ✅ listo |

---

## Entregables

Dos archivos de código fuente en C++, uno por cada programa. Guárdalos como
texto plano (`.txt`) — NEXUS no acepta cargar archivos `.cpp`:

1. El programa que resuelve el **Programa 1** (facturación, enunciado común).
2. El programa que resuelve el **Programa 2** de tu enunciado personalizado.

Ambos deben compilar y ejecutarse sin errores en Dev-C++.

---

## Forma de Entrega

- **Modalidad:** Individual. Cada alumno entrega sus propios archivos.
- **Plataforma:** NEXUS. Carga tus dos archivos en la evidencia
  *"1.1 - Evidencia de Aprendizaje 1: Laboratorio de Programas"*.
- Nombra tus archivos de la siguiente forma:

```
EV1.1_ApellidoNombre_p1.txt
EV1.1_ApellidoNombre_p2.txt
```

- **Fecha de entrega:** Domingo 13 de septiembre de 2026.
- **Hora límite:** 10:00 p.m.

---

## Rúbrica de Evaluación

| CRITERIO / NIVEL DE DOMINIO | Evidencia completa | Evidencia suficiente | Evidencia débil | Sin evidencia |
|-----------------------------|--------------------|---------------------|-----------------|---------------|
| **Conocimientos** — Relaciona los contenidos de la etapa con las actividades solicitadas. | **3** — Identifica todos los conceptos aprendidos en los temas de funciones. | **2** — Identifica la mayoría de los conceptos aprendidos en los temas de funciones. | **1** — Identifica pocos de los conceptos aprendidos en los temas de funciones. | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Habilidades** — Soluciona todas las actividades planteadas utilizando de manera correcta los conceptos de funciones. | **5** — Ambos programas compilan y ejecutan sin errores; las funciones de cálculo no usan `cin` ni `cout`; los valores de la tabla (límites, porcentajes, tasas) están definidos como constantes con nombre; el código es fácil de seguir y leer, con nombres de función descriptivos y buenas prácticas de programación. | **4** — Ambos programas compilan y funcionan, pero el código es poco claro o con estructura poco definida: alguna función de cálculo interactúa con el usuario, validación incompleta, o uso parcial de constantes. | **3** — El código funciona sin estructura clara y es difícil de comprender: mezcla cálculo con entrada/salida dentro de las funciones, no usa constantes para los valores de la tabla, o no valida los datos numéricos solicitados. | **0** — No cumple con los criterios establecidos o no presenta evidencia de la actividad. |
| **Actitudes / Valores** — Cumple con la estructura y características de la actividad. | **2** — Entregado en tiempo y con buena participación en la elaboración de las actividades, cumpliendo con las características solicitadas. | **1** — Entregado fuera de tiempo y/o con participación regular en la elaboración y/o cumplimiento de las características de las actividades. | **0** — Entregado fuera de tiempo y/o con poca participación en la elaboración y/o cumplimiento de las actividades. | **0** — No participó en la elaboración de las actividades. |
