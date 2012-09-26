#include "Node.h"


// Sam: In this method, this is just where I started.
// I'm not going to go through and change them all, but
// your variable names might be easier to read if you used the 
// under score. I changed new_X and new_Y as examples

void Node::move(int width, int height){
    int new_X = posX+speedX;
    //Sam: moved this up here b/c variable delcarations should go together
	int new_Y = posY+speedY;
    
	if(new_X-radius < 0){
        posX = radius;
        speedX = abs(speedX);
    } else{
        if(new_X+radius > width){
            posX = width-radius;
            speedX = -abs(speedX);
        }else{
            posX = new_X;
        }
    }
    
    
    
    if(new_Y-radius < 0){
        posY = radius;
        speedY = abs(speedY);
    } else{
        if(new_Y+radius > height){
            posY = height-radius;
            speedY = -abs(speedY);
        }else{
            posY = new_Y;
        }
    }
}

bool Node::onRing(int mouseX, int mouseY){
    int deltaX = mouseX-posX;
    int deltaY = mouseY-posY;
	//Sam: Cast this as a double because when I tried to run it, got an error
	// saying it could be multiple different calls of sqrt
    int distance = sqrt((double)deltaX*deltaX+deltaY*deltaY);
    return(distance <= radius  && distance >= 2*radius/3);
}

void Node::crazyColor(){
    color = cinder::Color8u(rand()%256, rand()%256, rand()%256);
}
//Sam: this is almost the exact same code as onRing. Waste of code. You could have used this to write the onRing
bool Node::inside(int x, int y){
    int deltaX = abs(x-posX);
    int deltaY = abs(y-posY);
	// Sam: same things as above here
    int distance = sqrt((double)deltaX*deltaX+deltaY*deltaY);
    return distance <= radius;
}

int distance(