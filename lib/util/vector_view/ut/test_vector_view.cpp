#include <gtest/gtest.h>

#include <util/vector_view/vector_view.h>


const std::vector<int> v = {1, 2, 3, 4, 5};


TEST(VectorView, TestSimple) {
    TVectorView<int> view(v);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(view[i], v[i]);
    }
    EXPECT_EQ(view.Size(), v.size());
}
