# Section 1.1: Installing C++ Compiler and SFML Library

## Overview
Setting up the development environment for C++ game development with SFML on Linux. This covers installing the compiler, build tools, and SFML library.

---

## Key Concepts

### The Build Toolchain
A complete C++ development environment requires:
- **C++ Compiler (g++)**: Converts source code (.cpp) into executable programs
- **Build tools**: Utilities like `make` that automate compilation
- **Development headers**: Interface files (.hpp) needed to compile against libraries

### SFML Library Structure
SFML (Simple and Fast Multimedia Library) is modular:
- **sfml-system**: Core functionality (time, threads, vectors)
- **sfml-window**: Window management and input handling
- **sfml-graphics**: 2D rendering (sprites, textures, shapes)
- **sfml-audio**: Sound effects and music
- **sfml-network**: Network communication

### Package Types on Linux

**Runtime packages:**
- Contain compiled libraries (.so files)
- Needed to *run* programs
- Example: `libsfml2.5`

**Development packages:**
- Contain headers (.hpp files) and libraries
- Needed to *compile* programs
- Always have `-dev` suffix
- Example: `libsfml-dev`

### Installation on Ubuntu/Debian
Two essential packages:
1. **build-essential**: Contains g++, make, and core build tools
2. **libsfml-dev**: SFML headers and libraries for development

The package manager automatically installs dependencies.

### Compilation Process

**Basic workflow:**
1. Write source code (.cpp files)
2. Compile with g++ and linker flags
3. Run the executable

**Linker flags** tell the compiler which libraries to link:
- `-lsfml-graphics`: Graphics module (includes window and system)
- `-lsfml-window`: Window module (includes system)
- `-lsfml-system`: Core system module
- `-o filename`: Output executable name

### Common Errors

| Error Message | Meaning | Solution |
|---------------|---------|----------|
| `fatal error: SFML/Graphics.hpp: No such file or directory` | Headers not found | Install `libsfml-dev` |
| `undefined reference to 'sf::...'` | Missing linker flags | Add `-lsfml-graphics -lsfml-window -lsfml-system` |
| `cannot open shared object file` | Runtime libraries missing | Install SFML runtime packages |

### Verification
After installation, verify:
- Compiler version: Check g++ is installed
- SFML packages: Confirm libsfml-dev is installed
- Test compilation: Try compiling a simple SFML program

---

## Important Notes
- Package names are **case-sensitive** and must be exact
- The order of linker flags doesn't matter, but all required flags must be present
- Development packages include both headers and libraries
- File paths in code are relative to where you *run* the executable, not where the source file is located

---

## Best Practices
- Install all dependencies before writing code
- Keep SFML updated to the latest stable version
- Use a consistent project structure (separate folders for source, assets, build)
- Test your setup with a minimal program before starting complex projects