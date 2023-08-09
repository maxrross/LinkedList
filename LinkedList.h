//
// Created by Max Ross on 2/15/22.
//

#ifndef PROJECT1_LINKEDLIST_H
#define PROJECT1_LINKEDLIST_H
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node
    {
        public:
        Node()
        {
            this->next = nullptr;
            this->prev = nullptr;
        }
        T data;
        Node *next;
        Node *prev;
    };

    LinkedList<T>()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    LinkedList(const LinkedList<T>& list){
        length = 0;
        if(list.length==0){
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* iter;
        iter = list.head;
        while (iter!=nullptr){
            AddTail(iter->data);
            iter=iter->next;
        }
    }

    ~LinkedList(){
        Clear();
    }

    LinkedList<T>& operator=(const LinkedList<T>& list){
        Clear();
        if(list.length==0){
            head = nullptr;
            tail = nullptr;
            return *this;
        }
        Node* iter;
        iter = list.head;
        while (iter!=nullptr){
            AddTail(iter->data);
            iter=iter->next;
        }
        return *this;
    }

    bool operator==(const LinkedList<T>& list){
        Node* temp1 = head;
        Node* temp2 = list.head;
        if (list.length!=this->length){
            return false;
        }
        for (int i=0; i<(int)list.length; i++){
            if(temp1->data!=temp2->data){
                return false;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return true;
    }

    void PrintForwardRecursive(const Node* node) const{
        if (node==tail)
        {
            cout << node->data << endl;
        }
        else {
            cout << node->data << endl;
            PrintForwardRecursive(node->next);
        }
    }

    void PrintReverseRecursive(const Node* node) const{
        if (node==head)
        {
            cout << node->data << endl;
        }
        else {
            cout << node->data << endl;
            PrintReverseRecursive(node->prev);
        }
    }

    unsigned int Remove(const T &data){
        vector<unsigned int> vect;
        Node* temp = head;
        for (unsigned int i = 0; i<length; i++) {
            if (temp->data == data) {
                vect.push_back(i);
            }
            temp = temp->next;
        }
        unsigned int Removed = vect.size();
        for (int j = vect.size()-1; j>=0; j--) {
            RemoveAt(vect[j]);
        }
        return Removed;
    }

    bool RemoveHead(){
        if (length == 0) {
            return false;
        }
        else if (length == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return true;
        }
        else {
            Node* temp = head->next;
            temp->prev = nullptr;
            delete head;
            head = temp;
            length--;
            return true;
        }
    }

    bool RemoveTail(){
        if (length == 0) {
            return false;
        }
        else if (length == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return true;
        }
        else {
            Node* temp = tail->prev;
            temp->next = nullptr;
            delete tail;
            tail = temp;
            length--;
            return true;
        }
    }

    bool RemoveAt(unsigned int index) {
        if (index>=length){
            return false;
        }
        Node *temp = GetNode(index);
        if (temp==head){
            RemoveHead();
            return true;
        } else if (temp==tail){
            RemoveTail();
            return true;
        } else {
            temp->next->prev=temp->prev;
            temp->prev->next=temp->next;
            delete temp;
            length--;
            return true;
        }
    }

    void InsertBefore(Node* node, const T& data){
        Node* temp = head;
        Node* newNode = new Node;
        newNode->data = data;
        for (int i=0; i<(int)length; i++){
            if (temp==node){
                break;
            }
            temp=temp->next;
        }
        temp->prev->next = newNode;
        newNode->prev = temp->prev;
        newNode->next = temp;
        temp->prev = newNode;
    }

    void InsertAfter(Node* node, const T& data){
        Node* temp = head;
        Node* newNode = new Node;
        for (int i=0; i<(int)length; i++){
            if (temp==node){
                break;
            }
            temp=temp->next;
        }
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
        newNode->data = data;
    }

    void InsertAt(const T& data, unsigned int index){
        Node* temp = head;
        Node* newNode = new Node;
        newNode->data = data;
        if(index>length) {
            throw out_of_range("Out of range");
        } else if(index==0){
            temp->next->prev=newNode;
            newNode->next=temp;
            newNode->prev=head->prev;
            head=newNode;
            length++;
        } else if (index==length){
            temp=tail;
            newNode->prev=temp;
            temp->next=newNode;
            tail=newNode;
            length++;
        } else {
            for (int i = 0; i < (int)index; i++) {
                temp = temp->next;
            }
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
            length++;
        }
    }

    void AddHead (const T data)
    {
        if (head==nullptr) {
            head = new Node;
            head->data = data;
            tail = head;
        }
        else
        {
            Node *new_node = new Node;
            new_node->next = head;
            new_node->data = data;
            head->prev = new_node;
            head = head->prev;
        }
        length++;
    }

    void AddTail(const T data)
    {
        Node *new_node = new Node;
        new_node->data = data;
        if (length==0){
            head=new_node;
            tail=new_node;
        }
        else
        {
            new_node->prev = tail;
            new_node->data = data;
            tail->next = new_node;
            tail = tail->next;
        }
        length++;
    }

    unsigned int NodeCount()
    {
        return length;
    }

    void PrintForward()
    {
        Node *point = head;
        while (point != nullptr)
        {
            std::cout << point->data << endl;
            point = point->next;
        }
    }

    void PrintReverse()
    {
        Node *point = tail;
        while (point != nullptr)
        {
            std::cout << point->data << endl;
            point = point->prev;
        }
    }

    void AddNodesHead(const T *data, unsigned int count){
        int final=(int)count-1;
        for (int i=final; i>=0; --i){
            AddHead(data[i]);
            length++;
        }
    }

    void AddNodesTail(const T *data, unsigned int count){
        for (unsigned int i=0; i<count; ++i){
            AddTail(data[i]);
            length++;
        }
    }

    Node* Head() const {
        return head;
    }

    Node* Tail() const {
        return tail;
    }

    Node* Find(const T& data)
    {
        Node* front = head;
        Node* back = tail;
        Node* ptr = nullptr;
        if (front == nullptr && back == nullptr){
            return nullptr;
        }
        while (front <= back)
        {
            if (front->data == data){
                ptr = front;
                break;
            }
            else if (back->data == data)
            {
                ptr = back;
                break;
            }
            front = front->next;
            back = back->prev;
        }
        return ptr;
    }

    const Node* Find(const T& data) const {
        Node* front = head;
        Node* back = tail;
        Node* ptr = nullptr;
        if (front == nullptr && back == nullptr){
            return nullptr;
        }
        while (front <= back)
        {
            if (front->data == data){
                ptr = front;
                break;
            }
            else if (back->data == data)
            {
                ptr = back;
                break;
            }
            front = front->next;
            back = back->prev;
        }
        return ptr;
    }

    void FindAll(vector<Node*>& outData, const T& value) {
        Node *ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == value)
                outData.push_back(ptr);
            ptr = ptr->next;
        }
    }

    T& operator[](unsigned int index){
        if(index>=length) {
            throw out_of_range("Out of range");
        } else {
            Node *ptr = head;
            for (unsigned int i = 0; i < index; i++) {
                ptr = ptr->next;
            }
            return ptr->data;
        }
    }

    const T& operator[](unsigned int index) const{
        if(index>=length) {
            throw out_of_range("Out of range");
        } else {
            Node *ptr = head;
            for (unsigned int i = 0; i < index; i++) {
                ptr = ptr->next;
            }
            return ptr->data;
        }
    }

    Node* GetNode(const unsigned int index){
        if(index>=length) {
            throw out_of_range("Out of range");
        } else {
        Node* ptr = head;
        for (unsigned int i=0; i<index && ptr!=nullptr; i++){
            ptr = ptr->next;
        }
        return ptr;
        }
    }

    const Node* GetNode(const unsigned int index) const{
        if(index>=length) {
            throw out_of_range("Out of range");
        } else {
            Node* ptr = head;
            for (unsigned int i=0; i<index && ptr!=nullptr; i++){
                ptr = ptr->next;
            }
            return ptr;
        }
    }

    void Clear() {
        Node *temp;
        Node *ptr = head;
        while (ptr != nullptr){
            temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

private:
    unsigned int length;
    Node* head;
    Node* tail;
};

#endif //PROJECT1_LINKEDLIST_H
