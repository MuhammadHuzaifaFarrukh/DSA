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

    // Insert from Array on the list head whenever we insert new element from array forward, we put that on our list head.
    // Time Complexity : O(N) and Space Complexity : O(N)
    DNode *insertAtheadfromArrayRecursively(int arr[], int ind, int size, DNode *prev)
    {
        if (ind < 0 || ind > size)
        {
            throw std::underflow_error("Wrong Range");
        }
        if (ind == size)
        {
            return prev;
        }

        DNode *temp = new DNode(arr[ind]);
        temp->next = prev;

        // Set prev pointer of the old head to point back to new node
        if (prev != nullptr)
        {
            prev->prev = temp;
        }

        size++;

        // If prev is nullptr, this is the very first node created.
        // In "Insert at Head" logic, the first node created becomes the tail.
        if (prev == nullptr)
        {
            this->tail = temp;
        }

        return insertAtheadfromArrayRecursively(arr, ind + 1, size, temp);
    }

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