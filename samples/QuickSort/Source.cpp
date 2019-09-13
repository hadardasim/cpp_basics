#include <iostream>
#include <vector>
#include <random>
#include <cassert>


// modify the array in place and return a pivot index.
// all items left to the pivot index are less or equal to the pivot and all items to the right are greater
template <typename TArray>
size_t partition(TArray& arrLike, size_t first, size_t last)
{
	auto pivot_value = arrLike[last];
	auto pivot_index = first;
	for (size_t pos = first; pos < last; ++pos)
	{
		if (arrLike[pos] < pivot_value)
		{
			std::swap(arrLike[pos], arrLike[pivot_index]);
			++pivot_index;
		}
	}
	std::swap(arrLike[pivot_index], arrLike[last]);
	assert(pivot_index >= first);
	assert(pivot_index <= last);
	return pivot_index;
}

template <typename TArray>
void sort_rec(TArray& arrLike, size_t first, size_t last)
{
	if (first < last)
	{
		if (first + 1 == last)
		{
			if (arrLike[first] > arrLike[last])
				std::swap(arrLike[first], arrLike[last]);
			return;
		}
		auto pivot = partition(arrLike, first, last);		
		if (pivot > first)
			sort_rec(arrLike, first, pivot-1);
		sort_rec(arrLike, pivot + 1, last);
	}
}

// todo: replace this with a template after we pass all the test
template <typename TArray>
void sort(TArray& arrLike)
{
	sort_rec(arrLike, 0, arrLike.size() - 1);
}

template <typename T>
bool test(size_t size, size_t mod = 0, T scale = (T)1)
{
	if (!mod)
		mod = size;
	std::vector<T> data(size);
	for (auto & item : data)
		item = (rand() % mod)*scale;

	sort(data);
	std::cout << size << ": ";
	for (size_t i = 0; i + 1 < size; ++i)
	{
		std::cout << data[i] << " ";
		if (data[i] > data[i + 1])
		{
			std::cout << std::endl;
			return false;
		}
	}
		
	std::cout << data[size - 1] << std::endl;

	return true;
}

int main()
{
	srand(100);
	int errors = 0;	
	int total = 0;
	
	for (int i = 1; i < 100; i *= 2, ++total )
	{
		bool bOK = (total % 2) ? test<int>(i, 200) : test<float>(i, 200, 0.1f);
		if (!bOK)
		{
			++errors;
			std::cout << "failed on test with array size: " << i << std::endl;
		}
			
	}
	std::cout << "total number of test :" << total << std::endl;
	std::cout << "errors :" << errors << std::endl;

	system("pause");
	return 0;
}