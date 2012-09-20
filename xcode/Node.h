class Node {
public:
    Node* next;
    Node* prev;
    int posX;
    int posY;
    int radius;
    cinder::Color8u color;
    void randomizeColor();
};