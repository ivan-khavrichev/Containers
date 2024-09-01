#include "tests_header.h"

using namespace s21;

TEST(TestMap, Constructor1) {
  Map<int, double> my_map{
      std::make_pair(42, 12.21), std::make_pair(3, 21.12),
      std::make_pair(33, 66.66), std::make_pair(3, 1.1)};
  std::map<int, double> std_map{
      std::make_pair(42, 12.21), std::make_pair(3, 21.12),
      std::make_pair(33, 66.66), std::make_pair(3, 1.1)};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (my_iter != my_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(std_iter == std_map.end());

  Map<int, double> my_map2(my_map);
  std::map<int, double> std_map2(std_map);

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());

  Map<int, double> my_map3 = std::move(my_map2);
  std::map<int, double> std_map3 = std::move(std_map2);

  my_iter = my_map3.begin();
  std_iter = std_map3.begin();

  while (std_iter != std_map3.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMap, Constructor2) {
  Map<int, char> A;
  Map<int, int> B;
  const Map<int, int> C;
  const Map<char, int> D;
  ASSERT_EQ(A.size(), 0);
  ASSERT_EQ(B.size(), 0);
  ASSERT_EQ(C.size(), 0);
  ASSERT_EQ(D.size(), 0);
}

TEST(TestMap, Constructor3) {
  Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 30), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 30), std::pair(3, 30)});
  auto j = B.begin();
  for (auto i : A) {
    // std::cout << i.first << i.second << "orig: " << (*j).first << (*j).second
    // << std::endl;
    ASSERT_EQ(i.second, (*j).second);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}

TEST(TestMap, Constructor4) {
  Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    ASSERT_EQ((*it1).second, (*it2).second);
  it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    ASSERT_EQ((*it1).first, (*it2).first);
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Constructor5) {
  Map<int, int> m1;
  std::map<int, int> m2;
  ASSERT_EQ(m1.size(), m2.size());
  m1.insert({1, 1});
  m2.insert({1, 1});
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Constructor6) {
  Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto m11 = m1;
  auto m22 = m2;
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it2++, it1++)
    ASSERT_EQ((*it1).second, (*it2).second);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
}

TEST(TestMap, Constructor7) {
  Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto m11 = std::move(m1);
  auto m22 = std::move(m2);
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it2++, it1++)
    ASSERT_EQ((*it1).second, (*it2).second);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
}

TEST(TestMap, Constructor8) {
  Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  Map<int, int> m11;
  std::map<int, int> m22;
  m11 = std::move(m1);
  m22 = std::move(m2);
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it2++, it1++)
    ASSERT_EQ((*it1).second, (*it2).second);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
}

TEST(TestMap, Empty1) {
  Map<int, std::string> new_map;
  ASSERT_TRUE(new_map.empty() == true);

  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_TRUE(my_map.empty() == false);
}

TEST(TestMap, Empty2) {
  Map<int, int> m1;
  std::map<int, int> m2;
  std::pair<int, int> pair = {1, 1};
  m1.insert(pair);
  m2.insert(pair);
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Empty3) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Empty4) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Empty5) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1.empty(), m2.empty());
}

TEST(TestMap, Empty6) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  ASSERT_EQ(m1.empty(), m2.empty());
}

TEST(TestMap, Size) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(TestMap, Clear1) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(TestMap, Clear2) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m1.empty(), m2.empty());
}

TEST(TestMap, Clear3) {
  Map<int, int> m1;
  std::map<int, int> m2;
  m1.clear();
  m2.clear();
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m1.empty(), m2.empty());
}

TEST(TestMap, Clear4) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m1.empty(), m2.empty());
  m1.clear();
  m2.clear();
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m1.empty(), m2.empty());
}

TEST(TestMap, Insert1) {
  Map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert(1, "one");
  std_map.insert({1, "one"});
  my_map.insert(2, "two");
  std_map.insert({2, "two"});
  my_map.insert(22, "twotwo");
  std_map.insert({22, "twotwo"});
  my_map.insert(-22, "-twotwo");
  std_map.insert({-22, "-twotwo"});
  my_map.insert(22, "three");
  std_map.insert({22, "three"});
  my_map.insert(22234, "two3two");
  std_map.insert({22234, "two3two"});
  my_map.insert(12, "onetwo");
  std_map.insert({12, "onetwo"});
  my_map.insert(-12, "-onetwo");
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMap, Insert2) {
  Map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert({1, "one"});
  std_map.insert({1, "one"});
  my_map.insert({2, "two"});
  std_map.insert({2, "two"});
  my_map.insert({22, "twotwo"});
  std_map.insert({22, "twotwo"});
  my_map.insert({-22, "-twotwo"});
  std_map.insert({-22, "-twotwo"});
  my_map.insert({22, "three"});
  std_map.insert({22, "three"});
  my_map.insert({22234, "two3two"});
  std_map.insert({22234, "two3two"});
  my_map.insert({12, "onetwo"});
  std_map.insert({12, "onetwo"});
  my_map.insert({-12, "-onetwo"});
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMap, Insert3) {
  Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  auto ans = A.insert(std::pair(4, 40));
  auto original_ans = B.insert(std::pair(4, 40));
  ASSERT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  ASSERT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  ASSERT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(4, 40));
  original_ans = B.insert(std::pair(4, 40));
  ASSERT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  ASSERT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  ASSERT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(5, 50));
  original_ans = B.insert(std::pair(5, 50));
  ASSERT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  ASSERT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  ASSERT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(5, 50));
  original_ans = B.insert(std::pair(5, 50));
  ASSERT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  ASSERT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  ASSERT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(6, 60));
  original_ans = B.insert(std::pair(6, 60));
  ASSERT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  ASSERT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  ASSERT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(6, 60));
  original_ans = B.insert(std::pair(6, 60));
  ASSERT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  ASSERT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  ASSERT_EQ(ans.second, original_ans.second);
  auto j = B.begin();
  for (auto i : A) {
    ASSERT_EQ((*j).first, i.first);
    ASSERT_EQ((*j).second, i.second);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}

TEST(TestMap, Insert4) {
  Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  A.insert(4, 40);
  B.insert(std::pair(4, 40));
  A.insert(4, 40);
  B.insert(std::pair(4, 40));
  A.insert(5, 50);
  B.insert(std::pair(5, 50));
  A.insert(5, 50);
  B.insert(std::pair(5, 50));

  A.insert(6, 60);
  B.insert(std::pair(6, 60));
  A.insert(6, 60);
  B.insert(std::pair(6, 60));
  auto j = B.begin();
  for (auto i : A) {
    ASSERT_EQ((*j).first, i.first);
    ASSERT_EQ((*j).second, i.second);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}

TEST(TestMap, Insert5) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::pair<int, int> pair = {3, 1};
  ASSERT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Insert6) {
  Map<int, int> m1;
  std::map<int, int> m2;
  ASSERT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  ASSERT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  ASSERT_EQ(m1.empty(), m2.empty());
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Insert7) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  ASSERT_EQ(m1.insert(3, 1).second, m2.insert(pair).second);
  ASSERT_EQ(m1.empty(), m2.empty());
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Insert8) {
  Map<int, int> m1;
  std::map<int, int> m2;
  ASSERT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  ASSERT_EQ(m1.insert(3, 1).second, m2.insert(pair).second);
  ASSERT_EQ(m1.empty(), m2.empty());
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Insert9) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1.empty(), m2.empty());
  ASSERT_EQ(m1.empty(), m2.empty());
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(TestMap, Erase1) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();



  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMap, Erase2) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;
  my_map.erase(my_iter);
  std_map.erase(std_iter);
  my_iter = my_map.begin();
  std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMap, Erase3) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;
  ++my_iter;
  ++std_iter;

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMap, Erase4) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.erase(m1.begin());
  m2.erase(m2.begin());
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Swap1) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  Map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Swap2) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  Map<int, int> m11 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  std::map<int, int> m22 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  m1.swap(m11);
  m2.swap(m22);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Swap3) {
  Map<int, int> m1;
  std::map<int, int> m2;
  Map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Swap4) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  Map<int, std::string> my_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.swap(my_map2);
  std_map.swap(std_map2);

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());
}

TEST(TestMap, Merge1) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  Map<int, std::string> my_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.merge(my_map2);
  std_map.merge(std_map2);
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(TestMap, Merge2) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  Map<int, int> m11 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  std::map<int, int> m22 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  m1.merge(m11);
  m2.merge(m22);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Merge3) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  Map<int, int> m11 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m22 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.merge(m11);
  m2.merge(m22);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Merge4) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {10, 3}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {10, 3}};
  Map<int, int> m11 = {{9, 12}, {39, 12}, {1, 12}, {18, 12},
                            {1, 12},  {1, 1},     {2, 2},    {10, 3},
                            {4, 4},    {5, 5}};

  std::map<int, int> m22 = {{9, 12}, {39, 12}, {1, 12}, {18, 12},
                            {1, 12},  {1, 1},     {2, 2},    {10, 3},
                            {4, 4},    {5, 5}};
  m1.merge(m11);
  m2.merge(m22);
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m11.size(), m22.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Iterator1) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  ASSERT_EQ((*it1).second, (*it2).second);
}

TEST(TestMap, Iterator2) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  it1++, it2++;
  it1++, it2++;
  it1--, it2--;
  it1++, it2++;
  it1--, it2--;
  ASSERT_EQ((*it2).second, (*it1).second);
}

TEST(TestMap, Contains1) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1.contains(1), true);
}

TEST(TestMap, Contains2) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1.contains(0), false);
}

TEST(TestMap, Contains3) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_EQ(my_map.contains(42), true);
  ASSERT_EQ(my_map.contains(42342), false);
  ASSERT_EQ(my_map.contains(33), true);
  ASSERT_EQ(my_map.contains(0), false);
}

TEST(TestMap, Contains4) {
  Map<int, int> a{{3, 7}, {8, 3}, {1, 9}};
  ASSERT_EQ(a.contains(8), true);
  ASSERT_EQ(a.contains(5), false);
}

TEST(TestMap, At1) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  for (size_t i = 1; i < m1.size(); i++) ASSERT_EQ(m1.at(i), m2.at(i));
}

TEST(TestMap, At2) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  ASSERT_ANY_THROW(m1.at(0));
  ASSERT_ANY_THROW(m2.at(0));
}

TEST(TestMap, At3) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1.at(100), m2.at(100));
}

TEST(TestMap, At4) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map.at(33);
  auto std_ans = std_map.at(33);
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map.at(3);
  std_ans = std_map.at(3);
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(TestMap, At5) {
  Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  ASSERT_EQ(A.at(1), B.at(1));
  ASSERT_EQ(A.at(2), B.at(2));
  ASSERT_EQ(A.at(3), B.at(3));
  A.at(3) = 200;
  B.at(3) = 200;
  ASSERT_EQ(A.at(3), B.at(3));
}

TEST(TestMap, OperatorSquareBrackets1) {
  Map<int, int> A({std::pair(1, 10)});
  std::map<int, int> B({std::pair(1, 10)});
  ASSERT_EQ(A[1], B[1]);
  A[2] = 20;
  B[2] = 20;
  B[4] = 999;
  A[4] = 999;
  ASSERT_EQ(A[4], B[4]);
  ASSERT_EQ(A[2], B[2]);
}

TEST(TestMap, OperatorSquareBrackets2) {
  Map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map[33];
  auto std_ans = std_map[33];
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map[3];
  std_ans = std_map[3];
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(TestMap, OperatorSquareBrackets3) {
  Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  ASSERT_EQ(m1[100], m2[100]);
  ASSERT_NO_THROW(m1[-2] = 3);
  ASSERT_NO_THROW(m2[-2] = 3);
  ASSERT_NO_THROW(m1.at(-2) = 5);
  ASSERT_NO_THROW(m2.at(-2) = 5);
  ASSERT_EQ(m1.at(-2), m2.at(-2));
}

TEST(TestMap, InsertOrAssign1) {
  Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  A.insert_or_assign(3, 60);
  B.insert_or_assign(3, 60);
  A.insert_or_assign(4, 60);
  B.insert_or_assign(4, 60);
  auto j = B.begin();
  for (auto i : A) {
    ASSERT_EQ((*j).first, i.first);
    ASSERT_EQ((*j).second, i.second);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}

TEST(TestMap, InsertOrAssign2) {
  Map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert_or_assign(1, "one");
  std_map.insert_or_assign(1, "one");
  my_map.insert_or_assign(2, "two");
  std_map.insert_or_assign(2, "two");
  my_map.insert_or_assign(22, "twotwo");
  std_map.insert_or_assign(22, "twotwo");
  my_map.insert_or_assign(-22, "-twotwo");
  std_map.insert_or_assign(-22, "-twotwo");
  my_map.insert_or_assign(22, "three");
  std_map.insert_or_assign(22, "three");
  my_map.insert_or_assign(22234, "two3two");
  std_map.insert_or_assign(22234, "two3two");
  my_map.insert_or_assign(12, "onetwo");
  std_map.insert_or_assign(12, "onetwo");
  my_map.insert_or_assign(-12, "-onetwo");
  std_map.insert_or_assign(-12, "-onetwo");

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(TestMap, Iterator9000) {
  Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  auto it = A.begin();
  auto it_std = B.begin();
  it++, it_std++;
  ++it, ++it_std;    
  it--, it_std--;
  ASSERT_EQ((*it).first, (*it_std).first);
  it--, it_std--;
  ASSERT_EQ((*it).first, (*it_std).first);
}

TEST(TestMap, Begin9000) {
  const Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  const std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  auto it = A.begin();
  auto it_std = B.begin();
  it++, it_std++;
  ASSERT_EQ((*it).first, (*it_std).first);
}

TEST(TestMap, InsertMany1) {
  Map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  A.insert_many(std::pair(4, 40), std::pair(5, 50), std::pair(6, 60), std::pair(7, 70));
  B.insert(std::pair(4, 40));
  B.insert(std::pair(5, 50));
  B.insert(std::pair(6, 60));
  B.insert(std::pair(7, 70));

  auto j = B.begin();
  for (auto i : A) {
    ASSERT_EQ((*j).first, i.first);
    ASSERT_EQ((*j).second, i.second);
    j++;
  }
  ASSERT_EQ(A.size(), B.size());
}

TEST(TestMap, InsertErase1) {
	Map<int, int> tree;
	std::pair<int, int> aaa = std::pair(5, 1); 
	tree.insert(aaa);
	tree.insert(std::pair(-1, 2));
	tree.insert(std::pair(3, 3));
	tree.insert(std::pair(7, 4));
	tree.insert(std::pair(2, 5));
	tree.insert(std::pair(1, 6));
	tree.insert(std::pair(-4, 7));	
	tree.insert(std::pair(4, 8));
	tree.insert(std::pair(10, 9));
	tree.print();
	auto itt = tree.begin();
	itt++; // -1
	itt++; // 1
	itt++; // 2
	itt++; // 3
	itt++; // 4
	itt++; // 5
	// itt++; // 7
	// itt++; // 10
	tree.erase(itt);
  }

  TEST(TestMap, InsertErase2) {
	Map<int, int> tree;
	std::pair<int, int> aaa = std::pair(5, 1); 
	tree.insert(aaa);
	tree.insert(std::pair(-1, 2));
	tree.insert(std::pair(3, 3));
	tree.insert(std::pair(7, 4));
	tree.insert(std::pair(2, 5));
	tree.insert(std::pair(1, 6));
	tree.insert(std::pair(-4, 7));	
	tree.insert(std::pair(4, 8));
	tree.insert(std::pair(10, 9));
	auto itt = tree.begin();
	itt++; // -1
	// itt++; // 1
	// itt++; // 2
	// itt++; // 3
	// itt++; // 4
	// itt++; // 5
	// itt++; // 7
	// itt++; // 10
	tree.erase(itt);
  }