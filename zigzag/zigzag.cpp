/*
   Given a string and a number of lines k, print the string in zigzag form. 
   In zigzag, characters are printed out diagonally from top left to bottom 
   right until reaching the kth line, then back up to top right, and so on.

   For example, given the sentence "thisisazigzag" and k = 4, you should print:

   t     a     g
    h   s z   a
     i i   i z
      s     g
*/

#include <iostream>
#include <memory>
#include <string>

enum class Direction { Down, Up };

void _fill_bytes(char *buf, size_t sz, char ch)
{
    for (int i = 0; i < sz; ++i)
    {
        *(buf+i)= ch;
    }
}

void _print_matrix(char* mat, int rows, int cols)
{
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            std::cout << *(mat + row + col) << " ";
        }
        std::cout << "\n";
    }
}

void fill_print_zig_zag(const std::string& str, const int k)
{
    auto slen = str.length();
    size_t mat_sz = slen * k;
    auto char_matrix = new char[k * slen];
    auto direction = Direction::Down;

    _fill_bytes(char_matrix, mat_sz, ' ');
    _print_matrix(char_matrix, k, slen);
    for (int col = 0, row = 0; col < slen; ++col)
    {
        if (direction == Direction::Down)
        {
            if (row < k)
            {
                std::cout << "Down : " << row << " " << col << " " << str[col] << "\n";
                *(char_matrix + (row * slen) + col) = str[col];
                ++row;
            }
            else
            {
                row = k - 2;
                std::cout << row << " " << col << " " << str[col] << "\n";
                *(char_matrix + (row * slen) + col) = str[col];
                --row;
                direction = Direction::Up;
            }
        }
        else
        {
            if (row >= 0)
            {
                std::cout << "Up : " << row << " " << col << " " << str[col]<< "\n";
                *(char_matrix + (row * slen) + col) = str[col];
                --row;
            }
            else
            {
                row = 1;
                *(char_matrix + (row * slen) + col) = str[col];
                std::cout << row << " " << col << " " << str[col]<< "\n";
                ++row;
                direction = Direction::Down;
            }
        }
    }

    _print_matrix(char_matrix, k, slen);
}

int main()
{
    std::string str = "thisisazigzag";
    const int k = 4;

    fill_print_zig_zag(str, k);

    return 0;
}
