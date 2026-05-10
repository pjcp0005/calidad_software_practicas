/**
 * @file MediExpress.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Implementación de la clase MediExpress.
 * @version 0.1
 * @date 2025-10-08
 *
 * @copyright Copyright (c) 2026
 */
#include "../include/MediExpress.h"
#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>

/**
 * Metodos privados
 */

/**
 * @brief Parsea una fila CSV de medicamentos y devuelve un PaMedicamento.
 * @param row Fila en formato "id_num;id_alpha;nombre".
 * @return PaMedicamento construido con los datos de la fila.
 */
static PaMedicamento parseMedRow(const std::string& row) {
    std::stringstream columns(row);
    std::string idNum;
    std::string idAlpha;
    std::string name;
    std::getline(columns, idNum, ';');
    std::getline(columns, idAlpha, ';');
    std::getline(columns, name, ';');
    return PaMedicamento(std::stoi(idNum), idAlpha, name);
}

/**
 * @brief Normaliza los saltos de línea de una cadena sustituyendo '\r' por '\n'.
 * @param content Cadena a normalizar (modificada en el lugar).
 */
static void normalizeLineEndings(std::string& content) {
    for (char& c : content) {
        if (c == '\r') c = '\n';
    }
}

/**
 * @brief Parsea una fila CSV de laboratorios y devuelve un Laboratorio.
 * @param row Fila en formato "id;nombre;dirección;cp;ciudad".
 * @return Laboratorio construido con los datos de la fila.
 */
static Laboratorio parseLabRow(const std::string& row) {
    std::stringstream columns(row);
    std::string idStr;
    std::string nombre;
    std::string direccion;
    std::string cod_postal;
    std::string localidad;
    std::getline(columns, idStr,      ';');
    std::getline(columns, nombre,     ';');
    std::getline(columns, direccion,  ';');
    std::getline(columns, cod_postal, ';');
    std::getline(columns, localidad);
    return Laboratorio(std::stoi(idStr), nombre, direccion, cod_postal, localidad);
}

VDinamico<PaMedicamento> MediExpress::loadMedicinesFromCsv(const std::string &csvPath) const{
    std::ifstream is(csvPath);
    VDinamico<PaMedicamento> aux;
    if (!is.good()) return aux;
    std::string row;
    while (std::getline(is, row)) {
        if (!row.empty()) aux.insert(parseMedRow(row));
    }
    return aux;
}

ListaEnlazada<Laboratorio> MediExpress::loadLabFromCsv(const std::string &csvPath) const{
    ListaEnlazada<Laboratorio> aux;
    std::ifstream is(csvPath, std::ios::binary);
    if (!is.is_open()) {
        std::cerr << "[ERROR] No puedo abrir: " << csvPath << "\n";
        return aux;
    }
    std::string content((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
    normalizeLineEndings(content);
    std::stringstream ss(content);
    std::string row;
    while (std::getline(ss, row, '\n')) {
        if (!row.empty() && row[0] != ';') aux.insertAtEnd(parseLabRow(row));
    }
    return aux;
}

void MediExpress::autoLinkMedications() const{
    const unsigned int siz = m_med.len();
    unsigned int labIdx = 0;
    for (auto it = m_lab.iterator(); !it.isEnd() && (labIdx * 2) < siz; it.next(), ++labIdx) {
        for (unsigned int pair = 0; pair < 2 && (labIdx * 2 + pair) < siz; ++pair) {
            m_med[labIdx * 2 + pair].setServidoPor(&it.data());
        }
    }
};

/**
 * Constructores
 */

MediExpress::MediExpress() = default;

MediExpress::MediExpress(const std::string &csvPathVD, const std::string &csvPathLE){
    m_med = loadMedicinesFromCsv(csvPathVD);
    m_lab = loadLabFromCsv(csvPathLE);
    autoLinkMedications();
}

MediExpress::~MediExpress() = default;

/**
 * Metodos
 */

void MediExpress::suministrarMed(const PaMedicamento& med, Laboratorio& lab) const{
    bool labExists = false;

    for (auto it = m_lab.iterator(); !it.isEnd(); it.next()) {
        if (it.data() == lab) {
            labExists = true;
            break;
        }
    }
    if (labExists){
        //Buscar el medicamento y enlazar el primero que coincida
        const unsigned int n = m_med.len();
        for (unsigned int i = 0; i < n; ++i) {
            if (m_med[i] == med) {
                m_med[i].setServidoPor(&lab);
                break;
        }
        }
    }
}

Laboratorio* MediExpress::buscarLab(std::string_view labName){
    for(auto it = m_lab.iterator(); !it.isEnd(); it.next()){
        if(it.data().getLabName()==labName){
            return &it.data();
        }
    }

    return nullptr;
};

ListaEnlazada<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &cityName) const{
    ListaEnlazada<Laboratorio*> aux;

    for(auto it = m_lab.iterator(); !it.isEnd(); it.next()){
        if(utils::iContains(it.data().getCity(),cityName)){
            aux.insertAtEnd(&it.data());
        }
    }

    return aux;
}

VDinamico<PaMedicamento*> MediExpress::buscarCompuesto(const std::string &compoundName) const{
    VDinamico<PaMedicamento*> aux;

    unsigned int siz = m_med.len();
    for(unsigned int i = 0; i < siz;++i){
        if (utils::iContains(m_med[i].getName(), compoundName)) {
            aux.insert(&m_med[i]);
        }
    }

    return aux;
};

VDinamico<PaMedicamento*> MediExpress::getMedicamSinLab() const{
    VDinamico<PaMedicamento*> aux;

    unsigned int siz = m_med.len();
    for(unsigned int i = 0; i < siz ; ++i){
        if(m_med[i].getServidoPor() == nullptr){
            aux.insert(&m_med[i]);
        }
    }

    return aux;
};