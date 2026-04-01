#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);
    q.push(70);
    q.push(80);
        
    // Rotating Right by using Linear queue.
    // It places last element at front. (N-1 Times Pushing and Popping)
    // This also makes it a circular queue.
    // Its still the same circular queue (type of queue) but not the type in the sense that we need to make it from scratch
    // We use the Linear queue to achieve it.

    // So its just a way to achieve circular queue that can be used in many problems to solve.
    // Circular Queue by array also solves problems that require high performance buffer.
    // But this type of achieving circular queue is easy than handling modulo and used in quick logic building.

    for(int i = 0 ; i<q.size()-1;i++)
    {
        q.push(q.front());
        q.pop();
    }

    auto copy = q;
    while(!copy.empty())
    {
        cout<<copy.front()<<" ";
        copy.pop();
    }
    return 0;
}