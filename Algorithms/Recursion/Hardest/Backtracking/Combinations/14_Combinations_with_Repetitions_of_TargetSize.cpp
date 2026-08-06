#include <iostream>
#include <unordered_map>
#include <climits>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// We are given a vector and some target size.
// We have to generate repeated combinations of the vector with same size as that of the targetSize.
// We have to use the same element multiple times to generate combinations.
// E.g : {1,2,3} and targetSize = 6 , we get : (n+k-1)Ck = (3+6-1)C6 = 8C6 = 28 Combinations
/*
1 1 1 1 1 1
1 1 1 1 1 2
1 1 1 1 1 3
1 1 1 1 2 2
1 1 1 1 2 3
1 1 1 1 3 3
1 1 1 2 2 2
1 1 1 2 2 3
1 1 1 2 3 3
1 1 1 3 3 3
1 1 2 2 2 2
1 1 2 2 2 3
1 1 2 2 3 3
1 1 2 3 3 3
1 1 3 3 3 3
1 2 2 2 2 2
1 2 2 2 2 3
1 2 2 2 3 3
1 2 2 3 3 3
1 2 3 3 3 3
1 3 3 3 3 3
2 2 2 2 2 2
2 2 2 2 2 3
2 2 2 2 3 3
2 2 2 3 3 3
2 2 3 3 3 3
2 3 3 3 3 3
3 3 3 3 3 3
*/

// This logic is the same as generating nCk with repetitions.
// We will use include exclude principle.
// First we take a value as a choice of "YES" and stay on the same index.
// Then we don't take the value and move to next index as choice of "NO".
// If we reach out of bounds , then we return.
// If we've reached our targetSize then we print it (or save it in another 2D vector).

// Time Complexity :
// Since repeated combinations take O( (n+k-1)Ck ) , its time is also O((n+k-1)Ck)

// Space Complexity :
// We aren't using any extra space to save answers.
// The deepest the call stack can go occurs when we take an element k times, and then skip elements until we run out of bounds (n times).
// The maximum stack frames piled up at once is n+k
// In the absolute deepest branch of our recursion, temp will hold exactly k elements which uses O(K) space.
// Total Space : O(n+k).
void combinations(vector<int> &v, vector<int> &temp, int index, int targetSize)
{
    // Base Case 1: If our combination reaches the double size (6), we are done
    if (temp.size() == targetSize)
    {
        for (int i : temp)
        {
            cout << i << " ";
        }
        cout << endl;
        return;
    }

    // Base Case 2: If we run out of elements in the vector v, stop.
    if (index == v.size())
    {
        return;
    }

    // --- CHOICE 1: TAKE the current element ---
    temp.push_back(v[index]);
    combinations(v, temp, index, targetSize);
    temp.pop_back(); // Backtrack

    // --- CHOICE 2: DON'T TAKE the current element ---
    combinations(v, temp, index + 1, targetSize);
}
int main()
{
    vector<int> v = {1, 2, 3};
    vector<int> temp;
    int targetSize = 2 * v.size();
    combinations(v, temp, 0, targetSize);

    return 0;
}