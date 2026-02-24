#include "Stack.hpp"
#include <iostream>

using namespace std;

int main()
{
    Stack<int> s = {10, 20, 30};
    std::cout << "Manual Stack Top: " << s.top() << std::endl;
    s.push(40);
    s.display(); // Top to Bottom: 40, 30, 20, 10
    return 0;
}