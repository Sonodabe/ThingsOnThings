#include "Node.h"

class List{
public:
    Node* sentinel;
    void moveToFront(Node* movee);
    void reverse();
    Node* insertNode(Node* prevNode, int posX, int posY);
    Node* onThisRing(int mouseX, int mouseY);
    void resize();
private:
    bool onRing(int mouseX, int mouseY, Node* ring);
};