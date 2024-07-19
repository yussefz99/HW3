#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    /// class Node --------------------------------------------------------

    template<typename T>
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& val) : data(val), next(nullptr) {}
    };
//    class Node{
//    private:
//        T* data;
//        Node<T>* next;
//    public:
//        explicit Node(const T& data):data(data),next(nullptr){}
//        Node():data(nullptr),next(nullptr){}
//        ~Node<T>(){
//            delete data;
//        }
//        T* get_data(){
//            return data;
//        }
//        Node<T>* getNext(){
//            return next;
//        }
//    };


/// class Sortedlist --------------------------------------------------------

    template <typename T>
    class SortedList {
    public:
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */
         ///constructors and destructor:
         SortedList():head(nullptr),size(0){}

         SortedList(const SortedList<T>& other):head(nullptr),size(other.size){  // add exspation?
             Node<T>* ptr=other.head;
             Node<T>* nextInorder = nullptr;
             while (ptr != nullptr){
                 Node<T>* newNode=new Node<T>(ptr->data);
                 if(head == nullptr){
                     head=newNode;
                 } else{
                     nextInorder->next=newNode;
                 }
                 nextInorder = newNode;
                 ptr=ptr->next;
             }
         }

         SortedList& operator=(const SortedList<T>& other){
             if(this == &other)return *this;
             Node<T>* ptr=other.head;
             Node<T>* nextInorder = nullptr;
             while (ptr != nullptr){
                 Node<T>* newNode=new Node<T>(ptr->data);
                 if(head == nullptr){
                     head=newNode;
                 } else{
                     nextInorder->next=newNode;
                 }
                 nextInorder = newNode;
                 ptr=ptr->next;
             }
             size=other.size;
             return *this;
         }
         ~SortedList(){
             while (head) {
                 Node<T>* temp = head;
                 head = head->next;
                 delete temp;
             }
         }
         //-----------------------------------------------------
         ///iterator:
         class ConstIterator;
        ConstIterator begin()const{
            return ConstIterator(this,0);
        }
        ConstIterator end()const{
            return ConstIterator(this,size);
        }
         //-----------------------------------------------------
         ///functions:
         void insert(T data){ // T* data ??
             Node<T>* newNode=new Node<T>(data);
             if (!head || data > head->data) {
                 newNode->next = head;
                 head = newNode;
             } else {
                 Node<T>* curr = head;
                 while (curr->next && curr->next->data > data) {//????????????????>=
                     curr = curr->next;
                 }
                 newNode->next = curr->next;
                 curr->next = newNode;
             }
             size++;
         }

         void remove(const ConstIterator& it){
             if (it.index < 0 || it.index >= size) {
                 throw std::out_of_range("out_of_range");
             }

             if (it.index == 0) {
                 Node<T>* temp = head;
                 head = head->next;
                 delete temp;
             } else {
                 Node<T>* nextInorder = head;
                 int count = 0;
                 while (count < it.index - 1) {
                     nextInorder = nextInorder->next;
                     count++;
                 }
                 Node<T>* temp = nextInorder->next;
                 nextInorder->next = temp->next;
                 delete temp;
             }
             size--;
         }

         int length()const{
             return this->size;
        }


//---------------------------------------------------------
         friend bool operator==(const SortedList<T>& l1 ,const SortedList<T>& l2){ //?????????
             if(l1.size != l2.size)return false;
             Node<T>* ptr1=l1.head;
             Node<T>* ptr2=l2.head;
             while (ptr1 && ptr2){
                 if(ptr1->get_data() != ptr2->get_data())return false;
                 ptr1=ptr1->next;
                 ptr2=ptr2->next;
             }
             return true;
         }
         //-----------------------------------------------------------------

    private:
        Node<T>* head;
        int size;

    };


    /// class ConstIterator --------------------------------------------------------

    template <class T>
    class SortedList<T>::ConstIterator {
    private:
        int index;
        const SortedList* list;
        friend class SortedList;
        ConstIterator(const SortedList* list,int index):list(list),index(index){}
    public:
        ConstIterator(const ConstIterator& other)=default;
        ConstIterator& operator=(const ConstIterator& other)=default;
        ~ConstIterator()=default;
        ConstIterator& operator++(){
            if(index == list->size){
                throw std::out_of_range("out_of_range");
            }
            index++;
            return *this;
        }

        ConstIterator operator++(int){
            ConstIterator iter=*this;
            ++*this;
            return iter;
        }

        bool operator==(const ConstIterator& other)const{
            if(list==other.list && this->index == other.index)return true; // list =list ???
            return false;
        }

        bool operator!=(const ConstIterator& other)const{
            return !(*this==other);
        }

        const T& operator*()const{
            if(index < 0 || index >= list->size){
                throw std::out_of_range("out_of_range");
            }
            Node<T>* ptr=list->head;
            int count=0;
            while (count <= index-1){
                ptr=ptr->next;
                count++;
            }
            return ptr->data;
        }

    };

}
