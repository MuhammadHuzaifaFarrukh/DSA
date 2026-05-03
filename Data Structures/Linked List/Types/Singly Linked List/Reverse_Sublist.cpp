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

    // We use 4-5 pointers for reversal.
    // First we find the total number of elements.
    // Then we find the left most node by traversal.
    // Then we apply 4 pointer technique.
    // Place 1 at before left , 1 at left , the other 2 (or 3) will be used in reversing
    // After reversal , 1 (or 2) will be at just after right and 1 will be at right node. 
    // So we just join the before left's next with right node and we join the 1 at left with the 1 (or 2) just after right.
    // So this is how we do it.

    // If left and right are equal no need to reverse them.

    Node *reverseBetween(Node *head, int left, int right)
    {
        /*
        // You can remove this if you are using dummy node.
        if (!head || !(head->next) || left == right)
        {
            return head;
        }
        */
        int x = right - left + 1;
        Node *first = new Node(0);
        first->next = head;
        head = first;
        first = head;

        Node *second;
        for (int i = 0; i < left - 1; i++)
        {
            first = first->next;
        }
        Node *prev, *future;
        Node *third;

        second = first->next;
        third = second;

        prev = first;

        // Single node will be handled here.
        while (second != nullptr && x)
        {
            future = second->next;
            second->next = prev;

            prev = second;
            second = future;
            x--;
        }

        // left == right will be handled here.
        third->next = second;
        first->next = prev;

        first = head;
        head = head->next;
        delete first;
        return head;
    }
};
int main()
{

    return 0;
}
