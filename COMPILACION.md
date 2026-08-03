# Compilar y ejecutar desde la terminal

Requiere tener el compilador `g++` instalado (ver [INSTALACION.md](INSTALACION.md),
Opción B).

Compilar y ejecutar son dos pasos distintos y dos comandos distintos.

## Paso 1: Compilar

```bash
g++ archivo.cpp
```

Sin flags, `g++` usa el nombre de salida por default:
- **macOS/Linux** → genera `a.out`
- **Windows (MinGW)** → genera `a.exe`

Si hay errores, se muestran aquí, con el número de línea del `.cpp` donde ocurrieron —
y no se genera ningún ejecutable hasta que el código compile sin errores.

## Paso 2: Ejecutar

```bash
./a.out         # macOS/Linux
a.exe           # Windows
```

## Qué archivos se generan

Con este comando, `g++` hace todo el proceso de compilación (preprocesado →
compilación → ensamblado → enlazado) **en una sola pasada**, y solo deja en el disco
el ejecutable final (`a.out` / `a.exe`). No quedan archivos intermedios (como `.o`) —
esos se generan y se descartan internamente durante el proceso, a menos que se pida
explícitamente compilar sin enlazar (`g++ -c`, que no se usa en este curso).

Cada vez que vuelves a compilar, `a.out`/`a.exe` se sobrescribe con la versión nueva.

## Flags opcionales

### `-std=c++17` — fijar el estándar de C++

Sin este flag, `g++` usa el estándar por default de tu versión instalada, que puede
variar entre máquinas. Para asegurar que el código se comporte igual en cualquier
computadora, agrégalo:

```bash
g++ -std=c++17 archivo.cpp
```

Los programas de este curso no requieren features específicas de C++17, así que
normalmente no hace falta — pero es buena práctica si vas a comparar resultados entre
distintas instalaciones de `g++`.

### `-Wall` y `-o` — revisar código con más cuidado y nombrar el ejecutable

```bash
g++ -std=c++17 -Wall archivo.cpp -o archivo
```

- `-Wall` — activa warnings del compilador (variables sin usar, comparaciones raras, etc.).
- `-o archivo` — nombre del ejecutable de salida, en vez de `a.out`/`a.exe`.

## Probar que todo funciona

Esta prueba es solo para verificar la instalación — no forma parte del curso, así que
hazla fuera del repo (por ejemplo en una carpeta temporal) para no dejar ejecutables
residuales dentro de `ejercicios/`.

1. Crea un archivo `prueba.cpp` en una carpeta temporal con este contenido:
   ```cpp
   #include <iostream>
   using namespace std;

   int main() {
       string nombre;
       cout << "Escribe tu nombre y presiona Enter: ";
       cin >> nombre;
       cout << "Hola, " << nombre << ". El entorno de C++ funciona correctamente.\n";
       return 0;
   }
   ```
2. Compílalo y ejecútalo ahí mismo:
   ```bash
   g++ prueba.cpp
   ./a.out         # macOS/Linux
   a.exe           # Windows
   ```
3. Debe pedir un nombre por teclado (`cin`) y luego mostrar el mensaje de éxito.
4. Borra la carpeta temporal cuando termines — ya cumplió su propósito.

Si ves ese mensaje, el entorno quedó listo para compilar y correr cualquier programa
de ejemplo del manual.
