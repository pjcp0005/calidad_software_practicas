/**
 * @file PaMedicamento.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Implementación de la clase PaMedicamento.
 * @version 0.1
 * @date 2025-10-08
 *
 * @copyright Copyright (c) 2026
 */
#include "../include/PaMedicamento.h"
#include "../include/Laboratorio.h"

/**
 * Constructores
 */
/**
 * @brief Constructor por defecto
 * @post Constructor por defecto que inicializa los atributos a valores por defecto
 */
PaMedicamento::PaMedicamento(){
    m_id_num = 0;
    m_id_alpha = "";
    m_name = "";
};

/**
 * @brief Constructor con parametros
 * @param idNum Identificador numerico del medicamento
 * @param idAlpha Identificador alfanumerico del medicamento
 * @param name Nombre del medicamento
 * @post Constructor con parametros que inicializa los atributos con los valores pasados por parametro
 */
PaMedicamento::PaMedicamento(int idNum, std::string_view idAlpha, std::string_view name){
    m_id_num = idNum;
    m_id_alpha = idAlpha;
    m_name = name;
};

/**
 * @brief Destructor
 * @post Destructor que libera la memoria ocupada por los atributos
 */
PaMedicamento::~PaMedicamento(){
    m_id_num = 0;
    m_id_alpha.clear();
    m_name.clear();
    m_servidoPor = nullptr;
};

/**
 * Getters
 */
/**
 * @brief Getter del identificador numerico
 * @return Devuelve el identificador numerico del medicamento
 */
int PaMedicamento::getIdNum() const{
    return m_id_num;
};

/**
 * @brief Getter del identificador alfanumerico
 * @return Devuelve el identificador alfanumerico del medicamento
 */
std::string PaMedicamento::getIdAlpha() const{
    return m_id_alpha;
};

/**
 * @brief Getter del nombre del medicamento
 * @return Devuelve el nombre del medicamento
 */
std::string PaMedicamento::getName() const{
    return m_name;
};

Laboratorio *PaMedicamento::getServidoPor() const{
    return m_servidoPor;
}

/**
 * Setters
 */
/**
 * @brief Setter del identificador numerico
 * @param num Nuevo identificador numerico del medicamento
 * @post Actualiza el identificador numerico del medicamento
 */
void PaMedicamento::setIdNum(int num){
    m_id_num = num;
};

/**
 * @brief Setter del identificador alfanumerico
 * @param alphanumeric Nuevo identificador alfanumerico del medicamento
 * @post Actualiza el identificador alfanumerico del medicamento
 */
void PaMedicamento::setIdAlpha(std::string_view alphanumeric){
    m_id_alpha = alphanumeric;
};

/**
 * @brief Setter del nombre del medicamento
 * @param name Nuevo nombre del medicamento
 * @post Actualiza el nombre del medicamento
 */
void PaMedicamento::setName(std::string_view name){
    m_name = name;
};

void PaMedicamento::setServidoPor(Laboratorio *lab){
    m_servidoPor = lab;
}
