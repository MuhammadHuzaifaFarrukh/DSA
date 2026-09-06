#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
Given a 2D matrix mat[][] of size k by m.
Each row in the matrix is sorted in non-decreasing order, merge all the rows and return a single sorted array that contains all the elements of the matrix.

Input: mat[][] = [[1, 3, 5, 7], [2, 4, 6, 8], [0, 9, 10, 11]]
Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
Explanation: Merging all elements from the 3 sorted arrays and sorting them results in: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

Input: mat[][] = [[1, 2, 3, 4], [2, 2, 3, 4], [5, 5, 6, 6], [7, 8, 9, 9]]
Output: [1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 9]
Explanation: Merging all elements from the 4 sorted arrays and sorting them results in:[1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 9]
*/

// 1a) Using merge sort :
// We can put all the values in a separate vector and then sort them all.
// Time : O(nlogn) (n = mk)
// Extra Space : O(n) (n = mk)
// Total Space : O(n) (n=mk)

// 1b) Similarly we could also use the method of merging k sorting arrays just like we did with merge k sorted lists by picking 2 consecutive lists and merging them , we can also do it like this instead of putting in a vector first. (Method 1b of the Merge K Sorted Lists.)
// Because we know that each row is sorted , we could use merging 2 sorted arrays on this as well and keep doing it until it becomes a single array.
// Time : O(mk^2) or O(nk)
// Extra Space : O(n)
// Total Space : O(n)
// Note that nlogn < nk.

// 2) Using Heap Sort :
// We can put all the values in a separate vector and then sort them all using heap sort.
// Time : O(nlogn) (n = mk)
// Extra Space : O(1)
// Total Space : O(n) (n=mk)

// 3) By using minheap :
// We keep pushing all the elements into the heap from matrix.
// Then we pop them out in the answer array.
// Time Complexity :
// Time to push/pop into heap : nlogn (n=mk)
// Total time : O(nlogn)

// Space Complexity :
// Extra Space : O(n) (n=mk)
// Total Space : O(n) (n=mk)
vector<int> mergeArrays(vector<vector<int>> &mat)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            pq.push(mat[i][j]);
        }
    }
    vector<int> ans;
    while (!pq.empty())
    {
        ans.push_back(pq.top());
        pq.pop();
    }
    return ans;
}

// 4) We use a min heap again with some optimization.
// We push only k elements in the matrix along with their rows and columns indexes so that when we pop , we can later get the next element (just like merging k sorted lists or k smallest pairs).
// Then we run a loop for (mk-k) elements , and just grab the minimum most element and add it to our answer.
// Then we check if this minimum element row has more elements or not by checking its column index.
// If yes then we push it otherwise we don't.
// Time Complexity :
// We push 'k' elements into heap : klogk.
// Then we pop/push (mk-k) elements : mklogk.
// Total Time : O(klogk + mklogk) or O(nlogk)
// Space Complexity :
// Extra Space : O(k)
// Total Space : O(n) where n = mk
vector<int> mergeArrays2(vector<vector<int>> &mat)
{
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    for (int i = 0; i < mat.size(); i++)
    {
        pq.push({mat[i][0], {i, 0}});
    }
    vector<int> ans;
    while (!pq.empty())
    {
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        pq.pop();
        ans.push_back(mat[i][j]);
        if (j + 1 < mat[i].size())
        {
            pq.push({mat[i][j + 1], {i, j + 1}});
        }
    }
    return ans;
}

// 5) We use merge sort again but with modifications.
// E.g we know that the arrays we are given are already sorted so we don't need to waste any time to sort them again.
// We put all elements in a vector for our ans.
// We try to use the merge sort here just like we did for merge k sorted lists by using merge sort (Method 2) , but in that we had each portion as the vector<Node *> , so it was easy for us to get start /mid/end of portions by just simple indexing as usual.
// Here we have to do something else.
// We just keep dividing the arrays like we do in merge sort.
// E.g we have  {{3, 4, 5, 11}, {1, 6, 7, 14}, {4, 5, 8, 13}}, it has 3 sorted arrays.
// We don't need to divide it in the half , we need to make these portions only.
// We can have {3,4,5,11} , then {1,6,7,14} , {4,5,8,12} portions but not divide these portions any further like {3,4} , {5,11}.
// Then we simply use merge 2 sorted arrays on each one by one and get our answer.
// When we are at complete 2d array , we convert it to 1d array.
// Then we make those portions by simply dividing into left and right halves as : [3,4,5,11] and [1,6,7,14,4,5,8,12].
// We simply found the mid to divide for these portions.
// We do that by (rows)/2*Cols , add start in it and then -1 in it. (Can be derived by seeing matrices of rows==cols)
// Rows/2 give number of the portion ( on left side) and (rows/2)*cols give total elements in that portion and we see this left half goes from start to the number of elements it has ,  by adding start in it and setting it 0-based index by subtracting 1 from it.
// So we see how many portions are going to be on left side and see those elements number as multiplying by cols and then sub 1 due to 0-indexed and add start which is the starting of the chunk so that for further elements we can divide it easily as well.
// Here this gives us index 3 , so we divide array left to 0-3 and right as 4-11 , we can see that left has only 1 portion , portions are being divided at each step.
// In case of even number of rows , both sides get equal portions as we do portions/2 , but in case of even , one side gets less (truncation), so we give other side as portion-portion/2 otherwise here both sides would get 1 1 portion each side whereas there are 2 portions on right side.
// Now when we are just left with a single portion , we return.
// Like we divided into : [3,4,5,11] and [1,6,7,14,4,5,8,12] , so [3,4,5,11] is a single portion already sorted , we don't need to part it anymore.
// Then we have [1,6,7,14,4,5,8,12] which gets parted into two portions , as [1,6,7,14] and [4,5,8,12] with 4-7 left half and 8-11 as right half.
// Both are single portions so we get them back and then we join them into a single sorted portion as : [1,4,5,6,7,8,12,14].
// Then we get this sorted portion [1,4,5,6,7,8,12,14] along with previous portion [3,4,5,11] , are sorted into a single portion.
// That's how we get our answer.

// Time Complexity :
// We are using merge sort so it can go upto logk levels.
// Work done in each level is mk or n.
// Total Time : O(mklogk) or O(nlogk)
// Space Complexity :
// Recursive : O(logk)
// Extra Space : O(n) (To Copy everything at the 1st level)
// Total Space : O(mk) or O(n)
void mergeSort(vector<int> &arr, int start, int end, int portions, int k);
void merge(vector<int> &arr, int start, int mid, int end);
vector<int> mergeArrays3(vector<vector<int>> &mat)
{
    vector<int> ans;
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            ans.push_back(mat[i][j]);
        }
    }
    mergeSort(ans, 0, ans.size() - 1, mat.size(), mat[0].size());
    return ans;
}

void mergeSort(vector<int> &arr, int start, int end, int portions, int k)
{
    if (portions < 2)
    {
        return;
    }
    int mid = start + (portions / 2) * k - 1;
    mergeSort(arr, start, mid, portions / 2, k);              // Division from Left side
    mergeSort(arr, mid + 1, end, portions - portions / 2, k); // Division from Right side
    merge(arr, start, mid, end);                              // Merge and sort the sorted left and right halves.
}
void merge(vector<int> &arr, int start, int mid, int end)
{
    int left = start, right = mid + 1;
    int index = 0;
    vector<int> temp(end - start + 1);

    while (left <= mid && right <= end)
    {
        if (arr[left] <= arr[right])
        {
            temp[index] = arr[left];
            index++;
            left++;
        }
        else
        {
            temp[index] = arr[right];
            index++;
            right++;
        }
    }

    // If Left Portion is still left
    while (left <= mid)
    {
        temp[index] = arr[left];
        index++;
        left++;
    }

    // If Right Portion is still left
    while (right <= end)
    {
        temp[index] = arr[right];
        index++;
        right++;
    }

    // Fill Values into the Array from the temp array
    index = 0;
    while (start <= end)
    {
        arr[start] = temp[index];
        index++;
        start++;
    }
}

// Method (4) here is the most optimized one.
int main()
{
    vector<vector<int>> v = {{3, 4, 5, 11}, {1, 6, 7, 14}, {4, 5, 8, 13}};
    vector<int> ans = mergeArrays3(v);
    for (int i : ans)
    {
        cout << i << " ";
    }
    return 0;
}