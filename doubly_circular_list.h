//! Copyright [2020] <Andre Luiz Souza dos Santos>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>  //  C++ exceptions

namespace structures {

template<typename T>
//! DoublyCircularLIst
class DoublyCircularList {
 public:
    //! DoublyCircularList
    DoublyCircularList();
    //! ~DoublyCircularList
    ~DoublyCircularList();
    //! clear
    void clear();
    //! push_back
    void push_back(const T& data);  // insere no fim
    //! push_front
    void push_front(const T& data);  // insere no início
    //! insert
    void insert(const T& data, std::size_t index);  // insere na posição
    //! insert_sorted
    void insert_sorted(const T& data);  // insere em ordem
    //! pop
    T pop(std::size_t index);  // retira da posição
    //! pop_back
    T pop_back();  // retira do fim
    //! pop_front
    T pop_front();  // retira do início
    //! remove
    void remove(const T& data);  // retira específico
    //! empty
    bool empty() const;  // lista vazia
    //! contains
    bool contains(const T& data) const;  // contém
    //! at
    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    //! const at
    const T& at(std::size_t index) const;  // getter constante a um elemento
    //! find
    std::size_t find(const T& data) const;  // posição de um dado
    //! size
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
        data_{data}
        {}

        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
        data_{data},
        next_{next},
        prev_{prev}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;  //!< data
        Node* prev_;  //!< prev
        Node* next_;  //!< next
    };

    Node* node_of_index(std::size_t index) {
        auto it = head;
        if (index <= size_/2) {
            for (auto i = 1u; i <= index; ++i)
                it = it->next();
        } else {
            for (auto i = 1u; i <= (size_-index); ++i)
                it = it->prev();
        }
        return it;
    }

    void insert(const T& data, Node* node_);

    Node* head{nullptr};  //!< head
    std::size_t size_{0u};  //!< size
};

//! Construtor padrão
template<typename T>
DoublyCircularList<T>::DoublyCircularList() {}

//! Destrutor
template<typename T>
DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

//! clear
template<typename T>
void DoublyCircularList<T>::clear() {
    while (!empty())
        pop_front();
}

//! Push back
template<typename T>
void DoublyCircularList<T>::push_back(const T& data) {
      insert(data, size_);
}

//! Push front
template<typename T>
void DoublyCircularList<T>::push_front(const T& data) {
    Node* newNode = new Node(data);
    if (newNode == nullptr)
        throw std::out_of_range("Lista cheia");

    if (empty()) {
      head = newNode;
      head->next(head);
      head->prev(head);
    } else {
      newNode->next(head);
      newNode->prev(head->prev());
      head->prev()->next(newNode);
      head->prev(newNode);
      head = newNode;
    }
    size_++;
}

//! Insert
template<typename T>
void DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("posiçao invalida");

    if (index == 0) {
        push_front(data);
    } else {
        Node* newNode = new Node(data);
        if (newNode == nullptr)
            throw std::out_of_range("lista cheia");

        Node* node_ = node_of_index(index);
        newNode->next(node_);
        newNode->prev(node_->prev());
        node_->prev()->next(newNode);
        node_->prev(newNode);
        size_++;
    }
}

//! Insert
template<typename T>
void DoublyCircularList<T>::insert(const T& data, Node* previous) {
    Node* newNode = new Node(data);
    if (newNode == nullptr)
        throw std::out_of_range("lista cheia!");

    if (empty()) {
        head = newNode;
        head->next(head);
        head->prev(head);
    } else {
        previous->next()->prev(newNode);
        newNode->next(previous->next());
        previous->next(newNode);
        newNode->prev(previous);
    }
    size_++;
}

//! Insert sorted
template<typename T>
void DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        auto node_ = head;
        std::size_t position = 0u;
        while (data > node_->data()) {
            if (++position == size_)
                break;
            node_ = node_->next();
        }
        position == 0? push_front(data) :
        position == size_?  push_back(data) :
                            insert(data, node_->prev());
    }
}

//! pop
template<typename T>
T DoublyCircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Lista vazia");
    if (index >= size())
        throw std::out_of_range("Posiçao invalida");

    if (index == 0)
        return pop_front();

    auto out = node_of_index(index);
    T data = out->data();
    out->prev()->next(out->next());
    out->next()->prev(out->prev());
    size_--;
    delete out;
    return data;
}

//! pop back
template<typename T>
T DoublyCircularList<T>::pop_back() {
    return pop(size_-1);
}

//! pop front
template<typename T>
T DoublyCircularList<T>::pop_front() {
      if (empty())
          throw std::out_of_range("Lista vazia");

      auto out = head;
      T data = head->data();
      head->prev()->next(head->next());
      head->next()->prev(head->prev());
      head = head->next();
      size_--;
      delete out;

      if (empty())
        head = nullptr;
      return data;
}

//! remove
template<typename T>
void DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}

//! empty
template<typename T>
bool DoublyCircularList<T>::empty() const {
    return size() == 0u;
}

//! contains
template<typename T>
bool DoublyCircularList<T>::contains(const T& data) const {
    return find(data) != size();
}

//! at
template<typename T>
T& DoublyCircularList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Posiçao Invalida");

    Node* node_ = node_of_index(index);
    return node_->data();
}

//! at
template<typename T>
const T& DoublyCircularList<T>::at(std::size_t index) const {
    if (index >= size())
        throw std::out_of_range("Posiçao invalida !");

    Node* node_ = node_of_index(index);
    return node_->data();
}

//! find
template<typename T>
std::size_t DoublyCircularList<T>::find(const T& data) const {
    std::size_t index = 0u;
    auto node_ = head;
    while (index < size()) {
        if (node_->data() == data)
            break;
        node_ = node_->next();
        index++;
    }
    return index;
}

//! size
template<typename T>
std::size_t DoublyCircularList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
