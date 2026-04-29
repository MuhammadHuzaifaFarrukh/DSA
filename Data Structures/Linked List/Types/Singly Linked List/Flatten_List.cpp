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
    Node *bottom;
    Node(int data = 0, Node *temp = nullptr, Node *b = nullptr) : data(data), next(temp), bottom(b) {}
};

class List
{
    Node *head;

public:
    List()
    {
        head = nullptr;
    }

    // We take two heads at a time and merge them and keep doing this until we reach end of the list.
    // Space Complexity : O(1) , Time Complexity : O(mn^2)
    // Suppose we have a list whose each bottom height is total 'm' and then we have total list from start to end as next as 'n'
    // Each column : 'm' and Each row : 'n'.
    // Then for first merge , it would take time : O(min(m,m)) = m
    // Then for next : O(min(2m,m)) = m
    // Then m , m ,m and so on...
    // So for last we would have m.
    // So : m+m+m+m+...+m (total n-1 times) = m*(n-1) = O(m*n)
    Node *Flatten_List(Node *root)
    {
        if (!root)
        {
            return nullptr;
        }
        
        while (root->next)
        {
            Node *head1 = root;
            Node *head2 = root->next;
            Node *head3 = root->next->next;
            root = merge_sorted_Lists(head1,head2);
            root->next = head3;
        }
        return root;
    }


    // Time Complexity : O(min(m,n)) , Space Complexity : O(1)
    Node *merge_sorted_Lists(Node *another_head1, Node *another_head2)
    {
        Node *head = new Node(0);
        Node *tail = head;

        Node *head1 = another_head1;
        Node *head2 = another_head2;

        while (head1 && head2)
        {
            if (head1->data <= head2->data)
            {
                tail->bottom = head1;
                head1 = head1->bottom;
                tail = tail->bottom;
                tail->bottom = nullptr;
            }
            else
            {
                tail->bottom = head2;
                head2 = head2->bottom;
                tail = tail->bottom;
                tail->bottom = nullptr;
            }
        }
        if (head1)
        {
            tail->bottom = head1;
        }
        else
        {
            tail->bottom = head2;
        }

        return head->next;
    }
};
int main()
{

    return 0;
}