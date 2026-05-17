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
    // We find the loop and then we move our pointer to start and then move the pointer where slow+fast met each other
    // Now where these pointers meet will be our starting point of loop.
    // Now once we get to the starting of loop , we move again from there right before the starting of the loop.
    // When we reach there , we cut off the loop.
    // Time Complexity : O(n) , Space Complexity ; O(1)
    void remove_loop(Node *head)
    {
        Node *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                break;
            }
        }
        if (!(fast && fast->next))
        {
            return;
        }
        slow = head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        while (slow->next != fast)
        {
            slow = slow->next;
        }
        slow->next = nullptr;
        this->tail = slow;      // Slow pointer is actually our tail.
    }

    // Why this works?
    // Suppose Slow Pointer : A + (B+C)i + B and Fast Pointer = A + (B+C)j + B
    // Where A = distance from starting to start of the loop
    // B = start of loop to point where they meet.
    // C = Point where they meet to the start of the loop.
    // (B+C) = Total Length of the Loop
    // (B+C)i or (B+C)j = Number of cycles.

    // Fast Pointer  = 2*Slow Pointer
    // Now equalize both equations :
    // A + (B+C)j + B  = 2A + 2(B+C)i + 2B
    // We get : A+B = (B+C)j - 2(B+C)i
    // A+B = (B+C)(j-2i)    // j>=2i or j>2i
    // A+B = T(B+C)         // This (j-2i) is the number of cycles so they don't matter.
    // A+B = (B+C)
    // A = C
    // This means that if we go starting of list to starting of head (A) then it is equal to the starting of loop to the point where both pointers meet (C).


    // 2) Another Method :
    // Detect the loop.
    // Now find total length of loop.
    // Move slow to head and fast total length of loop steps ahead of slow.
    // Now bring slow and fast equal.
    // Now move slow->next != fast 
    // Now cut off the loop.
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
