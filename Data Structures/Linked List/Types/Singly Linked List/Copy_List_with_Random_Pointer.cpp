#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *random;
    Node(int data = 0, Node *temp = nullptr, Node *r = nullptr) : data(data), next(temp), random(r) {}
};

class List
{
    Node *head;

public:
    List()
    {
        head = nullptr;
    }
    void push_front_list(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void push_back_list(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void pop_front_list()
    {
        if (!head)
            return;

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back_list()
    {
        if (!head)
            return;

        if (!head->next)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node *temp = head;
            // Move to the second-to-last node
            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    /*
    A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.
    Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.
    For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.
    Return the head of the copied linked list.
    E.g :
    Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
    */

    // 1) We make a new linked list copying the previous one's next and random pointers.
    // We easily traverse the original list and make a new list with next pointers.
    // For the random pointers , we have to use addresses.
    // For a node's random pointer , its address cannot be the same as the new list's random pointers.
    // So we traverse original list and take each original list's random pointer.
    // As soon as we find original list's one node's random pointer by moving forward , we also find the new list's random pointer in exact same steps.
    // So we just return the new list's node address at those exact steps travelled by original list's one node to find original list's node's random pointer.
    // We do this to find all the random pointers for our new list.
    // Time : O(n^2)
    // Extra Space : O(1)
    // Total Space : O(n)

    Node *copyRandomList(Node *head)
    {
        Node *headCopy = new Node(0);
        Node *tailCopy = headCopy;
        Node *temp = head;
        while (temp)
        {
            tailCopy->next = new Node(temp->data);
            tailCopy = tailCopy->next;
            temp = temp->next;
        }
        tailCopy = headCopy;
        headCopy = headCopy->next;
        delete tailCopy;
        tailCopy = headCopy;
        temp = head;
        while (temp)
        {
            tailCopy->random = bring_random_ptr(head, headCopy, temp->random);
            tailCopy = tailCopy->next;
            temp = temp->next;
        }
        return headCopy;
    }
    Node *bring_random_ptr(Node *head1, Node *headCopy1, Node *x)
    {
        if (x == nullptr)
        {
            return nullptr;
        }
        while (head1 != x)
        {
            head1 = head1->next;
            headCopy1 = headCopy1->next;
        }
        return headCopy1;
    }

    // 2) By using unordered map :
    // Same as above , but now finding the random pointers iteratively , we use unordered map for that.
    // We make a map as <Node *, Node *> where our key is the original list nodes and values are new list's nodes.
    // Now when we want to find any random pointer for new list , we simply search original list's random pointer to get that random pointer's address and see where this original random pointer is mapped to the new list's node address so it gives us answer instantly for the new random pointer for this node in O(1).
    // Time : O(n)
    // Space : O(n)
    Node *copyRandomList2(Node *head)
    {
        Node *headCopy = new Node(0);
        Node *tailCopy = headCopy;
        Node *temp = head;
        while (temp)
        {
            tailCopy->next = new Node(temp->data);
            tailCopy = tailCopy->next;
            temp = temp->next;
        }
        tailCopy = headCopy;
        headCopy = headCopy->next;
        delete tailCopy;
        tailCopy = headCopy;
        temp = head;
        unordered_map<Node *, Node *> m;
        while (temp)
        {
            m[temp] = tailCopy;
            tailCopy = tailCopy->next;
            temp = temp->next;
        }
        temp = head;
        tailCopy = headCopy;
        while (temp)
        {
            tailCopy->random = m[temp->random];
            tailCopy = tailCopy->next;
            temp = temp->next;
        }
        return headCopy;
    }

    // 3) We simply place the new list in between original list like :
    // Original List : 1->2->3->4->5 and New List : 1->2->3->4->5
    // New Configuration : 1->1->2->2->3->3->4->4->5->5.
    // We placed each new list node right to the next node in the original list.
    // Each copy is right next to its original node.
    // So we can now access random pointer of new list node by taking random pointer of original list node and when we do that , we know its random pointer must be the next one.
    // So in this way we get random pointer of new list node by taking right next node of the random pointer in original list node.
    // Then we both again and return the copied list.
    // Time : O(n)
    // Space : O(1)
    Node *copyRandomList3(Node *head)
    {
        Node *headCopy = new Node(0);
        Node *tailCopy = headCopy;
        Node *temp = head;
        // Copy the nodes
        while (temp)
        {
            tailCopy->next = new Node(temp->data);
            tailCopy = tailCopy->next;
            temp = temp->next;
        }

        tailCopy = headCopy;
        headCopy = headCopy->next;
        delete tailCopy;
        tailCopy = headCopy;

        // Make new configuration :
        Node *curr1 = head;
        Node *curr2 = headCopy;
        Node *front1, *front2;
        while (curr1)
        {
            front1 = curr1->next;
            front2 = curr2->next;
            curr1->next = curr2;
            curr2->next = front1;
            curr1 = front1;
            curr2 = front2;
        }

        // Now we find the random pointers for the new list :
        curr1 = head;
        while (curr1)
        {
            curr2 = curr1->next;
            // Just one check , if curr1->random points to null , then we don't have to assign.
            if (curr1->random)
            {
                curr2->random = curr1->random->next;
            }
            curr1 = curr2->next;
        }

        // Reverting both lists back
        curr1 = head;
        curr2 = headCopy;
        while (curr1)
        {
            curr1->next = curr2->next;
            curr1 = curr1->next;
            // This check prevents us to access the null pointer
            // When we have 1->1->2->2->3->3->4->4->5->5->Null , curr1 points to 1st 5 and curr2 at 2nd 5.
            // Now when we assign curr1's next to curr2's next , it points to Null , and then move curr1 to null
            // So now when we are doing curr2->next to curr1's next , we must check otherwise we will be accessing invalid memory because curr1 is already null.
            // So we must make sure if curr1 or curr2->next is available.
            if (curr1) // curr2->next
            {
                curr2->next = curr1->next;
            }
            curr2 = curr2->next;
        }
        return headCopy;
    }

    void print_list()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
int main()
{

    return 0;
}