#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int W;
    cout << "Enter max weight : ";
    cin >> W;

    queue<string> ID;
    queue<int> Weight;

    string id;
    int weight = 1;

    cout << "Enter -1 for weight and enter to exit input " << endl;
    while (1)
    {
        cin >> id >> weight;
        if (weight  == -1)
        {
            break;
        }
        ID.push(id);
        Weight.push(weight);
    }

    int total = 0;
    vector<string> fin;
    string fails = "";

    while (!ID.empty())
    {
        if (total + Weight.front() <= W)
        {
            total = total + Weight.front();
            fin.push_back(ID.front() + "(" + to_string(Weight.front()) + ")");
            ID.pop();
            Weight.pop();
        }
        else
        {
            fails = ID.front();
            break;
        }
    }

    cout << "Loaded : ";
    if (fin.empty())
    {
        cout << "None " << endl;
    }
    else
    {
        for (int i = 0; i < fin.size(); i++)
        {
            cout << fin[i] << " ";
        }
        cout << endl;
    }
    
    cout << "Remaining in Queue : ";
    if (ID.empty())
    {
        cout << " None " << endl;
    }
    else
    {
        while (!ID.empty())
        {
            cout << ID.front() << "(" << Weight.front() << ") ";
            ID.pop();
            Weight.pop();
        }
        cout << endl;
    }
    cout << endl;
    if (fails != "")
    {
        cout << "Note : " << fails << " was not loaded (Would exceed capacity)" << endl;
    }
    return 0;
}