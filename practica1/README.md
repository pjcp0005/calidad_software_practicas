# 📦 Proyecto: Practica2Listas

Proyecto C++ que implementa dos estructuras de datos genéricas propias: un **vector dinámico** (`VDinamico<T>`) con redimensionamiento automático basado en potencias de 2, y una **lista enlazada simple** (`ListaEnlazada<T>`) con iterador propio. Ambas estructuras se usan como base del sistema **MediExpress**, una aplicación de gestión del padrón de medicamentos que carga datos desde ficheros CSV, enlaza automáticamente medicamentos con laboratorios y ofrece búsquedas por nombre de ciudad, compuesto activo o laboratorio. El proyecto está organizado en varias carpetas que separan las cabeceras, implementaciones, datos y archivos de compilación, facilitando la modularidad y el mantenimiento del código.

## 🗂️ Estructura del proyecto

```
Practica2Listas/
│
├── include/                # Archivos de cabecera (.h)
│   ├── MediExpress.h
│   ├── PaMedicamento.h
│   ├── Laboratorio.h
│   ├── VDinamico.h
│   └── ListaEnlazada.h
│
├── src/                    # Implementaciones (.cpp y .tpp)
│   ├── MediExpress.cpp
│   ├── PaMedicamento.cpp
│   ├── VDinamico.tpp
│   ├── ListaEnlazada.tpp
│   ├── Laboratorio.cpp
│   └── main.cpp            # Punto de entrada del programa
│
├── build/                  # Archivos generados en la compilación
│   ├── *.o
│   └── MediExpress.exe / MediExpress.out
│
├── data/                   # Archivos de datos de prueba
│   ├── pa_medicamentos.csv
│   └── laboratorios.csv
│
├── Makefile                # (Opcional) Compilación automática
└── CMakeLists.txt          # Configuración para CMake
```

## 📁 Descripción de carpetas

- **`include/`** → Cabeceras con definiciones de clases y funciones.
- **`src/`** → Implementaciones en C++.
- **`data/`** → Archivos CSV de prueba.
- **`Makefile` / `CMakeLists.txt`** → Archivos para automatizar la compilación.

## Warnings del compilador GCC (corregidos)

Warnings detectados al compilar con GCC (`-Wall -Wextra`), visibles en la pestaña **Problemas** de VS Code filtrando con `!sonar`.

| Archivo | Línea original | Warning | Solución aplicada |
|---|---|---|---|
| [Laboratorio.cpp](src/Laboratorio.cpp) | 32 | `comparison of integer expressions of different signedness: 'const unsigned int' and 'int' [-Wsign-compare]` — comparación entre `m_id` (`unsigned int`) y el retorno de `getId()` (`int`). | Se añadió `static_cast<int>(m_id)` en `operator==` para que ambos operandos sean del mismo tipo. |
| [main.cpp](src/main.cpp) | 49 | `unused parameter 'argc' [-Wunused-parameter]` y `unused parameter 'argv' [-Wunused-parameter]` — los parámetros de `main` se declaraban pero no se usaban. | Se eliminaron los parámetros de la firma: `int main()`. Se actualizó también el comentario Doxygen. |
| [MediExpress.cpp](src/MediExpress.cpp) | 26 | `unused variable 'count' [-Wunused-variable]` — variable `int count = 0` declarada y nunca usada. | Se eliminó la declaración de `count`. |
| [MediExpress.cpp](src/MediExpress.cpp) | 36 | `unused variable 't_ini' [-Wunused-variable]` — variable `clock_t t_ini = clock()` declarada y nunca usada (probablemente de una medición de tiempo abandonada). | Se eliminó la declaración de `t_ini`. |
| [MediExpress.cpp](src/MediExpress.cpp) | 186 | `comparison of integer expressions of different signedness: 'int' and 'unsigned int' [-Wsign-compare]` — variable de bucle `int i` comparada con `unsigned int siz`. | Se cambió el tipo de `i` a `unsigned int` en `buscarCompuesto`. |
| [MediExpress.cpp](src/MediExpress.cpp) | 199 | `comparison of integer expressions of different signedness: 'int' and 'unsigned int' [-Wsign-compare]` — mismo problema en `getMedicamSinLab`. | Se cambió el tipo de `i` a `unsigned int` en `getMedicamSinLab`. |
| [VDinamico.tpp](src/VDinamico.tpp) | 260 | `comparison of integer expressions of different signedness: 'int' and 'unsigned int' [-Wsign-compare]` — en `insert`, el bucle `int i = m_tamal` se comparaba con `unsigned int index`. | Se aplicaron `static_cast<int>` sobre `m_tamal` e `index` para homogeneizar los tipos del bucle. |

## Warnings de SonarQube

Warnings detectados con SonarLint al filtrar con `!sonar` en la pestaña **Problemas** de VS Code.

### No corregidos

| Archivo | Línea | Regla | Descripción | Justificación |
|---|---|---|---|---|
| [PaMedicamento.h](include/PaMedicamento.h) | 55 | `cpp:S2807` | `operator==` debería ser un *hidden friend* en lugar de miembro. | Cambiar a `friend` modificaría la interfaz pública de la clase y podría romper código existente que depende de la llamada como miembro. Se mantiene como miembro para preservar la coherencia con `operator<`. |
| [PaMedicamento.h](include/PaMedicamento.h) | 62 | `cpp:S2807` | `operator<` debería ser un *hidden friend* en lugar de miembro. | Misma justificación que `operator==`. Ambos operadores se mantienen como miembros para coherencia interna. |
| [Laboratorio.h](include/Laboratorio.h) | 62 | `cpp:S2807` | `operator==` debería ser un *hidden friend* en lugar de miembro. | Misma justificación. El operador se mantiene como miembro para no alterar la interfaz ya utilizada en `MediExpress`. |
