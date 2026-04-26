#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int val = 0, Node *ptr = nullptr) : data(val), next(ptr) {}
};

class LinkedList
{
    Node *head;
    Node *tail;

public:
    LinkedList() : head(nullptr) {}

    void insertAtHead(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        tail = newNode;
    }

    void pop_back_list()
    {
        if (head == nullptr)
        {
            cout << "List is empty " << endl;
        }
        else
        {
            Node *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            temp->next = nullptr;
            delete tail;
            tail = temp;
        }
        return;
    }
    void display()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    Node *getHead() { return head; }
    Node *&sethead()
    {
        return head;
    }
    ~LinkedList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    // 1) Use two pointer approach and keep comparing both lists elements and store them in a new list.
    // Time Complexity : O(min(M,N)) , Space Complexity : O(M+N)


    // 2) Using Existing Nodes Arranging (With Dummy Node also)
    // Time Complexity : O(min(M,N)) , Space Complexity : O(1)
    // Dummy nodes help us in this case a little bit.
    Node *merge_sorted_Lists(Node *another_head1, Node *another_head2)
    {
        Node *head = new Node(0);
        Node *curr = head;

        Node *head1 = another_head1;
        Node *head2 = another_head2;

        while (head1 && head2)
        {
            if (head1->data <= head2->data)
            {
                curr->next = head1;
                head1 = head1->next;
                curr = curr->next;
                curr->next = nullptr;
            }
            else
            {
                curr->next = head2;
                head2 = head2->next;
                curr = curr->next;
                curr->next = nullptr;
            }
        }
        if (head1)
        {
            curr->next = head1;
        }
        else
        {
            curr->next = head2;
        }

        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        this->tail = curr; // Update Tail pointer if you have

        curr = head;
        head = head->next;
        delete curr;
        return head;
    }

    /*
    // 3) Same as above method but with little changing. (Without Dummy Node)
    // Time Complexity : O(min(M,N)) , Space Complexity : O(1)
    Node* merge_sorted_Lists(Node* head1, Node* head2)
    {
        // 1. Initial Null Checks
        if(!head1 && !head2)
        {
            return nullptr;
        }

        if (!head1) return head2;
        if (!head2) return head1;

        Node* newHead = nullptr;

        // 2. Decide the first node (This fixes your curr = nullptr issue)
        if (head1->data <= head2->data)
        {
            newHead = head1;
            head1 = head1->next;
        }
        else
        {
            newHead = head2;
            head2 = head2->next;
        }

        Node* curr = newHead;

        // 3. The General Merge Loop
        while (head1 && head2)
        {
            if (head1->data <= head2->data)
            {
                curr->next = head1;
                head1 = head1->next;
            }
            else
            {
                curr->next = head2;
                head2 = head2->next;
            }
            curr = curr->next;
            // Note: Do NOT set curr->next = nullptr here, it breaks the chain!
        }

        // 4. Attach the remaining nodes (The "Leftovers")
        if (head1)
        {
            curr->next = head1;
        }
        else
        {
            curr->next = head2;
        }

        while (curr && curr->next != nullptr) 
        {
            curr = curr->next;
        }
        this->tail = curr;

        return newHead;
    }

    */
};

int main()
{

    return 0;
}