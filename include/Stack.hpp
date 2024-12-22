#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <stdexcept>  // std::underflow_error kullanabilmek için
using namespace std;

template <typename T>  // belirli bir tür ile sınıf veya fonksiyon yazmak yerine, şablon kullanarak herhangi bir türde çalışabilen genel bir yapı oluşturduk
//Bu şablon sadece Node sınıfının içinde veri saklamak ve bağlantı oluşturmak için kullanılır.
class Node {
    public:
        T item;  // Node sınıfının taşıdığı veriyi temsil eder.
        Node<T> *next;  // next adlı bir işaretçidir. Bu işaretçi, bir sonraki Node nesnesine işaret eder.
        
        // Node sınıfının yapıcısı
        Node(const T& item, Node<T> *next = NULL) {
            this->item = item;
            this->next = next;
        }
};

template <typename T>  // Stack sınıfı için oluşturulan şablon 
class Stack {
    private:
        Node<T> *topOfStack;  // Yığının üstündeki öğeye işaretçi 
        
    public:
        Stack() {
            topOfStack = NULL;  // Yığın boş başlar
        }

        bool isEmpty() const {  // Yığının boş olup olmadığını kontrol eder
            return topOfStack == NULL;
        }

        void push(const T& item) {  // Yeni bir öğeyi yığına ekler
            topOfStack = new Node<T>(item, topOfStack);
        }

        void pop() {  // Yığının en üstündeki öğeyi çıkarma işlemi
            if (isEmpty()) throw "Stack is Empty";;  // Yığın boşsa hata fırlatılır
            Node<T> *tmp = topOfStack;
            topOfStack = topOfStack->next;
            delete tmp;
        }

        const T& top() const {  // Yığının en üstündeki öğeye erişir
            if (isEmpty()) throw "Stack is Empty";;  // Yığın boşsa hata fırlatılır
            return topOfStack->item;
        }

        void makeEmpty() {  // Yığın boş olana kadar pop işlemi yapar
            while (!isEmpty())
			 pop();
        }

        ~Stack() {  // Yığın nesnesi bellekten silindiğinde çalışır
            makeEmpty();
        }
};

#endif
