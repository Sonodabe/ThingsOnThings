#include "Node.h"

class List{
public:
    Node* sentinel;
    void moveToFront(Node* movee);
    void reverse();
    Node* insertNode(Node* prevNode, int posX, int posY, int radius);
    Node* onThisRing(int mouseX, int mouseY);
private:
    bool onRing(int mouseX, int mouseY, Node* ring);
};