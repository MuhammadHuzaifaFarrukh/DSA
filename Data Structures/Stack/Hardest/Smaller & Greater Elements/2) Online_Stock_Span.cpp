#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// We have to find the number of stock prices that were less than or equal to today's stock price.
// We are asked to find the number of elements greater than or equal to nums[i] for only newly added price from size() - 1 to 0.
// This problem becomes like finding next greater on left.

// This problem is a variant of the Stock Span done but in that we are given all the prices so we can easily store them inside a vector first and start evaluating.
// Here we are given each price 1 by 1 so we need to do similar approach but not exactly like that as it can do TLE.
// If new price is >= previous , we pop it and don't keep record of previous smaller ones cause we don't need the smaller ones , we need one big that keeps the span of those small ones.
// If new price is < previous , then we keep record of all the prices so that if a larger price is added then we can track down its span accordingly.


// 1) Brute Force : O(n^2)

// 2) Using Stack (Monotonic) : O(n)
class StockSpanner
{

private:
    // stack<pair<int,int>> stocks;
    vector<pair<int, int>> stocks; // (stock value, when)
    // We could also use a stack here but it would use a lot of memory since stack uses deque which allocates it lots of memory and still be unused.
public:
    StockSpanner()
    {
    }

    int next(int price)
    {
        int span = 1;
        while (!stocks.empty() && stocks.back().first <= price)
        {
            span += stocks.back().second;
            stocks.pop_back();
        }
        stocks.push_back({price, span});
        return span;
    }
};
int main()
{
    StockSpanner *stockSpanner = new StockSpanner();
    cout << "Stock 100 Pushed : " << stockSpanner->next(100) << endl;
    cout << "Stock 80 Pushed : " << stockSpanner->next(80) << endl;
    cout << "Stock 60 Pushed : " << stockSpanner->next(60) << endl;
    cout << "Stock 70 Pushed : " << stockSpanner->next(70) << endl;
    cout << "Stock 75 Pushed : " << stockSpanner->next(75) << endl;
    cout << "Stock 85 Pushed : " << stockSpanner->next(85) << endl;

    return 0;
}