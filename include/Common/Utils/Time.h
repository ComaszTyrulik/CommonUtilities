#pragma once
#include "Common/Types.h"

namespace CT_COMMON_NAMESPACE
{
    class Time final
    {
    public:
        /**
         * @brief Calculates and returns current time since epoch as timestamp.
         */
        static Timestamp GetCurrentTimestamp();
    };
} // namespace CT_COMMON_NAMESPACE
