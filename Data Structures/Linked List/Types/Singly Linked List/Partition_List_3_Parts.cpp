#include <iostream>
#include <vector>
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

    // Partition lists such that nodes less than x (in value) come first.
    // Then nodes equal to x (in value) come next.
    // Nodes greater to x (in value) come next.
    // Only 3 partitions are possible.
    // Hence we make 3 dummies and keep making 3 lists from original
    // Then we join them.
    // Time : O(n) and Space : O(1).
    // Here we must check if the lists are null or not.

    // We join greater to null.
    // Then we join equal to greater and less to equal.
    // We must check for null because if equal is null while greater is not then joining less to equal will make us lose greater one etc.

    Node *partition(Node *head, int x)
    {
        // Create three dummy nodes to act as starting points
        Node *lessHead = new Node(0);
        Node *equalHead = new Node(0);
        Node *greaterHead = new Node(0);

        // Keep track of the current end (tail) of each list
        Node *less = lessHead;
        Node *equal = equalHead;
        Node *greater = greaterHead;

        Node *curr = head;
        while (curr != nullptr)
        {
            if (curr->data < x)
            {
                less->next = curr;
                less = less->next;
            }
            else if (curr->data == x)
            {
                equal->next = curr;
                equal = equal->next;
            }
            else
            {
                greater->next = curr;
                greater = greater->next;
            }
            curr = curr->next;
        }

        // IMPORTANT: Set the end of the last list to NULL to prevent cycles
        greater->next = nullptr;

        // Connect the three chains
        // Chain: Less -> Equal -> Greater
        equal->next = greaterHead->next;
        if (equalHead->next)
        {
            less->next = equalHead->next;
        }
        else
        {
            less->next = greaterHead->next;
        }

        // Get the actual head of the new list
        Node *result;
        if (lessHead->next)
        {
            result = lessHead->next;
        }
        else
        {
            /*
            if(equalHead->next)
            {
                result = equalHead->next;
            }
            else
            {
                result = greaterHead->next;
            }
            */
            result = equalHead->next;       // This assignment actually does what above if-else does. As we know that equalhead->next will be pointing to greater->next even if equalhead is empty or not, we still have a dummy node. So joining result with equalhead->next works if it exists or it doesn't.
        }

        // Clean up dummy nodes (don't delete the nodes they point to!)
        delete lessHead;
        delete equalHead;
        delete greaterHead;

        return result;
    }
};

int main()
{
    Node *l1;
    Node *n1 = new Node(5);
    Node *n5 = new Node(4);
    Node *n6 = new Node(3);

    n1->next = n5;

    n5->next = n6;
    n6->next = nullptr;
    int x = 3;

    l1 = n1;
    l1->display(l1);
    Node *naya = l1->partition(l1, x);
    naya->display(naya);

    return 0;
}
