#include <iostream>
#include <stack>
#include <string>
#include <vector>
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
    int size = 0;
    Node *tail;

public:
    List()
    {
        head = tail = nullptr;
        size = 0;
    }

    Node *insertgcd(Node *head)
    {
        if (!head || !head->next)
        {
            return head;
        }

        Node *temp = head;
        while (temp != nullptr && temp->next != nullptr)
        {
            Node *to_insert = new Node(gcd(temp->data, temp->next->data), temp->next);
            temp->next = to_insert;
            temp = to_insert->next;
        }
        return head;
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
        size--;
    }
};

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main()
{

    return 0;
}