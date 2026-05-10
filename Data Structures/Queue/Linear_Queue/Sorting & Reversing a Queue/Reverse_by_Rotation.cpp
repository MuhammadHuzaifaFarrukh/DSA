#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

int main()
{
    queue<int>q1,q2;
    int n = 0;
    while (1)
    {
        cout<<"Enter any number to push (Press -1 to exit) : ";
        cin>>n;

        if(n == -1)
        {
            break;
        }
        q1.push(n);
    } 
    
    n = q1.size() ;
    for(int i = 0 ; i<n;i++)    // The loop actually works here in n - 1 , the last nth iteration doesn't run for j , it just pushes the last element in the queue.
    {                           // So we rotate the queue , in each iteration and get the last element at front in each pass.
        int cur_q1 = q1.size();
        for(int j = 0 ; j<cur_q1-1; j++)    // To get the last element at front each time , we need n-1 iterations.
        {
            int val = q1.front();
            q1.pop();
            q1.push(val);
        }
        q2.push(q1.front());
        q1.pop();
    }

    while(!q2.empty())
    {
        cout<<q2.front()<<" ";
        q2.pop();
    }
    cout<<endl;    
    
    return 0;
}
