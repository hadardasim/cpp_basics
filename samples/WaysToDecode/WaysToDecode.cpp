#include <vector>
#include <string>

using namespace std;

int numDecodings(string A) {
	if (A.size() == 0 || A[0] == '0')
		return 0;
	if (A.size() <= 1)
		return 1;


	std::vector<long long> combos(A.size() + 1, 0);
	combos.back() = 1;
	combos[combos.size() - 2] = 1;


	for (int i = A.size() - 2; i >= 0; --i)
	{
		if (A[i + 1] == '0' && !(A[i] == '1' || A[i] == '2'))
			return 0;
		bool sum = false;
		if (i + 2 < A.size() && A[i + 2] == '0')
			sum = false;
		else if (A[i] > '2' || A[i + 1] == '0' || A[i] == '0')
			sum = false;
		else if (A[i] == '2')
		{
			sum = (A[i + 1] <= '6');
		}
		else if (A[i] == '1')
		{
			sum = true;
		}
		else
			sum = false;


		if (sum)
			combos[i] = combos[i + 1] + combos[i + 2];
		else
			combos[i] = combos[i + 1];
	}
	return combos.front();
}

int main()
{
	numDecodings("12032111011");
	return 0;
}