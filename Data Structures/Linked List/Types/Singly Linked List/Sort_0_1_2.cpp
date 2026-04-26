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

    // Sort only a list which contains either 0,1,2.
    // Count the number of 1,2,0
    // Then place them in the list.
    // Time : O(n) and Space : O(1).
    Node *sort012(Node *curr)
    {
        curr = head;
        int count1 = 0, count2 = 0, count0 = 0;
        while (curr != nullptr)
        {
            curr = curr->next;
            if (curr->data == 0)
            {
                count0++;
            }
            else if (curr->data == 1)
            {
                count1++;
            }
            else if (curr->data == 2)
            {
                count2++;
            }
        }
        curr = head;

        for (int i = 0; i < count0 && curr != nullptr; i++)
        {
            curr->data = 0;
            curr = curr->next;
        }
        for (int i = 0; i < count1 && curr != nullptr; i++)
        {
            curr->data = 1;
            curr = curr->next;
        }
        for (int i = 0; i < count2 && curr != nullptr; i++)
        {
            curr->data = 2;
            curr = curr->next;
        }
        return head;
    }

    // 2) This method uses 3 head pointers.
    // We use the dummy pointers also to keep edge cases simple.
    // This allows us to change the nodes instead of changing values.
    // Time : O(N) , Space : O(1)
    void sort012()
    {
        if (!head || !head->next)
            return;

        // 1. Create dummy nodes on the stack (safer for PUCIT standards)
        Node zeroDummy(0), oneDummy(0), twoDummy(0);
        Node *zero = &zeroDummy, *one = &oneDummy, *two = &twoDummy;

        // 2. Partition the nodes
        Node *curr = head;
        while (curr)
        {
            if (curr->data == 0)
            {
                zero->next = curr;
                zero = zero->next;
            }
            else if (curr->data == 1)
            {
                one->next = curr;
                one = one->next;
            }
            else
            {
                two->next = curr;
                two = two->next;
            }
            curr = curr->next;
        }

        // 3. Connect the three chains
        // Connect zeros to ones (if ones exist, else connect to twos)
        if (zero->next == oneDummy.next)
        {
            zero->next = oneDummy.next;
        }
        else
        {
            zero->next = twoDummy.next;
        }

        // Connect ones to twos
        one->next = twoDummy.next;

        // Ensure the last node points to NULL
        two->next = nullptr;

        // 4. Update class-level Head and Tail
        this->head = (zeroDummy.next) ? zeroDummy.next : (oneDummy.next ? oneDummy.next : twoDummy.next);

        // Find the new tail
        if (two != &twoDummy)
            this->tail = two;
        else if (one != &oneDummy)
            this->tail = one;
        else
            this->tail = zero;
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
};

int main()
{
    LinkedList l1;
    l1.insertAtHead(4);
    l1.insertAtHead(3);
    l1.insertAtHead(3);
    l1.insertAtHead(2);
    l1.insertAtHead(1);
    l1.insertAtHead(1);

    cout << "Before : " << endl;
    l1.display();
    LinkedList l2;
    // l1.deleteDuplicates(l1.getHead());
    cout << "After : " << endl;
    l1.display();

    return 0;
}