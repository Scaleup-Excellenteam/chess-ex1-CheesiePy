#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Exception.h"  // Chess::UnderflowException
#include <list>

// templated priority queue: T is the element type, Comparator returns
// positive if a has higher priority than b, negative if lower, zero if equal.
template<typename T, typename Comparator>
class PriorityQueue {
private:
    std::list<T> data;    // store elements in priority order
    Comparator cmp;       // user-supplied comparator

public:
    // allow injecting a custom comparator (defaults to Comparator())
    explicit PriorityQueue(const Comparator& comp = Comparator())
        : cmp(comp) {}

    // insert element into its sorted position (O(n))
    void push(const T& value) {
        auto it = data.begin();
        // find first element with lower priority than 'value'
        for (; it != data.end(); ++it) {
            if (cmp(value, *it) > 0) {
                break;
            }
        }
        data.insert(it, value);
    }

    // remove and return the highest-priority element (O(1))
    // throws Chess::UnderflowException if empty
    T poll() {
        if (data.empty()) {
            throw Chess::UnderflowException(); // <== custom exception
        }
        T front = data.front();
        data.pop_front();
        return front;
    }

    // convenience queries
    bool empty() const { return data.empty(); }
    std::size_t size() const { return data.size(); }
};

#endif // PRIORITYQUEUE_H
