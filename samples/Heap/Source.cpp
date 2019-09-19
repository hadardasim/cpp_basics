// range heap example
#include <iostream>     // std::cout
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>       // std::vector

using namespace std;

int main() {

	std::vector<int> v = { 10,20,30,5,15 };

	std::make_heap(v.begin(), v.end());
	std::cout << "initial max heap   : " << v.front() << '\n';
	std::cout << "initial heap   : " ;
	for (auto n : v)
		cout << " " << n;
	cout << endl;

	/*
	Pop element from heap range
	===========================
	Rearranges the elements in the heap range [first,last) in such a way that the part considered a heap is shortened by one: 
	The element with the highest value is moved to (last-1).
	While the element with the highest value is moved from first to (last-1) (which now is out of the heap), 
	the other elements are reorganized in such a way that the range [first,last-1) preserves the properties of a heap.
	*/
	std::pop_heap(v.begin(), v.end()); v.pop_back();
	std::cout << "max heap after pop : " << v.front() << '\n';

	std::cout << "current heap   : ";
	for (auto n : v)
		cout << " " << n;
	cout << endl;

	v.push_back(99); std::push_heap(v.begin(), v.end());
	std::cout << "max heap after push: " << v.front() << '\n';

	std::sort_heap(v.begin(), v.end());

	std::cout << "final sorted range :";
	for (unsigned i = 0; i < v.size(); i++)
		std::cout << ' ' << v[i];

	std::cout << '\n';

	return 0;
}