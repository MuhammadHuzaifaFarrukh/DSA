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


    // We are deleting tail node considering we don't have DNode *tail.
    // Time Complexity : O(n) and Space Complexity : O(n)
    DNode *DeleteTailRecursively(DNode *curr)
    {
        if (curr == nullptr)
        {
            return nullptr;
        }

        if (curr->next == nullptr)
        {
            delete curr;
            tail = nullptr;
            return nullptr;
        }

        curr->next = DeleteTailRecursively(curr->next);

        // If curr->next is now null, curr is the new tail
        // Set curr->next->prev to nullptr is not needed since next is already null
        // Just update tail and clear the prev of the deleted node is already done
        if (curr->next == nullptr)
        {
            tail = curr;
            // Extra step for doubly: make sure new tail's next is clean
            curr->next = nullptr;
        }
        else
        {
            // Keep prev pointer of next node consistent
            curr->next->prev = curr;
        }

        return curr;
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