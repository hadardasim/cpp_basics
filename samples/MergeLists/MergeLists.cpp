#include <vector>
#include <algorithm>
using namespace std;
/**
 * Definition for singly-linked list.
 */
 struct ListNode {
 int val;
 ListNode *next;
 ListNode(int x) : val(x), next(nullptr) {}
 };
 
ListNode* mergeKLists(vector<ListNode*> &A) {
	// Do not write main() function.
	// Do not read input, instead use the arguments to the function.
	// Do not print the output, instead return values as specified
	// Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
	if (A.size() == 0)
		return nullptr;
	vector<ListNode*> minHeap(A);
	auto comp = [](ListNode* a, ListNode* b) {return (a->val > b->val); };
	make_heap(minHeap.begin(), minHeap.end(), comp);
	ListNode* result = nullptr;
	ListNode* tail = nullptr;
	while (minHeap.size())
	{
		auto new_node = new ListNode(minHeap.front()->val);

		if (!result)
		{
			result = new_node;
		}
		else
		{
			tail->next = new_node;
		}
		tail = new_node;

		auto next = minHeap.front()->next;
		std::pop_heap(minHeap.begin(), minHeap.end(), comp);
		minHeap.pop_back();
		if (next)
		{
			minHeap.push_back(next);
			std::push_heap(minHeap.begin(), minHeap.end(), comp);
		}
	}

	return result;
}