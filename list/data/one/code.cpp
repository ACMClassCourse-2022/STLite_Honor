// Provided by Lhtie 2022.2

#include "class-integer.hpp"
#include "class-matrix.hpp"
#include "class-bint.hpp"
#include "list.hpp"

#include <iostream>
#include <list>

const int N = 5e4;

template<typename T>
bool equal(const std::list<T> &x, const sjtu::list<T> &y) {
    if (x.size() != y.size())
        return false;

    typename std::list<T>::const_iterator itx = x.cbegin();
    typename sjtu::list<T>::const_iterator ity = y.cbegin();
    for (; itx != x.cend() && ity != y.cend(); ++itx, ++ity)
        if (!(*itx == *ity))
            return false;

    return true;
}

bool testConstructors() {
    std::list<int> ans;
    sjtu::list<int> myList;

    if (ans.size() != myList.size())
        return false;
    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    sjtu::list<int> *otherList = new sjtu::list<int>(myList);
    if (!equal(ans, *otherList)) {
        delete otherList;
        return false;
    }
    delete otherList;
    if (!equal(ans, myList))
        return false;

    return true;
}

bool testAssignment() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        ans.push_back(N - i);
        myList.push_back(N - i);
    }

    myList = myList;
    if (!equal(ans, myList))
        return false;

    sjtu::list<int> otherList;
    otherList = myList;
    if (!equal(ans, otherList))
        return false;

    return true;
}

bool testPush() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        if (rand()%2){
            ans.push_back(i);
            myList.push_back(i);
        } else {
            ans.push_front(i);
            myList.push_front(i);
        }
    }

    return equal(ans, myList);
}

bool testPop() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    for (int i = 0; i < rand()%N; ++i){
        if (rand()%2){
            ans.pop_front();
            myList.pop_front();
        } else {
            ans.pop_back();
            myList.pop_back();
        }
    }

    return equal(ans, myList);
}

bool testIterator() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    std::list<int>::iterator ansIt = ans.begin();
    sjtu::list<int>::iterator myIt = myList.begin();
    for (int i = 0; i < N / 4; ++i){
        if (*(ansIt++) != *(myIt++))
            return false;
        if (*(++ansIt) != *(++myIt))
            return false;
    }
    for (int i = 0; i < N / 8; ++i){
        if (*(ansIt--) != *(myIt--))
            return false;
        if (*(--ansIt) != *(--myIt))
            return false;
    }

    sjtu::list<Diamond::Matrix<double>> mtxList;
    int rows = 123, cols = 987, val = 456;
    mtxList.push_back(Diamond::Matrix<double>(rows, cols, val));
    sjtu::list<Diamond::Matrix<double>>::iterator mtxIt = mtxList.begin();
    if (mtxIt->RowSize() != rows || mtxIt->ColSize() != cols || (*mtxIt)[0][0] != val)
        return false;

    sjtu::list<int>::const_iterator cIt(myIt);
    sjtu::list<int>::iterator otherIt = myIt;
    if (cIt != myIt || myIt != cIt || myIt != otherIt)
        return false;
    myIt++;
    if (cIt == myIt || myIt == cIt || myIt == otherIt)
        return false;

    return true;
}

bool testBint() {
    std::list<Util::Bint> ans;
    sjtu::list<Util::Bint> myList;
    Util::Bint large = Util::Bint(rand());

    for (int i = 0; i < N / 30; ++i){
        ans.push_back(Util::Bint(i) * large);
        myList.push_back(Util::Bint(i) * large);
    }

    return equal(ans, myList);
}

bool testInteger() {
    std::list<Integer> ans;
    sjtu::list<Integer> myList;

    for (int i = 0; i < N; ++i){
        ans.push_back(Integer(N - i));
        myList.push_back(Integer(N - i));
    }

    return equal(ans, myList);
}

bool testMatrix() {
    using Matrix = Diamond::Matrix<double>;
    std::list<Matrix> ans;
    sjtu::list<Matrix> myList;

    for (int i = 0; i < N / 30; ++i){
        ans.push_back(Matrix(2, 3, i) * Matrix(3, 4, i));
        myList.push_back(Matrix(2, 3, i) * Matrix(3, 4, i));
    }

    return equal(ans, myList);
}

bool testElementAccess() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
        if (ans.front() != myList.front() || ans.back() != myList.back())
            return false;
    }
    return true;
}

bool testCapacityInfo() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < rand()%N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }
    if (ans.empty() != myList.empty() || ans.size() != myList.size())
        return false;

    myList.clear();
    return myList.empty() && myList.size() == 0;
}

bool testInsert() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        if (rand()%2) {
            ans.insert(ans.begin(), i);
            myList.insert(myList.begin(), i);
        } else {
            ans.insert(ans.end(), i);
            myList.insert(myList.end(), i);
        }
    }

    return equal(ans, myList);
}

bool testErase() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    for (int i = 0; i < rand()%N; ++i)
        if (rand()%2){
            if (*ans.erase(ans.begin()) != *myList.erase(myList.begin()))
                return false;
        } else {
            ans.erase(--ans.end());
            myList.erase(--myList.end());
        }

    return equal(ans, myList);
}

bool testException() {
    sjtu::list<int> myList, otherList;
    int ans = 0;

    try{ myList.pop_back(); } catch (...) { ans++; }
    try{ myList.pop_front(); } catch (...) { ans++; }
    try{ myList.front(); } catch (...) { ans++; }
    try{ myList.back(); } catch (...) { ans++; }
    sjtu::list<int>::iterator it = myList.end(), oit = otherList.end();
    try{ *it; } catch (...) { ans++; }
    try{ it--; } catch (...) { ans++; }
    try{ it++; } catch (...) { ans++; }
    try{ myList.erase(it); } catch (...) { ans++; }
    try{ myList.insert(oit, 0); } catch (...) { ans++; }

    return ans == 9;
}

bool testMerge() {
    std::list<int> ans1, ans2;
    sjtu::list<int> myList1, myList2;

    ans1.merge(ans2), myList1.merge(myList2);
    if (!equal(ans1, myList1))
        return false;

    for (int i = 0; i < N; ++i){
        ans1.push_back(i * 2);
        myList1.push_back(i * 2);
        ans2.push_back(i * 3);
        myList2.push_back(i * 3);
    }

    ans1.merge(ans2), myList1.merge(myList2);
    return equal(ans1, myList1);
}

bool testReverse(){
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        int x = rand();
        ans.push_back(x);
        myList.push_back(x);
    }

    ans.reverse(), myList.reverse();
    return equal(ans, myList);
}

bool testSort(){
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        int x = rand();
        ans.push_back(x);
        myList.push_back(x);
    }

    ans.sort(), myList.sort();
    return equal(ans, myList);
}

bool testUnique() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        int x = rand() % 2;
        ans.push_back(x);
        myList.push_back(x);
    }

    ans.unique(), myList.unique();
    return equal(ans, myList);
}

int main(){
    srand(time(NULL));
    bool (*testList[])() = {
            testConstructors, testAssignment, testPush, testPop, testIterator,
            testBint, testInteger, testMatrix, testElementAccess, testCapacityInfo,
            testInsert, testErase, testException, testMerge, testReverse, testSort, testUnique
    };
    const char* Messages[] = {
            "Test 1: Testing default & copy constructors and destructor...",
            "Test 2: Testing operator= ...",
            "Test 3: Testing push_front & push_back...",
            "Test 4: Testing pop_front & pop_back...",
            "Test 5: Testing iterator operations...",
            "Test 6: Testing class-bint...",
            "Test 7: Testing class-integer...",
            "Test 8: Testing class-Matrix...",
            "Test 9: Testing front() & back()...",
            "Test 10: Testing information of capacity...",
            "Test 11: Testing insert()...",
            "Test 12: Testing erase()...",
            "Test 13: Testing exception throw...",
            "Test 14: Testing merge()...",
            "Test 15: Testing reverse()...",
            "Test 16: Testing sort()...",
            "Test 17: Testing unique()..."
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