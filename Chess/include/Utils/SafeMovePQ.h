#pragma once
/*
   Thread-safe max-heap of MoveScorePair
   ------------------------------------
   push()      : O(log n)   (multiple producers)
   try_pop()   : O(log n)   (multiple consumers)
*/
#include "Utils/MoveScorePair.h"
#include <queue>
#include <vector>
#include <mutex>
#include <optional>

/* Comparator: higher score → higher priority */
struct MoveScoreGreater {
    bool operator()(const MoveScorePair& a,
                    const MoveScorePair& b) const noexcept
    {
        return a.score < b.score;   // reverse for max-heap
    }
};

class SafeMovePQ
{
public:
    void push(const MoveScorePair& m)
    {
        std::lock_guard<std::mutex> lk(mtx_);
        pq_.push(m);
    }

    std::optional<MoveScorePair> try_pop()
    {
        std::lock_guard<std::mutex> lk(mtx_);
        if (pq_.empty()) return std::nullopt;
        MoveScorePair best = pq_.top();
        pq_.pop();
        return best;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mtx_);
        return pq_.empty();
    }

private:
    mutable std::mutex mtx_;
    std::priority_queue<
        MoveScorePair,
        std::vector<MoveScorePair>,
        MoveScoreGreater
    > pq_;
};
