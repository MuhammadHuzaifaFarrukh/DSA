#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

int main()
{
    int n;
    cout<<"Enter number of tasks ";
    cin>>n;

    queue<int> q;
    int i = 1;
    while(i<=n)
    {
        int temp;
        cout<<"Enter duration of Task # "<<i<<" : ";
        cin>>temp; 
        q.push(temp);
        i++;
    }

    cin.ignore();

    string meet;
    cout<<"Enter the meeting time : ";
    getline(cin,meet);

    // Time 10:00 in minutes -> 600 minutes
    // Time for meet -> meet*60.

    int base_min = 600;
    int meet_min = 0;
    
    stringstream ss(meet);
    int sec;
    char c;
    
    ss>>meet_min;
    meet_min *= 60;
    ss>>c;
    ss>>sec;
    meet_min += sec;


    // base minutes = 600
    // exceeding val = meeting minutes
    bool flag = 0;
    i = 1;
    while(!q.empty())
    {
        base_min += q.front();
        q.pop();
        if(base_min>meet_min)
        {
            flag = 1;
            break;
        }
        i++;
    }

    
    if(flag)
    {
        cout<<"Reschedule the task : "<<i<<endl;
        cout<<meet_min<<endl;
    }
    else
    {
        cout<<"No Rescheduling Needed "<<endl;
    }
    return 0;
}
