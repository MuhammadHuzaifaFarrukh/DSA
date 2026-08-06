#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &arr, int start, int end); // Forward Declaration

// Quick Sort :
// We can select any random element as our pivot.
// Here we take it as the last element , we can select any element as pivot (starting or middle also).
// We place pivot at its correct position.
// Then we place all elements to its left as less than pivot and all elements to its right as greater than pivot.
// Once we do this , we have correctly placed our pivot in the correct position.
// Now we do this for the left and right parts of array , where left and right are the parts around our pivot because pivot is in corrected position.
// We call for (start,pivot-1) and (pivot+1,end).
// We keep doing this until we reach at single element or empty array , and return because they are already sorted or in their correct place.
// Top-Down Approach

// Time in Avg Case : O(nlogn) , Space in Avg Case : O(logn)
// Time in Worst case : O(n^2) , Space in Worst Case : O(n)
void quickSort(vector<int> &arr, int start, int end)
{
    if (start >= end)
    {
        return; // Go back incase of only single element or empty array (start > end) as they are already sorted.
    }
    int pivot = partition(arr, start, end);
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

// Helper function that places our pivot element at correct position and places all elements less than pivot to its left and all elements greater than pivot to its right.
// Time : O(n) where n is the size of our partition (start to end).
int partition(vector<int> &arr, int start, int end)
{
    // We could have done this by making an extra array and placing all less elements , pivot and greater than pivot elements in it and then we copy them back in our original array.
    // However that would have increased our space complexity to O(n) for all cases.

    // To make starting element as pivot , we can just :
    // swap(arr[start],arr[end]);

    // To make middle element as pivot :
    // int mid = start + (end - start) / 2;
    // swap(arr[mid], arr[end]);

    // We can also select pivot as a random indexed element so that it is independent of runtime.

    int pos = start;
    while (start <= end)
    {
        if (arr[start] <= arr[end])
        {
            swap(arr[start], arr[pos]);
            pos++;
        }
        start++;
    }
    return (pos - 1);
}

int main()
{
    vector<int> v = {6, 4, 2, 8, 13, 7, 11, 9, 3, 6};
    quickSort(v, 0, v.size() - 1);
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

/*
Pivot is written as (Pivot) and for none (-1)

                6, 4, 2, 8, 13, 7, 11, 9, 3, 6  (6)

                After being in corrected place :
                6, 4, 2, 3, 6, 8, 13, 7, 11, 9
                6,4,2,3 (3)       8,13,7,11,9   (9)   -> 2 Parts
                2,3,6,4           8,7,9,13,11
                2(-1)  6,4(4)     8,7(7)  13,11 (11)    -> 4 Parts
                2      4,6        7,8       11,13
                2    4(-1) 6(-1)  7(-1)  8(-1)   11(-1)  13(-1)
                2    4     6      7      8       11      13
*/

// For pivots choosen start,mid,end :

// Time for Avg Case :
// Total levels : logn because each time after finding pivot , array on average is being divided into 2 halves leaving pivot.
// Work done in each level : Can go upto 'n' because partition function places pivot at correct position for first level 1 time , for 2nd level 2 times , for 3rd level 4 times and so on.
// So if we see for n array , it does upto n time work , for 2 n/2 arrays , it works 2 times and total work is still in time 'n'.
// So work done in each level = n
// Multiply them : nlogn = O(nlogn)
// Recurrence Relation : T(n) = 2T(n/2) + cn which simplifies to O(nlogn)

// Space Complexity in Avg Case :
// Because we didn't use any extra array in partition , all the functions use constant space.
// The stack can grow upto maximum of logn levels.
// So Space Comp : O(logn)

// Time for Worst Case :
// For worst case like array being in ascending (already sorted) or descending (already sorted in reverse) can go upto n^2.
// Because it has to check n times for 1st level , n-1 times for 2nd level , n-2 times for 3rd level.
// Total levels = n and work done in each level decreases so we can find total time :
// n + (n-1) + (n-2) +...+ 1 = O(n^2)
// Recurrence Relation : T(n) = T(n-1) + 1 + cn which simplifies to O(n^2)

// Space Complexity in Worst Case :
// The stack grows upto n levels so space complexity becomes O(n)

// ====================================================================================================================================================================================

// For pivots choosen as rand() :
// If we choose our  pivot completely at random using rand(), there is still a mathematical possibility that the random number generator will choose the worst possible pivot (the absolute minimum or maximum element) at every single step of the recursion.
// However, the probability of this happening on an array of size n is roughly: (2/n)^n.
// For an array of just 100 elements, this probability is so phenomenally small that it is virtually guaranteed to never happen in the history of the universe.
// So theoretical worst-case of randomized Quick Sort is still O(n^2), in the real world, it is O(nlogn).

// =====================================================================================================================================================================================

// It is still possible to guarantee the time complexity of quicksort in nlogn and space as logn.
// That happens using algorithm of Median of Medians (BFPRT).
// Because if pivot selected is closer to the median of array then it perfectly divides the array.
// By choosing 5 elements and taking median of those elements will guarantee us that :
// This guarantees that no matter how chaotic or malicious the input array is, our partition split will never be worse than 30:70.
// So Time : O(nlogn) , Space : O(logn)

// Implementation :
/*
// Forward declarations
int partition(vector<int> &arr, int start, int end, int pivotValue);
int getMedianOfMedians(vector<int> &arr, int start, int end);

void quickSort(vector<int> &arr, int start, int end)
{
    if (start >= end)
    {
        return;
    }

    // Step 1: Find the guaranteed good pivot value using Median of Medians
    int pivotValue = getMedianOfMedians(arr, start, end);

    // Step 2: Partition the array around this pivot value
    int pivotIdx = partition(arr, start, end, pivotValue);

    // Step 3: Recurse
    quickSort(arr, start, pivotIdx - 1);
    quickSort(arr, pivotIdx + 1, end);
}

// Helper to find the Median of Medians (BFPRT)
int getMedianOfMedians(vector<int> &arr, int start, int end)
{
    int n = end - start + 1;
    if (n <= 5)
    {
        // Base Case: If 5 or fewer elements, sort directly and return the median
        sort(arr.begin() + start, arr.begin() + end + 1);
        return arr[start + n / 2];
    }

    // Step 1 & 2: Group into blocks of 5, sort them, and move medians to the front
    vector<int> medians;
    for (int i = start; i <= end; i += 5)
    {
        int subEnd = min(i + 4, end);
        sort(arr.begin() + i, arr.begin() + subEnd + 1);

        // Find median of this group of 5
        int mid = i + (subEnd - i) / 2;
        medians.push_back(arr[mid]);
    }

    // Step 3: Recursively find the median of the medians
    return getMedianOfMedians(medians, 0, medians.size() - 1);
}

int partition(vector<int> &arr, int start, int end, int pivotValue)
{
    // Find where the pivotValue is in our subarray and swap it to the end
    for (int i = start; i <= end; i++)
    {
        if (arr[i] == pivotValue)
        {
            swap(arr[i], arr[end]);
            break;
        }
    }

    int pos = start;
    while (start <= end)
    {
        if (arr[start] <= arr[end])
        {
            swap(arr[start], arr[pos]);
            pos++;
        }
        start++;
    }
    return (pos - 1);
}
*/

// Why this works ?
/*
If we take median of this array into groups of 5 and group those medians also :
Array : {12, 3, 18, 14, 7, 2, 19, 1, 8, 15, 6, 13, 9, 11, 5}
// Sort each group of 5 and find the middle as median.
Medians : {12,8,9}
Find the Median of this as well :
Median becomes 9
// So we see elements less than 9 and more than 9 :
// [3, 7, 2, 1, 8, 6, 5] , 9 , [12, 18, 14, 19, 15, 13, 11]
// This gives us a perfect split.

Even in the absolute worst-case scenario, this grouping method mathematically guarantees that the pivot will never be worse than a 30:70 split. It prevents the algorithm from ever choosing an extreme value (like 1 or 19 in this array) as the pivot, completely eliminating the O(n^2)
*/

// Why choose 5 instead of 7 or 3 :
/*
Although Medians of 3 elements in each group also works impressively :
Because of this, production-grade engines (like C++'s std::sort) use a hybrid algorithm called IntroSort (Introspective Sort):
It starts running Quick Sort with a fast pivot selection (like Median-of-Three).
It tracks the recursion depth.
If the recursion depth exceeds 2logn (meaning Quick Sort is starting to degrade into its worst-case O(n^2) behavior), the algorithm automatically switches to Heap Sort.

In many libraries, a simpler "median" approach is used, such as Median-of-Three (where you look at the first, middle, and last elements, and choose the median of those three as the pivot).
While this completely destroys the O(n^2) worst case for already-sorted or reverse-sorted arrays, it does not save you from a true worst case.
An adversary who knows your "Median-of-Three" code is running can purposefully design a specific, scrambled input sequence (often called a "Killer Adversary" sequence) that forces your median-of-three selection to choose a terrible pivot at every level.
*/

/*
If Merge Sort is guaranteed O(nlogn) time and Heap Sort is guaranteed O(nlogn) time and uses O(1) space, why does the entire software industry still rely so heavily on Quick Sort?
In the real world, Quick Sort is almost always significantly faster than both Merge Sort and Heap Sort due to three major factors:

1) Modern computers don't read data from your RAM one single number at a time.
Instead, they load a contiguous chunk of memory into a super-fast, ultra-close storage area on the processor called the CPU Cache (L1/L2/L3 cache).
Quick Sort has incredible cache locality: It steps through the array sequentially from left to right using pointers (start++, pos++).
This means almost every element it accesses is already loaded into the CPU cache, resulting in incredibly fast "cache hits.
"Heap Sort has terrible cache locality: To maintain the heap, Heap Sort constantly jumps across wildly different indexes (from index i to 2i and 2i+1. This forces the CPU to constantly clear its cache and fetch data from the much slower main RAM ("cache misses").
Merge Sort has decent locality, but it constantly has to allocate new temporary arrays and copy data back and forth between them, creating a massive amount of memory traffic that slows it down.

2) Quick Sort's inner loop is incredibly simple.
It does a quick comparison and a swap.
Its constant factor c is extremely small.
Merge Sort's inner loop is much more complex.
It has to handle bounds checking for two subarrays, copy elements to a temporary array, and then copy them back to the original array.
Its constant c is much larger.
Heap Sort's inner loop requires several mathematical index calculations and constant tree restructurings (sifting down), making its constant c larger as well.

3) While Merge Sort has a guaranteed time complexity, its O(n) auxiliary space complexity is a massive dealbreaker in production.
If you are sorting a database or a file that is 10 Gigabytes in size: Merge Sort requires you to allocate another 10 Gigabytes of RAM just to perform the sort.
If the system runs out of memory, it crashes.
Quick Sort (using the smaller-subarray-first trick) only needs O(logn) space.
For a 10 GB array, the call stack space is so microscopic (less than a few kilobytes) that it is virtually free.

*/

// Failure of Guaranteed O(nlogn) QuickSort.
/*
// However if there are huge numbers then finding median of medians can get even messier and even more slow than it was intended to be.
// If 'd' is the super super big digits present in our array then our time becomes : ndlogn.
// That's why std::sort() does this for it :
Because Median of Medians is too slow, C++'s std::sort uses much faster, cheaper pivot-selection strategies:
For small arrays (e.g., n <= 16):
It doesn't even use Quick Sort! It switches to Insertion Sort, which is incredibly fast for tiny datasets because it has almost zero overhead.
For medium arrays:
It picks the pivot using Median-of-Three (comparing the first, middle, and last elements). This takes O(1) time—essentially instant. Overall complexity time : O(nlogn)
For very large arrays: It uses Tukey’s Ninther (which is a "median of three medians of three").
It sounds complex, but it only looks at 9 specific elements in the array and takes $O(1)$ constant time to find a highly reliable pivot.
If these fast, cheap O(1) pivot choices occasionally fail on a weirdly designed dataset, IntroSort's safety net (the switch to Heap Sort) catches it.

*/