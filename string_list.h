//! Copyright [2020] <Andre Luiz de Souza Santos>


#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>



namespace structures {


//! ...
template<typename T>
class ArrayList {
 public:
    //! Constructor
    ArrayList();
    //! Construtor with params
    explicit ArrayList(std::size_t max_size);
    //! Destructor
    ~ArrayList();

    //! Cleaning the list
    void clear();
    //! insert at the end og the list
    void push_back(const T& data);
    //! insert at the begining of the list
    void push_front(const T& data);
    //! insert at a specific place of the list
    void insert(const T& data, std::size_t index);
    //! insert sorting the elemensts of the list
    void insert_sorted(const T& data);
    //!
    void new_tam(std::size_t tam);
    //! takes out of the list
    T pop(std::size_t index);
    //! takes out the last item of the list
    T pop_back();
    //! takes out the first item of the list
    T pop_front();
    //! removes the data from memory
    void remove(const T& data);
    //! returns if the list is full D
    bool full() const;
    //! returns if the list is empty D
    bool empty() const;
    //! returns if the list contains the specified data D
    bool contains(const T& data) const;
    //! returns the number by itself
    std::size_t find(const T& data) const;
    //! returns the actual size of the list
    std::size_t size() const;
    //! returns the maximum size of the list
    std::size_t max_size() const;
    //! ...
    T& at(std::size_t index);
    //! ...
    T& operator[](std::size_t index);
    //! ...
    const T& at(std::size_t index) const;
    //! ...
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};



//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! ...
    ~ArrayListString();
    //! ...
    void clear();
    //! ...
    void push_back(const char *data);
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    void remove(const char *data);
    //! ...
    bool contains(const char *data);
    //! ...
    std::size_t find(const char *data);
};

}  // namespace structures

#endif
// Constructor
template<typename T>
structures::ArrayList<T>::ArrayList() {
    ArrayList(DEFAULT_MAX);
}
// Constructor with params
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        size_  = 0;
}
// Destructor
template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}
// Retruning max size of the list
template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}
// Cleaning the list logically
template<typename T>
void structures::ArrayList<T>::clear() {
        size_ = 0;
}
// If size_ equals max_size_ it's true
template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size_ == max_size_);
}
// Empty the list
template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size_ == 0);
}
// Return the actual size of the list
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
//
template<typename T>
void structures::ArrayList<T>::new_tam(std::size_t tam) {
    size_ = tam;
}
// Inserts at the end of the list
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    contents[size_++] = data;
}
// inserts at the begin of the list
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
if (full()) throw std::out_of_range("lista cheia");
for (int i = size_ ; i > 0 ; i--) {
        contents[i] = contents[i-1];
    }
size_++;
contents[0] = data;
}
// inserts at a specific place of the list
template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    if (index > size_) {
        throw std::out_of_range("posicao invalida");
    }
    for (std::size_t i = size_; i > index; i--) {
        contents[i] = contents[i-1];
    }
    contents[index] = data;
    size_++;
}
// find the item at the list
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0 ; i < size_ ; i++) {
        if (data == contents[i]) {
            return i;
        }
    }
    return size_;
}

// returns true if the value is inside the list
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < size_ -1 ; i++) {
        if (data == contents[i]) {
            return true;
        }
    }
    return false;
}
// inserts by order of elements
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    int i = size_ - 1;
    while (i >= 0 && (contents[i] > data)) {
        contents[i + 1] = contents[i];
        i--;
    }
    contents[i + 1] = data;
    size_++;
}
// removes the first element of the list
template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) throw std::out_of_range("lista vazia");
    return pop(0);
}
// removes a spefic element of the list
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    }
    T aux = contents[index];
    for (int i = index; i < size_ - 1; i++) {
        contents[i] = contents[i+1];
    }
    size_--;
    return aux;
}
// removes the last item of the list
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) throw std::out_of_range("lista vazia");
    size_--;
    return contents[size_];
}
// removes itens from list
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (!contains(data)) return;
    int i = find(data);
    int j;
    for (j = i; j < size_ - 1; j++) {
        contents[j] = contents[j + 1];
    }
    size_--;
}
// returns the index value at the list
template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}
template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}
// Metodos da classe ArrayListString
// Destructor da Classe ArrayListString
structures::ArrayListString::~ArrayListString() {
    for (std::size_t i = 0 ; i < ArrayList::size() ; i++) {
        delete [] ArrayList::operator[](i);
    }
}
// Clear da classe ArrayListString
void structures::ArrayListString::clear() {
     for (std::size_t i = 0; i < ArrayList::size(); i++) {
        delete [] ArrayList::operator[](i);
    }
    ArrayList::new_tam(0);
}
// Insert Sorted
void structures::ArrayListString::insert_sorted(const char *data) {
    if (ArrayList::full()) throw std::out_of_range("lista cheia");
    int i = ArrayList::size() - 1;
    while (i >= 0 && (strcmp(ArrayList::at(i), data) > 0)) {
        i--;
    }
    this -> insert(data, i+1);
}
// Push front na classe ArrayListString
void structures::ArrayListString::push_front(const char *data) {
    if (ArrayList::full()) throw std::out_of_range("lista cheia");
    int string_size = strlen(data) + 1;
    char *data1 = new char[string_size];
    snprintf(data1 , string_size , "%s", data);
    data1[string_size-1] = '\0';
    ArrayList::push_front(data1);
}
// Push Back na classe ArrayListString
void structures::ArrayListString::push_back(const char *data) {
    if (ArrayList::full()) throw std::out_of_range("lista cheia");
    int string_size = strlen(data) + 1;
    char *data1 = new char[string_size];
    snprintf(data1 , string_size , "%s" , data);
    data1[string_size-1] = '\0';
    ArrayList::push_back(data1);
}
// Insert na classe ArrayListString
void structures::ArrayListString::insert(const char *data, std::size_t index) {
    if (ArrayList::full()) throw std::out_of_range("lista cheia");
    int string_size = strlen(data) + 1;
    char *data1 = new char[string_size];
    snprintf(data1 , string_size , "%s", data);
    data1[string_size-1] = '\0';
    ArrayList::insert(data1, index);
}
// Contain em ArrayListString
bool structures::ArrayListString::contains(const char *data) {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        if (!strcmp(ArrayList::at(i), data)) {
            return true;
        }
    }
    return false;
}
// find em ArrayListString
std::size_t structures::ArrayListString::find(const char *data) {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        if (!strcmp(ArrayList::at(i), data)) {
            return i;
        }
    }
    return ArrayList::size();
}
// pop em ArrayListString
char * structures::ArrayListString::pop(std::size_t index) {
    if (ArrayList::empty()) throw std::out_of_range("array vazio");
    if (index >= ArrayList::size()) {
        throw std::out_of_range("posicao invalida");
    }
    char *i = operator[](index);
    ArrayList::pop(index);
    return i;
}
// pop_back em ArrayListString
char * structures::ArrayListString::pop_back() {
    if (ArrayList::empty()) throw std::out_of_range("array vazio");
    char *i = this -> pop(ArrayList::size()-1);
    return i;
}
// pop front em ArrayListString
char * structures::ArrayListString::pop_front() {
    if (ArrayList::empty()) throw std::out_of_range("array vazio");
    char *i = this -> pop(0);
    return i;
}
// remove em ArrayListString
void structures::ArrayListString::remove(const char *data) {
    if (ArrayList::empty()) throw std::out_of_range("lista vazia");
    if (!contains(data)) return;
    int i = this -> find(data);
    this -> pop(i);
}
