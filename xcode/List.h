#include "Node.h"

class List{
public:
    /*The sentinel node is just a place holder to determine the beginning of this list */
    Node* sentinel;
    /**
     * Moves a specified node to the front of the list, shifting all the other nodes accordingly
     *
     * @param movee The node that will be moved to the front of this list.
     **/
    void moveToFront(Node* movee);
    /**
     * Completely reverses the list. This is done by going through the list and
     * switching the nodes' prev and next data members
     *
     **/
    void reverse();
    
    /**
     * Inserts a node into the list with a specified place, x coordinate and y coordinate
     *
     * @param prevNode The node that this node will follow
     * @param posX The new node's x coordinate
     * @param posY The new node's y coordinate
     **/
    Node* insertNode(Node* prevNode, int posX, int posY);
    /**
     * Tells you which ring a specified point falls on (returns top ring)
     *
     * @param mouseX The x coordinate of the point in question
     * @param mouseY The y coordinate of the point in question
     *
     * @return The first ring that the point falls on 0 if not on any ring.
     **/
    Node* onThisRing(int mouseX, int mouseY);
    /**
     * Makes the first ring the largest and each subsequent ring smaller
     **/
    void resize();
    /**
     * Moves all the rings, bouncing off of the walls if they collide
     *
     * @param width The maximum x coordinate that these rings will stay within
     * @param height The maximum y coordinate that these rings will stay within
     **/
    void moveAll(int width, int height);
private:
    /**
     * Tells you if a specified point is on a particular ring
     *
     * @param mouseX The x coordinate of the point in question
     * @param mouseY The y coordinate of the point in question
     * @param ring This is the ring that you are currently checking
     *
     * @return <code>true</code> if the coordinate falls on the ring, <code>false</code> otherwise.
     **/
    bool onRing(int mouseX, int mouseY, Node* ring);
    void bounceNext();
};