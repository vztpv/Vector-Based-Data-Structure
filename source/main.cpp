
#include <iostream>

#include <ctime>

#include "arr_vector.h"
#include "arr_stack.h"
#include "arr_queue.h"
#include "arr_map.h"

#include <queue>
#include <map>

#include "wiz/array_map.h"
#include "wiz/Queues.h"

void test1();
void test2();

int main(void)
{
	//test1(); // arrayvector, arraystack, arrayqueue
	test2();

	return 0;
}

void test2() {

	int a = clock(); // 
	for (int i = 0; i < 10000; ++i) {
		wiz::ArrayMap<long long, long long> x;
		//std::map<long long, long long> x;
		const long long MAX = 500;
		//wiz::arr_map<long long, long long> x(5);

		for (long long i = 0; i < MAX; ++i) {
			x.insert(std::pair(MAX - i, i + 1));
		}
		for (long long i = 0; i < MAX; ++i) {
			x[MAX - i];
		}
	}
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
