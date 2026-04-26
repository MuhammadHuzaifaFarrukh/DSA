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

class Queue
{
    Node *front = nullptr;
    Node *rear = nullptr;
    int _size = 0;

public:
    void enqueue(int data)
    {
        Node *newNode = new Node(data);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
        _size++;
    }
    int dequeue()
    {
        if (front == nullptr)
        {
            return -1;
        }

        Node *temp = front;
        int val = temp->val;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }
        temp->next = nullptr;
        delete temp;
        _size--;
        return val;
    }

    int peek()
    {
        if (front != nullptr)
        {
            return front->val;
        }
        return -1;
    }
    bool isEmpty()
    {
        // _size can also be checked
        if (front != nullptr)
        {
            return 0;
        }
        return 1;
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        Node *temp = front;
        while (temp != nullptr)
        {
            cout << temp->val << " ";
            temp = temp->next;
        }
    }
    void clear()
    {
        while (front != nullptr)
        {
            dequeue();
        }
        rear = nullptr;
        _size = 0;
    }
    ~Queue()
    {
        clear();
    }
}

;
int main()
{

    return 0;
}