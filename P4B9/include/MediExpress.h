/**
 * @file MediExpress.h
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Declaración de la clase MediExpress.
 * @version 0.1
 * @date 2025-10-08
 *
 * @copyright Copyright (c) 2026
 */
#include "../include/VDinamico.h"
#include "../include/ListaEnlazada.h"
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"

#ifndef MEDIEXPRESS_H
#define MEDIEXPRESS_H

/**
 * @class MediExpress
 * @brief Clase principal del sistema de gestión de medicamentos y laboratorios.
 * Gestiona la carga, enlace y consulta de medicamentos (PaMedicamento) y
 * laboratorios (Laboratorio) a partir de ficheros CSV.
 */
class MediExpress{
    private:
        VDinamico<PaMedicamento> m_med; ///< Vector dinámico con todos los medicamentos cargados.
        ListaEnlazada<Laboratorio> m_lab; ///< Lista enlazada con todos los laboratorios cargados.

        /**
         * @brief Carga medicamentos desde un fichero CSV.
         * @param csvPath Ruta al fichero CSV con los datos de medicamentos (formato: id_num;id_alpha;nombre).
         * @return VDinamico con todos los medicamentos leídos del fichero.
         */
        VDinamico<PaMedicamento> loadMedicinesFromCsv(const std::string &csvPath) const;

        /**
         * @brief Carga laboratorios desde un fichero CSV.
         * @param csvPath Ruta al fichero CSV con los datos de laboratorios (formato: id;nombre;dirección;cp;ciudad).
         * @return ListaEnlazada con todos los laboratorios leídos del fichero.
         */
        ListaEnlazada<Laboratorio> loadLabFromCsv(const std::string &csvPath) const;

        /**
         * @brief Enlaza automáticamente medicamentos con laboratorios.
         * @post Asigna a cada laboratorio 2 medicamentos consecutivos del vector, por orden de carga.
         */
        void autoLinkMedications() const;

    public:
        /**
         * @brief Constructor por defecto.
         */
        MediExpress();

        /**
         * @brief Constructor con rutas a los ficheros CSV.
         * @param csvPathVD Ruta al CSV de medicamentos.
         * @param csvPathLE Ruta al CSV de laboratorios.
         * @post Carga los datos de ambos ficheros y ejecuta el enlace automático.
         */
        MediExpress(const std::string &csvPathVD,const std::string &csvPathLE);

        /**
         * @brief Destructor.
         */
        ~MediExpress();

        /**
         * @brief Asigna un laboratorio como proveedor de un medicamento.
         * @param med Medicamento al que se le asigna el laboratorio.
         * @param lab Laboratorio que suministrará el medicamento.
         * @post Si el laboratorio existe en el sistema, se enlaza con el primer medicamento coincidente sin modificar el resto.
         */
        void suministrarMed(const PaMedicamento &med, Laboratorio &lab) const;

        /**
         * @brief Busca un laboratorio por nombre exacto.
         * @param labName Nombre exacto del laboratorio a buscar.
         * @return Puntero al Laboratorio encontrado, o nullptr si no existe ninguno con ese nombre.
         */
        Laboratorio* buscarLab(std::string_view labName);

        /**
         * @brief Busca laboratorios cuya ciudad contenga el texto dado (sin distinción de mayúsculas).
         * @param cityName Texto a buscar en el campo ciudad de cada laboratorio.
         * @return ListaEnlazada de punteros a los laboratorios cuya ciudad contiene el texto.
         */
        ListaEnlazada<Laboratorio*> buscarLabCiudad(const std::string &cityName) const;

        /**
         * @brief Busca medicamentos cuyo nombre contenga el compuesto dado (sin distinción de mayúsculas).
         * @param compoundName Nombre o parte del compuesto a buscar en el nombre del medicamento.
         * @return VDinamico de punteros a los medicamentos coincidentes.
         */
        VDinamico<PaMedicamento*> buscarCompuesto(const std::string &compoundName) const;

        /**
         * @brief Obtiene los medicamentos que no tienen laboratorio asignado.
         * @return VDinamico de punteros a los medicamentos cuyo proveedor es nullptr.
         */
        VDinamico<PaMedicamento*> getMedicamSinLab() const;
};

#endif //MEDIEXPRESS_H
