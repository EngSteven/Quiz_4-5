#include "Node.h"
#include "eventos.h"

#ifndef LIST 

#define LIST 1

// 2. ajustar a que esta lista sea doblemente enlazada, cambia el add, find, insert y el remove
template <class T>
class List {
    private:
        Node<T> *first;
        Node<T> *last;
        int quantity;
        bool empty;
        Node<T> *searchPosition = NULL;
        Node<T> *searchBehind = NULL;

    public:
        List() {
            first = NULL;
            last = NULL;
            quantity = 0;
            empty = true;
        }

        void add(T *pData) {
            Node<T> *newNode = new Node<T>(pData);

            if (quantity>0) {
                this->last->setPrev(newNode);      //se establece el prev de last
                this->last->setNext(newNode);
            } else {
                this->first = newNode;
            }
            this->last = newNode;

            empty = false;
            quantity++;
        }

        Node<T>* getFirst() {
            return this->first;
        }

        int getSize() {
            return quantity;
        }

        bool isEmpty() {
            return !quantity;
        }

        T* find(int pPosition) {
            T* result = NULL;
            searchPosition = this->first;
            searchBehind = NULL;

            if (pPosition<getSize()) {
                while(pPosition>0) {
                    searchBehind = searchPosition;
                    searchPosition->setPrev(searchPosition);
                    searchPosition = searchPosition->getNext();
                    pPosition--;
                }
                result = searchPosition->getData();
            }

            return result;
        }

        // es que si el position es mayor a la cantidad, entonces inserto al final
        void insert(int pPosition, T *pData) {
            
            if (pPosition<getSize() && first!=NULL) {
                Node<T> *newNode = new Node<T>(pData);

                T* result = find(pPosition);
                
                newNode->setNext(searchPosition);
                if (searchBehind!=NULL) {
                    searchBehind->setNext(newNode);
                   
                    searchPosition->getPrev()->setNext(newNode);
                    newNode->setPrev(searchPosition->getPrev());
                    searchPosition->setPrev(newNode);
                    newNode->setNext(searchPosition);

                } else {
                    this->first = newNode;
                }
                
                quantity++;
            } else {
                add(pData);
            }
        }

        bool remove(int pPosition) {
            bool result = false;
            if (first!=NULL && pPosition<getSize()) {
                Node<T> *search = first;
                if (pPosition!=0) {
                    T* data = find(pPosition);

                    searchBehind->setNext(searchPosition->getNext());
                    
                    /*Se queria implementar de esta forma, pero no da el resultado esparado
                    searchPosition->getPrev()->setNext(searchPosition->getNext());
                    searchPosition->getNext()->setPrev(searchPosition->getPrev());
                    */
                    if (searchPosition==last) {
                        last = last->getPrev();
                    }
                    searchPosition->setPrev(NULL);
                    searchPosition->setNext(NULL);
                } else {
                    first = first->getNext();
                    search->setNext(NULL);
                    delete search;
                }
                quantity--;
            }
            return result;
        }
};

#endif