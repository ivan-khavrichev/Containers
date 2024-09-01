#include "tests_header.h"

using namespace s21;

TEST(TestVector, PrintVector) {
  Vector<int> A = {1, -2};
  ASSERT_NO_THROW(A.print());
}

TEST(TestVector, constructor_default_and_init) {
  //default + size
  Vector<int> A;
  std::vector<int> AA;
  ASSERT_TRUE(A==AA);
  Vector<double, unsigned> B;
  ASSERT_EQ(B.size(), 0);
  ASSERT_EQ(B.capacity(), 0);
  ASSERT_EQ(sizeof(B.capacity()), sizeof(unsigned));
  // init
  Vector<double> C(15);
  ASSERT_EQ(C.size(), 15);
  Vector<bool> D(23);
  ASSERT_EQ(D.size(), 23);
#ifndef __APPLE__
  ASSERT_THROW(Vector<int> E(0), std::out_of_range);
  //  ASSERT_THROW(Vector<double> F(-1), std::out_of_range);
#endif
  // Vector<double> G(1.5);
  // std::vector<double> GG(1.5);
  // ASSERT_TRUE(G==GG);
  Vector<double> H = {2.32, 142.32, 5.555};
  std::vector<double> HH = {2.32, 142.32, 5.555};
  ASSERT_TRUE(H==HH);
  Vector<std::string> J = {"Peace", "Labour", "May", "Orthodoxy", "Autocracy", "Nationality"};
  std::vector<std::string> JJ = {"Peace", "Labour", "May", "Orthodoxy", "Autocracy", "Nationality"};
  ASSERT_TRUE(J==JJ);
}

TEST(TestVector, copy) {
  //copy
  Vector<double> A = {7.3, 1.2, 67.22, 55.4321, 10.0001};
  std::vector<double> AA = {7.3, 1.2, 67.22, 55.4321, 10.0001};
  Vector<double> B = A;
  std::vector<double> BB = AA;
  ASSERT_TRUE(B==BB);

  Vector<std::string> C = {"Peace", "Labour", "May", "Orthodoxy", "Autocracy", "Nationality"};
  std::vector<std::string> CC = {"Peace", "Labour", "May", "Orthodoxy", "Autocracy", "Nationality"};
  Vector<std::string> D = C;
  std::vector<std::string> DD = CC;
  ASSERT_TRUE(D==DD);
  
  //move
   Vector<double> X = {7.3, 1.2, 67.22, 55.4321, 10.0001};
  std::vector<double> XX = {7.3, 1.2, 67.22, 55.4321, 10.0001};
  Vector<double> Y = std::move(X);
  std::vector<double> YY = std::move(XX);
  ASSERT_TRUE(Y==YY);

  Vector<int> M = {7, 1, 67, 55, 10};
  std::vector<int> MM = {7, 1, 67, 55, 10};
  Vector<int> N = std::move(M);
  std::vector<int> NN = std::move(MM);
  ASSERT_TRUE(N==NN);  
}

TEST(TestVector, operator_copy_move) {
 Vector<double> A = {7.3, 1.2, 67.22, 55.4321, 10.0001};
 Vector<double> B;
  std::vector<double> AA = {7.3, 1.2, 67.22, 55.4321, 10.0001};
  std::vector<double> BB;
  B = A;
  BB = AA;
  ASSERT_TRUE(B==BB);
  ASSERT_TRUE(A==AA);

  Vector<double> X = {7.3, 1.2, 67.22, 55.4321, 10.0001};
  Vector<double> Y;
  std::vector<double> XX = {7.3, 1.2, 67.22, 55.4321, 10.0001};
  std::vector<double> YY;
  Y = std::move(X);
  YY = std::move(XX);
  ASSERT_TRUE(Y==YY);
  ASSERT_TRUE(X==XX);
}

TEST(TestVector, elements_access) {
  // at, front, back, data
  Vector<int> A = {123, 456, 789, -10000};
  std::vector<double> AA = {123, 456, 789, -10000};
  ASSERT_EQ(A.front(), AA.front());
  ASSERT_EQ(A.back(), AA.back());
  ASSERT_EQ(A.at(0), AA.at(0));
  ASSERT_EQ(A.at(1), AA.at(1));
  ASSERT_EQ(A.at(2), AA.at(2));
  ASSERT_DOUBLE_EQ(*A.data(), *AA.data());
  #ifndef __APPLE__
  ASSERT_THROW(A.at(-1), std::out_of_range);
  ASSERT_THROW(A.at(4), std::out_of_range);
  #endif
  // op[], front, back
  Vector<double> B = {12.3, 4.56, .789, -3.1415};
  std::vector<double> BB = {12.3, 4.56, .789, -3.1415};
  ASSERT_EQ(B.front(), BB.front());
  ASSERT_EQ(B.back(), BB.back());
  ASSERT_EQ(B[0], BB[0]);
  ASSERT_EQ(B[1], BB[1]);
  ASSERT_EQ(B[2], BB[2]);
  ASSERT_DOUBLE_EQ(*B.data(), *BB.data());
}

TEST(TestVector, brackets) {
 Vector<int> A({1, 2, 3, 4, 5});
  std::vector<int> B({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(A[i], B[i]);
    A[i] = i + 2;
    B[i] = i + 2;
    ASSERT_EQ(A[i], B[i]);
  }
  const Vector<double> AA({45.355642, -2.4315, 0.0002, 10.012341, -812.12345});
  const std::vector<double> BB({45.355642, -2.4315, 0.0002, 10.012341, -812.12345});
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(A[i], B[i]);
  }
}

TEST(TestVector, begin_end) {
  Vector<double> A = {12.3, 4.56, .789, -3.1415};
  std::vector<double> AA = {12.3, 4.56, .789, -3.1415};
  ASSERT_DOUBLE_EQ(*A.begin(), *AA.begin());
  ASSERT_DOUBLE_EQ(*(A.end() - 1), *(AA.end() - 1));
}

TEST(TestVector, empty) {
 Vector<double> A = {12.3, 4.56, .789, -3.1415};
 std::vector<double> AA = {12.3, 4.56, .789, -3.1415};
 Vector<double> B;
 std::vector<double> BB;
 ASSERT_TRUE(A.empty() == AA.empty());
 ASSERT_TRUE(B.empty() == BB.empty());
}

TEST(TestVector, clear) {
  Vector<double> A = {12.3, 4.56, .789, -3.1415};
  std::vector<double> AA = {12.3, 4.56, .789, -3.1415};
  A.clear();
  AA.clear();
  ASSERT_TRUE(A==AA);
}

TEST(TestVector, insert) {
 Vector<double> A = {12.3, 4.56, .789, -3.1415};
  std::vector<double> AA = {12.3, 4.56, .789, -3.1415};
  auto it_lib_vec = AA.begin();
  auto it_vec = A.begin();
  it_vec = A.insert(it_vec, 7.45312);
  it_lib_vec = AA.insert(it_lib_vec, 7.45312);
  ASSERT_TRUE(A==AA);
  ++it_lib_vec;
  ++it_lib_vec;
  ++it_vec;
  ++it_vec;
  A.insert(it_vec, 4325.3456);
  AA.insert(it_lib_vec, 4325.3456);
  ASSERT_TRUE(A==AA);
}

TEST(TestVector, erase) {
 Vector<double> A = {12.3, 4.56, .789, -3.1415, 50.43, -145.312};
  std::vector<double> AA = {12.3, 4.56, .789, -3.1415, 50.43, -145.312};
  auto it_lib_vec = AA.begin();
  auto it_vec = A.begin();

  AA.erase(it_lib_vec);
  A.erase(it_vec);

  ASSERT_TRUE(A==AA);
  it_lib_vec = AA.begin();
  it_vec = A.begin();
  ++it_lib_vec;
  ++it_lib_vec;
  ++it_vec;
  ++it_vec;
  AA.erase(it_lib_vec);
  A.erase(it_vec);
  ASSERT_TRUE(A==AA);
}

TEST(TestVector, push_back) {
 Vector<double> A = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> AA = {3.423, 2.5234, 3.4567, 2.423455};
  A.push_back(534.532);
  A.push_back(0.432456);
  AA.push_back(534.532);
  AA.push_back(0.432456);
  ASSERT_TRUE(A==AA);
}

TEST(TestVector, pop_back) {
 Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  A.pop_back();
  A.pop_back();
  AA.pop_back();
  AA.pop_back();
  ASSERT_TRUE(A==AA);
}

TEST(TestVector, swap) {
  Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  Vector<double> B = {12.3, 4.56, .789, -3.1415, 50.43, -145.312};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> BB = {12.3, 4.56, .789, -3.1415, 50.43, -145.312};
  A.swap(B);
  AA.swap(BB);
  ASSERT_TRUE(A==AA);
  ASSERT_TRUE(B==BB);

  Vector<int> Ai = {45, -2, 0, 10, -812, 0, 12, 789};
  Vector<int> Bi = {12, 4, -3, 50, -145};
  std::vector<int> AAi = {45, -2, 0, 10, -812, 0, 12, 789};
  std::vector<int> BBi = {12, 4, -3, 50, -145};
  Ai.swap(Bi);
  AAi.swap(BBi);
  ASSERT_TRUE(Ai==AAi);
  ASSERT_TRUE(Bi==BBi);
}


TEST(TestVector, reserve) {
 Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};

  A.reserve(2);
  AA.reserve(2);
  EXPECT_TRUE(AA.capacity() == A.capacity());
  A.reserve(100);
  AA.reserve(100);
  ASSERT_TRUE(AA.capacity() == A.capacity());
}

TEST(TestVector, shrink_to_fit) {
 Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};

  A.shrink_to_fit();
  AA.shrink_to_fit();

  ASSERT_TRUE(AA.capacity() == A.capacity());
  A.reserve(100);
  AA.reserve(100);
  ASSERT_TRUE(AA.capacity() == A.capacity());
}

TEST(TestVector, shrink_to_fit_2) {
 Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};

  ASSERT_TRUE(AA.capacity() == A.capacity());
  A.reserve(100);
  AA.reserve(100);
  ASSERT_TRUE(AA.capacity() == A.capacity());
  A.shrink_to_fit();
  AA.shrink_to_fit();
  ASSERT_TRUE(AA.capacity() == A.capacity());
}

TEST(TestVector, max_size) {
 Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  ASSERT_EQ(A.max_size(), AA.max_size());
}

TEST(TestVector, EqVector) {
  Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> B = {0.01, 0.01, 0.01, 10.012341, -812.12345};
  ASSERT_TRUE(A == AA);
  ASSERT_FALSE(A == B);
  Vector<int> A1 = {45, -2, 0, 10, -812};
  std::vector<int> AA1 = {45, -2, 0, 10, -812};
  std::vector<int> B1 = {0, 0, 0, 10, -812};
  ASSERT_TRUE(A1 == AA1);
  ASSERT_FALSE(A1 == B1);

  Vector<char> A2 = {'a', 'b', 'c', 'd', 'e'};
  std::vector<char> AA2 = {'a', 'b', 'c', 'd', 'e'};
  std::vector<char> B2 = {'a', 'a', 'a', 'd', 'e'};
  ASSERT_TRUE(A2 == AA2);
  ASSERT_FALSE(A2 == B2);
}

TEST(TestVector, emplace_back) {
  Vector<double> A = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  std::vector<double> AA = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345};
  AA.emplace_back(45.355642);
  A.emplace_back(45.355642);
  ASSERT_TRUE(A == AA);
  A.emplace_back(0., 0.0002, 10.012341, -812.12345);
  std::vector<double> BB = {45.355642, -2.4315, 0.0002, 10.012341, -812.12345, 45.355642, 0., 0.0002, 10.012341, -812.12345};
  ASSERT_TRUE(A == BB);
}

TEST(TestVector, emplace) {
  Vector<int> A = {1, 2, 3, 4, 5};
  std::vector<int> AA = {1, 2, 3, 4, 5};
  AA.emplace(AA.begin() + 2, 6);
  A.emplace(A.begin() + 2, 6);
  ASSERT_TRUE(A == AA);
  A.emplace(A.begin() + 2, 7, 8, 9);
  std::vector<int> BB = {1, 2, 7, 8, 9, 6, 3, 4, 5};
  ASSERT_TRUE(A == BB);
}

TEST(TestVector, sort) {
  Vector<int> A{9, 0, 8, 3, 2, 1, 6, 5, 7, 4, -1};
  std::vector<int> AA{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  A.sort();
  ASSERT_TRUE(A == AA);
}

TEST(TestVector, pair_vector) {
  Vector<std::pair<Map<int, int>::MapNode, bool>> A;
}