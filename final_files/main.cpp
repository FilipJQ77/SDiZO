#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <fstream>
#include "Array.cpp"
#include "DoublyLinkedList.cpp"
#include "BinaryHeapMax.cpp"
#include "RedBlackTree.cpp"

using std::cin;
using std::cout;
using std::ios;
using std::fstream;

/**
 * fragment kodu z https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
 * odpowiadaj¹cy za przygotowanie QueryPerformanceCounter oraz metod umo¿liwiaj¹cych mierzenie czasu
 */
double pcFreq = 0.0;
__int64 counterStart = 0;

/**
 * w³¹cza (od nowa) stoper
 */
void timerStart() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";
    pcFreq = double(li.QuadPart) / 1000000.0;
    QueryPerformanceCounter(&li);
    counterStart = li.QuadPart;
}

/**
 * zwraca czas w mikrosekundach od momentu ostatniego uruchomienia stopera
 * @return
 */
double timerTime() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - counterStart) / pcFreq;
}

/**
 * metoda która pobiera dane z podanego pliku
 * @param filename
 * @return
 */
int* getDataFromFile(string filename) {
    fstream file;
    file.open(filename, ios::in);
    int* array = nullptr;
    string str;
    int number;
    if (file.good()) {
        getline(file, str);
        number = stoi(str);
        array = new int[number + 1];
        array[0] = number;
        unsigned int i = 1;
        while (!file.eof()) {
            getline(file, str);
            number = stoi(str);
            array[i] = number;
            ++i;
        }
        file.close();
        return array;
    }
    else throw std::exception();
}

/**
 * metody do testów:
 */
 /**
  * losuje liczbê z danego przedzia³u
  * @param mini
  * @param maxi
  * @return
  */
int randomNumber(int mini, int maxi) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(mini, maxi);
    return distribution(mt);
}

/**
 * generuje losowe dane i zapisuje je do podanej tablicy
 * @param array
 * @param size
 */
void randomData(int* array, int size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);
    for (int i = 0; i < size; ++i) {
        array[i] = distribution(mt);
        //losowa liczba to distribution(mt)
    }
}

/**
 * automatyczny analizator wyników, nale¿y podaæ tabelê wyników oraz iloœæ tych¿e wyników
 * @param results
 * @param resultsAmount
 */
long double analyseResults(const double results[], int resultsAmount) {
    long double averageTime = 0;
    for (int i = 0; i < resultsAmount; ++i) {
        averageTime += results[i];
    }
    return averageTime / resultsAmount;
}

/**
 * menu
 */
string arrayAndListMenu = "\n1 - Stworz nowa pusta strukture\n2 - Stworz nowa strukture na podstawie danych z pliku\n3 - Dodaj liczbe na poczatek struktury\n4 - Dodaj liczbe na koniec struktury\n5 - Dodaj liczbe gdziekolwiek w strukturze\n6 - Usun liczbe na poczatku struktury\n7 - Usun liczbe na koncu struktury\n8 - Usun liczbe w dowolnym miejscu struktury\n9 - Usun podana liczbe ze struktury (pierwsze wystapienie)\n10 - Wyszukanie podanej liczby w strukturze (wynik - znaleziono/nie znaleziono)\n11 - Wyswietl liczbe ktora w strukturze jest pod podanym indeksem\n12 - Wyswietl strukture\n0 - Wyjdz do glownego menu\n";
string treeMenu = "\n1 - Stworz nowa pusta strukture\n2 - Stworz nowa strukture na podstawie danych z pliku\n3 - Dodaj liczbe do struktury\n4 - Usun liczbe ze struktury\n5 - Wyszukanie podanej liczby w strukturze (wynik - znaleziono/nie znaleziono)\n6 - Wyswietl strukture\n0 - Wyjdz do glownego menu\n";


/**
 * oddzielne pêtle do ka¿dej struktury
 */
void arrayLoop() {
    bool run = true;
    string inputS;
    int inputI;
    auto* structure = new Array();
    while (run) {
        cout << arrayAndListMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        }
        catch (std::exception & e) {
            cout << "Wyjatek: " << e.what() << "\n";
            continue;
        }
        switch (inputI) {
        case 1:
            delete structure;
            structure = new Array();
            break;
        case 2:
            cout << "Podaj nazwe pliku z ktorego maja byc wczytane dane\n";
            getline(cin, inputS);
            int* data;
            try {
                data = getDataFromFile(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n"
                    << "Cos poszlo nie tak, bedziesz nadal dzialal na poprzedniej strukturze, nacisnij enter aby kontynuowac\n";
                getline(cin, inputS);
                break;
            }
            delete structure;
            structure = new Array(data + 1, data[0]);
            break;
        case 3:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->addFront(inputI);
            break;
        case 4:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->addBack(inputI);
            break;
        case 5:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            cout << "Podaj indeks\n";
            unsigned int position;
            getline(cin, inputS);
            try {
                position = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->addAnywhere(inputI, position);
            break;
        case 6:
            structure->removeFront();
            break;
        case 7:
            structure->removeBack();
            break;
        case 8:
            cout << "Podaj indeks\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->removeAnywhere(inputI);
            break;
        case 9:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->removeGivenNumber(inputI);
            break;
        case 10:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            if (structure->findGivenNumber(inputI))
                cout << "Znaleziono podana liczbe\n";
            else
                cout << "Nie znaleziono podanej liczby\n";
            break;
        case 11:
            cout << "Podaj indeks\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            try {
                structure->getNumberAt(inputI);
            }
            catch (std::invalid_argument & e) {
                cout << "Wyjatek: " << e.what() << "\n";
            }
            break;
        case 12:
            structure->print();
            cout << "Nacisnij enter aby kontynuowac";
            getline(cin, inputS);
            break;
            break;
        case 0:
            run = false;
            delete structure;
            break;
        default:
            break;
        }
    }

}

void listLoop() {
    bool run = true;
    string inputS;
    int inputI;
    auto* structure = new DoublyLinkedList();
    while (run) {
        cout << arrayAndListMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        }
        catch (std::exception & e) {
            cout << "Wyjatek: " << e.what() << "\n";
            continue;
        }
        switch (inputI) {
        case 1:
            delete structure;
            structure = new DoublyLinkedList();
            break;
        case 2:
            cout << "Podaj nazwe pliku z ktorego maja byc wczytane dane\n";
            getline(cin, inputS);
            int* data;
            try {
                data = getDataFromFile(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n"
                    << "Cos poszlo nie tak, bedziesz nadal dzialal na poprzedniej strukturze, nacisnij enter aby kontynuowac\n";
                getline(cin, inputS);
                break;
            }
            delete structure;
            structure = new DoublyLinkedList(data + 1, data[0]);
            break;
        case 3:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->addFront(inputI);
            break;
        case 4:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->addBack(inputI);
            break;
        case 5:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            cout << "Podaj indeks\n";
            unsigned int position;
            getline(cin, inputS);
            try {
                position = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->addAnywhere(inputI, position);
            break;
        case 6:
            structure->removeFront();
            break;
        case 7:
            structure->removeBack();
            break;
        case 8:
            cout << "Podaj indeks\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->removeAnywhere(inputI);
            break;
        case 9:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->removeGivenNumber(inputI);
            break;
        case 10:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            if (structure->findGivenNumber(inputI))
                cout << "Znaleziono podana liczbe\n";
            else
                cout << "Nie znaleziono podanej liczby\n";
            break;
        case 11:
            cout << "Podaj indeks\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            try {
                structure->getNumberAt(inputI);
            }
            catch (std::invalid_argument & e) {
                cout << "Wyjatek: " << e.what() << "\n";
            }
            break;
        case 12:
            structure->print();
            cout << "Nacisnij enter aby kontynuowac";
            getline(cin, inputS);
            break;
        case 0:
            run = false;
            delete structure;
            break;
        default:
            break;
        }
    }

}

void heapLoop() {
    bool run = true;
    string inputS;
    int inputI;
    auto* structure = new BinaryHeapMax();
    while (run) {
        cout << treeMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        }
        catch (std::exception & e) {
            cout << "Wyjatek: " << e.what() << "\n";
            continue;
        }
        switch (inputI) {
        case 1:
            delete structure;
            structure = new BinaryHeapMax();
            break;
        case 2:
            cout << "Podaj nazwe pliku z ktorego maja byc wczytane dane\n";
            getline(cin, inputS);
            int* data;
            try {
                data = getDataFromFile(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n"
                    << "Cos poszlo nie tak, bedziesz nadal dzialal na poprzedniej strukturze, nacisnij enter aby kontynuowac\n";
                getline(cin, inputS);
                break;
            }
            delete structure;
            structure = new BinaryHeapMax(data + 1, data[0]);
            break;
        case 3:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->add(inputI);
            break;
        case 4:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->removeGivenNumber(inputI);
            break;
        case 5:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            if (structure->findGivenNumber(inputI))
                cout << "Znaleziono podana liczbe\n";
            else
                cout << "Nie znaleziono podanej liczby\n";
            break;
        case 6:
            structure->print();
            cout << "Nacisnij enter aby kontynuowac";
            getline(cin, inputS);
            break;
        case 0:
            run = false;
            delete structure;
            break;
        default:
            break;
        }
    }

}

void rbTreeLoop() {
    bool run = true;
    string inputS;
    int inputI;
    auto* structure = new RedBlackTree();
    while (run) {
        cout << treeMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        }
        catch (std::exception & e) {
            cout << "Wyjatek: " << e.what() << "\n";
            continue;
        }
        switch (inputI) {
        case 1:
            delete structure;
            structure = new RedBlackTree();
            break;
        case 2:
            cout << "Podaj nazwe pliku z ktorego maja byc wczytane dane\n";
            getline(cin, inputS);
            int* data;
            try {
                data = getDataFromFile(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n"
                    << "Cos poszlo nie tak, bedziesz nadal dzialal na poprzedniej strukturze, nacisnij enter aby kontynuowac\n";
                getline(cin, inputS);
                break;
            }
            delete structure;
            structure = new RedBlackTree(data + 1, data[0]);
            break;
        case 3:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->add(inputI);
            break;
        case 4:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            structure->removeGivenNumber(inputI);
            break;
        case 5:
            cout << "Podaj liczbe\n";
            getline(cin, inputS);
            try {
                inputI = stoi(inputS);
            }
            catch (std::exception & e) {
                cout << "Wyjatek: " << e.what() << "\n";
                break;
            }
            if (structure->findGivenNumber(inputI))
                cout << "Znaleziono podana liczbe\n";
            else
                cout << "Nie znaleziono podanej liczby\n";
            break;
        case 6:
            structure->print();
            cout << "Nacisnij enter aby kontynuowac";
            getline(cin, inputS);
            break;
        case 0:
            run = false;
            delete structure;
            break;
        default:
            break;
        }
    }

}

/**
 * todo wiem, ¿e menu jest zrobione w tragiczny sposób, i lepiej by by³o wykorzystaæ klasê abstrakcyjn¹ DataStructure oraz polimorfizm aby nie mieæ 4 praktycznie tych samych fragmentów kodu, ale ju¿ nie mia³em czasu aby przebudowywaæ program, i tak by³o proœciej
 */
void mainLoop() {
    string inputS;
    int inputI;
    bool run = true;
    cout << "Witaj w programie o strukturach danych\n";
    while (run) {
        cout
            << "\nWybierz jaka strukture chcesz stworzyc (wpisz):\n1 - tablica\n2 - lista dwukierunkowa\n3 - kopiec binarny typu maksimum\n4 - drzewo czerwono-czarne\n0 - wyjdz z programu\n";
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        }
        catch (std::exception & e) {
            cout << "Wyjatek: " << e.what() << "\n";
            continue;
        }
        switch (inputI) {
        case 1:
            arrayLoop();
            break;
        case 2:
            listLoop();
            break;
        case 3:
            heapLoop();
            break;
        case 4:
            rbTreeLoop();
            break;
        case 0:
            run = false;
            break;
        default:
            break;
        }
    }
}

int main() {
    mainLoop();
    return 0;
}