// BinaryTreeRangeSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <utility>
#include "BinarySearchTree.h"

/*
Given a binary search tree and a range [a, b] (inclusive), return the sum of the elements of 
the binary search tree within the range.

For example, given the following tree:

    5
   / \
  3   8
 / \ / \
2  4 6  10

and the range [4, 9], return 23 (5 + 4 + 6 + 8).
*/

int main()
{
    std::vector<int> x = { 4, 3, 2, 5, 10, 8, 6 };
    
    auto b = BinarySearchTree<int>(x);
    std::cout << "Range Sum: " << b.FindRangeSum(4,9) << "\n";
}
