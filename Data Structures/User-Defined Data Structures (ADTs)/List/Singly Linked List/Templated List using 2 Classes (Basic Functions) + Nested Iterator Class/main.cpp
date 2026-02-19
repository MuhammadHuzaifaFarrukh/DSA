#include <iostream>
#include "Singly_List.hpp"

using namespace std;

int main()
{
    List<string> l1;

    l1.push_back_list("banana");
    l1.push_back_list("apple");
    l1.push_back_list("cherry");
    l1.push_back_list("Avocado");
    l1.insert_node("Zebra",4);
    List<string> l2;
    l2 = l1;
    List<string>::Iterator it = l1.begin();

    //Using Iterators
    for( ; it!= l1.end() ; it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

    l1.append_shared(l2);
    cout<<l1<<endl;
    l1.join(l2);
    cout<<l2<<endl;

    //Using For-Range Based loop
    for(string c :  l1)
    {
        cout<<c<<" ";
    }
    cout<<endl<<l1<<endl;

    l2.print_list();
    l2.selectionSort();
    l2.print_list();
    cout<<"\n"<<l2.size;
    return 0;

}
