#include <iostream>

using namespace std;

// Find GCD of 'a' and 'b'.

// We apply Euclidean Algorithm
// (18,48)
// (48,18%48)
// (18,48%18) = (18,12)
// (12,18%12) = (12,6)
// (6,12%6) = (6,0)
// 6 is our answer.
// So we always take 'b' at first parameter and take 2nd parameter as a%b until 'b' becomes 0 and return 'a'.
// Base Case is always that if b is 0 , we return a.
// GCD(a,b) = GCD(b, a%b);

// Time : O(log(min(a,b))) , Space : O(log(min(a,b)))
int GCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return GCD(b, a % b);
}

int main()
{
    int a = 18, b = 48;
    cout << "GCD of " << a << " and " << b << " : " << GCD(a, b) << endl;
    return 0;
}

/*
// Iterative Version :
// Time : O(log(min(a,b)) , Space : O(1)
int GCD(int a , int b)
{
    while(b != 0 )
    {
        int temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}
*/

// Mathematical Proof of Euclidean Algorithm :
/*
The Euclidean Algorithm relies on one beautiful, core mathematical property: If a number d divides both a and b, then d must also divide the remainder of a divided by b (which is a % b).

Because of this, finding the greatest common divisor of two massive numbers can be systematically scaled down into finding the GCD of much smaller numbers:
gcd(a, b) = gcd(b, a % b)

======================================================================================

Here is both the visual concept and the rigorous algebraic proof made as simple as possible.

The Intuitive / Visual Proof (Lamé's Tiling)
Imagine you have a large rectangular room with side lengths a and b. You want to perfectly pave the entire floor using the largest possible square tiles without cutting any of them. The side length of this perfect square tile is, by definition, the gcd(a, b).
If you start laying down large square tiles of size b × b into the a × b room, you can fit a certain number of them until you are left with a narrow rectangular strip.
The width of that leftover strip is exactly the remainder: r = a % b.
Now, the problem shifts! Any square tile that perfectly fits both a and b must also perfectly fit inside this new leftover rectangle of size b × r.
You repeat the process, packing smaller squares of size r × r into the remaining space until the room is perfectly filled with no remainder. The size of the final square tile that perfectly closes the gap is your GCD.

=======================================================================================

The Mathematical Proof
To prove this formally, we must show that any common divisor of a and b is exactly the same as the common divisor of b and r.

Step 1: Write out the Division Equation
When you divide integer a by integer b, you get a quotient q and a remainder r:
a = q · b + r

Where the remainder is bounded by 0 <= r < b. We can rewrite this equation to solve for r:
r = a - q · b

Step 2: Show that a common divisor of (a, b) divides r
Let d be a common divisor of a and b. This means d divides a (a/d is an integer) and d divides b (b/d is an integer).

Look at our rewritten equation for the remainder:
r = a - q · b

If we divide the entire equation by d:
r/d = a/d - q · (b/d)

Since a/d and b/d are integers, the right side of the equation results in a clean integer. Therefore, r/d must also be an integer, meaning d is a divisor of r.

Step 3: Show the reverse (A common divisor of (b, r) divides a)
Now let’s look at it from the other direction. Let some divisor k cleanly divide both b and r.

Look back at our original formula:
a = q · b + r

If we divide this entire equation by k:
a/k = q · (b/k) + r/k

Since b/k and r/k are integers, the right side evaluates to an integer. Therefore, a/k must also be an integer, meaning k cleanly divides a.

Conclusion :
Because every number that divides the pair (a, b) also divides the pair (b, r), and vice versa, the two pairs share the exact same set of common divisors.
Since their sets of divisors are identical, their Greatest Common Divisor must be identical:
gcd(a, b) = gcd(b, r)
By repeating this substitution loop over and over, the numbers get smaller and smaller until r = 0. At that final moment, gcd(latest a, 0) = latest a
*/

// ==========================================================================================================================

// Finding Time Complexity :
/*
The mathematical derivation relies on a core pattern: after every two iterations of the loop, the value of b is guaranteed to be cut at least in half.

Step 1: The Core Reduction Property (With Examples)
When we run the operation a % b, the size of b relative to a determines how the remainder shrinks. There are only two mathematical possibilities:

Case 1: If b is greater than or equal to a / 2
In this case, b is more than half of a. When you divide a by b, it fits exactly once, leaving a remainder r = a - b. Because b took up more than half of a, whatever is left over (r) must be strictly less than half of a.

Example for Case 1: Let a = 10 and b = 7.
Here, half of a is 5, and since 7 is greater than 5, this fits Case 1 perfectly.
Let's calculate the remainder: 10 % 7 = 3.
Notice that our remainder (3) is strictly less than half of a (5). The rule holds: r < a / 2.

Case 2: If b is less than a / 2
The rules of mathematics state that the remainder of any modulo operation (a % b) must be strictly less than the divisor (b). Since b is already known to be less than half of a, the resulting remainder r automatically has to be less than half of a as well.

Example for Case 2: Let a = 10 and b = 3.
Here, half of a is 5, and since 3 is less than 5, this fits Case 2 perfectly.
Let's calculate the remainder: 10 % 3 = 1.
Notice that our remainder (1) is strictly less than half of a (5). The rule holds: r < a / 2.

Conclusion of Step 1: No matter what numbers you pick, the remainder of the very first operation is mathematically guaranteed to be less than half of a.

Step 2: Tracking Two Iterations (With Examples)
Now let's look at what happens over two full steps of the loop. Let's trace it abstractly first, and then apply real numbers to see the parameter drop in action.

Start State: We begin with our variables holding the values (a, b).

Iteration 1: We calculate the first remainder: r1 = a % b.
The variables swap for the next loop, so our state becomes: (b, r1).
Iteration 2: We calculate the next remainder using our updated variables: r2 = b % r1.
The variables swap again, updating our state to: (r1, r2).

Now let's apply our rule from Step 1 to Iteration 2. Because r2 is the remainder of b % r1, the value of r2 is guaranteed to be less than half of the numerator, which in this loop is b.
r2 < b / 2
Example for Step 2: Let's start a 2-iteration sequence with a = 26 and b = 18.

Iteration 1: We calculate 26 % 18 = 8. Our state updates to (18, 8).
Iteration 2: We calculate 18 % 8 = 2. Our state updates to (8, 2).
Look at our second parameter (b) across these two steps. It started at 18 before Iteration 1. After Iteration 2, it dropped to 2. Notice that 2 is strictly less than half of 18 (18 / 2 = 9).

Conclusion of Step 2: After every two iterations of the loop, the second parameter is guaranteed to drop to less than half of its original value from two steps prior.

Step 3: Solving the Recurrence Relation
Since the value cuts in half at least every 2 steps, we can calculate the absolute worst-case scenario by assuming it cuts exactly in half every 2 steps.

Let's represent the smaller of our two starting numbers as N. We want to find the maximum number of steps (k) it will take to reduce N all the way down to 1 (where the loop terminates).
Every 2 steps, N is divided by 2. Therefore, after k total steps, N has been divided by 2 a total of (k / 2) times. We set this equal to our stopping point:
N / (2^(k / 2)) = 1
To isolate our variables, multiply both sides by the denominator:
N = 2^(k / 2)
Take the logarithm (base 2) of both sides to pull the exponent down:
log2(N) = k / 2
Multiply both sides by 2 to completely isolate k:
k = 2 · log2(N)

Final Big-O Result
In asymptotic Big-O analysis, we drop constant multipliers because they don't change the rate of growth as inputs approach infinity. Dropping the multiplier of 2 leaves us with our final time complexity.
Since N was chosen as the smaller of the two inputs, the time complexity is:
Time Complexity = O(log(min(a, b)))

============================================================================================================================================================================================================

Proving it with a Full Comprehensive Trace
Let's prove this whole derivation end-to-end using a massive gap: a = 125 and b = 32.

Our smaller input N is 32.
According to our formula, the maximum number of steps this should take is:
2 · log2(32) = 2 · 5 = 10 steps maximum. Let's see how many it actually takes:

Initial State: a = 125, b = 32
Iteration 1: temp = 125, a = 32, b = 125 % 32 = 29. State is (32, 29).
Iteration 2: temp = 32, a = 29, b = 32 % 29 = 3. State is (29, 3).
Check 1: Two steps completed. Our original b was 32. Our new b is 3. Is 3 less than half of 32? Yes (3 < 16). The 2-step halving rule works!

Iteration 3: temp = 29, a = 3, b = 29 % 3 = 2. State is (3, 2).
Iteration 4: temp = 3, a = 2, b = 3 % 2 = 1. State is (2, 1).
Check 2: Four steps completed. The b at step 2 was 3. Our new b is 1. Is 1 less than half of 3? Yes (1 < 1.5). The 2-step halving rule works again!

Iteration 5: temp = 2, a = 1, b = 2 % 1 = 0. State is (1, 0).
The loop checks while(b != 0), sees that b is now 0, breaks out, and returns a = 1.
It took exactly 5 steps to finish, which is well under our calculated theoretical worst-case bound of 10 steps. The exponential decay of the parameters guarantees that the loop runs in logarithmic time!
*/