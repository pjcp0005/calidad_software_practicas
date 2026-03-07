/**
 * @file VDinamico.h
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Declaración de la clase plantilla VDinamico.
 * @version 0.1
 * @date 2025-09-23
 *
 * @copyright Copyright (c) 2026
 */
#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <climits>

/**
 * @class VDinamico
 * @brief Vector dinámico genérico con redimensionamiento automático basado en potencias de 2.
 * Gestiona memoria dinámica propia: crece al doble cuando se llena y se reduce
 * a la mitad cuando el tamaño lógico cae a un tercio del físico.
 * @tparam T Tipo de los elementos almacenados.
 */
template<class T>
class VDinamico {
private:
    unsigned int m_tamaf; ///< Tamaño físico del vector (capacidad total reservada, siempre potencia de 2).
    unsigned int m_tamal; ///< Tamaño lógico del vector (número de elementos almacenados actualmente).
    T *v;                 ///< Puntero al array dinámico de elementos.

    /**
     * @brief Redondea un valor al entero que es potencia de 2 inmediatamente superior o igual.
     * @param t Valor a redondear (se modifica por referencia).
     * @post t queda como la potencia de 2 más cercana por arriba; si ya era potencia de 2, no cambia.
     */
    void roundToPowerOf2(unsigned int &t);

    /**
     * @brief Duplica la capacidad física del vector copiando los elementos existentes.
     * @post m_tamaf se dobla (redondeado a potencia de 2) y se reserva nueva memoria.
     */
    void allocateMemory();

    /**
     * @brief Reduce la capacidad física del vector a la mitad si el tamaño lógico es <= 1/3 del físico.
     * @post Si la condición se cumple, m_tamaf se reduce y se libera la memoria sobrante.
     */
    void freeMemory();

public:
    /**
     * @brief Constructor por defecto.
     * @post Crea un vector vacío con capacidad física inicial de 1.
     */
    VDinamico();

    /**
     * @brief Constructor con tamaño y valor inicial.
     * @param tamalog Número de elementos iniciales.
     * @param dato Valor con el que se inicializan todas las posiciones.
     * @post Crea un vector de tamaño lógico tamalog con todas las posiciones iguales a dato.
     */
    VDinamico(unsigned int tamalog, T &dato);

    /**
     * @brief Constructor de copia.
     * @param orig Vector dinámico a copiar.
     * @post El nuevo vector es una copia profunda de orig.
     */
    VDinamico(const VDinamico<T> &orig);

    /**
     * @brief Constructor de copia de un rango de elementos.
     * @param origen Vector dinámico fuente.
     * @param inicio Índice del primer elemento a copiar.
     * @param num Número de elementos a copiar.
     * @throws std::out_of_range Si inicio >= tamaño lógico de origen.
     * @throws std::out_of_range Si inicio + num > tamaño lógico de origen.
     */
    VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num);

    /**
     * @brief Destructor.
     * @post Libera la memoria dinámica reservada.
     */
    ~VDinamico();

    /**
     * @brief Operador de asignación por copia.
     * @param arr Vector dinámico a asignar.
     * @return Referencia al propio objeto tras la asignación.
     * @post El vector actual es una copia profunda de arr.
     */
    VDinamico<T> &operator=(const VDinamico<T> &arr);

    /**
     * @brief Operador de acceso por índice.
     * @param index Índice del elemento a acceder.
     * @return Referencia al elemento en la posición index.
     * @throws std::out_of_range Si index >= tamaño lógico.
     */
    T &operator[](unsigned int index) const;

    /**
     * @brief Inserta un elemento en una posición dada (por defecto, al final).
     * @param data Dato a insertar.
     * @param pos Posición de inserción. Si es UINT_MAX, se inserta al final.
     * @throws std::out_of_range Si pos > tamaño lógico.
     * @post El tamaño lógico aumenta en 1. Si el vector estaba lleno, se redimensiona.
     */
    void insert (const T &data, unsigned int pos=UINT_MAX);

    /**
     * @brief Elimina el elemento en una posición dada (por defecto, el último).
     * @param index Posición del elemento a eliminar. Si es UINT_MAX, se elimina el último.
     * @return El elemento eliminado.
     * @throws std::out_of_range Si el vector está vacío o index >= tamaño lógico.
     * @post El tamaño lógico disminuye en 1. Si procede, se reduce la memoria.
     */
    T remove (unsigned int index=UINT_MAX);

    /**
     * @brief Devuelve el número de elementos almacenados (tamaño lógico).
     * @return Tamaño lógico del vector.
     */
    unsigned int len() const;

    /**
     * @brief Ordena los elementos del vector usando std::sort.
     * @pre El tipo T debe soportar el operador <.
     * @post Los elementos quedan ordenados de menor a mayor.
     */
    void sort();

    /**
     * @brief Busca un elemento mediante búsqueda binaria.
     * @pre El vector debe estar ordenado de menor a mayor.
     * @param data Elemento a buscar.
     * @return Índice del elemento si se encuentra; UINT_MAX si no existe.
     */
    unsigned int binarySearch(const T &data);
};

#include "../src/VDinamico.tpp"
#endif //VDINAMICO_H
