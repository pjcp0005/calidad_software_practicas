/**
 * @file main.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Punto de entrada del programa. Pruebas de ListaEnlazada y MediExpress.
 * @version 0.1
 * @date 2025-10-08
 *
 * @copyright Copyright (c) 2026
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/MediExpress.h"

/**
 * @brief Imprime por consola los elementos de una ListaEnlazada<int>.
 * @param lista Lista enlazada de enteros a mostrar.
 */
void mostrarLista(const ListaEnlazada<int> &lista) {
    auto it = lista.iterator();
    std::cout << "[ ";
    while (!it.isEnd()) {
        std::cout << it.data() << " ";
        it.next();
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Imprime por consola un separador visual con un título centrado.
 * @param titulo Texto a mostrar como título del separador.
 */
void separador(const std::string &titulo) {
    std::cout << "=======================================================================================================================" << std::endl;
    std::cout << "----------------------------------------------- " << titulo << " -----------------------------------------------" << std::endl;
    std::cout << "=======================================================================================================================" << std::endl;
}

/**
 * @brief Función principal. Ejecuta las pruebas de ListaEnlazada<int> y del sistema MediExpress.
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Vector de cadenas con los argumentos de línea de comandos.
 * @return 0 si la ejecución finaliza correctamente.
 */
int main(int argc, const char *argv[]) {
    try {
        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba I" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;
        ListaEnlazada<int> lista;

        separador("Lista creada vacia");
        mostrarLista(lista);

        // Insertar al final valores de 101 a 200
        for (int i = 101; i <= 200; ++i) {
            lista.insertAtEnd(i);
        }
        separador("Insertados valores 101 a 200 al final");
        mostrarLista(lista);

        // Insertar al comienzo valores de 98 a 1 (decrecientes)
        for (int i = 98; i >= 1; --i) {
            lista.insertAtBiginning(i);
        }
        separador("Insertados valores 98 a 1 al comienzo");
        mostrarLista(lista);

        // Insertar 100 delante del 101
        auto it = lista.iterator();
        while(!it.isEnd() && it.data() != 101) {
            it.next();
        }
        if(!it.isEnd()) {
            lista.InsertBefore(it, 100);
        }
        separador("Insertado 100 delante de 101");
        mostrarLista(lista);

        // Insertar 99 detrás del 98
        it = lista.iterator();
        while(!it.isEnd() && it.data() != 98) {
            it.next();
        }
        if(!it.isEnd()) {
            lista.insertAfter(it, 99);
        }
        separador("Insertado 99 detras de 98");
        mostrarLista(lista);

        // Borrar los 10 primeros elementos
        for (int i = 0; i < 10; ++i) {
            lista.removeFirst();
        }
        // Borrar los 10 últimos elementos
        for (int i = 0; i < 10; ++i) {
            lista.removeLast();
        }
        separador("Borrados los 10 primeros y 10 ultimos elementos");
        mostrarLista(lista);

        // Borrar todos los múltiplos de 10
        it = lista.iterator();
        while(!it.isEnd()) {
            if(it.data() % 10 == 0) {
                lista.remove(it);
            } else {
                it.next();
            }
        }
        separador("Borrados los multiplos de 10");
        mostrarLista(lista);

        separador("Fin de la prueba de ListaEnlazada<int>");
        std::cout << "Todos los pasos se ejecutaron correctamente." << std::endl;

        std::cout << "=======================================================================================================================" << std::endl;
        std::cout << "----------------------------------------------- " << "Prueba II" << " -----------------------------------------------" << std::endl;
        std::cout << "=======================================================================================================================" << std::endl;

        separador("Labs Granada");

        MediExpress mediExpr("../data/pa_medicamentos.csv", "../data/laboratorios.csv");
        VDinamico<PaMedicamento*> noLab = mediExpr.getMedicamSinLab();
        std::cout << "Medicamentos sin laboratorio: " << noLab.len() << "\n";

        ListaEnlazada<Laboratorio*> granada = mediExpr.buscarLabCiudad("Granada");
        std::cout << "\nLaboratorios en Granada o provincia: " << granada.size() << "\n";
        for (auto it = granada.iterator(); !it.isEnd(); it.next()) {
            std::cout << "- " << *it.data() << "\n";
        }

        separador("Labs Jaen");

        ListaEnlazada<Laboratorio*> jaen = mediExpr.buscarLabCiudad("jaen");
        std::cout << "\nLaboratorios en Jaen o provincia: " << jaen.size() << "\n";

        separador("Labs Madrid, 10 primeros");

        ListaEnlazada<Laboratorio*> madrid = mediExpr.buscarLabCiudad("Madrid");
        std::cout << "\nLaboratorios en Madrid o provincia: " << madrid.size() << "\n";

        std::cout << "Primeros 10:\n";
        int mostrados = 0;
        for (auto it = madrid.iterator(); !it.isEnd() && mostrados < 10; it.next(), ++mostrados) {
            std::cout << (mostrados + 1) << ". " << *it.data() << "\n";
        }
        if (madrid.size() == 0) {
            std::cout << "(No hay resultados)\n";
        }

        separador("Labs sumistran Aceites");

        VDinamico<PaMedicamento*> aceites = mediExpr.buscarCompuesto("aceite");
        ListaEnlazada<const Laboratorio*> labsUnicos;

        for (unsigned int i = 0; i < aceites.len(); ++i) {
            const Laboratorio* lab = aceites[i]->getServidoPor();
            if (!lab) continue;

            bool yaEsta = false;
            for (auto itL = labsUnicos.iterator(); !itL.isEnd(); itL.next()) {
                if (itL.data() == lab) { yaEsta = true; break; }
            }
            if (!yaEsta) labsUnicos.insertAtEnd(lab);
        }

        std::cout << "\nLaboratorios que suministran 'ACEITES': " << labsUnicos.size() << "\n";
        int idx = 1;
        for (auto itL = labsUnicos.iterator(); !itL.isEnd(); itL.next()) {
            std::cout << idx++ << ". " << *itL.data() << "\n";
        }
        if (labsUnicos.size() == 0) std::cout << "(Ninguno)\n";

        separador("Asignar labs");
        ListaEnlazada<Laboratorio*> labsMadrid = mediExpr.buscarLabCiudad("Madrid");

        unsigned int objetivo = 152;
        unsigned int asignados = 0;

        auto itMad = labsMadrid.iterator();
        while (!itMad.isEnd() && asignados < objetivo) {
            VDinamico<PaMedicamento*> sinLabAhora = mediExpr.getMedicamSinLab();
            if (sinLabAhora.len() == 0) break;

            mediExpr.suministrarMed(*sinLabAhora[0], *itMad.data());

            ++asignados;
            itMad.next();
        }

        std::cout << "\nAsignacion dinamica a laboratorios de Madrid\n";
        std::cout << "  Objetivo: 152\n";
        std::cout << "  Finalmente asignados: " << asignados << "\n";
        if (asignados < 152) {
            std::cout << "  (Aviso) No se alcanzaron 152 asignaciones: faltan medicamentos sin proveedor o laboratorios en Madrid.\n";
        }

    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    return 0;
}
