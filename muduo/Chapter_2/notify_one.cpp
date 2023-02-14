#include<thread>
#include<mutex>
#include<condition_variable>
#include<gtest/gtest.h>

bool flag = false;
std::mutex m;
std::condition_variable cv;

void Prod(void)
{
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [](){return flag;});
}

void Cons(void)
{
        flag = true;
        cv.notify_one();
}

TEST(notify_test, T01)
{
        flag = false;

        std::thread tProd(Prod);
        std::thread tCons(Cons);

        tProd.join();
        tCons.join();
}

int main(int argc, char* argv[])
{
        testing::InitGoogleTest(&argc, argv);

        return RUN_ALL_TESTS();
}