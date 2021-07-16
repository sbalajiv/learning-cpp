#pragma once

#include <initializer_list>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T>
class BinarySearchTree
{
private:
    struct node {
        T data;
        struct node* left;
        struct node* right;

        node(T v) : data(v), left(nullptr), right(nullptr) {};
    };

    using Node = struct node;

    Node* root;

    Node* _FindNodeToInsert(T v)
    {
        auto trav = root;

        while (trav != nullptr) {
            if (v > trav->data) {
                if (trav->right == nullptr) {
                    break;
                }
                else {
                    trav = trav->right;
                }
            }
            else {
                if (trav->left == nullptr) {
                    break;
                }
                else {
                    trav = trav->left;
                }
            }
        }

        return trav;
    }

    void _InsertValueAt(Node* node, T v)
    {
        auto tmp = new Node(v);
        if (v > node->data) {
            node->right = tmp;
        }
        else {
            node->left = tmp;
        }
    }

    void _DeallocateTree(Node* node)
    {
        if (node == nullptr) {
            return;
        }
        _DeallocateTree(node->left);
        _DeallocateTree(node->right);

        delete node;
    }

    void _FindElementsInRange(Node* t, std::pair<T, T>& pr, std::vector<T>& v)
    {
        if (t == nullptr) {
            return;
        }

        if ((t->data >= pr.first) && (t->data <= pr.second)) {
            v.push_back(t->data);
            if (t->left != nullptr)
                _FindElementsInRange(t->left, pr, v);
            if (t->right != nullptr)
                _FindElementsInRange(t->right, pr, v);
        }
        else {
            if (t->data < pr.first) {
                if (t->right != nullptr)
                    _FindElementsInRange(t->right, pr, v);
            }
            else if (t->data > pr.second) {
                if (t->left != nullptr)
                    _FindElementsInRange(t->left, pr, v);
            }
        }
    }

public:
    
    BinarySearchTree() : root(nullptr) {}
    
    BinarySearchTree(std::vector<T>& v) {
        root = nullptr;
        auto sz = v.size();
        auto mid_index = (sz / 2) - 1;

        root = new Node(v[mid_index]);

        if (root == nullptr) {
            return;
        }

        for (std::size_t i = 0; i < sz; ++i) {
            if (i == mid_index) {
                continue;
            }

            auto t = _FindNodeToInsert(v[i]);
            if (t != nullptr) {
                _InsertValueAt(t, v[i]);
            }
            else {
                // unlikely
                return;
            }
        }
    }

    ~BinarySearchTree()
    {
        _DeallocateTree(root);
    }

    T FindRangeSum(T min, T max)
    {
        auto t = root;
        std::vector<T> v;
        std::pair<T, T> pr = { min, max };
        
        _FindElementsInRange(root, pr, v);
        return std::reduce(v.begin(), v.end());
    }
};
