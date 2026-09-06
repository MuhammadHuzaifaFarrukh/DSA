#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

/*
You are given two integer arrays nums1 and nums2 sorted in non-decreasing order and an integer k.
Define a pair (u, v) which consists of one element from the first array and one element from the second array.
Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.

Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
*/

// Since these are sorted arrays , we will use pairing of all elements of nums1 to nums2[0].
// We cannot use max heap by just seeing kth smallest because here we have to do pairing and using min heap is the best choice.
// If we try to use max heap , then we will have to generate all pairs that can lead to more time.
// So we use min heap and pair nums1 all elements with nums2[0].
// We also use min(nums1.size() , k ) , because if 'k' is smaller than nums1.size() then we only need those relevant 'k' pairs and if nums1.size() is smaller , then setting 'k' would be accessing invalid index.
// We use nested pair to store the pair sum and the indexes instead of values.
// Then we run another loop 'k' times.
// This gets the first pair and we save our first answer.
// Then we check if there are more indices of nums2 that can be paired along this smallest pair's first index.
// So we check j+1 < nums2.size() and if yes then we add another pair with same first index but this time nums2 index with +1.
// This can get us another smallest pair if this pair's sum is smallest of all , or if the 2nd indexed element may be big that this pair is not the smallest pair.
// We just do it 'k' times to get our answer.
// The question has asked us the order (nums1,nums2) otherwise the vice verse is also not wrong but it will not be according to the question then.
// If these weren't sorted arrays then we would first sort them otherwise time would go to O(m*n) and space also to O(m*n).
// Time Complexity :
// Time to push min(n1,k) elements : min(n1,k)log(min(n1,k))
// Time to pop/push k elements : klog(min(n1,k)).
// Total Time : min(n1,k)log(min(n1,k)) + klog(min(n1,k)) or klog(min(n1,k)).
// Space : O(min(n1,k)).
vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
{
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    for (int i = 0; i < nums1.size(); i++) // Can be written also as for a little optimizations : (int i = 0; i < min((int)nums1.size(), k); i++)
    {
        pq.push({nums1[i] + nums2[0], {i, 0}});
    }
    vector<vector<int>> ans;
    while (k > 0 && !pq.empty())
    {
        pair<int, pair<int, int>> temp = pq.top();
        pq.pop();
        int i = temp.second.first;
        int j = temp.second.second;
        ans.push_back({nums1[i], nums2[j]});

        if (j + 1 < nums2.size())
        {
            pq.push({nums1[i] + nums2[j + 1], {i, j + 1}});
        }
        k--;
    }
    return ans;
}

int main()
{
    vector<int> v1 = {1, 7, 11};
    vector<int> v2 = {2, 4, 6};
    int k = 5;
    vector<vector<int>> ans = kSmallestPairs(v1, v2, k);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "(" << ans[i][0] << "," << ans[i][1] << ")" << endl;
    }
    cout << endl;
    return 0;
}