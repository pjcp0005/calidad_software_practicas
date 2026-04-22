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
                const std::string &nombre_lab,
                const std::string &direccion,
                const std::string &cod_postal,
                const std::string &localidad);

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
    bool operator==(Laboratorio lab) const;

    /**
     * @brief Sobrecarga del operador de salida. Imprime los datos del laboratorio.
     * @param os Flujo de salida.
     * @param l Laboratorio a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend std::ostream& operator<<(std::ostream& os, const Laboratorio& l);

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
    void setLabName(const std::string &nombre_lab);

    /**
     * @brief Establece la dirección del laboratorio.
     * @param direccion Nueva dirección del laboratorio.
     */
    void setAddress(const std::string &direccion);

    /**
     * @brief Establece el código postal del laboratorio.
     * @param cod_postal Nuevo código postal del laboratorio.
     */
    void setPostalCode(const std::string &cod_postal);

    /**
     * @brief Establece la ciudad del laboratorio.
     * @param localidad Nueva ciudad del laboratorio.
     */
    void setCity(const std::string &localidad);
};

#endif // LABORATORIO_H
