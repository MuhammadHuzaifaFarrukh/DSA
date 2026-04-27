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

    // 1)
    // Count Number of Nodes in both head1 and head2.
    // Now find extra nodes (if any).
    // Then move the max node head to the extra nodes space.
    // Then move both heads again until they become equal.
    // Time Complexity : O(n) , Space Complexity ; O(1)
    Node *getIntersectionNode(Node *head1, Node *head2)
    {
        Node *temp1 = head1, *temp2 = head2;
        int count1 = 0, count2 = 0;
        while (temp1)
        {
            temp1 = temp1->next;
            count1++;
        }
        while (temp2)
        {
            temp2 = temp2->next;
            count2++;
        }
        int k = max(count1, count2) - min(count1, count2);
        temp1=head1, temp2 = head2;
        while (count1 > count2)
        {
            temp1 = temp1->next;
            count1--;
        }
        while (count2 > count1)
        {
            temp2 = temp2->next;
            count2--;
        }
        while (temp1 != temp2)
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return temp1;
    }
    // No Need to update the tail (if you have).

    // 2) Join the last node of the list with either head1 or head2 (set to head1 here).
    // Now this becomes a loop in our list.
    // Now we start at head2 and try to find the starting of this loop which is actually our intersection point.
    // In case of no loop , there is no Y-shaped list


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