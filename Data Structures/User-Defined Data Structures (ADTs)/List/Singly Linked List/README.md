# Templated Singly Linked List (C++)

A comprehensive, header-only C++ template implementation of a **Singly Linked List**. This project provides a flexible `List` class that supports various data types, manual memory management, and modern C++ features like range-based for loops.

## 🚀 Features

- **Generic Programming**: Uses C++ Templates to support any data type (`int`, `double`, `std::string`, or custom objects).
- **Manual Memory Management**: Proper implementation of the **Rule of Three** (Copy Constructor, Assignment Operator, and Destructor) to prevent memory leaks and dangling pointers.
- **Iterator Support**: Custom `Iterator` class allows for the use of standard range-based for loops: `for(auto x : myList)`.
- **Sorting**: Built-in `selectionSort()` specifically designed for linked structures.
- **Rich API**: 
  - Insertion/Deletion at front, back, or specific index.
  - Search and element access via `operator[]`.
  - List concatenation methods: `append`, `append_shared`, and `join` (splice).

## 📂 File Structure

- `List.hpp`: The core header file containing the `Node` class, `List` class, and `Iterator` class.

## 🛠️ Usage

Since this is a template-based header-only library, you simply need to include `List.hpp` in your project.

### FUNCTIONS

* **`push_front_list(T val)`** Adds a new element to the start of the list.
* **`push_back_list(T val)`** Adds a new element to the end of the list.
* **`pop_front_list()`** Removes the first element and deallocates its memory.
* **`pop_back_list()`** Removes the last element (requires O(n) traversal to update the tail).
* **`insert_node(T val, int ind)`** Inserts a value at a specific index; automatically handles front/back cases.
* **`remove_node(int ind)`** Removes the node at the specified index and reconnects the list.
* **`selectionSort()`** Sorts the list in ascending order by swapping node data.
* **`linear_search(T target)`** Returns the zero-based index of the target value, or -1 if not found.
* **`clear_list()`** Deallocates all nodes in the list to prevent memory leaks.
* **`join(List& other)`** Moves all nodes from another list to this one (the other list becomes empty).
---

### How to Compile and Run:
* Run this by command normally using `g++ file_name.cpp -o my_program` as done here in the Basic Example of "List.hpp" file (Not a good practice).
* If you have separated files for each class i.e separate classes for List , Node , Iterator and then include all the necessary headers in your file then you need to run by including all the .cpp files like below example:
  `g++ file_name.cpp List.cpp Node.cpp Iterator.cpp -o my_program`
Although it works by both methods , the choice depends on your design and style you prefer in working environment which makes ease for you.

### Basic Example

```cpp
#include "List.hpp"
#include <iostream>

int main()
{
    List<int> myList;

    // Adding elements
    myList.push_back_list(10);
    myList.push_back_list(20);
    myList.push_front_list(5);

    // Using range-based for loop (via Iterators)
    std::cout << "List contents: ";
    for (int val : myList)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Sorting
    myList.push_back_list(1);
    myList.selectionSort();

    // Printing using overloaded << operator
    std::cout << "Sorted list: " << myList;

    return 0;
}
