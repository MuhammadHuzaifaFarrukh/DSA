#pragma once
#include <iostream>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Linked list is a Data Structure that is made of nodes.
// Each Linked List is a group of nodes and we access list using its head.
// We can have multiple nodes in a class and then wrap them around in either a single class or another class.
// Here we implemented it using two classes which is a good and standard way.
// For a single class , we would have to implement each logic in complex way.
// For single class , we will have to implement its head and other nodes by ourself in main and then for any other function of list , we will first
// have to make in Node class and then call in main by passing the head pointer.

// Here we have a Node class which contains data and next pointer that points to the next Node.
// Then we have a LinkedList class which contains the head that points to first node (and tail which points to last Node).
// The tail pointer is usually optional but we make it just for our ease so that push_back beomes O(1).
// We have 3 types of list : Singly , Doubly , Circular.
// Circular List can be Singly or Doubly as well.

// Here we implement the Singly Linked List.
// In C++ , we have it as : <forward_list>
// It is a linear data structure and sequential container.
// It is more efficient than a vector in a way that we only use the nodes (data) that we want and no other extra space
// In vector we have many space for extra elements that may or may not be used.
// Lists are generally better than our vectors and deque in insertion , extraction and moving elements.
// The main drawback of list is that we can't access the element directly in list as using [] or .at() like vectors in O(1).
// The forward_list in C++ doesn't even have a .size() function , and we may need to find its size in O(n) or by storing another counter variable.

template <typename T>
class Node
{
public:
    T val;
    Node<T> *next;
    Node(T v = T(), Node<T> *n = nullptr) : val(v), next(n) {}
};

template <typename T>
class List
{
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    class Iterator
    {
        Node<T> *ptr;

    public:
        Iterator(Node<T> *p = nullptr) : ptr(p) {}
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
        bool operator==(const Iterator &it) const { return ptr == it.ptr; }
        bool operator!=(const Iterator &it) const { return ptr != it.ptr; }
    };

    List() : head(nullptr), tail(nullptr), size(0) {}

    List(std::initializer_list<T> list) : head(nullptr), tail(nullptr), size(0)
    {
        for (const auto &item : list)
            push_back_list(item);
    }

    List(const List<T> &other) : head(nullptr), tail(nullptr), size(0)
    {
        for (Node<T> *temp = other.head; temp != nullptr; temp = temp->next)
        {
            push_back_list(temp->val);
        }
    }

    List(List<T> &&other) noexcept : head(other.head), tail(other.tail), size(other.size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    List<T> &operator=(const List<T> &other)
    {
        if (this != &other)
        {
            clear_list();
            for (Node<T> *temp = other.head; temp != nullptr; temp = temp->next)
            {
                push_back_list(temp->val);
            }
        }
        return *this;
    }

    List<T> &operator=(List<T> &&other) noexcept
    {
        if (this != &other)
        {
            clear_list();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~List() { clear_list(); }

    T &at(int index)
    {
        // 1. Bounds Checking
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of bounds");
        }

        // 2. Traversal
        Node<T> *curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }

        // 3. Return a reference to the data
        return curr->data;
    }

    // Const version (for read-only lists)
    const T &at(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of bounds");
        }

        Node<T> *curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }

        return curr->data;
    }

    bool is_empty() const { return head == nullptr; }
    int get_size() const { return size; }

    Node<T> *get_tail()
    {
        if (!tail)
            throw std::underflow_error("List is empty");
        return tail;
    }

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

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    // --- Core Modifiers ---
    void push_front_list(T val)
    {
        Node<T> *newNode = nullptr;
        try
        {
            newNode = new Node<T>(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_front failed.");
        }

        if (!head)
        {
            head = tail = newNode;
            newNode->next = nullptr;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void push_back_list(T val)
    {
        Node<T> *newNode = nullptr;
        try
        {
            newNode = new Node<T>(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_back failed.");
        }

        newNode->next = nullptr;
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void pop_front_list()
    {
        if (!head)
            throw std::underflow_error("Underflow: List empty");
        Node<T> *temp = head;
        head = head->next;
        if (!head)
            tail = nullptr;
        temp->next = nullptr;
        delete temp;
        size--;
    }

    void pop_back_list()
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
            Node<T> *temp = head;
            while (temp->next != tail)
                temp = temp->next;
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        size--;
    }

    void insert_node(T val, int ind)
    {
        if (ind < 0)
            throw std::out_of_range("Negative index");

        if (ind == 0)
        {
            push_front_list(val);
            return;
        }

        Node<T> *prev = head;
        for (int i = 0; i < ind - 1 && prev != nullptr; i++)
        {
            prev = prev->next;
        }

        if (!prev)
            throw std::out_of_range("Index out of bounds");

        if (prev == tail)
        {
            push_back_list(val);
        }
        else
        {
            Node<T> *newNode = nullptr;
            try
            {
                newNode = new Node<T>(val, prev->next);
            }
            catch (const std::bad_alloc &)
            {
                throw std::runtime_error("Out of memory: insertion failed.");
            }
            prev->next = newNode;
            size++;
        }
    }

    void insert_after(T val, int ind)
    {
        insert_node(val, ind + 1);
    }

    void remove_node(int ind)
    {
        if (ind < 0 || !head || ind > size)
            throw std::out_of_range("Invalid removal index");

        if (ind == 0)
        {
            pop_front_list();
            return;
        }

        Node<T> *prev = head;
        for (int i = 0; i < ind - 1 && prev->next != nullptr; i++)
        {
            prev = prev->next;
        }

        if (!prev || !prev->next)
            throw std::out_of_range("Index out of bounds");

        if (prev->next == tail)
        {
            pop_back_list();
        }
        else
        {
            Node<T> *toDelete = prev->next;
            prev->next = toDelete->next;
            toDelete->next = nullptr;
            delete toDelete;
            size--;
        }
    }

    void erase_after(int ind) { remove_node(ind + 1); }

    void remove_node_val(T val)
    {
        if (!head)
            throw std::underflow_error("List empty");
        if (head->val == val)
        {
            pop_front_list();
            return;
        }
        Node<T> *curr = head;
        while (curr->next && curr->next->val != val)
            curr = curr->next;

        if (curr->next)
        {
            if (curr->next == tail)
                pop_back_list();
            else
            {
                Node<T> *toDelete = curr->next;
                curr->next = toDelete->next;
                toDelete->next = nullptr;
                delete toDelete;
                size--;
            }
        }
        else
            throw std::runtime_error("Value not found");
    }

    // This function will remove all the instances of a value from list.
    void remove_all(T val)
    {
        while (head && head->val == val)
            pop_front_list();
        Node<T> *curr = head;
        while (curr && curr->next)
        {
            if (curr->next->val == val)
            {
                if (curr->next == tail)
                    pop_back_list();
                else
                {
                    Node<T> *temp = curr->next;
                    curr->next = temp->next;
                    temp->next = nullptr;
                    delete temp;
                    size--;
                }
            }
            else
                curr = curr->next;
        }
    }

    // This Removes on the basis of a function predicate
    /*
    // 1) Writing function outside main :
    // Outside main
    bool isEven(int n)
    {
        return n % 2 == 0;
    }

    // Inside main
    myList.remove_if(isEven); // Just pass the function name


    // 2) Using Lambda Expression :
    myList.remove_if([](int n)
    {
        return n % 2 == 0;
    });

    // 3) Using functor :
    struct IsEven
    {
        bool operator()(int n) const
        {
            return n % 2 == 0;
        }
    };

    // Usage in main:
    IsEven evenCheck;
    myList.remove_if(evenCheck);
    */
    void remove_if(std::function<bool(T)> predicate)
    {
        while (head && predicate(head->val))
            pop_front_list();
        Node<T> *curr = head;
        while (curr && curr->next)
        {
            if (predicate(curr->next->val))
            {
                if (curr->next == tail)
                    pop_back_list();
                else
                {
                    Node<T> *temp = curr->next;
                    curr->next = temp->next;
                    temp->next = nullptr;
                    delete temp;
                    size--;
                }
            }
            else
                curr = curr->next;
        }
    }

    void clear_list()
    {
        while (head)
            pop_front_list();
        head = tail = nullptr;
    }

    void resize(int s, T val = T())
    {
        if (s < 0)
            throw std::invalid_argument("Size cannot be negative");
        // We use a temporary count here to avoid logic bugs since we aren't using 'size' for the loop
        int currentCount = size;
        while (currentCount > s)
        {
            pop_back_list();
            currentCount--;
        }
        while (currentCount < s)
        {
            push_back_list(val);
            currentCount++;
        }
    }

    void reverse()
    {
        if (!head || head == tail)
            return;
        Node<T> *prev = nullptr, *curr = head, *nxt = nullptr;
        tail = head;
        while (curr)
        {
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        head = prev;
    }

    void selection_sort()
    {
        if (!head || head == tail)
            return;
        for (Node<T> *i = head; i; i = i->next)
        {
            Node<T> *minNode = i;
            for (Node<T> *j = i->next; j; j = j->next)
            {
                if (j->val < minNode->val)
                    minNode = j;
            }
            std::swap(i->val, minNode->val);
        }
    }

    // This removes each instance of the duplcates in the list.
    // E.g : List contains : 1->1->2->3->4->4->NULL
    // Then : 1->2->3->4->NULL
    void unique()
    {
        if (!head || head == tail)
            return;
        Node<T> *curr = head;
        while (curr->next)
        {
            if (curr->val == curr->next->val)
            {
                if (curr->next == tail)
                    pop_back_list();
                else
                {
                    Node<T> *temp = curr->next;
                    curr->next = temp->next;
                    temp->next = nullptr;
                    delete temp;
                    size--;
                }
            }
            else
            {
                curr = curr->next;
            }
        }
    }

    // This function copies/appends everything of list2 to list1 and then list2 is nullified.
    // If other list doesn't exist or if both are same then do nothing.
    void splicejoin_after(List<T> &other)
    {
        // 1. Check if the other list is empty
        // 2. Check if the user is trying to splice the list into itself
        if (!other.head || this == &other)
            return;

        if (!head)
        {
            // If the current list is empty, just take everything from other
            head = other.head;
            tail = other.tail;
        }
        else
        {
            // Connect our tail to their head
            tail->next = other.head;
            tail = other.tail;
        }

        size += other.size;

        // CRITICAL: We MUST nullify other so its destructor
        // doesn't delete the nodes we just took!
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // This just appends the list 2 on list 1.
    void append(const List<T> &other)
    {
        for (Node<T> *temp = other.head; temp; temp = temp->next)
        {
            push_back_list(temp->val);
        }
    }

    void swap(List<T> &other) noexcept
    {
        // Standard swap for the pointers
        Node<T> *tempHead = head;
        head = other.head;
        other.head = tempHead;

        Node<T> *tempTail = tail;
        tail = other.tail;
        other.tail = tempTail;

        // Swap the sizes
        int tempSize = size;
        size = other.size;
        other.size = tempSize;
    }

    // This only works on the sorted lists , so the lists must be sorted before.
    // The other list is nullified.
    // The Answered list will be sorted.
    // This doesn't preserve the index positions.
    // It preserves the positions inside each list.
    // E.g : 10,30,50 and 20,40,60,70 then we have 10,20,30,40,50,60,70.
    // See 10 is always behind 30 and 30 is always behind 50 in both list 1 and final answer.

    // Here function predicate is a default argument so we can replace it by our own functions.
    // 1) Use a function outside main.
    // 2) Use in-line lambda Expression.
    // 3) Use a functor.
    void merge_on_sorted_only(List<T> &other, std::function<bool(T, T)> comp = std::less<T>())
    {
        if (!other.head)
            return;
        Node<T> dummy;
        Node<T> *curr = &dummy;
        Node<T> *p1 = head, *p2 = other.head;

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
            curr = curr->next;

            if (p1)
            {
                curr->next = p1;
            }
            else
            {
                curr->next = p2;
            }

            head = dummy.next;

            Node<T> *t = head;
            if (t)
            {
                while (t->next)
                    t = t->next;
            }
            tail = t;

            size += other.size;
            other.head = other.tail = nullptr;
            other.size = 0;
        }
    }

    // Returns the index of the value, or -1 if not found
    int linear_search(const T &key) const
    {
        Node<T> *curr = head;
        int index = 0;

        while (curr != nullptr)
        {
            if (curr->data == key)
            {
                return index;
            }
            curr = curr->next;
            index++;
        }
        return -1; // Not found
    }

    // Helper function to find the middle node in a specific range
    Node<T> *get_middle(Node<T> *start, Node<T> *end) const
    {
        if (start == nullptr)
            return nullptr;

        Node<T> *slow = start;
        Node<T> *fast = start->next;

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

    // Binary Search requires Middle element.
    // Binary Search is not efficient for linked list.
    // Linear Search is efficient as this one takes O(nlogn)
    int binary_search(const T &key) const
    {
        // Binary Search ONLY works if the list is sorted!
        Node<T> *start = head;
        Node<T> *end = nullptr;

        while (start != end)
        {
            Node<T> *mid = get_middle(start, end);

            if (mid == nullptr)
                return false;

            if (mid->data == key)
            {
                return true;
            }
            else if (mid->data < key)
            {
                start = mid->next;
            }
            else
            {
                end = mid;
            }
        }
        return false;
    }
    void display()
        {
            Node *temp = head;
            while(temp!=nullptr)
            {
                cout<<temp->val<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }
};
