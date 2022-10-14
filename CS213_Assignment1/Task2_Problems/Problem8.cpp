#include <iostream>
using namespace std;

template<class T, size_t sz>
class array {
	T data;
	int arr_size;
	array* next;
public:
	array() {
		next = new array;
	}
	size_t size();
	~array() {
		delete next;
	}
};

template<class T, size_t sz>
size_t array<T, sz> :: size() {
	return sz;
}

int main() {
	array<int, 5> arr;
	cout << arr.size();
	return 0;
}