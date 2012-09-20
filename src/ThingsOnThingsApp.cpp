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
bool onRing(int mouseX, int mouseY, int circleX, int circleY, int radius);
void drawCircle(int posX, int posY, int radius, uint8_t* data, Color8u color, int repeats);
//bool onAnyRing(int mouseX, int mouseY, Node* sentinel);
Node* onThisRing(int mouseX, int mouseY, Node* sentinel);
void moveToFront(Node* movee, Node* sentinel);
void reverse(Node* sentinel);



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
    sentinel->prev = sentinel;
    insertNode(sentinel->next->next, appWidth/2, appHeight/2, 250);
    insertNode(sentinel, appWidth/3, appHeight/2, 250);
    insertNode(sentinel->next, 2*appWidth/3, appHeight/2, 250);

    

         
}

void ThingsOnThingsApp::mouseDown( MouseEvent event )
{
    int mouseX = event.getX();
    int mouseY = event.getY();
    Node* clicked = onThisRing(mouseX, mouseY, sentinel);
    if(clicked != NULL)
        moveToFront(clicked, sentinel);
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

//bool onAnyRing(int mouseX, int mouseY, Node* sentinel){
//    bool on = false;
//    Node* current = sentinel->next;
//    while(current!=sentinel && !on){
//        if(onRing(mouseX, mouseY, current->posX, current->posY, current->radius))
//            on = true;
//        current = current->next;
//    }    
//    return on;
//}


Node* onThisRing(int mouseX, int mouseY, Node* sentinel){
    Node* current = sentinel->next;
    while(current!=sentinel){
        if(onRing(mouseX, mouseY, current->posX, current->posY, current->radius))
            return current;
        current = current->next;
    }    
    return NULL;
}

void insertNode(Node* prevNode, int posX, int posY, int radius){
    Node* tempNode = new Node;
    tempNode->next = prevNode->next;
    tempNode->prev = prevNode;
    prevNode->next = tempNode;
    tempNode->next->prev = tempNode;
    tempNode->posX = posX;
    tempNode->posY = posY;
    tempNode->radius = radius;
    tempNode->color = Color8u(rand()%256, rand()%256, rand()%256);
}

void reverse(Node* sentinel){
    Node* cur = sentinel;
    Node* temp;
    
    do {
        temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }while(cur != sentinel);
}

void display(Node* sentinel, uint8_t* data){
    reverse(sentinel);
    Node* current = sentinel->next;
    while(current!=sentinel){
        drawCircle(current->posX, current->posY, current->radius, data, current->color, ringThickness);
        current = current->next;
    }    
    reverse(sentinel);
}

bool onRing(int mouseX, int mouseY, int circleX, int circleY, int radius){
    int distance = sqrt((mouseX-circleX)*(mouseX-circleX)+(mouseY-circleY)*(mouseY-circleY));
    return(distance <= radius  && distance >= radius-ringThickness);
    
}

void moveToFront(Node* movee, Node* sentinel){
    movee->prev->next = movee->next;
    movee->next->prev = movee->prev;
    sentinel->next->prev = movee;
    movee->next = sentinel->next;
    sentinel->next = sentinel->next->prev;
    movee->prev = sentinel;
    
    
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

