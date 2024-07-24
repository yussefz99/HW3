#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

/// class Sortedlist --------------------------------------------------------

    template <typename T>
    class SortedList {
    public:
         ///constructors and destructor:
         SortedList():head(nullptr),size(0){}

         SortedList(const SortedList<T>& other):head(nullptr),size(other.size){  // add exspation?
             if(size < 0){ ///???????????????????????
                 throw std::out_of_range("out_of_range");
             }
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
             while (head) {
                 Node<T>* temp = head;
                 head = head->next;
                 delete temp;
             }
             if(other.size < 0){ ///?????????????????????????????????????
                 throw std::out_of_range("out_of_range");
             }
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
             if (it.index < 0 || it.index > size) {
                 throw std::out_of_range("out of range");
             }
             if(it.index == size || size == 0)return;
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

        template<class  Condition>
        SortedList<T> filter(Condition cond)const{
            SortedList<T> newlist;
            for(const T& data : *this){
                if(cond(data)){
                    newlist.insert(data);
                }
            }
            return newlist;
        }

        template<class Function>
        SortedList<T> apply(Function Func)const{
            SortedList<T> newlist;
            for(const T& data : *this){
                newlist.insert(Func(data));
            }
            return newlist;
        }

//---------------------------------------------------------
         friend bool operator==(const SortedList<T>& l1 ,const SortedList<T>& l2){
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

        template<typename S>
        struct Node {
            S data;
            Node* next;
            explicit Node(const S& val) : data(val), next(nullptr) {}
        };

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
        ConstIterator(const SortedList* list,int index):index(index),list(list){}
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
            if(index < 0 || index >= list->length()){
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
