#pragma once
#include "Common/Types.h"
#include "Common/Helpers.h"

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Provides static, time-related functionalities.
     */
    class Time final
    {
    public:
        CT_IMPLEMENT_CLASS_NOT_CONSTRUCTIBLE(Time);

        /**
         * @brief Calculates and returns current time since epoch as timestamp.
         */
        static Timestamp GetCurrentTimestamp();
    };
} // namespace CT_COMMON_NAMESPACE
