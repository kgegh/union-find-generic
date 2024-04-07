#include <gtest/gtest.h>

#include "union_find.h"


TEST(union_find_test, basic) {
    // {1,2,3} {4,5} {6}
    union_find<int> uf;
    
    for (int i = 1; i <= 6; i++) uf.make_set(i);
    uf.merge(1,2);
    uf.merge(2,3);
    uf.merge(4,5);

    ASSERT_EQ(uf.size(1), 3);
    ASSERT_EQ(uf.size(2), 3);
    ASSERT_EQ(uf.size(3), 3);
    ASSERT_EQ(uf.size(4), 2);
    ASSERT_EQ(uf.size(5), 2);
    ASSERT_EQ(uf.size(6), 1);
    ASSERT_TRUE(uf.same(1,2));
    ASSERT_TRUE(uf.same(2,3));
    ASSERT_FALSE(uf.same(3,6));
}

TEST(union_find_test, strings) {
    // {"aaa", "aa", "a"}, {"b"}
    union_find<std::string> uf;

    uf.make_set("aaa");
    uf.make_set("aa");
    uf.make_set("a");
    uf.make_set("b");
    uf.merge("a","aa");
    uf.merge("aa","aaa");

    ASSERT_EQ(uf.size("aa"), 3);
    ASSERT_TRUE(uf.same("a","aaa"));
    ASSERT_FALSE(uf.same("a","b"));
}

TEST(union_find_test, missing_value) {
    // {1,2}
    union_find<int> uf;

    uf.make_set(1);
    uf.make_set(2);
    uf.merge(1,2);

    ASSERT_EQ(uf.find(3), -1);
    ASSERT_FALSE(uf.same(1,3));
    
    uf.merge(1,3);

    ASSERT_FALSE(uf.same(1,3));
    ASSERT_EQ(uf.size(1), 2);
    ASSERT_EQ(uf.size(3), 0);
}

TEST(union_find_test, grow_internal_vectors) {
    // internal vectors can grow properly
    // {1 ... 10}
    union_find<int> uf(5);

    for (int i = 1; i <= 10; i++) uf.make_set(i);
    ASSERT_EQ(uf.find(10), 9);
}
