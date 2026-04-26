#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    string data;
    Node *next;

    Node(string val = "", Node *ptr = nullptr) : data(val), next(ptr) {}
};

class LinkedList
{
    Node *head;
    Node *tail;

public:
    LinkedList() : head(nullptr) , tail(nullptr) {}

    void insertAtHead(string val)
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
            cout <<"["<< temp->data<<"]" << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void push_back_list(string val)
    {
        Node*newNode = new Node(val);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

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

LinkedList l1;
// Add Nodes in the list and assign them each word you find with spaces in between
Node *buildWordlList(string s)
{
    string temp = "";
    
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            l1.push_back_list(temp);
            temp = "";
        }
        else
        {
            temp.push_back(s[i]);
        }
    }
    if(temp != "")
    {
        l1.push_back_list(temp);
    }
    return l1.getHead();
}
int main()
{
    
    string s;
    cout << "Input : ";
    getline(cin, s);

    l1.sethead() = buildWordlList(s);
    l1.display();

    return 0;
}