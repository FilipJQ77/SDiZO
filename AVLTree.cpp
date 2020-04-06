#include <iostream>
#include <string>

using std::string;
using std::cout;

/**
 * Klasa reprezentująca drzewo AVL zrobiona z pomocą materiałów dr inż. Jarosława Mierzwy oraz https://github.com/developer0hye/AVLTree-CPP/blob/master/avltree.cpp
 */
class AVLTree {

    class Node {
    public:
        int value;
        int height; //na jakiej wysokości drzewa znajduje się węzeł
        Node *parent;
        Node *left;
        Node *right;

        explicit Node(int val, Node *p = nullptr, Node *l = nullptr, Node *r = nullptr) {
            value = val;
            parent = p;
            left = l;
            right = r;
            height=0;
        }

        void rotateLeft() {
            Node *b = this->right;
            Node *parent = this->parent;
            if (b != nullptr) {
                this->right = b->left;
                b->left = this;
                this->parent = b;
                if (this->right != nullptr) {
                    this->right->parent = this;
                }
                b->parent = parent;
                if (parent != nullptr) {
                    if (this == parent->left) {
                        parent->left = b;
                    } else if (this == parent->right) {
                        parent->right = b;
                    }
                }
            }
        }

        void rotateRight() {
            Node *b = this->left;
            Node *parent = this->parent;
            if (b != nullptr) {
                this->left = b->right;
                b->right = this;
                this->parent = b;
                if (this->left != nullptr) {
                    this->left->parent = this;
                }
                b->parent = parent;
                if (parent != nullptr) {
                    if (this == parent->right) {
                        parent->right = b;
                    } else if (this == parent->left) {
                        parent->left = b;
                    }
                }
            }
        }
    };

    Node *root;

    void removeNodeFromMemory(Node *node) {
        if (node == nullptr)
            return;
        removeNodeFromMemory(node->left);
        removeNodeFromMemory(node->right);
        delete node;
    }

public:

    //todo lepsza implementacja
    string cr;
    string cl;
    string cp;

    explicit AVLTree(int *array = nullptr, int arraySize = 0) {
        root = nullptr;
        for (unsigned int i = 0; i < arraySize; ++i) {
            add(array[i]);
        }
    }

    /**
     * destruktor
     */
    ~AVLTree() {
        removeNodeFromMemory(root);
    }

    //todo to sie chyba nie zmieni
    void add(int number) {
        if (root == nullptr) {
            root = new Node(number, nullptr, nullptr, nullptr);
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
            addFixTree(parent);
            //znalezienie nowego korzenia
            root = newNode;
            while (newNode->parent != nullptr) {
                newNode = newNode->parent;
                root = newNode;
            }
        }
    }

//    char getBalance(Node *node) {
//        if (node == nullptr)
//            return 0;
//        else {
//            return 1+getBalance(node->left)
//        }
//    }

    void addFixTree(Node *node) {

    }

    /**
     * szukanie i usuwanie danej liczby
     * @param number
     * @return true, jeśli znaleziono i usunięto liczbę, false w przeciwnym wypadku
     */
    bool removeGivenNumber(int number) {
        Node *temp = root;
        while (temp != nullptr) {
            if (number == temp->value) {
                removeGivenElement(temp);
                return true;
            } else {
                if (number < temp->value)
                    temp = temp->left;
                else
                    temp = temp->right;
            }
        }
        return false;
    }

    /**
     * usuwanie już danego elementu drzewa, algorytm
     * @param z
     */
    void removeGivenElement(Node *z) {

    }

    /**
     * wyszukanie podanej liczby w drzewie
     * @param number
     * @return true, jeśli znaleziono liczbę, false, jeśli nie znaleziono liczby
     */
    bool findGivenNumber(int number) {
        Node *temp = root;
        while (temp != nullptr) {
            if (number == temp->value)
                return true;
            else {
                if (number < temp->value)
                    temp = temp->left;
                else
                    temp = temp->right;
            }
        }
        return false;
    }

    /**
     * wyświetlenie drzewa w konsoli
     */
    void print() {
        cr = cl = cp = "  ";
        cr[0] = 218;
        cr[1] = 196;
        cl[0] = 192;
        cl[1] = 196;
        cp[0] = 179;
        printRecursive("", "", root);
        cout << '\n';
    }

    void printRecursive(string sp, string sn, Node *node) {
        if (node != nullptr) {
            string s = sp; //"tekst do wyświetlenia w wierszach pośrednich dla synów"
            if (sn == cr)
                s[s.length() - 2] = ' ';
            printRecursive(s + cp, cr, node->right);
            s = s.substr(0, sp.length() - 2);
//            string value = (node->colour == RED) ? to_string(node->value) + "R" : to_string(node->value) + "B";todo może dodać wyważenie?
            cout << s << sn << node->value << '\n';
            s = sp;
            if (sn == cl)
                s[s.length() - 2] = ' ';
            printRecursive(s + cp, cl, node->left);
        }
    }
};