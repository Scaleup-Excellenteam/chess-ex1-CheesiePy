// ThreadSafePriorityQueue.h
#pragma once
#include <queue>
#include <mutex>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class ThreadSafePriorityQueue {
public:
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        pq_.push(item);
    }

    bool try_pop(T& out) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pq_.empty()) return false;
        out = pq_.top();
        pq_.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return pq_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::priority_queue<T, std::vector<T>, Compare> pq_;
};
