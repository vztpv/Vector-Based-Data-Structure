

// chk wiz/Queues.h !!

#ifndef ARR_QUEUE_H
#define ARR_QUEUE_H

#include "arr_vector.h" 

namespace wiz {
	template <class T>
	class arr_queue {
		using size_type = typename arr_vector<T>::size_type; // chk typename!
	private:
		arr_vector<T> arr; // arr has length of vector?
		size_type start = 0;
		size_type size_ = 0;
	public:
		void push(const T& val) { // push_back
			if (start + size_ >= arr.size()) {
				arr.push_back(T());
			}
			arr[start + size_] = val;
			size_++;
		}
		void push(T&& val) { // push_back
			if (start + size_ >= arr.size()) {
				arr.push_back(T());
			}
			arr[start + size_] = std::move(val);
			size_++;
		}
		void pop() { // pop_front
			if (empty()) { return; } // false?
			// shift
			if (start >= arr.size() / 2) {
				std::move(arr.begin() + start, arr.begin() + start + size_, arr.begin());
				start = 0;
			}
			else {
				start++;
			}
			size_--;
		}
		T& front() {
			return arr[start];
		}
		const T& front() const {
			return arr[start];
		}

		bool empty() const {
			return size() == 0;
		}
		size_type size() const {
			return size_;
		}
		void clear() {
			arr.clear();
			start = 0;
			size_ = 0;
		}
	};
}


#endif

