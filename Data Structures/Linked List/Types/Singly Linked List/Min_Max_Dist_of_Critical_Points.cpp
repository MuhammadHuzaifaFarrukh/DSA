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
    A critical point in a linked list is defined as either a local maxima or a local minima.
    A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.
    A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.
    Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.
    Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points.
    If there are fewer than two critical points, return [-1, -1].

    Input: head = [3,1]
    Output: [-1,-1]
    Explanation: There are no critical points in [3,1].

    Input: head = [1,3,2,2,3,2,2,2,7]
    Output: [3,3]
    Explanation: There are two critical points:
    - [1,3,2,2,3,2,2,2,7]: The second node is a local maxima because 3 is greater than 1 and 2.
    - [1,3,2,2,3,2,2,2,7]: The fifth node is a local maxima because 3 is greater than 2 and 2.
    Both the minimum and maximum distances are between the second and the fifth node.
    Thus, minDistance and maxDistance is 5 - 2 = 3.
    Note that the last node is not considered a local maxima because it does not have a next node.

    Input: head = [5,3,1,2,5,1,2]
    Output: [1,3]
    Explanation: There are three critical points:
    - [5,3,1,2,5,1,2]: The third node is a local minima because 1 is less than 3 and 2.
    - [5,3,1,2,5,1,2]: The fifth node is a local maxima because 5 is greater than 2 and 1.
    - [5,3,1,2,5,1,2]: The sixth node is a local minima because 1 is less than 5 and 2.
    The minimum distance is between the fifth and the sixth node. minDistance = 6 - 5 = 1.
    The maximum distance is between the third and the sixth node. maxDistance = 6 - 3 = 3.

    */

    // 1) By using a Vector Indexes :
    // We store all the critical points indexes in a vector.
    // If the critical points are less than 2 , then we can immediately return {-1,-1} from right there without checking further.
    // Then for the max distance , it is between the first and last critical point so we just find by doing v.back()-v.front().
    // Then for min distance , we iterate through our indexes vector and find the minimum distance between any two critical points and save it as our min dist.
    // Time : O(n)
    // Space : O(n)
    vector<int> nodesBetweenCriticalPoints(Node *head)
    {
        // if (!head || !head->next)    // For zero or 1 size list.
        // {
        //     return {-1, -1};
        // }
        vector<int> v;
        Node *curr = head->next;
        Node *prev = head;
        int index = 1;
        while (curr)
        {
            if (curr->next)
            {
                if (prev->data > curr->data && curr->data < curr->next->data)
                {
                    v.push_back(index); // Local Minima
                }
                else if (prev->data < curr->data && curr->data > curr->next->data)
                {
                    v.push_back(index); // Local Maxima
                }
            }
            prev = curr;
            curr = curr->next;
            index++;
        }

        if (v.size() < 2)
        {
            return {-1, -1};
        }

        int maxDist = v.back() - v.front(); // Last Critical Point - First one.
        int minDist = INT_MAX;
        for (int i = 1; i < v.size(); i++)
        {
            minDist = min(minDist, v[i] - v[i - 1]);
        }
        return {minDist, maxDist};
    }

    // Without using Extra Space :
    // Our logic is still same , for getting minDist and maxDist.
    // For finding maxDist , we have two pointers first and last that keep the indexes of the first and last critical points.
    // When we find a critical point we check if first is updated or not , if not then we update the first critical point and if yes then we don't do anything and update/overwrite the last critical point.
    // Last critical point is always updated to find max distance as max as possible.
    // Once the loop finishes , we see if first or last is still -1 , that is that we found 0 or 1 critical points, if this happens we return {-1,-1}, otherwise we move on.
    // Now for the min Distance , we have to calculate it during our loop traversal.
    // We simply keep a previous critical point index that will be the most recent critical point found.
    // When first is updated , we update it too.
    // When we find the critical point other than first , we calculate the minimum distance between the previous critical point index and the current index.
    // After this we update the last critical point and also the previous critical point index.
    // Time : O(n)
    // Space : O(1)
    vector<int> nodesBetweenCriticalPoints2(Node *head)
    {
        Node *curr = head->next;
        Node *prev = head;
        int minDist = INT_MAX, maxDist = 0;
        int first = -1, last = -1;
        int prevcr = -1;
        int index = 1;
        while (curr)
        {
            if (curr->next)
            {
                if (prev->data > curr->data && curr->data < curr->next->data)
                {
                    if (first == -1)
                    {
                        first = index;
                        prevcr = first;
                    }
                    else
                    {
                        minDist = min(minDist, index - prevcr);
                        last = index;
                        prevcr = index;
                    }
                }
                else if (prev->data < curr->data && curr->data > curr->next->data)
                {
                    if (first == -1)
                    {
                        first = index;
                        prevcr = first;
                    }
                    else
                    {
                        minDist = min(minDist, index - prevcr);
                        last = index;
                        prevcr = index;
                    }
                }
            }
            prev = curr;
            curr = curr->next;
            index++;
        }
        if (first == -1 || last == -1)
        {
            return {-1, -1};
        }
        maxDist = last - first;
        return {minDist, maxDist};
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