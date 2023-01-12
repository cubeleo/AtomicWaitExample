#include <atomic>
#include <chrono>
#include <future>
#include <stdint.h>

int main()
{
    std::atomic<bool> all_tasks_completed = false;
    std::atomic<uint32_t> outstanding_task_count;
    std::future<void> task_futures[16];

    std::atomic<uint32_t> completion_count = 0;

    // Spawn several tasks which take different amounts of time, then
    // decrement the outstanding job count.
    for (size_t i = 0; i < 16; ++i)
    {
        ++outstanding_task_count;
        task_futures[i] = std::async([&outstanding_task_count, &all_tasks_completed, &completion_count, i]()
        {
            // This sleep represents doing real work...
            std::this_thread::sleep_for(std::chrono::milliseconds(5 * i));

            ++completion_count;

            --outstanding_task_count;

            // When the task count falls to zero, notify any waiters.
            if (outstanding_task_count.load() == 0)
            {
                all_tasks_completed = true;
                all_tasks_completed.notify_one();
            }
        });
    }

    all_tasks_completed.wait(false);

    printf("Tasks completed = %u\n", completion_count.load());

    return 0;
}
