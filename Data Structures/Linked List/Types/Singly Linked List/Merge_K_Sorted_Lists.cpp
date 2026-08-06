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
    Node(int data = 0, Node *temp = nullptr, Node *b = nullptr) : data(data), next(temp) {}
};

class List
{
    Node *head;

public:
    List()
    {
        head = nullptr;
    }

    // This problem asks us to merge all the K-Sorted Linked lists into a single sorted linked list.
    // This is similar to the flattening linked list.
    // 1) Keep merging the two lists until we have done all 'k'.
    // Time : O(Nk) , Space : O(1)
    Node *mergeKLists(vector<Node *> &lists)
    {
        if (lists.size() <= 0)
        {
            return nullptr;
        }

        Node *root = lists[0];
        for (int i = 1; i < lists.size(); i++)
        {
            root = merge_sorted_Lists(root, lists[i]);
        }
        return root;
    }

    // Space : O(1) and Time : O(min(m,n)).
    Node *merge_sorted_Lists(Node *another_head1, Node *another_head2)
    {
        Node *head = new Node(0);
        Node *curr = head;

        Node *head1 = another_head1;
        Node *head2 = another_head2;

        while (head1 && head2)
        {
            if (head1->data <= head2->data)
            {
                curr->next = head1;
                head1 = head1->next;
                curr = curr->next;
                curr->next = nullptr;
            }
            else
            {
                curr->next = head2;
                head2 = head2->next;
                curr = curr->next;
                curr->next = nullptr;
            }
        }
        if (head1)
        {
            curr->next = head1;
        }
        else
        {
            curr->next = head2;
        }

        while (curr->next != nullptr)
        {
            curr = curr->next;
        }

        curr = head;
        head = head->next;
        delete curr;
        return head;
    }

    // 2) Using Merge Sort Algorithm
    // Works best for linked list.
    // Time Complexity : O(N Logk) , Space Complexity : O(logk)

    Node *mergeKLists(vector<Node *> &lists)
    {
        merge_sort(lists, 0, lists.size());
        return lists[0];
    }
    void merge_sort(vector<Node *> &lists, int start, int end)
    {
        if (start >= end)
        {
            return;
        }
        int mid = start + (end - start) / 2;
        merge_sort(lists, start, mid);
        merge_sort(lists, mid + 1, end);

        lists[start] = merge_sorted_Lists(lists[start], lists[mid + 1]);
    }
};
int main()
{

    return 0;
}
