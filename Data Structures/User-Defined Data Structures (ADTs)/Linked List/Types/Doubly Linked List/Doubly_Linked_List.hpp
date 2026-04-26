#pragma once
#include <iostream>
#include <initializer_List>
#include <functional>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ============================================================
//  Doubly Linked List — Templated Implementation
// ============================================================
// A doubly linked List is a sequential container and a linear data structure where every DNode
// holds a pointer to both the NEXT and the PREVIOUS DNode.
//
// Advantages over Singly Linked List:
//   - Backward traversal is O(1) per step instead of impossible.
//   - pop_back() is O(1) because we can reach the second-to-last
//     DNode directly via tail->prev (no O(n) walk needed).
//   - insert_before() and erase at a known DNode are O(1).
//   - Bi-directional iterators (both ++ and --) work naturally.
//
// Disadvantages:
//   - Each DNode uses one extra pointer (8 bytes on 64-bit), so
//     memory per DNode is slightly larger than a singly DList.
//   - Every insertion/deletion must keep TWO pointers consistent
//     (next AND prev), so the logic has more steps to get right.
//
// In C++ STL this is <list> (std::list<T>).
//
// Structure used here:
//   [ head ] <-> [ DNode ] <-> [ DNode ] <-> [ tail ] <-> nullptr
//   head->prev == nullptr   tail->next == nullptr
//
// Two-class design (same as singly List template):
//   DNode<T>   — the DNode (val, prev, next)
//   DList<T>   — the container (head, tail, size + all operations)
// ============================================================

// ────────────────────────────────────────────────────────────
//  DNode — Doubly Linked Node
// ────────────────────────────────────────────────────────────
template <typename T>
class DNode
{
public:
    T val;
    DNode<T> *prev;
    DNode<T> *next;
    DNode(T v = T(), DNode<T> *p = nullptr, DNode<T> *n = nullptr) : val(v), prev(p), next(n) {}
};

template <typename T>
class DList
{
private:
    DNode<T> *head;
    DNode<T> *tail;
    int size;

public:
    // ── Iterator ─────────────────────────────────────────────
    // Supports both ++ and -- because we have prev pointers now.
    class Iterator
    {
        DNode<T> *ptr;

    public:
        Iterator(DNode<T> *p = nullptr) : ptr(p) {}

        T &operator*()
        {
            if (!ptr)
                throw std::runtime_error("Iterator out of bounds");
            return ptr->val;
        }
        T *operator->() { return &(ptr->val); }

        Iterator &operator++()
        {
            if (ptr)
                ptr = ptr->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            if (ptr)
                ptr = ptr->next;
            return temp;
        }
        // New : move backward (not possible in singly list)
        Iterator &operator--()
        {
            if (ptr)
                ptr = ptr->prev;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator temp = *this;
            if (ptr)
                ptr = ptr->prev;
            return temp;
        }

        bool operator==(const Iterator &it) const { return ptr == it.ptr; }
        bool operator!=(const Iterator &it) const { return ptr != it.ptr; }
    };

    // ── Constructors ──────────────────────────────────────────
    DList() : head(nullptr), tail(nullptr), size(0) {}

    DList(std::initializer_DList<T> DList) : head(nullptr), tail(nullptr), size(0)
    {
        for (const auto &item : DList)
            push_back_DList(item);
    }

    DList(const DList<T> &other) : head(nullptr), tail(nullptr), size(0)
    {
        for (DNode<T> *temp = other.head; temp; temp = temp->next)
            push_back_DList(temp->val);
    }

    DList(DList<T> &&other) noexcept : head(other.head), tail(other.tail), size(other.size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    DList<T> &operator=(const DList<T> &other)
    {
        if (this != &other)
        {
            clear_DList();
            for (DNode<T> *temp = other.head; temp; temp = temp->next)
                push_back_DList(temp->val);
        }
        return *this;
    }

    DList<T> &operator=(DList<T> &&other) noexcept
    {
        if (this != &other)
        {
            clear_DList();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~DList() { clear_DList(); }

    // ── State Queries ─────────────────────────────────────────
    bool is_empty() const { return head == nullptr; }
    int get_size() const { return size; }

    // ── Element Access ────────────────────────────────────────
    T &front()
    {
        if (!head)
            throw std::underflow_error("DList is empty");
        return head->val;
    }

    T &back()
    {
        if (!tail)
            throw std::underflow_error("DList is empty");
        return tail->val;
    }

    T &at(int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        DNode<T> *curr = head;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr->val;
    }

    const T &at(int index) const
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        DNode<T> *curr = head;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr->val;
    }

    // ── DNode Pointer Accessors ────────────────────────────────
    DNode<T> *get_head()
    {
        if (!head)
            throw std::underflow_error("DList is empty");
        return head;
    }

    DNode<T> *get_tail()
    {
        if (!tail)
            throw std::underflow_error("DList is empty");
        return tail;
    }

    // get_next : given a DNode pointer, return the next DNode
    DNode<T> *get_next(DNode<T> *DNode)
    {
        if (!DNode)
            throw std::invalid_argument("DNode is null");
        return DNode->next; // nullptr if DNode is tail
    }

    // get_prev : given a DNode pointer, return the previous DNode
    // This is only possible because we have a prev pointer (doubly DList)
    DNode<T> *get_prev(DNode<T> *DNode)
    {
        if (!DNode)
            throw std::invalid_argument("DNode is null");
        return DNode->prev; // nullptr if DNode is head
    }

    // ── Iterators ─────────────────────────────────────────────
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    // rbegin : start from tail, use -- to walk backward
    Iterator rbegin() { return Iterator(tail); }
    Iterator rend() { return Iterator(nullptr); }

    // ── Core Modifiers ────────────────────────────────────────
    void push_front_DList(T val)
    {
        DNode<T> *newDNode = nullptr;
        try
        {
            newDNode = new DNode<T>(val, nullptr, head);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_front failed.");
        }

        if (!head)
            head = tail = newDNode;
        else
        {
            head->prev = newDNode;
            head = newDNode;
        }
        size++;
    }

    void push_back_DList(T val)
    {
        DNode<T> *newDNode = nullptr;
        try
        {
            newDNode = new DNode<T>(val, tail, nullptr);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_back failed.");
        }

        if (!head)
            head = tail = newDNode;
        else
        {
            tail->next = newDNode;
            tail = newDNode;
        }
        size++;
    }

    void pop_front_DList()
    {
        if (!head)
            throw std::underflow_error("Underflow: DList empty");
        DNode<T> *temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        temp->next = nullptr;
        delete temp;
        size--;
    }

    // pop_back is now O(1) using tail->prev
    // In singly DList this was O(n) because we had to walk the whole DList
    void pop_back_DList()
    {
        if (!tail)
            throw std::underflow_error("Underflow: DList empty");
        DNode<T> *temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        temp->prev = nullptr;
        delete temp;
        size--;
    }

    void insert_DNode(T val, int ind)
    {
        if (ind < 0)
            throw std::out_of_range("Negative index");
        if (ind == 0)
        {
            push_front_DList(val);
            return;
        }
        if (ind >= size)
        {
            push_back_DList(val);
            return;
        }

        // Walk to the DNode currently sitting at `ind`
        DNode<T> *curr = head;
        for (int i = 0; i < ind; i++)
            curr = curr->next;

        DNode<T> *newDNode = nullptr;
        try
        {
            newDNode = new DNode<T>(val, curr->prev, curr);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: insertion failed.");
        }

        curr->prev->next = newDNode;
        curr->prev = newDNode;
        size++;
    }

    void insert_after(T val, int ind) { insert_DNode(val, ind + 1); }

    void remove_DNode(int ind)
    {
        if (ind < 0 || !head || ind >= size)
            throw std::out_of_range("Invalid removal index");

        if (ind == 0)
        {
            pop_front_DList();
            return;
        }
        if (ind == size - 1)
        {
            pop_back_DList();
            return;
        }

        DNode<T> *curr = head;
        for (int i = 0; i < ind; i++)
            curr = curr->next;

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = curr->next = nullptr;
        delete curr;
        size--;
    }

    void erase_after(int ind) { remove_DNode(ind + 1); }

    void remove_DNode_val(T val)
    {
        if (!head)
            throw std::underflow_error("DList empty");

        DNode<T> *curr = head;
        while (curr && curr->val != val)
            curr = curr->next;

        if (!curr)
            throw std::runtime_error("Value not found");

        if (curr == head)
        {
            pop_front_DList();
            return;
        }
        if (curr == tail)
        {
            pop_back_DList();
            return;
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = curr->next = nullptr;
        delete curr;
        size--;
    }

    void remove_all(T val)
    {
        DNode<T> *curr = head;
        while (curr)
        {
            DNode<T> *nx = curr->next;
            if (curr->val == val)
            {
                if (curr == head)
                    pop_front_DList();
                else if (curr == tail)
                    pop_back_DList();
                else
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr->prev = curr->next = nullptr;
                    delete curr;
                    size--;
                }
            }
            curr = nx;
        }
    }

    void remove_if(std::function<bool(T)> predicate)
    {
        DNode<T> *curr = head;
        while (curr)
        {
            DNode<T> *nx = curr->next;
            if (predicate(curr->val))
            {
                if (curr == head)
                    pop_front_DList();
                else if (curr == tail)
                    pop_back_DList();
                else
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr->prev = curr->next = nullptr;
                    delete curr;
                    size--;
                }
            }
            curr = nx;
        }
    }

    void clear_DList()
    {
        while (head)
            pop_front_DList();
    }

    void resize(int s, T val = T())
    {
        if (s < 0)
            throw std::invalid_argument("Size cannot be negative");
        while (size > s)
            pop_back_DList();
        while (size < s)
            push_back_DList(val);
    }

    // ── Algorithms ────────────────────────────────────────────
    void reverse()
    {
        if (!head || head == tail)
            return;
        DNode<T> *curr = head;
        while (curr)
        {
            std::swap(curr->prev, curr->next);
            curr = curr->prev; // prev is the old next after the swap
        }
        std::swap(head, tail);
    }

    void selection_sort()
    {
        if (!head || head == tail)
            return;
        for (DNode<T> *i = head; i; i = i->next)
        {
            DNode<T> *minDNode = i;
            for (DNode<T> *j = i->next; j; j = j->next)
                if (j->val < minDNode->val)
                    minDNode = j;
            std::swap(i->val, minDNode->val);
        }
    }

    void unique()
    {
        if (!head || head == tail)
            return;
        DNode<T> *curr = head;
        while (curr && curr->next)
        {
            if (curr->val == curr->next->val)
            {
                DNode<T> *dup = curr->next;
                curr->next = dup->next;
                if (dup->next)
                    dup->next->prev = curr;
                else
                    tail = curr;
                dup->prev = dup->next = nullptr;
                delete dup;
                size--;
            }
            else
                curr = curr->next;
        }
    }

    void splicejoin_after(DList<T> &other)
    {
        if (!other.head || this == &other)
            return;

        if (!head)
        {
            head = other.head;
            tail = other.tail;
        }
        else
        {
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
        }
        size += other.size;
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    void append(const DList<T> &other)
    {
        for (DNode<T> *temp = other.head; temp; temp = temp->next)
            push_back_DList(temp->val);
    }

    void swap(DList<T> &other) noexcept
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }

    void merge_on_sorted_only(DList<T> &other, std::function<bool(T, T)> comp = std::less<T>())
    {
        if (!other.head)
            return;
        DNode<T> dummy;
        DNode<T> *curr = &dummy;
        DNode<T> *p1 = head, *p2 = other.head;

        while (p1 && p2)
        {
            if (comp(p1->val, p2->val))
            {
                curr->next = p1;
                p1 = p1->next;
            }
            else
            {
                curr->next = p2;
                p2 = p2->next;
            }
            curr->next->prev = curr;
            curr = curr->next;
        }
        curr->next = p1 ? p1 : p2;
        if (curr->next)
            curr->next->prev = curr;

        head = dummy.next;
        if (head)
            head->prev = nullptr;

        DNode<T> *t = head;
        while (t && t->next)
            t = t->next;
        tail = t;

        size += other.size;
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    // ── Search ────────────────────────────────────────────────
    int linear_search(const T &key) const
    {
        int index = 0;
        for (DNode<T> *curr = head; curr; curr = curr->next, ++index)
            if (curr->val == key)
                return index;
        return -1;
    }

    DNode<T> *get_middle(DNode<T> *start, DNode<T> *end) const
    {
        if (!start)
            return nullptr;
        DNode<T> *slow = start, *fast = start->next;
        while (fast != end)
        {
            fast = fast->next;
            if (fast != end)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }
        return slow;
    }

    bool binary_search(const T &key) const
    {
        DNode<T> *start = head, *end = nullptr;
        while (start != end)
        {
            DNode<T> *mid = get_middle(start, end);
            if (!mid)
                return false;
            if (mid->val == key)
                return true;
            else if (mid->val < key)
                start = mid->next;
            else
                end = mid;
        }
        return false;
    }

    // ── Display ───────────────────────────────────────────────
    void display()
    {
        DNode<T> *temp = head;
        while (temp)
        {
            cout << temp->val;
            if (temp->next)
                cout << " <-> ";
            temp = temp->next;
        }
        cout << endl;
    }

    // display_reverse : walk from tail to head using prev pointer
    void display_reverse()
    {
        DNode<T> *temp = tail;
        while (temp)
        {
            cout << temp->val;
            if (temp->prev)
                cout << " <-> ";
            temp = temp->prev;
        }
        cout << endl;
    }
};