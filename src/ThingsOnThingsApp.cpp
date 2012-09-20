#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "List.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ThingsOnThingsApp : public AppBasic {
  public:
    List* myList;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void prepareSettings(Settings* settings);
    
private: 
    Surface* mySurface;
};

//Screen dimensions
static const int appWidth = 800;
static const int appHeight = 600;
static const int textureSize = 1024;

void display(List* myList, uint8_t* data);
void drawCircle(int posX, int posY, int radius, uint8_t* data, Color8u color, int repeats);



void ThingsOnThingsApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void ThingsOnThingsApp::setup()
{ 
    mySurface = new Surface(textureSize, textureSize, false);
    myList = new List;
    myList->sentinel = new Node;
    myList->sentinel->next = myList->sentinel;
    myList->sentinel->prev = myList->sentinel;
    Node* lastNode;
    lastNode = myList->insertNode(myList->sentinel, appWidth/6, appHeight/2, appWidth/6);
    lastNode = myList->insertNode(lastNode, 2*appWidth/6, appHeight/2, appWidth/6);
    lastNode = myList->insertNode(lastNode, 3*appWidth/6, appHeight/2, appWidth/6);
    lastNode = myList->insertNode(lastNode, 4*appWidth/6, appHeight/2, appWidth/6);
    lastNode = myList->insertNode(lastNode, 5*appWidth/6, appHeight/2, appWidth/6);

}

void ThingsOnThingsApp::mouseDown( MouseEvent event )
{
    int mouseX = event.getX();
    int mouseY = event.getY();
    Node* clicked = myList->onThisRing(mouseX, mouseY);
    if(clicked != 0)
        myList->moveToFront(clicked);
}

void ThingsOnThingsApp::update()
{
    uint8_t* data = (*mySurface).getData();    
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
        drawCircle(current->posX, current->posY, current->radius, data, current->color, current->ringThickness);
        current = current->next;
    }    
    myList->reverse();
}

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
        angle+=.001;
    }
    drawCircle(posX, posY, radius-1, data, color, repeats-1);
}

CINDER_APP_BASIC( ThingsOnThingsApp, RendererGl )

