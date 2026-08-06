#include <iostream>

using namespace std;

/*
The Tribonacci sequence Tn is defined as follows:
T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.
*/

// Top-Down Approach
// tribonacci(8) = tribonacci(7) + tribonacci(6) + tribonacci(5)
// tribonacci(7) = tribonacci(6) + tribonacci(5) + tribonacci(4)
// tribonacci(6) = tribonacci(5) + tribonacci(4) + tribonacci(3)
// tribonacci(5) = tribonacci(4) + tribonacci(3) + tribonacci(2)
// tribonacci(4) = tribonacci(3) + tribonacci(2) + tribonacci(1)
// tribonacci(3) = tribonacci(2) + tribonacci(1) + tribonacci(0)
// tribonacci(2) = 1
// tribonacci(1) = 1
// tribonacci(0) = 1
// Base Cases , n = 0,1,2

// Work done at each level is constant.
// We cannot just find number of calls and multiply by work done at each because they are branching out.
// We can find its time complexity at each level by :
/*
Level 0: tribonacci(n) -> 1 call
Level 1: tribonacci(n-1), tribonacci(n-2) , tribonacci(n-3)-> 3 calls
Level 2: -> 9 Calls
Level 3: -> 27 calls = 3^3
Level n: -> 3^n calls

// So all calls for a tribonacci 'nth' : 1+3+9+27+...+3^n = 3^(n+1) - 1
// O(3^(n+1)) = O(3^n)
*/

// Its Mathematical Function we can write :
// tribonacci(n) = tribonacci(n-1) + tribonacci(n-2) for n>2.
// If we write tribonacci(n) as T(n) then we can find its time complexity here as well :
// T(n) = T(n-1) + T(n-2) + T(n-3) + 1
// Because dealing with two different shrinking terms (n-1 and n-2 and n-3) makes the exact math messy, we simplify it for complexity analysis by assuming all these branches take roughly equal work.
// To find the upper bound, we approximate T(n-3) ~ T(n-2) ~ T(n-1):
// T(n) = T(n-1) + T(n-1) + + T(n-1) + 1 = 3T(n-1) + 1
// T(n-1) = 3T(n-2) + 1
// T(n-2) = 3T(n-3) + 1
// We replace and get : T(n) = 3*3T(n-2) + 1 + 1
// We replace and get : T(n) = 3*3*3T(n-3) + 1 + 1 + 1
// T(n) = 3^3T(n-3) + 3
// T(n) = 3^kT(n-k) + k     // k = 3
// Put n-k = 0 and k = n;
// T(n) = 3^nT(0) + n
// T(n) = 3^n(1) + n    // T(0) = 1
// T(n) = 3^n + n = O(3^n + n) = O(3^n)

// If this tree structure had 3 branches for each node , then if fib(8) was called , then it would take 3^8 calls however on the right side of tree , it loses some nodes so its not a tree structure having 3 branches for each node.
// Just like the Fibonacci tree loses nodes on the right, the Tribonacci tree drops branches even faster because n-2 and n-3 bottom out rapidly.
// A Golden ratio was introduced that tells that its time complexity is actually O(1.839^n)
// To Find actual calls for we can use this formula for nth tribonacci : (2*(Tribonacci(n+1)) + Tribonacci(n)-1)/2

// So for tribonacci(8) = (2*Tribonacci(9))+ Tribonacci(8) -1)/2 = (2(81)+44-1)/2 = 102 so actual calls are 102 instead of 3^8 (6561).

// The maximum depth of tree for any 'n' can go upto 'n' levels so its space is O(n)
// Time : O(3^n) or O(1.839^n) and Space : O(n)

int tribonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    if (n == 2)
    {
        return 1;
    }
    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}
int main()
{
    int n = 5;
    cout << n << "th Tribonacci Number : " << tribonacci(n) << endl;
    return 0;
}