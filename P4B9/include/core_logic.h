/**
 * @file core_logic.h
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Declaraciones de la lógica principal del programa desacoplada del punto de entrada.
 * @version 0.1
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VDinamico.h"
#include "ListaEnlazada.h"
#include "PaMedicamento.h"
#include "MediExpress.h"

/**
 * @brief Intenta leer un entero sin signo desde la entrada estándar de forma segura.
 *
 * Gestiona errores de entrada (por ejemplo, texto en lugar de número) limpiando el
 * estado de std::cin para evitar bucles infinitos en pruebas automatizadas.
 *
 * @param[out] value Variable donde se almacenará el valor leído.
 * @return true  Si la lectura fue correcta o si hubo un error recuperable.
 * @return false Si se alcanzó el fin de fichero (EOF), indicando que se debe terminar.
 */
bool safe_read(unsigned int& value);

/**
 * @brief Ejecuta la simulación completa del programa.
 *
 * Contiene toda la lógica que antes residía en main(): pruebas de ListaEnlazada<int>
 * y operaciones sobre el sistema MediExpress. Al estar desacoplada de main(), esta
 * función puede ser invocada y verificada por el framework de pruebas Google Test.
 *
 * Los parámetros tienen valores por defecto para que main() no necesite cambios.
 * Los tests pasan rutas propias para no tocar nunca los datos reales del proyecto.
 *
 * @param medsPath Ruta al CSV de medicamentos.
 * @param labsPath Ruta al CSV de laboratorios.
 */
void run_simulation(
    const std::string& medsPath = "../data/pa_medicamentos.csv",
    const std::string& labsPath = "../data/laboratorios.csv"
);
