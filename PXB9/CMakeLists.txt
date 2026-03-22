cmake_minimum_required(VERSION 3.14)
# Nombre del proyecto
project(Practica2_Tests CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# --- CORRECCIONES PARA LABORATORIO (WINDOWS/MINGW) ---
# 1. SOLUCIÓN ERROR SSL:
# Desactivamos verificación SSL para evitar fallos de descarga en red
universitaria
set(CMAKE_TLS_VERIFY 0)
# 2. SOLUCIÓN CONFLICTO RUNTIME:
# Fuerza a GTest a usar las mismas librerías dinámicas que MinGW
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
