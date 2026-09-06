#include <iostream>
#include <queue>

using namespace std;

// Given two binary max heaps as arrays , merge the given heaps to form a new max heap.

// Input : h1 = [10,5,6,2] , h2 = [12,7,9]
// Output : [12,10,9,2,5,7,6]

// 1) We use a priority queue and push those 2 vectors.
// Then we use an answer vector and get those values from heap to ans.
// Time : O((m+n)log(m+n))
// Space : O(m+n)
vector<int> maxHeap(vector<int> &h1, vector<int> &h2)
{
    priority_queue<int> pq;
    for (int i = 0; i < h1.size(); i++)
    {
        pq.push(h1[i]);
    }
    for (int i = 0; i < h2.size(); i++)
    {
        pq.push(h2[i]);
    }
    vector<int> ans;
    while (!pq.empty())
    {
        ans.push_back(pq.top());
        pq.pop();
    }
    return ans;
}

// 2) We put all the values of 2 vectors into a single vector.
// Then we use Heapify on all indexes from ans.size()/2 - 1 to 0.
// This makes heap in (m+n) time.
// Time : O(m+n)
// Space : O(m+n)
void Heapify(vector<int> &arr, int index);
vector<int> maxHeap2(vector<int> &h1, vector<int> &h2)
{
    vector<int> ans;
    for (int i = 0; i < h1.size(); i++)
    {
        ans.push_back(h1[i]);
    }
    for (int i = 0; i < h2.size(); i++)
    {
        ans.push_back(h2[i]);
    }

    for (int i = (ans.size() / 2) - 1; i >= 0; i--)
    {
        Heapify(ans, i);
    }
    return ans;
}

void Heapify(vector<int> &arr, int index)
{
    while (1)
    {
        int left = 2 * index + 1;  // Relation Can be seen easily by making some nodes
        int right = 2 * index + 2; // Relation Can be seen easily by making some nodes
        int largest = index;

        // Check if Parent > its both Child or not ?
        if (left < arr.size() && arr[left] > arr[largest])
        {
            largest = left;
        }
        if (right < arr.size()) // Here if we had put both conditions then maybe some old compilers will crash on this data : [10,40] as right is 2 so accessing arr[right] is Segmentation Fault.
        {
            if (arr[right] > arr[largest]) // Although C/C++ use short circuit evaluation still we put a nested if condition for safety
            {
                largest = right;
            }
        }
        if (largest != index)
        {
            swap(arr[index], arr[largest]);
            // Checking that Child Node Again if it were a Parent Node.
            index = largest;
        }
        else
        {
            break;
        }
    }
}
int main()
{
    vector<int> h1 = {10, 5, 6, 2}, h2 = {12, 7, 9};
    vector<int> ans = maxHeap2(h1, h2);
    for (int i : ans)
    {
        cout << i << " ";
    }
    return 0;
}