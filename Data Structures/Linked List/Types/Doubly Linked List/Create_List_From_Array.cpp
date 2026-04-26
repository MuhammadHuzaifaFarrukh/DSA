#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
class DNode
{
public:
    int val;
    DNode *prev;
    DNode *next;
    DNode(int v = 0, DNode *p = nullptr, DNode *n = nullptr) : val(v), prev(p), next(n) {}
};

class DList
{
private:
    DNode *head;
    DNode *tail;
    int size;

public:
    DList() : head(nullptr), tail(nullptr), size(0) {}
    ~DList() { clear_DList(); }

    DNode *get_head()
    {
        if (!head)
            throw std::underflow_error("DList is empty");
        return head;
    }

    DNode *get_tail()
    {
        if (!tail)
            throw std::underflow_error("DList is empty");
        return tail;
    }
    void clear_DList()
    {
        while (head)
        {
            pop_front_DList();
        }
    }

    // We create a doubly linked list using array elements.
    // Time Complexity : O(n) and Space Complexity : O(1)
    DNode *Create_List_from_Array(int *arr, int n)
    {
        for (int i = 0; i < n; i++)
        {
            if (!head)
            {
                head = new DNode(arr[i]);
                tail = head;
            }
            else
            {
                DNode *newNode = new DNode(arr[i]);
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    void pop_front_DList()
    {
        if (!head)
            throw std::underflow_error("Underflow: DList empty");
        DNode *temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        temp->next = nullptr;
        delete temp;
        size--;
    }
};

int main()
{

    return 0;
}