// Returns sum of arr[0..index]. This function assumes 
// that the array is preprocessed and partial sums of 
// array elements are stored in BITree[]. 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;
template <typename T>
class CBITree
{
public:
	// Constructs and returns a Binary Indexed Tree for given 
	// array of size n. 
	CBITree(const std::vector<T>& arr)
	{
		int n = arr.size();
		// Create and initialize BITree[] as 0 
		BITree.resize(n + 1);
		for (int i = 1; i <= n; i++)
			BITree[i] = 0;

		// Store the actual values in BITree[] using update() 
		for (int i = 0; i < n; i++)
			updateBIT(i, arr[i]);

		// Uncomment below lines to see contents of BITree[] 
		//for (int i=1; i<=n; i++) 
		//     cout << BITree[i] << " "; 
		
	}

	T getSum(int index) const
	{
		T sum = 0; // Iniialize result 

		// index in BITree[] is 1 more than the index in arr[] 
		index = index + 1;

		// Traverse ancestors of BITree[index] 
		while (index > 0)
		{
			// Add current element of BITree to sum 
			sum += BITree[index];

			// Move index to parent node in getSum View 
			index -= index & (-index);
		}
		return sum;
	}

	// Updates a node in Binary Index Tree (BITree) at given index 
	// in BITree. The given value 'val' is added to BITree[i] and  
	// all of its ancestors in tree. 
	void updateBIT(int index, T val)
	{
		const int n = BITree.size() - 1;
		// index in BITree[] is 1 more than the index in arr[] 
		index = index + 1;

		// Traverse all ancestors and add 'val' 
		while (index <= n)
		{
			// Add 'val' to current node of BI Tree 
			BITree[index] += val;

			// Update index to that of parent in update View 
			index += index & (-index);
		}
	}
private:
	std::vector<T> BITree;
};

// Complete the insertionSort function below.
long long insertionSort(vector<int> arr)
{
	vector<int> sorted(arr);
	std::sort(sorted.begin(), sorted.end());
	
	long long shifts = 0;

	std::unordered_map<int, int> mapItemToIndex;
	auto prev = sorted[0];
	mapItemToIndex[prev] = mapItemToIndex.size();
	for (int pos = 1; pos < sorted.size(); ++pos)
	{
		auto val = sorted[pos];
		if (val != prev)
		{
			mapItemToIndex[val] = mapItemToIndex.size();
			prev = val;
		}
	}

	std::vector<long long> distinct(mapItemToIndex.size(), 0);	
	CBITree<long long> bit(distinct);

	for (int step = 0; step < arr.size(); ++step)
	{
		// find the number of elements greater than the current num
		int pos = mapItemToIndex[arr[step]];
		long long greater = bit.getSum(distinct.size()-1) - bit.getSum(pos);
		shifts += greater;
		bit.updateBIT(pos, 1);
	}

	return shifts;
}

int main()
{
	/*
	std::vector<int> test1 = { 4,3,2,1 };
	cout << insertionSort(test1) << endl;
	std::vector<int> test2 = { 2, 1, 3, 1, 2 };
	cout << insertionSort(test2) << endl;
	*/
	int cases;
	cin >> cases;
	for (int c = 0; c < cases; ++c)
	{
		int n;
		cin >> n;
		std::vector<int> arr(n);
		for (int& item : arr)
			cin >> item;
		cout << insertionSort(arr) << endl;
	}

	return 0;
}





