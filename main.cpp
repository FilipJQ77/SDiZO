#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include "Array.cpp"
#include "DoublyLinkedList.cpp"
#include "BinaryHeapMax.cpp"

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
    auto heap = new BinaryHeapMax();
    heap->add(1);
    heap->add(3);
    heap->add(7);
    heap->add(5);
    heap->add(4);
    heap->add(11);
    heap->print();
    heap->removeGivenNumber(7);
    heap->print();
    heap->removeRoot();
    heap->print();
    return 0;
}