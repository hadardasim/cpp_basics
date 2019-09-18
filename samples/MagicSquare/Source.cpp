#include <array>
#include <vector>
#include <iostream>

using namespace std;
typedef array<int, 9> Mat3x3;
vector<Mat3x3> magicSquares;

void rec_square_create(int added, Mat3x3& data)
{
	if (added && (added % 3 == 0))
	{
		// check the last row        
		int row_sum = data[added - 3] + data[added - 2] + data[added - 1];
		if (row_sum != 15)
			return;
	}
	if (added >= 9)
	{
		// check columns
		for (int i = 0; i < 3; ++i)
		{
			int col_sum = data[i] + data[i + 3] + data[i + 6];
			if (col_sum != 15)
				return;
		}
		int d1 = data[0] + data[4] + data[8];
		if (d1 != 15)
			return;
		int d2 = data[2] + data[4] + data[6];
		if (d2 != 15)
			return;
		magicSquares.push_back(data);
		return;
	}
	for (int i = 1; i < 10; ++i)
	{
		bool bFound = false;
		for (int j = 0; !bFound && j < added; ++j)
		{
			if (data[j] == i)
				bFound = true;
		}
		if (bFound)
			continue;
		data[added] = i;
		rec_square_create(added + 1, data);
	}
}

void createAllSqaures()
{
	Mat3x3 cur;
	rec_square_create(0, cur);
}

int abs_diff(const Mat3x3& s1, const Mat3x3& s2)
{
	int sum = 0;
	for (int i = 0; i < 9; ++i)
		sum += abs(s1[i] - s2[i]);
	return sum;
}

// Complete the formingMagicSquare function below.
int formingMagicSquare(const Mat3x3& s) {

	int min_diff = 100;
	for (const Mat3x3& ms : magicSquares)
	{
		int diff = abs_diff(s, ms);
		min_diff = min(diff, min_diff);
	}
	return min_diff;
}

int main()
{
	//ofstream fout(getenv("OUTPUT_PATH"));

	createAllSqaures();

	Mat3x3 s;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> s[i * 3 + j];
		}
		
	}	

	int result = formingMagicSquare(s);

	cout << result << "\n";
	

	return 0;
}
