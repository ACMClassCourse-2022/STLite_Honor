#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include "exceptions.hpp"
#include "linked_hashmap.hpp"
const int MAXN = 50001;
const int Mod = 998244353;
int cur = 233,base = 2333;
inline int rand(){
	return 1ll*cur*base%Mod;
}
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

class IntA{
public:
	static int counter;
	int val;
	
	IntA(int val) : val(val) {
		counter++;
	}

	IntA(const IntA &rhs) {
		val = rhs.val;
		counter++;
	}

	IntA & operator = (const IntA &rhs) {
		assert(false);
	}
	
	bool operator ==(const IntA &rhs) {
		return val == rhs.val;
	}
	friend bool operator < (const IntA &lhs, const IntA &rhs) {
		return lhs.val > rhs.val;
	}
	
	~IntA() {
		counter--;
	}
};

int IntA::counter = 0;

class IntB{
public:
	int *val;
	explicit IntB(int val = 0) : val(new int(val)) {
	}
	
	IntB(const IntB &rhs) {
		val = new int(*rhs.val);
	}
	
	IntB & operator =(const IntB &rhs) {
		if (this == &rhs) return *this;
		delete this->val;
		val = new int(*rhs.val);
		return *this;
	}
	
	bool operator !=(const IntB &rhs) const {
		return *val != *rhs.val;
	}
	
	bool operator ==(const IntB &rhs) const {
		return *val == *rhs.val;
	}
	
	~IntB() {
		delete this->val;
	}
};

struct Equal{
	bool operator ()(const IntA &a, const IntA &b)const {
		return a.val == b.val;
	}
};
class Hash {
public:
	unsigned int operator () (const IntA &lhs) const {
		int val = lhs.val;
		return std::hash<int>()(val);
	}
};

const std::vector<int> & generator(int n = MAXN) {
	static std::vector<int> raw;
	raw.clear();
	for (int i = 0; i < n; i++) {
		raw.push_back(rand());
	}
	return raw;
}

void tester1() {
	TestCore console("Operator [] & Iterator traverse testing...", 1, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			srcmap[x] = tmp;
			for (int c = 0; c < 10; c++) {
				int p = rand() % (i + 1);
				std::cout<<*(srcmap[ret[p]].val)<<"\n";
			}
			console.showProgress();
		}
		for (auto itA = srcmap.begin(); itA != srcmap.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester2() {
	TestCore console("Insertion function testing...", 2, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			srcmap.insert(sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::value_type(x, tmp));
			for (int c = 0; c < 10; c++) {
				int p = rand() % (i + 1);
				std::cout<<*(srcmap[ret[p]].val)<<"\n";
			}
			console.showProgress();
		}
		auto itB = srcmap.begin();
		for (auto itA = srcmap.begin(); itA != srcmap.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester3() {
	TestCore console("Deletion & Find function testing...", 3, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			srcmap.insert(sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::value_type(x, tmp));
			console.showProgress();
		}
		std::random_shuffle(ret.begin(), ret.end());
		for (auto x : ret) {
			if (srcmap.find(x) != srcmap.end()) {
				srcmap.erase(srcmap.find(x));
			}
			for (int c = 0; c < 10; c++) {
				int p = rand() % ret.size();
				if (srcmap.find(ret[p]) != srcmap.end()) {
					std::cout<<p<<"\n";
				}
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester4() {
	TestCore console("Error throwing A - Invalid Iterator testing...", 4, 0);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		++srcmap.end();
	} catch (sjtu::exception error) {
		try{
			sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
			--srcmap.begin();
			
		} catch (sjtu::exception error) {
			try{
				sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
				srcmap.end()++;
			} catch (sjtu::exception error) {
				try{
					sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
					srcmap.begin()--;
				} catch (sjtu::exception error) {
					console.pass();
					return;
				}
			}
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.fail();
}

void tester5() {
	TestCore console("Error throwing B - Invalid Const_Iterator testing...", 5, 0);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		++srcmap.cend();
	} catch (sjtu::exception error) {
		try{
			sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
			--srcmap.cbegin();
		} catch (sjtu::exception error) {
			try{
				sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
				srcmap.cend()++;
			} catch (sjtu::exception error) {
				try{
					sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
					srcmap.cbegin()--;
				} catch (sjtu::exception error) {
					console.pass();
					return;
				}
			}
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.fail();
}

void tester6() {
	TestCore console("Error throwing C - Invalid Index testing...", 6, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (auto x : ret) {
			srcmap[x] = IntB(rand());
			console.showProgress();
		}
		try{
			sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
			srcmap.at(IntA(-1)) = IntB(2);
		} catch (...) {
			console.pass();
			return;
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.fail();
}

void tester7() {
	const int MAXC = MAXN / 2;
	TestCore console("Copy constructure testing...", 7, MAXN + MAXC + 2 * (MAXN - MAXC));
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			srcmap.insert(sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::value_type(x, tmp));
			console.showProgress();
		}
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> tmp2(srcmap);
		std::random_shuffle(ret.begin(), ret.end());
		for (int i = 0; i < MAXC; i++) {
			if (srcmap.find(ret[i]) != srcmap.end()) {
				srcmap.erase(srcmap.find(ret[i]));
			}
			console.showProgress();
		}
		for (auto itA = srcmap.begin(); itA != srcmap.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
		for (auto itA = tmp2.begin(); itA != tmp2.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester8() {
	const int MAXC = MAXN / 2;
	TestCore console("Operator = testing...", 8, MAXN + MAXC + 2 * (MAXN - MAXC));
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			srcmap.insert(sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::value_type(x, tmp));
			console.showProgress();
		}
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> tmp2;
		tmp2 = srcmap;
		std::random_shuffle(ret.begin(), ret.end());
		for (int i = 0; i < MAXC; i++) {
			if (srcmap.find(ret[i]) != srcmap.end()) {
				srcmap.erase(srcmap.find(ret[i]));
			}
			console.showProgress();
		}
		for (auto itA = srcmap.begin(); itA != srcmap.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
		
		for (auto itA = tmp2.begin(); itA != tmp2.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester9() {
	TestCore console("At function testing...", 9, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			srcmap[x] = tmp;
			for (int c = 0; c < 10; c++) {
				int p = rand() % (i + 1);
				std::cout<<*(srcmap.at(ret[p]).val)<<"\n";
				tmp = IntB(rand());
				srcmap.at(ret[p]) = tmp;
			}
			console.showProgress();
		}
		auto itB = srcmap.cbegin();
		for (auto itA = srcmap.begin(); itA != srcmap.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester10() {
	TestCore console("Objects' independence testing...", 10, 6 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			srcmap.insert(sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::value_type(x, tmp));
			console.showProgress();
		}
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> src1(srcmap), src2;
		src2 = src1 = src1;
		for (int i = 0; i < (int)ret.size(); i++) {
			if (srcmap.find(ret[i]) != srcmap.end()) {
				srcmap.erase(srcmap.find(ret[i]));
			}
			console.showProgress();
		}
		ret = generator(MAXN);
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			src1.insert(sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::value_type(x, tmp));
			console.showProgress();
		}
		
		for (auto itA = srcmap.begin(); itA != srcmap.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
		
		for (auto itA = src1.begin(); itA != src1.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
		
		for (auto itA = src2.begin(); itA != src2.end(); ++itA) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester11() {
	const int MAXN = 100001;
	TestCore console("Comprehensive testing...", 11, 3 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal> srcmap;
		for (int i = 0, cnt = 0; i < (int)ret.size(); i++, cnt++) {
			int tmp = rand();
			auto retB = srcmap.insert(sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::value_type(IntA(ret[i]), IntB(tmp)));
			console.showProgress();
			if (!retB.second) {
				cnt--;
				ret[i] = -1;
				console.showProgress();
				continue;
			}
			if (rand() % 100 < 12 && cnt > 0) {
				int p = 0;
				while (ret[p] < 0) {
					p = rand() % (i + 1);
				}
				srcmap.erase(srcmap.find(ret[p]));
				ret[p] = -1;
				cnt++;
				console.showProgress();
			}
			std::cout<<srcmap.size()<<"\n";
		}
		for (auto itA = srcmap.begin(); itA != srcmap.end(); ++itA ) {
			std::cout<<(itA -> first).val<<"\n";
			console.showProgress();
		}
		
		const auto srctmp(srcmap);
		
		sjtu::linked_hashmap<IntA, IntB, Hash,Equal>::const_iterator citB = srctmp.cbegin();
		
		srctmp.size();
		
		for (auto x : ret) {
			if (x >= 0) {
				std::cout<<*(srcmap.at(x).val)<<"\n";
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

int main() {
	tester1();
	tester2();
	tester3();
	tester4();
	tester5();
	tester6();
	tester7();
	tester8();
	tester9();
	tester10();
	tester11();
	return 0;
}
