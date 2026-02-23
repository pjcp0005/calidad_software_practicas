//
// Created by jmart on 08/10/2025.
//
#include "../include/ListaEnlazada.h"
#include <sstream>

/**
 * 
 * Iterador
 * 
 */
/**
 * @brief Constructor del iterador
 * @param aNode Nodo al que apunta el iterador (por defecto es nullptr)
 */
template<class T>
ListaEnlazada<T>::Iterator::Iterator(Node *aNode){
    m_node = aNode;
};

/**
 * @brief Comprueba si el iterador ha llegado al final de la lista
 * @return true si el iterador está al final de la lista, false en caso contrario
 */
template<class T>
bool ListaEnlazada<T>::Iterator::isEnd() const {
    return m_node == nullptr;
};

/**
 * @brief Avanza el iterador al siguiente nodo en la lista
 * @post Condición: Si el iterador ya estaba al final de la lista, permanece al final.
 */
template<class T>
void ListaEnlazada<T>::Iterator::next(){
    if(m_node != nullptr){
        m_node = m_node->next;
    }
};

/**
 * @brief Devuelve una referencia al dato del nodo actual al que apunta el iterador
 * @return Referencia al dato del nodo actual
 */
template<class T>
T &ListaEnlazada<T>::Iterator::data() const{
    if(m_node == nullptr){
        throw std::out_of_range("Iterador fuera de rango");
    }
    return m_node->m_data;
};

/**
 * @brief Destructor del iterador
 */
template<class T>
ListaEnlazada<T>::Iterator::~Iterator() = default;

/**
 * 
 * ListaEnlazada
 * 
 */
/**
 * Metodos privados
 */

 /**
  * @brief Elimina todos los nodos de la lista y libera la memoria asociada
  * @post Condición: La lista queda vacía (cabeza y cola son nulas, tamanyo es 0).
  */
template<class T>
void ListaEnlazada<T>::clear(){
    Node *current = m_head;
    Node *nextNode;

    while(current != nullptr){
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
};

/**
 * Constructor
 */

 /**
  * @brief Constructor por defecto de la lista enlazada
  * @post Condición: La lista está vacía (cabeza y cola son nulas, tamaño es 0).
  */
template<class T>
ListaEnlazada<T>::ListaEnlazada(){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
};

/**
 * @brief Constructor de copia de la lista enlazada
 * @param aux Lista enlazada que se va a copiar.
 * @post Condición: La nueva lista es una copia exacta de la lista dada.
 */
template<class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &aux){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;

    Node *current = aux.m_head;
    while(current != nullptr){
        insertAtEnd(current->m_data);
        current = current->next;
    }
};

/**
 * @brief Destructor de la lista enlazada
 * @post Condición: Todos los nodos de la lista son eliminados y la lista queda vacía.
 */
template<class T>
ListaEnlazada<T>::~ListaEnlazada(){
    clear();
}

/**
 * Operadores
 */

 /**
  * @brief Sobrecarga del operador de asignación para la lista enlazada
  * @param aux Lista enlazada que se va a asignar.
  * @return Referencia a la lista enlazada actual.
  * @post Condición: La lista actual es una copia exacta de la lista dada
  */
template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::operator=(const ListaEnlazada<T> &aux) {
    if (this == &aux) {
        return *this;
    }

    clear();

    Node *current = aux.m_head;
    while(current != nullptr){
        insertAtEnd(current->m_data);
        current = current->next;
    }

    return *this;
};

/**
 * @brief Sobrecarga del operador de suma para concatenar dos listas enlazadas
 * @param aux Lista enlazada que se va a concatenar.
 * @return Nueva lista enlazada que es la concatenación de las dos listas.
 */
template<class T>
ListaEnlazada<T> ListaEnlazada<T>::operator+(const ListaEnlazada<T> &aux){
    ListaEnlazada<T> result;

    Node *current = m_head;
    while(current != nullptr){
        result.insertAtEnd(current->m_data);
        current = current->next;
    }

    current = aux.m_head;
    while(current != nullptr){
        result.insertAtEnd(current->m_data);
        current = current->next;
    }

    return result;
}

/**
 * Iterador
 */

 /**
  * @brief Devuelve un iterador que apunta al primer nodo de la lista
  * @return Iterador que apunta al primer nodo de la lista
  */
template<class T>
typename ListaEnlazada<T>::Iterator ListaEnlazada<T>::iterator() const{
    return Iterator(m_head);
};

/**
 * Inserts
 */

 /**
  * @brief Inserta un elemento al inicio de la lista
  * @param data Dato que se va a insertar.
  * @post Condición: Si la lista está vacía, el nuevo nodo se convierte
  */
template<class T>
void ListaEnlazada<T>::insertAtBiginning(const T &data){
    Node *newNode = new Node(data, m_head);
    m_head = newNode;

    if(m_tail == nullptr){
        m_tail = newNode;
    }

    ++m_size;
};

/**
 * @brief Inserta un elemento al final de la lista
 * @param data Dato que se va a insertar.
 * @post Condición: Si la lista está vacía, el nuevo nodo se convierte en la cabeza y la cola de la lista.
 */
template<class T>
void ListaEnlazada<T>::insertAtEnd(const T &data){
    Node *newNode = new Node(data, nullptr);

    if(m_head == nullptr){
        m_head = m_tail = newNode;
    } else {
        m_tail->next = newNode;
        m_tail = newNode;
    }

    ++m_size;
};

/**
 * @brief Inserta un elemento antes del nodo apuntado por el iterador dado
 * @param it Iterador que apunta al nodo antes del cual se insertará el nuevo nodo.
 * @param data Dato que se va a insertar.
 * @throws std::invalid_argument si el iterador no apunta a ningún nodo
 * @throws std::out_of_range si el iterador no pertenece a la lista
 * @post Condición: Si el iterador apunta al primer nodo, se inserta al inicio de la lista.
 */
template<class T>
void ListaEnlazada<T>::InsertBefore(Iterator &it, const T &data){
    if(it.m_node == nullptr){
        throw std::invalid_argument("El iterador no apunta a nada (no se puede insertar antes del final)");
    }

    if(it.m_node == m_head){
        insertAtBiginning(data);
    }
    
    Node *prev = m_head;
    while(prev != nullptr && prev->next != it.m_node){
        prev = prev->next;
    }

    if(prev == nullptr){
        throw std::out_of_range("Iterador no encontrado en la lista");
    }

    Node *newNode = new Node(data, it.m_node);
    prev->next = newNode;
    ++m_size;
};

/**
 * @brief Inserta un elemento después del nodo apuntado por el iterador dado
 * @param it Iterador que apunta al nodo después del cual se insertará el nuevo nodo.
 * @param data Dato que se va a insertar.
 * @throws std::invalid_argument si el iterador no apunta a ningún nodo
 */
template<class T>
void ListaEnlazada<T>::insertAfter(Iterator &it, const T &data){
    if(it.m_node == nullptr){
        throw std::invalid_argument("El iterador no apunta a nada (no se puede insertar antes del final)");
    }

    Node *newNode = new Node(data, it.m_node->next);
    it.m_node->next = newNode;

    if(it.m_node == m_tail){
        m_tail = newNode;
    }

    ++m_size;
};

/**
 * Removes
 */

template<class T>
void ListaEnlazada<T>::removeFirst(){
    if (m_head == nullptr) {
        throw std::out_of_range("No se puede eliminar: la lista está vacía");
    }

    if(m_head == m_tail){
        clear();
    } else {
        Node *aux = m_head;
        m_head = m_head->next;
        delete aux;
        --m_size;
    }
};

template<class T>
void ListaEnlazada<T>::removeLast(){
    if(m_tail == nullptr){
        throw std::out_of_range("La lista está vacía, no se puede eliminar el último elemento");
    }

    if(m_head == m_tail){
        clear();
    } else {
        Node *aux = m_head;
        while(aux->next != m_tail){
            aux = aux->next;
        }
        
        delete m_tail;
        m_tail = aux;
        m_tail->next = nullptr;
        --m_size;
    }
};

template<class T>
void ListaEnlazada<T>::remove(Iterator &it){
    if(it.m_node == nullptr){
        throw std::invalid_argument("El iterador no apunta a ningún nodo");
    }

    if(it.m_node == m_head && it.m_node == m_tail){
        clear();
        it.m_node = nullptr;
    } else {
         Node *aux = m_head;
        while(aux != nullptr && aux->next != it.m_node){
            aux = aux->next;
        }

        if(aux == nullptr){
            throw std::out_of_range("El nodo del iterador no pertenece a la lista");
        }

        aux->next = it.m_node->next;

        if(it.m_node == m_tail){
            m_tail = aux;
        }

        delete it.m_node;
        it.m_node = aux->next; 
        --m_size;
    }
};

/**
 * Otros metodos
 */

template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::concatenate(const ListaEnlazada<T> &l){
    Node *current = l.m_head;

    while(current != nullptr){
        insertAtEnd(current->m_data);
        current = current->next;
    }

    return *this;
};

