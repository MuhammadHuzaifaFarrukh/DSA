#include <iostream>
#include <string>
#include <stack>

using namespace std;

// We want to reverse the output of elements popped out of the stack that were pushed.
// E.g : We push in order : 9,5,6,4,2 inside stack , top element of stack is 2 right now.
// Now we want that when we pop out , the output must be : 9,5,6,4,2 (Top of stack is 9 here) instead of 2,4,6,5,9 (Top of stack is 2 here).
// We reverse the output.

// 1)
// First we are clearing our stack , by calling all the elements out.
// Suppose we have elements 9,5,6,4,2 and we popped each one out by calling the function .
// Now that the stack is empty , now we take the last value and call another function insertAtBottom that takes the last value and puts it at its correct place.
// It takes 9 and places in the stack , now its done its work and call goes back to the reversal function , and then it calls insertAtBottom function with value 5 and takes the value 5 to insert it at its correct place.
// But it sees that stack is not empty yet , so it clears the stack and puts this element 5 , then it puts the other elements of stack. So it places 9,5 in the stack.
// Now its going to place the 3rd element 6 at its correct place but sees 9,5 already there inside stack so it clears the stack and places 6 there and then it places 5 then 9 making it 9,5,6 (Top of stack is 9 here).
// Now it takes 4 and clears the stack first , and then places 4 inside it , then it places the 6, then 5, and then 9 making it 9,5,6,4.
// Now it comes at the last element 2 and it has to insert it , so it clears out the stack and places 2 at the bottom and maintains the stack by pushing all other elements once again making it 9,5,6,4,2.
// So insertAtBottom , takes an element , and inserts it at the bottom of the stack no matter how many elements there are.
// We use this insertAtBottom on each element in the stack but in reversed order , so each element in forward order is put in the end making the stack reversed.
// In 9,5,6,4,2 (Where top is 2) , we inserted 2 at the bottom at the last because we know that top of the stack has to be the last element in the reversed order.

// Time Complexity : O(n^2)
// Each time we insert an element in the bottom , it takes linear calls.
// When we inserted 9 at the bottom , it did in 1 call , for inserting 5 , it took 2 calls , for inserting 6 , it took 3 calls , for inserting 4 it took 4 calls and for inserting 5 it took 5 calls.
// So we can see that for inserting 1 element : 1 Call
// Inserting 2nd Element : 2 Calls.
// Inserting 3rd Element : 3 Calls.
// Inserting Nth Element : N Calls
// Sum up : 1 + 2 + 3 +...+ n = n(n+1)/2 = O(n^2)

// The Space Complexity is still O(n) in this recursive version because for inserting the last element there are total n+1 max calls in the stack so it becomes O(n).

void insertAtBottom(stack<int> &s, int val)
{
    if (s.empty())
    {
        s.push(val);
        return;
    }
    int topVal = s.top();
    s.pop();
    insertAtBottom(s, val);
    s.push(topVal);
}

void reverse_rec(stack<int> &s)
{
    if (s.empty())
    {
        return;
    }

    int topVal = s.top();
    s.pop();
    reverse_rec(s);
    insertAtBottom(s, topVal);
}

// 2)
// This function uses another stack making space complexity O(n).
// Time : O(n)
// This is the best and efficient version.
stack<int> reverse(stack<int> &a)
{
    stack<int> b;
    while (!a.empty())
    {
        b.push(a.top());
        a.pop();
    }
    return b;
}

int main()
{
    stack<int> s;

    s.push(9);
    s.push(6);
    s.push(5);
    s.push(4);
    s.push(2);
    s.push(1);

    s = reverse(s);
    // reverse_rec2(s);

    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}