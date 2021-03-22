// AddTwoListOfNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <iterator>

#include "LinkedList.h"

// Given the iterator from src and a destination list dst,
// Copy and append and nodes from src to destination dst.
template <typename Iterator, typename T>
void AddAppendNodesFromPosition(Iterator src, LinkedList<T> &dst, int carry, Iterator src_end)
{
    // If you are at the end, nothing much to do
    if (src == src_end)
    {
        return;
    }

    // Loop through, add and append to dst
    auto s = 0;
    while (src != src_end)
    {
        s = *src + carry;
        if (s > 9)
        {
            carry = s / 10;
            s %= 10;
        }
        else
        {
            carry = 0;
        }
        dst.AddValueAtLastPosition(s);
        ++src;
    }

    // If carry exists, append it to dst
    if (carry != 0)
    {
        dst.AddValueAtLastPosition(carry);
    }
}

// add two list of numbers
template <typename T>
LinkedList<T> addTwoNumbers(LinkedList<T> &l1, LinkedList<T> &l2)
{
    if (l1.size() == 0)
    {
        return l2;
    }
    else if (l2.size() == 0)
    {
        return l1;
    }
    else
    {
        auto s1 = l1.begin();
        auto s2 = l2.begin();
        int sum = 0;
        int carry = 0;
        auto res = LinkedList<T>();

        // iterate and add numbers
        while ((s1 != l1.end()) && (s2 != l2.end()))
        {
            sum = *s1 + *s2 + carry;

            if (sum > 9)
            {
                carry = sum / 10;
                sum %= 10;
            }
            else
            {
                carry = 0;
            }

            res.AddValueAtLastPosition(sum);
            ++s1;
            ++s2;
        }

        if ((s1 != l1.end()) || (s2 != l2.end()))
        {
            if (s1 != l1.end())
            {
                AddAppendNodesFromPosition<decltype(s1), T>(s1, res, carry, l1.end());
            }
            else
            {
                AddAppendNodesFromPosition<decltype(s2), T>(s2, res, carry, l2.end());
            }
        }
        else
        {
            if (carry != 0)
            {
                res.AddValueAtLastPosition(carry);
            }
        }

        return res;
    }
}

int main()
{
    std::vector<int> v1 = {9, 9, 9, 9, 9, 9, 9};
    std::vector<int> v2 = {9, 9, 9};

    auto l1 = LinkedList<int>(v1);

    auto l2 = LinkedList<int>(v2);

    LinkedList<int> res = std::move(addTwoNumbers<int>(l1, l2));

    for (const auto &n : res)
    {
        std::cout << n << "\n";
    }
}
