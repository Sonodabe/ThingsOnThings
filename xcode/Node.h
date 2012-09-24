#include "cinder/app/AppBasic.h"
class Node {
public:
    Node* next;
    Node* prev;
    //The x coordinate of the CENTER of the ring
    int posX;
    //The y coordinate of the CENTER of the ring
    int posY;
    int speedX;
    int speedY;
    int radius;
    cinder::Color8u color;
    /**
     * Moves this ring bouncing off of the walls if they collide
     *
     * @param width The maximum x coordinate that this ring will stay within
     * @param height The maximum y coordinate that this ring will stay within
     **/
    void move(int width, int height);
};