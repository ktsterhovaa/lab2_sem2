#include <cstdlib>

#include "../MutableArraySequence.h"
#include "../LinkedList.h"
#include "../ListSequence.h"
#include "lib/googletest/include/gtest/gtest.h"

TEST(DynamicArray, basicOperations) {

    DynamicArray<int> array(3);
    MutableArraySequence<int> da(array);
    ASSERT_EQ(3, da.getLength());
    try {
        da.get(0);
        FAIL() << "Should be IndexOutOfRange";
        } catch (IndexOutOfRange &ex) {
            ASSERT_STREQ("Element with index 0 not defined", ex.what());
    }
    try {
        da.get(2);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Element with index 2 not defined", ex.what());
    }

    da[0] = 11;
    da[1] = 22;
    da[2] = 33;

    ASSERT_EQ(11, da.get(0));
    ASSERT_EQ(22, da.get(1));
    ASSERT_EQ(33, da.get(2));

    ASSERT_EQ(11, da[0]);
    ASSERT_EQ(22, da[1]);
    ASSERT_EQ(33, da[2]);

    try {
        da.get(-1);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -1 out of range 0..2", ex.what());
    }
    try {
        da[-1] = 101;
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -1 out of range 0..2", ex.what());
    }
    try {
        da.get(10);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index 10 out of range 0..2", ex.what());
    }
    try {
        int x = da[11];
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index 11 out of range 0..2", ex.what());
    }

    da[0] = 101;
    ASSERT_EQ(3, da.getLength());
    ASSERT_EQ(101, da[0]);
    ASSERT_EQ(22, da[1]);
    ASSERT_EQ(33, da[2]);

    da.insertAt(1, 0);
    ASSERT_EQ(4, da.getLength());
    ASSERT_EQ(1, da[0]);
    ASSERT_EQ(101, da[1]);
    ASSERT_EQ(22, da[2]);
    ASSERT_EQ(33, da[3]);

    da[0] = 2 * da[1] + da[2];

}
TEST(LinkedList, Iterator) {
    int items[] = {11, 22, 33};
    LinkedList<int> list(items, _countof(items));
    ASSERT_EQ(3, list.getLength());

    auto it = list.begin();
    ASSERT_EQ(11, *it);
    it++;
    ASSERT_EQ(22, *it);
    ++it;
    ASSERT_EQ(33, *it);
    it++;
    ASSERT_EQ(list.end(), it);

    for (auto it = list.begin(), end = list.end(); it != end; ++it) {
        const auto i = *it;
        std::cout << i << "\n";
    }
    for (int x : list) {
        cout << x << endl;
    }
}
TEST(DynamicArray, undefinedElements) {
    DynamicArray<int> da(4);
    try {
        int x = da.get(0);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Element with index 0 not defined", ex.what());
    }
    try {
        int x = da.get(2);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Element with index 2 not defined", ex.what());
    }
    try {
        int x = da.get(-1);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -1 out of range 0..3", ex.what());
    }
    try {
        int x = da.get(11);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index 11 out of range 0..3", ex.what());
    }
}



TEST(MutableArraySequence, removeAt) {
    int data[] = {11, 22, 33};
    MutableArraySequence<int> da(data, _countof(data));
    da.removeAt(1);
    ASSERT_EQ(2, da.getLength());
    ASSERT_EQ(11, da[0]);
    ASSERT_EQ(33, da[1]);
    da.removeAt(1);
    ASSERT_EQ(1, da.getLength());
    ASSERT_EQ(11, da[0]);
    da.removeAt(0);
    ASSERT_EQ(0, da.getLength());
}

TEST(DynamicArray, resize) {
    DynamicArray<int> da(0);
    ASSERT_EQ(0, da.getSize());
    for (int size = 1; size <= 10; size++) {
        da.resize(size);
        ASSERT_EQ(size, da.getSize());
    }
}

TEST(DynamicArray, arrayInitialization) {

    int data[] = {111, 222};
    DynamicArray<int> da(data, _countof(data));
    ASSERT_EQ(_countof(data), da.getSize());
    da.set(0, 111);
    da.set(1, 222);
    ASSERT_EQ(111, da.get(0));
    ASSERT_EQ(222, da.get(1));


    DynamicArray<int> d2(da);
    ASSERT_EQ(da.getSize(), d2.getSize());
    ASSERT_EQ(111, d2.get(0));
    ASSERT_EQ(222, d2.get(1));


    d2.resize(1);
    ASSERT_EQ(1, d2.getSize());
    ASSERT_EQ(111, d2.get(0));


    d2.resize(3);
    ASSERT_EQ(3, d2.getSize());
    ASSERT_EQ(111, d2.get(0));
    d2.set(1, 221);
    d2.set(2, 331);
    ASSERT_EQ(221, d2.get(1));
    ASSERT_EQ(331, d2.get(2));
}

TEST(LinkedList, listBasicOperations) {

    int data[] = {11, 22, 33};
    LinkedList<int> list(data, _countof(data));
    ASSERT_EQ(3, list.getLength());

    ASSERT_EQ(11, list.get(0));
    ASSERT_EQ(22, list.get(1));
    ASSERT_EQ(33, list.get(2));
    ASSERT_EQ(11, list[0]);
    ASSERT_EQ(22, list[1]);
    ASSERT_EQ(33, list[2]);

    try {
        list.get(-2);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -2 out of range 0...2", ex.what());
    }

    try {
        list[-2];
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -2 out of range 0...2", ex.what());
    }

    try {
        list.get(10);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index 10 out of range 0...2", ex.what());
    }
    list.insertAt(500, 1);
}

TEST(LinkedList, addElements) {
    LinkedList<int> list;

    ASSERT_EQ(0, list.getLength());
    try {
        list.getFirst();
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }
    try {
        list.getLast();
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }

    list.prepend(11);
    ASSERT_EQ(1, list.getLength());
    ASSERT_EQ(11, list.getFirst());
    ASSERT_EQ(11, list.getLast());

    list.prepend(22);
    ASSERT_EQ(2, list.getLength());
    ASSERT_EQ(22, list.getFirst());
    ASSERT_EQ(11, list.getLast());

    LinkedList<int> list2(list);
    ASSERT_EQ(2, list2.getLength());
    ASSERT_EQ(22, list2.getFirst());
    ASSERT_EQ(11, list2.getLast());
    ASSERT_EQ(22, list2.get(0));
    ASSERT_EQ(11, list2.get(1));

    LinkedList<int> *subList = list2.getSubList(0, 0);
    ASSERT_EQ(1, subList->getLength());
    ASSERT_EQ(22, subList->getFirst());
    ASSERT_EQ(22, subList->getLast());
    delete subList;

    try {
        list2.getSubList(-1, 0);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("startIndex -1 out of range 0...1", ex.what());
    }
    try {
        list2.getSubList(0, -1);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("endIndex -1 out of range 0...1", ex.what());
    }
    try {
        list2.getSubList(1, 0);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("startIndex=1 > endIndex=0", ex.what());
    }
}


TEST(LinkedList, appendElement) {
    LinkedList<int> list;

    ASSERT_EQ(0, list.getLength());

    try {
        list.getFirst();
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }

    try {
        list.getLast();
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }

    list.append(11);
    ASSERT_EQ(1, list.getLength());
    ASSERT_EQ(11, list.getFirst());
    ASSERT_EQ(11, list.getLast());

    list.append(22);
    ASSERT_EQ(2, list.getLength());
    ASSERT_EQ(11, list.getFirst());
    ASSERT_EQ(22, list.getLast());
}

TEST(LinkedList, Concat) {
    int items1[] = {11, 22, 33};
    int items2[] = {44, 55};
    LinkedList<int> list1(items1, _countof(items1));
    LinkedList<int> list2(items2, _countof(items2));

    ASSERT_EQ(3, list1.getLength());
    ASSERT_EQ(2, list2.getLength());

    LinkedList<int> *l = list1.concat(&list2);
    ASSERT_EQ(5, l->getLength());
    ASSERT_EQ(11, l->get(0));
    ASSERT_EQ(22, l->get(1));
    ASSERT_EQ(33, l->get(2));
    ASSERT_EQ(44, l->get(3));
    ASSERT_EQ(55, l->get(4));
    delete l;
}



TEST(LinkedList, insertAt) {
    LinkedList<int> list;

    ASSERT_EQ(0, list.getLength());

    list.insertAt(11, 0);
    ASSERT_EQ(1, list.getLength());
    ASSERT_EQ(11, list.get(0));
    ASSERT_EQ(11, list.getFirst());
    ASSERT_EQ(11, list.getLast());

    list.insertAt(22, 1);
    ASSERT_EQ(2, list.getLength());
    ASSERT_EQ(11, list.get(0));
    ASSERT_EQ(22, list.get(1));
    ASSERT_EQ(11, list.getFirst());
    ASSERT_EQ(22, list.getLast());

    try {
        list.insertAt(1, -1);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("insertAt index=-1 < 0", ex.what());
    }

    list.insertAt(15, 1);
    ASSERT_EQ(3, list.getLength());
    ASSERT_EQ(11, list.get(0));
    ASSERT_EQ(15, list.get(1));
    ASSERT_EQ(22, list.get(2));
    ASSERT_EQ(11, list.getFirst());
    ASSERT_EQ(22, list.getLast());
}


TEST(LinkedList, removeAt) {
    LinkedList<int> list;

    ASSERT_EQ(0, list.getLength());

    list.insertAt(11, 0);
    ASSERT_EQ(1, list.getLength());
    ASSERT_EQ(11, list.get(0));
    ASSERT_EQ(11, list.getFirst());
    ASSERT_EQ(11, list.getLast());

    list.removeAt(0);
    ASSERT_EQ(0, list.getLength());

    list.append(11);
    list.append(22);
    list.append(33);
    list.append(44);
    ASSERT_EQ(4, list.getLength());
    ASSERT_EQ(11, list.get(0));
    ASSERT_EQ(22, list.get(1));
    ASSERT_EQ(33, list.get(2));
    ASSERT_EQ(44, list.get(3));
    list.removeAt(0);
    ASSERT_EQ(3, list.getLength());
    ASSERT_EQ(22, list.get(0));
    ASSERT_EQ(33, list.get(1));
    ASSERT_EQ(44, list.get(2));
    list.removeAt(2);
    ASSERT_EQ(2, list.getLength());
    ASSERT_EQ(22, list.get(0));
    ASSERT_EQ(33, list.get(1));
    list.append(44);
    ASSERT_EQ(3, list.getLength());
    ASSERT_EQ(22, list[0]);
    ASSERT_EQ(33, list[1]);
    ASSERT_EQ(44, list[2]);
    list.removeAt(1);
    ASSERT_EQ(2, list.getLength());
    ASSERT_EQ(22, list[0]);
    ASSERT_EQ(44, list[1]);
}

TEST(MutableArraySequence, constructor) {
    Sequence<int> *s = new MutableArraySequence<int>();
    ASSERT_EQ(0, s->getLength());
    for (int x = 1; x <= 10; x++) {
        s->append(x);
        ASSERT_EQ(x, s->getLength());
        ASSERT_EQ(x, s->getLast());
    }
    delete s;
}

TEST(MutableArraySequence, ArraySequenceAppendPrependElement) {
    int data[] = {111, 222};
    Sequence<int> *s = new MutableArraySequence<int>(data, _countof(data));
    ASSERT_EQ(2, s->getLength());
    ASSERT_EQ(111, s->get(0));
    ASSERT_EQ(222, s->get(1));
    ASSERT_EQ(111, s->getFirst());
    ASSERT_EQ(222, s->getLast());
    s->append(333);
    ASSERT_EQ(3, s->getLength());
    ASSERT_EQ(333, s->get(2));
    s->prepend(10);
    ASSERT_EQ(4, s->getLength());
    ASSERT_EQ(10, s->get(0));
    ASSERT_EQ(111, s->get(1));
    ASSERT_EQ(222, s->get(2));
    ASSERT_EQ(333, s->get(3));
    delete s;
}


TEST(MutableArraySequence, createFromDynamicArray) {
    int data[] = {123, 234, 345};
    DynamicArray<int> da(data, _countof(data));
    Sequence<int> *s = new MutableArraySequence<int>(da);
    ASSERT_EQ(3, s->getLength());
    ASSERT_EQ(data[0], s->get(0));
    ASSERT_EQ(data[1], s->get(1));
    ASSERT_EQ(data[2], s->get(2));
    ASSERT_EQ(data[0], s->getFirst());
    ASSERT_EQ(data[2], s->getLast());
    s->append(333);
    ASSERT_EQ(4, s->getLength());
    ASSERT_EQ(333, s->getLast());
    s->prepend(10);
    ASSERT_EQ(5, s->getLength());

    ASSERT_EQ(10, s->get(0));
    ASSERT_EQ(data[0], s->get(1));
    ASSERT_EQ(data[1], s->get(2));
    ASSERT_EQ(data[2], s->get(3));
    ASSERT_EQ(333, s->get(4));
    Sequence<int> *sub = s->getSubsequence(1, 3);
    ASSERT_EQ(3, sub->getLength());
    ASSERT_EQ(123, sub->get(0));
    ASSERT_EQ(234, sub->get(1));
    ASSERT_EQ(345, sub->get(2));

    sub->insertAt(4444, 1);
    ASSERT_EQ(4, sub->getLength());
    ASSERT_EQ(123, sub->get(0));
    ASSERT_EQ(4444, sub->get(1));
    ASSERT_EQ(234, sub->get(2));
    ASSERT_EQ(345, sub->get(3));
    delete s;
    delete sub;
}


TEST(MutableArraySequence, concat) {

    int data1[] = {11, 22};
    DynamicArray<int> da1(data1, _countof(data1));
    Sequence<int> *s1 = new MutableArraySequence<int>(da1);

    int data2[] = {33};
    DynamicArray<int> da2(data2, _countof(data2));
    Sequence<int> *s2 = new MutableArraySequence<int>(da2);

    Sequence<int> *res = s1->concat(s2);
    ASSERT_EQ(3, res->getLength());
    ASSERT_EQ(11, res->get(0));
    ASSERT_EQ(22, res->get(1));
    ASSERT_EQ(33, res->get(2));
    delete s1;
    delete s2;
    delete res;
}

TEST(MutableArraySequence, findSubSequence) {
    int data[] = {11, 22, 33, 44, 55};
    DynamicArray<int> da(data, _countof(data));
    Sequence<int> *main = new MutableArraySequence<int>(da);

    {
        int d[] = {11, 22};
        Sequence<int> *sub1 = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(0, main->findSubsequence(*sub1));
        delete sub1;
    }
    {
        int d[] = {22, 33};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(1, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {33, 44, 55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(2, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {44, 55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(3, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(4, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {33, 55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(-1, main->findSubsequence(*sub));
        delete sub;
    }

    delete main;
}

TEST(LinkedListSequence, findSubsequence) {
    int data[] = {11, 22, 33, 44, 55};
    Sequence<int> *main = new ListSequence<int>(data, _countof(data));
    ASSERT_EQ(5, main->getLength());
    ASSERT_EQ(11, main->get(0));
    ASSERT_EQ(22, main->get(1));
    ASSERT_EQ(33, main->get(2));
    ASSERT_EQ(44, main->get(3));
    ASSERT_EQ(55, main->get(4));

    {
        int d[] = {11, 22};
        Sequence<int> *sub1 = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(0, main->findSubsequence(*sub1));
        delete sub1;
    }
    {
        int d[] = {22, 33};
        Sequence<int> *sub = new ListSequence<int>(d, _countof(d));
        ASSERT_EQ(2, sub->getLength());
        ASSERT_EQ(22, sub->get(0));
        ASSERT_EQ(33, sub->get(1));
        ASSERT_EQ(1, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {33, 44, 55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(2, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {44, 55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(3, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(4, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {33, 55};
        Sequence<int> *sub = new MutableArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(-1, main->findSubsequence(*sub));
        delete sub;
    }

    delete main;
}

TEST(ListSequence, operations) {
    auto *list = new ListSequence<int>();

    ASSERT_EQ(0, list->getLength());

    try {
        list->getFirst();
        FAIL();
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }

    try {
        list->getLast();
        FAIL();
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("List is empty", ex.what());
    }

    list->append(11);
    ASSERT_EQ(1, list->getLength());
    ASSERT_EQ(11, list->getFirst());
    ASSERT_EQ(11, list->getLast());

    list->append(22);
    ASSERT_EQ(2, list->getLength());
    ASSERT_EQ(11, list->getFirst());
    ASSERT_EQ(22, list->getLast());
    list->append(33);
    list->append(44);

    Sequence<int> *sub = list->getSubsequence(1, 2);
    ASSERT_EQ(2, sub->getLength());
    ASSERT_EQ(22, sub->get(0));
    ASSERT_EQ(33, sub->get(1));

    sub->prepend(-100);
    ASSERT_EQ(3, sub->getLength());
    ASSERT_EQ(-100, sub->getFirst());
    delete sub;
    delete list;
}

TEST(ListSequence, createListFromArray) {
    wstring items[3] = {L"first", L"second", L"third"};
    ListSequence<wstring> list(items, 3);
    ASSERT_EQ(3, list.getLength());
    ASSERT_EQ(wstring(L"first"), list.get(0));
    ASSERT_EQ(wstring(L"second"), list.get(1));
    ASSERT_EQ(wstring(L"third"), list.get(2));
    ASSERT_EQ(wstring(L"first"), list[0]);
    ASSERT_EQ(wstring(L"second"), list[1]);
    ASSERT_EQ(wstring(L"third"), list[2]);

    ListSequence<wstring> copy(list);
    ASSERT_EQ(3, copy.getLength());
    ASSERT_EQ(wstring(L"first"), copy.getFirst());
    ASSERT_EQ(wstring(L"first"), copy.get(0));
    ASSERT_EQ(wstring(L"second"), copy.get(1));
    ASSERT_EQ(wstring(L"third"), copy.get(2));
    ASSERT_EQ(wstring(L"third"), copy.getLast());
}

TEST(LinkedListSequence, insertAt) {
    wstring items[3] = {L"first", L"second", L"third"};
    Sequence<wstring> *list = new ListSequence<wstring>(items, 3);
    ASSERT_EQ(3, list->getLength());
    ASSERT_EQ(wstring(L"first"), list->get(0));
    ASSERT_EQ(wstring(L"second"), list->get(1));
    ASSERT_EQ(wstring(L"third"), list->get(2));

    list->insertAt(L"test", 1);
    ASSERT_EQ(4, list->getLength());
    ASSERT_EQ(wstring(L"first"), list->get(0));
    ASSERT_EQ(wstring(L"test"), list->get(1));
    ASSERT_EQ(wstring(L"second"), list->get(2));
    ASSERT_EQ(wstring(L"third"), list->get(3));
    delete list;
}


constexpr int square(int x) {
    return x * x;
};

constexpr int inc_int(int x) {
    return x + 1;
};

constexpr int dec_int(int x) {
    return x - 1;
};