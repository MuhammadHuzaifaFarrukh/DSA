#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> buildArray(vector<int> &target, int n)
{
    // returns an iterator to the maximum element
    auto it = std::max_element(target.begin(), target.end());

    int val = *it;
    string s1 = "Push";
    string s2 = "Pop";
    vector<string> ans;
    vector<bool> arr(val + 1, 0);
    for (int i = 0; i < target.size(); i++)
    {
        arr[target[i]] = 1;
    }
    // Now we have a 0,1s array
    // 1s mean that element is there in the target array
    // 0s mean that element is not there in the range
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] == 1)
        {
            ans.push_back(s1);
        }
        else
        {
            ans.push_back(s1);
            ans.push_back(s2);
        }
    }
    return ans;
}