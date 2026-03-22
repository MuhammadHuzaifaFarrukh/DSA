#include <iostream>
#include <string>
#include <stack>

using namespace std;
string reverseprefix(string word , char ch)
{
    int ind = -1;
    for(int i = 0 ; i<word.length() ; i++)
    {
        if(word[i] == ch)
        {
            ind = i;
            break;
        }
    }
    if(ind == -1)
    {
        return word;
    }
    stack <char> cont;
    for(int i = 0 ; i<=ind ;i++)
    {
        cont.push(word[i]);
    }

    for(int i = 0 ; i <=ind ;i++)
    {
        word[i] = cont.top();
        cont.pop();
    }
    return word;
}

int main()
{
    string s ;
    char ch;
    cout<<"Enter a word : ";
    getline(cin ,s);
    cout<<"Enter a character : ";
    cin>>ch;
    string x = reverseprefix(s,ch);

    cout<<"Reversed Prefix : "<<x<<endl;
    
    return 0;
}