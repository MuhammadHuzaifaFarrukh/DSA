#include <iostream>

using namespace std;

// Bottom-Up
// table(2,1) = Print 2*1 + table(2,2)
// table(2,2) = Print 2*2 + table(2,3)
// table(2,3) = Print 2*3 + table(2,4)
// table(2,4) = Print 2*4 + table(2,5)
// table(2,5) = Print 2*5 + table(2,6)
// table(2,6) = Print 2*6 + table(2,7)
// table(2,7) = Print 2*7 + table(2,8)
// table(2,8) = Print 2*8 + table(2,9)
// table(2,9) = Print 2*9 + table(2,10)
// table(2,10) = Print 2*10 + table(2,11)
// table(2,11) = Return (Base Case)

// Time : O(n+1) = O(n) , Space : O(n+1) = O(n)
void table(int n, int i)
{
    if (i > 10) // 10 can also be asked from user
    {
        return;
    }
    else
    {
        cout << n << " x " << i << " = " << (n * i);
        cout << endl;
        table(n, i + 1);
    }
}

int main()
{
    int n;
    cout << "Enter the number : ";
    cin >> n;

    table(n, 1);

    return 0;
}
