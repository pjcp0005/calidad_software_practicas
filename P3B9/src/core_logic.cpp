/**
 * @file core_logic.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Implementación de la lógica principal del programa desacoplada del punto de entrada.
 * @version 0.1
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2026
 */

#include "../include/core_logic.h"

/**
 * @brief Imprime por consola los elementos de una ListaEnlazada<int>.
 * @param lista Lista enlazada de enteros a mostrar.
 */
static void mostrarLista(const ListaEnlazada<int> &lista) {
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
static void separador(const std::string &titulo) {
    std::cout << "=======================================================================================================================" << std::endl;
    std::cout << "----------------------------------------------- " << titulo << " -----------------------------------------------" << std::endl;
    std::cout << "=======================================================================================================================" << std::endl;
}

bool safe_read(unsigned int& value) {
    if (std::cin >> value) return true; // Lectura correcta
    if (std::cin.eof()) return false;   // EOF: terminar el programa
    std::cin.clear();                   // Limpiar el estado de error
    std::cin.ignore(10000, '\n');       // Descartar el resto de la línea
    return true;                        // Continuar el programa
}

/**
 * @brief Realiza las inserciones de la Prueba I sobre la lista de enteros.
 * @param lista Lista enlazada sobre la que operar.
 */
static void prueba_lista_inserciones(ListaEnlazada<int>& lista) {
    for (int i = 101; i <= 200; ++i) lista.insertAtEnd(i);
    separador("Insertados valores 101 a 200 al final");
    mostrarLista(lista);
    for (int i = 98; i >= 1; --i) lista.insertAtBiginning(i);
    separador("Insertados valores 98 a 1 al comienzo");
    mostrarLista(lista);
    auto it = lista.iterator();
    while(!it.isEnd() && it.data() != 101) it.next();
    if(!it.isEnd()) lista.InsertBefore(it, 100);
    separador("Insertado 100 delante de 101");
    mostrarLista(lista);
    it = lista.iterator();
    while(!it.isEnd() && it.data() != 98) it.next();
    if(!it.isEnd()) lista.insertAfter(it, 99);
    separador("Insertado 99 detras de 98");
    mostrarLista(lista);
}

/**
 * @brief Realiza los borrados de la Prueba I sobre la lista de enteros.
 * @param lista Lista enlazada sobre la que operar.
 */
static void prueba_lista_borrados(ListaEnlazada<int>& lista) {
    for (int i = 0; i < 10; ++i) lista.removeFirst();
    for (int i = 0; i < 10; ++i) lista.removeLast();
    separador("Borrados los 10 primeros y 10 ultimos elementos");
    mostrarLista(lista);
    auto it = lista.iterator();
    while(!it.isEnd()) {
        if(it.data() % 10 == 0) lista.remove(it);
        else it.next();
    }
    separador("Borrados los multiplos de 10");
    mostrarLista(lista);
}

/**
 * @brief Ejecuta la Prueba I: operaciones de inserción y borrado sobre ListaEnlazada<int>.
 */
static void prueba_lista() {
    separador("Prueba I");
    ListaEnlazada<int> lista;
    separador("Lista creada vacia");
    mostrarLista(lista);
    prueba_lista_inserciones(lista);
    prueba_lista_borrados(lista);
    separador("Fin de la prueba de ListaEnlazada<int>");
    std::cout << "Todos los pasos se ejecutaron correctamente." << std::endl;
}

/**
 * @brief Muestra los laboratorios en Granada y provincia.
 * @param me Sistema MediExpress sobre el que consultar.
 */
static void prueba_labs_granada(const MediExpress& me) {
    separador("Labs Granada");
    ListaEnlazada<Laboratorio*> granada = me.buscarLabCiudad("Granada");
    std::cout << "\nLaboratorios en Granada o provincia: " << granada.size() << "\n";
    for (auto it = granada.iterator(); !it.isEnd(); it.next()) {
        std::cout << "- " << *it.data() << "\n";
    }
}

/**
 * @brief Muestra los laboratorios en Jaén y provincia.
 * @param me Sistema MediExpress sobre el que consultar.
 */
static void prueba_labs_jaen(const MediExpress& me) {
    separador("Labs Jaen");
    ListaEnlazada<Laboratorio*> jaen = me.buscarLabCiudad("jaen");
    std::cout << "\nLaboratorios en Jaen o provincia: " << jaen.size() << "\n";
}

/**
 * @brief Muestra los 10 primeros laboratorios en Madrid y provincia.
 * @param me Sistema MediExpress sobre el que consultar.
 */
static void prueba_labs_madrid(const MediExpress& me) {
    separador("Labs Madrid, 10 primeros");
    ListaEnlazada<Laboratorio*> madrid = me.buscarLabCiudad("Madrid");
    std::cout << "\nLaboratorios en Madrid o provincia: " << madrid.size() << "\n";
    std::cout << "Primeros 10:\n";
    int mostrados = 0;
    for (auto it = madrid.iterator(); !it.isEnd() && mostrados < 10; it.next(), ++mostrados) {
        std::cout << (mostrados + 1) << ". " << *it.data() << "\n";
    }
    if (madrid.size() == 0) std::cout << "(No hay resultados)\n";
}

/**
 * @brief Muestra los laboratorios únicos que suministran medicamentos con "aceite".
 * @param me Sistema MediExpress sobre el que consultar.
 */
static void prueba_labs_aceites(const MediExpress& me) {
    separador("Labs sumistran Aceites");
    VDinamico<PaMedicamento*> aceites = me.buscarCompuesto("aceite");
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
        std::cout << idx << ". " << *itL.data() << "\n";
        ++idx;
    }
    if (labsUnicos.size() == 0) std::cout << "(Ninguno)\n";
}

/**
 * @brief Asigna dinámicamente medicamentos sin proveedor a laboratorios de Madrid.
 * @param me Sistema MediExpress sobre el que operar.
 */
static void prueba_asignar_labs(MediExpress& me) {
    separador("Asignar labs");
    ListaEnlazada<Laboratorio*> labsMadrid = me.buscarLabCiudad("Madrid");
    const unsigned int objetivo = 152;
    unsigned int asignados = 0;
    auto itMad = labsMadrid.iterator();
    while (!itMad.isEnd() && asignados < objetivo) {
        VDinamico<PaMedicamento*> sinLabAhora = me.getMedicamSinLab();
        if (sinLabAhora.len() == 0) break;
        me.suministrarMed(*sinLabAhora[0], *itMad.data());
        ++asignados;
        itMad.next();
    }
    std::cout << "\nAsignacion dinamica a laboratorios de Madrid\n";
    std::cout << "  Objetivo: 152\n";
    std::cout << "  Finalmente asignados: " << asignados << "\n";
    if (asignados < 152) {
        std::cout << "  (Aviso) No se alcanzaron 152 asignaciones: faltan medicamentos sin proveedor o laboratorios en Madrid.\n";
    }
}

/**
 * @brief Ejecuta la Prueba II: operaciones sobre el sistema MediExpress.
 * @param medsPath Ruta al CSV de medicamentos.
 * @param labsPath Ruta al CSV de laboratorios.
 */
static void prueba_mediexpress(const std::string& medsPath, const std::string& labsPath) {
    separador("Prueba II");
    MediExpress mediExpr(medsPath, labsPath);
    VDinamico<PaMedicamento*> noLab = mediExpr.getMedicamSinLab();
    std::cout << "Medicamentos sin laboratorio: " << noLab.len() << "\n";
    prueba_labs_granada(mediExpr);
    prueba_labs_jaen(mediExpr);
    prueba_labs_madrid(mediExpr);
    prueba_labs_aceites(mediExpr);
    prueba_asignar_labs(mediExpr);
}

void run_simulation(const std::string& medsPath, const std::string& labsPath) {
    try {
        prueba_lista();
        prueba_mediexpress(medsPath, labsPath);
    } catch (const std::out_of_range &e){
        std::cerr << e.what() << '\n';
    } catch (const std::invalid_argument &e){
        std::cerr << e.what() << '\n';
    }
}
