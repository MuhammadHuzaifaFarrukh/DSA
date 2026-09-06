#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
*/

// 1) Using Vector/Deque/List which gives TLE since we need to sort() the elements for finding the median inside either push function or the finding median function.
// Using sort() in addNum will make Time : 1log1 + 2log2 + 3log3 +...+ nlogn = n^2logn. if it is called n times where n can go upto 5*10^4 times (as in constraints of LC).
// If we use sort() in findmedian() , then mnlogn where m is the no of times we call the median function or if m = n then n^2logn.
// Time for any function that uses sort() : O(nlogn) or O(n^2logn) for 'n' elements
// Time for addNum() without sort() : O(1) Avg or O(n) at worst (due to reallocation and copying ). and for 'n' elements it will be O(n) Avg or O(n^2).
// Time for medianfinder without sort() : O(1) or O(n) for 'n' elements
// Space : O(n)
// class MedianFinder
// {
//     vector<int> v;

// public:
//     MedianFinder()
//     {
//     }

//     void addNum(int num)
//     {
//         v.push_back(num);
//         sort(v.begin(), v.end());
//     }

//     double findMedian()
//     {
//         if (v.size() % 2 == 1)
//         {
//             return (double)v[v.size() / 2];
//         }
//         else
//         {
//             return (double)(v[v.size() / 2] + v[v.size() / 2 - 1]) / 2.0;
//         }
//         return 0.0;
//     }
// };

// 1) Brute Force.
// For each element coming , we put it at its right place by shifting that could take O(n) time for only 1 element.
// It would take O(n^2) time for all elements to shift.
// addNum() time for 1 element in worst : O(n)
// addNum() space for 1 element in worst : O(1)
// addNum() for 'n' elements will take time : O(n^2)
// addNum() for 'n' elements will take space : O(n)
// findMedian() takes O(1) time for 1 element and O(n) time for 'n' elements.
// findMedian() takes O(1) space for 1 element and O(1) space for 'n' elements.
class MedianFinder
{
    vector<int> nums;

public:
    MedianFinder()
    {
    }
    void addNum(int num)
    {
        if (nums.empty())
        {
            nums.push_back(num);
            return;
        }
        // Shifting :
        nums.push_back(num);
        for (int i = nums.size() - 1; i >= 1; i--)
        {
            if (nums[i - 1] > nums[i])
            {
                swap(nums[i - 1], nums[i]);
            }
        }
    }

    double findMedian() // Now works in O(1)
    {
        if (nums.size() % 2 == 1)
        {
            return nums[nums.size() / 2];
        }
        int x1 = nums[nums.size() / 2];
        int x2 = nums[nums.size() / 2 + 1];
        return (x1 + x2) / 2.0;
    }
};

// 2) Using 2 Priority Queues.
// We know that median in case of even number list is the half of the sum of the two middle values and it is the middle value incase of odd number list.
// E.g : [1,2,3,4,5,6,7,8] , the median is 4+5 = 9 /2 = 4.5.
// So we can clearly see : [1,2,3,4] and [5,6,7,8] , these look like the structures of min-heap and max-heaps.
// So we can say that our left half will be max heap and right half will be min heap.
// When both are empty , we give preference to our left half , max heap.
// Then if this max heap is not empty and another element comes in the stream , we check if it is greater than the maximum value of the max heap , if yes then it goes to the right half , otherwise it will go to left half max heap.
// Now once we've placed elements in our any of the heaps , we check for the sizes.
// If the max heap size is equal to min heap , its valid like the saw the case above.
// If max heap size is just +1 than min heap its still fine because : [1,2,3,4,5,6,7,8,9] , here max heap is [1,2,3,4,5] and min heap is [6,7,8,9] , so we can easily return the top of max heap as the median.
// Other than these cases , like max heap size is more than +1 than min heap , we have to give min heap an element from the max heap.
// Similarly , if min heap size somehow gets +1 than max heap , then we have to give max heap an element from the min heap.
// So Valid Size Cases : Maxheap Size == Minheap Size and Maxheap  == Minheap + 1.
// Unvalid Cases that we have to correct (if occurred) : Maxheap Size > Minheap + 1 and Minheap Size > Max heap.

// We have designed it so that for odd number of data items , our max heap contains more elements than min-heap.
// For even number of data items , number of elements are same.
// So we've also put a check while we add any number inside them.
// MaxHeap.Size() - MinHeap.Size() must be 0 or 1 otherwise we will have to maintain the size by adding 1 largest element from max heap into min heap.
// MinHeap.Size() - MaxHeap.Size() must be 0 (which means that MinHeap size cannot exceed MaxHeap) otherwise we will have to maintain the size by adding 1 smallest element of MinHeap into MaxHeap.
// This ensures that MinHeap Size can never exceed MaxHeap and if it does , then we will maintain the size so that their difference is either 0 or 1.
// Our entire median finding function relies on this property that's why we check on each step of addition of new elements.
// If the difference of min and max heap is 0 , then it means their sizes are same , and elements are of even length so we return the median by taking the (smallest + highest) / 2 , else we take the highest of the max heap if difference is of 1 (odd-length).

// Complexities :
// 1) addNum() Time : O(logn) for 1 element or O(nlogn) for 'n' elements.
// addNum() Space : O(1) for 1 element or O(n) for 'n' elements.

// 2) Median Finder Time : O(1) for 1 element or O(n) for 'n' elements.
// Space : O(1) in each case.
// Overall Space : O(n) for the whole class.
class MedianFinder2
{
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    MedianFinder2()
    {
    }

    // We divide the 50% elements left side and 50% elements to right side.
    // Max-Heap holds the 50% of the elements (small ones) and in case of odd length of data stream , this will hold one more.
    // Min-Heap holds the 50% of the other elements (large ones).
    // For Finding the median in odd length , we can just return the max heap top [1,3 | 8] , Max-Heap can have elements one more than min-heap by default at most.
    // For Finding the median in even length , we can just return the top of the min and max heaps / 2. [1 , 3 | 7 , 8] -> (3+7)/2.
    // Because the max-heap top holds the largest element (out of smaller elements than min-heap) that is one of the middle elements of the whole data stream.
    // On the other hand , min-heap holds the smallest elements (out of larger elements than max-heap) that is one of the middle elements of the array.
    // This means that max-heap's largest is even smaller than min-heap's smallest.
    // And min-heap's smallest is even larger than the max-heap's largest.
    void addNum(int num)
    {
        if (maxHeap.empty() || num <= maxHeap.top())
        {
            maxHeap.push(num);
        }
        else
        {
            minHeap.push(num);
        }

        // 2 Unvalid Cases :
        // Maxheap size is more than +1 than min heap
        if ((int)maxHeap.size() > (int)minHeap.size() + 1)
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } // Minheap size is more than MaxHeap.
        else if ((int)minHeap.size() > (int)maxHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() // Now works in O(1)
    {
        // 2 Valid Cases Here :
        // Elements are equal in both so median is (maxheap.top()+minheap.top())/2
        if (maxHeap.size() == minHeap.size()) // Difference of elements is 0.
        {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }

        // Maxheap Size is just +1 than Minheap.
        return (maxHeap.top()); // Difference of elements is 1.
    }
};

int main()
{
    return 0;
}