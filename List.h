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
        //Node<T> *searchBehind = NULL;

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
                this->last->setPrev(last);      //se establece el prev de last
                this->last->setNext(newNode);   
            } else {
                this->first = newNode;  
                this->last = newNode;
            }
            this->last = newNode;

            empty = false;
            quantity++;
        }

        Node<T>* getFirst() {
            return this->first;
        }

        Node<T>* getLast() {
            return this->last;
        }

        int getSize() {
            return quantity;
        }

        bool isEmpty() {
            return !quantity;
        }

        T* find(int pPosition) {    //el find ya no necesita el search behind
            T* result = NULL;
            searchPosition = this->first;
            //searchBehind = NULL;
            
            if (pPosition<getSize()) {
                cout<<"\nSize: "<<getSize()<<endl;
                while(pPosition>0) {
                    //searchBehind = searchPosition;
                    
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
                //if (searchBehind!=NULL) {
                    //searchBehind->setNext(newNode);
                if (searchPosition->getPrev() != NULL) {            //se usa el pointer prev en lugar de ir guardando cada behind position
                    
                    //-----------------------------------------
                    searchPosition->getPrev()->setNext(newNode);
                    newNode->setPrev(searchPosition->getPrev());
                    searchPosition->setPrev(newNode);
                    newNode->setNext(searchPosition);
                    //-----------------------------------------

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
                    find(pPosition);
                    
                    //searchBehind->setNext(searchPosition->getNext());

                    if (searchPosition==last) {
                        //last = searchBehind;
                        last = last->getPrev();
                        last->setNext(NULL);
                        searchPosition->setPrev(NULL);
                        cout<<"\nSe entro"<<endl;
                    }

                    
                    //-----------------------------------------------------------
                    //searchPosition->getPrev()->setNext(searchPosition->getNext());
                    searchPosition->getPrev()->setNext(searchPosition->getNext());
                    searchPosition->getNext()->setPrev(searchPosition->getPrev());
                    
                    searchPosition->setNext(NULL);
                    searchPosition->setPrev(NULL);
                    //-----------------------------------------------------------

                    //searchPosition->setNext(NULL);
                } else {
                    first = first->getNext();
                    first->setPrev(NULL);
                    search->setNext(NULL);
                    delete search;
                }
                quantity--;
            }
            return result;
        } 
};

#endif