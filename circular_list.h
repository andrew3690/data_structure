//!  Copyright [2020] <Andre Luiz Souza Santos>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>  //  std::size_t
#include <stdexcept>  //  C++ exceptions

namespace structures {
template<typename T>
//! Class CircularList
class CircularList {
 public:
    //! CircularList
    CircularList();  // Construtor
    //! ~CircularList
    ~CircularList();  // Destrutor
    //! clear
    void clear();  //  limpar lista
    //! push_back
    void push_back(const T& data);  //  inserir no fim
    //! push_front
    void push_front(const T& data);  //  inserir no início
    //! insert
    void insert(const T& data, std::size_t index);  //  inserir na posição
    //! insert_sorted
    void insert_sorted(const T& data);  //  inserir em ordem
    //! at
    T& at(std::size_t index);  //  acessar em  indice
    //! T& at
    const T& at(std::size_t index) const;  //  versão const do acesso ao indice
    //! pop
    T pop(std::size_t index);  //  retirar da posição
    //! pop_back
    T pop_back();  //  retirar do fim
    //! pop_front
    T pop_front();  //  retirar do início
    //! remove
    void remove(const T& data);  //  remover dado específico
    //! empty
    bool empty() const;  //  lista vazia
    //! contains
    bool contains(const T& data) const;  //  lista contém determinado dado?
    //! find
    std::size_t find(const T& data) const;  //  posição de  item na lista
    //! size
    std::size_t size() const;  //  tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
        data_{data}
        {}

        explicit Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        void data(const T& data) {
            data_ = data;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;  // data_
        Node* next_{nullptr};  // next_
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* before_index(std::size_t index) const {  // node anterior ao index
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* before);  // inserir na posicao polimorfico

    Node* head{nullptr};  //< head
    std::size_t size_{0u};  //< size_
};


template<typename T>
CircularList<T>::CircularList() {}

template<typename T>
CircularList<T>::~CircularList() {
    clear();
}

template<typename T>
void CircularList<T>::clear() {
    while (!empty())
        pop_front();
}


template<typename T>
void CircularList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* new_node = new Node(head->data(), head->next());
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        head->next(new_node);
        head->data(data);
        head = new_node;
        size_++;
    }
}

template<typename T>
void CircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    if (empty()) {
        head = new_node;
        head->next(head);
    } else {
        new_node->data(head->data());
        new_node->next(head->next());
        head->next(new_node);
        head->data(data);
    }
    size_++;
}

template<typename T>
void CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Invalid index!");

    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        Node* before = before_index(index);
        Node* next = before->next();
        new_node->next(next);
        before->next(new_node);
        size_++;
    }
}

template<typename T>
void CircularList<T>::insert(const T& data, Node* before) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(before->next());
    before->next(new_node);
    size_++;
}

template<typename T>
void CircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* node_ = head;
        Node* before = head;
        std::size_t position = size();
        for (auto i = 0u; i < size(); ++i) {
            if (!(data > node_->data())) {
                position = i;
                break;
            }
            before = node_;
            node_ = node_->next();
        }
        position == 0? push_front(data) :
        position == size_?  push_back(data) :
                            insert(data, before);
    }
}

template<typename T>
T& CircularList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* node_ = index == 0? head : before_index(index)->next();
    return node_->data();
}

template<typename T>
const T& CircularList<T>::at(std::size_t index) const {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* node_ = index == 0? head : before_index(index)->next();
    return node_->data();
}

template<typename T>
T CircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Invalid index!");

    if (index == 0)
        return pop_front();

    Node* before_out = before_index(index);
    Node* out = before_out->next();
    T data = out->data();
    before_out->next(out->next());
    size_--;
    delete out;
    return data;
}

template<typename T>
T CircularList<T>::pop_back() {
    return pop(size_ - 1u);
}

template<typename T>
T CircularList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Empty list!");

    Node* out;
    T data = head->data();
    if (size_ == 1) {
        out = head;
        head = nullptr;
    } else {
        out = head->next();
        head->next(out->next());
        head->data(out->data());
    }
    size_--;
    delete out;
    return data;
}

template<typename T>
void CircularList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool CircularList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool CircularList<T>::contains(const T& data) const {
    return find(data) != size();
}

template<typename T>
std::size_t CircularList<T>::find(const T& data) const {
    std::size_t index = 0u;
    Node* node_ = head;
    while (index < size()) {
        if (node_->data() == data)
            break;
        node_ = node_->next();
        index++;
    }
    return index;
}

template<typename T>
std::size_t CircularList<T>::size() const {
    return size_;
}

}  //  namespace structures

#endif
