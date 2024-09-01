#include "tests_header.h"

TEST(TestSet, Constructor1) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Constructor2) {
  s21::Set<int> s1;
  std::set<int> s2;
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestSet, Constructor3) {
  s21::Set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  auto s11 = std::move(s1);
  auto s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
}

TEST(TestSet, Constructor4) {
  s21::Set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  auto s11 = s1;
  auto s22 = s2;
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
}

TEST(TestSet, Constructor5) {
  s21::Set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  s21::Set<int> s11;
  std::set<int> s22;
  s11 = std::move(s1);
  s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
}

TEST(TestSet, ConstructorsList1) {
  std::initializer_list<int> items{2, 1, 3, 4};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, ConstructorsList2) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::Set<int> my_set2(items);
  std::set<int> std_set2(items);
  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();
  while (my_iter != my_set2.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, ConstructorsList_str) {
  std::initializer_list<const char*> items{"ab", "cd", "ef"};
  s21::Set<const char*> my_set2(items);
  std::set<const char*> std_set2(items);
  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();
  while (my_iter != my_set2.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, ConstructorsCopy) {
  std::initializer_list<int> items{2, 1, 3, 4};
  s21::Set<int> my_set2(items);
  std::set<int> std_set2(items);

  s21::Set<int> my_set3(my_set2);
  std::set<int> std_set3(std_set2);
  auto my_iter = my_set3.begin();
  auto std_iter = std_set3.begin();
  while (my_iter != my_set3.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
}

TEST(TestSet, ConstructorsCopy_str) {
  std::initializer_list<const char*> items{"ab", "cd", "ef"};
  s21::Set<const char*> my_set2(items);
  std::set<const char*> std_set2(items);

  s21::Set<const char*> my_set3(my_set2);
  std::set<const char*> std_set3(std_set2);
  auto my_iter = my_set3.begin();
  auto std_iter = std_set3.begin();
  while (my_iter != my_set3.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, ConstructorsMove1) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  s21::Set<int> my_set2(std::move(my_set));
  std::set<int> std_set2(std::move(std_set));

  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();

  while (my_iter != my_set2.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, ConstructorsMove2) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  s21::Set<int> my_set2 = my_set;
  std::set<int> std_set2 = std_set;

  auto my_iter = my_set2.begin();
  auto std_iter = std_set2.begin();
  while (my_iter != my_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, AssignmentOperators) {
  s21::Set<int> A = {1, 2, 3, 4};
  s21::Set<int> B = A;

  auto a = A.begin();
  auto b = B.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*a, *b);
    a++;
    b++;
  }
  b = B.begin();
  s21::Set<int> C = std::move(A);
  auto c = C.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*c, *b);
    c++;
    b++;
  }
}

TEST(TestSet, AssignmentOperatorsConst) {
  const s21::Set<int> A = {1, 2, 3, 4};
  const s21::Set<int> B = A;
  auto a = A.begin();
  auto b = B.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*a, *b);
    a++;
    b++;
  }
  b = B.begin();
  const s21::Set<int> C = std::move(A);
  auto c = C.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*c, *b);
    c++;
    b++;
  }
}

TEST(TestSet, Iterator1) {
  std::initializer_list<int> items{1, 2, 3};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Iterator2) {
  std::initializer_list<int> items{2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Iterator3) {
  std::initializer_list<int> items{1, 2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Iterator4) {
  std::initializer_list<int> items{2, 1};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Iterator5) {
  std::initializer_list<int> items{2, 1, 3, 34, 234, 231};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestSet, Iterator6) {
  std::initializer_list<int> items{2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestSet, Iterator7) {
  std::initializer_list<int> items{1, 2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestSet, Iterator8) {
  std::initializer_list<int> items{2, 1};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);

  auto my_iter = my_set.end();
  auto std_iter = std_set.end();

  while (my_iter != my_set.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestSet, Iterator9) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (int i = 0; i < 4; i++) it1++, it2++;
  ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Iterator10) {
  s21::Set<int> a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
                  -10, 45, 34, 76};
  std::set<int> std_a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
                      -10, 45, 34, 76};
  auto it = a.begin();
  auto std_it = std_a.begin();
  ASSERT_EQ(*it, *std_it);
}

TEST(TestSet, Iterator11) {
  s21::Set<int> a;
  auto it = a.begin();
  if (it == a.end()) {
    ASSERT_EQ(1, 1);
  } else {
    ASSERT_EQ(0, 1);
  }
}

TEST(TestSet, Iterator12) {
  s21::Set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Insert1) {
  // std::initializer_list<int> items{1,5,3,2,};
  s21::Set<int> my_set;
  std::set<int> std_set;
  my_set.insert(1);
  std_set.insert(1);
  my_set.insert(-1);
  std_set.insert(-1);
  my_set.insert(45);
  std_set.insert(45);
  my_set.insert(-24);
  std_set.insert(-24);
  my_set.insert(-24);
  std_set.insert(-24);
  my_set.insert(-24);
  std_set.insert(-24);
  my_set.insert(24);
  std_set.insert(24);
  my_set.insert(-24000);
  std_set.insert(-24000);
  my_set.insert(-2400);
  std_set.insert(-2400);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Insert2) {
  s21::Set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.insert(3).second, s2.insert(3).second);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(*(s1.insert(3).first), *(s2.insert(3).first));
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestSet, Insert3) {
  s21::Set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.insert(9).second, s2.insert(9).second);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(*(s1.insert(9).first), *(s2.insert(9).first));
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestSet, Erase1) {
  std::initializer_list<int> items{1, 5, 3, 2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();  // 1

  ++std_iter;  // 2
  ++my_iter;

  ++std_iter;  // 3
  ++my_iter;

  std_set.erase(std_iter);  // 1.2.5
  my_set.erase(my_iter);

  my_iter = my_set.begin();
  std_iter = std_set.begin();

  while (std_iter != std_set.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Erase2) {
  std::initializer_list<int> items{1, 5, 3, 4};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Erase3) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Erase4) {
  std::initializer_list<int> items{1, 5, 7, 8};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Erase5) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Erase6) {
  std::initializer_list<int> items{5, 1, 7, 6};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  std_set.erase(std_iter);
  my_set.erase(my_iter);
  my_iter = my_set.begin();
  std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Erase8) {
  s21::Set<int> A = {1, 2, 3, 4, 5};

  auto it = A.begin();
  it++;
  A.erase(++it);

  ASSERT_FALSE(A.contains(3));
}

TEST(TestSet, Erase9) {
  s21::Set<int> A = {1, 2, 3, 4, 5};

  auto it = A.begin();
  it++;
  it++;
  A.erase(++it);

  ASSERT_FALSE(A.contains(4));
}

TEST(TestSet, Erase10) {
  s21::Set<int> A = {1, 2, 3, 4, 5, 20, 40, 50, 1000, 11123, 123, 12355, 11111};

  auto it = A.begin();

  A.erase(it);

  ASSERT_FALSE(A.contains(1));
}

TEST(TestSet, Erase11) {
  s21::Set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
  s1.erase(s1.begin());
  s2.erase(s2.begin());
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestSet, Erase12) {
  s21::Set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.erase(s1.begin());
  s2.erase(s2.begin());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Erase13) {
  s21::Set<int> a{2, 3, 4, 5, 6, 7};
  auto it = a.begin();
  ++it;
  a.erase(it);
  ASSERT_EQ(a.size(), 5);
}

TEST(TestSet, Erase14) {
  s21::Set<int> a{-2, -3, -4, -5, -6, -7};
  auto it = a.begin();
  ++it;
  a.erase(it);
  ASSERT_EQ(a.size(), 5);
}

TEST(TestSet, Clear1) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  my_set.clear();
  std_set.clear();
  ASSERT_TRUE(my_set.size() == 0);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Clear2) {
  s21::Set<int> my_set;
  std::set<int> std_set;
  my_set.clear();
  std_set.clear();
  ASSERT_TRUE(my_set.size() == 0);

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Clear3) {
  s21::Set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestSet, Clear4) {
  s21::Set<double> s1;
  std::set<double> s2;
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestSet, Clear5) {
  s21::Set<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestSet, Clear6) {
  s21::Set<int> a{0, 2, -2, 3, -3, 4, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  a.clear();
  std_a.clear();
  ASSERT_EQ(a.size(), std_a.size());
}

TEST(TestSet, Swap1) {
  std::initializer_list<int> items{1, 5, 7, 6};
  std::initializer_list<int> items2{17, 25, 57, 66, 34, 12, 5};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  s21::Set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.swap(my_set2);
  std_set.swap(std_set2);

  // std::cout << my_set.size() << " std: " << std_set.size() << std::endl;
  // std::cout << my_set2.size() << " std: " << std_set2.size() << std::endl;
  ASSERT_TRUE(my_set.size() == std_set.size());
  ASSERT_TRUE(my_set2.size() == std_set2.size());

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  auto my_iter2 = my_set2.begin();
  auto std_iter2 = std_set2.begin();
  while (std_iter2 != std_set2.end()) {
    ASSERT_TRUE(*my_iter2 == *std_iter2);
    ++my_iter2;
    ++std_iter2;
  }
}

TEST(TestSet, Swap2) {
  s21::Set<int> A = {1, 2, 3, 4};
  s21::Set<int> B = {5, 6, 7, 8};
  A.swap(B);
  int e = 5;
  for (auto i : A) {
    ASSERT_EQ(e, i);
    e++;
  }
  e = 1;
  for (auto i : B) {
    ASSERT_EQ(e, i);
    e++;
  }
}

TEST(TestSet, Swap3) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::Set<int> s11;
  std::set<int> s22;
  s1.swap(s11);
  s2.swap(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Swap4) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::Set<int> s11 = {389, 3829, 111, 189, 11};
  std::set<int> s22 = {389, 3829, 111, 189, 11};
  s1.swap(s11);
  s2.swap(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Swap5) {
  s21::Set<int> s1;
  std::set<int> s2;
  s21::Set<int> s11;
  std::set<int> s22;
  s1.swap(s11);
  s2.swap(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Find1) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.find(66);
  auto std_iter = std_set.find(66);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(17);
  std_iter = std_set.find(17);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(25);
  std_iter = std_set.find(25);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(57);
  std_iter = std_set.find(57);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_set.find(34);
  std_iter = std_set.find(34);
  ASSERT_TRUE(*my_iter == *std_iter);
}

TEST(TestSet, Find2) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  auto my_iter = my_set.find(666);
  auto std_iter = std_set.find(666);
  ASSERT_TRUE(my_iter == my_set.end());
  ASSERT_TRUE(std_iter == std_set.end());
}

TEST(TestSet, Find3) {
  const s21::Set<int> A = {1, 2, 3, 3, 3, 3, 3, 3, 3, 3,
                           3, 3, 3, 4, 5, 6, 7, 8, 9, 10};
  auto i = A.find(6);
  ASSERT_EQ(*i, 6);
}

TEST(TestSet, Find4) {
  s21::Set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  auto it = a.find(5);
  auto std_it = std_a.find(5);
  ASSERT_EQ(*it, *std_it);
}

TEST(TestSet, Find5) {
  s21::Set<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::set<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  auto it = a.find(500);
  auto std_it = std_a.find(500);
  if (it == a.end() && std_it == std_a.end())
    ASSERT_EQ(1, 1);
  else
    ASSERT_EQ(1, 0);
}

TEST(TestSet, Contains1) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  bool my_cont = my_set.contains(17);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(18);
  ASSERT_TRUE(my_cont == false);
  my_cont = my_set.contains(25);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(57);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(5);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_set.contains(13457);
  ASSERT_TRUE(my_cont == false);
  my_cont = my_set.contains(0);
  ASSERT_TRUE(my_cont == false);
}

TEST(TestSet, Contains2) {
  std::string a = "asd";
  std::string b = "asdf";
  std::string c = "asdf";
  s21::Set<std::string> s1 = {a, b};
  ASSERT_EQ(s1.contains(c), true);
}

TEST(TestSet, Contains3) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.contains(0), false);
}

TEST(TestSet, Contains4) {
  s21::Set<int> a{0, 2, -2, 3, -3, 4, -4};
  ASSERT_EQ(a.contains(500), false);
}

TEST(TestSet, Contains5) {
  s21::Set<int> a;
  ASSERT_EQ(a.contains(500), false);
}

TEST(TestSet, Contains6) {
  s21::Set<double> a{2.34534534};
  ASSERT_EQ(a.contains(2.34534538), false);
}

TEST(TestSet, Merge1) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{4, 5, 6, 2};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  s21::Set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_EQ(*my_iter, *std_iter);
    ++my_iter;
    ++std_iter;
  }
  my_iter = my_set2.begin();
  std_iter = std_set2.begin();
  while (std_iter != std_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Merge2) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{1, 2, 3};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  s21::Set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Merge3) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{2, 3, 543};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  s21::Set<int> my_set2(items2);
  std::set<int> std_set2(items2);
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Merge4) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{44, 5, 6};
  s21::Set<int> my_set(items);
  std::set<int> std_set(items);
  s21::Set<int> my_set2(items2);
  std::set<int> std_set2(items2);

  // auto itt = std_set2.begin();
  // while (itt != std_set2.end()) {
  //   std::cout << *itt << std::endl;
  //   ++itt;
  // }

  my_set.merge(my_set2);
  std_set.merge(std_set2);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    // std::cout << *my_iter << " std: " << *std_iter << std::endl;
    ASSERT_EQ(*my_iter, *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestSet, Merge5) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::Set<int> s11 = {389, 3829, 111, 189, 11};
  std::set<int> s22 = {389, 3829, 111, 189, 11};
  s1.merge(s11);
  s2.merge(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Merge6) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::Set<int> s11 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s22 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.merge(s11);
  s2.merge(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Merge7) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::Set<int> s11 = {1, 2, 3, 4, 5, 6, 7, 8, 389, 3829, 111, 189, 11};
  std::set<int> s22 = {1, 2, 3, 4, 5, 6, 7, 8, 389, 3829, 111, 189, 11};
  s1.merge(s11);
  s2.merge(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestSet, Capacity1) {
  s21::Set<int> A;
  ASSERT_EQ(A.size(), 0);
  ASSERT_EQ(A.empty(), true);
}

TEST(TestSet, Capacity2) {
  s21::Set<int> A = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(A.size(), 8);
  ASSERT_EQ(A.empty(), false);
}

TEST(TestSet, Capacity3) {
  s21::Set<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(A.size(), 10);
  ASSERT_EQ(A.empty(), false);
}

TEST(TestSet, Empty1) {
  s21::Set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestSet, Empty2) {
  s21::Set<int> s1 = {1, 2, 3};
  std::set<int> s2 = {1, 2, 3};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestSet, Empty3) {
  s21::Set<int> a;
  std::set<int> std_a;
  ASSERT_EQ(a.empty(), std_a.empty());
}

TEST(TestSet, Empty4) {
  s21::Set<int> a{1};
  std::set<int> std_a{1};
  ASSERT_EQ(a.empty(), std_a.empty());
}

TEST(TestSet, Size1) {
  s21::Set<int> s1;
  std::set<int> s2;
  s1.insert(1);
  s2.insert(1);
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestSet, Size2) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestSet, Size3) {
  s21::Set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestSet, Size4) {
  s21::Set<int> a;
  std::set<int> std_a;
  ASSERT_EQ(a.size(), std_a.size());
}

TEST(TestSet, Max_size) {
  s21::Set<int> a;
  std::set<int> std_a;
  std::cout << "max size s21::Set - " << a.max_size()
            << "\nmax_size std::set - " << std_a.max_size() << std::endl;
}

TEST(TestSet, InsertMany1) {
  Set<int> A = {1, 2, 3, 4, 5};
  std::set<int> B = {1, 2, 3, 4, 5};
  A.insert_many(6, 7, 8);
  B.insert(6);
  B.insert(7);
  B.insert(8);

  auto j = B.begin();
  for (auto i : A) {
    ASSERT_EQ((*j), i);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}

TEST(TestSet, InsertMany2) {
  Set<int> A = {1, 2, 3, 4, 5, 6};
  std::set<int> B = {1, 2, 3, 4, 5, 6};
  A.insert_many(6, 7, 8);
  B.insert(6);
  B.insert(7);
  B.insert(8);

  auto j = B.begin();
  for (auto i : A) {
    ASSERT_EQ((*j), i);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}

TEST(TestSet, InsertMany3) {
  Set<int> A = {1, 2, 3, 4, 5};
  std::set<int> B = {1, 2, 3, 4, 5};
  A.insert_many(6, 7, 8, 6);
  B.insert(6);
  B.insert(7);
  B.insert(8);
  B.insert(6);
  auto j = B.begin();
  for (auto i : A) {
    ASSERT_EQ((*j), i);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}
