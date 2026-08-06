#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int data = 0, Node *temp = nullptr) : data(data), next(temp) {}
};

class List
{
    Node *head;
    int size = 0;
    Node *tail;

public:
    List()
    {
        head = tail = nullptr;
        size = 0;
    }

    // 1) Put all the list elements inside vector and check the vector for palindrome.
    // Time : O(n) and Space : O(n).

    // 2) Reverse the linked list and then compare each node data side by side.
    // Time : O(n) and Space : O(n)

    // 3) Break list into two halves and reverse the 2nd half , then compare each one.
    // If No of Nodes are even then the halves are equal and we check till end.
    // If No of Nodes are odd then the 2nd half is +1 element so we check till end-1.
    // Time : O(n) and Space : O(1).
    bool isPalindrome(Node *head)
    {
        // Essential safety check for empty list
        if (!head)
        {
            return 1;
        }

        // 1. Count total nodes
        Node *temp = head;
        int count = 0;
        while (temp)
        {
            count++;
            temp = temp->next;
        }

        // 2. Find the end of the first half
        count /= 2;
        temp = head;
        count--;
        while (count > 0)
        {
            temp = temp->next;
            count--;
        }

        // 3. Split and reverse the second half
        Node *temp2 = temp->next;
        temp->next = nullptr; // disconnect first half

        temp2 = reverse_list(temp2);
        temp = head;

        // 4. Compare both halves
        while (temp && temp2)
        {
            if (temp->data != temp2->data)
            {
                return 0;
            }
            temp = temp->next;
            temp2 = temp2->next;
        }

        return 1;
    }

    // 4) Using slow/fast pointers to find the middle node :
    // Time : O(n)
    // Space : O(1)
    bool isPalindrome(Node *head)
    {
        // Empty list or single node list is always a palindrome
        if (!head || !head->next)
        {
            return 1;
        }

        Node *slow = head;
        Node *fast = head;
        Node *prev = nullptr;

        // 1. Find the middle node using fast & slow pointers
        while (fast && fast->next)
        {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }

        // 2. Disconnect the first half from the second half
        prev->next = nullptr;

        // 3. Reverse the second half (starts at slow)
        Node *second_half = reverse_list(slow);
        Node *first_half = head;

        // 4. Compare both halves
        while (first_half && second_half)
        {
            if (first_half->data != second_half->data)
            {
                return 0;
            }
            first_half = first_half->next;
            second_half = second_half->next;
        }

        return 1;
    }

    ~List()
    {
        clear_list();
    }
    void clear_list()
    {
        while (head)
            pop_front_list();
        head = tail = nullptr;
    }
    void pop_front_list()
    {
        if (!head)
            throw std::underflow_error("Underflow: List empty");
        Node *temp = head;
        head = head->next;
        if (!head)
            tail = nullptr;
        temp->next = nullptr;
        delete temp;
        size--;
    }

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
};
int main()
{

    return 0;
}
