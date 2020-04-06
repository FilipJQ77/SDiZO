#include <iostream>
#include <string>

using std::string;
using std::cout;

class BinaryHeapMax {


public:
    //todo dodaj potem do private znowu
    int *array;
    int heapSize;
    //TODO pomyśleć nad lepszą implementacją
    string cr = "  ";
    string cl = "  ";
    string cp = "  ";

    /**
     * stworzenie kopca, albo pustego, albo na podstawie podanej tablicy za pomocą algorytmu Floyda
     * @param arrayGiven
     * @param arraySizeGiven
     */
    explicit BinaryHeapMax(int *arrayGiven = nullptr, int arraySizeGiven = 0) {
        heapSize = arraySizeGiven;
        array = new int[arraySizeGiven];
        for (unsigned int i = 0; i < arraySizeGiven; ++i) {
            array[i] = arrayGiven[i];
        }
        if (heapSize != 0) {
            unsigned int i = 1 + (heapSize - 2) / 2;
            do {
                --i;
                heapifyDown(i);
            } while (i);
        }
    }

    /**
     * destruktor
     */
    ~BinaryHeapMax() {
        delete[] array;
    }

    /**
     * dodanie nowej liczby do kopca
     * @param number
     */
    void add(int number) {
        int *newArray = new int[heapSize + 1];
        unsigned int i = 0;
        for (; i < heapSize; ++i) {
            newArray[i] = array[i];
        }
        newArray[i] = number;
        delete[] array;
        array = newArray;
        ++heapSize;
        heapifyUp(i);
    }

    /**
     * naprawianie kopca w górę
     * @param childIndex
     */
    void heapifyUp(unsigned int childIndex) {
        //jeśli dany indeks nie jest korzeniem, możemy naprawiać kopiec w górę
        if (childIndex) {
            unsigned int parentIndex = (childIndex - 1) / 2;
            if (array[childIndex] > array[parentIndex]) {
                int swap = array[parentIndex];
                array[parentIndex] = array[childIndex];
                array[childIndex] = swap;
                heapifyUp(parentIndex);
            }
        }
    }

    /**
     * usuwanie korzenia z kopca
     */
    void removeRoot() {
        if (heapSize > 0) {
            --heapSize;
            int *newArray = new int[heapSize];
            //zamiana korzenia z ostatnim liściem, korzenia nie wstawiamy na koniec bo i tak jest usuwany
            newArray[0] = array[heapSize];
            for (unsigned int i = 1; i < heapSize; ++i) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            heapifyDown(0);
        }
    }

    /**
     * naprawianie kopca w dół; algorytm apisany przy pomocy pseudokodu z https://en.wikipedia.org/wiki/Binary_heap#Extract
     * @param parentIndex
     */
    void heapifyDown(unsigned int parentIndex) {
        unsigned int largestIndex = parentIndex;
        unsigned int leftIndex = 2 * parentIndex + 1;
        unsigned int rightIndex = 2 * parentIndex + 2;

        //znalezienie największej liczby między rodzicem a jego dziećmi
        if ((leftIndex <= heapSize) && array[leftIndex] > array[largestIndex])
            largestIndex = leftIndex;
        if ((rightIndex <= heapSize) && array[rightIndex] > array[largestIndex])
            largestIndex = rightIndex;

        //jeśli rodzic nie jest największy, zamień go z większym dzieckiem, i wykonaj następną naprawę tam gdzie wstawiono rodzica
        if (largestIndex != parentIndex) {
            int swap = array[parentIndex];
            array[parentIndex] = array[largestIndex];
            array[largestIndex] = swap;
            heapifyDown(largestIndex);
        }
    }

    /**
     * szukanie i usuwanie danej liczby, jeśli jest w kopcu; jeśli jest kilka przypadków wystąpienia takiej liczby usunięte zostaje jedynie pierwsze znalezione wystąpienie
     * @param number
     * @return true jeśli usunięto liczbę, false jeśli nie udało się usunąć liczby
     */
    bool removeGivenNumber(int number) {
        for (unsigned int i = 0; i < heapSize; ++i) {
            if (array[i] == number) {
                --heapSize;
                int *newArray = new int[heapSize];
                for (unsigned int j = 0; j < i; ++j) {
                    newArray[j] = array[j];
                }
                //jeśli da się, zamiana usuwanego elementu z ostatnim liściem, korzenia nie wstawiamy na koniec bo i tak jest usuwany
                if (heapSize)
                    newArray[i] = array[heapSize];
                for (unsigned int j = i + 1; j < heapSize; ++j) {
                    newArray[j] = array[j];
                }
                delete[] array;
                array = newArray;
                heapifyDown(i);
                return true;
            }
        }
        return false;
    }

    //todo removeGivenElement żeby moć testować samo usuwanie
    void removeGivenElement(unsigned int index) {
        if (index < heapSize) {
            --heapSize;
            int *newArray = new int[heapSize];
            for (unsigned int j = 0; j < index; ++j) {
                newArray[j] = array[j];
            }
            //jeśli da się, zamiana usuwanego elementu z ostatnim liściem, korzenia nie wstawiamy na koniec bo i tak jest usuwany
            if (heapSize)
                newArray[index] = array[heapSize];
            for (unsigned int j = index + 1; j < heapSize; ++j) {
                newArray[j] = array[j];
            }
            delete[] array;
            array = newArray;
            heapifyDown(index);
        }
    }

    /**
     * wyszukanie podanej liczby w kopcu
     * @param number
     * @return true, jeśli znaleziono liczbę, false, jeśli nie znaleziono liczby
     */
    bool findGivenNumber(int number) {
        for (unsigned int i = 0; i < heapSize; ++i) {
            if (array[i] == number) {
                return true;
            }
        }
        return false;
    }

    /**
     * test sprawdzający poprawność własności kopca
     * @return
     */
    bool heapTest() {
        int i = heapSize - 1;
        for (; i > 0; --i) {
            unsigned int parentIndex = (i - 1) / 2;
            if (array[i] > array[parentIndex]) {
                return false;
            }
        }
        return true;
    }

    /**
     * wyświetla kopiec w konsoli, metoda ze strony https://eduinf.waw.pl/inf/alg/001_search/0112.php
     */
    void print() {
        //ustawienie stringów odpowiedzialnych za wyświetlanie gałęzi drzewa
        cr[0] = 218;
        cr[1] = 196;
        cl[0] = 192;
        cl[1] = 196;
        cp[0] = 179;
        printRecursive("", "", 0);
        cout << '\n';
    }

    /**
     * funkcja pomocnicza do wypisywania drzewa na ekranie, można również wykorzystać do wypisania poddrzewa zaczynającego się od wierzchołka o danym indeksie
     * @param sp "tekst do wyświetlenia w wierszu pośrednim"
     * @param sn "tekst do wyświetlenia przed węzłem"
     * @param index
     */
    void printRecursive(const string& sp, const string& sn, unsigned int index) {
        if (index < heapSize) {
            string s = sp; //"tekst do wyświetlenia w wierszach pośrednich dla synów"
            if (sn == cr)
                s[s.length() - 2] = ' ';
            printRecursive(s + cp, cr, 2 * index + 2);
            s = s.substr(0, sp.length() - 2);
            cout << s << sn << array[index] << '\n';
            s = sp;
            if (sn == cl)
                s[s.length() - 2] = ' ';
            printRecursive(s + cp, cl, 2 * index + 1);
        }
    }
};
