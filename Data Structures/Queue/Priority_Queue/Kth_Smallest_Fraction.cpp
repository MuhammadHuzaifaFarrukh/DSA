#include <iostream>
#include <queue>
#include <deque>
#include <limits.h>
#include <Heap.hpp>
using namespace std;

// One Approach to do this is without structs, using the nested loop and checking all the pairs and keeping inside the min heap
// Then finding kth largest element and getting that value and again matching that value with the pairs and finding those elements that made up that value (arr[i]/arr[j]).
// This maybe a brute force approach as the array is already sorted and we can do it still in less than O(n^2) in the next approach.

/*

int main()
{
    int n;
    cout << "Enter size of array : ";
    cin >> n;
    float *arr = new float[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter element [" << i << "] : ";
        cin >> arr[i];
    }

    int k;
    cout << "Enter k : ";
    cin >> k;

    float res[2] = {};
    priority_queue<float, vector<float>, greater<float>> pq;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            pq.push((float)arr[i] / arr[j]);
        }
    }

    int it = 1;
    float small = pq.top();
    while (!pq.empty())
    {
        if (it == k)
        {
            small = pq.top();
            break;
        }
        pq.pop();
        it++;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            float ans = arr[i] / arr[j];
            if ((double)small == ans)
            {

                res[0] = arr[i];
                res[1] = arr[j];
            }
        }
    }

    cout << "Smallest No : " << small << endl;
    cout << "Numerator : " << res[0] << endl;
    cout << "Denominator : " << res[1] << endl;

    return 0;
}
*/

// The Other one is an efficient way , to solve using struct.
// Also we know that array is sorted so the value is made smallest by having largest denominator_idx and only changing numerator_idxs from from 0 to n-2.
// This works in O((N+K)Log N)
struct Fraction
{
    double val;
    int numerator_idx;
    int denominator_idx;

    // Greater than operator for Min-Heap
    // Needed (either functor or this operator overload)
    bool operator>(const Fraction &other) const
    {
        return val > other.val;
    }
};

int main()
{
    int n, k;

    cout << "Enter size: ";
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter k: ";
    cin >> k;

    priority_queue<Fraction, vector<Fraction>, greater<Fraction>> pq;

    // Initial fractions: arr[i]/arr[n-1] where i goes 0 to n-2.
    for (int i = 0; i < n - 1; i++)
    {
        pq.push({(double)arr[i] / arr[n - 1], i, n - 1});
    }

    // Pop k-1 times to reach the kth smallest
    for (int it = 1; it < k; it++)
    {
        Fraction top = pq.top();
        pq.pop();
        if (top.denominator_idx - 1 > top.numerator_idx)
        {
            pq.push({(double)arr[top.numerator_idx] / arr[top.denominator_idx - 1], top.numerator_idx, top.denominator_idx - 1});
        }
    }

    int answer[2];
    answer[0] = arr[pq.top().numerator_idx];
    answer[1] = arr[pq.top().denominator_idx];

    cout<<"Smallest value : "<<endl;
    cout<<"Numerator : "<<endl;
    cout<<"Denominator : "<<endl;
    return 0;
}

// Explanation of the two loops :
/*
The First Loop: 
Setting the Starting Line
We don't know which numerator will give us the smallest overall fraction, so we take the "best version" of each one and put them in the heap.
We push 1/5, 2/5, and 3/5.
Why? Because 1/5 is the smallest fraction "Team 1" can produce. 
2/5 is the smallest "Team 2" can produce, and so on.
The Min-Heap now looks at these three "team captains" and puts the absolute smallest (1/5) at the top.


The Second Loop: 
Running the Race (k-1 times)
This loop is there to explore the next possibilities. 
Every time you pop the smallest fraction, you have to replace it with the "next best" one from that same team.
Pop 1/5: The heap says, "Okay, 1/5 is the 1st smallest.
"The Discovery: Now that 1/5 is gone, what is the next smallest fraction that uses 1 as a numerator? It’s 1/3.
Push 1/3: We put 1/3 into the heap. Now the heap compares the new 1/3 against the captains that were already there (2/5 and 3/5).
Repeat: The heap now sees that 1/3 (0.3) is smaller than 2/5 (0.4), so 1/3 moves to the top.
*/

/*
The 1st Loop gives you the smallest fraction for every numerator.
The 2nd Loop allows you to "step inward" and check the 2nd, 3rd, or 4th smallest fractions for those numerators until you've popped enough elements to reach the k-th one.

*/