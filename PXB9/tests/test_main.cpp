/**
 * @file test_main.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Batería de pruebas unitarias para la función run_simulation() generada con IA
 *        y revisada manualmente. Cubre los tres tipos de prueba exigidos: Happy Path,
 *        Edge Case y Error Handling.
 * @version 0.1
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
// Fixture: SimulationTest
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Fixture de prueba para aislar run_simulation() del entorno real.
 *
 * Antes de cada test (SetUp):
 *   - Redirige std::cout y std::cerr a stringstreams para capturar la salida.
 *   - Lee y guarda en memoria el contenido de los CSV reales (backup).
 *
 * Después de cada test (TearDown):
 *   - Restaura std::cout y std::cerr a sus buffers originales.
 *   - Restaura los CSV reales desde el backup, garantizando que los datos del
 *     proyecto nunca se pierden, independientemente del resultado del test.
 */
class SimulationTest : public ::testing::Test {
protected:
    std::stringstream cout_buffer;
    std::stringstream cerr_buffer;
    std::streambuf* orig_cout = nullptr;
    std::streambuf* orig_cerr = nullptr;

    // Contenido de los ficheros reales guardado antes de cada test
    std::string backup_meds_;
    std::string backup_labs_;
    bool meds_existed_ = false;
    bool labs_existed_ = false;

    // ── Utilidades de fichero ─────────────────────────────────────────────

    /**
     * @brief Lee el contenido completo de un fichero en una cadena.
     * @param path   Ruta al fichero.
     * @param[out] existed Verdadero si el fichero existía y se pudo abrir.
     * @return Contenido del fichero, o cadena vacía si no existe.
     */
    static std::string readFile(const std::string& path, bool& existed) {
        std::ifstream f(path, std::ios::binary);
        existed = f.is_open();
        if (!existed) return "";
        return std::string(
            (std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>()
        );
    }

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
     * @brief Crea ficheros CSV con datos mínimos pero válidos para pruebas normales.
     *
     * Formato de medicamentos: id_num;id_alpha;nombre;
     * Formato de laboratorios: id;nombre;direccion;cod_postal;localidad
     *
     * Con estos datos, autoLinkMedications() asigna:
     *   - Lab 1 (Granada) → meds 1 y 2
     *   - Lab 2 (Madrid)  → med 3 (Aceite de Ricino)
     */
    void createValidFiles() {
        writeFile("../data/pa_medicamentos.csv",
            "1;MED001;Paracetamol;\n"
            "2;MED002;Ibuprofeno;\n"
            "3;MED003;Aceite de Ricino;\n");
        writeFile("../data/laboratorios.csv",
            "1;FarmaGen S.L.;Calle Mayor 1;18001;Granada\n"
            "2;HealthMed S.A.;Calle Alcala 10;28001;Madrid\n");
    }

    /**
     * @brief Crea ficheros CSV vacíos (sin ninguna línea de datos).
     *
     * Sirve para verificar que el sistema se comporta correctamente cuando
     * no hay medicamentos ni laboratorios cargados.
     */
    void createEmptyFiles() {
        writeFile("../data/pa_medicamentos.csv", "");
        writeFile("../data/laboratorios.csv",    "");
    }

    /**
     * @brief Elimina ambos ficheros CSV del directorio de datos.
     *
     * Usado para simular la ausencia de ficheros de entrada y verificar
     * que el sistema reporta el error sin bloquearse.
     */
    void deleteDataFiles() {
        std::remove("../data/pa_medicamentos.csv");
        std::remove("../data/laboratorios.csv");
    }

    // ── Ciclo de vida del fixture ─────────────────────────────────────────

    void SetUp() override {
        // Redirigir salidas estándar
        orig_cout = std::cout.rdbuf(cout_buffer.rdbuf());
        orig_cerr = std::cerr.rdbuf(cerr_buffer.rdbuf());

        // Hacer backup de los ficheros reales antes de cualquier modificación
        backup_meds_ = readFile("../data/pa_medicamentos.csv", meds_existed_);
        backup_labs_ = readFile("../data/laboratorios.csv",    labs_existed_);
    }

    void TearDown() override {
        // Restaurar buffers de consola
        std::cout.rdbuf(orig_cout);
        std::cerr.rdbuf(orig_cerr);

        // Restaurar los ficheros originales siempre, pase lo que pase en el test
        if (meds_existed_)
            writeFile("../data/pa_medicamentos.csv", backup_meds_);
        else
            std::remove("../data/pa_medicamentos.csv");

        if (labs_existed_)
            writeFile("../data/laboratorios.csv", backup_labs_);
        else
            std::remove("../data/laboratorios.csv");
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// Caso 1: Happy Path — ejecución normal con datos válidos
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Happy Path: verifica que run_simulation() completa correctamente con datos válidos.
 *
 * Se crean ficheros CSV con formato correcto (separador ';', campos completos).
 * Se comprueba que:
 *   - La Prueba I (ListaEnlazada) imprime el mensaje de éxito final.
 *   - La Prueba II (MediExpress) muestra los bloques de laboratorios esperados.
 *   - No se emite ningún mensaje de error por std::cerr.
 */
TEST_F(SimulationTest, RunSimulation_HappyPath) {
    createValidFiles();

    run_simulation();

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

    run_simulation();

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
 * Se comprueba que:
 *   - std::cerr contiene al menos un mensaje de error descriptivo.
 *   - La función termina de forma controlada (no hay crash).
 */
TEST_F(SimulationTest, RunSimulation_ErrorHandling_MissingFiles) {
    deleteDataFiles();

    run_simulation();

    EXPECT_FALSE(cerr_buffer.str().empty())
        << "Se esperaba un mensaje de error en std::cerr al faltar los ficheros CSV.";
}
