#include "Node.h"

void Node::move(int width, int height){
    int newX = posX+speedX;
    
    if(newX-radius < 0){
        posX = radius;
        speedX = abs(speedX);
    } else{
        if(newX+radius > width){
            posX = width-radius;
            speedX = -abs(speedX);
        }else{
            posX = newX;
        }
    }
    
    int newY = posY+speedY;
    
    if(newY-radius < 0){
        posY = radius;
        speedY = abs(speedY);
    } else{
        if(newY+radius > height){
            posY = height-radius;
            speedY = -abs(speedY);
        }else{
            posY = newY;
        }
    }
}

bool Node::onRing(int mouseX, int mouseY){
    int deltaX = mouseX-posX;
    int deltaY = mouseY-posY;
    int distance = sqrt(deltaX*deltaX+deltaY*deltaY);
    return(distance <= radius  && distance >= 2*radius/3);
}

void Node::crazyColor(){
    color = cinder::Color8u(rand()%256, rand()%256, rand()%256);
}

bool Node::inside(int x, int y){
    int deltaX = abs(x-posX);
    int deltaY = abs(y-posY);
    int distance = sqrt(deltaX*deltaX+deltaY*deltaY);
    return distance <= radius;
}