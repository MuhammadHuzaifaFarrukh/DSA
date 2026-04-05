#include <queue>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

// 1st Approach is to flat the array and sort and keep doing it till we find kth element : O(N^2Logn).
// 2nd Approach is to use a min heap and then flat the array and keep finding the kth smallest element : O(N^2 + Klogn). (This would work if our data was unsorted)

// Since our data is sorted in each row , let's use that : We know that the elements smallest after (0,0) will be either (0,1) or (1,0). Since we will add all the (0,n-1) , we have to add (n-1,n-2) ourselves 
// And this is our 3rd Approach here below is to store all the rows' first val with their positions and then take the kth smallest elements by running the loop k times : O( N + KLogn).
int kthsmallest(int **arr, int n, int k)
{
    vector<pair<int,pair<int,int>> >v ;
    for(int i = 0 ; i<n ; i++)
    {
        v.push_back({arr[i][0] , {i,0} });      // We can also do : make_pair(arr[i][0] , make_pair(i,j)) 
    }

    priority_queue<pair<int,pair<int,int>> , vector<pair<int,pair<int,int>>> , greater<pair<int,pair<int,int>>>  > pq(v.begin(),v.end());

    int ans;
    pair<int,pair<int,int>> Element;
    int i,j;
    while(k--)
    {
        Element = pq.top();
        pq.pop();
        ans = Element.first;
        i = Element.second.first;
        j = Element.second.second;

        if(j+1<n)
        {
            pq.push({arr[i][j+1] , {i,j+1} });
        }
    }
    return ans;
}

// We can also use Binary Search here which would work better for large K.

int main()
{
    int n = 4;
    int **arr = new int *[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "Enter element : [" << i << "][" << j << "] : " ;
            cin >> arr[i][j];
        }
    }

    int k = 6;
    cout<<k<<"th Smallest Element is : "<<kthsmallest(arr,n,k);
    
    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}