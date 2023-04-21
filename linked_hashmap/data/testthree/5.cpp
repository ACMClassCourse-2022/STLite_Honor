#include<iostream>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include "linked_hashmap.hpp"
using namespace std;
const int MOD = 998244353;
int cur = 233,base = 2333;
inline int rand(){
	return 1ll*cur*base%MOD;
}
bool check1(){ //insert by []
	int a, b;
	sjtu::linked_hashmap<int, int> Q;	
	for(int i = 1; i <= 100000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[a] = b;
		}
	}
	sjtu::linked_hashmap<int, int> :: value_type pp;
	for(int i = 1; i <= 100000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q.insert(sjtu::linked_hashmap<int, int> :: value_type(a, b));
		}
	}
	cout<<Q.size()<<"\n";
	sjtu::linked_hashmap<int, int>::iterator it;
	for(it = Q.begin(); it != Q.end(); it++){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	return 1;
}

bool check2(){//Q.insert
	sjtu::linked_hashmap<int, int> Q;
	sjtu::linked_hashmap<int, int> :: iterator it;
	
	int num[51];
	for(int i = 1; i <= 50; i++) num[i] =i;
	for(int i = 1; i <= 100; i++) swap(num[rand() % 50 + 1], num[rand() % 50 + 1]);
	for(int i = 1; i <= 50; i++) Q[num[i]] = rand();
	int p = Q[6];
	if(Q.insert(sjtu::linked_hashmap<int, int>::value_type(6, 9)).second) return 0;
	it = Q.insert(sjtu::pair<int, int>(6, 9)).first;
	
	if(it -> second != Q[6]) return 0;
	
	it = Q.insert(sjtu::linked_hashmap<int, int>::value_type(325, 666)).first;
	if(it -> first != 325 || it -> second != 666) return 0;
	return 1;
}

bool check3(){//find remove 
	sjtu::linked_hashmap<int, int> Q;
	int num[30001];
	num[0] = 0;
	for(int i = 1; i <= 30000; i++) num[i] = num[i - 1] + rand() % 325 + 1; 
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 30000; i++){
		int t = rand();
		 Q[num[i]] = t;
	}
	
	sjtu::linked_hashmap<int, int>::iterator it;
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 10325; i++){
		it = Q.find(num[i]); 
		Q.erase(it);
	}	
	cout<<Q.size()<<"\n";
	it = Q.begin();
	for(it = Q.begin(); it != Q.end(); it++){ 
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	return 1;
}

bool check4(){//const_iterator
	int a, b;
	sjtu::linked_hashmap<int, int> Q;
	for(int i = 1; i <= 30000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[a] = b;
		}
	}
	sjtu::linked_hashmap<int, int> :: iterator pt;
	pt = Q.begin();
	sjtu::linked_hashmap<int, int> :: const_iterator it(pt), itt;
	for(it = Q.cbegin(); it != Q.cend(); ++it){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.cend(); it != Q.cbegin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	itt = --Q.cend();
	if(it == itt) return 1;
	return 0;
}

bool check5(){// insert && remove 
	int a, b;
	sjtu::linked_hashmap<int, int> Q;
	for(int i = 1; i <= 3000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[a] = b;
		}
	}
	while(!Q.empty()){
		cout<<Q.begin() -> first<<" "<<Q.begin() -> second<<"\n"; 
		Q.erase(Q.begin());
	}
	if(Q.begin() != Q.end()) return 0;
	Q.clear();
	sjtu::linked_hashmap<int, int> :: iterator it;
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) swap(num[rand() % 3000 + 1], num[rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(Q.count(num[i])){
				it = Q.find(num[i]); Q.erase(it);
			}
			else cout << "gg!" << endl;
		}
		else{
			Q[num[i]] = num[i];
			left[num[i]]++;
		}
	}
	cout<<Q.size()<<"\n";
	it = Q.begin();
	for(it  = Q.begin(); it != Q.end(); ++it){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	return 1;
}

bool check6(){ // copy test
	int a, b;
	sjtu::linked_hashmap<int, int> Q1;
	sjtu::linked_hashmap<int, int> :: value_type pp;
	for(int i = 1; i <= 10000; i++){
		a = rand(); b = rand();
		if(!Q1.count(a)){
			Q1.insert(sjtu::pair<int, int>(a, b));
		}
	}
	sjtu::linked_hashmap<int, int> Q(Q1);
	cout<<Q.size()<<"\n";
	sjtu::linked_hashmap<int, int>::iterator it;
	for(it = Q.begin(); it != Q.end(); it++){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	while(!Q.empty()) Q.erase(Q.begin());
	if(Q.size() != 0 || Q.begin() != Q.end()) return 0;

	for(it = Q1.begin(); it != Q1.end(); it++){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q1.end(); it != Q1.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	return 1; 
}

bool check7(){ //"=" operator 
	int a, b;
	sjtu::linked_hashmap<int, int> Q1;
	sjtu::linked_hashmap<int, int> :: value_type pp;
	for(int i = 1; i <= 10000; i++){
		a = rand(); b = rand();
		if(!Q1.count(a)){
			Q1.insert(sjtu::linked_hashmap<int, int> :: value_type(a, b));
		}
	}
	sjtu::linked_hashmap<int, int> Q;
	Q = Q1;
	cout<<Q.size()<<"\n";
	sjtu::linked_hashmap<int, int>::iterator it;
	for(it = Q.begin(); it != Q.end(); it++){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	while(!Q.empty()) Q.erase(Q.begin());
	if(Q.size() != 0 || Q.begin() != Q.end()) return 0;
	for(it = Q1.begin(); it != Q1.end(); it++){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q1.end(); it != Q1.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	return 1; 
}

bool check8(){ //  clear && insert
	int a, b;
	sjtu::linked_hashmap<int, int> Q;
	for(int i = 1; i <= 1000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			if(Q.count(a)) return 0;
			Q[a] = b;
		}
	}
	Q.clear();
	if(Q.begin() != Q.end()) return 0;
	if(Q.size()) return 0;
	for(int i = 1; i <= 1000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q.insert(sjtu::linked_hashmap<int, int> :: value_type(a, b));
		}
	}
	sjtu::linked_hashmap<int, int> :: iterator it;
	for(it = Q.begin(); it != Q.end(); ++it){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<< it -> first<<" "<<(*it).second<<'\n';
	}
	return 1;
}

bool check9(){//just have fun!
	sjtu::linked_hashmap<int, int> Q;
	sjtu::linked_hashmap<int, int> :: iterator fun;
	sjtu::linked_hashmap<int, int> :: const_iterator cfun;
	fun = Q.find(325); cfun = Q.find(325);
	sjtu::linked_hashmap<int, int> P(Q);
	sjtu::linked_hashmap<int, int> O;
	O = Q;
	Q.clear();
	if(Q.size()) return 0;
	Q[3] = 5; Q[6] = 10;
	const sjtu::linked_hashmap<int, int> Q_const(Q);
	sjtu::linked_hashmap<int, int> :: const_iterator cit;
	Q_const.at(3);
	cit = Q_const.find(3);
	O = Q;
	sjtu::linked_hashmap<int, int> :: iterator itQ, itO;
	sjtu::linked_hashmap<int, int> :: const_iterator citQ, citO;
	itQ = Q.end(); itO = O.end();
	citQ = Q.cend(); citO = O.cend();
	if(itQ == itO) return 0; if(citQ == citO) return 0;
	if(!(itQ != itO)) return 0; if(!(citQ != citO)) return 0;
	if(itQ == citO) return 0; if(itO == citQ) return 0;
	if(!(itQ != citO)) return 0; if(!(itO != citQ)) return 0;
	if(!(citQ == itQ)) return 0; if(citQ != itQ) return 0; 
	return 1;
}

class node{
	public:
	int num;
	public:
	node() : num(0) {}
	node(int p) : num(p) {}
	bool operator <(const node &b) const{
		return num < b.num;
	}
	bool operator !=(const node &b) const{
		return num != b.num;
	}
};
class Equal {
public:
	bool operator () (const node &lhs, const node &rhs) const {
		return lhs.num == rhs.num;
	}
};
class Hash {
public:
	unsigned int operator () (const node &rhs) const {
		int val = rhs.num;
		return std::hash<int>()(val);
	}
};
bool check10(){//class writen by users
	int a, b;
	sjtu::linked_hashmap<node, int,Hash,Equal> Q;
	for(int i = 1; i <= 3000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[node(a)] = b;
		}
	}
	while(!Q.empty()){
		cout<<Q.begin() -> first.num<<" "<<Q.begin() -> second<<"\n"; 
		Q.erase(Q.begin());
	}
	if(Q.begin() != Q.end()) return 0;
	Q.clear(); 
	sjtu::linked_hashmap<node, int,Hash,Equal> :: iterator it;
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) swap(num[rand() % 3000 + 1], num[rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(Q.count(node(num[i]))){
				it = Q.find(node(num[i])); Q.erase(it);
			}
			else cout << "gg!" << endl;
		}
		else{
			Q[node(num[i])] = num[i];
			left[num[i]]++;
		}
	}
	cout<<Q.size()<<"\n";
	it = Q.begin();
	for(it = Q.begin(); it != Q.end(); it++){ 
		cout<< it -> first.num<<" "<<(*it).second<<'\n';
	}
	for(it = --Q.end(); it != Q.begin(); --it){
		cout<< it -> first.num<<" "<<(*it).second<<'\n';
	}
	return 1;	
}

bool check11(){
	sjtu::linked_hashmap<string, int> Q;
	sjtu::linked_hashmap<string, int> :: iterator kit;
	kit = Q.begin();
	Q["aa"] = 5;
	Q["bb"] = 16;
	Q["cc"] = 20;
	Q["lucky"] = 325;
	Q["lwher"] = 666;
	int p = Q.at("lwher");
	if(p != 666) return 0;
	p = Q.at("lucky");
	if(p != 325) return 0;
	int OK = 0;
	try{
		p = Q.at("dd");
	}
	catch(...) {OK++;}
	sjtu::linked_hashmap<string, int> :: iterator it;
	try{
		it = Q.find("ok");
		Q.erase(it);
	}
	catch(...) {OK++;}
	try{
		Q.erase(kit);
	}
	catch(...) {OK++;}
	sjtu::linked_hashmap<string, int> Q2(Q);
	try{
		it = Q2.find("cc");
		Q.erase(it);
	}
	catch(...) {OK++;}
	it = Q.find("cc");
	Q.erase(it);
	try{
		p = Q.at("cc");
	}
	catch(...) {OK++;}	
	const sjtu::linked_hashmap<string, int> Qc(Q);
	try{
		Qc["hehe"];
	}
	catch(...) {OK++;}
	
	return OK == 6;
}

bool check12(){ // erase(it++)
	sjtu::linked_hashmap<int, int> Q;
	int num[30001];
	num[0] = 0;
	for(int i = 1; i <= 30000; i++) num[i] = num[i - 1] + rand() % 325 + 1; 
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 30000; i++){
		int t = rand();
		Q[num[i]] = t;
	}
	
	sjtu::linked_hashmap<int, int>::iterator it;
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 10325; i++){
		it = Q.find(num[i]); Q.erase(it++);
	}	
	cout<<Q.size()<<"\n";
	it = Q.begin();
	for(it = Q.begin(); it != Q.end(); it++){ 
		cout<<it->second<<"\n";
	}
	it = --Q.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<<it->second<<"\n";
	}
	return 1;
}

bool check13(){ // erase(it--)
	sjtu::linked_hashmap<int, int> Q;
	int num[30001];
	num[0] = 0;
	for(int i = 1; i <= 30000; i++) num[i] = num[i - 1] + rand() % 325 + 1; 
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 30000; i++){
		int t = rand();
		Q[num[i]] = t;
	}
	
	sjtu::linked_hashmap<int, int>::iterator it;
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 10325; i++){
		it = Q.find(num[i]); if(it != Q.begin()) Q.erase(it--);
	}	
	cout<<Q.size()<<"\n";
	it = Q.begin();
	for(it = Q.begin(); it != Q.end(); it++){ 
		cout<<it->second<<"\n";
	}
	it = --Q.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		cout<<it->second<<"\n";
	}
	return 1;
}

bool check14(){// have fun
	sjtu::linked_hashmap<int, int> Q;
	Q[3] = 25; Q[25] = 3; Q[1314] = 520; Q[3225] = 1; Q[10000] = 6666; 
	sjtu::linked_hashmap<int, int>::iterator it;
	it = Q.find(3225);
	Q.erase(--Q.end());
	if(it -> first != 3225 || it -> second != 1) return 0;
	Q.erase(Q.begin());
	if(it -> first != 3225 || it -> second != 1) return 0;
	return 1;
}
int A = 325, B = 2336, Last = 233, Mod = 1000007;

int Rand(){
	return Last = (A * Last + B) % Mod;
}

void easy_test(){
	sjtu::linked_hashmap<int, int> Q;
	Q.clear();
	sjtu::linked_hashmap<int, int> :: iterator it;
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) swap(num[Rand() % 3000 + 1], num[Rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(Q.count(num[i])){
				it = Q.find(num[i]); Q.erase(it);
			}
			else cout << "gg!" << endl;
		}
		else{
			Q[num[i]] = num[i];
			left[num[i]]++;
		}
	}
	for(it = Q.begin(); it != Q.end(); ++it){ 
		cout << it -> first << " "  << it -> second << " ";
	}
	cout << endl;
}

int main(){
	easy_test();
	if(!check1()) cout << "Test 1 Failed......" << endl; else cout << "Test 1 Passed!" << endl;
	if(!check2()) cout << "Test 2 Failed......" << endl; else cout << "Test 2 Passed!" << endl;
	if(!check3()) cout << "Test 3 Failed......" << endl; else cout << "Test 3 Passed!" << endl;
	if(!check4()) cout << "Test 4 Failed......" << endl; else cout << "Test 4 Passed!" << endl;
	if(!check5()) cout << "Test 5 Failed......" << endl; else cout << "Test 5 Passed!" << endl;
	if(!check6()) cout << "Test 6 Failed......" << endl; else cout << "Test 6 Passed!" << endl;
	if(!check7()) cout << "Test 7 Failed......" << endl; else cout << "Test 7 Passed!" << endl;
	if(!check8()) cout << "Test 8 Failed......" << endl; else cout << "Test 8 Passed!" << endl;
	if(!check9()) cout << "Test 9 Failed......" << endl; else cout << "Test 9 Passed!" << endl;
	if(!check10()) cout << "Test 10 Failed......" << endl; else cout << "Test 10 Passed!" << endl;
	if(!check11()) cout << "Test 11 Failed......" << endl; else cout << "Test 11 Passed!" << endl;
	if(!check12()) cout << "Test 12 Failed......" << endl; else cout << "Test 12 Passed!" << endl;
	if(!check13()) cout << "Test 13 Failed......" << endl; else cout << "Test 13 Passed!" << endl;
	if(!check14()) cout << "Test 14 Failed......" << endl; else cout << "Test 14 Passed!" << endl;
	return 0;
}

