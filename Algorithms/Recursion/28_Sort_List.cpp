#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

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

public:
    List()
    {
        head = nullptr;
    }

    // Merge Sort for list :
    // We split the list using fast-slow pointers.
    // We then find the first middle and set its next to null for 2 parts of the list.
    // We keep doing that until we are left with empty list or only 1 element.
    // Now once we have the empty or 1 element left , we backtrack.
    // We take those already sorted 1 elements / or empty list and combined those 2 sorted lists into 1 sorted list.

    // Time Comp :
    // We are going at maximum depth of logn.
    // For Level 0 we have divided lists in no part , so we have 1 list.
    // For Level 1 , we have 2 lists. (n/2)
    // For Level 2 , we have 4 lists. (n/4)
    // For Level 3 , we have 8 lists and so on. (n/8)
    // We combine the lists using merge() function at each step into their total size times.
    // If we are coming up from level 3 , then we have to make 8 lists to 4 , so we take 2 lists of n/8 size and make them into n/4 size , similarly other 2 ,2,2 also made into n/4 size in time n/4 size at most.
    // So total size at level 3 to 2 for combining : n/4+n/4+n/4+n/4 = n.
    // Work done at each level : n
    // Total levels = logn
    // Time becomes : (Work done at each level)*(Total Levels) = (n)*(logn).

    // Space Comp :
    // Maximum Depth of our recursive stack goes to logn.
    // We aren't using any extra space , so our space can go max to logn

    // Time Comp : O(nlogn)
    // Space Comp : O(logn)
    Node *mergeSort(Node *head)
    {
        if (!head)
        {
            return nullptr;
        }
        if (!(head->next))
        {
            return head;
        }
        // Using Slow-Fast Pointers for finding middle of the list.
        // We need the node before 2nd middle element so we can set its next to null.
        // We can take the first middle element for finding correct middle or
        // We can just keep a previous pointer which always tells us the correct position of the node before 2nd middle.
        Node *slow = head, *fast = head->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node *head2 = slow->next;
        slow->next = nullptr;

        Node *leftHalf = mergeSort(head);
        Node *rightHalf = mergeSort(head2);
        return merge(leftHalf, rightHalf);
    }

    // This takes two sorted lists and gives us a combined sorted list.
    // This runs in time : O(l1+l2) = O(n) size.
    Node *merge(Node *another_head1, Node *another_head2)
    {
        Node *head = new Node(0);
        Node *curr = head;

        Node *head1 = another_head1;
        Node *head2 = another_head2;

        while (head1 && head2)
        {
            if (head1->data <= head2->data)
            {
                curr->next = head1;
                head1 = head1->next;
                curr = curr->next;
                curr->next = nullptr;
            }
            else
            {
                curr->next = head2;
                head2 = head2->next;
                curr = curr->next;
                curr->next = nullptr;
            }
        }
        if (head1)
        {
            curr->next = head1;
        }
        else
        {
            curr->next = head2;
        }
        curr = head;
        head = head->next;
        delete curr;
        return head;
    }

    // Iterative Merge Sort that has time complexity of O(nlogn) and Space of O(1)
    Node *sortList(Node *head)
    {
        if (!head || !head->next)
        {
            return head;
        }

        // 1. Count the total length of the list
        int length = 0;
        Node *curr = head;
        while (curr)
        {
            length++;
            curr = curr->next;
        }

        Node dummy(0);
        dummy.next = head;

        // 2. Double the step size on each pass: 1, 2, 4, 8, ...
        for (int step = 1; step < length; step *= 2)
        {
            Node *prev = &dummy;
            curr = dummy.next;

            // 3. Process the entire list for the current step size
            while (curr)
            {
                Node *left = curr;
                Node *right = split(left, step); // Get the right sublist
                curr = split(right, step);       // Get the start of the next pair

                prev->next = merge(left, right); // Merge them , from our merge 2 sorted lists.

                // Move prev to the end of the newly merged sublist
                while (prev->next)
                {
                    prev = prev->next;
                }
            }
        }

        return dummy.next;
    }
    Node *split(Node *head, int k)
    {
        if (!head)
        {
            return nullptr;
        }

        // Walk k-1 steps (since we are already at step 1 on 'head')
        for (int i = 1; head && i < k; ++i)
        {
            head = head->next;
        }

        if (!head)
        {
            return nullptr;
        }

        Node *remaining = head->next;
        head->next = nullptr; // Sever the connection!
        return remaining;
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