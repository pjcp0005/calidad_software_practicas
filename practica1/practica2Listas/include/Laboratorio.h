//
// Created by jmart on 08/10/2025.
//

#ifndef LABORATORIO_H
#define LABORATORIO_H

#include <string>
#include <ostream>

class Laboratorio{
private:
    unsigned int m_id;
    std::string m_lab_name;
    std::string m_address;
    std::string m_postal_code;
    std::string m_city;

public:
    // Constructores
    Laboratorio();
    Laboratorio(int id,
                const std::string &nombre_lab,
                const std::string &direccion,
                const std::string &cod_postal,
                const std::string &localidad);

    // Destructor
    ~Laboratorio() = default;  // no hay recursos dinámicos, por ende se puede usar el default

    bool operator==(Laboratorio lab) const;
    friend std::ostream& operator<<(std::ostream& os, const Laboratorio& l);

    // Getters
    int getId() const;
    std::string getLabName() const;
    std::string getAddress() const;
    std::string getPostalCode() const;
    std::string getCity() const;

    // Setters
    void setId(int id);
    void setLabName(const std::string &nombre_lab);
    void setAddress(const std::string &direccion);
    void setPostalCode(const std::string &cod_postal);
    void setCity(const std::string &localidad);
};

#endif // LABORATORIO_H
