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

    // 1) Use an array to store elements and then again traverse list to store elements from array into list.
    // Time Complexity : O(n) and Space Complexity : O(n).
    Node *reverse_list_using_array(Node *head)
    {
        Node *temp = head;
        vector<int> ans;
        while (temp != nullptr)
        {
            ans.push_back(temp->data);
            temp = temp->next;
        }
        temp = head;
        int i = ans.size() - 1;
        while (temp != nullptr)
        {
            temp->data = ans[i];
            temp = temp->next;
            i--;
        }
        return head;
    }

    // 2) Another way is the same way we reverse an array by Two Pointer Approach.
    // But for that we will need to find the Last index each time in the loop before swapping.
    // So that makes it : Space Complexity : O(1) and Time Complexity : O(n^2).

    // 3) Reverse by reversing the Nodes
    // Space Complexity : O(1) and Time Complexity : O(N)
    Node *reverse_list(Node *head)
    {
        Node *newTail = head;

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

        this->head = prev;          // prev is the original tail/new head
        this->tail = newTail;       // newTail is the original head/new tail
        this->tail->next = nullptr; // Ensure the new tail points to null

        return this->head;
    }

    // 4) The Same Above method by using Recursion :
    // Space and Time Complexity : O(n)
    Node *reverse_list_by_recursion(Node *curr, Node *prev)
    {
        // Base Case: If we've reached the end
        if (curr == nullptr)
        {
            this->head = prev; // The last node we processed is the new head
            return prev;
        }

        // If this is the very first call, the current node is the new tail
        if (prev == nullptr)
        {
            this->tail = curr;
        }

        Node *future = curr->next;
        curr->next = prev;

        return reverse_list_by_recursion(future, curr);
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
};
int main()
{

    return 0;
}