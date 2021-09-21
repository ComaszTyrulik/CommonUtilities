#include "Common/Utils/Time.h"

namespace CT_COMMON_NAMESPACE
{
    Timestamp Time::GetCurrentTimestamp()
    {
        const auto currentTime = std::chrono::system_clock::now();
        const auto currentTimestamp = currentTime.time_since_epoch();

        return std::chrono::duration_cast<TimestampDuration>(currentTimestamp).count();
    }
} // namespace CT_COMMON_NAMESPACE
