//Brandon Sonoda
//Homework 2: things on things on things on things


#include "ThingsOnThingsApp.h"

/*
 Requirements met:
    A: node, list class structure
    C: mousedown()
    D: myList->moveAll();
    E: Press spacebar
    random thought: p stops motion
    H: myList->resize();
    
    K: myList->crazyInsideColor();
 */

//Screen dimensions
static const int appWidth = 750;
static const int appHeight = 750;
static const int textureSize = 1024;

void display(List* myList, uint8_t* data);
void clearScreen(uint8_t* data);
void drawCircle(int posX, int posY, int radius, uint8_t* data, Color8u color, int repeats);



void ThingsOnThingsApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void ThingsOnThingsApp::setup()
{ 
    run = true;
    mySurface = new Surface(textureSize, textureSize, false);
    myList = new List;
    myList->sentinel = new Node;
    myList->sentinel->next = myList->sentinel;
    myList->sentinel->prev = myList->sentinel;
    /* The sentinel radius will be the max radius*/
    myList->sentinel->radius = appWidth/6;
    myList->sentinel->posX = appWidth/2;
    myList->sentinel->posY = appHeight/2;

    Node* lastNode;
    lastNode = myList->insertNode(myList->sentinel, appWidth/4, appHeight/3);
    lastNode = myList->insertNode(lastNode, 3*appWidth/4, 2*appHeight/3);
    lastNode = myList->insertNode(lastNode, 3*appWidth/4, appHeight/3);
    lastNode = myList->insertNode(lastNode, appWidth/4, 2*appHeight/3);
    lastNode = myList->insertNode(lastNode, appWidth/2, 2*appHeight/3);
    lastNode = myList->insertNode(lastNode, appWidth/2, appHeight/3);

}

void ThingsOnThingsApp::mouseDown( MouseEvent event )
{
    int mouseX = event.getX();
    int mouseY = event.getY();
    Node* clicked = myList->onThisRing(mouseX, mouseY);
    if(clicked != 0)
        myList->moveToFront(clicked);
}

void ThingsOnThingsApp::keyDown( KeyEvent event ){
    int code = event.getCode();
    int keyChar = event.getChar();
    if(code == KeyEvent::KEY_SPACE){
        myList->reverse();
    } else {
        if(keyChar == 'P' || keyChar == 'p'){
            run = !run;
        }
    }
    
}

void ThingsOnThingsApp::update()
{
    uint8_t* data = (*mySurface).getData();
    clearScreen(data);
    myList->resize();
    if(run){
        myList->moveAll(appWidth, appHeight);
    }
    myList->crazyInsideColor();
    display(myList, data);
}

void ThingsOnThingsApp::draw()
{
    gl::draw(*mySurface);
}


void display(List* myList, uint8_t* data){
    myList->reverse();
    Node* current = myList->sentinel->next;
    while(current!= myList->sentinel){
        drawCircle(current->posX, current->posY, current->radius, data, current->color, current->radius/3);
        current = current->next;
    }    
    myList->reverse();
}

void clearScreen(uint8_t* data){
    for(int i = 0; i<textureSize*appWidth*3; i++)
        data[i] = 30;

}
//Sam: what is repeats for?
void drawCircle(int posX, int posY, int radius, uint8_t* data, Color8u color, int repeats){
    if(repeats<=0)
        return;
    int tempX, tempY;
    double angle = 0;
    
    int index;
    
    while(angle <= 6.3){
        tempX = posX+radius*sin(angle+3.14/2);
        tempY = posY+radius*sin(angle);
        index = 3*(tempY*textureSize+tempX);
        
        if(index>=0 && index <appHeight*textureSize*3){
            data[index] = color.r;
            data[index+1] = color.g;
            data[index+2] = color.b;
        }  
        angle+=.01;
    }
    drawCircle(posX, posY, radius-1, data, color, repeats-1);
}

CINDER_APP_BASIC( ThingsOnThingsApp, RendererGl )

