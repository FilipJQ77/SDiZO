#include <iostream>

using namespace std;

enum nodeColour {
    RED, BLACK
};

class RedBlackTree {

    class Node {
        Node *parent;
        Node *left;
        Node *right;
        nodeColour colour;

        Node() {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            colour = RED;
        }

    };

    /**
     * wyświetlenie drzewa w konsoli
     */
    void print(){

    }

};