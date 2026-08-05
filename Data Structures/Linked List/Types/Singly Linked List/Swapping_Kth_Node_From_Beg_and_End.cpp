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
    Node(int data = 0, Node *temp = nullptr) : data(data), next(temp) {}
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
        {
            return;
        }

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
    You are given the head of a linked list, and an integer k.
    Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
    Input: head = [1,2,3,4,5], k = 2
    Output: [1,4,3,2,5]
    */

    // 1) Swapping Actual Values instead of nodes.
    // We count total nodes and move the pointer total - k nodes to get the kth node from the end.
    // We then swap value of kth node from beginning and kth node from the end.
    // Time : O(n)
    // Space : O(1)
    Node *swapNodes(Node *head, int k)
    {
        int count = 0;
        Node *temp = head;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        int rem = count - k;
        Node *kth = head;
        temp = head;
        while (rem-- && kth)
        {
            kth = kth->next;
        }
        k--;
        while (k-- && temp)
        {
            temp = temp->next;
        }
        swap(temp->data, kth->data);
        return head;
    }

    // 2) Swapping values instead of actual nodes using slow/fast pointers.
    // We move the first pointer to the kth node from beginning.
    // Now there are exactly k-1 nodes between the kth node and the head.
    // So we put a fast pointer at the kth node and slow pointer at the head.
    // Now this same gap will be present between kth node from end and the last node.
    // So we move the fast and slow pointers one by one and by the time fast pointer is at the last node , slow pointer is at the kth node from the end.
    // This is the exact gap as we said earlier.
    // Now we just swap values between slow and the first pointer.
    // Time : O(n)
    // Space : O(1)
    Node *swapNodes(Node *head, int k)
    {
        Node *first = head;

        for (int i = 1; i < k; ++i)
        {
            first = first->next;
        }

        Node *fast = first;
        Node *second = head;

        while (fast->next)
        {
            fast = fast->next;
            second = second->next;
        }

        swap(first->data, second->data);
        return head;
    }

    // 3) Swapping actual nodes :
    // We do the same procedure as above.
    // But for swapping actual nodes , we require 4 things.
    // a) Kth Node from Beg  b) Kth Node from End  c) Prev Node of Kth Node from Beg   d) Prev Node of Kth Node from End
    // So we just find out these 4 things.
    // Here we get 4 cases :

    // a) When first and the second node are same. e.g 1->2->3 and k = 2 (Odd length list with middle node)
    // Here both are the same so actually no swapping is required , and we just return the list as it is.

    // b) When first and second are side by side e.g : 0->1->2->3 and k = 2 , then first->next = second.
    // So now we have to just make 0->2 and 1->3 and then 2->1 so it becomes 0->2->1->3
    // If the previous node of kth from beginning doesn't exist then we change the head node to second because it shows that kth node from beginning is actually the first node of list and if first and second are adjacent then after swap , second will be the head.
    // Like : 1->2->Null , k = 1 , so we change head to 2 , and then make 2->1 and 1->Null and it becomes like 2->1->Null.

    // c) When first and second are adjacent with second before first e.g : 1->2->3->4->5->6 and k = 4.
    // Here we see that second is 3 and first is 4, second is before the first so we do the same thing as we did earlier.
    // We join 2->4 and 3->5 and then 4->3 , to make it 1->2->4->3->5->6.
    // Also if previous node of the kth node from end is null , then we make head to the first node.

    // d) First and second are not adjacent nodes , the usual case which we think of e.g : 1->2->3->4->5->6->7->8->9->10 and k = 3
    // Now first is at 3 and second at 8 , we join 2->8 , 7->3 , 3->9 , 8->4 which makes 1->2->8->4->5->6->7->3->9->10.
    // So we actually move prev first's next to second and prev second's next to first , then first's next to second's next and second's next to first.
    // Incase prev first and prev second nodes are null , then we change heads.
    // Time : O(n)
    // Space : O(1)
    Node *swapNodes(Node *head, int k)
    {
        Node *first = head;
        Node *prevfirst = nullptr;

        for (int i = 1; i < k; ++i)
        {
            prevfirst = first;
            first = first->next;
        }

        Node *fast = first;
        Node *second = head;
        Node *prevsec = nullptr;

        while (fast->next)
        {
            fast = fast->next;
            prevsec = second;
            second = second->next;
        }

        // Case 1: Same node (e.g., middle node in odd-length list) 1->2->3 and k = 2
        if (first == second)
        {
            return head;
        }

        // Case 2: Nodes are adjacent (first comes immediately before second) e.g 1->2 and k = 1 or 0->1->2->3 and k = 2
        if (first->next == second)
        {
            if (prevfirst)
            {
                prevfirst->next = second;
            }
            else
            {
                head = second; // Update head if first was head
            }
            first->next = second->next;
            second->next = first;
            return head;
        }

        // Case 3: Nodes are adjacent (second comes immediately before first)
        if (second->next == first)
        {
            if (prevsec)
            {
                prevsec->next = first;
            }
            else
            {
                head = first; // Update head if second was head
            }
            second->next = first->next;
            first->next = second;
            return head;
        }

        // Case 4: Non-adjacent nodes
        if (prevfirst)
        {
            prevfirst->next = second;
        }
        else
        {
            head = second; // Update head if first was head
        }

        if (prevsec)
        {
            prevsec->next = first;
        }
        else
        {
            head = first; // Update head if second was head
        }

        Node *firstnext = first->next;
        first->next = second->next;
        second->next = firstnext;

        return head;
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