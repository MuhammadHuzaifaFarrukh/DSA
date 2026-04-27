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

    // Time Complexity : O(n) , Space Complexity : O(n)
    // Done in more than 1 pass.
    // If lists are already given as reversed then no need to reverse them.
    Node *addTwoNumbers(Node *l1, Node *l2)
    {
        l1 = reverse_list(l1);
        l2 = reverse_list(l2);
        Node *newHead = new Node(0);
        Node *last = newHead;
        int carry = 0;
        Node *curr1 = l1;
        Node *curr2 = l2;
        while (curr1 && curr2)
        {
            int sum = curr1->data + curr2->data + carry;
            tail->next = new Node(sum % 10);
            tail = tail->next;
            carry = sum / 10;

            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        // If current 1 has more digits than current 2
        while (curr1)
        {
            int sum = curr1->data + carry;
            tail->next = new Node(sum % 10);
            tail = tail->next;
            carry = sum / 10;
            curr1 = curr1->next;
        }
        // If current 2 has more digits than current 1
        while (curr2)
        {
            int sum = curr2->data + carry;
            tail->next = new Node(sum % 10);
            tail = tail->next;
            carry = sum / 10;
            curr2 = curr2->next;
        }
        // If there is still carry and our lists have been added fully

        if (carry)
        {
            tail->next = new Node(carry % 10);
            // tail = tail->next;
            carry /= 10;
        }
        Node *chuwara = newHead;
        newHead = newHead->next;
        delete chuwara;
        return newHead;
    }
    // No Need to Update tail here , we are making a new head here.

    // Doing in 1 pass :
    // If lists are already given as reversed then no need to reverse them.
    // Time Complexity : O(n) , Space Complexity : O(n)
    /*

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        l1 = reverse_list(l1);
        l2 = reverse_list(l2);

        ListNode *new_node = new ListNode();
        ListNode *dummy = new_node;
        int sum = 0;
        int carry = 0;

        while (l1 || l2 || carry)
        {
            sum = carry;

            if (l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            sum = sum % 10;

            new_node->next = new ListNode(sum);
            new_node = new_node->next;
        }

        ListNode *head = dummy->next;
        delete dummy;

        return head;
    }
    // No Need to Update tail here , we are making a new head here.
    */

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