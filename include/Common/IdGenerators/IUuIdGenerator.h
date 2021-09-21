#pragma once
#include "Common/Types.h"
#include "Common/Helpers.h"

namespace CT_COMMON_NAMESPACE
{
    class IUuIdGenerator
    {
    public:
        CT_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(IUuIdGenerator);
        IUuIdGenerator() = default;
        virtual ~IUuIdGenerator() = default;

        /**
         * Generates universally unique identifier.
         * 
         * @return New, unique Id
         */
        virtual Id Generate() const = 0;
    };
} // namespace CT_COMMON_NAMESPACE
