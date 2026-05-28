#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;
// Design a data structure to mimic like LRU Cache system.
// It is a system that replaces the least used data with the newly added data.
// The Data is least used when it is neither accessed nor it is updated for anything.
// If we update the data , or access to see its key , then it becomes the most recently used data.


// Optimized approach
// We use doubly linked list and have our Least Recently used Element at back of the list and the Most Recently used Element at the front of the list.
// We also use push at front to add the key at front.
// We use cache List to store list of key value and pair.
// Then we use an unordered map for O(1) lookup , and we store the address of the key. This helps us to get the key in O(1) time instead of searching for that key in the cacheList one by one. 
// If we had used <int,int> to store the info in map then it would work in O(n) instead of O(1) for reordering of list.

// Since we are using std::list , we don't use Node *  , as that is for the custom data type. For STL list , we store the address in the form of iterators.

class LRUCache
{
    int capacity;
    list<pair<int, int>> cacheList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }
    // When we use any function with the key then that key makes it most recently used at that time so we have to always put it at the front from its current position whether we get or put.

    // Key exists or Key doesn't exist
    void put(int key, int value)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end())
        {
            auto ls_it = it->second;
            ls_it->second = value; // We update our key
            // Then we have to attach its previous and next pointers together and then add the updated key-value at front.
            // We can do this manually by using erase and push front functions.
            // However this approach is quite exhausting for the CPU as it will delete node and request for new block every time.
            // So this trick should be avoided.
            // We have a built in splice function that does the same but without deleting node.
            cacheList.splice(cacheList.begin(), cacheList, ls_it);
            // This splice function will transfer the element pointed by the ls_it to the .begin() position from the cacheList.
            // We don't also need to change the address since we aren't deleting.
            return;

            // If you make your own custom Node class , then you can manually do the deletion , joining nodes and then push front which may be lot faster than doing using .erase and .push_front() functions for now.
            // You may also need to update the address if you use the deletion option and then pushing at front as allocating in the heap doesn't give same address always.
        }
        // Now if we have a brand new key then we need to see the size as well.
        if (cacheList.size() == capacity)
        {
            int k = cacheList.back().first;
            cacheMap.erase(k);
            cacheList.pop_back();
        }
        // Now that we handled space , we will insert.
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin(); // This will set its address as well.
        return;
    }
    // Key exists or Key doesn't exist
    int get(int key)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end())
        {
            // Do the same here what we did in the put() function and then return the value of the key.
            auto ls_it = it->second;
            cacheList.splice(cacheList.begin(), cacheList, ls_it);
            int v = ls_it->second;
            return v;
        }
        return -1;
    }
};

int main()
{
    /*
     * LRUCache* obj = new LRUCache(capacity);
     * int param_1 = obj->get(key);
     * obj->put(key,value);
     */
    return 0;
}

// The approach that we used would be for advanced ones who know how to use STL to their own benefits like we used splice() function here.
// This approach is what senior engineers would use , use their own custome data structure.
// For custom list , we could have used below template :
/*
class Node
{
    int data,key;
    Node *next ,*prev;
    Node(int key = 0 , int data = 0 , Node *next = nullptr , Node *prev = nullptr) : key(key) , data(data) , next(next) , prev(prev) {}
};
// We would also have to write the push at front , back , pop at front , at back and splice (if we use splice),
// Then we would also have to update the address in the unordered map each time after accessing a key , as we would first join connections of next and prev nodes , then delete current and put it at front.
// Our map would be unordered_map<int,Node *> cacheMap instead of unordered_map<int,list<pair<int,int>>> cacheMap;
*/