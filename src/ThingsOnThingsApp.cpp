#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Node.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ThingsOnThingsApp : public AppBasic {
  public:
    Node* sentinel;
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

void insertNode(Node* prevNode, int posX, int posY, int radius);
void display(Node* sentinel, uint8_t* data);
void drawCircle(int posX, int posY, int radius, uint8_t* data, int repeats);


void ThingsOnThingsApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void ThingsOnThingsApp::setup()
{ 
    mySurface = new Surface(appWidth, appHeight, false);
    sentinel = new Node;
    sentinel->next = sentinel;
    insertNode(sentinel, 600, 190, 100);
    insertNode(sentinel->next, 400, 350, 100);
         
}


void ThingsOnThingsApp::mouseDown( MouseEvent event )
{
}

void ThingsOnThingsApp::update()
{
    uint8_t* data = (*mySurface).getData();
    display(sentinel, data);
}

void ThingsOnThingsApp::draw()
{
    gl::draw(*mySurface);
}

void insertNode(Node* prevNode, int posX, int posY, int radius){
    Node* tempNode = new Node;
    tempNode->next = prevNode->next;
    prevNode->next = tempNode;
    tempNode->posX = posX;
    tempNode->posY = posY;
    tempNode->radius = radius;
}

void display(Node* sentinel, uint8_t* data){
    Node* current = sentinel->next;
    while(current!=sentinel){
        drawCircle(current->posX, current->posY, current->radius, data, 10);
        current = current->next;
    }    
}


void drawCircle(int posX, int posY, int radius, uint8_t* data, int repeats){
    if(repeats<=0)
        return;
    int tempX, tempY;
    double angle = 0;
    
    int index;
    
    while(angle < 6.28){
        tempX = posX+radius*sin(angle+3.14/2);
        tempY = posY+radius*sin(angle);
        index = 3*(tempY*appWidth+tempX);
        
        if(index>=0 && index <appHeight*appWidth*3){
            data[index] = 255;
            data[index+1] = 10;
            data[index+2] = 200;
        }  
        angle+=.02;
    }
    drawCircle(posX, posY, radius-1, data, repeats-1);
}

CINDER_APP_BASIC( ThingsOnThingsApp, RendererGl )

