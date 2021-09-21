#pragma once
#include <Common/Exceptions.h>
#include <fmt/format.h>
#include <type_traits>

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Checks correctness of the given pointer.
     * Throws exception if pointer is equal to nullptr.
     * 
     * @param pointer
     * @return 
     */
    template<typename PtrType>
    inline constexpr auto ValidatePointer(PtrType&& pointer)
    {
        if (pointer == nullptr)
        {
            SCE_THROW(fmt::format("Given pointer is null! Pointer type is: '{}'", typeid(PtrType).name()));
        }
    }
} // namespace CT_COMMON_NAMESPACE
