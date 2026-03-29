#include <iostream>
#include <string>

using namespace std;
int maxDepth(string s)
{
    int depth = 0;
    int max_depth = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            depth++;
            // max_depth = max(max_depth , depth);  // Both are valid (Either here or below)
        }
        else if (s[i] == ')')
        {
            max_depth = max(max_depth, depth);  // Both are valid (Either here or above)
            depth--;
        }
    }
    return max_depth;
}

int main()
{
    return 0;
}