/**
 * @file PaMedicamento.h
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Declaración de la clase PaMedicamento.
 * @version 0.1
 * @date 2025-09-25
 *
 * @copyright Copyright (c) 2026
 */

#ifndef PAMEDICAMENTO_H
#define PAMEDICAMENTO_H

#include <string>

class Laboratorio;

/**
 * @class PaMedicamento
 * @brief Representa un medicamento del padrón de medicamentos.
 * Almacena los identificadores, el nombre del medicamento y una referencia
 * al laboratorio que lo suministra.
 */
class PaMedicamento{
private:
    int m_id_num;                    ///< Identificador numérico del medicamento.
    std::string m_id_alpha;          ///< Identificador alfanumérico del medicamento.
    std::string m_name;              ///< Nombre del medicamento.
    Laboratorio *m_servidoPor{nullptr}; ///< Puntero al laboratorio que suministra el medicamento (nullptr si no tiene).

public:
    /**
     * @brief Constructor por defecto.
     * @post Inicializa todos los atributos a sus valores por defecto (0, cadenas vacías, puntero nulo).
     */
    PaMedicamento();

    /**
     * @brief Constructor con parámetros.
     * @param id_num Identificador numérico del medicamento.
     * @param id_alpha Identificador alfanumérico del medicamento.
     * @param name Nombre del medicamento.
     */
    PaMedicamento(int id_num, std::string id_alpha, std::string name);

    /**
     * @brief Destructor.
     * @post Limpia los atributos y establece el puntero a nullptr.
     */
    ~PaMedicamento();

    /**
     * @brief Operador de igualdad. Compara por identificador numérico.
     * @param object Objeto PaMedicamento con el que comparar.
     * @return true si ambos medicamentos tienen el mismo id numérico; false en caso contrario.
     */
    bool operator==(const PaMedicamento &object) const;

    /**
     * @brief Operador menor que. Compara por identificador numérico.
     * @param object Objeto PaMedicamento con el que comparar.
     * @return true si el id numérico de este objeto es menor que el del parámetro.
     */
    bool operator<(const PaMedicamento &object) const;

    /**
     * @brief Devuelve el identificador numérico del medicamento.
     * @return Identificador numérico.
     */
    int getIdNum() const;

    /**
     * @brief Devuelve el identificador alfanumérico del medicamento.
     * @return Identificador alfanumérico.
     */
    std::string getIdAlpha() const;

    /**
     * @brief Devuelve el nombre del medicamento.
     * @return Nombre del medicamento.
     */
    std::string getName() const;

    /**
     * @brief Devuelve el puntero al laboratorio que suministra el medicamento.
     * @return Puntero a Laboratorio, o nullptr si no tiene laboratorio asignado.
     */
    Laboratorio *getServidoPor() const;

    /**
     * @brief Establece el identificador numérico del medicamento.
     * @param id_num Nuevo identificador numérico.
     */
    void setIdNum(int id_num);

    /**
     * @brief Establece el identificador alfanumérico del medicamento.
     * @param id_alpha Nuevo identificador alfanumérico.
     */
    void setIdAlpha(std::string id_alpha);

    /**
     * @brief Establece el nombre del medicamento.
     * @param name Nuevo nombre del medicamento.
     */
    void setName(std::string name);

    /**
     * @brief Establece el laboratorio que suministra el medicamento.
     * @param lab Puntero al laboratorio proveedor (puede ser nullptr para desasignar).
     */
    void setServidoPor(Laboratorio *lab);
};

#endif //PAMEDICAMENTO_H
