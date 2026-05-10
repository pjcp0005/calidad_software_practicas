/**
 * @file test_main.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Batería de pruebas unitarias para la función run_simulation() generada con IA
 *        y revisada manualmente. Cubre los tres tipos de prueba exigidos: Happy Path,
 *        Edge Case y Error Handling.
 * @version 0.2
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2026
 */

#include <gtest/gtest.h>
#include "../include/core_logic.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

// ─────────────────────────────────────────────────────────────────────────────
// Rutas de ficheros exclusivos para tests (nunca coinciden con datos reales)
// ─────────────────────────────────────────────────────────────────────────────
static const std::string TEST_MEDS = "../data/test_pa_medicamentos.csv";
static const std::string TEST_LABS = "../data/test_laboratorios.csv";

// ─────────────────────────────────────────────────────────────────────────────
// Fixture: SimulationTest
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Fixture de prueba para aislar run_simulation() del entorno real.
 *
 * Antes de cada test (SetUp):
 *   - Redirige std::cout y std::cerr a stringstreams para capturar la salida.
 *
 * Después de cada test (TearDown):
 *   - Restaura std::cout y std::cerr a sus buffers originales.
 *   - Elimina los ficheros de test temporales si existen.
 *
 * Los datos reales del proyecto (pa_medicamentos.csv, laboratorios.csv) nunca
 * se tocan porque run_simulation() recibe rutas de test como parámetro.
 */
class SimulationTest : public ::testing::Test {
protected:
    std::stringstream cout_buffer;
    std::stringstream cerr_buffer;
    std::streambuf* orig_cout = nullptr;
    std::streambuf* orig_cerr = nullptr;

    // ── Utilidades de fichero ─────────────────────────────────────────────

    /**
     * @brief Escribe contenido en un fichero, creándolo o sobreescribiéndolo.
     * @param path    Ruta al fichero destino.
     * @param content Contenido a escribir.
     */
    static void writeFile(const std::string& path, const std::string& content) {
        std::ofstream f(path, std::ios::binary);
        f << content;
    }

    // ── Helpers de datos de prueba ────────────────────────────────────────

    /**
     * @brief Crea ficheros CSV de test con datos mínimos pero válidos.
     *
     * Formato de medicamentos: id_num;id_alpha;nombre;
     * Formato de laboratorios: id;nombre;direccion;cod_postal;localidad
     *
     * Con estos datos, autoLinkMedications() asigna:
     *   - Lab 1 (Granada) → meds 1 y 2
     *   - Lab 2 (Madrid)  → med 3 (Aceite de Ricino)
     */
    void createValidFiles() {
        writeFile(TEST_MEDS,
            "1;MED001;Paracetamol;\n"
            "2;MED002;Ibuprofeno;\n"
            "3;MED003;Aceite de Ricino;\n");
        writeFile(TEST_LABS,
            "1;FarmaGen S.L.;Calle Mayor 1;18001;Granada\n"
            "2;HealthMed S.A.;Calle Alcala 10;28001;Madrid\n");
    }

    /**
     * @brief Crea ficheros CSV de test vacíos (sin ninguna línea de datos).
     *
     * Sirve para verificar que el sistema se comporta correctamente cuando
     * no hay medicamentos ni laboratorios cargados.
     */
    void createEmptyFiles() {
        writeFile(TEST_MEDS, "");
        writeFile(TEST_LABS, "");
    }

    // ── Ciclo de vida del fixture ─────────────────────────────────────────

    void SetUp() override {
        orig_cout = std::cout.rdbuf(cout_buffer.rdbuf());
        orig_cerr = std::cerr.rdbuf(cerr_buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(orig_cout);
        std::cerr.rdbuf(orig_cerr);

        // Eliminar los ficheros temporales de test (no son datos reales)
        std::remove(TEST_MEDS.c_str());
        std::remove(TEST_LABS.c_str());
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// Caso 1: Happy Path — ejecución normal con datos válidos
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Happy Path: verifica que run_simulation() completa correctamente con datos válidos.
 *
 * Se crean ficheros CSV de test con formato correcto (separador ';', campos completos).
 * Se comprueba que:
 *   - La Prueba I (ListaEnlazada) imprime el mensaje de éxito final.
 *   - La Prueba II (MediExpress) muestra los bloques de laboratorios esperados.
 *   - No se emite ningún mensaje de error por std::cerr.
 */
TEST_F(SimulationTest, RunSimulation_HappyPath) {
    createValidFiles();

    run_simulation(TEST_MEDS, TEST_LABS);

    const std::string output = cout_buffer.str();

    EXPECT_NE(output.find("Todos los pasos se ejecutaron correctamente."), std::string::npos)
        << "No se encontro el mensaje de exito de la ListaEnlazada.";
    EXPECT_NE(output.find("Labs Granada"), std::string::npos)
        << "Falta el bloque de laboratorios de Granada.";
    EXPECT_NE(output.find("Labs Madrid, 10 primeros"), std::string::npos)
        << "Falta el bloque de laboratorios de Madrid.";
    EXPECT_TRUE(cerr_buffer.str().empty())
        << "Se emitieron errores inesperados en std::cerr: " << cerr_buffer.str();
}

// ─────────────────────────────────────────────────────────────────────────────
// Caso 2: Edge Case — ficheros de entrada vacíos (cero registros)
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Edge Case: verifica que run_simulation() no falla con ficheros CSV vacíos.
 *
 * Con ficheros vacíos, MediExpress carga 0 medicamentos y 0 laboratorios.
 * Se comprueba que:
 *   - La Prueba I se completa igualmente (no usa los CSV).
 *   - Los contadores de la Prueba II muestran 0 registros cargados.
 *   - No se produce ningún fallo catastrófico (crash o excepción no capturada).
 *   - std::cerr permanece vacío (ficheros vacíos se abren correctamente).
 */
TEST_F(SimulationTest, RunSimulation_EdgeCase_EmptyFiles) {
    createEmptyFiles();

    run_simulation(TEST_MEDS, TEST_LABS);

    const std::string output = cout_buffer.str();

    EXPECT_NE(output.find("Todos los pasos se ejecutaron correctamente."), std::string::npos)
        << "La Prueba I no debe depender de los CSV.";
    EXPECT_NE(output.find("Medicamentos sin laboratorio: 0"), std::string::npos)
        << "Con CSV vacios debe haber 0 medicamentos sin laboratorio.";
    EXPECT_NE(output.find("Laboratorios en Granada o provincia: 0"), std::string::npos)
        << "Con CSV vacios debe haber 0 laboratorios en Granada.";
    EXPECT_NE(output.find("Laboratorios en Madrid o provincia: 0"), std::string::npos)
        << "Con CSV vacios debe haber 0 laboratorios en Madrid.";
    EXPECT_TRUE(cerr_buffer.str().empty())
        << "Ficheros vacios (pero existentes) no deben generar errores.";
}

// ─────────────────────────────────────────────────────────────────────────────
// Caso 3: Error Handling — ficheros de entrada inexistentes
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Error Handling: verifica que run_simulation() reporta el error cuando
 *        los ficheros CSV no existen, sin bloquearse ni lanzar una excepción no capturada.
 *
 * loadLabFromCsv() imprime en std::cerr cuando no puede abrir el fichero de laboratorios.
 * No se crean ficheros de test, por lo que las rutas apuntan a ficheros inexistentes.
 * Se comprueba que:
 *   - std::cerr contiene al menos un mensaje de error descriptivo.
 *   - La función termina de forma controlada (no hay crash).
 */
TEST_F(SimulationTest, RunSimulation_ErrorHandling_MissingFiles) {
    // No llamamos a createValidFiles() ni createEmptyFiles():
    // TEST_MEDS y TEST_LABS no existen → run_simulation() debe reportar el error.

    run_simulation(TEST_MEDS, TEST_LABS);

    EXPECT_FALSE(cerr_buffer.str().empty())
        << "Se esperaba un mensaje de error en std::cerr al faltar los ficheros CSV.";
}
