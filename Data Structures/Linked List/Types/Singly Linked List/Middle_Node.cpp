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

    // Middle Nodes in Odd Nodes Case is the middle one.
    // In Even Nodes Case , we have two middle nodes so we select the 2nd one.

    // 1) Brute Force
    // We use a counter variable to count total nodes , and then count/2 and then again traverse list.
    // Space Complexity : O(1) and Time Complexity : O(N).
    Node *middle_node(Node *head)
    {
        int count = 0;
        Node *temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
            count++;
        }
        count /= 2;
        temp = head;
        while (count--)
        {
            temp = temp->next;
        }
        return temp;
    }

    // 2) Tortoise and Hare Algorithm (Fast and Slow Pointers)
    // We use two pointers fast and slow. Fast moves 2 steps and slow moves 1 step at a time.
    // By the time fast reaches end of the list , slow is at middle.
    // This requires us to do in 1 pass only.
    // Space Complexity : O(1) and Time Complexity : N/2 = O(N).
    Node *middle_node(Node *head)
    {
        Node *slow = head;
        Node *fast = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
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