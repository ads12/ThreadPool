#include <iostream>
#include<UnitTest++.h>
#include "main.h"
using namespace std;

TEST(testProdthreadPoolsize)
{
  {
    ThreadPool pool(5);
    CHECK_EQUAL(pool.GetProdThreadPoolsize(), 5);
  }
}

TEST(testConsthreadPoolsize)
{
  {
    ThreadPool pool(5);
    CHECK_EQUAL(pool.GetConsThreadPoolsize(), 5);
  }
}

TEST(testMemoryPoolsize)
{
  ThreadPool* pool = new ThreadPool(5);
  CHECK(pool->GetMemoryPoolsize());
  delete pool;
}

int main()
{
    cout << "Hello world!" << endl;
    return UnitTest::RunAllTests();
    return 0;
}
