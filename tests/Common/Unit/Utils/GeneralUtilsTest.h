#pragma once
#include <Common/Types.h>
#include <gtest/gtest.h>

namespace CT_COMMON_NAMESPACE::tests::unit
{
    class ForEachTest : public testing::Test
    {
    };

    class FindTest : public testing::Test
    {
    protected:
        struct TestStruct
        {
            Id id;
        };
    };

    class RemoveAtTest : public testing::Test
    {
    };
} // namespace sce::tests::unit
