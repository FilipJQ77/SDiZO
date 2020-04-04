#include<iostream>

using std::cout;
using std::invalid_argument;

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

        explicit ListElement(int val, ListElement *p = nullptr, ListElement *n = nullptr) {
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
        //nie trzeba tutaj ustawiać listSize=arraySize ponieważ jest to inkrementowane przez metodę addBack()
    }

    /**
     * destruktor
     */
    ~DoublyLinkedList() {
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
     * @param index indeks od 0, jak w tablicy
     */
    void addAnywhere(int number, unsigned int index) {
        if (index <= listSize) {
            ListElement *temp;
            if (index < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < index; ++i) {
                    temp = temp->next;
                }
            } else {
                temp = tail;
                unsigned int i = listSize - 1;
                for (; i > index; --i) {
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
        //jeśli są co najmniej 2 elementy
        if (head != tail) {
            --listSize;
            ListElement *newHead = head->next;
            if (newHead != nullptr)
                newHead->prev = nullptr;
            delete head;
            head = newHead;
        }
        //jeśli jest najwyżej 1 element
        else {
            head = tail = nullptr;
            listSize = 0;
        }
    }

    /**
     * usuwanie elementu z końca listy, jeśli istnieje
     */
    void removeBack() {
        //jeśli są co najmniej 2 elementy
        if (tail != head) {
            --listSize;
            ListElement *newTail = tail->prev;
            if (newTail != nullptr)
                newTail->next = nullptr;
            delete tail;
            tail = newTail;
        }
        //jeśli jest najwyżej 1 element
        else {
            head = tail = nullptr;
            listSize = 0;
        }
    }

    /**
     * usuwanie podanego elementu listy
     * @param temp element do usunięcia
     */
    void removeGivenElement(ListElement *temp) {
        --listSize;
        ListElement *left = temp->prev;
        ListElement *right = temp->next;
        delete temp;
        if (left != nullptr)
            left->next = right;
        if (right != nullptr)
            right->prev = left;
    }

    /**
     * usuwanie liczby na danej pozycji, jeśli indeks jest poprawny
     * @param index
     */
    void removeAnywhere(unsigned int index) {
        if (index == 0)
            removeFront();
        else if (index == listSize - 1)
            removeBack();
        else if (index < listSize - 1) {
            ListElement *temp;
            if (index < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < index; ++i) {
                    temp = temp->next;
                }
            } else {
                temp = tail;
                unsigned int i = listSize - 1;
                for (; i > index; --i) {
                    temp = temp->prev;
                }
            }
            removeGivenElement(temp);
        }
    }

    /**
     * szukanie i usunięcie podanej liczby, jeśli jest w liście; jeśli jest kilka przypadków wystąpienia takiej liczby usunięte zostaje jedynie pierwsze znalezione wystąpienie
     * @param number
     * @return true - jeśli znaleziono i usunięto daną liczbę, false - w przeciwnym wypadku
     */
    bool removeGivenNumber(int number) {
        ListElement *temp = head;
        while (temp != nullptr) {
            if (temp->value == number) {
                removeGivenElement(temp);
                return true;
            }
        }
        return false;
    }

    /**
     * wyszukanie podanej liczby w liście
     * @param number
     * @return true, jeśli znaleziono liczbę, false, jeśli nie znaleziono liczby
     */
    bool findGivenNumber(int number) {
        ListElement *temp = head;
        while (temp != nullptr) {
            if (temp->value == number) {
                removeGivenElement(temp);
                return true;
            }
        }
        return false;
    }

    /**
     * wydobycie liczby o danym indeksie z listy, jeśli indeks jest niepoprawny funkcja wyrzuci wyjątek
     * @param index
     * @return
     */
    int getNumberAt(unsigned int index) {
        if (index <= listSize) {
            ListElement *temp;
            //ponieważ mamy dostęp i do głowy i do ogona, możemy wybrać od której strony iść do liczby by szybciej na nią trafić
            if (index < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < index; ++i) {
                    temp = temp->next;
                }
            } else {
                temp = tail;
                unsigned int i = listSize - 1;
                for (; i > index; --i) {
                    temp = temp->prev;
                }
            }
            return temp->value;
        } else throw invalid_argument("Podany indeks jest niepoprawny");
    }

    void print() {
        ListElement *temp = head;
        cout << "Lista o rozmiarze: " << listSize << '\n';
        while (temp != nullptr) {
            cout << temp->value << ", ";
            temp = temp->next;
        }
        cout << '\n';
    }
};