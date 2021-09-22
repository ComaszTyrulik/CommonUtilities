#pragma once
#include "Common/Types.h"
#include "Common/Helpers.h"

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Interface providing generation of the universally unique identifiers (UUIDs) in the form of an integer.
     */
    class IUuIdGenerator
    {
    public:
        CT_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(IUuIdGenerator);
        IUuIdGenerator() = default;
        virtual ~IUuIdGenerator() = default;

        /**
         * @brief Generates universally unique identifier.
         * 
         * @return New, unique Id
         */
        [[nodiscard]] virtual Id Generate() const = 0;
    };
} // namespace CT_COMMON_NAMESPACE
