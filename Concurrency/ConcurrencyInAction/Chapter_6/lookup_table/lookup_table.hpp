#include "lookup_table.hpp"

#include <iostream>
#include <string>

#include "gtest/gtest.h"

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class ThreadsafeLookupTableTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  ThreadsafeLookupTableTest() {
    // You can do set-up work for each test here.
  }

  ~ThreadsafeLookupTableTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
    threadsafe_lookup_table<int, int> t;
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that Foo does Xyz.
TEST_F(ThreadsafeLookupTableTest, value_for_test) {}
// Tests that the Foo::Bar() method does Abc.
TEST_F(ThreadsafeLookupTableTest, add_or_update_mapping_test) {}

TEST_F(ThreadsafeLookupTableTest, remove_mapping_test) {}
}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
