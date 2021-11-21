#pragma once

#include <iostream>
#include <vector>

template <typename T>
class CartesianTreeMaxHeap
{
        private:
                typedef struct _tree_node
                {
                        T data;
                        struct _tree_node *right;
                        struct _tree_node *left;

                        _tree_node() = delete;
                        _tree_node(T item) : data(item), left(nullptr), right(nullptr) {} //, is_leaf(true) {}
                } TreeNode;

                TreeNode *root;

                // Construct a cartesian tree with Max Heap property
                void _create_cartesian_tree_from_sequence(std::vector<T> &seq)
                {
                        for(const auto &item : seq)
                        {
                                if (root == nullptr) {
                                        root = new TreeNode(item);
                                } else {
                                        _insert_in_cartesian_tree(item);
                                }
                        }
                }

                // Insert an item in cartesian tree satisfying max heap
                void _insert_in_cartesian_tree(T item)
                {
                        TreeNode *node = new TreeNode(item);
                        if (root->data > item) {
                                node->left = root;
                                root = node;
                        } else {
                                auto insert_node = _find_node_to_insert(root);
                                insert_node->right = node;
                        }
                }

                // Find a node with no right sub-tree
                TreeNode* _find_node_to_insert(TreeNode *node)
                {
                        if (node->right == nullptr) {
                                return node;
                        }
                        return _find_node_to_insert(node->right);
                }

                // Helper function for destructor 
                void _delete_all_nodes_post_order(TreeNode *root)
                {
                        if (root == nullptr) {
                                return;
                        }
                        _delete_all_nodes_post_order(root->left);
                        _delete_all_nodes_post_order(root->right);
                        delete root;
                }

                // Helper funcion for inorder traversal and print the tree nodes
                void _cartesian_print_sequence(TreeNode *node)
                {
                        if (node== nullptr) {
                                return;
                        }
                        _cartesian_print_sequence(node->left);
                        std::cout << node->data << " ";
                        _cartesian_print_sequence(node->right);
                }

        public:
                // default constructor currently not supported
                CartesianTreeMaxHeap() = delete;
                CartesianTreeMaxHeap(std::vector<T> &seq) : root(nullptr)
                {
                        if (seq.size() > 0)
                        {
                                _create_cartesian_tree_from_sequence(seq);
                        }
                }

                ~CartesianTreeMaxHeap()
                {
                        _delete_all_nodes_post_order(root);
                }

                void print_sequence()
                {
                        _cartesian_print_sequence(root);
                        std::cout << "\n";
                }
};
