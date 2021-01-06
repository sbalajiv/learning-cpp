#include <iostream>
#include <vector>
#include <string>

// Declaration of the ternary tree node
template <typename T>
struct TernaryNode {
  T value;
  struct TernaryNode<T> *left;
  struct TernaryNode<T> *middle;
  struct TernaryNode<T> *right;
};

// Specialization of the integer ternary node
typedef struct TernaryNode<char> TNode;

// Vector of strings type
typedef std::vector<std::string> VecStrings_t;

TNode* CreateTernaryTree(VecStrings_t &vs) {
  TNode *root = nullptr;
  TNode *temp = nullptr;

  if (vs.size() == 0) {
    std::cout << "Input vector strings is empty" << "\n";
    return nullptr;
  }

  for(auto &s : vs) {
    for(auto &c : s) {
      temp = new TNode;
      if (temp == nullptr) {
        
      }
      if (root == nullptr) {
      } else {

      }
    }
  }
}

int main()
{
  VecStrings_t vs = {"code", "cob", "be", "ax", "war", "we"};

  TNode *root = nullptr;

}
