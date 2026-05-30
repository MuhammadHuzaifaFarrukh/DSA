#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// This problem is actually a string/vectors problem but it can also be solved using linked list.
// At the end , there are two solutions using the strings/vectors.
// Below is the one with list.

class Solution
{
public:
    struct Node
    {
        string val;
        Node *next;
        Node(string val = "", Node *next = nullptr) : val(val), next(next) {}
    };
    Node *head;
    Node *tail;
    Node *reverse_list(Node *head)
    {
        Node *curr = head;
        Node *prev = nullptr;
        Node *future = nullptr;
        while (curr != nullptr)
        {
            future = curr->next;
            curr->next = prev;
            prev = curr;
            curr = future;
        }
        return prev;
    }

    // 3) We use linked list to store the words as nodes and then we reverse the list and copy the nodes into answer string.
    // This is not optimized because we need to allocate and use heap memory for each node creation.
    // This becomes complex to manage the pointers also.
    // Time : O(n) , Space : O(n)
    string reverseWords(string s)
    {
        head = tail = nullptr;
        string x = "";
        int start = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9'))
            {
                start = i;
                break;
            }
        }

        for (int i = start; i < s.size(); i++)
        {
            if (s[i] == ' ')
            {
                // We need to put this !x.empty() check because it avoids to add the node if our 'x' was empty which is the case when we input more than one spaces in between words.
                if (!x.empty())
                {
                    Node *newNode = new Node(x);
                    if (!head)
                    {
                        head = tail = newNode;
                    }
                    else
                    {
                        tail->next = newNode;
                        tail = newNode;
                    }
                    x = "";
                }
            }
            else
            {
                x += s[i];
            }
        }

        // Our last word was made but couldn't be as node because if there was no space as last word then loop exited without a node being created.
        // So we check if last index was space or not. If space then it means our last word was created and if not then we need to create this last word ourselves.
        // We can check either by string's last word is not space or by checking if the string 'x' is empty or not because 'x' should have some valid chars for that node creation and if node was created then 'x' would be empty.
        if (s[s.size() - 1] != ' ') // Here (!x.empty()) is also works
        {
            Node *newNode = new Node(x);

            if (!head)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
        head = reverse_list(head);
        Node *temp = head;
        x = "";
        while (temp->next)
        {
            x += temp->val;
            x += " ";
            temp = temp->next;
        }
        x += temp->val;
        return x;
    }
};
int main()
{
    Solution s1;
    string ans = s1.reverseWords(" hello world ");
    cout << " Reversed words :(->" << ans << "<-)" << endl;
    return 0;
}

// 1) :
// Use a vector of strings to maintain the words temporarily ,and then put back in the result string
// Time : O(n) , Space : O(n)

/*
    string reverseWords(string s)
    {
        vector<string> words;
        string temp = "";

        // Step 1: Extract words, ignoring all extra spaces
        for (char c : s)
        {
            if (c != ' ')
            {
                temp += c;
            }
            else
            {
                if (!temp.empty())
                {
                    words.push_back(temp);
                    temp = "";
                }
            }
        }

        // Don't forget the last word if it didn't end with a space
        if (!temp.empty())  // or use this : (s[s.size()-1] != ' ')
        {
            words.push_back(temp);
        }

        // Step 2: Reconstruct the string in reverse order
        string result = "";
        for (int i = words.size() - 1; i >= 0; i--)
        {
            result += words[i];
            if (i > 0)  // i == 0 is the first word which becomes last word for our answer.
            {
                result += " "; // Add space between words only
            }
        }
        return result;
    }
*/



// 2) Best Method (Two Pointers)
// We take the whole string and remove the unnecessary spaces from start , end , and in between if we find double spaces.
// Then we reverse the whole string.
// Then we reverse each word in our string.
// Time : O(n) , Space : O(1).
/*
string reverseWords(string s)
{
    int n = s.length();
    int left = 0;
    int right = 0;

    // Step 1: Clean up spaces using two pointers (left = write, right = read)
    while (right < n)
    {
        // Skip spaces
        while (right < n && s[right] == ' ')
        {
            right++;
        }

        // If we found a word, write it
        if (right < n)
        {
            // Add a single space before the word (but not before the very first word)
            if (left > 0)
            {
                s[left] = ' ';
                left++;
            }

            // Copy the word
            while (right < n && s[right] != ' ')
            {
                s[left] = s[right];
                left++;
                right++;
            }
        }
    }

    // Resize the string to cut off the trailing junk space/characters
    s.resize(left);

    // Step 2: Reverse the entire cleaned string
    reverse(s.begin(), s.end());

    // Step 3: Reverse each individual word back to normal
    int start = 0;
    for (int i = 0; i <= s.length(); i++)
    {
        // When we hit a space or the end of the string, we've found a word boundary
        if (i == s.length() || s[i] == ' ')
        {
            reverse(s.begin() + start, s.begin() + i);
            // You can do the manual reversing by reverse function by two pointers swapping of first and last characters until they meet
            // But in manual , you need to start the last pointer not from (0+i) but by (i-1) as this is the space or boundary and we don't want to reverse that.
            start = i + 1; // Move start pointer to the beginning of the next word
        }
    }

    return s;
}
*/
