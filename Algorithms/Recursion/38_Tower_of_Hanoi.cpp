#include <iostream>
#include <vector>

using namespace std;

/*
The Tower of Hanoi problem involves moving a stack of disks from one rod to another, following these rules:

Only one disk can be moved at a time.
A disk can only be placed on top of a larger disk or an empty rod.
All disks start on one source rod and need to be moved to another destination rod using a helper rod.
*/

// This is where the magic of Recursion occurs.
// When we have only 1 disk on the source , we can directly move it on the destination rod in 1 step.
// When we have 2 disks, then we move smaller one on the helper , larger one on the destination and smaller one on the destination as well completing in 3 steps.
// Now for 3 disks on the source , we do :
// Move disk 1 from source to destination
// Move disk 2 from source to helper
// Move disk 1 from destination to helper
// Move disk 3 from source to destination
// Move disk 1 from helper to source
// Move disk 2 from helper to destination
// Move disk 1 from source to destination
// Total steps taken : 7

// If we observe , we can clearly see that for moving our 'n' disks to destination our (n-1) rods must be at the helper rod.
// Only then we are able to put the largest nth disk at the destination.
// Then we again move all those disks from the helper to destination while using source as our intermediate (or helper) rod.
// E.g : when we have 3 disks on source , we had to move n = 2 disks from source to helper using destination.
// For moving those (n-1) = 2 to helper , we need to put (n-1) disks to destination first before moving n = 2 disk to helper.
// So that's why we take the base step to put n = 1 from source to destination and put our n = 2 from source to helper.
// Then we again put those (n-1) = 1 disk and move from destination to helper using source so that's why we move the disk 1 directly from destination to helper on top of disk 2.
// Now we can see that we have put (n-1) = 2 disks on helper from source using destination.
// Now we will put (n=3) on the destination directly so we move this disk 3 from source to destination.
// Now we have (n-1) 2 disks on the helper and n = 3 disk on the destination.
// Now we have to put (n-1) 2 disks from helper to destination using source.
// So for moving these (n-1) 2 disks at destination from helper , we must place disk 1 at the intermediate (source) so that here (n-1) which is 1 is placed on the intermediate and disk 2 can easily go to destination.
// For moving disk 2 to destination , we have to move (n-1) = 1 at intermediate one , so we put disk 1 from helper to source.
// Now we can directly move disk 2 to destination from helper.
// And finally after disk 2 is at destination , we can move disk 1 from source to destination.

// If we dry run it for n = 4, we can observe the same pattern , that for moving n=4 , we need to put the above 3 disks from source to helper using destination.
// Then we have to put the 4th disk at destination directly.
// And then we put those 3 disks from helper to destination using source.
// And for moving these 3 disks from any rod to other rod using intermediate rod , we've already seen it , so this pattern keeps going.
// Therefore for solving this , we do only 3 steps :
// 1) Move n-1 disks from source to helper using destination. (Recursive Call)
// 2) Move nth disk from source to destination. (Print Statement)
// 3) Move n-1 disks that were at helper from helper to destination using source as intermediate. (Recursive Call)
// Our base case for all is 1 disk which we can move directly from one rod to other (one and other rod can be any i.e source,helper or destination).

// Total Steps for any 'n' disks are : 2^n - 1.

// Time Complexity :
// We can find time complexity by seeing work done in each node times total nodes.
// Total Nodes we have :
// Level 0 : 1
// Level 1 : 2
// Level 2 : 4
// Level 3 : 8
// For any 'n' , max levels are (n-1).
// For n = 3, levels are 0,1,2.
// Level n-1 : 2^(n-1) nodes
// If we count the total number of nodes across all levels up to the bottom, the total count is:
// 1 + 2 + 4 + 8 + ... + 2^(n-1) = 2^n - 1 total nodes.
// Time : O(2^n)

// Space Complexity :
/*
The main function call for size n is pushed onto the stack.
It immediately calls the next step for size n - 1, which is pushed on top of it.
That call immediately invokes the step for size n - 2, which is pushed on top of that.
This linear chain continues straight down until we push the base case call for size 1 onto the stack.
At this exact moment, the stack has reached its absolute highest point. The stack contains a chain of active function calls for sizes: n, n - 1, n - 2, all the way down to 1.
Counting these up, the maximum depth of the recursion tree is exactly n.
Work done in each node is constant O(1) so total space is O(n)
Space : O(n)
*/
void tower_of_hanoi(int n, string source, string helper, string destintation)
{
    if (n == 1)
    {
        cout << "Move disk " << n << " from " << source << " to " << destintation << endl;
        return;
    }
    tower_of_hanoi(n - 1, source, destintation, helper);
    cout << "Move disk " << n << " from " << source << " to " << destintation << endl;
    tower_of_hanoi(n - 1, helper, source, destintation);
}

int main()
{
    int n;
    cout << "Enter number of disks : ";
    cin >> n;

    tower_of_hanoi(n, "source", "helper", "destination");

    return 0;
}

// Recurrence Relation :
/*
The Tower of Hanoi Recurrence Relation
For this problem, the work depends directly on the number of disks we have left to move.
Let's use n to represent the total number of disks.
When we call the function with n disks, our code does three things:
It makes a recursive call to move the top n - 1 disks from our source rod to our helper rod.
It executes a single print statement to move the largest remaining disk from the source rod to the destination rod, which takes constant O(1) time.
It makes a second recursive call to move the n - 1 disks from the helper rod over to the final destination rod.

Because we make two identical recursive calls for n - 1 disks and perform a single constant-time operation in between them, our recurrence relation for a normal step is:
T(n) = 2 * T(n - 1) + O(1)
The Base Case
When n = 1, we hit our base case at the top of the function. Inside this base case, we execute a single print statement to move the final disk and return immediately.
This operation takes constant time.
So, the exact time taken at the base case is:
T(1) = O(1)

Unrolling the Relation to Find Complexity
If we break down the formula T(n) = 2 * T(n - 1) + 1 step-by-step all the way down to our base case, a clear doubling pattern emerges:
First step:
T(n) = 2 * T(n - 1) + 1
Second step:
T(n) = 2 * (2 * T(n - 2) + 1) + 1 = 4 * T(n - 2) + 2 + 1
Third step:
T(n) = 8 * T(n - 3) + 4 + 2 + 1

If we follow this pattern all the way down until we hit our base case at T(1), the equation expands into a geometric series of powers of 2:
T(n) = 2^(n-1) + 2^(n-2) + ... + 4 + 2 + 1
This geometric series adds up perfectly to 2^n - 1 total operations. Each operation consists of printing a single disk move. Asymptotically, we drop the constant subtraction of 1, which gives us our final time complexity:

Total Time Complexity = O(2^n)
*/
