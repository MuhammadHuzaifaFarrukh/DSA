#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1. (This tells that there must be atleast 2 nodes for twin nodes in linked list).

For example, if n = 4, then node 0 is the twin of node 3 (4-1-0), and node 1 is the twin of node 2 (4-1-1) . These are the only nodes with twins for n = 4.
The twin sum is defined as the sum of a node and its twin.

Given the head of a linked list with even length, return the maximum twin sum of the linked list.
*/

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

public:
    List()
    {
        head = nullptr;
    }
    void push_front_list(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void push_back_list(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void pop_front_list()
    {
        if (!head)
            return;

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back_list()
    {
        if (!head)
            return;

        if (!head->next)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node *temp = head;
            // Move to the second-to-last node
            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    // If we have a list : L0->L1->L2-> ... -> Ln-1->Ln Then it should be : L0->Ln->L1->Ln-1->...
    // E.g : 1->2->3->4->5->6->7->8->9->10 , then : 1->10->2->9->3->8->4->7->5->6
    void reorderList(Node *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            return;
        }

        Node *slow = head, *fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node *prev = nullptr;
        Node *curr = slow->next;
        slow->next = nullptr;

        while (curr != nullptr)
        {
            Node *nexttemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nexttemp;
        }

        Node *first = head;
        Node *second = prev;
        while (second != nullptr)
        {
            Node *temp1 = first->next;
            Node *temp2 = second->next;

            first->next = second;
            second->next = temp1;

            first = temp1;
            second = temp2;
        }
    }

    // 1) Using the Reorder Problem Solution.
    // We can see that if we have linked list 1->2->3->4->5->6 then
    // Node 0 twin is Node 5 , Node 1 twin is Node 4 , Node 2 twin is Node 3.
    // So this tells that we can use the reordering of the list.
    // If we use slow fast pointers to go to middle and then reverse the 2nd half.
    // Then we join the 2nd half elements each with first half each elements e.g it becomes : 1->6->2->5->3->4.
    // Now we can just loop and find our max twin sums by calculating sum pair wise as twins are side by side now.
    // Time : O(n) , Space : O(1)
    int pairSum(Node *head)
    {
        reorderList(head);
        Node *temp = head;
        int max_sum = INT_MIN;
        while (temp && temp->next)
        {
            int sum = temp->data + temp->next->data;
            if (sum > max_sum)
            {
                max_sum = sum;
            }
            temp = temp->next->next;
        }
        return max_sum;
    }

    // 2) Same Reordering but little different
    // We know that we have to reorder list.
    // We will reverse the 2nd half.
    // But now we will just take 1 pointer at 1st element and the other pointer at the 1st element of the reversed 2nd half.
    // E.g if our list was 1->2->3->4->5->6 then we have : 1->2->3->6->5->4 and our 1st pointer is at 1 and the other is at 6.
    // Now we just move them both to find sums.
    // Time : O(n) ,  Space : O(1)
    int pairSum2(Node *head)
    {
        // 1. Find the middle using slow/fast pointers
        Node *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. Reverse the second half
        Node *prev = nullptr, *curr = slow;
        while (curr)
        {
            Node *nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }

        // 3. Calculate max twin sum
        int maxSum = 0;
        Node *first = head;
        Node *second = prev; // 'prev' is now the head of the reversed second half

        while (second)
        {
            maxSum = max(maxSum, first->data + second->data);
            first = first->next;
            second = second->next;
        }

        return maxSum;
    }

    void print_list()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
int main()
{

    return 0;
}