#include "cinder/app/AppBasic.h"
class Node {
public:
    Node* next;
    Node* prev;
    int posX;
    int posY;
    int speedX;
    int speedY;
    int radius;
    cinder::Color8u color;
    
    void move(int width, int height);
};