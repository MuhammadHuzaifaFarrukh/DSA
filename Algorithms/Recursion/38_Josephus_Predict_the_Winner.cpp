#include <iostream>
#include <vector>

using namespace std;
/*
There are n friends that are playing a game. The friends are sitting in a circle and are numbered from 1 to n in clockwise order. More formally, moving clockwise from the ith friend brings you to the (i+1)th friend for 1 <= i < n, and moving clockwise from the nth friend brings you to the 1st friend.

The rules of the game are as follows:

1) Start at the 1st friend.
2) Count the next k friends in the clockwise direction including the friend you started at.
The counting wraps around the circle and may count some friends more than once.
3) The last friend you counted leaves the circle and loses the game.
4) If there is still more than one friend in the circle, go back to step 2 starting from the friend immediately clockwise of the friend who just lost and repeat.
5) Else, the last friend in the circle wins the game.
Given the number of friends, n, and an integer k, return the winner of the game.
*/

// Example :
/*
Input: n = 5, k = 2
Output: 3
Explanation: Here are the steps of the game:
1) Start at friend 1.
2) Count 2 friends clockwise, which are friends 1 and 2.
3) Friend 2 leaves the circle. Next start is friend 3.
4) Count 2 friends clockwise, which are friends 3 and 4.
5) Friend 4 leaves the circle. Next start is friend 5.
6) Count 2 friends clockwise, which are friends 5 and 1.
7) Friend 1 leaves the circle. Next start is friend 3.
8) Count 2 friends clockwise, which are friends 3 and 5.
9) Friend 5 leaves the circle. Only friend 3 is left, so they are the winner.
*/

// 1) We keep a boolean array to keep a track of our persons. 0 means alive and 1 means eliminated.
// Our base case becomes when there is only 1 person left.
// When there's only 1 person left , we just check who still has 1 left.
// Now we run a loop and keep doing index+1 and we take modulo 'n' to wrap around.
// If we encounter already eliminated person (marked as '1') , run a nested while loop to skip that index.
// We keep the outer loop running until we find our target.
// Now if we have n = 5 and k = 3 , then it says that person 0,1 skipped and 2 eliminated , so we just skipped/took k-1 steps instead of 'k'.
// Therefore we need to go k-1 steps instead of k steps.
// Also if k is too large like n = 6 and k = 10 then we move 9 steps at reach at index 3 (4th person) to kill.
// We used more than one iteration for this whereas this could have been done in just 1 round.
// So for that we take modulo of (k-1) also but with persons_left.
// Because 'n' is a fixed size. Each time we take (k-1)%n we will be counting extra persons/steps.
// Each time a person gets eliminated so we need to take modulo with persons_left so that we can get exact number of steps.
// E.g if we have n = 6 and k = 10 then (k-1)% n and (k-1)% persons_left give same answers so at first we move and eliminate the 4th person (Index 3).
// Now for the next turn we find (k-1)%n = 3 and (k-1)% persons_left = 4.
// See that we will always keep having 3 steps whereas now we have new k so we need to move 4 steps and we eliminate the person at index 2 (3rd person).
// (k-1)%n shows that there are still 'n' persons alive whereas (k-1)% persons_left shows that we are going circle between only the persons left.
// (k-1)%n if done in later rounds mean that we are still counting the same eliminated person.
// After we have eliminated a person , we find the next valid index that is not 1.
// We can return our index as index or index+1 depending on the answer they are asking as 0th or 1-based indexing.

// Time Complexity :
// The Recursive calls are from 'n' persons to 1 as each person is eliminated in each recursive call.
// So total calls are 'n'.
// In each call , we iterate upto at most 'n' for finding the index for killing the person and then 'n' for finding the next valid index.
// So total time : O(n^2)
// If we didn't handle large k , and iterated upto (k-1) all the time then time complexity would be O(nk)

// Space Complexity :
// Extra space we took was boolean array : O(n)
// Total recursive depth becomes : n
// Total Space : O(n) + O(n) = O(n)
int winner(int n, int k, vector<bool> &persons, int persons_left, int index)
{
    // Base Case : When only 1 person remains !
    if (persons_left == 1)
    {
        /*
        for (int i = 0; i < persons.size(); i++)
        {
            if (persons[i] == 0)
            {
                return i;
            }
        }
        */
        return index;
    }

    int kill = (k - 1) % persons_left; // Counting how many steps to take to reach the person to eliminate.
    while (kill--)
    {
        index = (index + 1) % n; // Move index and then wrap around
        // Skip index if a person is already eliminated.
        while (persons[index] == 1)
        {
            index = (index + 1) % n;
        }
    }
    persons[index] = 1; // We eliminate the person on the 'index'.

    // Now we find the index of the next valid person (this also finds the index of the last person remaining so we really don't need the for loop in the base case to find the index for the last person)
    while (persons[index] == 1)
    {
        index = (index + 1) % n;
    }
    return winner(n, k, persons, persons_left - 1, index);
}

// 2) Same logic but iterative :
// Time : O(n^2)
// Space : O(n)
int winnerIterative(int n, int k)
{
    vector<bool> persons(n, false); // false = alive, true = eliminated
    int persons_left = n;
    int index = 0;

    // Run until only 1 person remains
    while (persons_left > 1)
    {
        // Counting how many steps to take to reach the person to eliminate.
        int kill = (k - 1) % persons_left;

        // Advance 'kill' steps skipping already eliminated people
        while (kill--)
        {
            index = (index + 1) % n;
            while (persons[index] == 1)
            {
                index = (index + 1) % n;
            }
        }

        // Eliminate the person at 'index'
        persons[index] = 1;
        persons_left--;

        // Move to the next alive person to start the next round
        // This loop finds the index even for the last person so that we don't need the last for loop to find the winner index.
        while (persons[index] == 1)
        {
            index = (index + 1) % n;
        }
        /*
        if (persons_left > 1)
        {
            while (persons[index] == 1)
            {
                index = (index + 1) % n;
            }
        }
        */
    }

    // Find and return the winner's 0-based index
    // There's no issue placing this loop but it will do unnecessary work if we are finding the next index in our nested while for each person.
    // This for becomes necessary only when we are not finding the last person index in the upper nested while loop.
    /*
    for (int i = 0; i < n; i++)
    {
        if (persons[i] == 0)
        {
            return i;
        }
    }
    */
    return index;
}

// 3) Circular Queue Module Simulation :
// Time Complexity : O(n^2) with large 'k' handled otherwise O(nk)
// Space : O(n)
/*
int winner_queue(int n , int k)
{
    for (int i = 1; i <= n; i++)        // Start from i = 0 or i = 1 depending on the question asked.
    {
        q.push(i);
    }

    while (q.size() > 1)
    {
        // int cur_k = (k-1)%q.size()   // So we rotate only those times as needed (and handle if k is too large) and put i<cur_k in for loop.

        for (int i = 0; i < k - 1; i++)
        {
            q.push(q.front());
            q.pop();
        }
        q.pop();
    }
    return q.front();
}
*/

// 4) Recursion + Maths :

// We will use the magic of recursion here.
// Suppose we have n = 5 , k = 3. (0->1->2->3->4)
// Now if we call it for (n-1) = 4 and now we can access only (0->1->2->3)
// This is the exact same number when we eliminate by using n = 5 one gets eliminated.
// When n = 5 and k = 3 , and one gets eliminated we get : (0->1->3->4) and our next round starts from index 3
// When we call for n = 4 ,k=3 we have a structure of : (0->1->2->3) and here we start from index 0.
// Now we need to compare (0->1->2->3) and (0->1->3->4).
// In 0->1->2->3 , our index starts from 0.
// In 0->1->3->4 , our index starts from 3.
// We can map as :
// (0 with 3) , (1 with 4) , (2 with 0) , (3 with 1).
// Now we can get same answer from (0->1->2->3) as that of (0->1->3->4).
// This mapping can be done by adding 'k' in it and modding with 'n' and this time we can take modulo with 'n' because in each recursive call , 'n' decreases so its fine to take the modulo with 'n'.
// Because modulo with 'n' will save us from going out of bounds , and we can map 2 easily with 0 by (2+3)%5 = 0 or (3+3)%5 = 1 etc.

/*
Step-by-Step with n = 5, k = 3
Let's look at what each returned number actually means as we go upward:

winnerSpecial(1, 3) returns 0:
Meaning: In a circle of 1 person, the winner is at index 0.

winnerSpecial(2, 3) returns (0 + 3) % 2 = 1:
Meaning: In a circle of 2 people, index 0 from the n = 1 subproblem maps to index 1.

winnerSpecial(3, 3) returns (1 + 3) % 3 = 1:
Meaning: In a circle of 3 people, index 1 from the n = 2 subproblem maps to index 1.

winnerSpecial(4, 3) returns (1 + 3) % 4 = 0:
Meaning: In a circle of 4 people, index 1 from the n = 3 subproblem maps to index 0.

winnerSpecial(5, 3) returns (0 + 3) % 5 = 3:
Meaning: In the original circle of 5 people, index 0 from the n = 4 subproblem maps to index 3.
*/

// Time : O(n)
// Space : O(n)
int winnerSpecial(int n, int k)
{
    if (n == 1)
    {
        return 0;
    }
    // This still returns 0-based index , we can add 1 in our answer from where we call this function.
    return (winnerSpecial(n - 1, k) + k) % n;
}

// 5) Same logic but iterative :
// The iterative one works same by starting from index-0.
// We know that in only 1 person left there is winner index-0.
// So we keep ans = 0.
// Now we know that our mapping was (winner+k)%n where n was being decreased until 1.
// So we start from i = 2 <= 5 so it goes 2 to 5 and it will do the same as recursive one by (ans+k) Modulo i where i goes from 2 to n = 5 here.
// Our winner was index-0 in 1 person game and we mapped it to the game of 2,3,4 and 5 persons just like the recursive one.
// Time : O(n)
// Space : O(1)
int winnerSpecialIterative(int n, int k)
{
    int ans = 0; // Base case for 1 person (0-based index)
    for (int i = 2; i <= n; i++)
    {
        ans = (ans + k) % i;
    }
    return ans;
}

int main()
{
    int n = 5, k = 3;
    vector<bool> persons(n);
    cout << "Winner of the Game is : " << (winner(n, k, persons, n, 0)) + 1 << endl;

    return 0;
}