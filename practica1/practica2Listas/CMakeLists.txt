cmake_minimum_required(VERSION 3.29)
project(Practica2Listas)

set(CMAKE_CXX_STANDARD 14)

# Directorio de headers
include_directories(include)

# Archivos fuente
add_executable(Practica2Listas
        src/main.cpp
        src/MediExpress.cpp
        src/PaMedicamento.cpp
        src/Laboratorio.cpp
        src/utils.cpp
)