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

Node* List::insertNode(Node* prevNode, int posX, int posY){
    Node* tempNode = new Node;
    tempNode->next = prevNode->next;
    tempNode->prev = prevNode;
    prevNode->next = tempNode;
    tempNode->next->prev = tempNode;
    tempNode->posX = posX;
    tempNode->posY = posY;
    tempNode->radius = sentinel->radius;
    tempNode->color = cinder::Color8u(rand()%156+100, 0, rand()%100+156);
    tempNode->speedX = rand()%2+1;
    tempNode->speedY = rand()%2+1;
    
    return tempNode;
}

void List::resize(){
    Node* current = sentinel->next;
    double factor = 1;
    while(current!=sentinel){
        current->radius = (int)(factor*sentinel->radius);
        factor*=.75;
        current = current->next;
    }    
}

void List::crazyInsideColor(){
    Node* current = sentinel->next;
    while(current!=sentinel){
        Node* temp = sentinel->next;
        while(temp!=sentinel){
            if(current->inside(temp->posX+temp->radius, temp->posY+temp->radius) &&
               current->inside(temp->posX-temp->radius, temp->posY-temp->radius))
                temp->crazyColor();
            temp = temp->next;
        } 
        current = current->next;
    }
}

void List::moveAll(int width, int height){
    Node* current = sentinel->next;
    while(current!=sentinel){
        current->move(width, height);
        current = current->next;
    }  
}

Node* List::onThisRing(int mouseX, int mouseY){
    Node* current = sentinel->next;
    while(current!=sentinel){
        if(current->onRing(mouseX, mouseY))
            return current;
        current = current->next;
    }    
    return 0;
}


