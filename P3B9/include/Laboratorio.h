/**
 * @file Laboratorio.h
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Declaración de la clase Laboratorio.
 * @version 0.1
 * @date 2025-10-08
 *
 * @copyright Copyright (c) 2026
 */

#ifndef LABORATORIO_H
#define LABORATORIO_H

#include <string>
#include <string_view>
#include <ostream>

/**
 * @class Laboratorio
 * @brief Representa un laboratorio farmacéutico con sus datos identificativos y de localización.
 */
class Laboratorio{
private:
    unsigned int m_id;          ///< Identificador único del laboratorio.
    std::string m_lab_name;     ///< Nombre del laboratorio.
    std::string m_address;      ///< Dirección del laboratorio.
    std::string m_postal_code;  ///< Código postal del laboratorio.
    std::string m_city;         ///< Ciudad donde está ubicado el laboratorio.

public:
    /**
     * @brief Constructor por defecto.
     * @post Inicializa todos los atributos a sus valores por defecto (0 y cadenas vacías).
     */
    Laboratorio();

    /**
     * @brief Constructor con parámetros.
     * @param id Identificador numérico del laboratorio.
     * @param nombre_lab Nombre del laboratorio.
     * @param direccion Dirección del laboratorio.
     * @param cod_postal Código postal del laboratorio.
     * @param localidad Ciudad donde está ubicado el laboratorio.
     */
    Laboratorio(int id,
                std::string_view nombre_lab,
                std::string_view direccion,
                std::string_view cod_postal,
                std::string_view localidad);

    /**
     * @brief Destructor por defecto.
     * @post No hay recursos dinámicos que liberar.
     */
    ~Laboratorio() = default;

    /**
     * @brief Operador de igualdad. Compara por identificador numérico.
     * @param lab Laboratorio con el que comparar.
     * @return true si ambos laboratorios tienen el mismo id; false en caso contrario.
     */
    friend bool operator==(const Laboratorio& lhs, const Laboratorio& rhs) {
        return lhs.m_id == rhs.m_id;
    }

    /**
     * @brief Sobrecarga del operador de salida. Imprime los datos del laboratorio.
     * @param os Flujo de salida.
     * @param l Laboratorio a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend std::ostream& operator<<(std::ostream& os, const Laboratorio& l) {
        os << "[id=" << l.getId()
           << "] " << l.getLabName()
           << " | " << l.getAddress()
           << " | " << l.getPostalCode()
           << " | " << l.getCity();
        return os;
    }

    /**
     * @brief Devuelve el identificador numérico del laboratorio.
     * @return Identificador numérico del laboratorio.
     */
    int getId() const;

    /**
     * @brief Devuelve el nombre del laboratorio.
     * @return Nombre del laboratorio.
     */
    std::string getLabName() const;

    /**
     * @brief Devuelve la dirección del laboratorio.
     * @return Dirección del laboratorio.
     */
    std::string getAddress() const;

    /**
     * @brief Devuelve el código postal del laboratorio.
     * @return Código postal del laboratorio.
     */
    std::string getPostalCode() const;

    /**
     * @brief Devuelve la ciudad del laboratorio.
     * @return Ciudad del laboratorio.
     */
    std::string getCity() const;

    /**
     * @brief Establece el identificador numérico del laboratorio.
     * @param id Nuevo identificador numérico.
     */
    void setId(int id);

    /**
     * @brief Establece el nombre del laboratorio.
     * @param nombre_lab Nuevo nombre del laboratorio.
     */
    void setLabName(std::string_view nombre_lab);

    /**
     * @brief Establece la dirección del laboratorio.
     * @param direccion Nueva dirección del laboratorio.
     */
    void setAddress(std::string_view direccion);

    /**
     * @brief Establece el código postal del laboratorio.
     * @param cod_postal Nuevo código postal del laboratorio.
     */
    void setPostalCode(std::string_view cod_postal);

    /**
     * @brief Establece la ciudad del laboratorio.
     * @param localidad Nueva ciudad del laboratorio.
     */
    void setCity(std::string_view localidad);
};

#endif // LABORATORIO_H
