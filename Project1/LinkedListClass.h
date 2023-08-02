//
// Created by Justin Galin on 9/29/22.
//

#ifndef PROJECT1_LINKEDLISTCLASS_H
#define PROJECT1_LINKEDLISTCLASS_H
#include <iostream>
#include <stdexcept>
#include <vector>
//#include "leaker.h"

using namespace std;

template <typename T>
class LinkedList {

public:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node()
        {
            next = nullptr;
        };
    };
    unsigned int nodeCount = 0;
    Node* headNode = nullptr;
    Node* tailNode = nullptr;

    //Behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
//
//    // Accessors
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;

    //Insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail( const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    //Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T&data);
    bool RemoveAt(unsigned int index);
    void Clear();

    //Operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator ==(const LinkedList<T>& rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    //Construction / Destruction
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

};
// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list){
    Node* current = list.headNode;
    Node* oldNode;
    while (current->next != nullptr) {
        //Create memory for a new node
        Node *newNode = new Node();
        nodeCount++;
        if (nodeCount == 1)
        {
            headNode = newNode;
            newNode->prev = nullptr;
        } else
        {
            newNode->prev = oldNode;
            oldNode->next = newNode;
        }
        newNode->data = current->data;
        current = current->next;
        oldNode = newNode;
    }
    //Case for last Node
    Node *newNode = new Node();
    nodeCount++;
    if (nodeCount == 1)
    {
        headNode = newNode;
        newNode->prev = nullptr;
    } else
    {
        newNode->prev = oldNode;
        oldNode->next = newNode;
    }
    newNode->data = current->data;
    tailNode = newNode;
}


// Destructor
template <typename T>
LinkedList<T>::~LinkedList(){
    Node* current = headNode;
    Node* temp;
    if (current == nullptr)
    {
        return;
    } else
    {
        while (current->next != nullptr)
        {
            temp = current;
            current = current->next;
            delete temp;
            nodeCount--;
        }
        //Deletes last node
        delete current;
        nodeCount--;
    }

}

//Behaviors
template <typename T>
void LinkedList<T>::PrintForward() const {

    //Condition for empty list (MAY NEED TO FIX FOR SUBMISSION)
    if (headNode == nullptr)
    {
        try
        {
            throw 5;
        }
        catch (int)
        {
            cout << "No Nodes in List" << endl;
        }
    }

    Node* current = headNode;
    while (current->next != nullptr)
    {
        cout << current->data << endl;
        current = current->next;
    }
    cout << current->data << endl;

}

template <typename T>
void LinkedList<T>::PrintReverse() const {
    // iterate through list to find the end
    Node* current = tailNode;
    while (current->prev != nullptr)
    {
        cout << current->data << endl;
        current = current->prev;
    }
    cout << current->data << endl;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const{
    cout << node->data << endl;
    if (node->next == nullptr)
    {
        return;
    }
    PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const{
    cout << node->data << endl;
    if (node->prev == nullptr)
    {
        return;
    }
    PrintReverseRecursive(node->prev);
}


//Accesors
//MIGHT NEED TO FIX TO START AT 0
template <typename T>
unsigned int LinkedList<T>::NodeCount() const{
//    Node* current = headNode;
//    unsigned int counter = 1;
//    while (current->next != nullptr)
//    {
//        current = current->next;
//        counter ++;
//    }
//    return counter;
    return nodeCount;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const{
    //List Traversal
    Node* current = headNode;
    while (current->next != nullptr)
    {
        //For every node check to see if it matches what youre looking for, if it does then data the pointer to the node in an ouput vector
        if (current->data == value)
        {
            outData.push_back(current);
        }
        current = current->next;
    }
    if (current->data == value)
    {
        outData.push_back(current);
    }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
    Node* current = headNode;

    //Condition for one node
    if (this->NodeCount() == 1)
    {
        if (current->data == data) {
            return current;
        }
    }

//Traverse the list looking for current->data == data
    while (current->next != nullptr)
    {
        //For every node check to see if it matches what youre looking for, if it does then data the pointer to the node in an ouput vector
        if (current->data == data)
        {
            //Stop and return a pointer to that node when its found
            return current;
            break;
        }
        current = current->next;
    }
//Return nullptr if is doesn't exist
    return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
    Node* current = headNode;

    //Condition for one node
    if (this->NodeCount() == 1)
    {
        if (current->data == data) {
            return current;
        }
    }

//Traverse the list looking for current->data == data
    while (current->next != nullptr)
    {
        //For every node check to see if it matches what youre looking for, if it does then data the pointer to the node in an ouput vector
        if (current->data == data)
        {
            //Stop and return a pointer to that node when its found
            return current;
            break;
        }
        current = current->next;
    }
//Return nullptr if is doesn't exist
    return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const{
    //List Traversal
    Node* current = headNode;
    unsigned int counter = 0;
    while (current->next != nullptr)
    {
        //For every node check to see if it matches what you're looking for, if it does then data the pointer to the node in an ouput vector
        if (counter == index)
        {
            return current;
        }
        current = current->next;
        counter++;
    }
    if (counter == index)
    {
        return current;
    }
    else{
        throw out_of_range("Out of Range");
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    //List Traversal
    Node* current = headNode;
    unsigned int counter = 0;
    while (current->next != nullptr)
    {
        //For every node check to see if it matches what you're looking for, if it does then data the pointer to the node in an ouput vector
        if (counter == index)
        {
            return current;
        }
        current = current->next;
        counter++;
    }
    if (counter == index)
    {
        return current;
    }
    else{
        throw out_of_range("Out of Range");
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head(){
    return headNode;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const{
    return headNode;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail(){
    return tailNode;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const{
    return tailNode;
}







// Insertion Operations
template <typename T>
void LinkedList<T>::AddHead(const T& data){
    Node* newNode = new Node();
    nodeCount++;
    newNode->data = data;
    newNode->prev = nullptr;
    if (headNode != nullptr)
    {
        newNode->next = headNode;
        headNode->prev = newNode;
    } else
    {
        tailNode = newNode;
    }
    headNode = newNode;
}

template <typename T>
void LinkedList<T>::AddTail(const T &data) {
    Node *newNode = new Node();
    newNode->data = data;
    // Case if 0 nodes exist
    if (nodeCount == 0)
    {
        newNode->prev = nullptr;
        headNode = newNode;
        //Case if 1 Node exists
    } else if (nodeCount == 1)
    {
        headNode->next = newNode;
        newNode->prev = headNode;
        //Case if 2 or more nodes exist
    } else
    {
        newNode->prev = tailNode;
        tailNode->next = newNode;
    }
    tailNode = newNode;
    nodeCount++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count){

    for (int i=count-1; i >= 0; i--)
    {
        //Create memory for a new node
        Node* newNode = new Node();
        nodeCount++;
        //Assigning tail node if list is empty
        if (headNode == nullptr)
        {
            tailNode = newNode;
        }

        if (headNode != nullptr)
        {
            //Direct the new node to point to the header node
            newNode->next = headNode;
            //Direct the Head Nodes prev to the new node as long as its not the first Node
            headNode->prev = newNode;
        }
        //Copy the data from the array into the new node
        newNode->data = data[i];
        //Reassign the new node as the header
        headNode = newNode;

    }
    headNode->prev = nullptr;

}

template <typename T>
void LinkedList<T>::AddNodesTail( const T* data, unsigned int count)
{
    for (unsigned int i=0; i<count; i++)
    {
        //Make new node
        Node* newNode = new Node();
        nodeCount++;
        //Check to see if list is empty if it is assign head node to first created node
        if (headNode == nullptr)
        {
            headNode = newNode;
        }
        //Have tail node point to the new node as long as list isnt empty
        if (tailNode != nullptr)
        {
            tailNode->next = newNode;
        }
        //Assign the new nodes prev to be the old tail node
        newNode->prev = tailNode;
        //data data in the new node
        newNode->data = data[i];
        //Reassign tail to the new node
        tailNode = newNode;

    }
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
    // Create a new node with data = data
    Node* newNode = new Node();
    nodeCount++;
    newNode->data = data;
    // Check to see if there is a next node if so do next, if not, dont and add tail to the new node
    if (node->next == nullptr)
    {
        tailNode = newNode;
    }else{
        // Assign the node after nexts prev pointer to the new node
        // Assign the new node to point to the node after node
        node->next->prev = newNode;
        newNode->next = node->next;
    }
    // Assign the nodes next node to new node
    node->next = newNode;
    // Assign the new nodes prev to node
    newNode->prev = node;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    //Create new node with data = data
    Node* newNode = new Node();
    nodeCount++;
    newNode->data = data;
    //Check to see if there is a node before node
    //If NO then assign head to it
    if (node->prev == nullptr)
    {
        headNode = newNode;
    }else{
        //If YES then assign the node before nodes next pointer to newNode
        node->prev->next = newNode;
        //Also assign newNodes prev pointer to that node
        newNode->prev = node->prev;
    }
    //Assign nodes prev pointer to new node
    node->prev = newNode;
    //Assign newNodes next pointer to Node
    newNode->next = node;
}


template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    //List Traversal
    Node *current = headNode;
    unsigned int counter = 0;
    while (current->next != nullptr)
    {
        if (counter == index)
        {
            this->InsertBefore(current, data);
            return;
        }
        current = current->next;
        counter++;
    }
    //Condtition for index being last existing node
    if (counter == index)
    {
        this->InsertBefore(current, data);
    }else if (counter+1 == index)
    {
        this->InsertAfter(current, data);
    }
    else{
        throw out_of_range("Out of range");
    }

}





// Removal Operations

//STILL NEED TO TEST
template <typename T>
bool LinkedList<T>::RemoveHead(){
    //As long as there is one node
    if (headNode != nullptr)
    {

        if (this->NodeCount() == 1)
        {
            delete headNode;
            nodeCount--;
            headNode = nullptr;
            tailNode = nullptr;
            return true;
        } else{
            //If there is more than one node
            Node* current = headNode;
            //Assign head to the second pointer
            headNode = current->next;
            //Assign the second nodes prev pointer to null
            current->next->prev = nullptr;
            //Delete the head pointer
            delete current;
            nodeCount--;
            return true;
        }


    }
    //If there are 0 nodes
    return false;

}

template <typename T>
bool LinkedList<T>::RemoveTail(){
    //As long as there is one node
    if (headNode != nullptr)
    {
        if (this->NodeCount() == 1)
        {
            delete headNode;
            nodeCount--;
            headNode = nullptr;
            tailNode = nullptr;
            return true;
        } else{
            //If there is more than one node
            Node* current = tailNode;
            //Assign head to the second to last node
            tailNode = current->prev;
            //Assign the second nodes prev pointer to null
            current->prev->next = nullptr;
            //Delete the head pointer
            delete current;
            nodeCount--;
            return true;
        }


    }
    //If there are 0 nodes
    return false;

}

template <typename T>
unsigned int LinkedList<T>::Remove(const T&data){
    //List Traversal
    Node *current = headNode;
    unsigned int counter = 0;
    while (current->next != nullptr)
    {
        if (current->data == data)
        {
            //Condition for head pointer
            if (current->prev == nullptr)
            {
                this->RemoveHead();
                current = current->next;
            } else
                //Condition for anything in the middle
            {
                //Direct prev next pointer to the next node
                current->prev->next = current->next;
                //Next prev should point to the prev node
                current->next->prev = current->prev;
                //Delete the current node
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            counter++;
            nodeCount--;
        }else
        {
            current = current->next;
        }
    }
    //Check the last node
    if (current->data == data)
    {
        this->RemoveTail();
        counter ++;
    }
    return counter;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index){
    Node* current = headNode;
    unsigned int counter = 0;
    while (current->next != nullptr)
    {
        //Condition for head node
        if (index == 0)
        {
            this->RemoveHead();
            return true;
        } else if (counter == index)
            //Condition for middle node
        {
            //Direct prev next pointer to the next node
            current->prev->next = current->next;
            //Next prev should point to the prev node
            current->next->prev = current->prev;
            //Delete the current node
            delete current;
            nodeCount--;
            return true;
        }

        current = current->next;
        counter++;
    }
    if (counter == index)
    {
        this->RemoveHead();
        return true;
    }
    return false;
}

template <typename T>
void LinkedList<T>::Clear(){
    //Traverse the list
    Node* current = headNode;
    while (current->next != nullptr)
    {
        current = current->next;
        delete current->prev;
    }
    delete current;
    headNode = nullptr;
    tailNode = nullptr;
    nodeCount = 0;
}






//OPERATORS
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const{
    //Traverse the list
    Node* current = headNode;
    unsigned int counter = 0;
    while (current->next != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->next;
        counter++;
    }
    //Condition for tail node
    if (counter == index)
    {
        return current->data;
    }
    throw out_of_range("Out of Range");
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
    //Traverse the list
    Node* current = headNode;
    unsigned int counter = 0;
    while (current->next != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->next;
        counter++;
    }
    //Condition for tail node
    if (counter == index)
    {
        return current->data;
    }
    throw out_of_range("Out of Range");
}



template <typename T>
bool LinkedList<T>::operator ==(const LinkedList<T>& rhs) const{
    //Traverse the list
    Node* current = headNode;
    unsigned int counter = 0;
    if (this->NodeCount() != rhs.NodeCount())
    {
        return false;
    }
    while (current->next != nullptr)
    {
        if (current->data != rhs[counter])
        {
            return false;
        }
        //cout << current->data << rhs[counter];
        current = current->next;
        counter++;
    }
    //cout << current->data << rhs[counter];
    if (current->data != rhs[counter])
    {
        return false;
    }
    return true;
}


template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs){
    T* array = new T[rhs.nodeCount];
    Node* current = rhs.headNode;
    //Make an array with the same data data as the lhs
    for (unsigned int i = 0; i < rhs.NodeCount(); i++)
    {
        array[i] = current->data;
        current = current->next;
    }
    //Get rid of the old data in this
    this->Clear();
    //Add the array of data from rhs to lhs
    this->AddNodesHead(array,rhs.NodeCount());
    delete[] array;
    return *this;
}

//template <typename T>
//LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
//    Node* currentRHS = rhs.headNode;
//    cout << currentRHS->data;
//    Node* currentLHS = headNode;
//    cout << this->Head()->data;
//    //Check if lists are already ==
//    if (this == rhs)
//    {
//        return this;
//    } else
//        //If not, iteratre through checking if lhs = rhs and if it doesnt assign lhs to rhs until you hit a next = nullptr
//    //{
//        while (currentRHS->next != nullptr)
//        {
//            if (currentLHS->next != nullptr)
//            {
//                currentLHS->data = currentRHS->data;
//            //If at the end of lhs data the data of the lhs tail as rhs current and make a new node with data from rhs
//            } else
//            {
//                //data rhs data into lhs node
//                currentLHS->data = currentRHS->data;
//                //Make a new node
//                Node* newNode = new Node();
//                //Leave the new node empty so it can be filled in by the next iteration
//                //Assign it as the tail nodes next
//                this->tailNode->next = newNode;
//                //Assign its prev to the tail node
//                newNode->prev = this->tailNode;
//                //make it the tail node
//                this->tailNode = newNode;
//                //increase nodecount
//                this->nodeCount++;
//            }
//            currentRHS = currentRHS->next;
//            currentLHS = currentLHS->next;
//
//        }
//        //Fill in the empty box
//        currentLHS->data = currentRHS->data;
//        //Delete extra LHS Nodes if LHS is longer than RHS
//        if (currentLHS != nullptr and currentLHS->next != nullptr)
//        {
//            while (this->tailNode->data != currentLHS->data or this->nodeCount != rhs.nodeCount)
//            {
//                this->RemoveTail();
//            }
//        }
//    //}
//
//
//}
//NEW IDEA FOR ABOVE FUNCTION
//Check if both lists have nullptr
//If they dont then create and assign nodes for lhs from the values of rhs if rhs is bigger
//Delete the extra nodes if lhs is bigger

template <typename T>
LinkedList<T>::LinkedList(){
    headNode = nullptr;
    tailNode = nullptr;
}


#endif //PROJECT1_LINKEDLISTCLASS_H
