#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node
{
public:
    int data;
    Node *next;
    Node(int val = 0, Node *next = nullptr) : data(val), next(next) {}

    void display(Node *head)
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << " NULL ";
        cout << endl;
    }

    // 1) Using Two Pointer Approach 
    // Time Complexity : O(n^2)
    // Space Complexity : O(1) 
    Node *removeZeroSumSublists(Node *head)
    {
        // 1. Create a dummy to handle cases where the head itself is part of a zero-sum
        Node *dummy = new Node(0, head);
        Node *start = dummy;

        while (start != nullptr)
        {
            int runningSum = 0;
            Node *end = start->next;

            while (end != nullptr)
            {
                runningSum += end->data;

                if (runningSum == 0)
                {
                    // 2. Found a zero-sum!
                    // We "jump" over the nodes from start->next to end.
                    start->next = end->next;
                    // Note: We don't break; we keep checking from the same 'start'
                    // in case there's another zero-sum sequence right after!
                }
                end = end->next;
            }
            // 3. Move the start pointer forward and repeat
            start = start->next;
        }

        Node *result = dummy->next;
        delete dummy;
        return result;
    }


    // 2) Using Map and Prefix Sum
    // Time : O(n) and Space : O(n).
    // If the prefix sum (the total sum from the start to the current node) is the same at two different points in the list, then the nodes between those two points must add up to exactly zero.
    // We record each prefix sum as key and its value being the current Node.

    // E.g : 1,2,3,-3,4
    // We see its prefix sum : 1,3,6,3,7
    // So 3 appears two times so we can say that after first 3 appears , the sum between next and the node where last 3 appears must be zero.
    // So we store this information in our map and it will update the last node to be stored only as our prefix sum key value.
    // It would store (3,Node(-3)) instead of (3,Node(2)).
    
    Node *removeZeroSumSublists(Node *head)
    {
        Node *dummy = new Node(0, head);
        unordered_map<int, Node *> m;
        int prefix = 0;

        // First pass: Record the LAST occurrence of each prefix sum
        for (Node *curr = dummy; curr != nullptr; curr = curr->next)
        {
            prefix += curr->data;
            m[prefix] = curr;
        }

        // Second pass: Connect nodes to the last known node with the same sum
        prefix = 0;
        for (Node *curr = dummy; curr != nullptr; curr = curr->next)
        {
            prefix += curr->data;
            curr->next = m[prefix]->next;
        }

        Node *result = dummy->next;
        delete dummy;
        return result;
    }
};

int main()
{
    Node *l1;
    Node *n1 = new Node(7);
    Node *n2 = new Node(2);
    Node *n3 = new Node(4);
    Node *n4 = new Node(3);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = nullptr;

    Node *n5 = new Node(5);
    Node *n6 = new Node(6);
    Node *n7 = new Node(4);

    return 0;
}
