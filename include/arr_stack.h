
#ifndef WIZ_STACK_H
#define WIZ_STACK_H

#include "arr_vector.h"

namespace wiz {
	template <class T>
	class arr_stack {
	private:
		arr_vector<T> arr;
	public:
		T & top() {
			return arr.back();
		}
		const T & top() const {
			return arr.back();
		}
		void push(const T& val) {
			arr.push_back(val);
		}
		void push(T&& val) {
			arr.push_back(std::move(val));
		}
		void pop() {
			arr.pop_back();
		}
		bool empty() const {
			return  arr.empty();
		}
		auto size() const {
			return arr.size();
		}
		void clear() {
			arr.clear();
		}
	};
}


#endif

