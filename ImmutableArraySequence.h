#ifndef LR2_IMMUTABLE_ARRAY_SEQUENCE_H
#define LR2_IMMUTABLE_ARRAY_SEQUENCE_H

#include <cwchar>
#include "DynamicArray.h"
#include "sequence.h"

template <typename T>
class ImmutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T> data;
public:
    //СОЗДАНИЕ ОБЪЕКТА
    //копировать элементы из  переданного массива
    ImmutableArraySequence(T *data, int arraySize) : data(data, arraySize){}
    //создать пустой список
    ImmutableArraySequence() : data() {};
    //копирующий конструктор
    explicit  ImmutableArraySequence(const DynamicArray<T> &array) : data(array) {};
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
        return data[i]; // ссылка, чтобы сделать присваивание
    }
    //получить список из всех элементов, начиная с startIndex и заканчивая endIndex
    Sequence<T> *getSubSequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex) {
            throw IndexOutOfRange(string("Index startIndex <= endIndex"));
        }
        int size = endIndex - startIndex + 1; //размер последовательности
        DynamicArray<T> dynamicArray(size);
        for (int i = 0; i < size; i++) {
            dynamicArray[i] = get(startIndex + i);
        }
        return new  ImmutableArraySequence<T>(dynamicArray);
    }
    //получить длину списка
    int getLength() const override {
        return data.getSize();
    }
    //ОПЕРАЦИИ
    //добавить элемент в конец списка
    Sequence<T> *append(T item) override {
        int size = data.getSize();
        DynamicArray<T> dynamicArray(size);
        for (int i = 0; i < size; i++){
            dynamicArray[i] = get(i);
        }
        dynamicArray.append(item);
        return new ImmutableArraySequence<T>(dynamicArray);
    };
    //добавить элемент в начало списка
    Sequence<T> *prepend(T item) override {
        int size = data.getSize();
        DynamicArray<T> dynamicArray(size);
        for (int i = 0; i < size; i++) {
            dynamicArray[i] = get(i);
        }
        dynamicArray.prepend(item);
        return new ImmutableArraySequence<T>(dynamicArray);
    };
    //вставить элемент в заданную позицию
    Sequence<T> *insertAt(T item) override{
        int size = data.getSize();
        DynamicArray<T> dynamicArray(size);
        for (int i = 0; i < size; i++){
            dynamicArray[i] = get(i);
        }
        dynamicArray.insertAt(item);
        return new ImmutableArraySequence<T>(dynamicArray);
    };
    //соединить два списка
    Sequence<T> *concat(Sequence<T> *list) override {
        auto *result = new  ImmutableArraySequence<T>(this->data);
        result->data.resize(getLength() + list->getLength());
        for (int i = 0; i < list->getLength(); i++) {
            result->data.set(getLength() + i, list->get(i));
        }
        return result;
    };
    //удаление элемента по индексу
    Sequence<T> *removeAt(int index) override {
        int size = data.getSize();
        DynamicArray<T> dynamicArray(size);
        for (int i = 0; i < size; i++){
            dynamicArray[i] = get(i);
        }
        dynamicArray.removeAt(index);
        return new ImmutableArraySequence<T>(dynamicArray);
    };

    //вывод элементов на экран
    void print() override{
        data.print();
    }
    //виртуальный деструктор
    virtual ~ImmutableArraySequence<T>() = default;
    //map
    Sequence<T> *map(T (*f)(T)) const override{
        Sequence<T> *res = new  ImmutableArraySequence<T>();
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
        auto *res = new  ImmutableArraySequence<T>;
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