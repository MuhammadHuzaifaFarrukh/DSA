#include <iostream>
#include <vector>

using namespace std;

// Bottom-Up Approach :

// print(arr,0,5) = arr[0] + print(arr,1,5)
// print(arr,1,5) = arr[1] + print(arr,2,5)
// print(arr,2,5) = arr[2] + print(arr,3,5)
// print(arr,3,5) = arr[3] + print(arr,4,5)
// print(arr,4,5) = arr[4] + print(arr,5,5)
// print(arr,5,5) = Return;
// Base Case : When index == Size.

// print(arr,index,n) = arr[index] + print(arr,index+1,n)
// We solve only 1 case and rest of the cases are handled with that.

// Time : O(n) , Space : O(n)
void print(vector<int> &arr, int index, int n)
{
    if (index >= n)
    {
        return;
    }
    cout << arr[index] << " ";
    print(arr, index + 1, n);
}

// Top-Down Approach (More Efficient because we passed less arguments)

// print2(arr,4) = print2(arr,3) + arr[4]
// print2(arr,3) = print2(arr,2) + arr[3]
// print2(arr,2) = print2(arr,1) + arr[2]
// print2(arr,1) = print2(arr,0) + arr[1]
// print2(arr,0) = print2(arr,-1) + arr[0]
// print2(arr,-1) = Return
// Base Case : Index becomes negative

// print2(arr,n) = print2(arr,n-1) + arr[n] where n is array.size()-1.
// We solve only 1 case and rest of the cases are handled with that.

// Time : O(n) , Space : O(n)
void print2(vector<int> &arr, int n)
{
    if (n < 0)
    {
        return;
    }
    print2(arr, n - 1);
    cout << arr[n] << " ";
}

int main()
{
    vector<int> arr = {3, 7, 2, 6, 8};
    // print(arr, 0, arr.size());
    print2(arr, arr.size() - 1);
    return 0;
}