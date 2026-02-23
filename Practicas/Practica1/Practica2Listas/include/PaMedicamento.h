//
// Created by jmart on 25/09/2025.
//

#ifndef PAMEDICAMENTO_H
#define PAMEDICAMENTO_H

#include <string>

class Laboratorio;
class PaMedicamento{
private:
    int m_id_num;
    std::string m_id_alpha;
    std::string m_name;
    Laboratorio *m_servidoPor{nullptr};

public:
    PaMedicamento();
    PaMedicamento(int id_num, std::string id_alpha, std::string name);
    /**
     * Prefuntar si se podria usar "~PaMedicamento() = default;" para que el contructor lo haga automaticamente
     * porque como no hay nada dinamico nos podriamos ahorar el hacerlo manual
     */
    ~PaMedicamento();

    //Operators
    //Al poner al final el const se promete que esa funcion no modificara atributos
    bool operator==(const PaMedicamento &object) const;
    bool operator<(const PaMedicamento &object) const;
    
    //Getters
    int getIdNum() const;
    std::string getIdAlpha() const;
    std::string getName() const;
    Laboratorio *getServidoPor() const;

    //Setters
    void setIdNum(int id_num);
    void setIdAlpha(std::string id_alpha);
    void setName(std::string name);
    void setServidoPor(Laboratorio *lab);
};

#endif //PAMEDICAMENTO_H
