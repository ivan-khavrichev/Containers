#include "tests_header.h"

TEST(TestArray, DefaultConstructor) {
  s21::array<int, 5> arr;
  // Check that the size is correct
  ASSERT_EQ(arr.size(), 5);

  // Check that all elements are initialized to their default value (0 for int)
  for (size_t i = 0; i < arr.size(); ++i) {
    ASSERT_EQ(arr[i], 0);
  }
}

TEST(TestArray, InitListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  // Check that the size is correct
  ASSERT_EQ(arr.size(), 5);

  // Check that each element is initialized correctly
  for (size_t i = 0; i < arr.size(); ++i) {
    ASSERT_EQ(arr[i], static_cast<int>(i) + 1);
  }
}

TEST(TestArray, CopyConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrCopy(arr);

  // Check that the size is correct
  ASSERT_EQ(arrCopy.size(), 5);

  // Check that the elements are copied correctly
  for (size_t i = 0; i < arr.size(); ++i) {
    ASSERT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(TestArray, MoveConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrMoved(std::move(arr));

  // Check that the size is correct
  ASSERT_EQ(arrMoved.size(), 5);

  // Check that the elements are moved correctly
  for (size_t i = 0; i < arrMoved.size(); ++i) {
    ASSERT_EQ(arrMoved[i], static_cast<int>(i) + 1);
  }
}

TEST(TestArray, Begin) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.begin();
  ASSERT_EQ(*it, 1);
  // Modify the data through the iterator and check if the array is updated
  *it = 10;
  ASSERT_EQ(arr[0], 10);
}

TEST(TestArray, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.end();
  // end() iterator should not be dereferenced; comparing it to another iterator
  // should work
  auto beginIt = arr.begin();
  ASSERT_EQ(it, beginIt + 5);
}

TEST(TestArray, At_ValidIndex) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.at(2);
  ASSERT_EQ(value, 3);
}

TEST(TestArray, At_OutOfBounds) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  // Attempting to access an out-of-bounds index using at() should throw an
  // exception
  ASSERT_THROW(arr.at(10), std::out_of_range);
}

TEST(TestArray, Front) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.front();
  ASSERT_EQ(value, 1);
}

TEST(TestArray, Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.back();
  ASSERT_EQ(value, 5);
}



TEST(TestArray, Empty_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  ASSERT_FALSE(arr.empty());
}

TEST(TestArray, Empty_EmptyArray) {
  s21::array<int, 0> arr;
  ASSERT_TRUE(arr.empty());
}

TEST(TestArray, Size_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  ASSERT_EQ(arr.size(), 5);
}

TEST(TestArray, Size_EmptyArray) {
  s21::array<int, 0> arr;
  ASSERT_EQ(arr.size(), 0);
}

TEST(TestArray, MaxSize) {
  s21::array<int, 5> arr;
  // The max size of an array with a specified size is the same as its declared
  // size
  ASSERT_EQ(arr.max_size(), 5);
}

TEST(TestArray, Swap) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1.swap(arr2);

  // Check that the elements of arr1 are now from arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    ASSERT_EQ(arr1[i], static_cast<int>(i) + 6);
  }

  // Check that the elements of arr2 are now from arr1
  for (size_t i = 0; i < arr2.size(); ++i) {
    ASSERT_EQ(arr2[i], static_cast<int>(i) + 1);
  }
}

TEST(TestArray, Fill) {
  s21::array<int, 5> arr;
  arr.fill(10);

  // Check that all elements are filled with the specified value
  for (size_t i = 0; i < arr.size(); ++i) {
    ASSERT_EQ(arr[i], 10);
  }
}

TEST(TestArray, CopyAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = arr2;

  // Check that arr1 now contains the same elements as arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    ASSERT_EQ(arr1[i], arr2[i]);
  }
}

TEST(TestArray, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = std::move(arr2);

  // Check that arr1 now contains the same elements as arr2
  for (size_t i = 0; i < arr1.size(); ++i) {
    ASSERT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
}

TEST(TestArray, OperatorBracket) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  // Check that elements can be accessed using the [] operator
  for (size_t i = 0; i < arr.size(); ++i) {
    ASSERT_EQ(arr[i], static_cast<int>(i) + 1);
  }

  // Modify an element using the [] operator and check if the array is updated
  arr[2] = 10;
  ASSERT_EQ(arr[2], 10);
}