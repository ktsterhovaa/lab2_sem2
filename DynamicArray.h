#ifndef LR2_DYNAMIC_ARRAY_H
#define LR2_DYNAMIC_ARRAY_H

#include <iostream>
#include <cstring>
#include "IndexOutOfRange.hpp"
template <typename T>
class DynamicArray {
    int size; //количество элементов
    T *data;
    bool *defined; //задан ли элемент массива
    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange(string("Index ") + to_string(index) + " out of range 0.." + to_string(size - 1));
        }
    }

public:
    //СОЗДАНИЕ ОБЪЕКТА

    //создание массива заданной длины arraySize
    explicit DynamicArray(int arraySize = 0) : size(arraySize) {
        if (size < 0) throw IndexOutOfRange("Size < 0");
        data = new T[size];
        defined = new bool[size];
        for (int i = 0; i < size; i++) {
            defined[i] = false;
        }
    }

    //копировать элементы из переданного массива
    DynamicArray(T *items, int arraySize) : size(arraySize) {
        if (size < 0) {
            throw IndexOutOfRange("Size < 0");
        }
        data = new T[size];
        defined = new bool[size];
        memcpy(data, items, sizeof(T) * size);
        for (int i = 0; i < size; i++) {
            defined[i] = true; // то есть элемент задан
        }
    };

    //копирующий конструктор
    DynamicArray(const DynamicArray<T> &dynamicArray) {
        size = dynamicArray.size;
        data = new T[dynamicArray.size];
        memcpy(data, dynamicArray.data, dynamicArray.size * sizeof(T));
        //копирование элементов, которые определены
        defined = new bool[dynamicArray.size];
        memcpy(defined, dynamicArray.defined, dynamicArray.size * sizeof(bool));
    }

    //деструктор - очистка памяти
    ~DynamicArray() {
        delete[] data;
        data = nullptr;
        delete[] defined;
        defined = nullptr;
    }

    //ДЕКОМПОЗИЦИЯ
    //получить элемент по индексу
    T &get(int index) const {
        checkIndex(index);
        if (!defined[index]) {
            throw IndexOutOfRange(string("Element with index ") + to_string(index) + " not defined");
        }
        return data[index];
    }

    //получить размер массива
    int getSize() const {
        return size;
    }

    //ОПЕРАЦИИ
    //задать элемент по индексу
    void set(int index, T value) {
        checkIndex(index);
        data[index] = value;
        defined[index] = true;
    }

        T operator[](size_t index) const {
            return get(index);
        }
        T &operator[](size_t index) {
            checkIndex(index);
            defined[index] = true;
            return data[index];
        }
        //изменить размер массива
        void resize(int newSize) {
            if (newSize < 0) {
                throw bad_array_new_length();
            }
            T *newData = new T[newSize];
            bool *newDefined = new bool[newSize];
            for (int i = 0; i < min(size, newSize); i++) {
                newData[i] = data[i];
                newDefined[i] = defined[i];
            }
            memcpy(newData, data, sizeof(T) * min(size, newSize));
            memcpy(newDefined, defined, sizeof(bool) * min(size, newSize));
            for (int i = size; i < newSize; i++) {
                newDefined[i] = false;
            }
            //обновление
            size = newSize;
            delete[] data;
            data = newData;
            delete[] defined;
            defined = newDefined;
        }
        //добавить элемент в конец массива
        void append(T item) {
            resize(size + 1);
            set(size - 1, item);
        }
        //добавить элемент в начало массива
        void prepend(T item) {
            resize(size + 1);
            for (int i = size - 1; i >= 1; i--) { //сдвиг всех элементов вправо
                data[i] = data[i - 1];
                defined[i] = defined[i - 1];
            }
            data[0] = item;
            defined[0] = true;
        }
        //вставить элемент в заданную позицию
        void insertAt(T item, const int index) {
            resize(size + 1);
            checkIndex(index);
            for (int i = size - 1; i > index; i--) { //сдвиг всех элементов влево
                data[i] = data[i - 1];
                defined[i] = defined[i - 1];
            }
            set(index, item);
        }
        //удалить элемент по индексу
        void removeAt(const int index) {
            checkIndex(index);
            for (int i = index + 1; i < size; i++) {//сдвиг всех элементов с i+1 влево
                data[i - 1] = data[i];
                defined[i - 1] = defined[i];
            }
            resize(size - 1);
        }
        //вывод массива
        void print() {
            wcout << L"DynamicArray size = " << size << L":";
            for (int i = 0; i < size; i++) {
                if (defined[i]) {
                    wcout << L" " << data[i];
                } else {
                    wcout << L" - ";
                }
            }
            wcout << endl;
        }

    };





#endif