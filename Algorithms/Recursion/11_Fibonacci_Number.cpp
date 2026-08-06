#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
Given n, calculate F(n).
*/

// fib(8) = fib(7) + fib(6) = 13 + 8 = 21
// fib(7) = fib(6) + fib(5) = 8 + 5 = 13
// fib(6) = fib(5) + fib(4) = 5 + 3 = 8
// fib(5) = fib(4) + fib(3) = 3 + 2 = 5
// fib(4) = fib(3) + fib(2) = 2 + 1 = 3
// fib(3) = fib(2) + fib(1) = 1 + 1 = 2
// fib(2) = fib(1) + fib(0) = 1 + 0 = 1
// fib(1) = 0
// Base Case : fib(0) = 0 , fib(1) = 1
// Top-Down Approach

// Work done at each level is constant.
// We cannot just find number of calls and multiply by work done at each because they are branching out.
// We can find its time complexity at each level by :
/*
Level 0: fib(n) -> 1 call
Level 1: fib(n-1), fib(n-2) -> 2 calls
Level 2: fib(n-2), fib(n-3), fib(n-3), fib(n-4) -> 4 calls
Level 3: -> 8 calls = 2^3
Level n: -> 2^n calls

// So all calls for a fibonacci 'nth' : 1+2+4+8+...+2^n = 2^(n+1) - 1
// O(2^(n+1)) = O(2^n)
*/

// Its Mathematical Function we can write :
// Fib(n) = Fib(n-1) + Fib(n-2) for n>1.
// If we write Fib(n) as T(n) then we can find its time complexity here as well :
// T(n) = T(n-1) + T(n-2) + 1
// Because dealing with two different shrinking terms (n-1 and n-2) makes the exact math messy, we simplify it for complexity analysis by assuming both branches take roughly equal work.
// To find the upper bound, we approximate T(n-2) ~ T(n-1):
// T(n) = T(n-1) + T(n-1) + 1 = 2T(n-1) + 1
// T(n-1) = 2T(n-2) + 1
// T(n-2) = 2T(n-3) + 1
// We replace and get : T(n) = 2*2T(n-2) + 1 + 1
// We replace and get : T(n) = 2*2*2T(n-3) + 1 + 1 + 1
// T(n) = 2^3T(n-3) + 3
// T(n) = 2^kT(n-k) + k     // k = 3
// Put n-k = 0 and k = n;
// T(n) = 2^nT(0) + n
// T(n) = 2^n(1) + n    // T(0) = 1
// T(n) = 2^n + n = O(2^n + n) = O(2^n)

// If this were a perfect tree structure then if fib(8) was called , then it would take 256 calls however on the right side of tree , it loses some nodes so its not a perfect tree structure.
// A Golden ratio was introduced that tells that its time complexity is actually O(1.618^n)
// To Find actual calls for we can use this formula for nth fib : 2*fib(n+1)-1
// So for fib(8) = 2*(fib(9))-1 = 2*34-1=67 so actual calls are 67 instead of 256.

// The maximum depth of tree for any 'n' can go upto 'n' levels so its space is O(n)
// Time : O(2^n) or O(1.618^n) and Space : O(n)
int fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    int n = 8;
    cout << n << "th Fibonacci Number : " << fib(n) << endl;
    return 0;
}