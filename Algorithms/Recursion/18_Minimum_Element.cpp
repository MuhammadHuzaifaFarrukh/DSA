#include <iostream>
#include <vector>

using namespace std;

// Bottom-Up Approach :

// We will get answer when we take min of this index value , and the minimum from the index+1 to n of the array.
// minimum_element(arr,0,5) = min(arr[0] , minimum_element(arr,1,5)) = min(3,1) = 1
// minimum_element(arr,1,5) = min(arr[1] , minimum_element(arr,2,5)) = min(4,1) = 1
// minimum_element(arr,2,5) = min(arr[2] , minimum_element(arr,3,5)) = min(1,2) = 1
// minimum_element(arr,3,5) = min(arr[3] , minimum_element(arr,4,5)) = min(2,8) = 2
// minimum_element(arr,4,5) = Return this index value  = 8
// Base Case : When we are at the Last Index , we return its value , cause that might be the minimum.

// minimum_element(arr,index,n) = min(arr[index] , minimum_element(arr,index+1,n));
// We solve only 1 case and rest of the cases are handled with that.

// Time : O(n) , Space : O(n)
int minimum_element(vector<int> &arr, int index, int n)
{
    if (index >= n - 1)
    {
        return arr[index];
    }

    return min(arr[index], minimum_element(arr, index + 1, n));

    // We can also write this instead of above line :
    /*
    int x = minimum_element(arr, index + 1, n);
    if (arr[index] < x)
    {
        return arr[index];
    }
    return x;
    */
}

// Top-Down Approach :

// We will get answer when we take min of this index value , and the minimum from the n-1 to 0 of the array.
// minimum_element(arr,4) = min(arr[4] , minimum_element(arr,3)) = min(8,1) = 1
// minimum_element(arr,3) = min(arr[3] , minimum_element(arr,2)) = min(2,1) = 1
// minimum_element(arr,2) = min(arr[2] , minimum_element(arr,1)) = min(1,3) = 1
// minimum_element(arr,1) = min(arr[1] , minimum_element(arr,0)) = min(4,3) = 3
// minimum_element(arr,0) = Return this index value = 3
// Base Case : When we are at the 0th index, we return its value , cause that might be the minimum.

// minimum_element(arr,n) = min(arr[n] , minimum_element(arr,n-1));  where n is array.size()-1.
// We solve only 1 case and rest of the cases are handled with that.

// Time : O(n) , Space : O(n)
int minimum_element2(vector<int> &arr, int n)
{
    if (n <= 0)
    {
        return arr[n];
    }
    return min(arr[n], minimum_element2(arr, n - 1));

    // We can also write this instead of above line :
    /*
    int x = minimum_element2(arr, n - 1);
    if (arr[n] < x)
    {
        return arr[n];
    }
    return x;
    */
}

// We can also use this approach to find the minimum element.
// Similar to the Top Down , cause we are finding and accumulating the minimum element each time.
// We pass it as a parameter so we can keep its track easily.
// However this should be avoided in pure recursion.
// This approach should be done  when we have to find more than 1 minimums and we pass them as parameters instead of making the return type pair<int,int>.
// Time : O(n)
// Space : O(n)
/*
int minimum_element3(vector<int> &arr, int n, int index, int small = INT_MAX)
{
    if (index == n)
    {
        return small;
    }
    if (arr[index] < small)
    {

        small = arr[index];
    }
    return minimum_element3(arr, n, index + 1, small);
}
*/

int main()
{
    vector<int> arr = {3, 4, 1, 2, 8};

    // cout << "Minimum Element : " << minimum_element(arr, 0, arr.size()) << endl;
    cout << "Minimum Element : " << minimum_element2(arr, arr.size() - 1) << endl;
    return 0;
}