#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <fstream>
#include "Array.cpp"
#include "DoublyLinkedList.cpp"
#include "BinaryHeapMax.cpp"
#include "RedBlackTree.cpp"
#include "AVLTree.cpp"

using std::cin;
using std::cout;
using std::ios;
using std::fstream;

/**
 * fragment kodu z https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
 * odpowiadający za przygotowanie QueryPerformanceCounter oraz metod umożliwiających mierzenie czasu
 */
double pcFreq = 0.0;
__int64 counterStart = 0;

/**
 * włącza (od nowa) stoper
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

int *getDataFromFile(string filename) {
    fstream file;
    file.open(filename, ios::in);
    int *array = nullptr;
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
    } else throw std::exception();
}

string arrayAndListMenu = "1 - Stworz nowa pusta strukture\n2 - Stworz nowa strukture na podstawie danych z pliku\n3 - Dodaj liczbe na poczatek struktury\n4 - Dodaj liczbe na koniec struktury\n5 - Dodaj liczbe gdziekolwiek w strukturze\n6 - Usun liczbe na poczatku struktury\n7 - Usun liczbe na koncu struktury\n8 - Usun liczbe w dowolnym miejscu struktury\n9 - Usun podana liczbe ze struktury (pierwsze wystapienie)\n10 - Wyszukanie podanej liczby w strukturze (wynik - znaleziono/nie znaleziono)\n11 - Wyswietl liczbe ktora w strukturze jest pod podanym indeksem\n12 - Wyswietl strukture\n0 - Wyjdz do glownego menu\n";
string treeMenu = "1 - Stworz nowa pusta strukture\n2 - Stworz nowa strukture na podstawie danych z pliku\n3 - Dodaj liczbe do struktury\n4 - Usun liczbe ze struktury\n5 - Wyszukanie podanej liczby w strukturze (wynik - znaleziono/nie znaleziono)\n6 - Wyswietl strukture\n0 - Wyjdz do glownego menu\n";

void arrayLoop() {
    bool run = true;
    string inputS;
    int inputI;
    auto *structure = new Array();
    while (run) {
        cout << arrayAndListMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        } catch (std::exception &e) {
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
                int *data;
                try {
                    data = getDataFromFile(inputS);
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
                    cout << "Wyjatek: " << e.what() << "\n";
                    break;
                }
                cout << "Podaj indeks\n";
                unsigned int position;
                getline(cin, inputS);
                try {
                    position = stoi(inputS);
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
                    cout << "Wyjatek: " << e.what() << "\n";
                    break;
                }
                try {
                    structure->getNumberAt(inputI);
                } catch (std::invalid_argument &e) {
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
    auto *structure = new DoublyLinkedList();
    while (run) {
        cout << arrayAndListMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        } catch (std::exception &e) {
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
                int *data;
                try {
                    data = getDataFromFile(inputS);
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
                    cout << "Wyjatek: " << e.what() << "\n";
                    break;
                }
                cout << "Podaj indeks\n";
                unsigned int position;
                getline(cin, inputS);
                try {
                    position = stoi(inputS);
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
                    cout << "Wyjatek: " << e.what() << "\n";
                    break;
                }
                try {
                    structure->getNumberAt(inputI);
                } catch (std::invalid_argument &e) {
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
    auto *structure = new BinaryHeapMax();
    while (run) {
        cout << treeMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        } catch (std::exception &e) {
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
                int *data;
                try {
                    data = getDataFromFile(inputS);
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
    auto *structure = new RedBlackTree();
    while (run) {
        cout << treeMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        } catch (std::exception &e) {
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
                int *data;
                try {
                    data = getDataFromFile(inputS);
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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

void avlTreeLoop() {
    bool run = true;
    string inputS;
    int inputI;
    auto *structure = new AVLTree();
    while (run) {
        cout << treeMenu;
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        } catch (std::exception &e) {
            cout << "Wyjatek: " << e.what() << "\n";
            continue;
        }
        switch (inputI) {
            case 1:
                delete structure;
                structure = new AVLTree();
                break;
            case 2:
                cout << "Podaj nazwe pliku z ktorego maja byc wczytane dane\n";
                getline(cin, inputS);
                int *data;
                try {
                    data = getDataFromFile(inputS);
                } catch (std::exception &e) {
                    cout << "Wyjatek: " << e.what() << "\n"
                         << "Cos poszlo nie tak, bedziesz nadal dzialal na poprzedniej strukturze, nacisnij enter aby kontynuowac\n";
                    getline(cin, inputS);
                    break;
                }
                delete structure;
                structure = new AVLTree(data + 1, data[0]);
                break;
            case 3:
                cout << "Podaj liczbe\n";
                getline(cin, inputS);
                try {
                    inputI = stoi(inputS);
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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
                } catch (std::exception &e) {
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

int randomNumber(int mini, int maxi) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(mini, maxi);
    return distribution(mt);
}

void randomData(int *array, int size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);
    for (int i = 0; i < size; ++i) {
        array[i] = distribution(mt);
        //losowa liczba to distribution(mt)
    }
}

void analyseResults(const double results[], long double &averageTime) {
    averageTime = 0;
    for (int i = 0; i < 1000; ++i) {
        averageTime += results[i];
    }
    averageTime /= 1000;
}

//void completeTest() {
//    cout
//            << "Czy na pewno chcesz przeprowadzic kompletny test? Nie ma mozliwosci jego przerwania. Wpisz \'Y\' aby przeprowadzic test, lub cokolwiek innego, zeby nie przeprowadzic testu.\n";
//    string s;
//    getline(cin, s);
//    if (s == "Y" || s == "y") {
//        cout
//                << "Podaj nazwe pliku do ktorego zostana zapisane wyniki testow, jesli plik o podanej nazwie istnieje zostanie on nadpisany!\n";
//        getline(cin, s);
//        fstream file;
//        file.open(s, ios::out);
//        /*file<<*/cout << "Nazwa struktury;Operacja;Rozmiar struktury;Minimalny czas;Sredni czas;Maksymalny czas\n";
//        int structureSizes[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000,
//                                15000, 16000, 17000, 18000, 19000, 20000};
//        double results[1000];
//        long double averageTime;
//        int *data;
//        for (int structureSize : structureSizes) {
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                timerStart();
//                structure->addFront(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Dodanie na poczatek;" << structureSize << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                timerStart();
//                structure->addBack(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Dodanie na koniec;" << structureSize << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                timerStart();
//                structure->addAnywhere(number, index);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Dodanie w dowolne miejsce;" << structureSize << ";" << ";"
//                           << averageTime
//                           << ";"
//                           << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                delete data;
//                timerStart();
//                structure->removeFront();
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Usuniecie na poczatku;" << structureSize << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                delete data;
//                timerStart();
//                structure->removeBack();
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Usuniecie na koncu;" << structureSize << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                delete data;
//                unsigned int index = randomNumber(0, structureSize - 1);
//                timerStart();
//                structure->removeAnywhere(index);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Usuniecie w dowolnym miejscu;" << structureSize << ";" <<  << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->findGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Wyszukanie elementu (wiemy ze jest w strukturze);" << structureSize << ";"
//                           <<
//                           << ";" << averageTime << ";" <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->removeGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Wyszukanie i usuniecie elementu (wiemy ze jest w strukturze);" << structureSize
//                           << ";"
//                           <<  << ";" << averageTime << ";" <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new Array(data, structureSize);
//                delete data;
//                unsigned int index = randomNumber(0, structureSize - 1);
//                timerStart();
//                structure->getNumberAt(index);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Tablica;Wydobycie elementu na danej pozycji;" << structureSize << ";" <<
//                           << ";" << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                timerStart();
//                structure->addFront(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Dodanie na poczatek;" << structureSize << ";" <<  << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                timerStart();
//                structure->addBack(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Dodanie na koniec;" << structureSize << ";" <<  << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                timerStart();
//                structure->addAnywhere(number, index);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Dodanie w dowolne miejsce;" << structureSize << ";" <<  << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                delete data;
//                timerStart();
//                structure->removeFront();
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Usuniecie na poczatku;" << structureSize << ";" <<  << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                delete data;
//                timerStart();
//                structure->removeBack();
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Usuniecie na koncu;" << structureSize << ";" <<  << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                delete data;
//                unsigned int index = randomNumber(0, structureSize - 1);
//                timerStart();
//                structure->removeAnywhere(index);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Usuniecie w dowolnym miejscu;" << structureSize << ";" <<
//                           << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->findGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Wyszukanie elementu (wiemy ze jest w strukturze);" << structureSize
//                           << ";"
//                           <<
//                           << ";" << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->removeGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Wyszukanie i usuniecie elementu (wiemy ze jest w strukturze);"
//                           << structureSize
//                           << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new DoublyLinkedList(data, structureSize);
//                delete data;
//                unsigned int index = randomNumber(0, structureSize - 1);
//                timerStart();
//                structure->getNumberAt(index);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Lista dwukierunkowa;Wydobycie elementu na danej pozycji;" << structureSize << ";"
//                           <<
//                           << ";" << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            //todo kopiec porównanie między dodawaniem 1 elementu a stworzeniem od razu z całej tablicy
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new BinaryHeapMax(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                timerStart();
//                structure->add(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Kopiec;Dodanie;" << structureSize << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new BinaryHeapMax(data, structureSize);
//                delete data;
//                unsigned int index = randomNumber(0, structureSize - 1);
//                timerStart();
//                structure->removeGivenElement(index);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Kopiec;Usuniecie;" << structureSize << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new BinaryHeapMax(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->findGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Kopiec;Wyszukanie elementu (wiemy ze jest w strukturze);" << structureSize << ";"
//                           <<
//                           << ";" << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new BinaryHeapMax(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->removeGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Kopiec;Wyszukanie i usuniecie elementu (wiemy ze jest w strukturze);" << structureSize
//                           << ";"
//                           << averageTime << "\n";
////todo drzewo aaaaaaa
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new RedBlackTree(data, structureSize);
//                delete data;
//                int number = randomNumber(INT_MIN, INT_MAX);
//                timerStart();
//                structure->add(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Drzewo czerwono-czarne;Dodanie;" << structureSize << ";" << averageTime << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new RedBlackTree(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                auto *a = structure->getNodeWithGivenNumber(number);
//                //todo sprawdz czy na pewno dziala
//                timerStart();
//                structure->removeGivenElement(a);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Drzewo czerwono-czarne;Usuniecie;" << structureSize << ";" <<  << ";"
//                           << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new RedBlackTree(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->findGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Drzewo czerwono-czarne;Wyszukanie elementu (wiemy ze jest w strukturze);"
//                           << structureSize << ";"
//                           <<
//                           << ";" << averageTime
//                           << ";"
//                           <<  << "\n";
//
//            for (double &result : results) {
//                data = randomData(structureSize);
//                auto *structure = new RedBlackTree(data, structureSize);
//                unsigned int index = randomNumber(0, structureSize - 1);
//                int number = data[index];
//                delete data;
//                timerStart();
//                structure->removeGivenNumber(number);
//                result = timerTime();
//                delete structure;
//            }
//            analyseResults(results, averageTime);
//            /*file<<*/cout << "Drzewo czerwono-czarne;Wyszukanie i usuniecie elementu (wiemy ze jest w strukturze);"
//                           << structureSize << ";" << averageTime << "\n";
//
//
//            //todo drzewo avl jeśli się uda
////            for (double & result : results) {
////                data = randomData(structureSize);
////                auto *structure = new AVLTree(data, structureSize);
////                delete data;
////                int number = randomNumber(INT_MIN, INT_MAX);
////                timerStart();
////                structure->add(number);
////                result = timerTime();
////                delete structure;
////            }
////            analyseResults(results, averageTime);
////            /*file<<*/cout<< "Drzewo czerwono-czarne;Dodanie;" << structureSize << ";" <<  << ";" << averageTime
////                 << ";"
////                 <<  << "\n";
////
////            for (double & result : results) {
////                data = randomData(structureSize);
////                auto *structure = new AVLTree(data, structureSize);
////                unsigned int index = randomNumber(0, structureSize - 1);
////                int number = data[index];
////                delete data;
////                auto *a = structure->getNodeWithGivenNumber(number);
////                //todo sprawdz czy na pewno dziala
////                timerStart();
////                structure->removeGivenElement(a);
////                result = timerTime();
////                delete structure;
////            }
////            analyseResults(results, averageTime);
////            /*file<<*/cout<< "Drzewo czerwono-czarne;Usuniecie;" << structureSize << ";" <<  << ";" << averageTime
////                 << ";"
////                 <<  << "\n";
////
////            for (double & result : results) {
////                data = randomData(structureSize);
////                auto *structure = new AVLTree(data, structureSize);
////                unsigned int index = randomNumber(0, structureSize - 1);
////                int number = data[index];
////                delete data;
////                timerStart();
////                structure->findGivenNumber(number);
////                result = timerTime();
////                delete structure;
////            }
////            analyseResults(results, averageTime);
////            /*file<<*/cout<< "Drzewo czerwono-czarne;Wyszukanie elementu (wiemy ze jest w strukturze);" << structureSize << ";" <<
////                 << ";" << averageTime
////                 << ";"
////                 <<  << "\n";
////
////            for (double & result : results) {
////                data = randomData(structureSize);
////                auto *structure = new AVLTree(data, structureSize);
////                unsigned int index = randomNumber(0, structureSize - 1);
////                int number = data[index];
////                delete data;
////                timerStart();
////                structure->removeGivenNumber(number);
////                result = timerTime();
////                delete structure;
////            }
////            analyseResults(results, averageTime);
////            /*file<<*/cout<< "Drzewo czerwono-czarne;Wyszukanie i usuniecie elementu (wiemy ze jest w strukturze);" << structureSize << ";" <<  << ";" << averageTime
////                 << ";"
////                 <<  << "\n";
//
//        }
//        //file.close();
////            /*file<<*/cout<< distribution(mt) << "\n";
//    }
//}

/**
 * todo wiem, że menu jest zrobione w tragiczny sposób, i lepiej by było wykorzystać klasę abstrakcyjną DataStructure oraz polimorfizm aby nie mieć 5 praktycznie tych samych fragmentów kodu, ale już nie miałem czasu aby przebudowywać program, i tak było prościej
 */
void mainLoop() {
    string inputS;
    int inputI;
    bool run = true;
    cout << "Witaj w programie o strukturach danych\n";
    while (run) {
        cout
                << "Wpisz:\n1 - Stworz nowa strukture\n2 - Przeprowadz kompletny test wszystkich struktur\n0 - Wyjdz z programu\n";
        getline(cin, inputS);
        try {
            inputI = stoi(inputS);
        } catch (std::exception &e) {
            cout << "Wyjatek: " << e.what() << "\n";
            continue;
        }
        switch (inputI) {
            case 1:
                cout
                        << "Wybierz jaka strukture chcesz stworzyc:\n1 - tablica\n2 - lista dwukierunkowa\n3 - kopiec binarny typu maksimum\n4 - drzewo czerwono-czarne\n5 - drzewo AVL\n";
                getline(cin, inputS);
                try {
                    inputI = stoi(inputS);
                } catch (std::exception &e) {
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
                    case 5:
                        avlTreeLoop();
                        break;
                    default:
                        break;
                }
                break;
            case 2:
//                completeTest();
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