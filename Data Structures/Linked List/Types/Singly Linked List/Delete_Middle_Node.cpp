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

    // 1) We can delete the middle node by checking whole of its length and then running a loop again to go to (length/2).
    // Time : O(n) and Space : O(1)

    
    // 2) Slow and Fast Pointers (More Efficient)
    // We use slow and fast pointers to go to the middle of the list.
    // We also initialize a node that is previous to the slow pointer everytime.
    // Once the loop ends , slow ptr is at middle and prev ptr is right behind it.
    // Now we can simply delete by managing pointers.
    // Time : O(n) and Space : O(1).
    Node *deleteMiddle(Node *head)
    {
        if (!head->next)
        {
            return nullptr;
        }
        Node *slow = head, *fast = head, *prev;
        while (fast && fast->next)
        {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = slow->next;
        slow->next = nullptr;
        delete slow;
        return head;
    }
};
int main()
{

    return 0;
}