#include "tests_header.h"

namespace {
using namespace s21;  
TEST(TestQueue, Constructor_Default) {
  Queue<int> s21_queue;
  std::queue<int> std_queue;
  ASSERT_EQ(s21_queue.size(), std_queue.size());
  ASSERT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(TestQueue, Constructor_Initializer_queue) {
  Queue<int> s21_queue = {1, 2, 3, 4};
  ASSERT_EQ(s21_queue.front(), 1);
  ASSERT_EQ(s21_queue.size(), size_t(4));
  ASSERT_EQ(s21_queue.empty(), false);
}

TEST(TestQueue, Constructor_Copy) {
  Queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  Queue<char> s21_queue_2 = s21_queue_1;

  ASSERT_EQ(s21_queue_1.size(), s21_queue_2.size());

  for (auto i = 0; i < 4; i++) {
    ASSERT_EQ(s21_queue_1.front(), s21_queue_2.front());
    ASSERT_EQ(s21_queue_1.size(), s21_queue_2.size());
    s21_queue_1.pop(), s21_queue_2.pop();
  }
}

TEST(TestQueue, Constructor_Move) {
  Queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  Queue<char> s21_queue_2 = std::move(s21_queue_1);
  Queue<char> s21_queue_3 = {'a', 'b', 'c', 'd'};

  ASSERT_EQ(s21_queue_2.size(), s21_queue_3.size());
  ASSERT_EQ(s21_queue_1.size(), size_t(0));
  ASSERT_EQ(s21_queue_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    ASSERT_EQ(s21_queue_3.front(), s21_queue_2.front());
    ASSERT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
}

TEST(TestQueue, Front_Back) {
  Queue<double> s21_queue_d = {-7.3, 10.0001};
  std::queue<double> std_queue_d;
  std_queue_d.push(-7.3);
  std_queue_d.push(10.0001);
  ASSERT_EQ(s21_queue_d.front(), std_queue_d.front());
  ASSERT_EQ(s21_queue_d.back(), std_queue_d.back());

  Queue<int> s21_queue_i = {5, -43};
  std::queue<int> std_queue_i;
  std_queue_i.push(5);
  std_queue_i.push(-43);
  ASSERT_EQ(s21_queue_i.front(), std_queue_i.front());
  ASSERT_EQ(s21_queue_i.back(), std_queue_i.back());

  Queue<char> s21_queue_c = {'a', 'b'};
  std::queue<char> std_queue_c;
  std_queue_c.push('a');
  std_queue_c.push('b');
  ASSERT_EQ(s21_queue_c.front(), std_queue_c.front());
  ASSERT_EQ(s21_queue_c.back(), std_queue_c.back());
}

TEST(TestQueue, Modifier_Push) {
  Queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  ASSERT_EQ(s21_queue.front(), std_queue.front());
  ASSERT_EQ(s21_queue.size(), std_queue.size());
  ASSERT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(TestQueue, Modifier_Pop) {
  Queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  s21_queue.pop();
  s21_queue.pop();
  std_queue.pop();
  std_queue.pop();
  s21_queue.push(15);
  s21_queue.push(10);
  std_queue.push(15);
  std_queue.push(10);
  s21_queue.pop();
  std_queue.pop();
  ASSERT_EQ(s21_queue.front(), std_queue.front());
  ASSERT_EQ(s21_queue.size(), std_queue.size());
  ASSERT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(TestQueue, Modifier_Swap) {
  Queue<std::string> s21_queue_1 = {"bababa", "school", "no",
                                         "yes"};
  Queue<std::string> s21_queue_2 = {"bebebe", "bubububu", "aaaaaa"};
  Queue<std::string> s21_queue_3 = {"bababa", "school", "no",
                                         "yes"};
  Queue<std::string> s21_queue_4 = {"bebebe", "bubububu", "aaaaaa"};

  s21_queue_1.swap(s21_queue_2);

  ASSERT_EQ(s21_queue_1.size(), s21_queue_4.size());
  ASSERT_EQ(s21_queue_2.size(), s21_queue_3.size());
  for (auto i = 0; i < 4; i++) {
    ASSERT_EQ(s21_queue_3.front(), s21_queue_2.front());
    ASSERT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    ASSERT_EQ(s21_queue_1.front(), s21_queue_4.front());
    ASSERT_EQ(s21_queue_1.size(), s21_queue_4.size());
    s21_queue_1.pop(), s21_queue_4.pop();
  }
}

TEST(TestQueue, InsertManyBack) {
 Queue<double> A;
 std::queue<double> AA;
  A.insert_many_back(5.4321, -1.2345, 0.0, 0.0, -2.0001);
  AA.push(5.4321);
  AA.push(-1.2345);
  AA.push(0.0);
  AA.push(0.0);
  AA.push(-2.0001);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(A.front(), AA.front());
    ASSERT_EQ(A.size(), AA.size());
    A.pop();
    AA.pop();
  }
}

}  // namespace