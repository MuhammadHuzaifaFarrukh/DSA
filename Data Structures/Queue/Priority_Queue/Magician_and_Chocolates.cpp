#include <iostream>
#include <queue>

using namespace std;

int MagicianAndChocolates(vector<int> &chocs , int T)
{
    priority_queue<int>pq(chocs.begin(),chocs.end());
    int total = 0;
    while( (T--) && !pq.empty())
    {
        int x = pq.top();
        total += x;
        pq.pop();
        
        if(x/2)
        {
            pq.push(x/2);
        }
    }
    return total;
}
int main()
{
    vector<int> v = {2,4,6,8,10};
    int T = 5;
    cout<<"Maximum Chocolates eaten are : "<<MagicianAndChocolates(v,T)<<endl;
    return 0;
}