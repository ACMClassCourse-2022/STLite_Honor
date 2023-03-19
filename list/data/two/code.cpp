// Provided by Lhtie 2022.2

#include "class-integer.hpp"
#include "class-matrix.hpp"
#include "class-bint.hpp"
#include "list.hpp"

#include <iostream>
#include <list>

const int N = 5e4;

int ansCounter = 0, myCounter = 0, noUseCounter = 0;
class DynamicType {
public:
    int *pct;
    int *data;
    DynamicType (int *p) : pct(p) , data(new int[2]) {
        (*pct)++;
    }
    DynamicType (int *p, int x) : pct(p) , data(new int[2]) {
        (*pct)++;
        data[0] = x;
    }
    DynamicType (const DynamicType &other) : pct(other.pct), data(new int[2]) {
        (*pct)++;
        data[0] = other.data[0];
    }
    DynamicType &operator =(const DynamicType &other) {
        if (this == &other) return *this;
        (*pct)--;
        pct = other.pct;
        (*pct)++;
        delete [] data;
        data = new int[2];
        data[0] = other.data[0];
        return *this;
    }
    ~DynamicType() {
        delete [] data;
        (*pct)--;
    }
    bool operator == (const DynamicType &rhs) const {
        return data[0] == rhs.data[0];
    }
    bool operator != (const DynamicType &rhs) const {
        return data[0] != rhs.data[0];
    }
    bool operator < (const DynamicType &rhs) const {
        return data[0] < rhs.data[0];
    }
};

template<typename T>
bool equal(const std::list<T> &x, const sjtu::list<T> &y) {
    if (x.size() != y.size())
        return false;

    typename std::list<T>::const_iterator itx(x.begin());
    typename sjtu::list<T>::const_iterator ity(y.cbegin());
    for (; itx != x.cend() && ity != y.cend(); ++itx, ++ity)
        if (*itx != *ity)
            return false;

    return true;
}

bool testPush() {
    {
        std::list<DynamicType> ans;
        sjtu::list<DynamicType> myList;

        for (int i = 0; i < N; ++i) {
            if (rand()%2){
                ans.push_back(DynamicType(&ansCounter));
                myList.push_back((DynamicType(&myCounter)));
            } else {
                ans.push_front(DynamicType(&ansCounter));
                myList.push_front((DynamicType(&myCounter)));
            }
        }

        if (myCounter != ansCounter)
            return false;
    }
    return myCounter == ansCounter;
}

bool testPop() {
    {
        std::list<DynamicType> ans;
        sjtu::list<DynamicType> myList;
        for (int i = 0; i < N; ++i){
            ans.push_back(DynamicType(&ansCounter));
            myList.push_back(DynamicType(&myCounter));
        }

        for (int i = 0; i < rand()%N; ++i) {
            if (rand()%2){
                ans.pop_back();
                myList.pop_back();
            } else {
                ans.pop_front();
                myList.pop_front();
            }
        }

        if (myCounter != ansCounter)
            return false;
    }
    return myCounter == ansCounter;
}

bool testInsert() {
    std::list<DynamicType> ans;
    sjtu::list<DynamicType> myList;

    ans.push_back(DynamicType(&ansCounter, 0));
    myList.push_back(DynamicType(&myCounter, 0));
    for (int i = 0; i < N; ++i){
        int val = rand();
        switch(rand()%4){
            case 0:
                if (*ans.insert(ans.begin(), DynamicType(&ansCounter, val)) !=
                    *myList.insert(myList.begin(), DynamicType(&myCounter, val)))
                    return false;
                break;
            case 1:
                if (*ans.insert(++ans.begin(), DynamicType(&ansCounter, val)) !=
                    *myList.insert(++myList.begin(), DynamicType(&myCounter, val)))
                    return false;
                break;
            case 2:
                if (*ans.insert(ans.end(), DynamicType(&ansCounter, val)) !=
                    *myList.insert(myList.end(), DynamicType(&myCounter, val)))
                    return  false;
                break;
            case 3:
                if (*ans.insert(--ans.end(), DynamicType(&ansCounter, val)) !=
                    *myList.insert(--myList.end(), DynamicType(&myCounter, val)))
                    return false;
                break;
        }
    }

    if (!equal(ans, myList))
        return false;
    return myCounter == ansCounter;
}

bool testErase() {
    std::list<DynamicType> ans;
    sjtu::list<DynamicType> myList;
    for (int i = 0; i < N; ++i){
        ans.push_back(DynamicType(&ansCounter, i));
        myList.push_back(DynamicType(&myCounter, i));
    }

    for (int i = 0; i < N / 2; ++i){
        switch(rand()%4){
            case 0: ans.erase(ans.begin()), myList.erase(myList.begin()); break;
            case 1: ans.erase(++ans.begin()), myList.erase(++myList.begin()); break;
            case 2: ans.erase(--ans.end()), myList.erase(--myList.end()); break;
            case 3: ans.erase(--(--ans.end())), myList.erase(--(--myList.end())); break;
        }
    }

    if (!equal(ans, myList))
        return false;
    return myCounter == ansCounter;
}

bool testSort() {
    std::list<DynamicType> ans;
    sjtu::list<DynamicType> myList;
    for (int i = 0; i < N; ++i){
        int val = rand();
        ans.push_back(DynamicType(&ansCounter, val));
        myList.push_back(DynamicType(&myCounter, val));
    }

    ans.sort(), myList.sort();
    if (!equal(ans, myList))
        return false;
    return myCounter == ansCounter;
}

bool testMerge() {
    std::list<DynamicType> ans1, ans2;
    sjtu::list<DynamicType> myList1, myList2;
    for (int i = 0; i < N; ++i){
        int val = rand();
        ans1.push_back(DynamicType(&ansCounter, val));
        myList1.push_back(DynamicType(&myCounter, val));
        val = rand();
        ans2.push_back(DynamicType(&ansCounter, val));
        myList2.push_back(DynamicType(&myCounter, val));
    }

    ans1.sort(), ans2.sort();
    myList1.sort(), myList2.sort();
    ans1.merge(ans2), myList1.merge(myList2);
    if (!equal(ans1, myList1))
        return false;
    return myCounter == ansCounter;
}

bool testReverse() {
    std::list<DynamicType> ans;
    sjtu::list<DynamicType> myList;
    for (int i = 0; i < N; ++i){
        int val = rand();
        ans.push_back(DynamicType(&ansCounter, val));
        myList.push_back(DynamicType(&myCounter, val));
    }

    ans.reverse(), myList.reverse();
    if (!equal(ans, myList))
        return false;
    return myCounter == ansCounter;
}

bool testUnique() {
    std::list<DynamicType> ans;
    sjtu::list<DynamicType> myList;
    for (int i = 0; i < N; ++i){
        int val = rand() % 2;
        ans.push_back(DynamicType(&ansCounter, val));
        myList.push_back(DynamicType(&myCounter, val));
    }

    ans.unique(), myList.unique();
    if (!equal(ans, myList))
        return false;
    return myCounter == ansCounter;
}

int main(){
    srand(time(NULL));
    bool (*testList[])() = {
        testPush, testPop, testInsert, testErase, testSort, testMerge, testReverse, testUnique
    };
    const char* Messages[] = {
        "Test 1: Testing push_front() & push_back() and check number of live objects...",
        "Test 2: Testing pop_front() & pop_back() and check number of live objects...",
        "Test 3: Testing insert() and check number of live objects...",
        "Test 4: Testing erase() and check number of live objects...",
        "Test 5: Testing sort() and check number of live objects...",
        "Test 6: Testing merge() and check number of live objects...",
        "Test 7: Testing reverses() and check number of live objects...",
        "Test 8: Testing unique() and check number of live objects..."
    };

    bool okay = true;
    for (int i = 0; i < sizeof(testList) / sizeof(testList[0]); ++i) {
        printf("%s", Messages[i]);
        if (testList[i]()){
            printf("Passed\n");
        } else {
            okay = false;
            printf("Failed\n");
        }
    }

    if (okay)
        printf("Congratulations, you have passed all tests!\n");
    else printf("Unfortunately, you failed in some of the tests.\n");
    return 0;
}