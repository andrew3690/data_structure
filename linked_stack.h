//! Copyright 2020 <Andre Luiz Souza Santos>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H


#include <cstdint>
#include <stdexcept>  // C++ Exceptions
#include <cstring>

namespace structures {

//! LinkedStack
template<typename T>
class LinkedStack {
 public:
    //!
    LinkedStack();
    //!
    ~LinkedStack();
    //! clear
    void clear();  // limpa pilha D
    //! push
    void push(const T& data);  // empilha D
    //! pop
    T pop();  // desempilha D
    //! top
    T& top() const;  // dado no topo D
    //! empty
    bool empty() const;  // pilha vazia D
    //! size
    std::size_t size() const;  // tamanho da pilha D

 private:
    class Node {  // elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: info
            return data_;
        }

        const T& data() const {  // getter-constante: info
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }
        const Node* next() const {  // getter-constante: próximo
            return next_;
        }

        void next(Node* next) {  // setter: próximo
            next_ = next;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};  // nodo-topo
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedStack<T>::LinkedStack() {   // Construtor
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::push(const T &data) {
    Node *novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("pilha cheia");
    } else {
        novo->next(top_);
        top_ = novo;
        size_++;
    }
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    } else {
        T data_aux;
        auto saiu = top_;
        data_aux = saiu->data();
        top_ = saiu->next();
        size_--;
        delete saiu;
        return data_aux;
    }
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    } else {
        return top_->data();
    }
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return(size_ == 0);
}
template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
