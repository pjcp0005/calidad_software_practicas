//
// Created by jmart on 08/10/2025.
//
#include "../include/MediExpress.h"
#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>

/**
 * Metodos privados
 */

VDinamico<PaMedicamento> MediExpress::loadMedicinesFromCsv(const std::string &csvPath){

    std::ifstream is;
    std::stringstream columns;
    std::string row;
    int count = 0;
    std::string idNum = "";
    std::string idAlpha = "";
    std::string name = "";

    VDinamico<PaMedicamento> aux;

    is.open(csvPath); // carpeta de proyecto
    if (is.good()){

        clock_t t_ini = clock();

        while (getline(is, row)){

            // ¿Se ha leído una nueva fila?
            if (row != ""){

                columns.str(row);

                // formato de fila: id_number;id_alpha;nombre;

                getline(columns, idNum, ';'); // leemos caracteres hasta encontrar y omitir ';'
                getline(columns, idAlpha, ';');
                getline(columns, name, ';');

                row = "";
                columns.clear();

                PaMedicamento med(std::stoi(idNum), idAlpha, name);
                aux.insert(med);
            }
        }

        is.close();

    } else {
        
    }

    return aux;
};

ListaEnlazada<Laboratorio> MediExpress::loadLabFromCsv(const std::string &csvPath){
    ListaEnlazada<Laboratorio> aux;

    std::ifstream is(csvPath, std::ios::binary);
    if (!is.is_open()) {
        std::cerr << "[ERROR] No puedo abrir: " << csvPath << "\n";
        return aux;
    }

    //Leer todo el archivo a memoria
    std::string content((std::istreambuf_iterator<char>(is)),
                         std::istreambuf_iterator<char>());

    //Normalizar finales de línea: \r\n -> \n y \r -> \n
    for (char &c : content) {
        if (c == '\r') c = '\n';
    }

    //Parsear línea a línea
    std::stringstream ss(content);
    std::string row;
    while (std::getline(ss, row, '\n')) {
        if (row.empty()) continue;

        std::stringstream columns(row);
        std::string idStr, nombre, direccion, cod_postal, localidad;

        std::getline(columns, idStr,      ';');
        std::getline(columns, nombre,     ';');
        std::getline(columns, direccion,  ';');
        std::getline(columns, cod_postal, ';');
        std::getline(columns, localidad);

        if (idStr.empty()) continue;

        Laboratorio lab(std::stoi(idStr), nombre, direccion, cod_postal, localidad);
        aux.insertAtEnd(lab);
    }

    return aux;
};

void MediExpress::autoLinkMedications(){
    unsigned int index  = 0;
    const unsigned int siz = m_med.len();

    for (auto it = m_lab.iterator(); !it.isEnd() && index < siz; it.next()) {
        for (int pairIndex = 0; pairIndex < 2 && index < siz; ++pairIndex, ++index) {
            m_med[index].setServidoPor(&it.data());
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

void MediExpress::suministrarMed(PaMedicamento& med, Laboratorio& lab){
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

Laboratorio* MediExpress::buscarLab(const std::string &labName){
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
    for(int i = 0; i < siz;++i){
        if (utils::iContains(m_med[i].getName(), compoundName)) {
            aux.insert(&m_med[i]);
        }
    }

    return aux;
};

VDinamico<PaMedicamento*> MediExpress::getMedicamSinLab() const{
    VDinamico<PaMedicamento*> aux;

    unsigned int siz = m_med.len();
    for(int i = 0; i < siz ; ++i){
        if(m_med[i].getServidoPor() == nullptr){
            aux.insert(&m_med[i]);
        }
    }

    return aux;
};