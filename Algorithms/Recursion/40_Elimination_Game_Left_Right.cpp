#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
You have a list arr of all integers in the range [1, n] sorted in a strictly increasing order. Apply the following algorithm on arr:

Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
Repeat the previous step again, but this time from right to left, remove the rightmost number and every other number from the remaining numbers.
Keep repeating the steps again, alternating left to right and right to left, until a single number remains.
Given the integer n, return the last number that remains in arr.

Input: n = 9
Output: 6
Explanation:
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
arr = [2, 4, 6, 8]
arr = [2, 6]
arr = [6]

Input: n = 1
Output: 1
*/

// 1) We make a new array from 1 to n.
// We can keep iterating untill there is only 1 element left in our vector.
// We remove elements from Left to Right 1 pass , then in next pass we remove Right to Left with alternating and so on until we have 1 element left.
// However due to constraints on 10^9 , it will fail badly on much larger test cases.
// Each time we are iterating from forward to backward , or backward to forward.
// Total Work : n + n/2 + n/4 +...+ 1 = O(n^2)
// We create a new array of size 'n'.
// Time : O(n^2)
// Space : O(n)

// 2) We will use Maths :
// We know that we are dividing the array into two parts.
// So we keep dividing our array until we are left with only 1 element.
// We also keep a boolean variable that will keep altering its value each time.
// Each time we eliminate half elements , the distance is doubled.
// Also when our elements in Right to left case are odd , we have to in that case check by taking their remainder is 1.

// Time : O(logn)
// Space : O(1)

int lastRemaining(int n)
{
    int head = 1;              // Tracks the first element remaining
    int step = 1;              // Distance between adjacent remaining numbers
    int remaining = n;         // How many elements are left
    bool left_to_right = true; // Flips direction each pass

    while (remaining > 1)
    {
        // Head shifts if moving Left->Right OR if moving Right->Left with an ODD count
        if (left_to_right || remaining % 2 == 1)
        {
            head += step;
        }

        // Update parameters for the next round
        step *= 2;                      // Gap doubles after every pass
        remaining /= 2;                 // Total count is halved
        left_to_right = !left_to_right; // Flip direction
    }

    return head;
}

// 3) Recursive Approach (Way Better than iterative to understand)
// Time : O(logn) , Space : O(logn)
// Explained at the end
int lastRemaining(int n)
{
    if (n == 1)
        return 1;

    return 2 * (1 + n / 2 - lastRemaining(n / 2));
}

int main()
{
    int n = 10;
    cout << "Player who won : " << lastRemaining(n) << endl;
    return 0;
}

// How recursive formula is derived and works?
/*
Suppose n = 8. The original array is:
[1, 2, 3, 4, 5, 6, 7, 8]

When we do the first pass (Left to Right), every odd-indexed element gets deleted:
[x]1, 2, [x]3, 4, [x]5, 6, [x]7, 8

The remaining elements are:
[2, 4, 6, 8]

Notice anything about these numbers? They are all even!
If we divide every remaining number by 2, we get:
[1, 2, 3, 4]

Look at that! We shrunk an array of size 8 into a fresh array of size 4 (n / 2).

Key Discovery 1: If we know the answer for n/2, we can just multiply it by 2 to get the answer in our original array.

The Direction Problem (The "Flipping" Trick)
There is one big catch:
For size n = 8, the first pass went Left to Right.
Now, for the remaining array of size n/2 = 4, the next pass needs to go Right to Left.

When you run lastRemaining(4), it assumes you start Left to Right. But we need the answer for a Right to Left sweep!

How do we convert a Right-to-Left sweep into a Left-to-Right sweep? By flipping the sequence backward!

The Symmetry Property
In any sequence of numbers from 1 to K:
The "mirror image" of index x from the right end is:
Mirrored Index = (1 + K - x)

Example (K = 4):
Position 1 mirrored is 1 + 4 - 1 = 4
Position 2 mirrored is 1 + 4 - 2 = 3

Key Discovery 2: The survivor of a Right to Left game of size K is equal to:
(1 + K - lastRemaining(K))

Putting It All Together
Now, combine Key Discovery 1 (doubling) and Key Discovery 2 (mirroring) where K = n/2:

Find the survivor for a sub-problem of size n/2:
lastRemaining(n/2)

Flip it to account for the reversed direction (Right to Left):
(1 + n/2 - lastRemaining(n/2))

Multiply by 2 to scale back up to the original even numbers:
2 * (1 + n/2 - lastRemaining(n/2))
*/
