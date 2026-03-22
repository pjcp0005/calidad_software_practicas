// tests/test_main.cpp
#include <gtest/gtest.h>
#include "../include/core_logic.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio> // Para std::remove

// Fixture de prueba para redirigir la salida estándar y manejar los archivos de prueba
class SimulationTest : public ::testing::Test {
protected:
    std::stringstream cout_buffer;
    std::stringstream cerr_buffer;
    std::streambuf* orig_cout;
    std::streambuf* orig_cerr;

    void SetUp() override {
        // Redirigir std::cout y std::cerr a nuestros stringstreams
        orig_cout = std::cout.rdbuf(cout_buffer.rdbuf());
        orig_cerr = std::cerr.rdbuf(cerr_buffer.rdbuf());
    }

    void TearDown() override {
        // Restaurar los buffers originales
        std::cout.rdbuf(orig_cout);
        std::cerr.rdbuf(orig_cerr);
    }

    // Funciones auxiliares para simular los CSVs ya que las rutas están "hardcodeadas"
    void createDummyFiles(bool empty = false) {
        std::ofstream meds("../data/pa_medicamentos.csv");
        std::ofstream labs("../data/laboratorios.csv");
        
        if (!empty) {
            // Generar contenido simulado válido
            meds << "id,nombre,laboratorio\n1,Paracetamol,1\n2,Ibuprofeno,2\n3,Aceite de Ricino,1\n";
            labs << "id,nombre,ciudad\n1,FarmaGen,Granada\n2,HealthMed,Madrid\n3,SaludSur,jaen\n";
        }
        
        meds.close();
        labs.close();
    }

    void removeDummyFiles() {
        std::remove("../data/pa_medicamentos.csv");
        std::remove("../data/laboratorios.csv");
    }
};

// Caso 1: Normal (Happy Path) - Ejecución estándar válida
TEST_F(SimulationTest, HappyPathNormalExecution) {
    createDummyFiles(false);
    
    // Ejecutar la función a probar
    run_simulation();
    
    std::string output = cout_buffer.str();
    
    // Validar la prueba de la lista enlazada
    EXPECT_NE(output.find("Todos los pasos se ejecutaron correctamente."), std::string::npos) 
        << "No se encontro el mensaje de exito de la ListaEnlazada.";
    
    // Validar la salida de los laboratorios
    EXPECT_NE(output.find("Labs Granada"), std::string::npos);
    EXPECT_NE(output.find("Labs Madrid, 10 primeros"), std::string::npos);
    
    // Validar que no hay errores en cerr
    EXPECT_TRUE(cerr_buffer.str().empty()) << "Se detectaron errores en std::cerr durante el Happy Path.";
    
    removeDummyFiles();
}

// Caso 2: Borde (Edge Case) - Archivos de entrada vacíos (cero datos reales)
TEST_F(SimulationTest, EdgeCaseEmptyFiles) {
    createDummyFiles(true); // Crea los archivos, pero sin contenido
    
    run_simulation();
    
    std::string output = cout_buffer.str();
    
    // La prueba de lista enlazada (Prueba I) debería ejecutarse igual
    EXPECT_NE(output.find("Todos los pasos se ejecutaron correctamente."), std::string::npos);
    
    // Para la Prueba II, las listas de laboratorios y medicamentos deben ser 0
    EXPECT_NE(output.find("Medicamentos sin laboratorio: 0"), std::string::npos) 
        << "Se esperaban 0 medicamentos al leer un CSV vacio.";
    EXPECT_NE(output.find("Laboratorios en Granada o provincia: 0"), std::string::npos);
    EXPECT_NE(output.find("Laboratorios en Madrid o provincia: 0"), std::string::npos);
    
    // Verificar que no crashea al intentar asignar laboratorios sin datos
    EXPECT_NE(output.find("Asignacion dinamica a laboratorios de Madrid"), std::string::npos);
    
    EXPECT_TRUE(cerr_buffer.str().empty());
    
    removeDummyFiles();
}

// Caso 3: Error - Entradas inválidas (archivos inexistentes)
TEST_F(SimulationTest, ErrorCaseMissingFiles) {
    removeDummyFiles(); // Asegurarnos de que no existen los CSV
    
    run_simulation();
    
    // MediExpress debería lanzar una excepción al no encontrar los archivos.
    // El bloque try-catch en run_simulation() atrapará la excepción y la imprimirá en std::cerr.
    std::string error_output = cerr_buffer.str();
    
    EXPECT_FALSE(error_output.empty()) 
        << "Se esperaba un mensaje de error en std::cerr al no encontrar los archivos CSV.";
}