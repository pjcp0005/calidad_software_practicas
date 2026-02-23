//
// Created by jmart on 23/09/2025.
//
#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <climits>

template<class T>
class VDinamico {
private:
    unsigned int m_tamaf;
    unsigned int m_tamal;
    T *v;

    //Se ocupa de redondear a la potencia de 2
    void roundToPowerOf2(unsigned int &t);
    //Se ocupa de coger memoria
    void allocateMemory();
    //Se ocupa de liberar memoria
    void freeMemory();

public:
    VDinamico();
    VDinamico(unsigned int tamalog, T &dato);
    VDinamico(const VDinamico<T> &orig);
    VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num);
    ~VDinamico();

    VDinamico<T> &operator=(const VDinamico<T> &arr);
    T &operator[](unsigned int index) const;

    void insert (const T &data, unsigned int pos=UINT_MAX);
    T remove (unsigned int index=UINT_MAX);
    unsigned int len() const;
    void sort();
    unsigned int binarySearch(const T &data);
};

#include "../src/VDinamico.tpp"
#endif //VDINAMICO_H