#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Print all the numbers in a window of size K (can be done using Sliding Window).
// We use circular queue simulation here.
void print_queue(queue<int> q)
{
    while(!q.empty())
    {
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
}

void printing_queue_window(int arr[] , int k , int n = 10)
{
    queue<int> q;
    for(int i = 0 ; i<k-1;i++)
    {
        q.push(arr[i]);
    }

    for(int i = k-1; i< n ; i++)
    {
        q.push(arr[i]);
        print_queue(q);
        q.pop();
    }

}

int main()
{
    int k = 3;
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
        
    printing_queue_window(arr,k);
    return 0;
}
