/**
 * @file Laboratorio.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Implementación de la clase Laboratorio.
 * @version 0.1
 * @date 2025-10-08
 *
 * @copyright Copyright (c) 2026
 */
#include "../include/Laboratorio.h"

/**
 * Constructores
 */
Laboratorio::Laboratorio(){
    m_id = 0;
    m_lab_name = "";
    m_address = "";
    m_postal_code = "";
    m_city = "";
};

Laboratorio::Laboratorio(int id, const std::string &nombre_lab, const std::string &direccion, const std::string &cod_postal, const std::string &localidad) {
    m_id = id;
    m_lab_name = nombre_lab;
    m_address = direccion;
    m_postal_code = cod_postal;
    m_city = localidad;
}

bool Laboratorio::operator==(Laboratorio lab) const{
    if(static_cast<int>(m_id) == lab.getId()){
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Laboratorio& l) {
    os << "[id=" << l.getId()
       << "] " << l.getLabName()
       << " | " << l.getAddress()
       << " | " << l.getPostalCode()
       << " | " << l.getCity();
    return os;
}

/**
 * Getters
 */
int Laboratorio::getId() const {
    return m_id;
}

std::string Laboratorio::getLabName() const {
    return m_lab_name;
}

std::string Laboratorio::getAddress() const {
    return m_address;
}

std::string Laboratorio::getPostalCode() const {
    return m_postal_code;
}

std::string Laboratorio::getCity() const {
    return m_city;
}

/**
 * Setters
 */
void Laboratorio::setId(int id) {
    m_id = id;
}

void Laboratorio::setLabName(const std::string &nombre_lab) {
    m_lab_name = nombre_lab;
}

void Laboratorio::setAddress(const std::string &direccion) {
    m_address = direccion;
}

void Laboratorio::setPostalCode(const std::string &cod_postal) {
    m_postal_code = cod_postal;
}

void Laboratorio::setCity(const std::string &localidad) {
    m_city = localidad;
}