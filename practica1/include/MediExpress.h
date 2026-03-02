//
// Created by jmart on 08/10/2025.
//
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

class MediExpress{
    private:
        VDinamico<PaMedicamento> m_med;
        ListaEnlazada<Laboratorio> m_lab;

        VDinamico<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath);
        ListaEnlazada<Laboratorio> loadLabFromCsv(const std::string &csvPath);
        void autoLinkMedications();

    public:
        MediExpress();
        MediExpress(const std::string &csvPathVD,const std::string &csvPathLE);
        ~MediExpress();

        void suministrarMed(PaMedicamento &med, Laboratorio &lab);
        Laboratorio* buscarLab(const std::string &labName);
        ListaEnlazada<Laboratorio*> buscarLabCiudad(const std::string &cityName) const;
        VDinamico<PaMedicamento*> buscarCompuesto(const std::string &compoundName) const;
        VDinamico<PaMedicamento*> getMedicamSinLab() const;
};

#endif //MEDIEXPRESS_H
