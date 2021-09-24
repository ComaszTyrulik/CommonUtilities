#pragma once
#include "Common/Resources.h"

#include <thread>
#include <future>

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Evenly divides work into multiple threads.
     */
    class AsyncTaskExecutor final
    {
    private:
        using Task = std::function<void(std::size_t, std::size_t)>;

    public:
        /**
         * @brief Initializes executor.
         * The perTastAction must have the following format perTaskAction(std::size_t firstIndex, std::size_t lastIndex)
         * where given values define inclusive range of indices to handle by each task:
         * @code
         * [](std::size_t firstIndex, std::size_t lastIndex) {
         *  for (std::size_t index = firstIndex; index <= lastIndex; ++index)
         *  {
         *      // Do something with index
         *  }
         * }
         * @endcode
         *
         * 
         * @param numberOfElementsToProcess - Total number of elements to process. Those will be divided into async tasks
         * @param perTaskAction - A function to be executed for each async task
         */
        AsyncTaskExecutor(std::size_t numberOfElementsToProcess, Task perTaskAction)
            : m_numberOfElements(numberOfElementsToProcess), m_task(perTaskAction)
        {
        }

        /**
         * @brief Divides workload and asynchronously execute perTaskAction provided during construction.
         */
        void Execute() const
        {
            if (m_numberOfElements == 0)
            {
                return;
            }

            const auto availableThreads = std::min(m_numberOfElements, static_cast<std::size_t>(std::thread::hardware_concurrency()));
            const auto numberOfElementsPerTask = m_numberOfElements / availableThreads;
            const auto lastTaskElements = numberOfElementsPerTask + (m_numberOfElements % availableThreads); // If numberOfElements is not divisable by availableThreads, the last task gets the remainder of the elements to process

            std::vector<std::future<void>> tasks(availableThreads);
            for (std::size_t i = 0; i < availableThreads; ++i)
            {
                auto elementsInTask = (i == availableThreads - 1) ? lastTaskElements : numberOfElementsPerTask;

                const auto firstIndex = i * numberOfElementsPerTask;
                const auto lastIndex = firstIndex + elementsInTask - 1;

                tasks[i] = std::async(std::launch::async, m_task, firstIndex, lastIndex);
            }
        }

    private:
        std::size_t m_numberOfElements = 0;
        Task m_task;
    };
} // namespace CT_COMMON_NAMESPACE
