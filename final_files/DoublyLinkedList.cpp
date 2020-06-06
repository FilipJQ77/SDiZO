#include<iostream>

using std::cout;
using std::invalid_argument;

/**
 * klasa reprezentuj¹ca listê dwukierunkow¹
 */
class DoublyLinkedList {

    /**
     * pomocnicza klasa reprezentuj¹ca pojedynczy element listy
     */
    class ListElement {
    public:
        int value; //wartoœæ elementu
        ListElement* prev; //wskaŸnik na poprzedni element
        ListElement* next; //wskaŸnik na nastêpny element

        explicit ListElement(int val, ListElement* p = nullptr, ListElement* n = nullptr) {
            value = val;
            prev = p;
            next = n;
        }
    };

    ListElement* head; //g³owa - pierwszy element listy
    ListElement* tail; //ogon - ostatni element listy
    unsigned int listSize; // d³ugoœæ listy

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
     * @param array wskaŸnik na pierwszy element tablicy
     * @param arraySize d³ugoœæ tablicy
     */
    DoublyLinkedList(int* array, unsigned int arraySize) : DoublyLinkedList() { //delegacja podstawowego konstruktora
        for (unsigned int i = 0; i < arraySize; ++i) {
            addBack(array[i]);
        }
        //nie trzeba tutaj ustawiaæ listSize=arraySize poniewa¿ jest to inkrementowane przez metodê addBack()
    }

    /**
     * destruktor
     */
    ~DoublyLinkedList() {
        while (head != nullptr) {
            removeFront(); //aby zdealokowaæ pamiêæ po wszystkich elementach
        }
    }

    /**
     * dodanie nowej liczby na pocz¹tek listy
     * @param number
     */
    void addFront(int number) {
        ++listSize;
        auto* newElement = new ListElement(number, nullptr, head);
        if (head == nullptr)
            tail = newElement; //jeœli g³owa nie wskazuje na nic, oznacza to ¿e lista jest pusta, wiêc dodajemy jedyny element, który bêdzie jednoczeœnie g³ow¹ oraz ogonem
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
            head = newElement; //jeœli ogon nie wskazuje na nic, oznacza to ¿e lista jest pusta, wiêc dodajemy jedyny element, który bêdzie jednoczeœnie ogonem oraz g³ow¹
        else
            tail->next = newElement;
        tail = newElement;
    }

    /**
     * dodanie nowej liczby w dowolne miejsce listy, jeœli podany indeks jest poprawny - przedzia³ [0, rozmiar listy]
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
     * usuwanie elementu z pocz¹tku listy, jeœli istnieje
     */
    void removeFront() {
        //jeœli s¹ co najmniej 2 elementy
        if (head != tail) {
            --listSize;
            ListElement* newHead = head->next;
            if (newHead != nullptr)
                newHead->prev = nullptr;
            delete head;
            head = newHead;
        }
        //jeœli jest najwy¿ej 1 element
        else {
            delete head;
            head = tail = nullptr;
            listSize = 0;
        }
    }

    /**
     * usuwanie elementu z koñca listy, jeœli istnieje
     */
    void removeBack() {
        //jeœli s¹ co najmniej 2 elementy
        if (tail != head) {
            --listSize;
            ListElement* newTail = tail->prev;
            if (newTail != nullptr)
                newTail->next = nullptr;
            delete tail;
            tail = newTail;
        }
        //jeœli jest najwy¿ej 1 element
        else {
            delete tail;
            head = tail = nullptr;
            listSize = 0;
        }
    }

    /**
     * usuwanie podanego elementu listy
     * @param temp element do usuniêcia
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
     * usuwanie liczby na danej pozycji, jeœli indeks jest poprawny
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
     * szukanie i usuniêcie podanej liczby, jeœli jest w liœcie; jeœli jest kilka przypadków wyst¹pienia takiej liczby usuniête zostaje jedynie pierwsze znalezione wyst¹pienie
     * @param number
     * @return true - jeœli znaleziono i usuniêto dan¹ liczbê, false - w przeciwnym wypadku
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
     * wyszukanie podanej liczby w liœcie
     * @param number
     * @return true, jeœli znaleziono liczbê, false, jeœli nie znaleziono liczby
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
     * wydobycie liczby o danym indeksie z listy, jeœli indeks jest niepoprawny funkcja wyrzuci wyj¹tek
     * @param index
     * @return
     */
    int getNumberAt(unsigned int index) {
        if (index <= listSize) {
            ListElement* temp;
            //poniewa¿ mamy dostêp i do g³owy i do ogona, mo¿emy wybraæ od której strony iœæ do liczby by szybciej na ni¹ trafiæ
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