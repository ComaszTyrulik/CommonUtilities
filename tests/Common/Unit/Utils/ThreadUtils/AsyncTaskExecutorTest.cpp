#include "AsyncTaskExecutorTest.h"

#include <Common/Utils/ThreadUtils/AsyncTaskExecutor.h>
#include <atomic>

namespace CT_COMMON_NAMESPACE::tests::unit
{
    TEST_F(AsyncTaskExecutorTest, ExecuteWillRunGivenLambdaFunctionAtLeastOnce)
    {
        std::size_t numberOfElements = 100;

        std::atomic_size_t actualCount = 0;
        const auto function = [&](std::size_t firstIndex, std::size_t endIndex) {
            actualCount++;
        };

        AsyncTaskExecutor sut(numberOfElements, function);
        sut.Execute();

        ASSERT_TRUE(actualCount > 0);
    }

    TEST_F(AsyncTaskExecutorTest, ExecuteWillNotRunGivenLambdaFunctionIfNumberOfElementsIs0)
    {
        std::size_t numberOfElements = 0;

        std::atomic_size_t actualCount = 0;
        const auto function = [&](std::size_t firstIndex, std::size_t endIndex) {
            actualCount++;
        };

        AsyncTaskExecutor sut(numberOfElements, function);
        sut.Execute();

        ASSERT_EQ(0, actualCount);
    }
} // namespace sce::tests::unit
