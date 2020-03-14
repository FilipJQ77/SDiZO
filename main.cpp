#include<iostream>

using namespace std;

class Array {

    int *array;
    unsigned int arraySize;

public:

    Array() {
        array = new int[0];
        arraySize = 0;
    }

    Array(int *arrayGiven, int arraySizeGiven) {
        array = new int[arraySizeGiven];
        arraySize = arraySizeGiven;
        for (unsigned int i = 0; i < arraySize; ++i) {
            array[i] = arrayGiven[i];
        }
    }

    void addFront(int number) {
        ++arraySize;
        int *newArray = new int[arraySize];
        newArray[0] = number;
        for (unsigned int i = 1; i < arraySize; ++i) {
            newArray[i] = array[i - 1];
        }
        delete[] array;
        array = newArray;
    }

    void addBack(int number) {
        int *newArray = new int[arraySize + 1];
        for (unsigned int i = 0; i < arraySize; ++i) {
            newArray[i] = array[i];
        }
        newArray[arraySize] = number;
        ++arraySize;
        delete[] array;
        array = newArray;
    }

    void addAnywhere(int number, unsigned int position) {
        if (position <= arraySize) {
            ++arraySize;
            int *newArray = new int[arraySize];
            unsigned int i = 0;
            for (; i < position; ++i) {
                newArray[i] = array[i];
            }
            newArray[i] = number;
            ++i;
            for (; i < arraySize; ++i) {
                newArray[i] = array[i - 1];
            }
            delete[] array;
            array = newArray;
        }
    }

    void removeFront() {
        if (arraySize > 0) {
            --arraySize;
            int *newArray = new int[arraySize];
            for (unsigned int i = 0; i < arraySize; ++i) {
                newArray[i] = array[i + 1];
            }
            delete[] array;
            array = newArray;
        }
    }

    void removeBack() {
        if (arraySize > 0) {
            --arraySize;
            int *newArray = new int[arraySize];
            for (unsigned int i = 0; i < arraySize; ++i) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
    }

    void removeAnywhere(unsigned int position) {
        if (position < arraySize) {
            --arraySize;
            int *newArray = new int[arraySize];
            unsigned int i = 0;
            for (; i < position; ++i) {
                newArray[i] = array[i];
            }
            for (; i < arraySize; ++i) {
                newArray[i] = array[i + 1];
            }
            delete[] array;
            array = newArray;
        }
    }

    //TODO adding pop methods

    int getNumberAt(unsigned int position) {
        if (position < arraySize)
            return array[position];
        return 0;
    }

    int *getArray() {
        return array;
    }

    unsigned int getArraySize() {
        return arraySize;
    }

    void printArray() {
        cout << "Size:" << arraySize << " | ";
        for (unsigned int i = 0; i < arraySize; ++i) {
            cout << array[i] << ",";
        }
        cout << endl;
    }
};

class DoublyLinkedList {

    class ListElement {
    public:
        int value;
        ListElement *prev;
        ListElement *next;

        ListElement(int val) {
            value = val;
            prev = nullptr;
            next = nullptr;
        }

        ListElement(int val, ListElement *p, ListElement *n) {
            value = val;
            prev = p;
            next = n;
        }
    };

    ListElement *head;
    ListElement *tail;
    unsigned int listSize;

public:

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    void addFront(int number) {
        ++listSize;
        ListElement *newElement = new ListElement(number, nullptr, head);
        if (head == nullptr)
            tail = newElement; //jeśli głowa nie wskazuje na nic, oznacza to że lista jest pusta, więc dodajemy jedyny element, który będzie jednocześnie głową oraz ogonem
        else
            head->prev = newElement;
        head = newElement;
    }

    void addBack(int number) {
        ++listSize;
        ListElement *newElement = new ListElement(number, tail, nullptr);
        if (tail == nullptr)
            head = newElement; //jeśli ogon nie wskazuje na nic, oznacza to że lista jest pusta, więc dodajemy jedyny element, który będzie jednocześnie ogonem oraz głową
        else
            tail->next = newElement;
        tail = newElement;
    }

    /**
     *
     * @param number
     * @param position indeks od 0, jak w tablicy
     */
    void addAnywhere(int number, unsigned int position) {
        if (position <= listSize) {
            ListElement *temp;
            if (position < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < position; ++i) {
                    temp = temp->next;
                }
            } else {
                temp = tail;
                unsigned int i = listSize - 1;
                for (; i > position; --i) {
                    temp = temp->prev;
                }
            }
            ++listSize;
            ListElement *newElement = new ListElement(number, temp->prev, temp);
            (temp->prev)->next = newElement;
            temp->prev = newElement;
        }
    }

    void removeFront() {
        if (head != nullptr) {
            --listSize;
            ListElement *newHead = head->next;
            if (newHead != nullptr)
                newHead->prev = nullptr;
            delete head;
            head = newHead;
        }
    }

    void removeBack() {
        if (tail != nullptr) {
            --listSize;
            ListElement *newTail = tail->prev;
            if (newTail != nullptr)
                newTail->next = nullptr;
            delete tail;
            tail = newTail;
        }
    }

    void removeAnywhere(unsigned int position) {
        //todo
    }

    int findNumberAt(unsigned int position) {
        if (position <= listSize) {
            ListElement *temp;
            if (position < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < position; ++i) {
                    temp = temp->next;
                }
            } else {
                temp = tail;
                unsigned int i = listSize - 1;
                for (; i > position; --i) {
                    temp = temp->prev;
                }
            }
            return temp->value;
        }
        return 0;
    }

    //TODO add pop methods?

    ListElement *getHead() {
        return head;
    }

    void printList() {
        ListElement *temp = head;
        while (temp != nullptr) {
            cout << temp->value << ",";
            temp = temp->next;
        }
        cout << endl;
    }

};

class BinaryHeap {

    int *array;
    int heapSize;

public:

    BinaryHeap() {
        array = new int[0];
        heapSize = 0;
    }

    void add(int number) {
        ++heapSize;
        int *newArray = new int[heapSize];
    }

};

bool test() {
    Array *a = new Array();
    if (a->getArraySize() != 0) return false;
    a->addAnywhere(1, -1);
    if (a->getArraySize() != 0) return false;
    a->addAnywhere(1, 1);
    if (a->getArraySize() != 0) return false;
    a->addAnywhere(1, 0);
    if (a->getArraySize() != 1) return false;
    a->removeAnywhere(-1);
    a->removeAnywhere(1);
    if (a->getArraySize() != 1) return false;
    a->removeAnywhere(0);
    if (a->getArraySize() != 0) return false;
    a->removeFront();
    a->removeBack();
    a->removeAnywhere(-1);
    a->removeAnywhere(0);
    a->removeAnywhere(1);
    if (a->getArraySize() != 0) return false;
    a->addFront(1);
    if (a->getArraySize() != 1) return false;
    if (a->getNumberAt(0) != 1) return false;
    a->removeFront();
    if (a->getArraySize() != 0) return false;
    a->addBack(1);
    if (a->getArraySize() != 1) return false;
    if (a->getNumberAt(0) != 1) return false;
    a->removeBack();
    if (a->getArraySize() != 0) return false;
    a->addFront(2);
    a->addFront(1);
    a->addFront(0);
    if (a->getArraySize() != 3) return false;
    if (a->getNumberAt(0) != 0 && a->getNumberAt(1) != 1 && a->getNumberAt(2) != 2) return false;
    a->addBack(3);
    a->addBack(4);
    a->addBack(5);
    if (a->getArraySize() != 6) return false;
    if (a->getNumberAt(3) != 3 && a->getNumberAt(4) != 4 && a->getNumberAt(5) != 5) return false;
    a->addAnywhere(6, 5);
    a->addAnywhere(7, 7);
    if (a->getNumberAt(5) != 6 && a->getNumberAt(6) != 5 && a->getNumberAt(7) != 7) return false;
    a->removeAnywhere(7);
    a->printArray();
    if (a->getArraySize() != 7) return false;
    a->removeAnywhere(5);
    a->printArray();
    if (a->getArraySize() != 6) return false;
    return true;
    /*int tab[] = {1, 2, 3, 4, 5};
    Array x(tab, 5);
    x.addBack(6);
    x.printArray();
    x.removeBack();
    x.printArray();
    x.addFront(0);
    x.printArray();
    x.removeFront();
    x.printArray();
    x.addAnywhere(7, 1);
    x.printArray();
    x.removeAnywhere(1);
    x.printArray();
    x.addAnywhere(7, 1);
    cout << x.findNumberAt(1);
    cout << x.findNumberAt(0);
    cout << x.getNumberAt(-1);
    DoublyLinkedList list;
    list.addFront(3);
    list.printList();
    list.addFront(2);
    list.printList();
    list.addFront(1);
    list.printList();
    list.addBack(4);
    list.printList();
    list.removeFront();
    list.printList();
    list.removeBack();
    list.printList();
    list.removeBack();
    list.printList();
    list.removeBack();
    list.printList();
    list.removeBack();
    list.printList();
    list.removeFront();
    list.printList();*/
}

int main() {
    DoublyLinkedList *list = new DoublyLinkedList();
    for (int i = 0; i < 9; ++i) {
        list->addBack(i);
    }
    list->addAnywhere(11, 4);
    return 0;
}