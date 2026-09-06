#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

class Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->data > b->data;
    }
};
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

    /*
    You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
    Merge all the linked-lists into one sorted linked-list and return it.

    Input: lists = [[1,4,5],[1,3,4],[2,6]]
    Output: [1,1,2,3,4,4,5,6]
    Explanation: The linked-lists are:
    [
    1->4->5,
    1->3->4,
    2->6
    ]
    merging them into one sorted linked list:
    1->1->2->3->4->4->5->6

    Input: lists = []
    Output: []

    Input: lists = [[]]
    Output: []
    */

    // 1a) We could just join all these lists into a singly list new.
    // Then we just apply merge sort on all of the new list.
    // Time : O(nlogn)      where n = mk
    // Total Space : O(n)   where n = mk

    // This is similar to the flattening linked list / merge 2 sorted linked lists.
    // 1b) By using merge 2 Sorted Lists.
    // We know that we can easily merge two sorted list and return its head from the first list head.
    // We will do the same in a loop by keeping head on the first index 0 and keep joining this list with others for (k-1) times.
    // Time Complexity :
    // Suppose you have K lists, each containing m nodes (so total nodes N = K * m):
    // 1st Merge: Merge List 1 (m nodes) + List 2 (m nodes) -> 2m operations
    // 2nd Merge: Merge Result (2m nodes) + List 3 (m nodes) -> 3m operations
    // 3rd Merge: Merge Result (3m nodes) + List 4 (m nodes) -> 4m operations
    // ...
    // (K - 1)-th Merge: Merge Result ((K - 1) * m nodes) + List K (m nodes) -> Km operations
    // Total operations = 2m + 3m + 4m + ... + Km = m * (K * (K + 1) / 2) ≈ O(m * K^2) = mK*K = N*K = O(NK) where N=mK Number of nodes across all K sorted lists.
    // The earlier lists get re-traversed repeatedly with every single iteration!
    // Total Time : O(mk^2) or O(nk)
    // Space Complexity : O(1)
    // Note that nlogn < nk.
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

    // 2a) Using Merge Sort Algorithm
    // Works best for linked list.
    // We won't find mid or use the slow/fast pointers.
    // We just have to keep joining the lists.
    // As we are given an array , we can find mid using indexing.
    // All the lists given are already sorted , so we just keep dividing indexes until we are left with 2 indexes and then we merge them just by using merge 2 sorted lists.
    // We keep joining left sorted halves and right sorted halves , and eventually whole sorted list is returned at index 0.
    // This could be thought of as a recursive solution of the above though a little different.
    // Time Complexity :
    // Total Nodes of all K Lists combined = N and Total Levels = K.
    // Level 1 : Merge K lists into K/2 lists (Processed N Nodes).
    // Level 2 : Merge K/2 lists into K/4 lists (Processed N Nodes).
    // Level 3 : Merge K/4 lists into K/8 lists (Processed N Nodes).
    // Level logk : Merge 2 lists into 1 lists (Processed N Nodes).
    // Total Time = (Height)*(Work done in each Level) = O(logk * n) = O(nlogk) or O(mklogk) where n = mk (Assuming all 'k' lists are of size 'm')

    // Space : Recursive Stack goes to logk levels at most.
    // Total Space becomes : O(logk)

    Node *mergeKLists2(vector<Node *> &lists)
    {
        merge_sort(lists, 0, lists.size() - 1);
        return lists[0];
    }
    // The merge_sorted_Lists() function is above
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

    // 2b)
    // If we used iterative for above , we can reduce its space complexity to O(1) making it the best method out of all.
    // We know that recursive space was being logk.
    // So we set steps = 1 and keep increasing them as step*2 and also check if they are less than k.
    // This runs the outer loop in logk times.
    // Then we know if we have a list of 8 size , it will merge into 4 lists , then 4 lists will merge into 2 and then those 2 lists into 1.
    // So it took three steps (log8 = 3) and we had to join 4,2,1 times in inner loop.
    // So for that we increment i by step*2 at each level inside inner loop.
    // For the first level step =1 , so merging lists will be at 1 step distance , we can just do i+step to access them.
    // For the next inner iteration , we do step*2 increment in 'i' that allows it to skip past over this merged list.
    // Then when all inner are finished for first out iteration , we do step=step*2 so now we have to merge the list at double distance.
    // Time : O(nlogk)
    // Space : O(1)
    Node *mergeKLists2b(vector<Node *> &lists)
    {
        if (lists.empty())
            return nullptr;

        int k = lists.size();
        int step = 1;

        // Outer loop runs log(K) times
        while (step < k)
        {
            // Pairwise merge adjacent sub-lists
            for (int i = 0; i + step < k; i += step * 2)
            {
                lists[i] = merge_sorted_Lists(lists[i], lists[i + step]);
            }
            step *= 2; // Move to the next level of the merge tree
        }

        return lists[0];
    }

    // 3) We use min heap.
    // We simply put all the nodes inside a minheap.
    // Then we take out each node attach their next pointers to the next.
    // This gives us the complete sorted list using min-heap.
    // Note that we used a Custom Comparator as our linked list is customized.
    // Note that we used a dummy node for joining lists otherwise we would have to keep checking for null nodes or last or first nodes etc.
    // We are putting all the nodes together inside that can also cause duplicates to mess things up.
    // E.g : [[-1,-1,-1],[-2,-2,-2]] , now here if we put all the nodes , the comparator won't be able to decide on the basis of values.
    // The Min-Heap breaks ties based on its internal tree structure layout, which causes duplicate nodes from different lists to get interleaved or popped out of their original sequential order.
    // When it cannot see a>b , it uses array as a tree to see if it should return false or not.
    // In case of normal integers , when we push(1) , then again push(1) , the last pushed 1 may not be swapped cause it returned false for -1 > -1 false.
    // Now in case of linked list , we push a node whose next is not null and another node whose next is  null , so now when we pop , it swaps the last node whose next is null and deletes the top most node , but now when it had to heapify for the last node that had next as null , it simply sits at the top because it may contain equal values in its neighbours so no swapping will occur.
    // It is possible that it might pick the last node (-1) as the first node while any other node whose next is not null as last.
    // This can cause loops and errors in our list.
    // So we just write tail->next = nullptr , so the last node is really the end even if its next existed in the original list.
    // Time Complexity :
    // Suppose all list 'k' are of size 'm'.
    // Then time to push all the nodes in heap : mklog(mk)
    // Then we simply pop out all the nodes in heap : mklog(mk)
    // Total Time : O(mklogmk) or O(nlogn) where n=mk total number of nodes across all list.

    // Space Complexity :
    // We store all the list elements again : mk.
    // Space : O(mk) or O(n) where n=mk total number of nodes across all list.
    Node *mergeKLists3(vector<Node *> &lists)
    {
        if (lists.size() <= 0)
        {
            return nullptr;
        }
        priority_queue<Node *, vector<Node *>, Compare> pq;
        for (int i = 0; i < lists.size(); i++)
        {
            Node *temp = lists[i];
            while (temp)
            {
                pq.push(temp);
                temp = temp->next;
            }
        }
        Node *head = new Node(0);
        Node *tail = head;
        while (!pq.empty())
        {
            tail->next = pq.top();
            pq.pop();
            tail = tail->next;
        }
        tail->next = nullptr;
        return head->next;
    }

    // 4) We use Min-Heap but in optimized way this time.
    // We push all the heads of lists , not all nodes , just the heads of those lists.
    // We can also have list which is empty so we check as well if lists[i] is null or not.
    // Then we create a dummy node and keep attaching nodes to it.
    // In our min heap , we pop out the smallest valued node (using our Custom Comparator), and add it to our answer list.
    // Then we also check if this head has next or not , if not then we proceed , if yes , it means that we need to push this element into our min heap as well cause this can be a candidate for minimum element in the next iteration.
    // Here the duplicates won't trouble us because we are putting only 'k' nodes.
    // Heap can pick any node to put at tail's next out of 'k' nodes but then it checks whether its next is null or not.
    // So it puts the last node of that list whose mem address is greater at last place like it should've been and its next must be nullptr.
    // So we don't need to write null explicitly here.

    // Time Complexity :
    // Suppose all list 'k' are of size 'm'.
    // Then total time taken to build heap using 'k' heads : klogk.
    // Then for the popping out for remaining nodes (in worst case ) : (mk-k)logk.
    // Total time : (klogk + mklogk) or O(nlogk) where n = mk.

    // Space Complexity :
    // Our Heap only holds at most 'k' lists.
    // Space : O(k)
    Node *mergeKLists3(vector<Node *> &lists)
    {
        if (lists.size() <= 0)
        {
            return nullptr;
        }

        // If we know that our vector cannot contain an empty list , only then we would use this , otherwise our program will crash.
        // priority_queue<Node *, vector<Node *>, Compare> pq(lists.begin() , lists.end());
        priority_queue<Node *, vector<Node *>, Compare> pq;

        for (int i = 0; i < lists.size(); i++)
        {
            if (lists[i])
            {
                pq.push(lists[i]);
            }
        }
        Node *head = new Node(0);
        Node *tail = head;
        while (!pq.empty())
        {
            Node *temp = pq.top();
            tail->next = temp;
            pq.pop();
            if (temp->next)
            {
                pq.push(temp->next);
            }
            tail = tail->next;
        }
        return head->next;
    }

    // Method 4 and 2b are the most optimized methods.
};

int main()
{

    return 0;
}