#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.
Note that operands in the returned expressions should not contain leading zeros.
Note that a number can contain multiple digits.

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
Example 3:

Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
*/
// Target can also be negative so we need to generate all the possible choices (no repetition of digits though).

// This is a combination problem without repetitions , with fixed order and partitioning like the one in palindromic partitions.
// We have to try all the possible combinations we can make to get our answers.
// We can also use multiple digits for making a number , however we cannot let any number have leading zeroes.
// E.g [1,0,5] with Target 15 -> 10+5
// So we have 2 choices in this case.
// We either make a cut at this index , or we skip the cut just like palindrome partition.
// We also keep previous number and evaluating number currently.
// This will help because we can check if we have completed all the indexes then we just need to check if we evaluated = target.
// We are not gonna do target - number because here mul is involved so truncation can also occur when we backtrack so we just keep running evaluation.
// So base case we check if we reached all the numbers i.e index == num.size() , and we also check eval == target.
// We check one more thing that i == num.size() because this is the starting point where we have to make a cut.
// If we have processed some digits but left some digits without even cutting them , then we need to make sure that they are cut before adding to answer.
// So that's why we check this i==num.size().
// Then we take and add a number to make it string.
// We check if this number is of size 1 , and if it is not then its first number must not be 0.
// This condition handles invalid multi-digit numbers and also the single digits including zero also.
// Now when we are at i==0 , it means we have added no digit , so we add this digit inside our temp array , and also make a cut at this point.
// After this we know that i>0 so it will take the next number from the string , and then it will try all the 4 possible operations it can trying them one by one.
// We can try any operation (+,-,*).
// We append the operator and this number in our temp array.
// For + or - , we just keep + or - the answer and also send a previous value as well.
// For multiplication we have to handle some things.
// While passing this current value , we don't just multiply , we have to subtract the previous number that was added / subtracted and then multiply this previous number with this index value and then add them both.
// This is for the DMAS rule , because if we have 3+4*2 , then we are doing 3+4 and then 7*2 =14 whereas it would have been actually 11 if we multiplied first.
// So when we have 3+4 , we undo by doing 7-4 + (4*2) = 3 + 8 = 11.
// So that's how we can handle multiplication.
// Also when we have to send its previous value , its previous value is now 8 instead of 2 , because our current number is now 3 and we got 4*2 , so we send this 4*2 as our previous number instead of just 2 so later on if any other multiplication arises we just do (11-8) + (8*Something) to go further.
// So we only had to just handle this multiplication and multi-digits , that's all in this.
// We basically have 2 choices , to make a cut or skip it.
// We only take answers that are fully cut , like "123" , if we have cut 1 | 2 | 3 but not 3 , then first we need to cut 3 as well with different operators in between.
// After we cut 3 and try all choices 1 | 2 | 3 | then we go for skip , but we return because we aren't using all the numbers if we take 1|2| and skip the last one so skipping just helps in making multi-digits.
// We have to use all the digits for our answer.
// E.g if we have "105" with target 15 , then we take a cut at first index , second and 3rd indexes , 1 | 0 | 5 | and then we make our choices 1+0+5 or 1+0-5 or 1+0*5.
// Then we skip it and once we fail then we come back and change our operator with 1 - 0 and then 1 * 0 and then again make the cuts with 5 making 1-0+5 , 1-0-5,1-0*5 and also 1*0+5,1*0-5,1*0*5.
// Then we come and skip which fails again.
// Then we come back at this stage where we had make a cut on 0-5 , 1 | 05 and now we choose to skip.
// Once we skip we make choice of cut and see that 05 has leading zeroes so it can never be cut and so we skip which again leads to fail.
// So we come back 1 | 05 where we have taken both choices cut and skip.
// Now we go back and again skip : 1 0 5 , and then make a choice of cut : 10 | 5.
// Now we again try operations : 10+5 , 10-5, 10*5.
// Once done we skip the cut and see we have no numbers left so we go back.
// Now we come back on the 10 5 , where we made a choice to cut , now we skip the cut and it becomes like 105 and now make our cut here.
// Now we check this whole "105" = target or not and then we come back and choose to skip which we cannot since we've used up all the digits.

// Time Complexity :
// When we have a number say "1234" , then we have total 3 spots in between , we have 4 choices.
// We can place operator (+,-,*) -> 3 Choices or we can just skip it extending the number.
// This creates a decision tree of height n with a branching factor of at most 4.
// So we have approx nodes as 4^n.
// Using substr and temp copied into answer takes 'n' time as well.
// So Time : O(4^n)  (or O(n*4^n) if we take substr() and push_back() time as well).

// Space Complexity :
// The maximum depth of the recursion tree is equal to the length of the input string n (i.e., when we process character by character).
// Space used on the call stack = O(n)
// The auxiliary string temp builds the expression.
// In the worst case (inserting an operator between every single digit), temp reaches a maximum length of 2n-1.
// Space used for worst case string storage = O(2n-1) = O(n)
// Space : O(n)
// If you count the space used to store the output results array ans, it can hold up to O(4^n) valid expressions, with n characters in each string making it upto approx : n*(4^n).
// Total Space : O(n*4^n).
vector<string> addOperators(string num, int target)
{
    vector<string> ans;
    string temp = "";
    recursion(ans, temp, num, target, 0, 0, 0, 0);
    return ans;
}

void recursion(vector<string> &ans, string &temp, string &num, int target, int i, int index, long long eval, long long prev)
{
    if (index == num.size())
    {
        if (i == num.size() && eval == target)
        {
            ans.push_back(temp);
        }
        return;
    }

    string x = num.substr(i, index - i + 1);

    long long val = stoll(x);
    // Choice 1 : Make a Cut
    // single digit OR no leading zero
    if (x.size() == 1 || x[0] != '0')
    {
        if (i == 0) // Putting a number without an operator
        {
            temp += x;
            recursion(ans, temp, num, target, index + 1, index + 1, eval + val, val);
            temp.erase(temp.size() - x.size());
        }
        else
        {
            // Options to Add +,-,*
            temp += "+" + x;
            recursion(ans, temp, num, target, index + 1, index + 1, eval + val, val);
            temp.erase(temp.size() - (x.size() + 1));

            temp += "-" + x;
            recursion(ans, temp, num, target, index + 1, index + 1, eval - val, -val);
            temp.erase(temp.size() - (x.size() + 1));

            temp += "*" + x;
            recursion(ans, temp, num, target, index + 1, index + 1, eval - prev + (prev * val), prev * val);
            temp.erase(temp.size() - (x.size() + 1));
        }
    }

    // Choice 2 : Skip the cut :
    recursion(ans, temp, num, target, i, index + 1, eval, prev);
}

// Recursive tree for "123" with target = 6 for clear understanding :
/*
// Recursive Tree for num = "123", target = 6 (All Operations Included)
/*
                                                      (i=0, index=0, temp="", eval=0)
                                                     /                               \
                                                (CUT "1")                         (SKIP CUT)
                                               /                                             \
                           (i=1, index=1, temp="1", eval=1)                        (i=0, index=1, temp="", eval=0)
                          /                               \                       /                               \
                     (TRY CUT "2")                    (SKIP CUT)             (CUT "12")                          (SKIP CUT)
                    /                             /                \            /                                     \
    ┌───────────────┼───────────────┐            /                  \          /                                       \
   (+)             (-)             (*)          /                    \        /                                         \
("1+2", e=3)   ("1-2", e=-1)   ("1*2", e=2)    (i=1, index=2)      (i=2, index=2)                             (i=0, index=2, temp="")
  /     \        /     \        /     \        temp="1"           temp="12", e=12                             /                    \
(CUT) (SKIP)   (CUT) (SKIP)   (CUT) (SKIP)        |                      |                                    (CUT "123")           (SKIP CUT)
  │     │        │     │        │     │        (CUT "23")             (CUT "3")                                  │                     │
┌─┴─┐ [FAIL]   ┌─┴─┐ [FAIL]   ┌─┴─┐ [FAIL]        │                      │                                 (i=3, index=3)        (i=0, index=3)
│   │ i!=3     │   │ i!=3     │   │ i!=3     ┌────┼────┐            ┌────┼────┐                             temp="123", e=123     temp="", e=0
│   │          │   │          │   │          │    │    │            │    │    │                                    │                     │
T1 T2 T3       T4 T5 T6       T7 T8 T9      T10  T11  T12          T13  T14  T15                          [FAIL: eval!=6]       [FAIL: i!=3]
*/

/*
===================================================================================================================
LEAF EVALUATIONS AT index = 3 (Bottom Nodes):

├── FROM "1+2" (eval = 3):
│   ├── T1: (+) -> temp = "1+2+3", eval = 3 + 3 = 6  ==> [SUCCESS!] -> Added to ans ("1+2+3")
│   ├── T2: (-) -> temp = "1+2-3", eval = 3 - 3 = 0  ==> [FAIL: eval=0 != 6]
│   └── T3: (*) -> temp = "1+2*3", eval = 3 - 2 + (2*3) = 7 ==> [FAIL: eval=7 != 6]
│
├── FROM "1-2" (eval = -1):
│   ├── T4: (+) -> temp = "1-2+3", eval = -1 + 3 = 2 ==> [FAIL: eval=2 != 6]
│   ├── T5: (-) -> temp = "1-2-3", eval = -1 - 3 = -4 ==> [FAIL: eval=-4 != 6]
│   └── T6: (*) -> temp = "1-2*3", eval = -1 - (-2) + (-2*3) = -5 ==> [FAIL: eval=-5 != 6]
│
├── FROM "1*2" (eval = 2):
│   ├── T7: (+) -> temp = "1*2+3", eval = 2 + 3 = 5  ==> [FAIL: eval=5 != 6]
│   ├── T8: (-) -> temp = "1*2-3", eval = 2 - 3 = -1 ==> [FAIL: eval=-1 != 6]
│   └── T9: (*) -> temp = "1*2*3", eval = 2 - 2 + (2*3) = 6 ==> [SUCCESS!] -> Added to ans ("1*2*3")
│
├── FROM SKIP CUT "2" (x = "23"):
│   ├── T10:(+) -> temp = "1+23",  eval = 1 + 23 = 24  ==> [FAIL: eval=24 != 6]
│   ├── T11:(-) -> temp = "1-23",  eval = 1 - 23 = -22 ==> [FAIL: eval=-22 != 6]
│   └── T12:(*) -> temp = "1*23",  eval = 1 * 23 = 23  ==> [FAIL: eval=23 != 6]
│
└── FROM SKIP CUT "1" (x = "12"):
    ├── T13:(+) -> temp = "12+3",  eval = 12 + 3 = 15 ==> [FAIL: eval=15 != 6]
    ├── T14:(-) -> temp = "12-3",  eval = 12 - 3 = 9  ==> [FAIL: eval=9 != 6]
    └── T15:(*) -> temp = "12*3",  eval = 12 * 3 = 36 ==> [FAIL: eval=36 != 6]
===================================================================================================================
*/

int main()
{
    string s = "105";
    int target = 5;
    vector<string> ans = addOperators(s, target);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}