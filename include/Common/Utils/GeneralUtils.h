#pragma once
#include "Common/Types.h"
#include "Common/Exceptions.h"

#include <optional>

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Executes given function for every element of the given container.
     * Container must support standard begin() and end() methods to be able to iterate over its elements via iterators.
     * 
     * @param container
     * @param function
     */
    template<typename ContainerType, typename Function>
    inline void ForEach(ContainerType&& container, Function&& function)
    {
        std::for_each(container.begin(), container.end(), std::forward<decltype(function)>(function));
    }

    /**
     * @brief Executes given function for every element of the given array.
     * Elements are taken from the range <beginning, beginning + count).
     * This method should be used for C-style arrays and may lead to undefined behaviors if used with incorrect count.
     * USE WITH CAUTION!
     * 
     * @param beginning - Pointer to the first element of the array
     * @param count - Number of elements to iterate over
     * @param function - Function executed for each element
     */
    template<typename DataType, typename Function>
    inline void ForEach(DataType* beginning, std::size_t count, Function&& function)
    {
        std::for_each(beginning, beginning + count, std::forward<decltype(function)>(function));
    }

    /**
     * @brief Seeks for the index of the element inside the container.
     * It uses given function as a predicate for finding the desired element.
     * Container must support standard begin() and end() methods to be able to iterate over its elements.
     * Returns optional object which can either contain index of the found element or be empty if element is not found.
     * 
     * @param container
     * @param function
     * @return 
     */
    template<typename ContainerType, typename Function>
    inline std::optional<std::size_t> FindIndex(ContainerType&& container, Function&& function)
    {
        const auto result = std::find_if(container.begin(), container.end(), std::forward<decltype(function)>(function));
        if (result == container.end())
        {
            return {};
        }

        return static_cast<std::size_t>(std::distance(container.begin(), result));
    }

    /**
     * @brief Removes element at given index from the given vec modyfing the vec itself.
     * Throws exception if given index is out of vector's range
     * 
     * @param vec
     * @param index
     */
    template<typename VectorType>
    inline void RemoveAt(std::vector<VectorType>& vec, std::size_t index)
    {
        if (index >= vec.size())
        {
            CT_THROW(fmt::format("Index '{}' is out of given vector's range!", index));
        }

        vec.erase(vec.begin() + index);
    }
} // namespace CT_COMMON_NAMESPACE
