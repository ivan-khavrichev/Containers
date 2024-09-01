#include "tests_header.h"

TEST(TestMultiSet, Constructor1) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Constructor2) {
  s21::MultiSet<int> s1;
  std::multiset<int> s2;
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestMultiSet, Constructor3) {
  s21::MultiSet<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  auto s11 = std::move(s1);
  auto s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
}

TEST(TestMultiSet, Constructor4) {
  s21::MultiSet<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  auto s11 = s1;
  auto s22 = s2;
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
}

TEST(TestMultiSet, Constructor5) {
  s21::MultiSet<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  s21::MultiSet<int> s11;
  std::multiset<int> s22;
  s11 = std::move(s1);
  s22 = std::move(s2);
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
}

TEST(TestMultiSet, ConstructorsList1) {
  std::initializer_list<int> items{2, 1, 3, 4};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (my_iter != my_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, ConstructorsList2) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::MultiSet<int> my_multiset2(items);
  std::multiset<int> std_multiset2(items);
  auto my_iter = my_multiset2.begin();
  auto std_iter = std_multiset2.begin();
  while (my_iter != my_multiset2.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, ConstructorsList_str) {
  std::initializer_list<const char*> items{"ab", "cd", "ef"};
  s21::MultiSet<const char*> my_multiset2(items);
  std::multiset<const char*> std_multiset2(items);
  auto my_iter = my_multiset2.begin();
  auto std_iter = std_multiset2.begin();
  while (my_iter != my_multiset2.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, ConstructorsCopy) {
  std::initializer_list<int> items{2, 1, 3, 4};
  s21::MultiSet<int> my_multiset2(items);
  std::multiset<int> std_multiset2(items);

  s21::MultiSet<int> my_multiset3(my_multiset2);
  std::multiset<int> std_multiset3(std_multiset2);
  auto my_iter = my_multiset3.begin();
  auto std_iter = std_multiset3.begin();
  while (my_iter != my_multiset3.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
}

TEST(TestMultiSet, ConstructorsCopy_str) {
  std::initializer_list<const char*> items{"ab", "cd", "ef"};
  s21::MultiSet<const char*> my_multiset2(items);
  std::multiset<const char*> std_multiset2(items);

  s21::MultiSet<const char*> my_multiset3(my_multiset2);
  std::multiset<const char*> std_multiset3(std_multiset2);
  auto my_iter = my_multiset3.begin();
  auto std_iter = std_multiset3.begin();
  while (my_iter != my_multiset3.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, ConstructorsMove1) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  s21::MultiSet<int> my_multiset2(std::move(my_multiset));
  std::multiset<int> std_multiset2(std::move(std_multiset));

  auto my_iter = my_multiset2.begin();
  auto std_iter = std_multiset2.begin();

  while (my_iter != my_multiset2.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, ConstructorsMove2) {
  std::initializer_list<int> items{2, 1, 2, 2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  s21::MultiSet<int> my_multiset2 = my_multiset;
  std::multiset<int> std_multiset2 = std_multiset;

  auto my_iter = my_multiset2.begin();
  auto std_iter = std_multiset2.begin();
  while (my_iter != my_multiset2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, AssignmentOperators) {
  s21::MultiSet<int> A = {1, 2, 3, 4};
  s21::MultiSet<int> B = A;

  auto a = A.begin();
  auto b = B.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*a, *b);
    a++;
    b++;
  }
  b = B.begin();
  s21::MultiSet<int> C = std::move(A);
  auto c = C.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*c, *b);
    c++;
    b++;
  }
}

TEST(TestMultiSet, AssignmentOperatorsConst) {
  const s21::MultiSet<int> A = {1, 2, 3, 4};
  const s21::MultiSet<int> B = A;
  auto a = A.begin();
  auto b = B.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*a, *b);
    a++;
    b++;
  }
  b = B.begin();
  const s21::MultiSet<int> C = std::move(A);
  auto c = C.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(*c, *b);
    c++;
    b++;
  }
}

TEST(TestMultiSet, Iterator1) {
  std::initializer_list<int> items{1, 2, 3};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (my_iter != my_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Iterator2) {
  std::initializer_list<int> items{2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);

  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();

  while (my_iter != my_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Iterator3) {
  std::initializer_list<int> items{1, 2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);

  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();

  while (my_iter != my_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Iterator4) {
  std::initializer_list<int> items{2, 1};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);

  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();

  while (my_iter != my_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Iterator5) {
  std::initializer_list<int> items{2, 1, 3, 34, 234, 231};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);

  auto my_iter = my_multiset.end();
  auto std_iter = std_multiset.end();

  while (my_iter != my_multiset.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestMultiSet, Iterator6) {
  std::initializer_list<int> items{2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);

  auto my_iter = my_multiset.end();
  auto std_iter = std_multiset.end();

  while (my_iter != my_multiset.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestMultiSet, Iterator7) {
  std::initializer_list<int> items{1, 2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);

  auto my_iter = my_multiset.end();
  auto std_iter = std_multiset.end();

  while (my_iter != my_multiset.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestMultiSet, Iterator8) {
  std::initializer_list<int> items{2, 1};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);

  auto my_iter = my_multiset.end();
  auto std_iter = std_multiset.end();

  while (my_iter != my_multiset.end()) {
    ++my_iter;
    ++std_iter;
    ASSERT_TRUE(*my_iter == *std_iter);
  }
}

TEST(TestMultiSet, Iterator9) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (int i = 0; i < 4; i++) it1++, it2++;
  ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Iterator10) {
  s21::MultiSet<int> a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
                  -10, 45, 34, 76};
  std::multiset<int> std_a{2,   -3, 4,  -1, 5,  -7, 6,    -9,  8,
                      -10, 45, 34, 76};
  auto it = a.begin();
  auto std_it = std_a.begin();
  ASSERT_EQ(*it, *std_it);
}

TEST(TestMultiSet, Iterator11) {
  s21::MultiSet<int> a;
  auto it = a.begin();
  if (it == a.end()) {
    ASSERT_EQ(1, 1);
  } else {
    ASSERT_EQ(0, 1);
  }
}

TEST(TestMultiSet, Iterator12) {
  s21::MultiSet<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Insert1) {
  s21::MultiSet<int> my_multiset;
  std::multiset<int> std_multiset;
  my_multiset.insert(1);
  std_multiset.insert(1);
  my_multiset.insert(-1);
  std_multiset.insert(-1);
  my_multiset.insert(45);
  std_multiset.insert(45);
  my_multiset.insert(-24);
  std_multiset.insert(-24);
  my_multiset.insert(-24);
  std_multiset.insert(-24);
  my_multiset.insert(-24);
  std_multiset.insert(-24);
  my_multiset.insert(24);
  std_multiset.insert(24);
  my_multiset.insert(-24000);
  std_multiset.insert(-24000);
  my_multiset.insert(-2400);
  std_multiset.insert(-2400);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Insert2) {
  s21::MultiSet<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.size(), s2.size());
  auto it = s1.insert(3);
  ASSERT_EQ(*(it), *(s2.insert(3)));
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestMultiSet, Insert3) {
  s21::MultiSet<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(*(s1.insert(9)), *(s2.insert(9)));
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(*(s1.insert(9)), *(s2.insert(9)));
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestMultiSet, Erase1) {
  std::initializer_list<int> items{1, 5, 3, 2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();  // 1

  ++std_iter;  // 2
  ++my_iter;

  ++std_iter;  // 3
  ++my_iter;

  std_multiset.erase(std_iter);  // 1.2.5
  my_multiset.erase(my_iter);

  my_iter = my_multiset.begin();
  std_iter = std_multiset.begin();

  while (std_iter != std_multiset.end()) {
    // std::cout << *my_iter << " - std iter:" << *std_iter << std::endl;
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Erase2) {
  std::initializer_list<int> items{1, 5, 3, 4};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_multiset.erase(std_iter);
  my_multiset.erase(my_iter);
  my_iter = my_multiset.begin();
  std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Erase3) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_multiset.erase(std_iter);
  my_multiset.erase(my_iter);
  my_iter = my_multiset.begin();
  std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Erase4) {
  std::initializer_list<int> items{1, 5, 7, 8};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  ++std_iter;
  ++my_iter;
  ++std_iter;
  ++my_iter;
  std_multiset.erase(std_iter);
  my_multiset.erase(my_iter);
  my_iter = my_multiset.begin();
  std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Erase5) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  std_multiset.erase(std_iter);
  my_multiset.erase(my_iter);
  my_iter = my_multiset.begin();
  std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Erase6) {
  std::initializer_list<int> items{5, 1, 7, 6};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  std_multiset.erase(std_iter);
  my_multiset.erase(my_iter);
  my_iter = my_multiset.begin();
  std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Erase8) {
  s21::MultiSet<int> A = {1, 2, 3, 4, 5};

  auto it = A.begin();
  it++;
  A.erase(++it);

  ASSERT_FALSE(A.contains(3));
}

TEST(TestMultiSet, Erase9) {
  s21::MultiSet<int> A = {1, 2, 3, 4, 5};

  auto it = A.begin();
  it++;
  it++;
  A.erase(++it);

  ASSERT_FALSE(A.contains(4));
}

TEST(TestMultiSet, Erase10) {
  s21::MultiSet<int> A = {1, 2, 3, 4, 5, 20, 40, 50, 1000, 11123, 123, 12355, 11111};

  auto it = A.begin();

  A.erase(it);

  ASSERT_FALSE(A.contains(1));
}

TEST(TestMultiSet, Erase11) {
  s21::MultiSet<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
  s1.erase(s1.begin());
  s2.erase(s2.begin());
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestMultiSet, Erase12) {
  s21::MultiSet<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.erase(s1.begin());
  s2.erase(s2.begin());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Erase13) {
  s21::MultiSet<int> a{2, 3, 4, 5, 6, 7};
  auto it = a.begin();
  ++it;
  a.erase(it);
  ASSERT_EQ(a.size(), 5);
}

TEST(TestMultiSet, Erase14) {
  s21::MultiSet<int> a{-2, -3, -4, -5, -6, -7};
  auto it = a.begin();
  ++it;
  a.erase(it);
  ASSERT_EQ(a.size(), 5);
}

TEST(TestMultiSet, Clear1) {
  std::initializer_list<int> items{1, 5, 7, 6};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  my_multiset.clear();
  std_multiset.clear();
  ASSERT_TRUE(my_multiset.size() == 0);

  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Clear2) {
  s21::MultiSet<int> my_multiset;
  std::multiset<int> std_multiset;
  my_multiset.clear();
  std_multiset.clear();
  ASSERT_TRUE(my_multiset.size() == 0);

  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Clear3) {
  s21::MultiSet<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestMultiSet, Clear4) {
  s21::MultiSet<double> s1;
  std::multiset<double> s2;
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestMultiSet, Clear5) {
  s21::MultiSet<double> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<double> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestMultiSet, Clear6) {
  s21::MultiSet<int> a{0, 2, -2, 3, -3, 4, 6, -6, 7, -7};
  std::multiset<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  a.clear();
  std_a.clear();
  ASSERT_EQ(a.size(), std_a.size());
}

TEST(TestMultiSet, Swap1) {
  std::initializer_list<int> items{1, 5, 7, 6};
  std::initializer_list<int> items2{17, 25, 57, 66, 34, 12, 5};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  s21::MultiSet<int> my_multiset2(items2);
  std::multiset<int> std_multiset2(items2);
  my_multiset.swap(my_multiset2);
  std_multiset.swap(std_multiset2);

  // std::cout << my_multiset.size() << " std: " << std_multiset.size() << std::endl;
  // std::cout << my_multiset2.size() << " std: " << std_multiset2.size() << std::endl;
  ASSERT_TRUE(my_multiset.size() == std_multiset.size());
  ASSERT_TRUE(my_multiset2.size() == std_multiset2.size());

  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  auto my_iter2 = my_multiset2.begin();
  auto std_iter2 = std_multiset2.begin();
  while (std_iter2 != std_multiset2.end()) {
    ASSERT_TRUE(*my_iter2 == *std_iter2);
    ++my_iter2;
    ++std_iter2;
  }
}

TEST(TestMultiSet, Swap2) {
  s21::MultiSet<int> A = {1, 2, 3, 4};
  s21::MultiSet<int> B = {5, 6, 7, 8};
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

TEST(TestMultiSet, Swap3) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::MultiSet<int> s11;
  std::multiset<int> s22;
  s1.swap(s11);
  s2.swap(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Swap4) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::MultiSet<int> s11 = {389, 3829, 111, 189, 11};
  std::multiset<int> s22 = {389, 3829, 111, 189, 11};
  s1.swap(s11);
  s2.swap(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Swap5) {
  s21::MultiSet<int> s1;
  std::multiset<int> s2;
  s21::MultiSet<int> s11;
  std::multiset<int> s22;
  s1.swap(s11);
  s2.swap(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s11.begin();
  for (auto it2 = s22.begin(); it2 != s22.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Find1) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.find(66);
  auto std_iter = std_multiset.find(66);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_multiset.find(17);
  std_iter = std_multiset.find(17);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_multiset.find(25);
  std_iter = std_multiset.find(25);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_multiset.find(57);
  std_iter = std_multiset.find(57);
  ASSERT_TRUE(*my_iter == *std_iter);
  my_iter = my_multiset.find(34);
  std_iter = std_multiset.find(34);
  ASSERT_TRUE(*my_iter == *std_iter);
}

TEST(TestMultiSet, Find2) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  auto my_iter = my_multiset.find(666);
  auto std_iter = std_multiset.find(666);
  ASSERT_TRUE(my_iter == my_multiset.end());
  ASSERT_TRUE(std_iter == std_multiset.end());
}

TEST(TestMultiSet, Find3) {
  const s21::MultiSet<int> A = {1, 2, 3, 3, 3, 3, 3, 3, 3, 3,
                           3, 3, 3, 4, 5, 6, 7, 8, 9, 10};
  auto i = A.find(6);
  ASSERT_EQ(*i, 6);
}

TEST(TestMultiSet, Find4) {
  s21::MultiSet<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::multiset<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  auto it = a.find(5);
  auto std_it = std_a.find(5);
  ASSERT_EQ(*it, *std_it);
}

TEST(TestMultiSet, Find5) {
  s21::MultiSet<int> a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  std::multiset<int> std_a{0, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7};
  auto it = a.find(500);
  auto std_it = std_a.find(500);
  if (it == a.end() && std_it == std_a.end())
    ASSERT_EQ(1, 1);
  else
    ASSERT_EQ(1, 0);
}

TEST(TestMultiSet, Contains1) {
  std::initializer_list<int> items{17, 25, 57, 66, 34, 12, 5};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  bool my_cont = my_multiset.contains(17);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_multiset.contains(18);
  ASSERT_TRUE(my_cont == false);
  my_cont = my_multiset.contains(25);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_multiset.contains(57);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_multiset.contains(5);
  ASSERT_TRUE(my_cont == true);
  my_cont = my_multiset.contains(13457);
  ASSERT_TRUE(my_cont == false);
  my_cont = my_multiset.contains(0);
  ASSERT_TRUE(my_cont == false);
}

TEST(TestMultiSet, Contains2) {
  std::string a = "asd";
  std::string b = "asdf";
  std::string c = "asdf";
  s21::MultiSet<std::string> s1 = {a, b};
  ASSERT_EQ(s1.contains(c), true);
}

TEST(TestMultiSet, Contains3) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.contains(0), false);
}

TEST(TestMultiSet, Contains4) {
  s21::MultiSet<int> a{0, 2, -2, 3, -3, 4, -4};
  ASSERT_EQ(a.contains(500), false);
}

TEST(TestMultiSet, Contains5) {
  s21::MultiSet<int> a;
  ASSERT_EQ(a.contains(500), false);
}

TEST(TestMultiSet, Contains6) {
  s21::MultiSet<double> a{2.34534534};
  ASSERT_EQ(a.contains(2.34534538), false);
}

TEST(TestMultiSet, Merge1) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{4, 5, 6, 2};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  s21::MultiSet<int> my_multiset2(items2);
  std::multiset<int> std_multiset2(items2);
  my_multiset.merge(my_multiset2);
  std_multiset.merge(std_multiset2);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_EQ(*my_iter, *std_iter);
    ++my_iter;
    ++std_iter;
  }
  my_iter = my_multiset2.begin();
  std_iter = std_multiset2.begin();
  while (std_iter != std_multiset2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Merge2) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{1, 2, 3};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  s21::MultiSet<int> my_multiset2(items2);
  std::multiset<int> std_multiset2(items2);
  my_multiset.merge(my_multiset2);
  std_multiset.merge(std_multiset2);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Merge3) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{2, 3, 543};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  s21::MultiSet<int> my_multiset2(items2);
  std::multiset<int> std_multiset2(items2);
  my_multiset.merge(my_multiset2);
  std_multiset.merge(std_multiset2);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Merge4) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{44, 5, 6};
  s21::MultiSet<int> my_multiset(items);
  std::multiset<int> std_multiset(items);
  s21::MultiSet<int> my_multiset2(items2);
  std::multiset<int> std_multiset2(items2);

  // auto itt = std_multiset2.begin();
  // while (itt != std_multiset2.end()) {
  //   std::cout << *itt << std::endl;
  //   ++itt;
  // }

  my_multiset.merge(my_multiset2);
  std_multiset.merge(std_multiset2);
  auto my_iter = my_multiset.begin();
  auto std_iter = std_multiset.begin();
  while (std_iter != std_multiset.end()) {
    // std::cout << *my_iter << " std: " << *std_iter << std::endl;
    ASSERT_EQ(*my_iter, *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMultiSet, Merge5) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::MultiSet<int> s11 = {389, 3829, 111, 189, 11};
  std::multiset<int> s22 = {389, 3829, 111, 189, 11};
  s1.merge(s11);
  s2.merge(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Merge6) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::MultiSet<int> s11 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s22 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.merge(s11);
  s2.merge(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Merge7) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::MultiSet<int> s11 = {1, 2, 3, 4, 5, 6, 7, 8, 389, 3829, 111, 189, 11};
  std::multiset<int> s22 = {1, 2, 3, 4, 5, 6, 7, 8, 389, 3829, 111, 189, 11};
  s1.merge(s11);
  s2.merge(s22);
  ASSERT_EQ(s1.size(), s2.size());
  ASSERT_EQ(s11.size(), s22.size());
  auto it1 = s1.begin();
  for (auto it2 = s2.begin(); it2 != s2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
}

TEST(TestMultiSet, Capacity1) {
  s21::MultiSet<int> A;
  ASSERT_EQ(A.size(), 0);
  ASSERT_EQ(A.empty(), true);
}

TEST(TestMultiSet, Capacity2) {
  s21::MultiSet<int> A = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(A.size(), 8);
  ASSERT_EQ(A.empty(), false);
}

TEST(TestMultiSet, Capacity3) {
  s21::MultiSet<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(A.size(), 10);
  ASSERT_EQ(A.empty(), false);
}

TEST(TestMultiSet, Empty1) {
  s21::MultiSet<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestMultiSet, Empty2) {
  s21::MultiSet<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(TestMultiSet, Empty3) {
  s21::MultiSet<int> a;
  std::multiset<int> std_a;
  ASSERT_EQ(a.empty(), std_a.empty());
}

TEST(TestMultiSet, Empty4) {
  s21::MultiSet<int> a{1};
  std::multiset<int> std_a{1};
  ASSERT_EQ(a.empty(), std_a.empty());
}

TEST(TestMultiSet, Size1) {
  s21::MultiSet<int> s1;
  std::multiset<int> s2;
  s1.insert(1);
  s2.insert(1);
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestMultiSet, Size2) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestMultiSet, Size3) {
  s21::MultiSet<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8};
  s1.clear();
  s2.clear();
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(TestMultiSet, Size4) {
  s21::MultiSet<int> a;
  std::multiset<int> std_a;
  ASSERT_EQ(a.size(), std_a.size());
}

TEST(TestMultiSet, Max_size) {
  s21::MultiSet<int> a;
  std::multiset<int> std_a;
  std::cout << "max size s21::MultiSet - " << a.max_size()
            << "\nmax_size std::multiset - " << std_a.max_size() << std::endl;
}

TEST(TestMultiSet, Count1) {
  s21::MultiSet<int> a = {1, 2, 3, 4, 5, 5, 5, 6, 7, 8};
  std::multiset<int> std_a = {1, 2, 3, 4, 5, 5, 5, 6, 7, 8};
  ASSERT_EQ(a.count(5), std_a.count(5));
}

TEST(TestMultiSet, Count2) {
  s21::MultiSet<double> a = {1.123, -21.345, 3.1415, 3.1415};
  std::multiset<double> std_a = {1.123, -21.345, 3.1415, 3.1415};
  ASSERT_EQ(a.count(3.1415), std_a.count(3.1415));
  ASSERT_EQ(a.count(2.2), std_a.count(2.2));
  ASSERT_EQ(a.count(1.123), std_a.count(1.123));
}

TEST(TestMultiSet, EqualRange1) {
  s21::MultiSet<double> a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, 1.2};
  std::multiset<double> std_a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, 1.2};
  auto a_first = a.equal_range(-21.345).first;
  auto a_second = a.equal_range(-21.345).second;
  auto std_first = std_a.equal_range(-21.345).first;
  auto std_second = std_a.equal_range(-21.345).second;
  ASSERT_EQ(*(a_first), *(std_first));
  ASSERT_EQ(*(a_second), *(std_second));
  ASSERT_EQ(*(a.lower_bound(-21.345)), *(std_first));
  ASSERT_EQ(*(a.upper_bound(-21.345)), *(std_second));
}

TEST(TestMultiSet, EqualRange2) {
  s21::MultiSet<double> a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, 1.2};
  std::multiset<double> std_a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, 1.2};
  auto a_first = a.equal_range(3.1415).first;
  auto a_second = a.equal_range(3.1415).second;
  auto std_first = std_a.equal_range(3.1415).first;
  // auto std_second = std_a.equal_range(3.1415).second;
  ASSERT_EQ(*(a_first), *(std_first));
  ASSERT_TRUE(a_second == nullptr);

}

TEST(TestMultiSet, EqualRange3) {
  s21::MultiSet<double> a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, -111.2, 4.55, -111.2, -111.2};
  std::multiset<double> std_a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, 1.2, 4.55, -111.2, -111.2};
  auto a_first = a.equal_range(3.1415).first;
  auto a_second = a.equal_range(3.1415).second;
  auto std_first = std_a.equal_range(3.1415).first;
  auto std_second = std_a.equal_range(3.1415).second;
  ASSERT_EQ(*(a_first), *(std_first));
  ASSERT_EQ(*(a_second), *(std_second));
  ASSERT_EQ(*(a.lower_bound(3.1415)), *(std_first));
  ASSERT_EQ(*(a.upper_bound(3.1415)), *(std_second));
}

TEST(TestMultiSet, EqualRange4) {
  s21::MultiSet<double> a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, -111.2, 4.55, -111.2, -111.2};
  std::multiset<double> std_a = {1.123, -21.345, 3.1415, 3.1415, 3.1415, 1.2, 4.55, -111.2, -111.2};
  auto a_first = a.equal_range(-111.2).first;
  auto a_second = a.equal_range(-111.2).second;
  auto std_first = std_a.equal_range(-111.2).first;
  auto std_second = std_a.equal_range(-111.2).second;
  ASSERT_EQ(*(a_first), *(std_first));
  ASSERT_EQ(*(a_second), *(std_second));
  ASSERT_EQ(*(a.lower_bound(-111.2)), *(std_first));
  ASSERT_EQ(*(a.upper_bound(-111.2)), *(std_second));

}

TEST(TestMultiSet, InsertMany1) {
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

TEST(TestMultiSet, InsertMany2) {
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

TEST(TestMultiSet, InsertMany3) {
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