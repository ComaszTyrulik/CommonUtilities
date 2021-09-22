#include "GeneralUtilsTest.h"

#include <Common/Utils/GeneralUtils.h>

namespace CT_COMMON_NAMESPACE::tests::unit
{
    TEST_F(ForEachTest, WillExecuteGivenFunctionForEveryElementOfTheGivenContainer)
    {
        int counter = 0;
        const auto function = [&](auto&& element) { counter++; };

        std::vector<int> container{1, 2, 3, 4, 5};
        ForEach(container, function);

        ASSERT_EQ(container.size(), counter);
    }

    TEST_F(ForEachTest, WillExecuteGivenFunctionForEveryElementFromTheGivenRange)
    {
        std::size_t counter = 0;
        const auto function = [&](auto&& element) { counter++; };

        std::size_t expectedCount = 5;
        std::vector<int> container{1, 2, 3, 4, 5};
        
        ForEach(container.data(), expectedCount, function);
        ASSERT_EQ(expectedCount, counter);
    }

    TEST_F(FindTest, FindIndexWillReturnEmptyObjectIfNoElementMatchingGivenPredicateFound)
    {
        const Id idToFind = 0;
        std::vector<TestStruct> container(2);
        container[0].id = 1;
        container[1].id = 2;
        
        const auto predicate = [&](const TestStruct& element) { return element.id == idToFind; };
        auto result = FindIndex(container, predicate);
        ASSERT_FALSE(result.has_value());
    }

    TEST_F(FindTest, FindIndexWillReturnCorrectIndexOfTheObjectIfElementMatchingGivenPredicateFound)
    {
        const std::size_t expectedIndex = 0;

        const Id idToFind = 1;
        std::vector<TestStruct> container(2);
        container[0].id = idToFind;
        container[1].id = 2;

        const auto predicate = [&](const TestStruct& element) { return element.id == idToFind; };
        auto result = FindIndex(container, predicate);
        ASSERT_EQ(expectedIndex, result);
    }

    TEST_F(RemoveAtTest, WillRemoveElementAtGivenIndexFromGivenVector)
    {
        std::size_t indexToRemove = 2;
        std::vector<int> vector = {1, 2, 3, 4};
        std::vector<int> expectedVectorAfter = {1, 2, 4};

        RemoveAt(vector, indexToRemove);
        ASSERT_EQ(expectedVectorAfter, vector);
    }

    TEST_F(RemoveAtTest, WillThrowExceptionIfGivenIndexIsTooBig)
    {
        std::size_t indexToRemove = 10;
        std::vector<int> vector = {1, 2, 3, 4};

        ASSERT_THROW(RemoveAt(vector, indexToRemove), std::runtime_error);
    }

    TEST_F(RemoveAtTest, WillThrowExceptionIfGivenIndexIsTooSmall)
    {
        std::size_t indexToRemove = -1;
        std::vector<int> vector = {1, 2, 3, 4};

        ASSERT_THROW(RemoveAt(vector, indexToRemove), std::runtime_error);
    }
} // namespace sce::tests::unit
