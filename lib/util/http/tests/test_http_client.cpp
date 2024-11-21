#include <gtest/gtest.h>

#include "util/http/client.h"


TEST(HttpClientTest, TestGet) {
    THttpClient client("https://jsonplaceholder.typicode.com");

    Json::Value response = client.Get("/posts");
    ASSERT_TRUE(response.isArray());
    ASSERT_FALSE(response.empty());
    std::cerr << response.toStyledString() << std::endl;

    if (!response.empty()) {
        const auto& firstPost = response[0];
        ASSERT_TRUE(firstPost.isObject());
        EXPECT_TRUE(firstPost.isMember("userId"));
        EXPECT_TRUE(firstPost.isMember("id"));
        EXPECT_TRUE(firstPost.isMember("title"));
        EXPECT_TRUE(firstPost.isMember("body"));
    }
}
