
#include <iostream>

#include <cstdlib>
#include <ctime>

#include "arr_vector.h"
#include "arr_stack.h"
#include "arr_queue.h"
#include "arr_map.h"

#include <queue>
#include <map>

#include "wiz/global.h"
#include "Header.h"
//#include "wiz/array_map.h"
#include "wiz/Queues.h"
//#include "arr_rbtree.h"

void test1();
void test2();

int main(void)
{
	//test1(); // arrayvector, arraystack, arrayqueue
	test2();

	return 0;
}


class Data
{
public:
	long long first;
	long long second;
//	std::string second;
public:
	bool operator<(const Data& other) const {
		return this->first < other.first;
	}
	bool operator!=(const Data& other) const {
		return this->first != other.first;
	}
	bool operator==(const Data& other) const {
		return this->first == other.first;
	}
};
void test2() {
	srand(0); // time(nullptr));

	int a = clock(); // 
	

//	wiz::RB_Tree<Data, wiz::ASC<Data>>* x = new wiz::RB_Tree<Data, wiz::ASC<Data>>();

	wiz::ArrayMap<long long, long long>* x = new wiz::ArrayMap<long long, long long>();

//	std::map<long long, long long>* x = new std::map<long long, long long>();

	const long long MAX = 1000000; // 4 * 1024;

	//(*x)[MAX];

	for (int i = 0; i < 10; ++i) { // 100
		x->clear(); 
		//wiz::arr_map<long long, long long> x(5);
	//	x->reserve(MAX);

		for (long long i = 0; i < MAX; ++i) {
			std::pair<long long, long long> temp(wiz::Rand2<long long>()%MAX, i + 1); // "abcdabcdabcdabcdabcdabcdabcdabcd"); //MAX - i, i + 1);

			//std::cout << temp.first << " " << temp.second << "\n";
			x->insert(temp);
		}
		x->update();

		/*for (long long i = 0; i < MAX; ++i) {
			x->remove(std::pair<long long, long long>(i, 0));
			//x->erase(i);
		}*/
	}
	
	/*
	for (int i = 0; i < x->size(); ++i) {
		if (x->find(i) != x->end()) {
			std::cout << (*x)[i] << "\n";
		}
	}
	*/

	delete x;

	int b = clock();
	std::cout << b - a << "ms" << std::endl;
}

void test1() {
	wiz::arr_vector<int> x;
	wiz::arr_stack<int> y;
	wiz::ArrayQueue<long long> z;
	//wiz::arr_queue<long long> z;
	//std::queue<long long> z;

	long long MAX = 300000000;
	int a = clock();
	for (long long i = 0; i < MAX; ++i) {
		z.push(i);
	}
	for (long long i = 0; i < MAX / 2; ++i) {
		//std::cout << i << " " << z.front() << std::endl;
		z.pop();
	}
	for (long long i = MAX / 2; i < MAX; ++i) {
		z.push(i);
	}
	for (long long i = MAX / 2; i < MAX; ++i) {
		//std::cout << i << " " << z.front() << std::endl;
		z.pop();
	}
	int b = clock();
	std::cout << b - a << std::endl;

	return ;
}
