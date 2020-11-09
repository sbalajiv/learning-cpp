#include <iostream>
#include <cstdlib>

/*
 * Problem: Rotate a singly linked list to the right k times
 * 
 * Constraint: Does not work for k > n, n --> number of nodes in the list
 */

typedef struct _Node {
    int value;
    struct _Node *next;
} Node;

// Forward delcarations
Node * create_list(const int);
void print_list(const Node *);
Node * rotate_list_right_in_place(Node *, const int);
void delete_list(Node *);

/*
 * Create a list of 'n' nodes
 */
Node * create_list(const int n) {
    // Initializing random number generator
    std::srand(0xdeadbeef);

    Node *s = nullptr;
    Node *t = nullptr;

    for(int i=0; i < n; ++i)
    {
        try
        {
            t = new Node;
        }
        catch (const std::bad_alloc& e)
        {
            std::cout << "Allocation failed : " << e.what() << "\n";
            delete_list(s);
            return nullptr;
        }

        t->value = std::rand() % 1000;
        if (s == nullptr) {
            t->next = nullptr;
        }
        else {
            t->next = s;
        }
        s = t;
    }

    return s;
}

/*
 * Print the given list to console
 */
void print_list(const Node *s) {
    while (s != nullptr) {
        std::cout << s->value << " ";
        s = s->next;
    }
    std::cout << "\n";
}

/*
 * Rotate list k time to the right, in place.
 * Arrangement of the nodes in the list are changed.
 */
Node * rotate_list_right_in_place(Node *s, const int k) {
    if ((s == nullptr) || (k <=0)) {
        return nullptr;
    }

    Node *t1 = s;
    Node *t2 = s;

    // Set 2 pointers with distance k node between them
    for(int i=0; ((i < k) && (t2 != nullptr)); ++i, t2=t2->next)
        ;
     
    if (t2 == nullptr) {
        return nullptr;
    }

    // move t1 and t2, till t2 hits end of list
    while(t2->next != nullptr){
        t2 = t2->next;
        t1 = t1->next;
    }

    // Rearrange the list to rotate.
    t2->next = s;
    s = t1->next;
    t1->next = nullptr;
    
    return s;
}

/*
 * Release all memory allocated to the list
 */
void delete_list(Node *s) {
    Node *t = nullptr;

    if (s != nullptr) {
        while (s->next != nullptr) {
            t = s->next;
            delete s;
            s = t;
        }
    }
}

int main()
{
    Node *start = nullptr;

    start = create_list(10);

    if (start == nullptr) {
        std::cout << "Start is nullptr" << "\n";
        return -1;
    }

    // this is k, number of times to rotate
    int k = 2;

    // print initialized list
    print_list(start);

    auto l = rotate_list_right_in_place(start, k);

    if (l != nullptr) {
        print_list(l);
        delete_list(l);
    }
    else {
        // rotation not possible
        print_list(start);
        delete_list(start);
    }
}