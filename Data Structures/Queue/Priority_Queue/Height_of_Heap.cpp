#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue <int> pq;
    pq.push(5);
    pq.push(6);
    pq.push(10);
    pq.push(12);
    pq.push(7);
    pq.push(19);
    pq.push(14);

    int  n = pq.size();
    int height = 0;
    // This works in O(log n)
    if(n == 1)
    {
        height = 1;
    }
    else
    {
        while(n>1)
        {
            n = n/2;
            height++;
        }
    }
    cout<<"Height of the Heap : "<<height<<endl;

    return 0;
}