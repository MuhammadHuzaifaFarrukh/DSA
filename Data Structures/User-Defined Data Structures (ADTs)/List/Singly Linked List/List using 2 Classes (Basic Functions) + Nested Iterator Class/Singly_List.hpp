#pragma once
#include <iostream>

using namespace std;
//You can also use this Node class Nested inside List
class Node
{
public:
    int val;
    Node *next;
    Node(int v = 0, Node *n = nullptr) : val(v), next(n) {}
};
class List
{
    Node *head, *tail;
public:
    int size = 0;
    //You can also keep the count of size if you want
    List()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void push_front_list(int val)
    {
        Node *newNode = new Node(val);
        if(head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        size++;
        return;
    }
    //Can also use one line code : start = new Node(val , start) instead of all the code for push_front

    void push_back_list(int val)
    {
        Node *newNode = new Node(val);
        if(head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next= newNode;
            tail = newNode;

        }
        size++;
        return ;
    }
    //If our Linked List class doesn't have a tail pointer then we need to iterate through the list for adding the new element at right side

    void pop_front_list()
    {
        if(head == nullptr)
        {
            cout<<"List is empty "<<endl;
        }
        else
        {
            Node *temp = head;
            head = head->next;
            temp->next = nullptr;   //Disconnect temp from the list (Optional here)
            size--;
            delete temp;    //Now Deallocate the Node from the list
        }
        return ;
    }
    /*
    We can also do for else part :
    Node *temp = head->next;
    head->next = nullptr;   (Optional here)
    delete head;
    head = temp;
    */

    void pop_back_list()
    {
        if(head == nullptr)
        {
            cout<<"List is empty "<<endl;
        }
        else
        {
            Node *temp = head;
            while(temp->next != tail) //Can also use temp->next->next != nullptr
            {
                temp = temp->next;
            }
            temp->next = nullptr;
            delete tail;    //Delete the last node
            tail = temp;    //Update tail to previous node
            size--;
        }
        return ;
    }
    void insert_node(int val, int ind)
    {
        if(ind<0 || ind>size)
        {
            cout<<"Invalid Index "<<endl;
            return;
        }
        else if(ind == 0)   //Push_front() Case
        {
            push_front_list(val);
            return ;
        } //If you want then you can also write push_back case but its not needed here
        else if(ind == size)
        {
            push_back_list(val);
            return ;
        }
        else
        {
            Node *temp = head;
            for(int i = 0 ; i<ind-1 && temp!= nullptr ; i++)
            {
                temp = temp->next;
            }

            // Check if we reached end of list prematurely
            if (temp == nullptr)
            {
                push_back_list(val);
                return;
            }
            //We could also use ind == size instead of temp==nullptr to check for the last position and do push back
            Node *newNode = new Node(val);
            newNode->next = temp->next;
            temp->next = newNode;
            size++;
            return ;
        }
    }
    void remove_node_val(int val)
    {
        // Handle empty list
        if (head == nullptr)
        {
            return;
        }

        // Remove from beginning if value matched
        while (head != nullptr && head->val == val)
        {
            pop_front_list();
        }

        // Remove from middle/end
        Node* temp = head;
        while (temp != nullptr && temp->next != nullptr)
        {
            if (temp->next->val == val)
            {
                Node* newNode = temp->next;
                temp->next = newNode->next;

                // Update tail if deleting last node
                if (newNode == tail)
                {
                    tail = temp;
                }

                delete newNode;
                size--;
            }
            else
            {
                temp = temp->next;
            }
        }
        return ;
    }
    void remove_node(int ind)
    {
        if(ind < 0 || ind >= size)
        {
            cout<<"Invalid Size "<<endl;
            return ;
        }
        else if(ind == 0 )
        {
            pop_front_list();
        }
        else if(ind == size-1)
        {
            pop_back_list();
        }
        else
        {
            // Find the node BEFORE the one to delete
            Node* temp = head;
            for(int i = 0; i < ind - 1; i++)
            {
                temp = temp->next;
            }
            // Node to delete is temp->next
            Node* newNode = temp->next;
            temp->next = newNode->next;  // Bypass the node to delete (Changing the connection)

            newNode->next = nullptr;     // Optional: Disconnect before delete
            delete newNode;              // Delete the node
            size--;
        }
    }
    int linear_search(int target)
    {
        Node *temp = head;
        int ind = 0;
        while(temp != nullptr)
        {
            if(temp->val == target)
            {
                return ind;
            }
            temp = temp->next;
            ind++;
        }
        return -1;
    }

    int at_list(int ind)
    {
        if(ind<0 || ind>=size)
        {
            cout<<"Invalid Position "<<endl;
            return -1;
        }
        Node *temp = head;
        for(int i = 0 ; i<ind && temp != nullptr ; i++)
        {
            temp = temp->next;
        }
        return (temp->val);
    }

    int& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            //throw std::out_of_range("List index out of range");
            cout<<"Invalid Index "<<endl;
        }
        Node* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->val;
    }

    //Same Logic for all other relation operators != , < , > , <= , >=
    // This function can also be a friend of the List Class written outside
    bool operator==(const List& other)  //Won't work backwards if not a friend function (a==b) OK  But (b==a) Error if not friend
    {
        if (size != other.size)
        {
            return false;
        }

        Node* temp1 = head;
        Node* temp2 = other.head;

        while (temp1!= nullptr && temp2 != nullptr)
        {
            if (temp1->val != temp2->val)
            {
                return false;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        return true;
    }

    //Using Selection Sort on List :
    void selectionSort()
    {
        if (head == nullptr || head->next == nullptr)
        {
            return;  // Empty list or single node already sorted
        }

        Node* current = head;

        while (current != nullptr)
        {
            // Find the minimum node in the remaining list
            Node* minNode = current;
            Node* temp = current->next;

            while (temp != nullptr)
            {
                if (temp->val < minNode->val)
                {
                    minNode = temp;
                }
                temp = temp->next;
            }

            // Swap values between current and minNode
            if (minNode != current)
            {
                int swapVal = current->val;
                current->val = minNode->val;
                minNode->val = swapVal;
            }

            // Move to next node
            current = current->next;
        }
    }

    void append_shared(List& other)    //std::list::merge but without sorting
    {
        if (other.head == nullptr)
        {
            return;  // nothing to append
        }
        if (head == nullptr)    // if this list is empty then other list becomes this list
        {
            head = other.head;
            tail = other.tail;
            return;
        }
        else
        {
            tail->next = other.head;
            tail = other.tail;
        }
        size += other.size;
        //Here both lists share the other one list nodes so can be problematic if modify one other is modified as well
    }
    void append(const List& other)  //Copy the appending list
    {
        for (Node* temp = other.head; temp!= nullptr; temp= temp->next)
        {
            push_back_list(temp->val);  // copy each value
        }
    }

    void join(List& other)  //Just like std::list::splice function that copies but then empties the other list
    {
        if (other.head == nullptr)
        {
            return;
        }

        if (head == nullptr)
        {
            head = other.head;
            tail = other.tail;
        }
        else
        {
            tail->next = other.head;
            tail = other.tail;
        }
        size += other.size;

        // Now empty other (like std::list::splice)
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    void print_list()
    {
        Node *temp = head;
        while(temp!=nullptr)
        {
            cout<<temp->val<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
    void clear_list()
    {

        Node* temp = head;
        //You can also call pop_front() or pop_back() in a while loop
//        while(temp != nullptr)
//        {
//            pop_front();
//        }
        while (temp != nullptr)
        {
            Node* nextNode = temp->next;  // Save next pointer first
            temp->next= nullptr;          // Optional (Remove the connection)
            delete temp;                  // Delete current node
            temp = nextNode;              // Move to next node
        }
        head = tail = nullptr;  //Optional (Already Dangling Pointers)
        size = 0;
    }
    ~List()
    {
        clear_list();
    }
    //Make your own copy constructor and assignment operator for deep copy
    // Copy Constructor :
    List(const List& other)
    {
        head = nullptr;
        if (other.head != nullptr)
        {
            //Copy the Size Also :
            size = other.size;

            // Copy first node
            head = new Node(other.head->val);
            Node* current = head;
            Node* otherCurrent = other.head->next;

            // Copy remaining nodes
            while (otherCurrent != nullptr)
            {
                current->next = new Node(otherCurrent->val);
                current = current->next;
                otherCurrent = otherCurrent->next;
            }
        }
    }

    // Copy Assignment Operator
    List& operator=(const List& other)
    {
        if (this != &other)    // Protect against self-assignment
        {
            // Clear current list
            clear_list();

            //Copy the Size Also :
            size = other.size;

            // Copy from other list (same logic as copy constructor)
            if (other.head!= nullptr)
            {
                head= new Node(other.head->val);
                Node* current = head;
                Node* otherCurrent = other.head->next;

                while (otherCurrent != nullptr)
                {
                    current->next = new Node(otherCurrent->val);
                    current = current->next;
                    otherCurrent = otherCurrent->next;
                }
            }
        }
        return *this;
    }

    friend ostream& operator << (ostream &out, const List &list)
    {
        for (Node *temp = list.head; temp != nullptr ; temp = temp -> next)
            out << temp -> val << ' ';
        out << '\n';
        return out;
    }

    //Using Iterator (nested class) :
    class Iterator
    {
        Node *ptr; //Points to current Node
    public:
        Iterator(Node* p = nullptr) : ptr(p) {}
        int& operator*()
        {
            return (ptr->val); // Can use as Lvalue and Rvalue both
        }
        int* operator->()   //Can use as Lvalue and Rvalue both
        {
            return &(ptr->val);
        }
        Iterator operator++()   //You may add safety check if the ptr crosses the tail , though user's responsibility not iterator's
        {
            ptr = ptr->next;
            return (*this);
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ptr = ptr->next;
            return (*this);
        }
        //Didn't add minus cause singly linked list doesn't go backward
        // You may write them and then throw exception when anyone uses it-- or --it
        bool operator==(const Iterator& it)
        {
            return (ptr== it.ptr);
        }

        bool operator!=(const Iterator& it)
        {
            return (ptr!=it.ptr);
        }
        Iterator(const Iterator& it) : ptr(it.ptr) {} //Optional as we aren't using any dynamic allocation in iterator class
        Iterator& operator = (const Iterator& it)  //Optional
        {
            if(this != &it)
            {
                ptr = it.ptr;
            }
            return (*this);
        }
        ~Iterator() {}  //Optional
    };

    //Using begin() and end() functions we can now use List class in the for-range based loop
    Iterator begin() //The Head node always points to First Node
    {
        return Iterator(head);
    }
    Iterator end()  //The Last node always points to nullptr
    {
        //return Iterator(tail->nullptr);
        return Iterator(nullptr);
    }

};

