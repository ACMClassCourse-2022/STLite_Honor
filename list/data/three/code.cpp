#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <ctime>
#include "exceptions.hpp"
#include "list.hpp"

const int MAXN = 10001;

enum Color{
	Red, Green, Blue, Normal
};

class TestCore{
private:
	const char *title;
	const int id, total;
	long dfn;
	int counter, enter;
public:	
	TestCore(const char *title, const int &id, const int &total) : title(title), id(id), total(total), dfn(clock()), counter(0), enter(0) {
	}
	void init() {
		static char tmp[200];
		sprintf(tmp, "Test %d: %-55s", id, title);
		printf("%-65s", tmp);
	}
	void showMessage(const char *s, const Color &c = Normal) {
	}
	void showProgress() {
	}
	void pass() {
		showMessage("PASSED", Green);
		printf("PASSED");
	}
	void fail() {
		showMessage("FAILED", Red);
		printf("FAILED");
	}
	~TestCore() {
		puts("");
		fflush(stdout);
	}
};

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

class Int{
public:
	static int born;
    static int dead;
	int val;
	
	Int(int val) : val(val) {
		born++;
	}

	Int(const Int &rhs) {
		val = rhs.val;
		born++;
	}

	Int & operator = (const Int &rhs) {
		born++; dead++;
        val = rhs.val;
        return *this;
	}
	
	bool operator == (const Int &rhs) const {
		return val == rhs.val;
	}
    bool operator != (const Int &rhs) const {
		return val != rhs.val;
	}
	friend bool operator < (const Int &lhs, const Int &rhs) {
		return lhs.val > rhs.val;
	}
	
	~Int() {
		dead++;
	}
};

int Int::born = 0;
int Int::dead = 0;

int rands() {
    int r = int (rand() << 15) + int ( rand() );
    return r;
}

const std::vector<int> & generator(int n = MAXN) {
	static std::vector<int> raw;
	raw.clear();
	for (int i = 0; i < n; i++) {
		raw.push_back(rands());
	}
	return raw;
}

void tester1() {
	TestCore console("Push and pop testing...", 1, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2) stdlist.push_back(tmp), mylist.push_back(tmp);
            else stdlist.push_front(tmp), mylist.push_front(tmp);
        }

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }

        for (int i = 0;i < MAXN/2;i++) {
            if (rands() % 2) stdlist.pop_back(), mylist.pop_back();
            else stdlist.pop_front(), mylist.pop_front();
        }

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }
		
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester2() {
	TestCore console("Iterator testing...", 2, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            stdlist.push_back(tmp), mylist.push_back(tmp);
        }

        for (int i = 0;i < MAXN/2;i++) {
            int gap = rands() % stdlist.size();
            auto stdit = stdlist.begin();
            auto myit = mylist.begin();
            for (int i = 0;i < gap;i++)
                ++stdit, ++myit;
            if (*stdit != *myit) {
                console.fail();
                return;
            }
        }

        for (int i = 0;i < MAXN/2;i++) {
            int gap = (rands() % stdlist.size()) + 1;
            auto stdit = stdlist.end();
            auto myit = mylist.end();
            for (int i = 0;i < gap;i++)
                --stdit, --myit;
            if (*stdit != *myit) {
                console.fail();
                return;
            }

        }

	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester3() {
	TestCore console("Insert and erase testing...", 3, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN/2);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        std::list<Int>::iterator stdit = stdlist.end();
        sjtu::list<Int>::iterator myit = mylist.end();
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            stdit = stdlist.insert(stdit, tmp);
            myit = mylist.insert(myit, tmp);
            stdlist.insert(stdit, tmp), mylist.insert(myit, tmp);
            int gap = rands() % stdlist.size();
            stdit = stdlist.begin(), myit = mylist.begin();
            for (int i = 0;i < gap;i++){
                stdit = ++stdit;
                myit = ++myit;
            }
        }

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }

        for (int i = 0;i < MAXN/2;i++) {
            int gap = rands() % stdlist.size();
            stdit = stdlist.begin(), myit = mylist.begin();
            for (int i = 0;i < gap;i++){
                stdit = ++stdit;
                myit = ++myit;
            }
            stdlist.erase(stdit), mylist.erase(myit);
        }

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }
		
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester4() {
	TestCore console("Size and clear testing...", 4, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            stdlist.push_front(tmp), mylist.push_front(tmp);
            if (stdlist.size() != mylist.size()) {
                console.fail();
                return;
            }
        }

        stdlist.clear(), mylist.clear();
        if (!mylist.empty() || mylist.size()) {
            console.fail();
            return;
        }
        
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester5() {
	TestCore console("Sort testing...", 5, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            stdlist.push_front(tmp), mylist.push_front(tmp);
        }

        stdlist.sort(), mylist.sort();

        if (!equal(stdlist, mylist)){
            console.fail();
            return;
        }
        
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester6() {
	TestCore console("Unique testing...", 6, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            stdlist.push_front(tmp), mylist.push_front(tmp);
            stdlist.push_back(tmp), mylist.push_back(tmp);
        }

        stdlist.unique(), mylist.unique();
        
        if (!equal(stdlist, mylist)){
            console.fail();
            return;
        }
        
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester7() {
	TestCore console("Merge testing...", 7, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist1, stdlist2;
        sjtu::list<Int> mylist1, mylist2;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2) stdlist1.push_front(tmp), mylist1.push_front(tmp);
            else stdlist2.push_back(tmp), mylist2.push_back(tmp);
            
        }

        stdlist1.sort(), stdlist2.sort();
        mylist1.sort(), mylist2.sort();

        Int::born = 0;
        Int::dead = 0;
        
        stdlist1.merge(stdlist2);
        mylist1.merge(mylist2);
        
        if (Int::born || Int::dead || !equal(stdlist1, mylist1)){
            console.fail();
            return;
        }
        
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester8() {
	TestCore console("Reverse testing...", 8, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2) stdlist.push_front(tmp), mylist.push_front(tmp);
            else stdlist.push_back(tmp), mylist.push_back(tmp);
            
        }

        Int::born = 0;
        Int::dead = 0;

        stdlist.reverse();
        mylist.reverse();
        
        if (Int::born || Int::dead || !equal(stdlist, mylist)){
            console.fail();
            return;
        }
        
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

int main() {
    // freopen("ans.out", "w", stdout);
    srand(time(NULL));
	tester1();
	tester2();
	tester3();
	tester4();
	tester5();
	tester6();
	tester7();
	tester8();
	return 0;
}