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

    // 1) Swap each Node's previous and current pointer and then head and tail also.
    // Time Complexity : O(N) and Space Complexity : O(1)
    void reverse()
    {
        if (!head || head == tail)
            return;

        DNode *curr = head;
        while (curr)
        {
            // Swap prev and next for every node
            std::swap(curr->prev, curr->next);
            // Move to the next node (which is now stored in prev after swap)
            curr = curr->prev;
        }
        // Swap head and tail
        std::swap(head, tail);
    }

    // 2) Using Two Pointer Approach (Can be used because we can go prev now)
    // Time Complexity : O(N) and Space Complexity : O(1)
    void reverse()
    {
        if (!head || head == tail)
            return;

        DNode *left = head;
        DNode *right = tail;

        while (left != right && left->prev != right)
        {
            std::swap(left->val, right->val);
            left = left->next;
            right = right->prev;
        }
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