#pragma once

// Node in the singly linked list
template <typename T>
struct ListNode
{
    // Data member
    T val;

    // Next node in the list
    ListNode<T> *next;

    // Default constructor
    ListNode() : val{}, next(nullptr) {}

    // Helpful constructors
    ListNode(T x) : val(x), next(nullptr) {}
    ListNode(T x, ListNode<T> *next) : val(x), next(next) {}

    // type trait
    using value_type = T;
};

// Linked list manager
template <typename T>
class LinkedList
{
private:
    //Pointer to dummy start node - sentinel
    ListNode<T> *start;

    // Count of elements in the list
    std::size_t count;

    // Pointer to the last node in the list (not dummy node)
    ListNode<T> *last;

    // Pointer to the dummy last node - sentinel
    ListNode<T> *tail;

public:
    // Utility function to know number of elements in the list
    std::size_t size()
    {
        return count;
    }

    // Custom const forward iterator
    class const_iterator
    {
    public:
        // Some iterator type traits
        using value_type = T;
        using iterator_tag = std::forward_iterator_tag;

        // Constructors
        const_iterator(LinkedList<T> *pos) : curr(pos) {}
        const_iterator() : curr(nullptr) {}

        // Iterator dereference
        const T &operator*() const
        {
            return curr->val;
        }

        // != operator overloading - useful for looping
        bool operator!=(const_iterator rhs) const
        {
            return this->curr != rhs.curr;
        }

        // Prefix ++ operation for const iterator
        const_iterator &operator++()
        {
            if (this->curr != nullptr)
            {
                this->curr = this->curr->next;
                return this;
            }
            else
            {
                return nullptr;
            }
        }

        // Postfix ++ operation for const iterator
        const_iterator operator++(int)
        {
            auto old = *this;
            ++*this;
            return old;
        }

        // Equality operation for const iterator
        bool operator==(const const_iterator &rhs)
        {
            return this->curr == rhs.curr;
        }

        // Iterator is a wrapper around a pointer to a ListNode
        ListNode<T> *curr;
    };

    // Custom forward interator
    class iterator : public const_iterator
    {
    public:
        // Base class name alias
        using _Base = const_iterator;

        // Constructor
        iterator(ListNode<T> *pos)
        {
            _Base::curr = pos;
        }

        // Prefix ++ operation on iterator
        iterator &operator++()
        {
            if (this->curr != nullptr)
            {
                this->curr = this->curr->next;
            }
            return *this;
        }

        // Postfix ++ operation on iterator
        iterator operator++(int)
        {
            auto old = *this;
            _Base::operator++();
            return old;
        }

        // Iterator dereference
        T &operator*()
        {
            return _Base::curr->val;
        }

        // Equality operation
        bool operator==(iterator &rhs)
        {
            return this->curr == rhs.curr;
        }

        // Not equal operation
        bool operator!=(iterator rhs)
        {
            return this->curr != rhs.curr;
        }
    };

    iterator begin()
    {
        return iterator(start->next);
    }

    iterator end()
    {
        return iterator(tail);
    }

    const_iterator begin() const
    {
        return const_iterator(start->next);
    }

    const_iterator end() const
    {
        return const_iterator(tail);
    }

    // Default constructor
    LinkedList()
    {
        count = 0;
        start = new ListNode<T>();
        tail = new ListNode<T>();
        start->next = tail;
        last = nullptr;
    }

    /*
     * Constructor to take the input vector and convert it to a an singly linked list
     */
    LinkedList(const std::vector<T> &v) : LinkedList()
    {
        ListNode<T> *tmp = nullptr;

        for (const auto &i : v)
        {
            tmp = new ListNode<T>(i, tail);
            if (count == 0)
            {
                start->next = tmp;
            }
            else
            {
                last->next = tmp;
            }
            last = tmp;
            ++count;
        }
    }

    // Copy constructor
    LinkedList(LinkedList<T> &l) : LinkedList()
    {
        start = new ListNode<T>();
        tail = new ListNode<T>();
        start->next = tail;

        auto t = l.start->next;
        ListNode<T> *tmp = nullptr;
        last = nullptr;

        while (t != l.tail)
        {
            AddValueAtLastPosition(t->val);
            t = t->next;
        }
    }

    // Move constructor
    LinkedList(LinkedList<T> &&l) noexcept
    {
        start = l.start;
        tail = l.tail;
        count = l.count;
        last = l.last;

        l.start = nullptr;
        l.tail = nullptr;
        l.count = 0;
        l.last = nullptr;
    }

    // Default destructor
    ~LinkedList<T>()
    {
        ListNode<T> *t = nullptr;
        if ((start != nullptr) && (tail != nullptr))
        {
            ListNode<T> *trav = start->next;
            while (trav != tail)
            {
                t = trav->next;
                delete trav;
                trav = t;
            }
            delete start;
            delete tail;
            count = 0;
        }
    }

    // Insert a node as first node in the list
    void AddNodeAtFirstPosition(ListNode<T> *node)
    {
        if (node != nullptr)
        {
            node->next = start->next;
            start = node;
            ++count;
        }
    }

    // Insert a given node as last node
    void AddNodeAtLastPosition(ListNode<T> *node)
    {
        if (node != nullptr)
        {
            node->next = tail;
            if (last != nullptr)
            {
                last->next = node;
            }

            last = node;
            ++count;
        }
    }

    // Insert given value as a first node in the list
    void AddValueAtFirstPosition(const T &val)
    {
        start = new ListNode<T>(val, start);
        ++count;
    }

    // Insert give value as last node in the list
    void AddValueAtLastPosition(const T &val)
    {
        auto t = new ListNode<T>(val, tail);

        if (last != nullptr)
        {
            last->next = t;
        }
        last = t;
        if (count == 0)
        {
            start->next = t;
        }
        ++count;
    }
};