#include <iostream>

using namespace std;

/*
Conventional Doubly Linked Lists necessitate two distinct pointer fields per node to store the
memory addresses of their predecessor and successor. While highly versatile for bidirectional
traversal, this architectural design incurs a significant memory overhead, particularly in large
scale applications.

A sophisticated, memory-efficient alternative is the XOR Linked List. This data structure
compresses the two standard pointers into a single address field. By leveraging the bitwise XOR
(^) operator, each node stores the XORed value of the previous and next nodes' addresses. This
technique effectively halves the pointer memory requirements while fully preserving the ability to
traverse the list in both forward and backward directions.
*/

// The foundational structure of a memory-efficient doubly linked list node is defined below. The
// npx (Next-Previous XOR) pointer serves as the sole navigational link.
class Node
{
public:
    int data;
    Node *npx;
    Node(int val = 0, Node *npx = nullptr);
};
Node ::Node(int val, Node *npx) : data(val), npx(npx) {}

/*
The npx field dictates the traversal and structural integrity of the list.
During insertion or traversal operations, the precise address of the subsequent node is dynamically computed by XORing the
current node's npx value with the memory address of the previously visited node.
Example Scenario: When inserting a new node at the head of the list, its npx field is computed
as the XOR of NULL and the current head. Consequently, the former head's npx must be
updated to reflect the XOR of the newly inserted node and its subsequent neighbor and so on.
*/
class XORLinkedList
{
private:
    Node *head;
    Node *tail;

public:
    Node *XOR(Node *a = nullptr, Node *b = nullptr);
    XORLinkedList(Node *a = nullptr, Node *b = nullptr);
    void insertAtHead(int val);
    void insertAtTail(int val);
    int removeAtHead();
    int removeAtTail();
    bool search(int key);
    void print();
    ~XORLinkedList();

public:
};

Node *XORLinkedList ::XOR(Node *a, Node *b)
{
    return (Node *)((unsigned long long)(a) ^ (unsigned long long)(b));
}
XORLinkedList ::XORLinkedList(Node *a, Node *b) : head(a), tail(b) {}

void XORLinkedList ::insertAtHead(int val)
{
    Node *newNode = new Node(val);
    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        newNode->npx = XOR(nullptr, head);
        head->npx = XOR(newNode, XOR(nullptr, head->npx));
        head = newNode;
    }
}

void XORLinkedList ::insertAtTail(int val)
{
    Node *newNode = new Node(val);
    if (!tail)
    {
        head = tail = newNode;
    }
    else
    {
        newNode->npx = XOR(tail, nullptr);
        tail->npx = XOR(XOR(tail->npx, nullptr), newNode);
        tail = newNode;
    }
}

int XORLinkedList ::removeAtHead()
{
    if (!head)
        return -1;

    Node *toDelete = head;
    int val = toDelete->data;

    Node *nextNode = XOR(nullptr, head->npx);

    if (nextNode)
    {
        nextNode->npx = XOR(nullptr, XOR(head, nextNode->npx));
        head = nextNode;
    }
    else
    {
        head = tail = nullptr;
    }

    toDelete->npx = nullptr;
    delete toDelete;
    toDelete = nullptr;
    return val;
}

int XORLinkedList ::removeAtTail()
{
    if (!tail)
        return -1;

    Node *toDelete = tail;
    int val = toDelete->data;

    Node *prevNode = XOR(tail->npx, nullptr);

    if (prevNode)
    {
        prevNode->npx = XOR(XOR(prevNode->npx, tail), nullptr);
        tail = prevNode;
    }
    else
    {
        head = tail = nullptr;
    }

    toDelete->npx = nullptr;
    delete toDelete;
    toDelete = nullptr;
    return val;
}

bool XORLinkedList ::search(int key)
{
    Node *curr = head;
    Node *prev = nullptr;
    Node *next;

    while (curr)
    {
        if (curr->data == key)
        {
            return true;
        }
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    return false;
}

void XORLinkedList ::print()
{
    Node *curr = head;
    Node *prev = nullptr;
    Node *next;

    while (curr)
    {
        cout << curr->data << " ";
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    cout << endl;
}
XORLinkedList ::~XORLinkedList()
{
    Node *curr = head;
    Node *prev = nullptr;
    Node *next;

    while (curr != nullptr)
    {
        next = XOR(prev, curr->npx);
        prev = curr;
        curr->npx = nullptr;
        delete curr;
        curr = next;
    }
    head = tail = nullptr;
}

int main()
{
    XORLinkedList list;

    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtTail(30);

    cout << "Current List: ";
    list.print();

    cout << "Searching for 10: ";
    if (list.search(10))
    {
        cout << "Found " << endl;
    }
    else
    {
        cout << "Not Found " << endl;
    }

    list.removeAtHead();
    cout << "After removing head: ";
    list.print();

    return 0;
}