#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"



class Node {
public:
    Node* next;
    Node* prev;
    int posX;
    int posY;
    int radius;
    cinder::Color8u color;
    void randomizeColor();
    int ringThickness;

};