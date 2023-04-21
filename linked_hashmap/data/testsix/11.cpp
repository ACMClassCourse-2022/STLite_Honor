#include "linked_hashmap.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <algorithm> 
class Integer {
public:
	static int counter;
	int val;
	
	Integer(int val) : val(val) {
		counter++;
	}

	Integer(const Integer &rhs) {
		val = rhs.val;
		counter++;
	}

	Integer& operator = (const Integer &rhs) {
		assert(false);
	}

	~Integer() {
		counter--;
	}
};

int Integer::counter = 0;

class Equal {
public:
	bool operator () (const Integer &lhs, const Integer &rhs) const {
		return lhs.val ==rhs.val;
	}
};
class Hash {
public:
	unsigned int operator () (const Integer &lhs) const {
		return std::hash<int>()(lhs.val); 
	}
};
const int mod = 23333;
int cur = 3,factor = 233;
inline int getNum() {
	cur=1ll*cur*factor%mod;
	return cur;
}
void tester(void) {
	
	sjtu::linked_hashmap<Integer,int,Hash,Equal> map;
	for(int i=0;i<1000;++i) {
		for(int j=0;j<10000;++j) {
			if(!map.count(Integer(getNum()))) {
				int x=getNum();
				map[Integer(x)] = x;
			}
		}
		int ans=0;
		sjtu::linked_hashmap<Integer,int,Hash,Equal>::iterator it= map.begin();
		while(it!=map.end()) {
			ans+=it->second;
			++it; 
		}
		map.clear();
		std::cout<<ans<<"\n";
	}
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	tester();
	std::cout << Integer::counter << std::endl;
}
