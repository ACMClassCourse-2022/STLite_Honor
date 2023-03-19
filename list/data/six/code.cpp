#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <ctime>

#include "exceptions.hpp"
#include "list.hpp"
#include "class-bint.hpp"
#include "class-integer.hpp"
#include "class-matrix.hpp"

const int MAXN = 50005;

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
        TestCore console("test 1 ...", 1, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
    auto mirr = generator(MAXN/20);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2) stdlist.push_back(tmp), mylist.push_back(tmp);
            else stdlist.push_front(tmp), mylist.push_front(tmp);
        }

        std::list<Int> ministd;
        sjtu::list<Int> minimy;
        for (int i = 0;i < 10;i++) ministd.push_back(Int(mirr[i])), minimy.push_back(Int(mirr[i]));
        for (int i = 10;i < mirr.size();i++) {
            Int tmp = Int(mirr[i]);
            int pos = rands() % (ministd.size());
            auto stdit = ministd.begin();
            auto myit = minimy.begin();
            for (int j = 0;j < pos;j++) ++stdit, ++myit;
            if (*stdit != *myit) {
                console.fail();
                return;
            }
            if (rands() % 4) ministd.insert(stdit, tmp), minimy.insert(myit, tmp);
            else if (!ministd.empty()) ministd.erase(stdit), minimy.erase(myit);
        }

		stdlist.sort(), ministd.sort();
		mylist.sort(), minimy.sort();
		
        stdlist.merge(ministd), mylist.merge(minimy);

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
        TestCore console("test 2...", 2, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        Int::born = Int::dead = 0;
        std::list<Int> stdlist1, stdlist2;
        sjtu::list<Int> mylist1, mylist2;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2) stdlist1.push_back(tmp), mylist1.push_back(tmp);
            else stdlist2.push_back(tmp), mylist2.push_back(tmp);
        }
        stdlist1.sort(), mylist1.sort();
        stdlist2.sort(), mylist2.sort();

        stdlist1.merge(stdlist2), mylist1.merge(mylist2);
        stdlist1.merge(stdlist2), mylist1.merge(mylist2);

        stdlist1.unique(), mylist1.unique();

        if (!equal(stdlist1, mylist1)){
            console.fail();
            return;
        }

	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester3() {
        TestCore console("test 3...", 3, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        std::list<Int>::iterator stdit = stdlist.begin();
        sjtu::list<Int>::iterator myit = mylist.begin();
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            stdit = stdlist.insert(stdit, tmp);
            myit = mylist.insert(myit, tmp);
            int gap = rands() % 100;
            int ins = (rands() % 2);
            for (int j = 0;j < gap;j++) {
                if (!ins && (stdit == stdlist.begin() || myit == mylist.begin())) break;
                if (ins && (stdit == stdlist.end() || myit == mylist.end())) break;
                if (!ins) --stdit, --myit;
                else ++stdit, ++myit;
            }
            stdlist.insert(stdit, tmp), mylist.insert(myit, tmp);
        }

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }

        int ins = (rands() % 10) + 3;
        stdit = stdlist.begin(), myit = mylist.begin();
        while (true) {
            if (stdit == stdlist.end() || myit == mylist.end()) break;
            stdit = stdlist.erase(stdit);
            myit = mylist.erase(myit);
            bool flag = 0;
            for (int i = 0;i < ins;i++) {
                if (stdit == stdlist.end() || myit == mylist.end()){
                    flag = 1; break;
                }
                ++stdit, ++myit;
            }
            if (flag) break;
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
        TestCore console("test 4...", 4, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN/3);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2)  stdlist.push_front(tmp), mylist.push_front(tmp);
            else stdlist.push_back(tmp), mylist.push_back(tmp);

            if (!(rands() % 20)) stdlist.reverse(), mylist.reverse();
        }

        if (!equal(stdlist, mylist)){
            console.fail();
            return;
        }

        while (!stdlist.empty() && !mylist.empty()){
            int gap = rands() % stdlist.size();
            auto stdit = stdlist.begin();
            auto myit = mylist.begin();
            for (int i = 0; i < gap;i++) ++stdit, ++myit;
            if (*stdit != *myit) {
                console.fail();
                return;
            }
            if (rands() % 2) stdlist.pop_front(), mylist.pop_front();
            else stdlist.pop_back(), mylist.pop_back();
        }
        if (!stdlist.empty() || !mylist.empty()) {
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
    srand(time(NULL));
	tester1();
	tester2();
	tester3();
	tester4();
	return 0;
}
