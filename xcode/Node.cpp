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