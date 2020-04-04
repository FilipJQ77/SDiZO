#include <iostream>
//#include <string>
#include <windows.h>
#include <fstream>
#include "Array.cpp"
#include "DoublyLinkedList.cpp"
#include "BinaryHeapMax.cpp"
#include "RedBlackTree.cpp"
#include "AVLTree.cpp"

using std::cout;

/**
 * fragment kodu z https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
 * odpowiadający za przygotowanie QueryPerformanceCounter oraz metod umożliwiających mierzenie czasu
 */
double pcFreq = 0.0;
__int64 counterStart = 0;

/**
 * włącza (od nowa) stoper
 */
void startCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";
    pcFreq = double(li.QuadPart) / 1000000.0;
    QueryPerformanceCounter(&li);
    counterStart = li.QuadPart;
}

/**
 * zwraca czas w mikrosekundach od momentu uruchomienia stopera
 * @return
 */
double getCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - counterStart) / pcFreq;
}

int main() {
    startCounter();
    for (int i = 0; i < 1000000; i++){}
    double x = getCounter();
    startCounter();
    for (int i = 0; i < 1000000; ++i){}
    double y = getCounter();
    cout << x << ", " << y << '\n';
    //todo postincrement jest szybszy? wtf
    /*DoublyLinkedList *list = new DoublyLinkedList();
    for (int i = 0; i < 9; ++i) {
        list->addBack(i);
    }
    list->addAnywhere(11, 4);
    int tab[] = {1, 2, 3, 4, 5};
    DoublyLinkedList *list1 = new DoublyLinkedList(tab, 5);
    */

    /*srand(time(NULL));
    BinaryHeapMax *heap = new BinaryHeapMax();
    int errorCounter = 0;
    for (int i = 0; i < 20000000; ++i) {
        int number = rand() % 10000;
        heap->add(number);
        heap->print();
        if (!(heap->heapTest()))
            ++errorCounter;
        if (i % 10 == 0) {
            heap->removeGivenNumber(number);
        }
        if (i % 500 == 0) {
            delete heap;
            heap = new BinaryHeapMax();
        }
        if (i % 10000==0) cout << i << ", errors: " << errorCounter << '\n';
    }
    cout << errorCounter;*/
//    auto heap = new BinaryHeapMax();
//    srand(time(NULL));
//    for (int i = 0; i < 10; ++i) {
//        int number = rand() % 100;
//        heap->add(number);
//    }
//    heap->print();
//    heap->removeGivenNumber(7);
//    heap->print();
//    heap->removeRoot();
//    heap->print();
//    RedBlackTree *a = new RedBlackTree();
//    DoublyLinkedList *a = new DoublyLinkedList();
//    a->removeAnywhere(0);
//    a->addFront(2);
//    a->addFront(3);
//    a->removeAnywhere(1);
//    a->removeAnywhere(0);
//    a->addBack(3);
//    a->addBack(4);
//    a->removeAnywhere(1);
//    a->addBack(5);
//    a->addBack(6);
//    a->add(3);
//    a->add(4);
//    a->add(1);
//    a->add(5);
//    a->print();
    /*int tab[] = {1, 3, 4, 7, 19, 18, 16, 10, 8, 2, 5, 20, 17, 15, 11, 6, 9, 12, 14, 13};
    BinaryHeapMax *heap = new BinaryHeapMax(tab, 20);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';
    heap->add(21);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';
    heap->add(0);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';
    heap->removeRoot();
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';
    heap->removeGivenNumber(17);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';*/
    /*BinaryHeapMax *heap=new BinaryHeapMax();
    heap->removeGivenNumber(0);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';
    heap->add(1);
    heap->removeGivenNumber(1);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';
    heap->add(1);
    heap->add(2);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<'\n';
    heap->removeGivenNumber(2);
    heap->print();//todo podczas run jest tu syf, podczas debugu jest 1 jak powinno, i dont even know anymore...
    if (heap->heapTest())
        cout << "Yeet"<<'\n';*/
    /*int tab[] = {1, 2, 3, 4, 5, 6, 7};
    RedBlackTree *tree;
    tree = new RedBlackTree(tab, 7);
    tree->print();
    tree->remove(7);
    tree->print();
    tree->add(8);
    tree->print();
    tree->add(7);
    tree->print();
    tree->add(0);
    tree->print();
    tree->remove(7);
    tree->print();
    tree->remove(2);
    tree->print();
    tree->remove(-1);
    delete tree;*/
    return 0;
}