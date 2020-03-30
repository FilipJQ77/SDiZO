#include<iostream>

using namespace std;

/**
 * Klasa reprezentująca tablicę
 */
class Array {

    int *array; // wskaźnik na pierwszy element tablicy
    unsigned int arraySize; //długość tablicy

public:

    /**
     * stworzenie nowej, pustej tablicy
     */
    Array() {
        array = new int[0];
        arraySize = 0;
    }

    /**
     * stworzenie nowej tablicy na podstawie danych liczb
     * @param arrayGiven wskaźnik na początek danej tablicy liczb
     * @param arraySizeGiven rozmiar danej tablicy liczb
     */
    Array(int *arrayGiven, int arraySizeGiven) {
        array = new int[arraySizeGiven];
        arraySize = arraySizeGiven;
        for (unsigned int i = 0; i < arraySize; ++i) {
            array[i] = arrayGiven[i];
        }
    }

    /**
     * destruktor
     */
    ~Array() {
        delete[] array;
    }

    /**
     * dodanie nowej liczby na początek tablicy
     * @param number
     */
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

    /**
     * dodanie nowej liczby na koniec tablicy
     * @param number
     */
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

    /**
     * dodanie nowej liczby w dowolne miejsce tablicy, jeśli dany indeks jest poprawny tzn. w przedziale [0, rozmiar tablicy]; rozmiar tablicy jest poprawnym indeksem ponieważ oznacza to że liczba ma być dodana na koniec tablicy
     * @param number
     * @param position indeks
     */
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

    /**
     * usuwanie pierwszej liczby z tablicy, jeśli istnieje
     */
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

    /**
     * usuwanie ostatniej liczby z tablicy, jeśli istnieje
     */
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

    /**
     * usuwanie liczby z dowolnego miejsca w tablicy, jeśli dany indeks jest poprawny - przedział [0, rozmiar tablicy)
     * @param position
     */
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

    /**
     * usuwanie podanej liczby z tablicy, jeśli jest kilka przypadków wystąpienia takiej liczby usunięte zostaje jedynie pierwsze wystąpienie
     * @param number
     * @return true jeśli znaleziono i usunięto liczbę, false jeśli nie znaleziono liczby
     */
    bool removeGivenNumber(int number) {
        for (unsigned int i = 0; i < arraySize; ++i) {
            if (array[i] == number) {
                removeAnywhere(i);
                return true;
            }
        }
        return false;
    }

    /**
     * wydobycie z tablicy liczby o danym indeksie, jeśli indeks jest poprawny - [0, rozmiar tablicy); w przeciwnym wypadku wyrzucenie wyjątku
     * @param position
     * @return
     */
    int getNumberAt(unsigned int position) {
        if (position < arraySize)
            return array[position];
        else throw invalid_argument("Podany indeks jest niepoprawny");
    }


    /**
     * getter tablicy
     * @return
     */
    int *getArray() {
        return array;
    }

    /**
     * getter rozmiaru tablicy
     * @return
     */
    unsigned int getArraySize() {
        return arraySize;
    }

    /**
     * pokazanie tablicy w konsoli
     */
    void printArray() {
        cout << "Tablica o rozmiarze: " << arraySize << endl;
        for (unsigned int i = 0; i < arraySize; ++i) {
            cout << array[i] << ", ";
        }
        cout << endl;
    }
};

/**
 * Klasa reprezentująca listę dwukierunkową
 */
class DoublyLinkedList {

    /**
     * Pomocnicza klasa reprezentująca pojedynczy element listy
     */
    class ListElement {
    public:
        int value; //wartość elementu
        ListElement *prev; //wskaźnik na poprzedni element
        ListElement *next; //wskaźnik na następny element

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

    ListElement *head; //głowa - pierwszy element listy
    ListElement *tail; //ogon - ostatni element listy
    unsigned int listSize; // długość listy

public:

    /**
     * stworzenie nowej pustej listy
     */
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    /**
     * stworzenie nowej listy na podstawie danej tablicy liczb
     * @param array wskaźnik na pierwszy element tablicy
     * @param arraySize długość tablicy
     */
    DoublyLinkedList(int *array, unsigned int arraySize) : DoublyLinkedList() { //delegacja podstawowego konstruktora
        for (unsigned int i = 0; i < arraySize; ++i) {
            addBack(array[i]);
        }
    }

    /**
     * destruktor
     */
    ~DoublyLinkedList() {
        ListElement *temp;
        while (head != nullptr) {
            removeFront(); //aby zdealokować pamięć po wszystkich elementach
        }
    }

    /**
     * dodanie nowej liczby na początek listy
     * @param number
     */
    void addFront(int number) {
        ++listSize;
        ListElement *newElement = new ListElement(number, nullptr, head);
        if (head == nullptr)
            tail = newElement; //jeśli głowa nie wskazuje na nic, oznacza to że lista jest pusta, więc dodajemy jedyny element, który będzie jednocześnie głową oraz ogonem
        else
            head->prev = newElement;
        head = newElement;
    }

    /**
     * dodanie nowej liczby na koniec listy
     * @param number
     */
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
     * dodanie nowej liczby w dowolne miejsce listy, jeśli podany indeks jest poprawny - przedział [0, rozmiar listy]
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

    /**
     * usuwanie elementu z początku listy, jeśli istnieje
     */
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

    /**
     * usuwanie elementu z końca listy, jeśli istnieje
     */
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

    /**
     * usuwanie liczby na danej pozycji, jeśli indeks jest poprawny
     * @param position
     */
    void removeAnywhere(unsigned int position) {
        //TODO test
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
            --listSize;
            ListElement *left = temp->prev;
            ListElement *right = temp->next;
            delete temp;
            left->next = right;
            right->prev = left;
        }
    }

    /**
     * usunięcie podanej liczby, jeśli udało się taką znaleźć
     * @param number
     */
    void removeGivenNumber(int number) {
        ListElement *temp = head;
        
    }

    /**
     * wydobycie liczby o danym indeksie z listy, jeśli indeks jest niepoprawny funkcja wyrzuci wyjątek
     * @param position
     * @return
     */
    int getNumberAt(unsigned int position) {
        if (position <= listSize) {
            ListElement *temp;
            /**
             * ponieważ mamy dostęp i do głowy i do ogona, możemy wybrać od której strony iść do liczby by szybciej na nią trafić
             */
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
        } else throw invalid_argument("Podany indeks jest niepoprawny");
    }

    ListElement *getHead() {
        return head;
    }

    ListElement *getTail() {
        return tail;
    }

    void printList() {
        ListElement *temp = head;
        while (temp != nullptr) {
            cout << temp->value << ", ";
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

int main() {
//    DoublyLinkedList *list = new DoublyLinkedList();
//    for (int i = 0; i < 9; ++i) {
//        list->addBack(i);
//    }
//    list->addAnywhere(11, 4);
    int tab[] = {1, 2, 3, 4, 5};
    DoublyLinkedList *list = new DoublyLinkedList(tab, 5);
    return 0;
}