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
    Node *tail;

public:
    List()
    {
        head = tail = nullptr;
    }

    // Partition lists such that nodes less than x (in value) come first.
    // Nodes greater or equal to x (in value) come next.
    // Only two partitions are possible.
    // Hence we make two dummies and keep making two lists from original 
    // Then we join them.
    // Time : O(n) and Space : O(1).
    // Here we don't need to check if the lists are null or not as we are using dummies and have only 2 parts of list.
    // In case of 3 partitions , we would check that also.
    Node *partition(Node *head, int x)
    {
        // Two dummy heads: one for the "Small" side, one for the "Large" side
        Node *smallHead = new Node(0);
        Node *largeHead = new Node(0);

        // Pointers to the current last node of each list
        Node *small = smallHead;
        Node *large = largeHead;

        Node *curr = head;
        while (curr)
        {
            if (curr->data < x)
            {
                small->next = curr;
                small = small->next;
            }
            else
            {
                // This handles BOTH >= x cases automatically
                large->next = curr;
                large = large->next;
            }
            curr = curr->next;
        }

        // 1. Terminate the large list to avoid cycles
        large->next = nullptr;

        // 2. Connect the end of small list to the start of large list
        small->next = largeHead->next;

        // 3. Save the actual head and cleanup dummies
        Node *result = smallHead->next;
        delete smallHead;
        delete largeHead;

        return result;
    }

    void push_front_list(int val)
    {
        Node *newNode = nullptr;
        try
        {
            newNode = new Node(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_front failed.");
        }

        if (!head)
        {
            head = tail = newNode;
            newNode->next = nullptr;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
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
    }
};
int main()
{

    return 0;
}