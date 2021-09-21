#pragma once
#include "Common/IdGenerators/IUuIdGenerator.h"

namespace CT_COMMON_NAMESPACE
{
    class UuId4Generator final : public IUuIdGenerator
    {
    public:
        [[nodiscard]] Id Generate() const override;
    };
} // namespace CT_COMMON_NAMESPACE
