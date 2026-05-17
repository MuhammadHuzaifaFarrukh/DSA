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

    // Detect Loop in a Linked List.
    // 1) Use a vector to keep check of the nodes that were visited , by their pointers
    // Vector < Node *> and then check each node if it was visited or not.
    // If we find such , then there exists a loop in the linked list.
    // If not , it is a singly list only.
    // Time Complexity : O(N^2) and Space Complexity : O(N)
    bool hasCycle(Node *head)
    {
        vector<Node *> visited;
        Node *curr = head;
        while (curr != nullptr)
        {
            for (int i = 0; i < visited.size(); i++)
            {
                if (curr == visited[i])
                {
                    return 1;
                }
            }
            visited.push_back(curr);
            curr = curr->next;
        }
        return 0;
    }// No Need to update the tail (if you have).

    // 2) Use the same method but with unordered maps.
    // Time Complexity : O(N) and Space Complexity : O(N)
    bool hasCycle(Node *head)
    {
        unordered_map<Node *,bool> visited;
        Node *curr = head;
        while (curr != nullptr)
        {
            if(visited[curr] == 1)
            {
                return 1;
            }
            visited[curr] = 1; 
            curr = curr->next;
        }
        return 0;
    }// No Need to update the tail (if you have).

    // 3) Floyd Algorithm (Fast and Slow Pointer)
    // Time Complexity : O(N) and Space Complexity : O(1)
    // We usually keep slow pointer at one step and fast pointer at two steps.
    // But this can also be done if fast pointer moves at 2 or more steps.
    // However , in that way , the time complexity may decrease even though being O(N) because the fast pointer is moving too many nodes more.

    // E.g : 2t - 1t (mod C) = 0 => 1t mod C = 0 in our standard version. (2 Jumps for fast)
    // That means that we find the slow and fast pointers equal at a multiple of Cycle Length.
    // If 3t - 1t (mod C) = 0 => 2t mod C = 0 , in other versions. ( 3 or more Jumps for fast)
    // That means that we find the slow and fast pointers equal at a multiple of Cycle Length.
    
    // Suppose we have nodes 1-10 and 10 joins to 4 with loop length = 7.
    // Then for 1t mod C , both become equal at node 7 , fast travels total (14+1) and slow travels 7 nodes.
    // For 2t mod C , both become equal at node 7 (Since gcd(2,7) = 1), fast  travels (21+1) and slow travels only 7 nodes.
    // Fast covers nodes at rate of almost 7/2 = 3.5 ~ 3 nodes per each slow one.
    bool hasCycle(Node *head)
    {
        Node *slow = head , *fast = head;
        while(fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast)
            {
                return 1;
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
    
    // To Find at which step will they meet from start of the list : we subtract them
    // (2t) - (t) = (L + k_2C + m) - (L + k_1C + m)
    // t = (k2-k1)C , This simplifies to : t is a multiple of C.
    // This shows that fast pointer will complete k2 iterations of the loop and slow pointer k1 , when they both meet at point 't' from start to the 't' point.
    // This shows the only difference is the k2 and k1 between these pointers to meet , other things are all same.
    

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
