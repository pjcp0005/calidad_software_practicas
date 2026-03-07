/**
 * @file ListaEnlazada.h
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Declaración de la clase plantilla ListaEnlazada.
 * @version 0.1
 * @date 2025-10-08
 *
 * @copyright Copyright (c) 2026
 */

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <stdexcept>
#include <string>

/**
 * @class ListaEnlazada
 * @brief Lista enlazada simple genérica con iterador propio.
 * Gestiona nodos dinámicos encadenados. Ofrece inserción y eliminación
 * en cabeza, cola y posición arbitraria mediante iterador.
 * @tparam T Tipo de los elementos almacenados.
 */
template<class T>
class ListaEnlazada {
private:
    /**
     * @class Node
     * @brief Nodo interno de la lista enlazada.
     */
    class Node {
    public:
        T m_data;    ///< Dato almacenado en el nodo.
        Node *next;  ///< Puntero al siguiente nodo (nullptr si es el último).

        /**
         * @brief Constructor del nodo.
         * @param aData Dato a almacenar.
         * @param nextNode Puntero al siguiente nodo (nullptr por defecto).
         */
        Node(const T &aData, Node *nextNode = nullptr)
            : m_data(aData), next(nextNode) {};

        /**
         * @brief Destructor del nodo.
         */
        ~Node() {};
    };

    Node  *m_head; ///< Puntero al primer nodo de la lista (nullptr si vacía).
    Node  *m_tail; ///< Puntero al último nodo de la lista (nullptr si vacía).
    unsigned m_size; ///< Número de elementos almacenados en la lista.

    /**
     * @brief Elimina todos los nodos y libera su memoria.
     * @post La lista queda vacía (cabeza, cola nulas y tamaño 0).
     */
    void clear();
public:

    /**
     * @class Iterator
     * @brief Iterador de recorrido secuencial para ListaEnlazada.
     */
    class Iterator {
    private:
        Node  *m_node; ///< Puntero al nodo actual apuntado por el iterador.
    public:
        friend class ListaEnlazada<T> ;

        /**
         * @brief Constructor del iterador.
         * @param aNode Nodo inicial al que apunta el iterador (nullptr por defecto).
         */
        Iterator (Node  *aNode=nullptr);

        /**
         * @brief Comprueba si el iterador ha llegado al final de la lista.
         * @return true si el iterador apunta a nullptr (fin de lista); false en caso contrario.
         */
        bool isEnd() const;

        /**
         * @brief Avanza el iterador al siguiente nodo.
         * @post Si ya estaba al final, permanece en nullptr.
         */
        void next();

        /**
         * @brief Devuelve una referencia al dato del nodo actual.
         * @return Referencia al dato del nodo actual.
         * @throws std::out_of_range Si el iterador apunta a nullptr.
         */
        T &data() const;

        /**
         * @brief Destructor del iterador.
         */
        ~Iterator();
    };

    /**
     * @brief Constructor por defecto.
     * @post Crea una lista vacía (cabeza, cola nulas y tamaño 0).
     */
    ListaEnlazada();

    /**
     * @brief Constructor de copia.
     * @param aux Lista enlazada a copiar.
     * @post El nuevo objeto es una copia profunda de aux.
     */
    ListaEnlazada(const ListaEnlazada<T>  &aux);

    /**
     * @brief Destructor.
     * @post Libera todos los nodos de la lista.
     */
    ~ListaEnlazada();

    /**
     * @brief Operador de asignación por copia.
     * @param aux Lista enlazada a asignar.
     * @return Referencia al propio objeto tras la asignación.
     * @post El objeto actual es una copia profunda de aux.
     */
    ListaEnlazada &operator=(const ListaEnlazada<T>  &aux);

    /**
     * @brief Operador de suma. Concatena dos listas en una nueva.
     * @param aux Lista enlazada a concatenar a la derecha.
     * @return Nueva lista con los elementos de this seguidos de los de aux.
     */
    ListaEnlazada<T>  operator+(const ListaEnlazada<T>  &aux);

    /**
     * @brief Devuelve un iterador apuntando al primer nodo.
     * @return Iterador al inicio de la lista.
     */
    Iterator iterator() const;

    /**
     * @brief Inserta un elemento al inicio de la lista.
     * @param data Dato a insertar.
     * @post El tamaño aumenta en 1. Si la lista estaba vacía, el nodo es cabeza y cola.
     */
    void insertAtBiginning(const T &data);

    /**
     * @brief Inserta un elemento al final de la lista.
     * @param data Dato a insertar.
     * @post El tamaño aumenta en 1. Si la lista estaba vacía, el nodo es cabeza y cola.
     */
    void insertAtEnd(const T &data);

    /**
     * @brief Inserta un elemento antes del nodo apuntado por el iterador.
     * @param p Iterador que apunta al nodo de referencia.
     * @param data Dato a insertar.
     * @throws std::invalid_argument Si el iterador no apunta a ningún nodo.
     * @throws std::out_of_range Si el iterador no pertenece a esta lista.
     * @post El tamaño aumenta en 1.
     */
    void InsertBefore(Iterator &p, const T &data);

    /**
     * @brief Inserta un elemento después del nodo apuntado por el iterador.
     * @param p Iterador que apunta al nodo de referencia.
     * @param data Dato a insertar.
     * @throws std::invalid_argument Si el iterador no apunta a ningún nodo.
     * @post El tamaño aumenta en 1.
     */
    void insertAfter( Iterator &p, const T &data);

    /**
     * @brief Elimina el primer elemento de la lista.
     * @throws std::out_of_range Si la lista está vacía.
     * @post El tamaño disminuye en 1.
     */
    void removeFirst();

    /**
     * @brief Elimina el último elemento de la lista.
     * @throws std::out_of_range Si la lista está vacía.
     * @post El tamaño disminuye en 1.
     */
    void removeLast();

    /**
     * @brief Elimina el nodo apuntado por el iterador y avanza el iterador al siguiente.
     * @param i Iterador que apunta al nodo a eliminar.
     * @throws std::invalid_argument Si el iterador no apunta a ningún nodo.
     * @throws std::out_of_range Si el nodo no pertenece a esta lista.
     * @post El tamaño disminuye en 1. El iterador queda apuntando al nodo siguiente.
     */
    void remove(Iterator &i);

    /**
     * @brief Devuelve el número de elementos de la lista.
     * @return Número de elementos almacenados.
     */
    int size(){ return m_size;};

    /**
     * @brief Concatena otra lista al final de esta (modifica el objeto actual).
     * @param l Lista a concatenar.
     * @return Referencia al propio objeto con los elementos de l añadidos al final.
     */
    ListaEnlazada<T> &concatenate(const ListaEnlazada<T>  &l);

    /**
     * @brief Devuelve una referencia al primer elemento de la lista.
     * @return Referencia al dato del primer nodo.
     * @throws std::invalid_argument Si la lista está vacía.
     */
    T &first(){
        if (!m_head)
            throw std::invalid_argument("No existe ese elemento");
        return m_head->m_data;
    };

    /**
     * @brief Devuelve una referencia al último elemento de la lista.
     * @return Referencia al dato del último nodo.
     * @throws std::invalid_argument Si la lista está vacía.
     */
    T &last(){
        if (!m_tail)
            throw std::invalid_argument("No existe ese elemento");
        return m_tail->m_data;
    };
};

#include "../src/ListaEnlazada.tpp"
#endif //LISTAENLAZADA_H
