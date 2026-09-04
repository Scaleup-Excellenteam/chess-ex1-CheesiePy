#pragma once
#include "ThreadPool.h"

/* Access the single global thread-pool instance.
   The first call creates it with `nThreads` threads (defaults to HW cores). */
ThreadPool& globalPool(std::size_t nThreads = std::thread::hardware_concurrency());
