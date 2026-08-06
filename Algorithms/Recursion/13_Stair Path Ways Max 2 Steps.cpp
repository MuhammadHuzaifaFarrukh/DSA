#include <iostream>

using namespace std;
/*
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

// We analyze a pattern that when we want to go to n = 1 Stair , we have only 1 way i.e 1.
// When n = 2 Stairs then we can go by 1+1 or 2, so we have 2 ways.
// For n = 3 Stairs we can go by :
// 1+1+1 , 1+2 , 2+1 -> 3 Ways.
// For n = 4 Stairs we can go by :
// 1+1+1+1 , 1+1+2 , 1+2+1 , 2+1+1 , 2+2 -> 5 Ways.
// So we see its like this series : 1,2,3,5,8,13,... like fibonacci series.
// But why does it work ?
// When we want to find the stair ways of n = 4 , we have to be either on n = 3 or n=2.
// When we are on n = 2 we have only 2 ways : 1+1 or 2.
// When we are on n = 3 we have only 3 ways : 1+1+1 or 1+2 or 2+1.
// So for going to n = 4 , we can add +2 in the ways of n=2 and +1 for n=3 if we want to go on n=4 from n=2 and n=3.
// So n = 2 , 1+1(+2) and 2(+2)
// So n = 3 , 1+1+1(+1) , 1+2(+1) , 2+1(+1)
// Now we can reach n = 4 from n = 2 and n = 3 so we add up those ways.
// We have total 5 ways for n = 4 , 2 from n = 2 and 3 from n = 3 ways.
// So for finding any 'nth' stair ways climibing , we need to know the ways we can climb one and two steps of 'n' back because when we are at one and two steps back , we can reach 'n' directly.

// Base Cases : n = 1,2
// We can suppose that if n = 0 , then it means we are right there so there is only 1 way for it.
// Very simple to understand but fails for greater values (TLE or stack overflow)

// Time and Space are same as that of fibonacci series :
// ClimbStairs(4) = climbStairs(3) + climbStairs(2) = 3+2 = 5
// climbStairs(3) = climbStairs(2) + climbStairs(1) = 2+1 = 3
// climbStairs(2) = 2;
// climbStairs(1) = 1;
// climbStairs(n) = climbStairs(n-1) + climbStairs(n-2) for n>2.
// Top-Down Approach
// Time : O(2^n) or , Space : O(n)
int climbStairs(int n)
{
    if (n == 1 || n == 2)
    {
        return n;
    }
    else
    {
        return climbStairs(n - 1) + climbStairs(n - 2);
    }
}

int main()
{
    int n;
    cout << "Enter the number of stairs : ";
    cin >> n;
    cout << "Ways to reach " << n << "th stair are : " << climbStairs(n) << endl;

    return 0;
}

// More Efficient : Dynamic Programming
// It is the same as fibonacci sequence (which uses DP ):
/*
int stair(int n)
{
    if (n <= 2) return n;

    int first = 1;  // Represents stair(i-2)
    int second = 2; // Represents stair(i-1)
    int current = 0;

    for (int i = 3; i <= n; i++) {
        current = first + second; // The Fibonacci logic: F(n) = F(n-1) + F(n-2)
        first = second;           // Move the window forward
        second = current;
    }

    return second;
}
*/

// For more professional , we will use actual names :
/*
int stair(int n)
{
    if (n <= 2) return n;
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
*/