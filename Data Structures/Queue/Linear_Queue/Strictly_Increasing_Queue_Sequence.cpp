#include <iostream>
#include <queue>

using namespace std;

int main()
{
    queue<int> q;
    int x;
    while (true)
    {
        cout << "Enter a number (Press -1 to exit): ";
        cin >> x;
        if (x != -1)
        {
            q.push(x);
        }
        else
        {
            break;
        }
    }
    int length = 0;
    int max_length = 0;
    while (!q.empty())
    {
        int x1 = q.front();
        q.pop();

        if (x1 < q.front())
        {
            length++;
        }
        else
        {
            max_length = max(max_length, length);
            length = 0;
        }
    }

    max_length = max(max_length, length);
    cout << "Length : " << length << endl;
    return 0;
}