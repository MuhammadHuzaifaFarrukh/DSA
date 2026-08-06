#include <iostream>
#include <string>
#include <vector>

using namespace std;

// A Function calling itself again and again -> Recursion.
// A Function that calls itself again calls with changed parameters.
// Until a Specific Condition is met.

// Basic Normal Recursion
// Time : O(n) , Space : O(n)
void fun(int n)
{
    if (n == 0) // Base Condition
    {
        cout << "Happy Birthday ";
        cout << endl;
        return;
    }
    cout << n << " days left for Birthday" << endl;
    fun(n - 1);
}
// How we find the time and space for recursion ?
/*
Time Complexity: How many operations are we doing?
To find the time complexity, look at how much work is done inside a single function call, and multiply it by the total number of calls.
Work per call: Inside the function, we perform basic operations: a comparison to check if n is equal to 0, some printing using cout, and a subtraction of n minus 1. All of these take constant time, written as O(1).
Number of calls: Let us trace how the function calls unfold if we pass n = 3:
fun(3) prints and calls fun(2)
fun(2) prints and calls fun(1)
fun(1) prints and calls fun(0)
fun(0) hits the base case, prints, and returns.

For an input of size n, the function executes exactly n + 1 times.
Total Time = (n + 1) multiplied by O(1) constant work, which simplifies to O(n).
Time Complexity: O(n) (Linear Time)


Space Complexity: How much memory are we using?
Every time a function is called, a new stack frame is pushed onto the stack and stays there until the function returns.

Let us look at how the stack memory accumulates at its peak point, which is right when it hits fun(0):
fun(0) (Active - Top of Stack)
fun(1) (Suspended, waiting for fun(0) to finish)
fun(2) (Suspended, waiting for fun(1) to finish)
fun(3) (Suspended, waiting for fun(2) to finish)
main() (Base Frame)

Because this is a linear chain, fun(3) cannot finish until fun(2) finishes, which cannot finish until fun(1) finishes, and so on.
At the deepest point of recursion, there will be exactly n + 1 frames sitting in memory simultaneously -> n+1 ~ n
Space Complexity: O(n) (Linear Space due to the recursion stack)
// The depth of recursive tree is the space complexity of recursion.
*/

// We can create a recursive tree for this also.
/*
        fun(3)
            \
            fun(2)
                \
                fun(1)
                    \
                    fun(0)
*/

// We can write it as Mathematical relation :
// Print(0) = Happy Birthday
// Print(1) = 1 Days Left + Print(0)
// Print(2) = 2 Days Left + Print(1)
// Print(3) = 3 Days Left + Print(2)
// Print(n) = n Days Left + Print(n-1)      // We can write the full code of our fun() using only this statement
// We divided our problem into sub-problems (Divide & Conquer) and solved sub-problems that combine to solve the actual problem.

// Recurrence Relation T(n) :
// When n = 0, the function does a quick comparison and prints a message.
// This takes a constant amount of time, which we represent simply as 1.
// So, we write:
// T(0) = 1 (when n = 0)

// The total work done for T(n) is split into two parts:
// The non-recursive work: Printing the message and performing the if check takes a constant amount of time. We represent this as 1.
// The recursive work: The function calls itself with a smaller input size of n - 1. The time taken by this sub-problem is represented as T(n - 1).
// Adding these two parts together gives you the equation for the recursive step:
// T(n) = T(n - 1) + 1 (when n > 0)

// T(n) = T(n-1) + 1
// Here (n-1) is the time to solve the (n-1) problem and +1 is the constant work done in writing the print statement.

// If we want to find the Time Complexity using Recurrence Relation :
/*
How to Solve This Recurrence Relation (Substitution Method)
To see how this leads to the O(n) time complexity, you can expand or unroll the relation step-by-step:
T(n) = T(n - 1) + 1
Substitute T(n - 1): T(n) = [T(n - 2) + 1] + 1 = T(n - 2) + 2
Substitute T(n - 2): T(n) = [T(n - 3) + 1] + 2 = T(n - 3) + 3
If you repeat this pattern k times, the equation looks like this:
T(n) = T(n - k) + k

The recursion stops completely when the inner term becomes 0. To make n - k = 0, we must set k = n. Let us substitute k = n into our pattern:
T(n) = T(n - n) + n
T(n) = T(0) + n

Since we already know from our base case that T(0) = 1, we substitute that back in:
T(n) = 1 + n

Because 1 + n grows linearly with the size of n, this mathematically proves that the time complexity is O(n)
*/
int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    fun(3);

    return 0;
}

// Recursion is of 2 Types depending on the last statement called :
// 1) Tail Recursion :
// In tail recursion, the recursive call is the very last operation in the function.
// There is zero work left to do after the recursive call finishes.
// Tail Recursion Example :
/*
void countDown(int n)
{
    if (n <= 0)
    {
        return; // Base case
    }

    printf("%d ", n);

    // Tail Call: The function has nothing left to do but return what this call returns
    countDown(n - 1);
}
*/

// 2) Non-Tail Recursion : Here the recursive call is
// In non-tail recursion, the recursive call is not the last action.
// The function still has to wait for the recursive call to finish because it has some extra "homework" or calculation to do with the result.
// Non-Tail Recursion :
/*
int factorial(int n)
{
    if (n <= 1)
    {
        return 1; // Base case
    }

    // Non-Tail Call: The recursive call happens,
    // BUT we still have to multiply the result by 'n' afterward!
    return n * factorial(n - 1);
}
*/

// Recursion is of 2 Types depending on how it is called :
// Direct Recursion :
// This is the standard, classic form of recursion that most people think of. In direct recursion, a function explicitly calls itself inside its own body.
// There are no other functions involved in the cycle.
// Direct Recursion Example :
/*
void directFunction(int n)
{
    if (n <= 0) return;

    printf("%d ", n);

    // Direct Call: It calls ITSELF directly
    directFunction(n - 1);
}
// The Flow:
// directFunction() -> directFunction() -> directFunction()
*/

// Indirect Recursion :
// In indirect recursion, a function does not call itself directly. Instead, Function A calls Function B, and Function B then calls Function A.
// This creates a circular chain or a mutual loop between two or more functions.
// Indirect Recursion Example :
/*
// Forward declarations so the compiler knows they exist
int isEven(int n);
int isOdd(int n);

int isEven(int n)
{
    if (n == 0)
    {
        return 1; // Base case: 0 is even
    }

    // Indirect Call: calls isOdd
    return isOdd(n - 1);
}

int isOdd(int n)
{
    if (n == 0)
    {
        return 0; // Base case: 0 is not odd
    }

    // Indirect Call: calls isEven
    return isEven(n - 1);
}
*/
// If we call for n = 4 :
// The Flow:
// isEven(4) -> isOdd(3) -> isEven(2) -> isOdd(1) -> isEven(0) (Hits base case!)
