#include <iostream>
#include <string>

using namespace std;

enum nodeColour {
    RED, BLACK
};

/**
 * Klasa reprezentująca drzewo czerwono-czarne, stworzona z pomocą https://en.wikipedia.org/wiki/Red–black_tree
 */
class RedBlackTree {

    string cr;
    string cl;
    string cp;//todo lepsza implementacja tego

    class Node {
    public:
        int value;
        Node *parent;
        Node *left;
        Node *right;
        nodeColour colour;

        explicit Node(int val, Node *p = nullptr, Node *l = nullptr, Node *r = nullptr, nodeColour givenColour = RED) {
            value = val;
            parent = p;
            left = l;
            right = r;
            colour = givenColour;
        }
    };

    Node *root;

public:

    RedBlackTree(int *array = nullptr, int arraySize = 0) {
        cr = cl = cp = "  ";//todo leppiej
        cr[0] = 218;
        cr[1] = 196;
        cl[0] = 192;
        cl[1] = 196;
        cp[0] = 179;
        root = nullptr;
        for (unsigned int i = 0; i < arraySize; ++i) {
            add(array[i]);
        }
    }

    ~RedBlackTree() {
        //todo important
    }

    void add(int number) {
        if (root == nullptr) {
            root = new Node(number, nullptr, nullptr, nullptr, BLACK);
        } else {
            Node *parent;
            Node *placeToAdd = root;
            do {
                parent = placeToAdd;
                if (number < parent->value)
                    placeToAdd = parent->left;
                else placeToAdd = parent->right;
            } while (placeToAdd != nullptr);
            Node *newNode = new Node(number, parent);
            if (number < parent->value)
                parent->left = newNode;
            else
                parent->right = newNode;
        }
    }

    void remove(int number) {

    }

    void findGivenNumber(int number) {

    }

    /**
     * wyświetlenie drzewa w konsoli, kolory węzłów są oznaczane przez literę R (red) lub B (black) na końcu liczby
     */
    void print() {
        printRecursive("", "", root);
    }

    void printRecursive(string sp, string sn, Node *node) {
        if (node != nullptr) {
            string s = sp; //"tekst do wyświetlenia w wierszach pośrednich dla synów"
            if (sn == cr)
                s[s.length() - 2] = ' ';
            printRecursive(s + cp, cr, node->right);
            s = s.substr(0, sp.length() - 2);
            string value = (node->colour == RED) ? to_string(node->value) + "R" : to_string(node->value) + "B";
            cout << s << sn << value << endl;
            s = sp;
            if (sn == cl)
                s[s.length() - 2] = ' ';
            printRecursive(s + cp, cl, node->left);
        }
    }
};