// https://mail.google.com/mail/u/1/#inbox/KtbxLvhVgqvVWFQtcxFnGLnhQpmcbCdgLV
#include <vector>
#include <iostream>
#include <cstdint>
#include <map>

struct Person
{
	int birth;
	int death;
};

int main()
{
	// read the data
	size_t num_people;
	std::cin >> num_people;
	std::map<int, int> yearDelta;
	
	int birth, death;
	for (size_t p=0; p<num_people; ++p)
	{
		std::cin >> birth >> death;
		auto it = yearDelta.find(death);
		if (it == yearDelta.end())
			yearDelta[death] = -1;
		else
			yearDelta[death] -= 1;

		it = yearDelta.find(birth);
		if (it == yearDelta.end())
			yearDelta[birth] = 1;
		else
			yearDelta[birth]++;
	}

	// count the number of people in each segment
	int max_people = 0;
	int year_of_max = 0;
	int cur_count = 0;
	for (auto it : yearDelta)
	{
		cur_count += it.second;
		if (cur_count > max_people)
		{
			max_people = cur_count;
			year_of_max = it.first;
		}
	}

	std::cout << "year: " << year_of_max << " count" << max_people << std::endl;			

	return 0;
}