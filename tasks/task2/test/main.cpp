#include "task2/list.hpp"

#include <gtest/gtest.h>

class EnsureDeletion {
public:
    ~EnsureDeletion() { *deleted_ = true; }

    std::shared_ptr<std::atomic<bool>> deleted() const {
        return deleted_;
    }

private:
    std::shared_ptr<std::atomic<bool>> deleted_{std::make_shared<std::atomic<bool>>(false)};
};

TEST(List, one) {
    task2::List<EnsureDeletion> list;
    EnsureDeletion ensure_deletion;
    list.insert(list.begin(), ensure_deletion);
    EXPECT_EQ(list.begin()->deleted(), ensure_deletion.deleted());
    EXPECT_EQ(std::distance(list.begin(), list.end()), 1ul);
    list.remove(list.begin());
    EXPECT_TRUE(*ensure_deletion.deleted());
    EXPECT_EQ(list.begin(), list.end());
}

TEST(List, many) {
    std::vector<std::shared_ptr<std::atomic<bool>>> deleted;
    task2::List<EnsureDeletion> list;
    for (size_t i = 0; i != 10; ++i) {
        EnsureDeletion ensure_deletion;
        deleted.push_back(ensure_deletion.deleted());
        list.insert(list.end(), ensure_deletion);
    }
    {
        auto it = list.begin();
        for (const auto& item : deleted) {
            EXPECT_EQ((it++)->deleted(), item);
        }
    }
    for (size_t i = 0; i != 10; ++i) {
        auto it = list.begin();
        std::advance(it, (10 - i) / 2);
        list.remove(it);
    }
    EXPECT_TRUE(std::all_of(deleted.begin(), deleted.end(), [](const auto& item) -> bool { return *item; }));
}

TEST(List, sort) {
    task2::List<int> list;
    for (int i : {3, 4, 1, -1, 3, 5, -6, 3, -4, 5}) {
        list.insert(list.end(), i);
    }
    list.sort(std::less<int>{});
    EXPECT_TRUE(std::is_sorted(list.begin(), list.end()));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
