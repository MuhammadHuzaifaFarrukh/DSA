#pragma once
#include <iostream>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ============================================================
//  Singly Circular Linked List
// ============================================================
// Same as Singly Linked List except:
//   - tail->next points back to head instead of nullptr.
//   - There is no nullptr anywhere in the chain.
//   - Traversal must stop when we come back to head, NOT when we hit nullptr.
//
// Structure:
//   head -> [1] -> [2] -> [3] -> [4] -> (back to head)
//
// Use case : Round-robin scheduling, circular buffers, playing song from playlist any problem
// where you want to keep looping over elements endlessly.
//
// In C++ STL there is no direct circular list container.
// However , it is a linear data structure.
// ============================================================

template <typename T>
class CNode
{
public:
    T val;
    CNode<T> *next;
    CNode(T v = T(), CNode<T> *n = nullptr) : val(v), next(n) {}
};

template <typename T>
class CList
{
private:
    CNode<T> *head;
    CNode<T> *tail; // tail->next always == head (or nullptr if list is empty)
    int size;

public:
    // ── Iterator ─────────────────────────────────────────────
    // IMPORTANT : end() is NOT nullptr here — it is head again.
    // So we store the head and a count to know when to stop,
    // otherwise ++ would loop forever.
    class Iterator
    {
        CNode<T> *ptr;
        CNode<T> *start; // remember where we began
        bool done;       // true once we've completed one full loop

    public:
        Iterator(CNode<T> *p = nullptr, bool d = false)
            : ptr(p), start(p), done(d) {}

        T &operator*()
        {
            if (!ptr || done)
                throw std::runtime_error("Iterator out of bounds");
            return ptr->val;
        }
        T *operator->() { return &(ptr->val); }

        Iterator &operator++()
        {
            if (ptr)
            {
                ptr = ptr->next;
                if (ptr == start)
                    done = true; // completed one full circle
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator &it) const { return ptr == it.ptr && done == it.done; }
        bool operator!=(const Iterator &it) const { return !(*this == it); }
    };

    // ── Constructors ──────────────────────────────────────────
    CList() : head(nullptr), tail(nullptr), size(0) {}

    CList(std::initializer_list<T> list) : head(nullptr), tail(nullptr), size(0)
    {
        for (const auto &item : list)
            push_back_CList(item);
    }

    CList(const CList<T> &other) : head(nullptr), tail(nullptr), size(0)
    {
        if (!other.head)
            return;
        CNode<T> *curr = other.head;
        do
        {
            push_back_CList(curr->val);
            curr = curr->next;
        } while (curr != other.head);
    }

    CList(CList<T> &&other) noexcept : head(other.head), tail(other.tail), size(other.size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    CList<T> &operator=(const CList<T> &other)
    {
        if (this != &other)
        {
            clear_CList();
            if (!other.head)
                return *this;
            CNode<T> *curr = other.head;
            do
            {
                push_back_CList(curr->val);
                curr = curr->next;
            } while (curr != other.head);
        }
        return *this;
    }

    CList<T> &operator=(CList<T> &&other) noexcept
    {
        if (this != &other)
        {
            clear_CList();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~CList() { clear_CList(); }

    // ── State Queries ─────────────────────────────────────────
    bool is_empty() const { return head == nullptr; }
    int get_size() const { return size; }

    // ── Element Access ────────────────────────────────────────
    T &front()
    {
        if (!head)
            throw std::underflow_error("List is empty");
        return head->val;
    }

    T &back()
    {
        if (!tail)
            throw std::underflow_error("List is empty");
        return tail->val;
    }

    T &at(int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        CNode<T> *curr = head;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr->val;
    }

    // ── Node Accessors ────────────────────────────────────────
    CNode<T> *get_head()
    {
        if (!head)
            throw std::underflow_error("List is empty");
        return head;
    }

    CNode<T> *get_tail()
    {
        if (!tail)
            throw std::underflow_error("List is empty");
        return tail;
    }

    CNode<T> *get_next(CNode<T> *node)
    {
        if (!node)
            throw std::invalid_argument("Node is null");
        return node->next; // in circular list this is NEVER nullptr
    }

    // ── Iterators ─────────────────────────────────────────────
    Iterator begin() { return Iterator(head, false); }
    // end() is a "done" iterator pointing back at head
    Iterator end() { return Iterator(head, true); }

    // ── Core Modifiers ────────────────────────────────────────
    void push_front_CList(T val)
    {
        CNode<T> *newNode = nullptr;
        try
        {
            newNode = new CNode<T>(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_front failed.");
        }

        if (!head)
        {
            head = tail = newNode;
            newNode->next = head; // point to itself
        }
        else
        {
            newNode->next = head;
            head = newNode;
            tail->next = head; // keep the circle closed
        }
        size++;
    }

    void push_back_CList(T val)
    {
        CNode<T> *newNode = nullptr;
        try
        {
            newNode = new CNode<T>(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_back failed.");
        }

        if (!head)
        {
            head = tail = newNode;
            newNode->next = head; // point to itself
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // keep the circle closed
        }
        size++;
    }

    void pop_front_CList()
    {
        if (!head)
            throw std::underflow_error("Underflow: List empty");

        if (head == tail)
        {
            // Only one node
            delete head;
            head = tail = nullptr;
        }
        else
        {
            CNode<T> *temp = head;
            head = head->next;
            tail->next = head; // keep the circle closed
            temp->next = nullptr;
            delete temp;
        }
        size--;
    }

    // pop_back is O(n) in singly circular because we must walk to second-to-last
    void pop_back_CList()
    {
        if (!head)
            throw std::underflow_error("Underflow: List empty");

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            // Walk to the node just before tail
            CNode<T> *curr = head;
            while (curr->next != tail)
                curr = curr->next;

            delete tail;
            tail = curr;
            tail->next = head; // keep the circle closed
        }
        size--;
    }

    void insert_node(T val, int ind)
    {
        if (ind < 0 || ind > size)
            throw std::out_of_range("Negative index");
        if (ind == 0)
        {
            push_front_CList(val);
            return;
        }

        CNode<T> *prev = head;
        for (int i = 0; i < ind - 1 && prev->next != head; i++)
            prev = prev->next;

        // If we hit back to head, we are past the end — push back
        if (prev->next == head)
        {
            push_back_CList(val);
            return;
        }

        CNode<T> *newNode = nullptr;
        try
        {
            newNode = new CNode<T>(val, prev->next);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: insertion failed.");
        }

        prev->next = newNode;
        size++;
    }

    void insert_after(T val, int ind) { insert_node(val, ind + 1); }

    void remove_node(int ind)
    {
        if (ind < 0 || !head || ind >= size)
            throw std::out_of_range("Invalid removal index");

        if (ind == 0)
        {
            pop_front_CList();
            return;
        }

        CNode<T> *prev = head;
        for (int i = 0; i < ind - 1; i++)
        {
            prev = prev->next;
        }

        CNode<T> *toDelete = prev->next;

        // If toDelete is tail, use pop_back to keep tail pointer correct
        if (toDelete == tail)
        {
            pop_back_CList();
            return;
        }

        prev->next = toDelete->next;
        toDelete->next = nullptr;
        delete toDelete;
        size--;
    }

    void erase_after(int ind) { remove_node(ind + 1); }

    void remove_node_val(T val)
    {
        if (!head)
            throw std::underflow_error("List empty");

        if (head->val == val)
        {
            pop_front_CList();
            return;
        }
        if (tail->val == val)
        {
            pop_back_CList();
            return;
        }

        CNode<T> *prev = head;
        while (prev->next != head && prev->next->val != val)
            prev = prev->next;

        if (prev->next == head)
            throw std::runtime_error("Value not found");

        CNode<T> *toDelete = prev->next;
        prev->next = toDelete->next;
        toDelete->next = nullptr;
        delete toDelete;
        size--;
    }

    void remove_all(T val)
    {
        if (!head)
            return;
        // Keep removing from front while head matches
        while (head && head->val == val)
            pop_front_CList();

        if (!head)
            return;

        CNode<T> *prev = head;
        while (prev->next != head)
        {
            if (prev->next->val == val)
            {
                if (prev->next == tail)
                {
                    pop_back_CList();
                    break;
                }
                CNode<T> *toDelete = prev->next;
                prev->next = toDelete->next;
                toDelete->next = nullptr;
                delete toDelete;
                size--;
            }
            else
                prev = prev->next;
        }
    }

    void remove_if(std::function<bool(T)> predicate)
    {
        if (!head)
            return;
        while (head && predicate(head->val))
            pop_front_CList();

        if (!head)
            return;

        CNode<T> *prev = head;
        while (prev->next != head)
        {
            if (predicate(prev->next->val))
            {
                if (prev->next == tail)
                {
                    pop_back_CList();
                    break;
                }
                CNode<T> *toDelete = prev->next;
                prev->next = toDelete->next;
                toDelete->next = nullptr;
                delete toDelete;
                size--;
            }
            else
                prev = prev->next;
        }
    }

    void clear_CList()
    {
        while (head)
            pop_front_CList();
    }

    void resize(int s, T val = T())
    {
        if (s < 0)
            throw std::invalid_argument("Size cannot be negative");
        while (size > s)
            pop_back_CList();
        while (size < s)
            push_back_CList(val);
    }

    // ── Algorithms ────────────────────────────────────────────
    void reverse()
    {
        if (!head || head == tail)
            return;

        CNode<T> *prev = tail; // prev starts at tail so circle stays valid
        CNode<T> *curr = head;
        CNode<T> *nxt = nullptr;
        tail = head; // old head becomes new tail

        do
        {
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        } while (curr != head);

        head = prev;
        tail->next = head; // close the circle
    }

    void selection_sort()
    {
        if (!head || head == tail)
            return;
        CNode<T> *i = head;
        do
        {
            CNode<T> *minNode = i;
            CNode<T> *j = i->next;
            while (j != head)
            {
                if (j->val < minNode->val)
                    minNode = j;
                j = j->next;
            }
            std::swap(i->val, minNode->val);
            i = i->next;
        } while (i != head);
    }

    void append(const CList<T> &other)
    {
        if (!other.head)
            return;
        CNode<T> *curr = other.head;
        do
        {
            push_back_CList(curr->val);
            curr = curr->next;
        } while (curr != other.head);
    }

    void swap(CList<T> &other) noexcept
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }

    // ── Search ────────────────────────────────────────────────
    int linear_search(const T &key) const
    {
        if (!head)
            return -1;
        int index = 0;
        CNode<T> *curr = head;
        do
        {
            if (curr->val == key)
                return index;
            curr = curr->next;
            index++;
        } while (curr != head);
        return -1;
    }

    bool contains(const T &key) const { return linear_search(key) != -1; }

    // ── Display ───────────────────────────────────────────────
    // Shows the circular nature: head -> ... -> tail -> (head)
    void display()
    {
        if (!head)
        {
            cout << "Empty List" << endl;
            return;
        }
        CNode<T> *curr = head;
        do
        {
            cout << curr->val;
            if (curr->next != head)
                cout << " -> ";
            curr = curr->next;
        } while (curr != head);
        cout << " -> (head)" << endl;
    }
};
