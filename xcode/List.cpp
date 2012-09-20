#include "List.h"

void List::moveToFront(Node* movee){
    movee->prev->next = movee->next;
    movee->next->prev = movee->prev;
    sentinel->next->prev = movee;
    movee->next = sentinel->next;
    sentinel->next = sentinel->next->prev;
    movee->prev = sentinel;
}

void List::reverse(){
    Node* cur = sentinel;
    Node* temp;
    
    do {
        temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }while(cur != sentinel);
}

Node* List::insertNode(Node* prevNode, int posX, int posY, int radius){
    Node* tempNode = new Node;
    tempNode->next = prevNode->next;
    tempNode->prev = prevNode;
    prevNode->next = tempNode;
    tempNode->next->prev = tempNode;
    tempNode->posX = posX;
    tempNode->posY = posY;
    tempNode->radius = radius;
    tempNode->color = cinder::Color8u(rand()%256, rand()%256, rand()%256);
    tempNode->ringThickness = 50;
    
    return tempNode;
}


bool List::onRing(int mouseX, int mouseY, Node* ring){
    int deltaX = mouseX-ring->posX;
    int deltaY = mouseY-ring->posY;
    int distance = sqrt(deltaX*deltaX+deltaY*deltaY);
    return(distance <= ring->radius  && distance >= ring->radius-ring->ringThickness);
}

Node* List::onThisRing(int mouseX, int mouseY){
    Node* current = sentinel->next;
    while(current!=sentinel){
        if(onRing(mouseX, mouseY, current))
            return current;
        current = current->next;
    }    
    return 0;
}


