#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "List.h"

using namespace ci;
using namespace ci::app;
using namespace std;



class ThingsOnThingsApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void ThingsOnThingsApp::setup()
{ 
}


void ThingsOnThingsApp::mouseDown( MouseEvent event )
{
}

void ThingsOnThingsApp::update()
{
}

void ThingsOnThingsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( ThingsOnThingsApp, RendererGl )

