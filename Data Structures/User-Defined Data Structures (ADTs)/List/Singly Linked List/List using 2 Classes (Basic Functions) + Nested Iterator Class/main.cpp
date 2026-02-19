#include <iostream>
#include "Singly_List.hpp"

using namespace std;

int main()
{
    List l1;
    l1.push_back_list(67);
    l1.push_back_list(68);
    l1.push_back_list(65);
    l1.push_back_list(69);
    l1.insert_node(66,4);
    l1.print_list();
    l1.selectionSort();
    l1.print_list();
    cout<<"\nSize : "<<l1.size<<endl;

    List::Iterator it = l1.begin();
    cout<<"Value at Head : "<<*it<<endl;
//    it = l1.end();    //Invalid Memory Location
    it++;
    cout<<"Next Value from Head : "<<*it<<endl;
//    //Using For-Range Based Loop :
    for(char x : l1)
    {
        cout<<x<<"  ";
    }
    cout<<endl;
    for(int x : l1)
    {
        cout<<x<<" ";
    }

    return 0;
}

