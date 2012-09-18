#include "Node.h"
#include "List.h"

void List::initialize(){
    sentinel = new Node();
    listCount = 0;
}

void List::insertNode(Node* pointer, int data){
    Node* tempNode = new Node;
    
    tempNode->data = data;
    tempNode->next = pointer->next;
    pointer->next = tempNode;
    
    listCount++;
}

