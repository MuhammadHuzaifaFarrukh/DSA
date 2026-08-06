#include <iostream>
#include <vector>

using namespace std;

// Example 1 :
void Print(int n)
{
    if (n == 0)
    {
        return;
    }
    cout << n << " ";
    Print(n - 1);
}

// For Finding Time Complexity of any recursive function we have many ways , such as :

// 1) Draw a Recursive Tree for a case say n = 5;
// Print(5) = Does Some Work + T(Print(5-1 = 4)) = 1 + T(Print(4)) , the work other than function call is all constant so we represent it by +1.
// Print(5) = 1 + T(Print(4)) = 1 + 5 = 6 = (5) + 1 = n+1 = O(n)
// Print(4) = 1 + T(Print(3)) = 1 + 4 = 5
// Print(3) = 1 + T(Print(2)) = 1 + 3 = 4
// Print(2) = 1 + T(Print(1)) = 1 + 2 = 3
// Print(1) = 1 + T(Print(0)) = 1 + 1 = 2
// Print(0) = Takes Constant Time = 1
// So we get its time complexity as O(n).

// Another method :
// 2) Write its recursive relation :
// T(n) = 1 + T(n-1)
// Solving it will give us time complexity.
// T(n-1) = 1 + T(n-2) = 1 + 1 + T(n-3)
// T(n-2) = 1 + T(n-3) // Put in above
// Putting in T(n)
// T(n) = 1 + 1 + 1 + T(n-3) = 3 + T(n-3)
// Let k = 3 then : T(n) = k + T(n-k)
// Now T(n-k) becomes T(0) when k = n.
// So after long calls : k = n :
// T(n) = n + T(n-n) = n + T(0)
// T(0) means constant work
// T(n) = n + 1 = O(n)

// 3) Another way :
// Check number of recursive calls , let's take n = 5
// Print(5) = 1 + T(Print(4))
// Print(4) = 1 + T(Print(3))
// Print(3) = 1 + T(Print(2))
// Print(2) = 1 + T(Print(1))
// Print(1) = 1 + T(Print(0))
// Print(0) = Takes Constant Time = 1
// Print(5) takes total 6 calls.
// Work done in each call is constant = 1.
// We multiply both : No of calls * Work Done in 1 call = 6 * 1 = 6 = 1 + 5 = 1 + n = O(n)

// ===============================================================================================================

// Space Complexity :
// 1) We need to see how many times recursive function is called.
// When we call for Print(5) , it calls Print(4)
// Print(5) = Some Space + S(Print(4)) = 1 + 5 = 6
// Print(4) = Some Space + S(Print(3)) = 1 + 4 = 5
// Print(3) = Some Space + S(Print(2)) = 1 + 3 = 4
// Print(2) = Some Space + S(Print(1)) = 1 + 2 = 3
// Print(1) = Some Space + S(Print(0)) = 1 + 1 = 2
// Print(0) = 1
// We treat int memory bytes = 4 as constant.
// Our stack in the worst case goes upto 0 from 5.
// Total Space taken in Print(5) when the stack is at its maximum depth is 6.
// 6 = 1 + 5 = 1 + n = O(n)
/*
// Stack Memory Layout :
        ======================
       |                      |
       |                      |
       |                      |
        ______________________
       | Print(0)             |  For n = 0
        ______________________
       | Print(1) -> Print(0) |  For n = 1
        ______________________
       | Print(2) -> Print(1) |  For n = 2
        ______________________
       | Print(3) -> Print(2) |  For n = 3
        ______________________
       | Print(4) -> Print(3) |  For n = 4
        ______________________
       | Print(5) -> Print(4) |  For n = 5
        ______________________
       | main() -> Print(5)   |
        ======================


*/

// 2) Space * Calls
// If we see total calls Print(5) takes , which are 6 when it goes in maximum depth, and multiply by space taken in each call.
// Space taken in each call = 1.
// Calls = 6
// 1*6 = 6 = 1 + 5 = 1 + n = O(n)

// Example 2 :
void print_vec(vector<int> &arr, int index)
{
    if (index == -1)
    {
        return;
    }
    cout << arr[index] << " ";
    print_vec(arr, index - 1);
}

// Time Comp :
// 1) We analyze this function using for : print_vec(arr , 5);
// print_vec(arr , 5) = 1 + T(print_vec(arr , 4)) = 1 + 6  = 7
// print_vec(arr , 4) = 1 + T(print_vec(arr , 3)) = 1 + 5  = 6
// print_vec(arr , 3) = 1 + T(print_vec(arr , 2)) = 1 + 4  = 5
// print_vec(arr , 2) = 1 + T(print_vec(arr , 1)) = 1 + 3  = 4
// print_vec(arr , 1) = 1 + T(print_vec(arr , 0)) = 1 + 2  = 3
// print_vec(arr , 0) = 1 + T(print_vec(arr , -1)) = 1 + 1 = 2
// print_vec(arr , -1) = 1 Constant Work
// Total work done = 7 = 1 + 6 = 1 + n where n is the length of array.
// So we have : 1 + n = O(n)

// 2) We can see total calls = 7 and work done in each call 1
// Multiply them : 7 = 1 + 6 = 1 + n = O(n)

// 3) We can express it as recurrence relation :
// T(n) = 1 + T(n-1)
// Solving it gives : O(n)

// ===============================================================================================

// Space Comp :
// 1) We need to see how many times recursive function is called in max depth
// When we call for Print(5) , it calls Print(4)
// print_vec(5) = Some Space + S(print_vec(4)) = 1 + 5 = 6
// print_vec(4) = Some Space + S(print_vec(3)) = 1 + 4 = 5
// print_vec(3) = Some Space + S(print_vec(2)) = 1 + 3 = 4
// print_vec(2) = Some Space + S(print_vec(1)) = 1 + 2 = 3
// print_vec(1) = Some Space + S(print_vec(0)) = 1 + 1 = 2
// print_vec(0) = 1

// 2) Function call in max depth is : 7
// Memory allocated in each call is constant.
// Multiply we get : 7*1 = 7 = 1 + 6 = 1 + n = O(n)

// Example 3 :
void print_vec_ref(vector<int> arr, int index)
{
    if (index == -1)
    {
        return;
    }
    cout << arr[index] << " ";
    print_vec_ref(arr, index - 1);
}

// Time Comp :
// 1) We analyze this function using for : print_vec(arr , 5);
// print_vec_ref(arr , 5) = 1 + T(print_vec_ref(arr , 4)) = 1 + 6  = 7
// print_vec_ref(arr , 4) = 1 + T(print_vec_ref(arr , 3)) = 1 + 5  = 6
// print_vec_ref(arr , 3) = 1 + T(print_vec_ref(arr , 2)) = 1 + 4  = 5
// print_vec_ref(arr , 2) = 1 + T(print_vec_ref(arr , 1)) = 1 + 3  = 4
// print_vec_ref(arr , 1) = 1 + T(print_vec_ref(arr , 0)) = 1 + 2  = 3
// print_vec_ref(arr , 0) = 1 + T(print_vec_ref(arr , -1)) = 1 + 1 = 2
// print_vec_ref(arr , -1) = 1 Constant Work
// Total work done = 7 = 1 + 6 = 1 + n where n is the length of array.
// So we have : 1 + n = O(n)

// 2) We can see total calls = 7 and work done in each call 1
// Multiply them : 7 = 1 + 6 = 1 + n = O(n)

// 3) We can express it as recurrence relation :
// T(n) = 1 + T(n-1)
// Solving it gives : O(n)

// ==================================================================================================

// Space Comp :
// 1) We need to see how many times recursive function is called in max depth
// When we call for Print(5) , it calls Print(4)
// If we see , we are passing the whole vector (array) instead of just reference , so the space is not constant.
// print_vec_ref(5) = Some Space + S(print_vec_ref(4)) = n + 1 + n + 1 + n + 1 + n + 1 + n + 1 + n + 1 + (1+n) = 7n+7 = 7(n+1)
// print_vec_ref(4) = Some Space + S(print_vec_ref(3)) = n + 1 + n + 1 + n + 1 + n + 1 + n + 1 + (1+n)
// print_vec_ref(3) = Some Space + S(print_vec_ref(2)) = n + 1 + n + 1 + n + 1 + n + 1 + (1+n)
// print_vec_ref(2) = Some Space + S(print_vec_ref(1)) = n + 1 + n + 1 + n + 1 + (1+n)
// print_vec_ref(1) = Some Space + S(print_vec_ref(0)) = n + 1 + n + 1 + (1+n)
// print_vec_ref(0) = Some Space + S(print_vec_ref(0)) = n + 1 + (1+n)
// print_vec_ref(-1) = 6 + 1 or n + 1
// We can see 7(n+1) , here 7 is not to be ignored like a constant because this is not a constant , this can change according to vector size.
// So we see our space : n(n+1) = n^2 + n and dominant term is n^2 = O(n^2) Space

// 2) Function call in max depth is : 7 = n+1
// Memory allocated in each call is non-constant (linear) : n
// Multiply we get : 7*(n+1) or n(n+1) = n^2 + n = O(n^2)

// Example 4 :
// Time Complexity :
// 1) Now for this we have to analyze it first :
// BS(arr,0,4,60) = Some constant work + BS(arr,2,4,60) = 1 + 3 = 4
// BS(arr,2,4,60) = Some constant work + BS(arr,4,4,60) = 1 + 2 = 3
// BS(arr,4,4,60) = Some constant work + BS(arr,5,4,60) = 1 + 1 = 2
// BS(arr,5,4,60) = Return Nothing (Constant Work)
// So our work was done in 4 Time for input of 5 sized array.
// Now for each level we have to see , our input n was being divided :
// BS(arr,0,4,60) -> n
// BS(arr,2,4,60) -> n/2
// BS(arr,4,4,60) -> n/4
// BS(arr,5,4,60) -> n/8
// If there was more size then it would have gone till the size remained 1.
// So total time we are searching in whole 'n' array :
// n + n/2 + n/4 + n/8 +...+ n/2^k.
// If we see a pattern :
// n/2^0 + n/2^1 + n/2^2 + n/2^3 +...+ n/2^k
// 1     +   1   +   1   +    1  +...+   1
// 1     +   2   +   3   +    4  +...+   ? // Prefixed Answers
// So last term becomes to 1 for k :
// n/2^k = 1
// n = 2^k
// logn = k
// Seeing above sequence of n/2^k and Prefixed , we can see that we will get answer when we have k+1.
// So k+1 = logn+1 = O(logn+1) ~ O(logn)

// 2) If we see its recurrence relation :
// T(n) = 1 + T(n/2) = 1 + 1 + 1 + T(n/8)
// T(n/2) = 1 + T(n/4) = 1 + 1 + T(n/8)
// T(n/4) = 1 + T(n/8)
// Solving T(n) :
// T(n) = 3 + T(n/8) = k + T(n/2^k)
// Now we put n/2^k = 1 (not 0 because then k would vanish) , :
// n/2^k = 1 => n = 2^k
// logn = k or k = logn
// T(n) = k + T(n/2^k) = logn + T(1) = logn + 1 = O(logn)
// T(1) also represents constant work

// ============================================================================================================

// Space Complexity :
// We have to see the maximum depth of our search calls.
// It went total upto logn calls since in average case the calls are less than 'n'.
// The maximum depth of our binary search for 5 sized array with some target went upto 4 calls.
// For average case its logn calls.
// n + n/2 + n/4 + n/8 + .... + n/2^k so it finishes in atmost logn+1.
// And our space taken for each call was constant.
// So multiply them : 1*logn = logn
// O(logn)

int binarySearch(vector<int> &arr, int start, int end, int target)
{
    if (start > end)
    {
        return -1;
    }
    int mid = (start) + (end - start) / 2;
    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] < target)
    {
        return binarySearch(arr, mid + 1, end, target);
    }
    else
    {
        return binarySearch(arr, start, mid - 1, target);
    }
}

// Example 5 :
// For Fibonacci series its actual time complexity is less than O(2^n) however we just write it just for our ease and for practicing and to see if it were a perfect binary tree.
// Time Complexity :
// We can draw its recursive tree :
/*
                                     fib(5)
                                   /        \
                             fib(4)          fib(3)
                            /      \        /      \
                       fib(3)    fib(2)  fib(2)    fib(1)
                       /    \     /   \   /   \
                  fib(2)  fib(1)fib(1)fib(0)fib(1)fib(0)
                  /    \
             fib(1)  fib(0)
*/
// 1) For each level , we can see total calls.
// Work done in each call is constant.
// For first level 0 : 1
// For first level 1 : 2
// For first level 2 : 4
// For first level 3 : 6 (We can take it as 8 if it were a perfect binary tree)
// For first level 4 : 2 (We can take it as 16 if it were a perfect binary tree)
// Total Nodes = 1 + 2 + 4 + 8 + 16 + 32 +...+ 2^(n-1) = 2^n - 1
// So we can multiply : work*nodes = 1*(2^n - 1) = 2^n - 1 = O(2^n)
// This way of finding time complexity is easier if recursion takes tree structure because doing too much calls can take so much hectic.

// 2) Recurrence Relation :
// T(n) = 1 + T(n-1) + T(n-2)
// Because dealing with two different shrinking terms (n-1 and n-2) makes the exact math messy, we simplify it for complexity analysis by assuming both branches take roughly equal work.
// To find the upper bound, we approximate T(n-2) ~ T(n-1):
// T(n) = T(n-1) + T(n-1) + 1 = 2T(n-1) + 1
// T(n-1) = 2T(n-2) + 1
// T(n-2) = 2T(n-3) + 1
// We replace and get : T(n) = 2*2T(n-2) + 1 + 1
// We replace and get : T(n) = 2*2*2T(n-3) + 1 + 1 + 1
// T(n) = 2^3T(n-3) + 3
// T(n) = 2^kT(n-k) + k     // k = 3
// Put n-k = 0 and k = n;
// T(n) = 2^nT(0) + n
// T(n) = 2^n(1) + n    // T(0) = 1
// T(n) = 2^n + n = O(2^n + n) = O(2^n)

// ================================================================================================================================================

// Space Complexity :
// For tree like structure that spreads more children , we can find space complexity by finding the memory taken by root to maximum depth leaf.
// If we see fib(5) , it can go maximum at fib(1) , then it goes back to fib(2) and fib(1) , then fib(3) and fib(1) and so on.
// If we see it in stack , the maximum frames it holds are from fib(5) from fib(1) which is the left most route.
// These are total 5 calls.
// Memory occupied in these calls is constant so multiply them :
//  = Memory * Maximum Depth Frames = 1*(n) = n , Maximum Depth is n because fib(5) goes at max to fib(1) for base case.
// O(n)

int fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    // Print(5);
    vector<int> v = {10, 20, 30, 40, 50};
    // print_vec(v, v.size() - 1);

    int target = 60;
    // binarySearch(v, 0, v.size() - 1, target);

    // cout << " Fibonacci Number " << 5 << "th is : " << fib(5) << endl;

    return 0;
}