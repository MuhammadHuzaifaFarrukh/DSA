#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Node
{
public:
    Node *next;
    int val;
    Node(int data = 0, Node *ptr = nullptr) : val(data), next(ptr) {}
};

class Stack
{
    Node *topNode = nullptr;
    int _size = 0;

public:
    void push(int data)
    {
        Node *newNode = new Node(data, topNode);
        topNode = newNode;
        _size++;
    }
    int pop()
    {
        if (!topNode)
        {
            cout << "Stack is empty already" << endl;
            return -1;
        }
        Node *temp = topNode;

        int val = temp->val;
        topNode = topNode->next;
        temp->next = nullptr;
        delete temp;

        _size--;
        return val;
    }
    int peek()
    {
        if (!topNode)
        {
            cout << "Stack is empty already" << endl;
            return -1;
        }
        return (topNode->val);
    }
    bool isEmpty()
    {
        // Can check by size == 0
        if (!topNode)
        {
            return 1;
        }
        return 0;
    }
    void display()
    {
        Node *temp = topNode;
        if (temp == nullptr)
        {
            cout << "Stack is empty " << endl;
            return;
        }
        while (temp != nullptr)
        {
            cout << temp->val << " ";
            temp = temp->next;
        }
    }
    void clear()
    {
        while (topNode != nullptr)
        {
            pop();
        }
        --_size = 0;
    }
    ~Stack()
    {
        clear();
    }
};
int main()
{

    return 0;
}