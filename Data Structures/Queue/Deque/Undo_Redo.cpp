#include <iostream>
#include <deque>
#include <string>
using namespace std;
int main()
{
    deque<string> undoStack, redoStack;
    string text = "";
    int choice;
    do
    {
        cout << "\nCurrent text: " << text << "\n";
        cout << "--- Undo/Redo System ---\n";
        cout << "1. Add text\n";
        cout << "2. Undo\n";
        cout << "3. Redo\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            string add;
            cout << "Enter text to append: ";
            getline(cin, add);
            undoStack.push_back(text);
            text += add;
            redoStack.clear();
            break;
        }
        case 2:
            if (undoStack.empty())
                cout << "Nothing to undo.\n";
            else
            {
                redoStack.push_back(text);
                text = undoStack.back();
                undoStack.pop_back();
            }
            break;
        case 3:
            if (redoStack.empty())
                cout << "Nothing to redo.\n";
            else
            {
                undoStack.push_back(text);
                text = redoStack.back();
                redoStack.pop_back();
            }
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}