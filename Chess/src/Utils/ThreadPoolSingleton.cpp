#include "Utils/ThreadPoolSingleton.h"

ThreadPool& globalPool(std::size_t nThreads)
{
    static ThreadPool pool{ nThreads };   // constructed once, thread-safe in C++11+
    return pool;
}