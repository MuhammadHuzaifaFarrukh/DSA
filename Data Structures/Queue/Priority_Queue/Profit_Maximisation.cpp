#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Given an array A , representing seats in each row of a stadium.
You need to sell tickets to B people.
Each seat costs equal to the number of vacant seats in the row it belongs to. The task is to maximize the profit by selling the tickets to B people.

Input: A = [2, 3] ,B = 3
Output : 7
First you serve the seat with number = 3. Then with 2 and then with 2. hence answer = 3 + 2 + 2 = 7.
*/

// 1) Brute Forcing / Sorting will lead to time : O(n^2)

// 2) Greedy + Max-Heap :
// We choose the maximum seated row , and see if its not zero because it is possible that given 'B' may be so much greater that if we don't put this check we might start entering negative values in our heap.
// So we check that value entered is greater than 0 , then we add it to our profit and push (value-1) in our heap.
// We keep doing this till B or till pq exists.
// Time : O(n+blogn) , where b can be even more than 'n'
// Space : O(n)
// We could also just add the profit first and then check whether (value-1 > 0) or not , if yes only then we push this value to our pq , this will eliminate all the zero from even being entered , whereas in the approach that we did by (value >0) , 0 is being entered once for each row of seats if 'B' gets till there.
long long maximizeProfit(vector<int> &A, int B)
{
    priority_queue<int> pq(A.begin(), A.end());

    long long totalProfit = 0;
    while (B > 0 && !pq.empty())
    {
        int currentMaxSeats = pq.top();
        pq.pop();

        if (currentMaxSeats > 0) // Only if zeroes are allowed , otherwise we don't need this check
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