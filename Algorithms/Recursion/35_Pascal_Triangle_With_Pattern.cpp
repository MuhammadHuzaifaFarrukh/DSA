#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1) Using Recursion to print a simple pascal number by the nCr = (n-1)C(r-1) + (n-1)Cr
// Time : O(2^n) for all rows.
// Space : O(n) due to recursive stack.
// Call : pascalNumber(i-1,cols) where cols resets everytime it enters inner loop and col++ when it prints the number.

// 2) Using the Iterative one with the formula : (n-i)/(1+i) :
// Time : O(n^3)
// Space : O(1) due to just printing not storing anywhere.
// Call : pascalIterative(i-1,cols) where cols resets everytime it enters inner loop and col++ when it prints the number.

// 3) Using the Iterative one that prints whole row in just O(n) time.
// The Mathematical Relation Between Consecutive Elements
// Look at two consecutive elements in row n:

// Element k = C(n, k) = n! / (k! * (n - k)!)
// Element (k - 1) = C(n, k - 1) = n! / ((k - 1)! * (n - k + 1)!)
// Dividing C(n, k) by C(n, k - 1) gives:
// C(n, k) / C(n, k - 1) = (n - k + 1) / k
// Next Element / Previous Element (k-1)  = (n - k + 1)/k
// This gives us the recurrence relation to compute the next element from the current element in O(1) time:
// Element k = Element (k - 1) * (n - k + 1) / k
// This formula is index 0-based and our program uses pattern printing from i = 1 to n.
// So for the formula Element * (n-k+1)/k , n becomes i-1 to take it index 0-based.
// 'k' presents the number of elements in each row , like if n = 4 , then we have to print the last row as 1,3,3,1 so there are 4 numbers so 'k' tracks the number of elements printed.
// Here n = 4 mean Row 3 ,3C0 then 3C1 , 3C2 , 3C3
// So that's why we keep here a column variable 'col' that resets each time we enter inner loop and then increases when it prints a new value.
// We increase the value , because for finding the next nCk from nC(k-1), we see that we need a previous value at k-1 col and then for putting in denominator of (n-k+1)/k we see it as k instead of k-1 so we increase col before using this formula to make k = col.
// First we found for the col-1 value which was default and now we need to find for the next column col-1(+1) = col so we

// So we put the values :
// (n-k+1)/k = (i-1-col+1)/(col) = (i-col)/(col)

// For Example for n=4
// Row 0:           1
// Row 1:         1   1
// Row 2:       1   2   1
// Row 3:     1   3   3   1
//            ^   ^   ^   ^
// Col:       0   1   2   3

// Time : O(n^2).
// Space : O(1) as we are just printing not storing results.
void pascalPatternNRows(int rows)
{
    int i, j, count = 0;
    int k;
    k = 1;
    for (i = 1; i <= rows; i++)
    {
        int col = 0;
        long long value = 1;
        for (j = 1; j <= (rows * 2) - 1; j++)
        {
            if ((j >= rows - count) && (j <= rows + count) && (k))
            {
                printf("%lld", value);
                // Now we calculate the value for next using col+1.
                col++;
                value = value * (i - col) / (col);
                k = 0;
            }
            else
            {
                printf(" ");
                k = 1;
            }
        }
        k = 1;
        count++;
        printf("\n");
    }
}

int main()
{
    int rows = 0;
    do
    {
        printf("Enter the number of rows : ");
        scanf("%d", &rows);
    } while (rows <= 0 || rows >= 11);

    pascalPatternNRows(rows);

    return 0;
}
