#include <iostream>
#include <vector>

using namespace std;

// Generate all subsequences of a set.
// Like powerset (or combinations)
// E.g : ["abc"] -> [ ["a"] , ["b"] , ["c"] , ["ab"] , ["ac"] , ["bc"] , ["abc"] , [] ]
//  We can return answer in any order.
// Even the internal order won't matter here like "ab" = "ba".
// This is not a specific nCr , this is a powerset.
// The Powerset contains all the nCr like nC0 + nC1 + ... + nCn without any repetition.

// We generate all the subsets by taking a particular choice. "abc"
/*
                                   ()
                             /              \
                           ()                 (a)
                          /   \            /       \
                        ()    (b)         (a)       (ab)
                        /\     /\         /  \       / \
                       () (c) (b)(bc)   (a) (ac)  (ab) (abc)

*/
// If we say no , then we don't take a particular number and move on to the next index asking the same question.
// When we run out of the indices , then we backtrack.
// While backtracking , we then look for the 'yes' answers and for that we store our answer inside a temp array.
// For that 'yes' we can look for more 'no' or 'yes' if more indices left.
// We can pass temp string by value , then it takes more memory and we can also pass it as a reference (for that we need to pop_back() as well cause changes are made in only same temp string).
// temp string stores our each subset , and when it reaches leaf node , we can push it in our ans vector.

// Time : O(n*2^n)
// This loop grows for n = 3 , level 0 : 1
// Level 1 : 2 , Level 2 : 4 , Level 3 : 8 = 2^3
// So we sum all work done in each nodes which is constant.
// Sum of all nodes : 1+2+4+8+...+2^n = 2^(n+1) - 1 = O(2^n)
// But copying whole string inside 1D vector takes O(n) at worst case (because string is dynamic so it is copied into 1D vector char by char) or if reallocation happens.
// So its time comp becomes : n*2^n.
// If we neglect this push_back() operation as O(1) , then it takes time : O(2^n)

// Space : O(n*2^n)
// The maximum depth of the stack is n.
// When we look at the rightmost side , we can see all the yes answers , so temp stores our temporary one length increased in each level.
// So space taken  by temp in 'n' levels :
// 1 , 2, 3 , 4 ,....,n = O(n^2)
// Though this can be avoided and reduced to O(n) by using temp as reference vector.
// But Worst space taken for the subset can be atmost n by temp
// Our answer array stores upto 2^n powerset so we can suppose we have all the sets length n , then total space by 2D vector is :n*2^n and combining stack calls total space becomes : O(n*2^n) + O(n)
// Total Space : O(n*2^n)
void subSet(string &x, int index, int n, vector<string> &ans, string temp)
{
    if (index == n)
    {
        ans.push_back(temp);
        return;
    }
    subSet(x, index + 1, n, ans, temp); // Choice of No
    temp.push_back(x[index]);           // We stored this character , so we are taking it as a "YES" now
    subSet(x, index + 1, n, ans, temp);
    // We can write temp.pop_back() here if we are using reference string temp which saves memory and space.
}

int main()
{
    string n = "abc";
    vector<string> ans;
    string temp;
    subSet(n, 0, n.size(), ans, temp);

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
