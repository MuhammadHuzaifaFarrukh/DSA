#include <iostream>

using namespace std;

/*
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 or 3 steps. In how many distinct ways can you climb to the top?
*/

// We analyze a pattern that when we want to go to n = 1 Stair , we have only 1 way i.e 1.
// When n = 2 Stairs then we can go by 1+1 or 2, so we have 2 ways.
// For n = 3 Stairs we can go by :
// 1+1+1 , 1+2 , 2+1 , 3 -> 4 Ways.
// For n = 4 Stairs we can go by :
// 1+1+1+1 , 1+1+2 , 1+2+1 , 2+1+1 , 2+2 , 1+3 , 3+1  -> 7 Ways.
// So we see its like this series : 1,2,4,7,13,24,44,... like Tribonacci series.
// But why does it work ?
// When we want to find the stair ways of n = 4 , we have to be either on n = 3 or n=2 or n=1.
// When we are on n = 1, we only have 1 way : 1
// When we are on n = 2 we have only 2 ways : 1+1 or 2.
// When we are on n = 3 we have only 3 ways : 1+1+1 or 1+2 or 2+1.
// So for going to n = 4 , we can add +3 in the ways of 1 , we can add +2 in the ways of n=2 and +1 for n=3 if we want to go on n=4 from n=2 and n=3.
// So n = 1 , 1(+3) and (+3)+1 although for n = 1 there's only 1 step but now we are adding another number so it becomes 2 steps cause that changes the ways if we take 1 step first or later.
// So n = 2 , 1+1(+2) and 2(+2)
// So n = 3 , 1+1+1(+1) , 1+2(+1) , 2+1(+1)
// Now we can reach n = 4 from n = 1 , n = 2 and n = 3 so we add up those ways.
// We have total 7 ways for n = 4 , 2 from n = 1 , 2 from n = 2 and 3 from n = 3 ways.
// So for finding any 'nth' stair ways climibing , we need to know the ways we can climb one , two , three steps to 'n' back because when we are at one , two , three steps back from 'n' , we can reach 'n' directly.

// Base Cases : n = 1,2,3
// We can suppose that if n = 0 , then it means we are right there so there is only 1 way for it.

// Time and Space are same as that of tribonacci series :
// ClimbStairs(4) = climbStairs(3) + climbStairs(2) + climbStairs(1)  = 3+2+2 = 7
// climbStairs(3) = 4;
// climbStairs(2) = 2;
// climbStairs(1) = 1;
// climbStairs(n) = climbStairs(n-1) + climbStairs(n-2) + climbStairs(n-3) for n>3.
// Top-Down Approach
// Time : O(3^n) or O(1.839^n), Space : O(n)

int climbStairs(int n)
{
    if (n <= 2)
    {
        return n;
    }
    else if (n == 3)
    {
        return 4;
    }
    else
    {
        int totalWays = climbStairs(n - 1) + climbStairs(n - 2) + climbStairs(n - 3);
        return totalWays;
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
