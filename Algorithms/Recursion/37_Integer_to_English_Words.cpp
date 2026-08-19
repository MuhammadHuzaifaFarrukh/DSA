#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Convert a non-negative integer num to its English words representation.

Input: num = 123
Output: "One Hundred Twenty Three"

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
*/

// We know that :
/*
Thousand -> 1000 = 3 Zeroes
Million -> 1,000,000 = 6 Zeroes
Billion -> 1,000,000,000 = 9 Zeroes
Every time we move a step up , we add 3 zeroes.
If we look at the pattern of numbers , 1-19 numbers , 20,30,40,50,60,70,80,90,100 are uniquely written.
Other than these if we write , it becomes Thousand , Million , Billion (2147483647 is the C++ Max Int Limit though it can be extended for trillion let's observe this out).
We make two lookup tables arrays : 1 for the 1-19 and the other for the 20,30,40,50,60,70,80,90.
The Other steps that we will get we can just hard code it like Hundred , Million , Billion etc.

Suppose we get : 1,005,020
Now we have to see if its greater than billion , which its not.
Then we see , and find that its greater than million so we take its million part and add million in it.
We compute it as number / million + "Million " + number % million.
And we do it for each.
Now we find that number/million = 1 so it becomes "One Million ".
Now we solve for the remaining part and that is 5020.
5020 is >= 1000 and its modulus is not 0 so we will have to find 5020/1000 + " Hundred " + 5020%1000.
We get "Five Hundred " and from the modulus part we get "Twenty"
So it becomes "Five Hundred Twenty"
Now we've got the modulus part of the 1,005,020 % million which is "Five Hundred Twenty"
Overall our answer becomes "One Million Five Hundred Twenty"

See we broke the large number into parts of 3 sizes and then we computed each division + Abbreviation + Remaining Part.

*/

// Time Complexity :
// Its time is bounded by the largest C++ INT_MAX which is O(2147483647) = O(1)
// Because n is capped at 2 Billion, the function can make at most 4 recursive calls deep (e.g., 1B -> 1M -> 1K -> 100 -> 20). = O(1)
// Time : O(1)

// Space Complexity :
// At any point during execution, the maximum stack depth is capped at 4 call frames.
// The Lookup tables are also of sizes 10 and 20 = O(30) = O(1)
// Space : O(1)
vector<string> BELOW_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

vector<string> TENS = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

string solve(int num)
{
    if (num == 0)
    {
        return "";
    }

    // 1. Billion
    if (num >= 1000000000)
    {
        if (num % 1000000000 != 0)
        {
            return solve(num / 1000000000) + " Billion " + solve(num % 1000000000);
        }
        else
        {
            return solve(num / 1000000000) + " Billion";
        }
    }

    // 2. Million
    if (num >= 1000000)
    {
        if (num % 1000000 != 0)
        {
            return solve(num / 1000000) + " Million " + solve(num % 1000000);
        }
        else
        {
            return solve(num / 1000000) + " Million";
        }
    }

    // 3. Thousand
    if (num >= 1000)
    {
        if (num % 1000 != 0)
        {
            return solve(num / 1000) + " Thousand " + solve(num % 1000);
        }
        else
        {
            return solve(num / 1000) + " Thousand";
        }
    }

    // 4. Hundred
    if (num >= 100)
    {
        if (num % 100 != 0)
        {
            return solve(num / 100) + " Hundred " + solve(num % 100);
        }
        else
        {
            return solve(num / 100) + " Hundred";
        }
    }

    // 5. Tens (20 to 99)
    if (num >= 20)
    {
        if (num % 10 != 0)
        {
            return TENS[num / 10] + " " + solve(num % 10);
        }
        else
        {
            return TENS[num / 10];
        }
    }

    // 6. Below 20
    return BELOW_20[num];
}

string numberToWords(int num)
{
    if (num == 0)
    {
        return "Zero";
    }
    return solve(num);
}

int main()
{
    cout << numberToWords(1234567) << endl;

    return 0;
}

// If this program were made for large digit numbers then its time and space would be :
/*
Space complexity asks: "As the number of digits grows, how much extra memory does our program need?"

Memory is used in two places:

1) The Function Call Stack (Recursion):
Our algorithm breaks numbers down into 3-digit chunks (Thousands, Millions, Billions, Trillions, Quadrillions, Quintillions...).
If we have D digits, the number of 3-digit chunks is given by:
Number of chunks = D / 3
If D = 9 digits, we have 9 / 3 = 3 chunks.
If D = 1,000 digits, we have 1000 / 3, which is approximately 333 chunks.
Every chunk creates 1 recursive call frame on our stack.

2) The Output String:
To hold the final English sentence for a 1,000-digit number, we need to store thousands of words ("One Hundred Twenty Three Trillion...").
The length of this output string is directly proportional to D.

Space :
Stack frames (D / 3) + Output String memory (approximately D) scales directly with D. In Big-O, we ignore constant multipliers like 1/3.
So the Space Complexity is O(D).
*/

// Time Complexity :
/*
Time complexity asks: "As the number of digits grows, how many basic operations (work) does the computer perform?"

Let's count our work step-by-step:

How many recursive calls happen?
Since we process 3 digits at a time, our function runs D / 3 times.

How much work happens inside each recursive call?
Inside each call, we take a 3-digit chunk (like "456"), look up "Four Hundred Fifty Six" in our array, and attach it to the rest of the string.
Looking up 3 digits in BELOW_20 or TENS takes constant time, O(1).
Combining/concatenating strings takes time proportional to the length of the string being copied.

If we use an efficient string builder (appending words to a buffer without repeatedly re-copying the entire text):

Total Time = (Number of Chunks) * (Work per Chunk)
Total Time = (D / 3) * O(1) = O(D)

Time Complexity is O(D).

A 1-digit number can go up to 9 (which is less than 10^1).
A 2-digit number can go up to 99 (which is less than 10^2).
A 3-digit number can go up to 999 (which is less than 10^3).
A D-digit number N can go up to roughly 10^D.

Applying the Logarithm:
By definition, a logarithm base 10 tells us: "What exponent must we raise 10 to, in order to get our number N?"

If N = 10^D, then taking log base 10 of both sides gives:

log10(N) = D

For example, if our number N is 1,000,000:
log10(1,000,000) = 6, which is exactly the number of zeros (or roughly the number of digits D).
Since our function processes numbers in 3-digit chunks (thousands, millions, billions), the formula for the number of chunks is : D/3 = 6/3 = 2 Function Calls.
This D/3 can vary because D/3 is for purely the numbers that are Exact Mil , Bil , Thousand , it may be different for the 1,234,567 = D/3 + 2 etc.

Connecting to Time Complexity:
Since D = log10(N), saying our algorithm runs in O(D) time is completely identical to saying it runs in O(log10(N)) time.
*/
