#include <gtest/gtest.h>

#include <iostream>

#include <util/sum_queue/sum_queue.h>


TEST(SumQueue, TestAll) {
    TSumQueue<int> q;
    q.Push(1); // 1 = 1
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 1);
    EXPECT_EQ(q(), 1);
    q.Push(2); // 1 + 2 = 3
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 2);
    EXPECT_EQ(q(), 3);
    q.Push(3); // 1 + 2 + 3 = 6
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 3);
    EXPECT_EQ(q(), 6);
    q.Push(4); // 1 + 2 + 3 + 4 = 10
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 4);
    EXPECT_EQ(q(), 10);
    q.Push(5); // 1 + 2 + 3 + 4 + 5 = 15
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 5);
    EXPECT_EQ(q(), 15);
    EXPECT_EQ(q.Pop(), 1); // 2 + 3 + 4 + 5 = 14
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 4);
    EXPECT_EQ(q(), 14);
    q.Push(6); // 2 + 3 + 4 + 5 + 6 = 20
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 5);
    EXPECT_EQ(q(), 20);
    EXPECT_EQ(q.Pop(), 2); // 3 + 4 + 5 + 6 = 18
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 4);
    EXPECT_EQ(q(), 18);
    EXPECT_EQ(q.Pop(), 3); // 4 + 5 + 6 = 15
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 3);
    EXPECT_EQ(q(), 15);
    EXPECT_EQ(q.Pop(), 4); // 5 + 6 = 11
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 2);
    EXPECT_EQ(q(), 11);
    EXPECT_EQ(q.Pop(), 5); // 6 = 6
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 1);
    EXPECT_EQ(q(), 6);
    q.Clear();
    std::cerr << q << std::endl;
    EXPECT_EQ(q.Size(), 0);
    EXPECT_EQ(q(), 0);
}
