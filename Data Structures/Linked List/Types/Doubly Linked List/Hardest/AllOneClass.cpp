#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Design a data structure that stores strings and its frqeuencies also , and with functions inc,dec,getMaxKey and getMinKey in O(1).
// Also delete them if their count is zero and when asked for delete , the element is guaranteed to be there. Also check to increase the count in inc function if the element is already there.


// 1) Use only unordered map
// Time for Max and Min becomes : O(n) and Space : O(n)
// Will get TLE on Leetcode.
/*
class AllOne
{
public:
    unordered_map<string, int> data;

    AllOne()
    {
    }

    void inc(string key)
    {
        auto it = data.find(key);
        if (it != data.end())
        {
            it->second++;
        }
        else
        {
            data[key] = 1;
        }
    }

    void dec(string key)
    {
        auto it = data.find(key);
        // Since its guaranteed to be there , no need for check
        it->second--;
        if (it->second == 0)
        {
            data.erase(key);
        }
    }

    string getMaxKey()
    {
        string maxKey = "";
        int maxKeyCount = INT_MIN;
        for (auto it = data.begin(); it != data.end(); it++)
        {
            if (it->second > maxKeyCount)
            {
                maxKeyCount = it->second;
                maxKey = it->first;
            }
        }
        return maxKey;
    }

    string getMinKey()
    {
        string minKey = "";
        int minKeyCount = INT_MAX;
        for (auto it = data.begin(); it != data.end(); it++)
        {
            if (it->second < minKeyCount)
            {
                minKeyCount = it->second;
                minKey = it->first;
            }
        }
        return minKey;
    }
};
*/

// 2) Optimized , Use a list to store objects of different counts.
// For storing objects with different counts , we define another class as 'Contain' that stores frequencies and objects of that frequencies.
// So now our list will store the multiple frequencies objects.
// Also we use unordered maps to store those multiple objects with their addresses in the doubly linked list so that they can be looked up very fast.
// We implement the inc and dec functions in such a way that our list has lowest frequencies objects at starting and ascending order (sorted) with highest frequencies objects at last.
// This will make Max and Min functions also O(1).

// Time for Operations : O(1) , Space : O(n)

// This class is made so that we have different count 'keys' stored in groups.
class Contain
{
public:
    unordered_set<string> keys; // All the strings that have this exact frequency.

    int count; // This will be fixed , say 5 , then 1 object of this class will always have objects whose counts are 5, if any object's count increases or decreses we simply move it to the count 4 or count 3 object.
};

class AllOne
{
public:
    list<Contain> strings;                                      // This holds all the strings with different frequencies.
    unordered_map<string, list<Contain>::iterator> lookupTable; // This will give each string its iterator so we have a direct O(1) lookup.

    AllOne()
    {
    }

    void inc(string key)
    {
        auto it = lookupTable.find(key);
        if (it != lookupTable.end())
        {
            auto ls_it = lookupTable[key];
            ls_it->keys.erase(key);
            // auto ls_it_next = next(ls_it) , this uses a next function of iterator class that given ls_it->next to ls_it_next.
            // But we can also write it like below :
            auto ls_it_next = ls_it;
            ls_it_next++;

            // Check if we need to create the Count 2 bucket
            // We create it if we reached the end of the list OR the next bucket's count isn't (current count + 1)
            if (ls_it_next == strings.end() || ls_it_next->count != ls_it->count + 1)
            {
                Contain s;
                s.count = ls_it->count + 1;
                ls_it_next = strings.insert(ls_it_next, s);
            }
            ls_it_next->keys.insert(key);
            lookupTable[key] = ls_it_next;

            // When we removed the key from current list floor , it might have become empty so we can totally remove if it became zero.
            if (ls_it->keys.empty())
            {
                strings.erase(ls_it);
            }
        }
        else
        {
            // If the key didn't exist.
            auto ls_it = strings.begin();
            if (ls_it == strings.end() || ls_it->count != 1)
            {
                Contain s;
                s.count = 1;
                ls_it = strings.insert(strings.begin(), s);
            }
            ls_it->keys.insert(key);
            lookupTable[key] = ls_it;
        }
    }

    void dec(string key)
    {
        // Since its guaranteed to be there , no need to check for keys' existence.
        auto ls_it = lookupTable[key];
        ls_it->keys.erase(key);
        if (ls_it->count == 1)
        {
            lookupTable.erase(key);
        }
        else // This is for the count > 1
        {
            // We could also have used prev(ls_it) function just like next() func.
            auto ls_it_prev = ls_it;
            ls_it_prev--;
            // We again check for creation of a new bucket if :
            // 1. ls_it was at the very beginning of the list (meaning ls_it_prev would be out of bounds/invalid)
            // 2. The previous bucket's count isn't exactly current count - 1
            if (ls_it == strings.begin() || ls_it_prev->count != ls_it->count - 1)
            {
                Contain s;
                s.count = ls_it->count - 1;
                ls_it_prev = strings.insert(ls_it, s);
            }
            ls_it_prev->keys.insert(key);
            lookupTable[key] = ls_it_prev;
        }
        if (ls_it->keys.empty())
        {
            strings.erase(ls_it);
        }
    }

    // Our Data Insertion was held so that elements can be put in increasing order.
    // So getMaxKey is now O(1) if we just access strings.back().
    // And getMinKey is also O(1) if we just access strings.front().
    string getMaxKey()
    {
        if (strings.empty())
        {
            return "";
        }
        return *(strings.back().keys.begin());
    }

    string getMinKey()
    {
        if (strings.empty())
        {
            return "";
        }
        return *(strings.front().keys.begin());
    }
};
// This is just one way of solving this in O(1).
// There can be many more using combination of unordered map , sets , lists and other derived or basic data structures in a suitable and logical way.


int main()
{
    return 0;
}