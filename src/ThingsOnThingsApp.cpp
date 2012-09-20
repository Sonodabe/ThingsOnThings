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
void randomizeColor();
bool onRing(int mouseX, int mouseY, int circleX, int circleY, int radius);
void drawCircle(int posX, int posY, int radius, uint8_t* data, int repeats);
bool onAnyRing(int mouseX, int mouseY, Node* sentinel);
int absoluteValue(int num);
int red = 255;
int green = 0;
int blue = 100;
int ringThickness = 100;


void ThingsOnThingsApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void ThingsOnThingsApp::setup()
{ 
    mySurface = new Surface(textureSize, textureSize, false);
    sentinel = new Node;
    sentinel->next = sentinel;
    insertNode(sentinel, appWidth/3, appHeight/2, 250);
    insertNode(sentinel->next, 2*appWidth/3, appHeight/2, 250);
    

         
}

void ThingsOnThingsApp::mouseDown( MouseEvent event )
{
    int mouseX = event.getX();
    int mouseY = event.getY();
    if(onAnyRing(mouseX, mouseY, sentinel))
        randomizeColor();
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

bool onAnyRing(int mouseX, int mouseY, Node* sentinel){
    bool on = false;
    Node* current = sentinel->next;
    while(current!=sentinel && !on){
        if(onRing(mouseX, mouseY, current->posX, current->posY, current->radius))
            on = true;
        current = current->next;
    }    
    return on;
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
        drawCircle(current->posX, current->posY, current->radius, data, ringThickness);
        current = current->next;
    }    
}

bool onRing(int mouseX, int mouseY, int circleX, int circleY, int radius){
    int distance = sqrt((mouseX-circleX)*(mouseX-circleX)+(mouseY-circleY)*(mouseY-circleY));
    return(distance <= radius  && distance >= radius-ringThickness);
    
}

void randomizeColor(){
    red = rand()%256;
    green = rand()%256;
    blue = rand()%256;
}

int absoluteValue(int num){
    if(num>0)
        return num;
    return -num;
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
        index = 3*(tempY*textureSize+tempX);
        
        if(index>=0 && index <appHeight*textureSize*3){
            data[index] = red;
            data[index+1] = green;
            data[index+2] = blue;
        }  
        angle+=.01;
    }
    drawCircle(posX, posY, radius-1, data, repeats-1);
}

CINDER_APP_BASIC( ThingsOnThingsApp, RendererGl )

