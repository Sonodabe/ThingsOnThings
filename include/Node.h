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
    /**
     * Tells you if a specified point is on this ring
     *
     * @param mouseX The x coordinate of the point in question
     * @param mouseY The y coordinate of the point in question
     *
     * @return <code>true</code> if the coordinate falls on this ring, <code>false</code> otherwise.
     **/
    bool onRing(int mouseX, int mouseY);
    
    /**
     * Randomly changes the color of a ring
     **/
    void crazyColor();
    /**
     * Checks if a coordinate is inside this ring
     *
     * @param x The x coordinate of the point in question
     * @param y The y coordiante of the point in question
     *
     * @return <code>true</code> if the point is inside the ring, <code>false</code> otherwise
     **/
    bool inside(int x, int y);
};