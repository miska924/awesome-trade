#include <gtest/gtest.h>

#include <strategy/params/params.h>


TEST(Params, TestLinearRangeInt) {
    {
        TLinearRange<int> range(-1, 10, 2);

        std::vector<int> got;
        int current = range.min;
        while (range.Contains(current)) {
            got.push_back(current);
            current = range.Next(current);
        }

        const std::vector<int> expected = {-1, 1, 3, 5, 7, 9};
        ASSERT_EQ(got, expected);
    }
}

TEST(Params, TestLinearRangeDouble) {
    {
        TLinearRange<double> range(-3, 2, 0.5);

        std::vector<double> got;
        double current = range.min;
        while (range.Contains(current)) {
            got.push_back(current);
            current = range.Next(current);
        }

        const std::vector<double> expected = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2};
        ASSERT_EQ(got, expected);
    }
}

TEST(Params, TestLogRangeInt) {
    {
        TLogRange<int> range(1, 100, 2);

        std::vector<int> got;
        int current = range.min;
        while (range.Contains(current)) {
            got.push_back(current);
            current = range.Next(current);
        }

        const std::vector<int> expected = {1, 2, 4, 8, 16, 32, 64};
        ASSERT_EQ(got, expected);
    }
}

TEST(Params, TestLogRangeDouble) {
    {
        TLogRange<double> range(0.5, 100, 2);

        std::vector<double> got;
        double current = range.min;
        while (range.Contains(current)) {
            got.push_back(current);
            current = range.Next(current);
        }

        const std::vector<double> expected = {0.5, 1, 2, 4, 8, 16, 32, 64};
        ASSERT_EQ(got, expected);
    }
}

TEST(Params, TestParams) {
    TParams params({
        {"a", 1},
        {"b", 0.9},
        {"c", TLinearRange<int>(-1, 1, 2)},
        {"d", TLinearRange<double>(-1, 1, 0.5)},
        {"e", TLogRange<int>(1, 100, 2)},
        {"f", TLogRange<double>(0.5, 100, 2)},
        // {"g", TParams({{"h", 2}, {"i", 3}}) + TParams({{"j", 4}, {"k", 5}})},
    });
    
}
