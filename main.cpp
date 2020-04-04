#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include "Array.cpp"
#include "DoublyLinkedList.cpp"
#include "BinaryHeapMax.cpp"
#include "RedBlackTree.cpp"

using namespace std;


int main() {
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
        if (i % 10000==0) cout << i << ", errors: " << errorCounter << endl;
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
        cout << "Yeet"<<endl;
    heap->add(21);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<endl;
    heap->add(0);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<endl;
    heap->removeRoot();
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<endl;
    heap->removeGivenNumber(17);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<endl;*/
    /*BinaryHeapMax *heap=new BinaryHeapMax();
    heap->removeGivenNumber(0);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<endl;
    heap->add(1);
    heap->removeGivenNumber(1);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<endl;
    heap->add(1);
    heap->add(2);
    heap->print();
    if (heap->heapTest())
        cout << "Yeet"<<endl;
    heap->removeGivenNumber(2);
    heap->print();//todo podczas run jest tu syf, podczas debugu jest 1 jak powinno, i dont even know anymore...
    if (heap->heapTest())
        cout << "Yeet"<<endl;*/
    int tab[] = {1, 2, 3, 4, 5, 6, 7};
    RedBlackTree *tree = new RedBlackTree(tab, 7);
//    tree->add(1);
//    tree->add(2);
//    tree->add(3);
//    tree->add(4);
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
    return 0;
}