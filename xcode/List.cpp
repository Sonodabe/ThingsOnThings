#include "List.h"
//Sam: movee isn't a good variable name
void List::moveToFront(Node* current){
    current->prev->next = current->next;
    current->next->prev = current->prev;
    sentinel->next->prev = current;
    current->next = sentinel->next;
    sentinel->next = sentinel->next->prev;
    current->prev = sentinel;
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
	// Sam: played with the colors some...was %156 and %100. 
	// Wasn't sure if there was a reason behind it or not. 
	// Just changed starting colors
    tempNode->color = cinder::Color8u(rand()%199+100, 0, rand()%89+156);
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
			//Sam: I tried to follow what you did here to no avail...
			// but it works. Comment more maybe?
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


