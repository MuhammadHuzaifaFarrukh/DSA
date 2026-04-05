#include <iostream>
#include <queue>
#include <string>
#include <stack>

using namespace std;

// Efficient Approach (Without Queues) :
// Josephus Formula : J(n,k) = (J(n-1,k)+k) mod n
// do it in O(n)
/*
int winner = 0; // Base case for 1 person
for (int i = 2; i <= n; i++) 
{
    winner = (winner + k) % i;
}
return winner + 1; // Convert back to 1-based indexing
*/

int main()
{
    queue<int> q;
    int n = 0;
    cout << "Enter n : ";
    cin >> n;
    int k;
    cout << "Enter k : ";
    cin >> k;

    for (int i = 1; i <= n; i++)
    {
        q.push(i);
    }

    while (q.size() > 1)
    {
        // int cur_k = (k-1)%q.size()   // So we rotate only those times as needed (and handle if k is too large) and put i<cur_k in for loop.

        for (int i = 0; i < k - 1; i++)
        {
            q.push(q.front());
            q.pop();
        }
        q.pop();
    }

    cout << "Last Remaining Friend : " << q.front() << endl;
    return 0;
}
