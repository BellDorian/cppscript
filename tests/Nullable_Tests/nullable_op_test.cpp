#include <gtest/gtest.h>
#include <cpps/Nullable.h>

using namespace cpps;

TEST(NullableTest, copyAssignment) {
	Nullable<int> left(42);
	Nullable<int> right;

	right = left;

	int right_value = -1;
	right.Resolve(right_value);

	EXPECT_FALSE(left.IsNull());
	EXPECT_EQ(right_value, 42);

	// Original should be unchanged
	int left_value = -1;
	left.Resolve(left_value);
	EXPECT_EQ(left_value, 42);
}

TEST(NullableTest, moveAssignment) {
	Nullable<int> older(77);
	Nullable<int> newer;

	newer = std::move(older);

	int value = -1;
	newer.Resolve(value);

	EXPECT_EQ(value, 77);

	// Older object is now null
	EXPECT_TRUE(older.IsNull());
}