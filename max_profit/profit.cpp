#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
/*
    Given an array of numbers representing the stock prices of a company in chronological order, 
    write a function that calculates the maximum profit you could have made from buying and 
    selling that stock once. You must buy before you can sell it.

    For example, given [9, 11, 8, 5, 7, 10], you should return 5, 
    since you could buy the stock at 5 dollars and sell it at 10 dollars.
*/
uint32_t get_max_profit(const std::vector<int> &v)
{
    auto profit = 0;

    if (v.size() > 1)
    {
        auto minval = std::min_element(std::begin(v), std::end(v));
        auto maxval = std::max_element(minval, std::end(v));
        profit = *maxval - *minval;
    }

    return profit;
}

int main()
{
    //auto v = {5, 1, 3, 2, 1, 4, 1};
    auto v = {9, 11, 8, 5, 7, 10};
    //std::vector<int> v = {1};

    std::cout << "Max difference : " << get_max_profit(v) << "\n";
    return 0;
}
