#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Helper Function
void Heapify(vector<int>&v , int index)
{
    while (true)
    {
        int left = 2 * index + 1;  // Relation Can be seen easily by making some nodes
        int right = 2 * index + 2; // Relation Can be seen easily by making some nodes
        int largest = index;

        // Check if Parent > its both Child or not ?
        if (left < v.size() && v[left] > v[largest])
        {
            largest = left;
        }
        if (right < v.size()) // Here if we had put both conditions then maybe some old compilers will crash on this data : [10,40] as right is 2 so accessing v[right] is Segmentation Fault.
        {
            if (v[right] > v[largest]) // Although C/C++ use short circuit evaluation still we put a nested if condition for safety
            {
                largest = right;
            }
        }
        if (largest != index)
        {
            swap(v[index], v[largest]);
            // Checking that Child Node Again if it were a Parent Node.
            index = largest;
        }
        else
        {
            break;
        }
    }
}

// Time Complexity : O(v1.size() + v2.size() )
vector<int> MergeHeaps(vector<int> &v1, vector<int> &v2)
{
    for (int i = 0; i < v2.size(); i++)
    {
        v1.push_back(v2[i]);
    }
    for(int i = v1.size()/2-1 ; i>=0 ; i--)
    {
        Heapify(v1,i);
    }
    return v1;
}

int main()
{
    vector<int> v1 = {10, 5, 6, 2};
    vector<int> v2 = {12, 7, 9};

    v1 = MergeHeaps(v1, v2);
    for (int num : v1)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}