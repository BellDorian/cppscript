#include <gtest/gtest.h>
#include <cpps/Nullable.h>

using namespace cpps;

TEST(NullableTest, CheckIsNull) {
	Nullable<int> obj(25);
	Nullable<int> null_obj;

	EXPECT_FALSE(obj.IsNull());
	EXPECT_TRUE(null_obj.IsNull());
}

TEST(NullableTest, resolve) {
	Nullable<int> empty;
	Nullable<int> full(23);

	int empty_value = -1;
	int full_value = -1;

	bool changed_empty = empty.Resolve(empty_value);
	bool changed_full = full.Resolve(full_value);

	// Null Nullable objects do not mutate the destination param of Resolve
	EXPECT_FALSE(changed_empty);
	EXPECT_EQ(empty_value, -1);
	EXPECT_TRUE(changed_full);
	EXPECT_EQ(full_value, 23);
}

// need to write a moveresolve test.