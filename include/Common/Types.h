#pragma once
#include "Common/Resources.h"

#include <xxHash/xxhash.h>

#include <memory>
#include <string_view>
#include <filesystem>
#include <cstdint>
#include <string>
#include <map>
#include <unordered_map>
#include <chrono>
#include <map>
#include <string>
#include <vector>

namespace CT_COMMON_NAMESPACE
{
    /*********************BASIC TYPES DEFINITIONS*************************/
    using byte = unsigned char;

    // Note: in case of some weird type errors or speed issues, try replacing those with *_fast_* versions
    // See: https://en.cppreference.com/w/cpp/header/cstdint for reference
    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;

    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;
    /*********************************************************************/

    /***********************POINTERS DEFINITIONS**************************/
    template<typename T>
    using Unique = std::unique_ptr<T>;

    template<typename T, typename... Args>
    [[nodiscard]] constexpr Unique<T> CreateUnique(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T, typename... Args>
    [[nodiscard]] constexpr Shared<T> CreateShared(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Weak = std::weak_ptr<T>;
    /***********************************************************************/

    /*******************************OTHERS**********************************/
    using Id = XXH64_hash_t;
    static constexpr Id ID_EMPTY = 0;

    using TimestampDuration = std::chrono::nanoseconds;
    using Timestamp = TimestampDuration::rep;
    /***********************************************************************/
} // namespace CT_COMMON_NAMESPACE
