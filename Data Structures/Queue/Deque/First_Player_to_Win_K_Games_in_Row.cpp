#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
A competition consists of n players numbered from 0 to n - 1.

You are given an integer array skills of size n and a positive integer k, where skills[i] is the skill level of player i.
All integers in skills are unique.
All players are standing in a queue in order from player 0 to player n - 1.

The competition process is as follows:
The first two players in the queue play a game, and the player with the higher skill level wins.
After the game, the winner stays at the beginning of the queue, and the loser goes to the end of it.
The winner of the competition is the first player who wins k games in a row.
Return the initial index of the winning player.

Input: skills = [4,2,6,3,9], k = 2

Output: 2

Explanation:
Initially, the queue of players is [0,1,2,3,4]. The following process happens:
Players 0 and 1 play a game, since the skill of player 0 is higher than that of player 1, player 0 wins. The resulting queue is [0,2,3,4,1].
Players 0 and 2 play a game, since the skill of player 2 is higher than that of player 0, player 2 wins. The resulting queue is [2,3,4,1,0].
Players 2 and 3 play a game, since the skill of player 2 is higher than that of player 3, player 2 wins. The resulting queue is [2,4,1,0,3].
Player 2 won k = 2 games in a row, so the winner is player 2.
*/

// 1) By using Deque.
// We push all the indices inside the deque.
// We try to find the winner of the game by traversing the loop.
// We keep the always out and then start the battle.
// We wait for someone's consecutive wins to occur.
// If our winner wins , then we push_back() the opponent and we increase the consecutive wins as well.
// If our winner loses , then we push_back() this one and our opponent becomes the new winner and we reset the consecutive wins to 1.
// So this is the normal case because if we have total 5 players then 'k' in general should be at most 5-1 = 4.
// This means that a player needs to beat atmost n-1 people to win because nth person is the player himself.
// But some platforms can give us a huge value of 'k'.
// That means that in this case , our answer is guaranteed to be the player with max skills.
// Because no matter how much we iterate , max skilled player is always gonna beat everyone any number of times.

// Time : O(n)  (Although if we have k<n and skilled player is at last then it may take n-1 turns for max skilled to come and then n-1 turns for him to beat so O(n-1+n-1) = O(2n-2) = O(n))
// Space : O(n) (Deque)

int findWinningPlayer(vector<int> &skills, int k)
{
    int n = skills.size();

    // Edge case: No one needs more than n - 1 wins
    if (k >= n - 1)
    {
        int maxIdx = 0;
        for (int i = 1; i < n; i++)
        {
            if (skills[i] > skills[maxIdx])
            {
                maxIdx = i;
            }
        }
        return maxIdx;
    }

    deque<int> dq;
    for (int i = 0; i < n; i++)
    {
        dq.push_back(i);
    }

    int current_winner = dq.front();
    dq.pop_front();
    int consecutive_wins = 0;

    while (consecutive_wins < k)
    {
        int challenger = dq.front();
        dq.pop_front();

        if (skills[current_winner] > skills[challenger])
        {
            // Winner DOES NOT go into dq; only loser goes to back!
            dq.push_back(challenger);
            consecutive_wins++;
        }
        else
        {
            // Loser goes to back, new winner takes over
            dq.push_back(current_winner);
            current_winner = challenger;
            consecutive_wins = 1;
        }
    }

    return current_winner;
}

// 2) Using the same logic without deque.
// Now we know that if 'k' is too large we just need n-1 beats.
// Else we need only 'k' beats.
// Also when we traverse a vector using index i to n, the next challenger automatically comes so there is really no need of deque.
// Now if in an array (4,2,6,3,9) k=4, 9 is the one that beats everyone , but it won't have enough victories , still we know if its like this maximum value or the current winner at that time will be the final winner.
// However if k is less than n-1 , then perhaps we can find someone other than the maximum element that gets enought victories equal to k.
// Time : O(n)
// Space : O(1)
int findWinningPlayer(vector<int> &skills, int k)
{
    int n = skills.size();
    // Wrapping k: No one ever needs more than n - 1 wins,
    // because beating n - 1 people means beating EVERYONE.
    int target_wins = min(k, n - 1);

    int current_winner = 0;
    int consecutive_wins = 0;

    for (int challenger = 1; challenger < n; challenger++)
    {
        if (skills[current_winner] > skills[challenger])
        {
            consecutive_wins++;
        }
        else
        {
            current_winner = challenger;
            consecutive_wins = 1;
        }

        if (consecutive_wins == target_wins)
        {
            break;
            // return current_winner;
        }
    }

    return current_winner;
}
int main()
{
    int k = 2;
    vector<int> v = {4, 2, 6, 3, 9};
    cout << "Player who won (index) : " << findWinningPlayer(v, k) << endl;
    return 0;
}