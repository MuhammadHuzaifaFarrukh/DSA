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

    // We use the Slow and Fast Pointers , to find the length of the loop
    // Time : O(n) and Space : O(1)
    // Once we know there exists a loop , we then count the number of nodes from that point.

    int length_of_cycle(Node *head)
    {
        Node *slow = head, *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            int count = 1;
            if (fast == slow)
            {
                while (slow->next != fast)
                {
                    slow = slow->next;
                    count++;
                }
                return count;
            }
        }
        return 0;
    }// No Need to update the tail (if you have).

    
    // Floyd Algorithm Formula : t = L + kC + m
    // Here t = total steps from head to now.
    // L is the linear distance from head starting to the head of the cycle.
    // C is the length of loop.
    // k is an integer representing how many full times the pointer has gone around that circle.
    // m is the meeting offset. This is the distance from the start of the loop to where the pointer is currently located.
    // It’s the "extra" bit after completing the last full lap.
    // E.g : Slow Pointer moves : t = L + k_1C + m and Fast Pointer moves : 2t = L + k_2C + m

    // To Find where they meet : we subtract them
    // (2t) - (t) = (L + k_2C + m) - (L + k_1C + m)
    // t = (k2-k1)C , This simplifies to : t is a multiple of C.

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