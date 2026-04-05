#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long maximizeProfit(vector<int> &A, int B)
{
    priority_queue<int> pq;
    for (int seats : A)
    {
        pq.push(seats);
    }

    long long totalProfit = 0;
    while (B > 0 && !pq.empty())
    {
        int currentMaxSeats = pq.top();
        pq.pop();

        if (currentMaxSeats > 0)
        {
            totalProfit += currentMaxSeats; // Sell ticket at current vacancy price
            pq.push(currentMaxSeats - 1);   // Row now has one less vacant seat
        }
        B--;
    }
    return totalProfit;
}

int main()
{
    vector<int> A = {2, 5}; // Row 1 has 2 seats, Row 2 has 5 seats
    int B = 4;              // Sell to 4 people
    cout << "Max Profit: " << maximizeProfit(A, B) << endl;
    return 0;
}