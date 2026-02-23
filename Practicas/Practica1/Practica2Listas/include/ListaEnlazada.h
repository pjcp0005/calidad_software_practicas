//
// Created by jmart on 08/10/2025.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <stdexcept>
#include <string>

template<class T>
class ListaEnlazada {
private:
    //declaracion del Nodo local
    class Node {

    public:
        T m_data;
        Node *next;
        Node(const T &aData, Node *nextNode = nullptr)
            : m_data(aData), next(nextNode) {};
        ~Node() {};
    };

    Node  *m_head, *m_tail;
    unsigned m_size;

    void clear();
public:

    //declaracion del iterador
    class Iterator {
    private:
        Node  *m_node;
    public:
        friend class ListaEnlazada<T> ;

        Iterator (Node  *aNode=nullptr);
        bool isEnd() const;
        void next();
        T &data() const;
        ~Iterator();
    };

    ListaEnlazada();
    ListaEnlazada(const ListaEnlazada<T>  &aux);
    ~ListaEnlazada();

    ListaEnlazada &operator=(const ListaEnlazada<T>  &aux);
    ListaEnlazada<T>  operator+(const ListaEnlazada<T>  &aux);

    Iterator iterator() const;

    void insertAtBiginning(const T &data);
    void insertAtEnd(const T &data);
    void InsertBefore(Iterator &p, const T &data);
    void insertAfter( Iterator &p, const T &data);

    void removeFirst();
    void removeLast();
    void remove(Iterator &i);

    int size(){ return m_size;};

    ListaEnlazada<T> &concatenate(const ListaEnlazada<T>  &l);

    T &first(){ 
        if (!m_head) 
            throw std::invalid_argument("No existe ese elemento");
        return m_head->m_data;
    };
    T &last(){
        if (!m_tail) 
            throw std::invalid_argument("No existe ese elemento");
        return m_tail->m_data;
    };
};

#include "../src/ListaEnlazada.tpp"
#endif //LISTAENLAZADA_H
