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

public:
    Node *head;
    int size = 0;
    Node *tail;
    List()
    {
        head = tail = nullptr;
        size = 0;
    }

    void push_front_list(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // 1) Use an array to store elements and then again traverse list to store elements from array into list.
    // Time Complexity : O(n) and Space Complexity : O(n).
    Node *reverse_list_using_array(Node *head)
    {
        Node *temp = head;
        vector<int> ans;
        while (temp != nullptr)
        {
            ans.push_back(temp->data);
            temp = temp->next;
        }
        temp = head;
        int i = ans.size() - 1;
        while (temp != nullptr)
        {
            temp->data = ans[i];
            temp = temp->next;
            i--;
        }
        return head;
    }

    // 2) Another way is the same way we reverse an array by Two Pointer Approach.
    // But for that we will need to find the Last index each time in the loop before swapping.
    // So that makes it : Space Complexity : O(1) and Time Complexity : O(n^2).

    // 3) Reverse by reversing the Nodes
    // Space Complexity : O(1) and Time Complexity : O(N)
    Node *reverse_list(Node *head)
    {
        Node *newTail = head;

        Node *curr = head;
        Node *prev = nullptr;
        Node *future = nullptr;
        while (curr != nullptr)
        {
            future = curr->next;
            curr->next = prev;
            prev = curr;
            curr = future;
        }

        this->head = prev;          // prev is the original tail/new head
        this->tail = newTail;       // newTail is the original head/new tail
        this->tail->next = nullptr; // Ensure the new tail points to null

        return this->head;
    }

    // 4) The Same Above method by using Recursion :
    // We reverse the nodes first then make a recursive call to find the head.
    // Space and Time Complexity : O(n)
    Node *reverse_list_by_recursion(Node *curr, Node *prev)
    {
        // Base Case: If we've reached the end
        if (curr == nullptr)
        {
            this->head = prev; // The last node we processed is the new head
            return prev;
        }

        // If this is the very first call, the current node is the new tail
        // Write this only if we have tail pointer in our list.
        // if (prev == nullptr)
        // {
        //     this->tail = curr;
        // }

        Node *future = curr->next;
        curr->next = prev;

        return reverse_list_by_recursion(future, curr);
    }

    // 4b) Same as above but just a little modification :
    // We do reversing from the last node to the first.
    // We go till the end of the last to get the head of the reversed linked list and then we start reversing.
    // Time and Space : O(n)
    Node *reverse_list_by_recursion2(Node *curr, Node *prev)
    {
        // Base Case: If we've reached the end
        if (curr == nullptr)
        {
            this->head = prev; // The last node we processed is the new head
            return prev;
        }

        // If this is the very first call, the current node is the new tail
        // Write this only if we have tail pointer in our list.
        // if (prev == nullptr)
        // {
        //     this->tail = curr;
        // }

        // We call recursive function first and then we reverse nodes.
        Node *newHead = reverse_list_by_recursion2(curr->next, curr);
        curr->next = prev;

        return newHead;
    }

    ~List()
    {
        clear_list();
    }
    void clear_list()
    {
        while (head)
        {
            pop_front_list();
        }
        head = tail = nullptr;
    }
    void pop_front_list()
    {
        if (!head)
        {
            throw std::underflow_error("Underflow: List empty");
        }
        Node *temp = head;
        head = head->next;
        if (!head)
        {
            tail = nullptr;
        }
        temp->next = nullptr;
        delete temp;
        size--;
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
    List l1;
    l1.push_front_list(5);
    l1.push_front_list(4);
    l1.push_front_list(3);
    l1.push_front_list(2);
    l1.push_front_list(1);
    l1.head = l1.reverse_list_by_recursion(l1.head, nullptr);
    l1.print_list();
    return 0;
}
