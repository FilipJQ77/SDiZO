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

    Node *nil;
    Node *root;

    void removeNodeFromMemory(Node *node) {
        if (node == nil)
            return;
        removeNodeFromMemory(node->left);
        removeNodeFromMemory(node->right);
        delete node;
    }

public:

    //todo lepsza implementacja tego
    string cr;
    string cl;
    string cp;

    /**
     * konstruktor tworzący nowe drzewo czerwono-czarne, albo puste, albo wypełnione podaną tablica
     * @param array
     * @param arraySize
     */
    RedBlackTree(int *array = nullptr, int arraySize = 0) {
        nil = new Node(0, nullptr, nullptr, nullptr, BLACK);
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        root = nil;
        for (unsigned int i = 0; i < arraySize; ++i) {
            add(array[i]);
        }
    }

    /**
     * destruktor
     */
    ~RedBlackTree() {
        removeNodeFromMemory(root);
    }

    /**
     * rotacja danego węzła w lewo, jeśli jest możliwa
     * @param a
     */
    void rotateLeft(Node *a) {
        if (a == nil)
            return;
        Node *b = a->right;
        Node *parent = a->parent;
        if (b != nil) {
            a->right = b->left;
            b->left = a;
            a->parent = b;
            if (a->right != nil) {
                a->right->parent = a;
            }
            b->parent = parent;
            if (parent != nil) {
                if (a == parent->left) {
                    parent->left = b;
                } else if (a == parent->right) {
                    parent->right = b;
                }
            }
        }
    }

    /**
     * rotacja danego węzła w prawo, jeśli jest możliwa
     * @param a
     */
    void rotateRight(Node *a) {
        if (a == nil)
            return;
        Node *b = a->left;
        Node *parent = a->parent;
        if (b != nil) {
            a->left = b->right;
            b->right = a;
            a->parent = b;
            if (a->left != nil) {
                a->left->parent = a;
            }
            b->parent = parent;
            if (parent != nil) {
                if (a == parent->right) {
                    parent->right = b;
                } else if (a == parent->left) {
                    parent->left = b;
                }
            }
        }
    }

    /**
     * zwraca brata podanego węzła
     * @param node
     * @return brat danego węzła, lub nil jeśli nie ma brata
     */
    Node *getBrotherOfNode(Node *node) {
        if (node->parent != nil) {
            return (node->parent->left == node) ? node->parent->right : node->parent->left;
        }
        return nil;
    }

    /**
     * dodanie liczby do drzewa - algorytm - Cormen - wprowadzenie do algorytmów 13.3
     * @param number
     */
    void add(int number) {
        Node *y = nil;
        Node *x = root;
        while (x != nil) {
            y = x;
            if (number < x->value)
                x = x->left;
            else
                x = x->right;
        }
        Node *z = new Node(number, y, nil, nil);
        if (y == nil)
            root = z;
        else if (number < y->value) {
            y->left = z;
        } else y->right = z;
        addFixTree(z);
        /*if (root == nil) {
            root = new Node(number, nil, nil, nil, BLACK);
        } else {
            Node *parent;
            Node *placeToAdd = root;
            do {
                parent = placeToAdd;
                if (number < parent->value)
                    placeToAdd = parent->left;
                else placeToAdd = parent->right;
            } while (placeToAdd != nil);
            Node *z = new Node(number, parent, nil, nil);
            if (number < parent->value)
                parent->left = z;
            else
                parent->right = z;
            addFixTree(z);
            root = z;
            while (z->parent != nil) {
                z = z->parent;
                root = z;
            }
        }*/
    }

    /**
     * naprawianie właściwości drzewa czerwono-czarnego po dodaniu do niego liczby - algorytm - Cormen - wprowadzenie do algorytmów 13.3
     * @param z
     */
    void addFixTree(Node *z) {
        while (z->parent->colour == RED) {
            Node *grandparent = z->parent->parent;
            Node *y;
            if (z->parent == grandparent->left) {
                y = grandparent->right;
                if (y->colour == RED) {
                    z->parent->colour = BLACK;
                    y->colour = BLACK;
                    grandparent->colour = RED;
                    z = grandparent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->colour = BLACK;
                    grandparent->colour = RED;
                    rotateRight(grandparent);
                }
            } else {
                y = grandparent->left;
                if (y->colour == RED) {
                    z->parent->colour = BLACK;
                    y->colour = BLACK;
                    grandparent->colour = RED;
                    z = grandparent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->colour = BLACK;
                    grandparent->colour = RED;
                    rotateLeft(grandparent);
                }
            }
        }
//        ważne, bo korzeń po operacjach wyżej może już nie być aktualnym korzeniem, todo check
//        root = z;
        while (root->parent != nil) {
            root = root->parent;
        }
        root->colour = BLACK;
        /*if (z->parent != nil) {
            Node *parent = z->parent;
            if (parent->colour == RED) {
                Node *uncle = getBrotherOfNode(parent);
                Node *grandparent = parent->parent;
                if (uncle != nil) {
                    if (uncle->colour == RED) {
                        //trzeci przypadek
                        parent->colour = BLACK;
                        uncle->colour = BLACK;
                        grandparent->colour = RED;
                        addFixTree(grandparent);
                    }
                } else {
                    //czwarty przypadek
                    if (z == parent->right && parent == grandparent->left) {
                        rotateLeft(parent);
                        z = z->left;
                    } else if (z == parent->left && parent == grandparent->right) {
                        rotateRight(parent);
                        z = z->right;
                    }
                    if (z == parent->left) {
                        rotateRight(grandparent);
                    } else {
                        rotateLeft(grandparent);
                    }
                    parent->colour = BLACK;
                    grandparent->colour = RED;
                }
            }
            //drugi przypadek (nie trzeba robić nic)
        }
            //pierwszy przypadek
        else z->colour = BLACK;*/

    }

    /**
     * szukanie i usuwanie danej liczby
     * @param number
     * @return true, jeśli znaleziono i usunięto liczbę, false w przeciwnym wypadku
     */
    bool remove(int number) {
        Node *temp = root;
        while (temp != nil) {
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
     * usuwanie już danego elementu drzewa, algorytm - Cormen - Wprowadzenie do algorytmów 13.4
     * @param node
     */
    void removeGivenElement(Node *node) {
        /*Node *y = node;
        if (node->left != nil && node->right != nil) {
            //node ma dwóch potomków, wyznaczenie następnika i wstawienie jego wartości do node, i usuwamy następnika
            y = node->right;
            while (y->left != nil)
                y = y->left;
            node->value = y->value;
        }
        //wiadomo, że y ma najwyżej jednego potomka
        Node *child = (y->right == nil) ? y->left : y->right;
        if (child != nil) {
            child->parent = y->parent;
            if (y == y->parent->left)
                y->parent->left = child;
            else
                y->parent->right = child;
        }
        if (y->colour == BLACK) {
            if (child->colour == RED) {
                child->colour = BLACK;
            } else {
                removeFixTree(child);
            }
        }
        //usunięcie odniesienia do danego elementu u rodzica usuwanego elementu
        Node *parentOfDeletedNode = y->parent;
        if (parentOfDeletedNode->left == y)
            parentOfDeletedNode->left = nil;
        else
            parentOfDeletedNode->right = nil;
        delete y;*/
        Node *y;
        if (node->left == nil || node->right == nil)
            y = node;
        else {
            //node ma dwóch potomków, y będzie następnikiem node
            y = node->right;
            while (y->left != nil)
                y = y->left;
        }
        Node *x;
        x = y->right;
        if (x != nil)
            x->parent = y->parent;
        if (y->parent == nil) {
            root = x;
        } else if (y == y->parent->left) {
            x = y->parent->left;
        } else x = y->parent->right;
        if (y != node)
            node->value = y->value;
        if (y->colour == BLACK)
            removeFixTree(x);
        //usunięcie odniesienia do danego elementu u rodzica usuwanego elementu
        Node *parentOfDeletedNode = y->parent;
        if (parentOfDeletedNode->left == y)
            parentOfDeletedNode->left = nil;
        else
            parentOfDeletedNode->right = nil;
        delete y;
    }

    /**
     * naprawianie właściwości drzewa czerwono-czarnego, algorytm - Cormen - wprowadzenie do algorytmów 13.4
     * @param child
     */
    void removeFixTree(Node *child) {
        /*if (child->parent != nil) {
            Node *brother = getBrotherOfNode(child);
            if (brother->colour == RED) {
                child->parent->colour = RED;
                brother->colour = BLACK;
                if (child == child->parent->left) {
                    rotateLeft(child->parent);
                } else {
                    rotateRight(child->parent);
                }
            }
            if ((child->parent->colour == BLACK) && (brother->left->colour == BLACK) &&
                (brother->right->colour == BLACK)) {
                brother->colour = RED;
                removeFixTree(child->parent);
            } else {
                if ((child->parent->colour == RED) && (brother->left->colour == BLACK) &&
                    (brother->right->colour == BLACK)) {
                    brother->colour = RED;
                    child->parent->colour = BLACK;
                } else {
                    // The following statements just force the red to be on the left of the
                    // left of the parent, or right of the right, so case six will rotate
                    // correctly.
                    if ((child == child->parent->left) && (brother->right->colour == BLACK) &&
                        (brother->left->colour == RED)) {
                        // This last test is trivial too due to cases 2-4.
                        brother->colour = RED;
                        brother->left->colour = BLACK;
                        rotateRight(brother);
                    } else if ((child == child->parent->right) && (brother->left->colour == BLACK) &&
                               (brother->right->colour == RED)) {
                        // This last test is trivial too due to cases 2-4.
                        brother->colour = RED;
                        brother->right->colour = BLACK;
                        rotateLeft(brother);
                    }
                    brother->colour = child->parent->colour;
                    child->parent->colour = BLACK;

                    if (child == child->parent->left) {
                        brother->right->colour = BLACK;
                        rotateLeft(child->parent);
                    } else {
                        brother->left->colour = BLACK;
                        rotateRight(child->parent);
                    }
                }
            }
        }*/
        while (child != root && child->colour == BLACK) {
            if (child == child->parent->left) {
                Node *w = child->parent->right;
                if (w->colour == RED) {
                    w->colour = BLACK;
                    child->parent->colour = RED;
                    rotateLeft(child->parent);
                    w = child->parent->right;
                }
                if (w->left->colour == BLACK && w->right->colour == BLACK) {
                    w->colour = RED;
                    child = child->parent;
                } else if (w->right->colour == BLACK) {
                    w->left->colour = BLACK;
                    w->colour = RED;
                    rotateRight(w);
                    w = child->parent->right;
                }
                w->colour = child->parent->colour;
                child->parent->colour = BLACK;
                w->right->colour = BLACK;
                rotateLeft(child->parent);
                child = root;
            } else {
                Node *w = child->parent->left;
                if (w->colour == RED) {
                    w->colour = BLACK;
                    child->parent->colour = RED;
                    rotateRight(child->parent);
                    w = child->parent->left;
                }
                if (w->right->colour == BLACK && w->left->colour == BLACK) {
                    w->colour = RED;
                    child = child->parent;
                } else if (w->left->colour == BLACK) {
                    w->right->colour = BLACK;
                    w->colour = RED;
                    rotateLeft(w);
                    w = child->parent->left;
                }
                w->colour = child->parent->colour;
                child->parent->colour = BLACK;
                w->left->colour = BLACK;
                rotateRight(child->parent);
                child = root;
            }
        }
        child->colour = BLACK;
    }

    /**
     * wyszukanie podanej liczby w drzewie RB
     * @param number
     * @return true, jeśli znaleziono liczbę, false, jeśli nie znaleziono liczby
     */
    bool findGivenNumber(int number) {
        Node *temp = root;
        while (temp != nil) {
            if (number == temp->value)
                return true;
            else {
                if (number < temp->value)
                    temp = temp->left;
                else
                    temp = temp->right;
            }
        }
    }

    /**
     * todo? test sprawdzający czy drzewo jest poprawne
     * @return
     */
    bool rbTreeTest(){

    }

    /**
     * wyświetlenie drzewa w konsoli, kolory węzłów są oznaczane przez literę R (red) lub B (black) na końcu liczby
     */
    void print() {
        cr = cl = cp = "  ";
        cr[0] = 218;
        cr[1] = 196;
        cl[0] = 192;
        cl[1] = 196;
        cp[0] = 179;
        printRecursive("", "", root);
        cout << endl;
    }

    void printRecursive(string sp, string sn, Node *node) {
        if (node != nil) {
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