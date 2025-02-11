#ifndef LR2_MUTABLE_ARRAY_SEQUENCE_H
#define LR2_MUTABLE_ARRAY_SEQUENCE_H

#include <cwchar>
#include "DynamicArray.h"
#include "Sequence.h"
template <typename T>

class MutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T> data;
public:
    //СОЗДАНИЕ ОБЪЕКТА
    //копировать элементы из переданного массива
    MutableArraySequence(T *data, int arraySize) : data(data, arraySize){}
    //создать пустой список
    MutableArraySequence() : data() {};
    //копирующий конструктор
    explicit  MutableArraySequence(const DynamicArray<T> &array) : data(array) {};
    //ДЕКОМПОЗИЦИЯ
    //получить первый элемент в списке
    T getFirst() const override {
        return data.get(0);
    };
    //получить последний элемент в списке
    T getLast() const override {
        return data.get(data.getSize() - 1);
    };
    //получить элемент по индексу
    T get(int index) const override{
        return data.get(index);
    };

    T operator[](int i) const override {
        return data[i];
    }
    T &operator[](int i) override {
        return data[i];
    }
    //получить список из всех элементов, начиная с startIndex и заканчивая endIndex
    Sequence<T> *getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex) {
            throw IndexOutOfRange(string("Index startIndex <= endIndex"));
        }
        int size = endIndex - startIndex + 1;
        DynamicArray<T> dynamicArray(size);
        for (int i = 0; i < size; i++) {
            dynamicArray[i] = get(startIndex + i);
        }
        return new  MutableArraySequence<T>(dynamicArray);
    }
    //получить длину списка
    int getLength() const override {
        return data.getSize();
    }
    //ОПЕРАЦИИ
    //добавить элемент в конец списка
    void append(T item) override{
        data.append(item);
    };
    //добавить элемент в начало списка
    void prepend(T item) override{
        data.prepend(item);
    };
    //вставить элемент в заданную позицию
    void insertAt(T item, int index) override{
        data.insertAt(item, index);
    };
    //соединить два списка
    Sequence<T> *concat(Sequence<T> *list) override {
        auto *result = new  MutableArraySequence<T>(this->data);
        result->data.resize(getLength() + list->getLength());
        for (int i = 0; i < list->getLength(); i++) {
            result->data.set(getLength() + i, list->get(i));
        }
        return result;
    };
    //удаление элемента по индексу
    void removeAt(int index) override{
        data.removeAt(index);
    }
    //вывод элементов на экран
    void print() override{
        data.print();
    }
    //виртуальный деструктор
    virtual ~MutableArraySequence<T>() = default;
    //map
    Sequence<T> *map(T (*f)(T)) const override{
        Sequence<T> *res = new  MutableArraySequence<T>();
        for (int i = 0; i < getLength(); i++){
            res->append(f(data.get(i)));
        }
        return res;
    }
    //reduce
    T reduce(T (*f)(T, T)) const override{
        T result = data.get(0);
        for (int i = 1; i < data.getSize(); i++){
            result = f(result, data.get(i));
        }
        return result;
    }
    //where
    Sequence<T> *where(bool (*h)(T)) const override {
        auto *res = new  MutableArraySequence<T>;
        for (int i = 0; i < getLength(); i++){
            T item = data.get(i);
            if (h(item)){
                res->append(item);
            }
        }
        return res;
    }

};





#endif