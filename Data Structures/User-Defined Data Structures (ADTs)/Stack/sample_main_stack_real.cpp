#include "Stack_real.hpp"
#include <vector>
#include <string>

using namespace std;

int main()
{
    // Using default deque
    Stack<std::string> s = {"A", "B", "C"};
    s.display();

    // Forcing it to use a vector engine
    Stack<int, std::vector<int>> vStack = {1, 2, 3};
    vStack.push(4);
    std::cout << "Adaptor Stack (Vector Engine) Top: " << vStack.top() << std::endl;

    return 0;
}