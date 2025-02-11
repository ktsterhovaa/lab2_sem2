#ifndef LR2_MAIN_FUNCTIONS_H
#define LR2_MAIN_FUNCTIONS_H
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fcntl.h>
#include <fstream>
#include <vector>
#include <iterator>

#include "MutableArraySequence.h"
#include "ListSequence.h"


void printMenu(){
    wprintf(L"0. STOP\n");
    wprintf(L"1. Dynamic Arrays\n");
    wprintf(L"2. Linked Lists\n");
    wprintf(L"Choose:");
}
void printArrayMenu(){
    wprintf(L"0. Exit\n");
    wprintf(L"1. Add an element to the end of the array\n");
    wprintf(L"2. Add an element to the beginning of the array\n");
    wprintf(L"3. Add an element to an array by index\n");
    wprintf(L"4. Remove an element in an array by index\n");
    wprintf(L"5. Get a subsequence\n");
    wprintf(L"6. Find a subsequence\n");
    wprintf(L"7. Concatenation of two arrays\n");
    wprintf(L"Choose an action:");
}
void printListMenu(){
    wprintf(L"0. Exit\n");
    wprintf(L"1. Add an element to the end of the list\n");
    wprintf(L"2. Add an element to the top of the list\n");
    wprintf(L"3. Add an element to the list by index\n");
    wprintf(L"4. Remove an element in the list by index\n");
    wprintf(L"5. Get a subsequence\n");
    wprintf(L"6. Find a subsequence\n");
    wprintf(L"7. Concatenation of two lists\n");
    wprintf(L"8. Application of functions map, where, reduce\n");
    wprintf(L"9. Iterator\n");

    wprintf(L"Choose an action: ");
}

int mapFunction(int x) {
    return x * x;
}

bool whereFunction(int x) {
    bool result = (x % 2) == 0;
    wcout << L"  where: number " << x << L" even: " << result << endl;
    return result;
}


int reduceFunction(int a, int b) {
    int result = a + b;
    wcout << L"  reduce: " << a << L" + " << b << " = " << result << endl;
    return result;
}

void linkedListIterator() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    try {
        LinkedList<int> linkedList(data, length);
        auto it = linkedList.begin();

        for (int i = 0; i < length; i++) {
            wcout << L"Element under the index " << i << L": " << *it << L"\n";
            it++;
        }

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}
void printSequence(Sequence<int> *sequence) {
    std::vector<wchar_t> mas;
    //mas.push_back(L'П');
    for (int i = 0; i < sequence->getLength(); i++) {
        wcout << to_wstring(sequence->get(i)) << L" ";
        mas.push_back(sequence->get(i));
    }

    wcout << L"\n";
}
void linkedListMapWhereReduce() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    ListSequence<int> listSequence(data, length);
    wprintf(L"You enter the sequence: ");
    printSequence(&listSequence);
    wprintf(L"Apply function map\n");
    Sequence<int> *mapRes =  listSequence.map(mapFunction);
    printSequence(mapRes);
    delete mapRes;

    wprintf(L"Apply function where\n");
    Sequence<int> *whereRes = listSequence.where(whereFunction);
    printSequence(whereRes);
    delete whereRes;

    wprintf(L"Apply function reduce\n");
    int reduceRes = listSequence.reduce(reduceFunction);
    wcout << L"Result of reduce function: " << reduceRes << endl << endl;

    wprintf(L"\n");
}


void linkedListConcat() {
    wprintf(L"How many elements are there in the first sequence? ");
    int length1;
    wcin >> length1;
    int data1[length1];
    for (int i = 0; i < length1; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data1[i];
    }
    wprintf(L"How many elements are there in the second sequence? ");
    int length2;
    wcin >> length2;
    int data2[length2];
    for (int i = 0; i < length2; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data2[i];
    }
    try {
        ListSequence<int> listSequence1(data1, length1);
        ListSequence<int> listSequence2(data2, length2);
        Sequence<int> *result = listSequence1.concat(&listSequence2);
        wprintf(L"You enter the sequence: ");
        printSequence(&listSequence1);
        printSequence(&listSequence2);
        wprintf(L"The result of concatenation: ");
        printSequence(result);
        delete result;

        wprintf(L"\n");
    }
    catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void linkedListGetSubSequence() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    try {
        wcout << L"Enter the initial index: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Enter the end index: ";
        int endIndex;
        wcin >> endIndex;
        ListSequence<int> listSequence(data, length);
        wprintf(L"You enter the sequence: ");
        printSequence(&listSequence);
        wprintf(L"The resulting subsequence: ");
        Sequence<int> *result = listSequence.getSubsequence(startIndex, endIndex);
        printSequence(result);
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}


void linkedListFindSubSequence() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"How many elements are there in the subsequence?");
    int subLength;
    wcin >> subLength;
    int subData[subLength];
    for (int i = 0; i < subLength; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> subData[i];
    }
    try {
        ListSequence<int> listSequence(data, length);
        ListSequence<int> subSequence(subData, subLength);
        wprintf(L"You enter the sequence: ");
        printSequence(&listSequence);
        wprintf(L"You enter the subsequence: ");
        printSequence(&subSequence);
        int index = listSequence.findSubsequence(subSequence);
        wcout << L"The position of the subsequence = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void linkedListAppend() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"What number do you want to add? ");
    int num;
    wcin >> num;

    try {
        ListSequence<int> listSequence(data, length);
        wprintf(L"You enter the sequence: ");
        printSequence(&listSequence);
        wprintf(L"The sequence after adding: ");
        listSequence.append(num);
        printSequence(&listSequence);

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void linkedListPrepend() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"What number do you want to add? ");
    int num;
    wcin >> num;

    try {
        ListSequence<int> listSequence(data, length);
        wprintf(L"You enter the sequence: ");
        printSequence(&listSequence);
        wprintf(L"The sequence after adding: ");
        listSequence.prepend(num);
        printSequence(&listSequence);

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void linkedListInsertAt() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Enter the number you want to insert: ");
    int num, index;
    wcin >> num;

    wprintf(L"Enter the index to insert the number: ");
    wcin >> index;
    try {
        ListSequence<int> listSequence(data, length);
        wprintf(L"You enter the sequence: ");
        printSequence(&listSequence);
        wprintf(L"The sequence after adding: ");
        listSequence.insertAt(num, index);
        printSequence(&listSequence);
        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void linkedListRemoveAt() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    int index;
    wprintf(L"Enter the index of the element to remove: ");
    wcin >> index;
    try {
        ListSequence<int> listSequence(data, length);
        wprintf(L"You enter the sequence: ");
        printSequence(&listSequence);
        wprintf(L"The sequence after removing: ");
        listSequence.removeAt(index);
        printSequence(&listSequence);
        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamicArrayConcat() {
    wprintf(L"How many elements are there in the first sequence?");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"How many elements are there in the second sequence?: ");
    int length2;
    wcin >> length2;
    int data2[length];
    for (int i = 0; i < length2; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data2[i];
    }
    try {
        MutableArraySequence<int> arraySequence1(data, length);
        MutableArraySequence<int> arraySequence2(data2, length2);
        Sequence<int> *result = arraySequence1.concat(&arraySequence2);
        wprintf(L"You enter the sequences: ");
        printSequence(&arraySequence1);
        printSequence(&arraySequence2);
        wprintf(L"The sequence after concatenation: ");
        printSequence(result);
        delete result;

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamicArrayGetSubSequence() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    try {

        wcout << L"Enter start index: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Enter end index: ";
        int endIndex;
        wcin >> endIndex;
        MutableArraySequence<int> arraySequence(data, length);
        Sequence<int> *result = arraySequence.getSubsequence(startIndex, endIndex);
        wprintf(L"You enter the sequence: ");
        printSequence(&arraySequence);
        wprintf(L"The resulting subsequence: ");
        printSequence(result);
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}


void dynamicArrayFindSubSequence() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"How many elements are there in the subsequence? ");
    int subLength;
    wcin >> subLength;
    int subData[subLength];
    for (int i = 0; i < subLength; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> subData[i];
    }
    try {
        MutableArraySequence<int> arraySequence(data, length);
        MutableArraySequence<int> subSequence(subData, subLength);
        wprintf(L"You enter the sequence: ");
        printSequence(&arraySequence);
        wprintf(L"You enter the subsequence: ");
        printSequence(&subSequence);
        int index = arraySequence.findSubsequence(subSequence);
        wcout << L"The position of the subsequence = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamicArrayAppend() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Enter the element to insert: ");
    int num;
    wcin >> num;

    try {
        MutableArraySequence<int> arraySequence(data, length);
        wprintf(L"You enter the sequence: ");
        printSequence(&arraySequence);
        wprintf(L"The sequence after adding: ");
        arraySequence.append(num);
        printSequence(&arraySequence);

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamicArrayPrepend() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Enter the element to insert: ");
    int num;
    wcin >> num;

    try {
        MutableArraySequence<int> arraySequence(data, length);
        wprintf(L"You enter the sequence:  ");
        printSequence(&arraySequence);
        wprintf(L"The sequence after adding: ");
        arraySequence.prepend(num);
        printSequence(&arraySequence);

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamicArrayInsertAt() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Enter the number to insert: ");
    int num, index;
    wcin >> num;

    wprintf(L"Enter the index where to insert the number: ");
    wcin >> index;
    try {
        MutableArraySequence<int> arraySequence(data, length);
        wprintf(L"You entered the sequence: ");
        printSequence(&arraySequence);
        wprintf(L"The sequence after adding: ");
        arraySequence.insertAt(num, index);
        printSequence(&arraySequence);

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamicArrayRemoveAt() {
    wprintf(L"How many elements are there in the sequence? ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Enter the sequence element under the index " << i << L": ";
        wcin >> data[i];
    }
    int index;
    wprintf(L"Enter the index of the number you want to remove: ");
    wcin >> index;
    try {
        MutableArraySequence<int> arraySequence(data, length);
        wprintf(L"You entered the sequence: ");
        printSequence(&arraySequence);
        wprintf(L"The sequence after removing: ");
        arraySequence.removeAt(index);
        printSequence(&arraySequence);

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}
#endif
