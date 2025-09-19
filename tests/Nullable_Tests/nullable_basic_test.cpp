#include <gtest/gtest.h>
#include <cpps/Nullable.h>

using namespace cpps;


TEST(NullableTest, default_construct) {
	Nullable<char> obj;

	EXPECT_TRUE(obj.IsNull());
}

TEST(NullableTest, init_construct) {
	Nullable<int> obj(25);

	EXPECT_FALSE(obj.IsNull());
}

TEST(NullableTest, copy_construct) {
	Nullable<int> first(55);
	Nullable<int> second(first);
	int value = -1;

	// When Resolve cannot resolve to a concrete type, it does nothing
	// Therefore, if the construction failed, value stays -1;
	second.Resolve(value);
	EXPECT_FALSE(second.IsNull());
	EXPECT_EQ(value, 55);
}

TEST(NullableTest, move_construct)
{
	// This is basically the same test concept as the copy constructor test.
	// But it's a more low-level apporach, since this method moves a raw buffer

	alignas(Nullable<int>) unsigned char storage[sizeof(Nullable<int>)];
	Nullable<int>* obj = new(storage) Nullable<int>(42);

	alignas(Nullable<int>) unsigned char storage2[sizeof(Nullable<int>)];
	Nullable<int>* movedTo = new(storage2) Nullable<int>(std::move(*obj));

	int value = -1;
	movedTo->Resolve(value);

	// Verify memory is valid and object behaves correctly
	EXPECT_FALSE(movedTo->IsNull());
	EXPECT_EQ(value, 42);

	// Cleanup
	obj->~Nullable();
	movedTo->~Nullable();
}

TEST(NullableTest, value_move_construct)
{
	std::string source = "Hello";
	Nullable<std::string> movedIn(std::move(source));
	std::string value = "";
	movedIn.Resolve(value);

	EXPECT_FALSE(movedIn.IsNull());
	EXPECT_EQ(value, "Hello");

	// This is a move -- not a copy.
	EXPECT_TRUE(source.empty());
}