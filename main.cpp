#include<iostream>

class Array {

    int* array;
    unsigned int arraySize;

public:

    Array() {
        array = new int[0];
        arraySize = 0;
    }

    Array(int* arrayGiven, int arraySizeGiven) {
        array = new int[arraySizeGiven];
        arraySize = arraySizeGiven;
        for (unsigned int i = 0; i < arraySize; ++i) {
            array[i] = arrayGiven[i];
        }
    }

    void addFront(int number) {
        ++arraySize;
        int* newArray = new int[arraySize];
        newArray[0] = number;
        for (unsigned int i = 1; i < arraySize; ++i) {
            newArray[i] = array[i - 1];
        }
        delete[] array;
        array = newArray;
    }

    void addBack(int number) {
        int* newArray = new int[arraySize + 1];
        for (unsigned int i = 0; i < arraySize; ++i) {
            newArray[i] = array[i];
        }
        newArray[arraySize] = number;
        ++arraySize;
        delete[] array;
        array = newArray;
    }

    void addAnywhere(int number, unsigned int position) {
        ++arraySize;
        int* newArray = new int[arraySize];
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

    void removeFront() {
        --arraySize;
        int* newArray = new int[arraySize];
        for (unsigned int i = 0; i < arraySize; ++i) {
            newArray[i] = array[i + 1];
        }
        delete[] array;
        array = newArray;
    }

    void removeBack() {
        --arraySize;
        int* newArray = new int[arraySize];
        for (unsigned int i = 0; i < arraySize; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }

    void removeAnywhere(unsigned int position) {
        --arraySize;
        int* newArray = new int[arraySize];
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

    //TODO adding pop methods

    int findNumberAt(int position) {
        return array[position];
    }

    int* getArray() {
        return array;
    }

    int getArraySize() {
        return arraySize;
    }

    void printArray() {
        std::cout << "Size:" << arraySize<<" | ";
        for (unsigned int i = 0; i < arraySize; ++i) {
            std::cout << array[i] << ",";
        }
        std::cout << std::endl;
    }
};

class DoublyLinkedList {

    class ListElement {
    public:
        int value;
        ListElement* prev;
        ListElement* next;

        ListElement(int val) {
            this->value = val;
            this->prev = nullptr;
            this->next = nullptr;
        }

        ListElement(int val, ListElement* p, ListElement* n) {
            this->value = val;
            this->prev = p;
            this->next = n;
        }
    };

    ListElement* head;
    ListElement* tail;

public:

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void addFront(int number) {
        ListElement newElement(number, nullptr, head);
        if (head == nullptr)
            tail = &newElement; //jeśli głowa nie wskazuje na nic, oznacza to że lista jest pusta, więc dodajemy jedyny element, który będzie jednocześnie głową oraz ogonem
        else
            head->prev = &newElement;
        head = &newElement;
    }

    void addBack(int number) {
        ListElement newElement(number, tail, nullptr);
        if (tail == nullptr)
            head = &newElement; //jeśli ogon nie wskazuje na nic, oznacza to że lista jest pusta, więc dodajemy jedyny element, który będzie jednocześnie ogonem oraz głową 
        else
            tail->next = &newElement;
        tail = &newElement;
    }

    void addAnywhere(int number, unsigned int position) {

    }

    void removeFront() {
        ListElement* newHead = head->next;
        newHead->prev = nullptr;
    }

    void removeBack() {

    }

    void removeAnywhere(unsigned int position) {

    }

    int findNumberAt(unsigned int position) {

    }

    //TODO add pop methods?

    ListElement* getHead() {
        return head;
    }

    void twoWayTest() {
        if (head == nullptr) return;
        Array array1;
        Array array2;
        ListElement* temp = head;
        while (temp->next != nullptr) {
            array1.addBack(temp->value);
            array1.printArray();
            temp = temp->next;
        }
        temp = tail;
        while (temp->prev != nullptr) {
            array2.addFront(temp->value);
            array2.printArray();
            temp = temp->prev;
        }
        array1.printArray();
        array2.printArray();
        return;
    }
};

void arrayTest() {
    int tab[] = { 1,2,3,4,5 };
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
    std::cout << x.findNumberAt(1);
    std::cout << x.findNumberAt(0);
    std::cout << x.findNumberAt(-1);
}

void listTest() {
    DoublyLinkedList list1;
    list1.addFront(3);
    //list1.twoWayTest();
    list1.addFront(2);
    //list1.twoWayTest();
    list1.addFront(1);
    list1.twoWayTest();
    DoublyLinkedList list2;
    list2.addBack(1);
    //list2.twoWayTest();
    list2.addBack(2);
    //list2.twoWayTest();
    list2.addBack(3);
    list2.twoWayTest();
}

int main() {
    //arrayTest();
    listTest();
    return 0;
}