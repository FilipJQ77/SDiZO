//#include <iostream>
//#include <string>
//
//using namespace std;
//
///**
// * Klasa reprezentująca drzewo AVL
// */
//class AVLTree {
//    //todo poprawki
//    class Node {
//    public:
//        int value;
//        Node *parent;
//        Node *left;
//        Node *right;
//
//        explicit Node(int val, Node *p = nullptr, Node *l = nullptr, Node *r = nullptr, nodeColour givenColour = RED) {
//            value = val;
//            parent = p;
//            left = l;
//            right = r;
//            colour = givenColour;
//        }
//
//        Node *getBrother() {
//            if (parent != nullptr) {
//                return (parent->left == this) ? parent->right : parent->left;
//            }
//            return nullptr;
//        }
//
//        void rotateLeft() {
//            Node *b = this->right;
//            Node *parent = this->parent;
//            if (b != nullptr) {
//                this->right = b->left;
//                b->left = this;
//                this->parent = b;
//                if (this->right != nullptr) {
//                    this->right->parent = this;
//                }
//                b->parent = parent;
//                if (parent != nullptr) {
//                    if (this == parent->left) {
//                        parent->left = b;
//                    } else if (this == parent->right) {
//                        parent->right = b;
//                    }
//                }
//            }
//        }
//
//        void rotateRight() {
//            Node *b = this->left;
//            Node *parent = this->parent;
//            if (b != nullptr) {
//                this->left = b->right;
//                b->right = this;
//                this->parent = b;
//                if (this->left != nullptr) {
//                    this->left->parent = this;
//                }
//                b->parent = parent;
//                if (parent != nullptr) {
//                    if (this == parent->right) {
//                        parent->right = b;
//                    } else if (this == parent->left) {
//                        parent->left = b;
//                    }
//                }
//            }
//        }
//    };
//
//    Node *root;
//
//    void removeNodeFromMemory(Node *node) {
//        if (node == nullptr)
//            return;
//        removeNodeFromMemory(node->left);
//        removeNodeFromMemory(node->right);
//        delete node;
//    }
//
//public:
//
//    //todo lepsza implementacja tego
//    string cr;
//    string cl;
//    string cp;
//
//    AVLTree(int *array = nullptr, int arraySize = 0) {
//        root = nullptr;
//        for (unsigned int i = 0; i < arraySize; ++i) {
//            add(array[i]);
//        }
//    }
//
//    /**
//     * destruktor
//     */
//    ~AVLTree() {
//        removeNodeFromMemory(root);
//    }
//
//    /**
//     *
//     * @param number
//     */
//    void add(int number) {
//        //pierwszy przypadek
//        if (root == nullptr) {
//            root = new Node(number, nullptr, nullptr, nullptr, BLACK);
//        } else {
//            Node *parent;
//            Node *placeToAdd = root;
//            do {
//                parent = placeToAdd;
//                if (number < parent->value)
//                    placeToAdd = parent->left;
//                else placeToAdd = parent->right;
//            } while (placeToAdd != nullptr);
//            Node *newNode = new Node(number, parent);
//            if (number < parent->value)
//                parent->left = newNode;
//            else
//                parent->right = newNode;
//            addFixTree(newNode);
//            //znalezienie nowego korzenia
//            root = newNode;
//            while (newNode->parent != nullptr) {
//                newNode = newNode->parent;
//                root = newNode;
//            }
//        }
//    }
//
//    void addFixTree(Node *node) {
//        if (node->parent != nullptr) {
//            Node *parent = node->parent;
//            if (parent->colour == RED) {
//                Node *uncle = parent->getBrother();
//                Node *grandparent = parent->parent;
//                if (uncle != nullptr) {
//                    if (uncle->colour == RED) {
//                        //trzeci przypadek
//                        parent->colour = BLACK;
//                        uncle->colour = BLACK;
//                        grandparent->colour = RED;
//                        addFixTree(grandparent);
//                    }
//                } else {
//                    //czwarty przypadek
//                    if (node == parent->right && parent == grandparent->left) {
//                        parent->rotateLeft();
//                        node = node->left;
//                    } else if (node == parent->left && parent == grandparent->right) {
//                        parent->rotateRight();
//                        node = node->right;
//                    }
//                    if (node == parent->left) {
//                        grandparent->rotateRight();
//                    } else {
//                        grandparent->rotateLeft();
//                    }
//                    parent->colour = BLACK;
//                    grandparent->colour = RED;
//                }
//            }
//            //drugi przypadek (nie trzeba robić nic)
//        }
//            //pierwszy przypadek
//        else node->colour = BLACK;
//    }
//
//    /**
//     * szukanie i usuwanie danej liczby
//     * @param number
//     * @return true, jeśli znaleziono i usunięto liczbę, false w przeciwnym wypadku
//     */
//    bool remove(int number) {
//        Node *temp = root;
//        while (temp != nullptr) {
//            if (number == temp->value) {
//                removeGivenElement(temp);
//                return true;
//            } else {
//                if (number < temp->value)
//                    temp = temp->left;
//                else
//                    temp = temp->right;
//            }
//        }
//    }
//
//    /**
//     * usuwanie już danego elementu drzewa, algorytm - https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/?ref=rp
//     * @param z
//     */
//    void removeGivenElement(Node *z) {
//        //todo znaleźć lepszy algorytm
//        Node *y;
//        if (z->left == nullptr || z->right == nullptr)
//            y = z;
//        else {
//            //Node ma dwóch potomków
//            y = z->right;
//            while (y->left != nullptr)
//                y = y->left;
//        }
//        Node *x;
//        if (y->left != nullptr)
//            x = y->left;
//        else
//            x = y->right;
//        x->parent = y->parent;
//        if (y->parent == nullptr) {
//            root = x;
//        } else if (y == y->parent->left) {
//            x = y->parent->left;
//        } else x = y->parent->right;
//        if (y != z)
//            z->value = y->value;
//    }
//
//    /**
//     * wyszukanie podanej liczby w drzewie RB
//     * @param number
//     * @return true, jeśli znaleziono liczbę, false, jeśli nie znaleziono liczby
//     */
//    bool findGivenNumber(int number) {
//        Node *temp = root;
//        while (temp != nullptr) {
//            if (number == temp->value)
//                return true;
//            else {
//                if (number < temp->value)
//                    temp = temp->left;
//                else
//                    temp = temp->right;
//            }
//        }
//    }
//
//    /**
//     * wyświetlenie drzewa w konsoli, kolory węzłów są oznaczane przez literę R (red) lub B (black) na końcu liczby
//     */
//    void print() {
//        cr = cl = cp = "  ";
//        cr[0] = 218;
//        cr[1] = 196;
//        cl[0] = 192;
//        cl[1] = 196;
//        cp[0] = 179;
//        printRecursive("", "", root);
//        cout << endl;
//    }
//
//    void printRecursive(string sp, string sn, Node *node) {
//        if (node != nullptr) {
//            string s = sp; //"tekst do wyświetlenia w wierszach pośrednich dla synów"
//            if (sn == cr)
//                s[s.length() - 2] = ' ';
//            printRecursive(s + cp, cr, node->right);
//            s = s.substr(0, sp.length() - 2);
//            string value = (node->colour == RED) ? to_string(node->value) + "R" : to_string(node->value) + "B";
//            cout << s << sn << value << endl;
//            s = sp;
//            if (sn == cl)
//                s[s.length() - 2] = ' ';
//            printRecursive(s + cp, cl, node->left);
//        }
//    }
//};