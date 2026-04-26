#include <iostream>
#include <string>
#include <vector>
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
    LinkedList() : head(nullptr), tail(nullptr) {}

    void insertAtHead(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
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

    // If we have a list : L0->L1->L2-> ... -> Ln-1->Ln Then it should be : L0->Ln->L1->Ln-1->...
    // E.g : 1->2->3->4->5->6->7->8->9->10 , then : 1->10->2->9->3->8->4->7->5->6
    void reorderList(Node *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            return;
        }

        Node *slow = head, *fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node *prev = nullptr;
        Node *curr = slow->next;
        slow->next = nullptr;

        while (curr != nullptr)
        {
            Node *nexttemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nexttemp;
        }

        Node *first = head;
        Node *second = prev;
        while (second != nullptr)
        {
            Node *temp1 = first->next;
            Node *temp2 = second->next;

            first->next = second;
            second->next = temp1;

            first = temp1;
            second = temp2;
        }

        // Finding Tail :
        Node *temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
        }
        this->tail = temp;
    }
};

int main()
{
    LinkedList l1;
    l1.insertAtHead(10);
    l1.insertAtHead(9);
    l1.insertAtHead(8);
    l1.insertAtHead(7);
    l1.insertAtHead(6);
    l1.insertAtHead(5);
    l1.insertAtHead(4);
    l1.insertAtHead(3);
    l1.insertAtHead(2);
    l1.insertAtHead(1);
    l1.insertAtHead(0);
    cout << "Before : " << endl;
    l1.display();
    cout << "After : " << endl;
    l1.reorderList(l1.getHead());
    l1.display();

    return 0;
}
