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
    //Checks to see if a ring is pressed, if so then it moves it to the front of the list
	void mouseDown( MouseEvent event );	
    //Reversed the order of the list if the Spacebar is pressed
    //Pauses the movement if p is pressed
    void keyDown( KeyEvent event);
	void update();
	void draw();
    void prepareSettings(Settings* settings);
    
private: 
    Surface* mySurface;
    bool run;
};