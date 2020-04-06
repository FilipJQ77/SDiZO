#include<iostream>

using std::cout;
using std::invalid_argument;

/**
 * Klasa reprezentująca tablicę
 */
class Array {

    int *array; // wskaźnik na pierwszy element tablicy
    int arraySize; //długość tablicy

public:

    /**
     * stworzenie nowej tablicy, pustej lub na podstawie danych liczb
     * @param arrayGiven wskaźnik na początek danej tablicy liczb
     * @param arraySizeGiven rozmiar danej tablicy liczb
     */
    explicit Array(int *arrayGiven = nullptr, int arraySizeGiven = 0) {
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
     * @param index
     */
    void addAnywhere(int number, unsigned int index) {
        if (index <= arraySize) {
            ++arraySize;
            int *newArray = new int[arraySize];
            unsigned int i = 0;
            for (; i < index; ++i) {
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
     * usuwanie liczby z danego miejsca w tablicy, jeśli dany indeks jest poprawny - przedział [0, rozmiar tablicy)
     * @param index
     */
    void removeAnywhere(unsigned int index) {
        if (index < arraySize) {
            --arraySize;
            int *newArray = new int[arraySize];
            unsigned int i = 0;
            for (; i < index; ++i)
                newArray[i] = array[i];
            for (; i < arraySize; ++i)
                newArray[i] = array[i + 1];
            delete[] array;
            array = newArray;
        }
    }

    /**
     * usuwanie podanej liczby, jeśli jest w tablicy; jeśli jest kilka przypadków wystąpienia takiej liczby usunięte zostaje jedynie pierwsze znalezione wystąpienie
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
     * wyszukanie podanej liczby w tablicy
     * @param number
     * @return true, jeśli znaleziono liczbę, false, jeśli nie znaleziono liczby
     */
    bool findGivenNumber(int number) {
        for (unsigned int i = 0; i < arraySize; ++i) {
            if (array[i] == number)
                return true;
        }
        return false;
    }

    /**
     * wydobycie z tablicy liczby o danym indeksie, jeśli indeks jest poprawny - [0, rozmiar tablicy); w przeciwnym wypadku wyrzucenie wyjątku
     * @param index
     * @return
     */
    int getNumberAt(unsigned int index) {
        if (index < arraySize)
            return array[index];
        else throw invalid_argument("Podany indeks jest niepoprawny");
    }

    /**
     * pokazanie tablicy w konsoli
     */
    void print() {
        cout << "Tablica o rozmiarze: " << arraySize << '\n';
        for (unsigned int i = 0; i < arraySize; ++i) {
            cout << array[i] << ", ";
        }
        cout << '\n';
    }
};