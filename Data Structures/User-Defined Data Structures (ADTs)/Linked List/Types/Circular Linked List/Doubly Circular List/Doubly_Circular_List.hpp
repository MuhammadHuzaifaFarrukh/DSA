#pragma once
#include <iostream>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ============================================================
//  Doubly Circular Linked List
// ============================================================
// Same as Doubly Linked List except:
//   - tail->next points back to head  (instead of nullptr)
//   - head->prev points back to tail  (instead of nullptr)
//   - There is no nullptr anywhere in the chain.
//   - Traversal must stop when we come back to head, NOT nullptr.
//
// Structure:
//   (tail) <-> [1] <-> [2] <-> [3] <-> [4] <-> (back to head)
//      ^___________________________________________________|
//
// Advantage over Singly Circular:
//   - pop_back() is O(1) because tail->prev gives the second-to-last node.
//   - Can traverse backwards just like doubly list.
//   - There is no STL for this in C++.
//   - It is a linear data structure.
// ============================================================

template <typename T>
class DCNode
{
public:
    T val;
    DCNode<T> *prev;
    DCNode<T> *next;
    DCNode(T v = T(), DCNode<T> *p = nullptr, DCNode<T> *n = nullptr)
        : val(v), prev(p), next(n) {}
};

template <typename T>
class DCList
{
private:
    DCNode<T> *head;
    DCNode<T> *tail;
    int size;

public:
    // ── Iterator ─────────────────────────────────────────────
    // Same idea as singly circular: track a done flag to stop at one full loop.
    class Iterator
    {
        DCNode<T> *ptr;
        DCNode<T> *start;
        bool done;

    public:
        Iterator(DCNode<T> *p = nullptr, bool d = false)
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
                    done = true;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        // Backward traversal — unique to doubly circular
        Iterator &operator--()
        {
            if (ptr)
            {
                ptr = ptr->prev;
                if (ptr == start)
                    done = true;
            }
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator &it) const { return ptr == it.ptr && done == it.done; }
        bool operator!=(const Iterator &it) const { return !(*this == it); }
    };

    // ── Constructors ──────────────────────────────────────────
    DCList() : head(nullptr), tail(nullptr), size(0) {}

    DCList(std::initializer_list<T> list) : head(nullptr), tail(nullptr), size(0)
    {
        for (const auto &item : list)
            push_back_DCList(item);
    }

    DCList(const DCList<T> &other) : head(nullptr), tail(nullptr), size(0)
    {
        if (!other.head)
            return;
        DCNode<T> *curr = other.head;
        do
        {
            push_back_DCList(curr->val);
            curr = curr->next;
        } while (curr != other.head);
    }

    DCList(DCList<T> &&other) noexcept : head(other.head), tail(other.tail), size(other.size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    DCList<T> &operator=(const DCList<T> &other)
    {
        if (this != &other)
        {
            clear_DCList();
            if (!other.head)
                return *this;
            DCNode<T> *curr = other.head;
            do
            {
                push_back_DCList(curr->val);
                curr = curr->next;
            } while (curr != other.head);
        }
        return *this;
    }

    DCList<T> &operator=(DCList<T> &&other) noexcept
    {
        if (this != &other)
        {
            clear_DCList();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~DCList() { clear_DCList(); }

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
        DCNode<T> *curr = head;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr->val;
    }

    // ── Node Accessors ────────────────────────────────────────
    DCNode<T> *get_head()
    {
        if (!head)
            throw std::underflow_error("List is empty");
        return head;
    }

    DCNode<T> *get_tail()
    {
        if (!tail)
            throw std::underflow_error("List is empty");
        return tail;
    }

    DCNode<T> *get_next(DCNode<T> *node)
    {
        if (!node)
            throw std::invalid_argument("Node is null");
        return node->next; // in circular list, NEVER nullptr — wraps to head
    }

    DCNode<T> *get_prev(DCNode<T> *node)
    {
        if (!node)
            throw std::invalid_argument("Node is null");
        return node->prev; // in circular list, NEVER nullptr — wraps to tail
    }

    // ── Iterators ─────────────────────────────────────────────
    Iterator begin() { return Iterator(head, false); }
    Iterator end() { return Iterator(head, true); }
    Iterator rbegin() { return Iterator(tail, false); }
    Iterator rend() { return Iterator(tail, true); }

    // ── Core Modifiers ────────────────────────────────────────
    void push_front_DCList(T val)
    {
        DCNode<T> *newNode = nullptr;
        try
        {
            newNode = new DCNode<T>(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_front failed.");
        }

        if (!head)
        {
            head = tail = newNode;
            newNode->next = newNode->prev = newNode; // point to itself
        }
        else
        {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
        size++;
    }

    void push_back_DCList(T val)
    {
        DCNode<T> *newNode = nullptr;
        try
        {
            newNode = new DCNode<T>(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_back failed.");
        }

        if (!head)
        {
            head = tail = newNode;
            newNode->next = newNode->prev = newNode; // point to itself
        }
        else
        {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
        size++;
    }

    void pop_front_DCList()
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
            DCNode<T> *temp = head;
            head = head->next;
            head->prev = tail; // close the circle from the new head side
            tail->next = head; // close the circle from the tail side
            temp->next = temp->prev = nullptr;
            delete temp;
        }
        size--;
    }

    // pop_back is O(1) because tail->prev gives us the second-to-last node
    void pop_back_DCList()
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
            DCNode<T> *temp = tail;
            tail = tail->prev;
            tail->next = head; // close the circle from the new tail side
            head->prev = tail; // close the circle from the head side
            temp->next = temp->prev = nullptr;
            delete temp;
        }
        size--;
    }

    void insert_node(T val, int ind)
    {
        if (ind < 0 || ind > size)
        {
            throw std::out_of_range("Negative index");
        }
        if (ind == 0)
        {
            push_front_DCList(val);
            return;
        }

        DCNode<T> *curr = head;
        for (int i = 0; i < ind && curr->next != head; i++)
            curr = curr->next;

        // If curr->next is head, we walked past the end — push back
        if (curr->next == head)
        {
            push_back_DCList(val);
            return;
        }

        DCNode<T> *newNode = nullptr;
        try
        {
            newNode = new DCNode<T>(val, curr->prev, curr);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: insertion failed.");
        }

        curr->prev->next = newNode;
        curr->prev = newNode;
        size++;
    }

    void insert_after(T val, int ind) { insert_node(val, ind + 1); }

    void remove_node(int ind)
    {
        if (ind < 0 || !head || ind >= size)
            throw std::out_of_range("Invalid removal index");

        if (ind == 0)
        {
            pop_front_DCList();
            return;
        }

        DCNode<T> *curr = head;
        for (int i = 0; i < ind; i++)
            curr = curr->next;

        // If curr->next is head, curr is the tail
        if (curr->next == head)
        {
            pop_back_DCList();
            return;
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = curr->next = nullptr;
        delete curr;
        size--;
    }

    void erase_after(int ind) { remove_node(ind + 1); }

    void remove_node_val(T val)
    {
        if (!head)
            throw std::underflow_error("List empty");

        if (head->val == val)
        {
            pop_front_DCList();
            return;
        }
        if (tail->val == val)
        {
            pop_back_DCList();
            return;
        }

        DCNode<T> *curr = head->next;
        while (curr != head && curr->val != val)
            curr = curr->next;

        if (curr == head)
            throw std::runtime_error("Value not found");

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = curr->next = nullptr;
        delete curr;
        size--;
    }

    void remove_all(T val)
    {
        if (!head)
            return;
        int passes = size; // guard against infinite loop
        while (passes-- > 0 && head)
        {
            if (head->val == val)
            {
                pop_front_DCList();
                continue;
            }
            if (tail->val == val)
            {
                pop_back_DCList();
                continue;
            }

            DCNode<T> *curr = head->next;
            bool found = false;
            while (curr != head)
            {
                DCNode<T> *nx = curr->next;
                if (curr->val == val)
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr->prev = curr->next = nullptr;
                    delete curr;
                    size--;
                    found = true;
                }
                curr = nx;
            }
            if (!found)
                break;
        }
    }

    void remove_if(std::function<bool(T)> predicate)
    {
        if (!head)
            return;
        int passes = size;
        while (passes-- > 0 && head)
        {
            if (predicate(head->val))
            {
                pop_front_DCList();
                continue;
            }
            if (predicate(tail->val))
            {
                pop_back_DCList();
                continue;
            }

            DCNode<T> *curr = head->next;
            bool found = false;
            while (curr != head)
            {
                DCNode<T> *nx = curr->next;
                if (predicate(curr->val))
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr->prev = curr->next = nullptr;
                    delete curr;
                    size--;
                    found = true;
                }
                curr = nx;
            }
            if (!found)
                break;
        }
    }

    void clear_DCList()
    {
        while (head)
            pop_front_DCList();
    }

    void resize(int s, T val = T())
    {
        if (s < 0)
            throw std::invalid_argument("Size cannot be negative");
        while (size > s)
            pop_back_DCList();
        while (size < s)
            push_back_DCList(val);
    }

    // ── Algorithms ────────────────────────────────────────────
    void reverse()
    {
        if (!head || head == tail)
            return;

        DCNode<T> *curr = head;
        do
        {
            std::swap(curr->prev, curr->next);
            curr = curr->prev; // prev is the old next after the swap
        } while (curr != head);

        std::swap(head, tail);
    }

    void selection_sort()
    {
        if (!head || head == tail)
            return;
        DCNode<T> *i = head;
        do
        {
            DCNode<T> *minNode = i;
            DCNode<T> *j = i->next;
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

    void append(const DCList<T> &other)
    {
        if (!other.head)
            return;
        DCNode<T> *curr = other.head;
        do
        {
            push_back_DCList(curr->val);
            curr = curr->next;
        } while (curr != other.head);
    }

    void swap(DCList<T> &other) noexcept
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
        DCNode<T> *curr = head;
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
    void display()
    {
        if (!head)
        {
            cout << "Empty List" << endl;
            return;
        }
        DCNode<T> *curr = head;
        do
        {
            cout << curr->val;
            if (curr->next != head)
                cout << " <-> ";
            curr = curr->next;
        } while (curr != head);
        cout << " <-> (head)" << endl;
    }

    // display_reverse : walk from tail to head using prev pointer
    void display_reverse()
    {
        if (!head)
        {
            cout << "Empty List" << endl;
            return;
        }
        DCNode<T> *curr = tail;
        do
        {
            cout << curr->val;
            if (curr->prev != tail)
                cout << " <-> ";
            curr = curr->prev;
        } while (curr != tail);
        cout << " <-> (tail)" << endl;
    }
};
