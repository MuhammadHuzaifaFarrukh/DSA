#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;

// Priority Queue is actually a heap (either min or max) which is a complete binary tree.
// In C++ , priority queue is a linear data structure and a derived container.
// It uses std::vector<T> (Adaptee) and also less<T> so it uses vector and max heap by default.
// We can write greater<int> to make it work like min heap.

// It can even work with those containers that have random access iterators like std::deque , std::array etc.
// But not with std::list , std::set , std::map etc as they don't have random access iterators or manage their memory by themselve like Red-Black Tree.
// And also not with std::queue , std::stack cause they are already derived containers and hide their functionality while std::priority_queue needs to see the functions.

// We can make it work for other than built in data types as well :
// 1) You can also make your own functors of greater<T>() and less<T>() and allow it to work for any data type , any objects , any UDT also.
// 2) For making it for UDTs , they must have < , > overloaded also so that we can have less<myClass> or greater<myClass>.

int main()
{
    // --- 1. THE AUTOMATIC WAY (Container Adapter) ---
    // This internally calls make_heap/push_heap for you.
    priority_queue<int> pq; // uses vector<int> and make_heap()
    // Can be used for any specific class as well instead of normal int,float,char etc
    // For that , we need either overload of <,> in our class or functors for < and > in separate structs.

    pq.push(10);
    pq.push(30);
    pq.push(20);
    pq.push(5);

    cout << "Priority Queue Top (Highest Priority): " << pq.top() << endl; // Should be 30
    pq.pop();                                                              // Internally calls pop_heap and vector::pop_back
    cout << "New Top after pop: " << pq.top() << endl;                     // Should be 20

    cout << "------------------------------------" << endl;

    // --- 2. THE MANUAL WAY (The "Under the Hood" Logic) ---
    // This is what the priority_queue class is doing behind the scenes.
    vector<int> v = {10, 30, 20, 5};

    // Transform the vector into a heap - O(N)
    make_heap(v.begin(), v.end());
    cout << "Manual Heap Root: " << v.front() << endl; // 30

    // To add a new element manually:
    v.push_back(40);                                                   // 1. Add to the end of the vector
    push_heap(v.begin(), v.end());                                     // 2. "Sift up" to maintain heap property
    cout << "Manual Heap Root after adding 40: " << v.front() << endl; // 40

    // To remove the top element manually:
    pop_heap(v.begin(), v.end()); // 1. Swaps root with last element and "Sifts down"
    int highest = v.back();       // 2. The old root is now at the end
    v.pop_back();                 // 3. Actually remove it from the vector

    cout << "Manual Heap Root after popping 40: " << v.front() << endl; // 30

    return 0;
}
