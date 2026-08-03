# Instalación del entorno de C++ (Programación II)

Hay dos rutas distintas para compilar y ejecutar tus programas de C++:

- **Opción A — Dev-C++** (Windows): un solo instalador, botón de "Compilar y
  ejecutar", sin terminal.
- **Opción B — Compilador por terminal**: instala el compilador `g++` (paso distinto
  por sistema operativo) y usa la terminal directamente. Una vez instalado, ver
  [COMPILACION.md](COMPILACION.md) para los comandos de compilar y ejecutar.

## Opción A: Dev-C++ (Windows)

1. Descarga el instalador desde [sourceforge.net/projects/orwelldevcpp](https://sourceforge.net/projects/orwelldevcpp/)
   (la versión más mantenida del Dev-C++ original, trae MinGW incluido).
2. Instala con las opciones por default.
3. Configura el estándar de C++ a C++17 (el default de Dev-C++ suele ser más viejo):
   - Menú **Herramientas → Opciones del Compilador** (Tools → Compiler Options).
   - Pestaña **Configuraciones** → activa "Agregar los siguientes comandos" y escribe:
     ```
     -std=c++17
     ```
4. Para compilar y ejecutar un programa: abre el `.cpp`, presiona **F11** (o el botón
   "Compilar y ejecutar"). Se abre una consola con el resultado.

## Opción B: Instalar el compilador por terminal

Paso distinto por sistema operativo, una sola vez:

### Windows
1. Abre PowerShell y ejecuta:
   ```powershell
   winget install -e --id MSYS2.MSYS2
   ```
2. Abre "MSYS2 UCRT64" desde el menú inicio y ejecuta:
   ```bash
   pacman -Syu
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```
3. Agrega `C:\msys64\ucrt64\bin` a la variable de entorno **PATH** (Panel de control →
   Sistema → Configuración avanzada → Variables de entorno).
4. Verifica en una terminal nueva: `g++ --version`.

### macOS
1. Abre la Terminal y ejecuta:
   ```bash
   xcode-select --install
   ```
2. Acepta la instalación de las "Herramientas de línea de comandos".
3. Verifica: `g++ --version` (en macOS esto en realidad invoca a `clang++`, es normal y
   totalmente compatible con lo que usaremos).

### Linux (Debian/Ubuntu y derivados)
```bash
sudo apt update
sudo apt install build-essential
```
Para Fedora: `sudo dnf groupinstall "Development Tools"`
Verifica: `g++ --version`

Con el compilador ya instalado, sigue en [COMPILACION.md](COMPILACION.md) para compilar
y ejecutar programas desde la terminal.
