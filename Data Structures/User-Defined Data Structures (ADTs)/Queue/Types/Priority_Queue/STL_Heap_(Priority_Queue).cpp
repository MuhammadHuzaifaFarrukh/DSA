// range heap example
#include <iostream>  // std::cout
#include <algorithm> // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>    // std::vector

using namespace std;

/*
The heap data structure can be implemented in a range using STL which provides faster max or min item retrieval,
 and faster insertion and deletion on sorted data and also works as a sub-routine for heapsort.
*/
// std::priority_queue container uses std::make_heap()  
int main()
{
    int myints[] = {10, 20, 30, 5, 15};
    vector<int> v(myints, myints + 5); // Making Vector from C-Styled Array

    // By default make_heap is max_heap or you can mention less<T>
    make_heap(v.begin(), v.end()); // Orders vector into a Binary Heap
    cout << "initial max heap   : " << v.front() << '\n';

    pop_heap(v.begin(), v.end()); // It swaps the largest element in vector with last element. The last element is still accessible.
    v.pop_back();                 // Using this ensures that now , we remove that last element also.
    cout << "max heap after pop : " << v.front() << '\n';

    v.push_back(99);               // We add the element at last , it may or may not be largest
    push_heap(v.begin(), v.end()); // But this then checks that last element to be swapped with the front one or not.
    cout << "max heap after push: " << v.front() << '\n';
    // We could also have used make_heap but it would use O(N) cause it needs to check all the nodes again.
    // push_heap() just checks logn times from bottom to top (Step Up)

    sort_heap(v.begin(), v.end()); // Sorts by using Heap Sort : O(nlogn).

    cout << "final sorted range :";
    for (unsigned i = 0; i < v.size(); i++)
    {
        cout << " " << v[i];
    }

    cout << '\n';

    // For making min_heap :
    // Passing std::greater<T>() makes it a Min-Heap
    // std::make_heap(v.begin(), v.end(), std::greater<int>());
    // You can also make your own functors of greater<T>() and less<T>() and allow it to work for any data type , any objects , any UDT also or
    // For making it for UDTs , they must have < , > overloaded also .

    // There are also many functions like is_heap() , is_heap_until()
    // This make_heap() can be used on any container that has random access iterators e.g :
    // std::vector
    // std::deque
    

    // It cannot be used on :
    // std::map
    // std::set
    // std::list
    // std::forward_list    
    // Because these all have no random access iterators or manage their memory by self like Red-Black Trees.
    // Even std::array has random access iterators but still it cannot grow dynamically.
    
    // std::stack 
    // std::queue
    // These two also not because they are already derived containers and hide their functionality while priority queue needs to see the functionality as this is also a derived container.
    return 0;
}