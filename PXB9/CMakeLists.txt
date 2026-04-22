cmake_minimum_required(VERSION 3.14)
# Nombre del proyecto
project(Practica3_Tests CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# --- CORRECCIONES PARA LABORATORIO (WINDOWS/MINGW) ---
# 1. SOLUCIÓN ERROR SSL:
# Desactivamos verificación SSL para evitar fallos de descarga en red
#universitaria
set(CMAKE_TLS_VERIFY 0)
# 2. SOLUCIÓN CONFLICTO RUNTIME:
# Fuerza a GTest a usar las mismas librerías dinámicas que MinGW
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# --- CONFIGURACIÓN GOOGLE TEST (Descarga Automática) ---
include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
 DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)
# --- DEFINICIÓN AUTOMÁTICA DE FUENTES ---
# Busca TODOS los .cpp dentro de la carpeta src/
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
# IMPORTANTE: Eliminamos 'main.cpp' de esta lista para poder usar
# el resto del código en los tests sin duplicar la función 'main()'
# (Ajusta la ruta si tu main.cpp está en otro lugar)
list(FILTER ALL_SOURCES EXCLUDE REGEX "main.cpp$")
# --- EJECUTABLE PRINCIPAL (La aplicación normal) ---
add_executable(MiPrograma src/main.cpp ${ALL_SOURCES})
# --- EJECUTABLE DE TESTS (Google Test) ---
enable_testing()
add_executable(MisTests
 tests/test_main.cpp # Tu fichero de tests
 ${ALL_SOURCES} # Toda la lógica SIN el main.cpp original
)
# Configuración de Includes y Librerías
target_include_directories(MiPrograma PRIVATE include)
target_include_directories(MisTests PRIVATE include)
target_link_libraries(MisTests GTest::gtest_main)
# Integración con el explorador de tests de VS Code
include(GoogleTest)
gtest_discover_tests(MisTests)