#include<iostream>

using std::cout;
using std::invalid_argument;

/**
 * klasa reprezentuj�ca list� dwukierunkow�
 */
class DoublyLinkedList {

    /**
     * pomocnicza klasa reprezentuj�ca pojedynczy element listy
     */
    class ListElement {
    public:
        int value; //warto�� elementu
        ListElement* prev; //wska�nik na poprzedni element
        ListElement* next; //wska�nik na nast�pny element

        explicit ListElement(int val, ListElement* p = nullptr, ListElement* n = nullptr) {
            value = val;
            prev = p;
            next = n;
        }
    };

    ListElement* head; //g�owa - pierwszy element listy
    ListElement* tail; //ogon - ostatni element listy
    unsigned int listSize; // d�ugo�� listy

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
     * @param array wska�nik na pierwszy element tablicy
     * @param arraySize d�ugo�� tablicy
     */
    DoublyLinkedList(int* array, unsigned int arraySize) : DoublyLinkedList() { //delegacja podstawowego konstruktora
        for (unsigned int i = 0; i < arraySize; ++i) {
            addBack(array[i]);
        }
        //nie trzeba tutaj ustawia� listSize=arraySize poniewa� jest to inkrementowane przez metod� addBack()
    }

    /**
     * destruktor
     */
    ~DoublyLinkedList() {
        while (head != nullptr) {
            removeFront(); //aby zdealokowa� pami�� po wszystkich elementach
        }
    }

    /**
     * dodanie nowej liczby na pocz�tek listy
     * @param number
     */
    void addFront(int number) {
        ++listSize;
        auto* newElement = new ListElement(number, nullptr, head);
        if (head == nullptr)
            tail = newElement; //je�li g�owa nie wskazuje na nic, oznacza to �e lista jest pusta, wi�c dodajemy jedyny element, kt�ry b�dzie jednocze�nie g�ow� oraz ogonem
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
        auto* newElement = new ListElement(number, tail, nullptr);
        if (tail == nullptr)
            head = newElement; //je�li ogon nie wskazuje na nic, oznacza to �e lista jest pusta, wi�c dodajemy jedyny element, kt�ry b�dzie jednocze�nie ogonem oraz g�ow�
        else
            tail->next = newElement;
        tail = newElement;
    }

    /**
     * dodanie nowej liczby w dowolne miejsce listy, je�li podany indeks jest poprawny - przedzia� [0, rozmiar listy]
     * @param number
     * @param index indeks od 0, jak w tablicy
     */
    void addAnywhere(int number, unsigned int index) {
        if (index <= listSize) {
            ListElement* temp;
            if (index < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < index; ++i) {
                    temp = temp->next;
                }
            }
            else {
                temp = tail;
                unsigned int i = listSize - 1;
                for (; i > index; --i) {
                    temp = temp->prev;
                }
            }
            ++listSize;
            auto* newElement = new ListElement(number, temp->prev, temp);
            if (temp->prev != nullptr)
                (temp->prev)->next = newElement;
            temp->prev = newElement;
        }
    }

    /**
     * usuwanie elementu z pocz�tku listy, je�li istnieje
     */
    void removeFront() {
        //je�li s� co najmniej 2 elementy
        if (head != tail) {
            --listSize;
            ListElement* newHead = head->next;
            if (newHead != nullptr)
                newHead->prev = nullptr;
            delete head;
            head = newHead;
        }
        //je�li jest najwy�ej 1 element
        else {
            delete head;
            head = tail = nullptr;
            listSize = 0;
        }
    }

    /**
     * usuwanie elementu z ko�ca listy, je�li istnieje
     */
    void removeBack() {
        //je�li s� co najmniej 2 elementy
        if (tail != head) {
            --listSize;
            ListElement* newTail = tail->prev;
            if (newTail != nullptr)
                newTail->next = nullptr;
            delete tail;
            tail = newTail;
        }
        //je�li jest najwy�ej 1 element
        else {
            delete tail;
            head = tail = nullptr;
            listSize = 0;
        }
    }

    /**
     * usuwanie podanego elementu listy
     * @param temp element do usuni�cia
     */
    void removeGivenElement(ListElement* temp) {
        --listSize;
        ListElement* left = temp->prev;
        ListElement* right = temp->next;
        delete temp;
        if (left != nullptr)
            left->next = right;
        if (right != nullptr)
            right->prev = left;
    }

    /**
     * usuwanie liczby na danej pozycji, je�li indeks jest poprawny
     * @param index
     */
    void removeAnywhere(unsigned int index) {
        if (index == 0)
            removeFront();
        else if (index == listSize - 1)
            removeBack();
        else if (index < listSize - 1) {
            ListElement* temp;
            if (index < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < index; ++i) {
                    temp = temp->next;
                }
            }
            else {
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
     * szukanie i usuni�cie podanej liczby, je�li jest w li�cie; je�li jest kilka przypadk�w wyst�pienia takiej liczby usuni�te zostaje jedynie pierwsze znalezione wyst�pienie
     * @param number
     * @return true - je�li znaleziono i usuni�to dan� liczb�, false - w przeciwnym wypadku
     */
    bool removeGivenNumber(int number) {
        ListElement* temp = head;
        while (temp != nullptr) {
            if (temp->value == number) {
                removeGivenElement(temp);
                return true;
            }
            else
                temp = temp->next;
        }
        return false;
    }

    /**
     * wyszukanie podanej liczby w li�cie
     * @param number
     * @return true, je�li znaleziono liczb�, false, je�li nie znaleziono liczby
     */
    bool findGivenNumber(int number) {
        ListElement* temp = head;
        while (temp != nullptr) {
            if (temp->value == number)
                return true;
            else
                temp = temp->next;
        }
        return false;
    }

    /**
     * wydobycie liczby o danym indeksie z listy, je�li indeks jest niepoprawny funkcja wyrzuci wyj�tek
     * @param index
     * @return
     */
    int getNumberAt(unsigned int index) {
        if (index <= listSize) {
            ListElement* temp;
            //poniewa� mamy dost�p i do g�owy i do ogona, mo�emy wybra� od kt�rej strony i�� do liczby by szybciej na ni� trafi�
            if (index < listSize / 2) {
                temp = head;
                unsigned int i = 0;
                for (; i < index; ++i) {
                    temp = temp->next;
                }
            }
            else {
                temp = tail;
                unsigned int i = listSize - 1;
                for (; i > index; --i) {
                    temp = temp->prev;
                }
            }
            return temp->value;
        }
        else throw invalid_argument("Podany indeks jest niepoprawny");
    }

    void print() {
        ListElement* temp = head;
        cout << "Lista o rozmiarze: " << listSize << '\n';
        while (temp != nullptr) {
            cout << temp->value << ", ";
            temp = temp->next;
        }
        cout << '\n';
    }
};