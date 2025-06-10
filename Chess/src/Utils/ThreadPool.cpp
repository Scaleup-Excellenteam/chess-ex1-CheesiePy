#include "Utils/ThreadPool.h"

ThreadPool::ThreadPool(size_t threads)
{
    for (size_t i = 0; i < threads; ++i)
    {
        workers.emplace_back([this] {
            for (;;)
            {
                std::function<void()> task;

                {   // --- critical section -----------------------------
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    condition.wait(lock,
                        [this]{ return stop || !tasks.empty(); });

                    if (stop && tasks.empty())
                        return;                 // graceful exit

                    task = std::move(tasks.front());
                    tasks.pop();
                }   // --- lock released here ---------------------------

                task();                         // run user work
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    {   // signal all threads to stop
        std::lock_guard<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();

    for (std::thread& t : workers)
        if (t.joinable()) t.join();
}