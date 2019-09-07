#include "CyclicBuffer.inl"
#include <iostream>
#include "MTWrite.h"

int main()
{
	CyclicBuffer<int> cyclicInt(5);
	cyclicInt.push_back(1);
	assert(cyclicInt.get_data(0) == 1);
	for (int i = 1; i < 10; ++i)
		cyclicInt.push_back(i + 1);	
	
	for (int i = 0; i < cyclicInt.get_size(); ++i)	
		std::cout << cyclicInt.get_data(i) << std::endl;	

	assert(cyclicInt.get_data(cyclicInt.get_size() - 1) == 10);

	MTWrite::test(8);

	return 0;
}