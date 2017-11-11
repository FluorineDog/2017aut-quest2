/**
 * By recolic, Nov 10.
 */

#include <chrono>
#include <iostream>
#include <random>
#include <functional>
#include "test_utils.hpp"
using rlib::println;

std::default_random_engine rand_eng(810);
std::uniform_real_distribution<double> distribution(0, 100);
double m_rand() {return distribution(rand_eng);}

template <class operation_t, typename... args_t>
void timed_func(const std::string &info, std::function<operation_t> f, args_t... args)
{
    println(info, "launched.");
    auto begin = std::chrono::high_resolution_clock::now();
    f(args ...);
    auto end = std::chrono::high_resolution_clock::now();
    println(info, "used", std::chrono::duration<double>(end - begin).count(), "s");
}

template <class operation_t, typename... args_t>
void repeat(size_t count, std::function<operation_t> f, args_t... args)
{
    for(size_t cter = 0; cter < count; ++cter)
        f(args ...);
}

int main()
{
    using data_t = double;
    Lab::priority_queue<data_t> priority_queuea;
    std::priority_queue<data_t> priority_queueb;
    using op_arg1_t = Lab::priority_queue<data_t> &;
    using op_arg2_t = std::priority_queue<data_t> &;
    #define op_args_t op_arg1_t, op_arg2_t
    using operation_t = void(op_args_t);

    auto co_push = [](auto &bufa, auto &bufb){
        auto val = m_rand();
        bufa.push(val);
        bufb.push(val);
    };

    auto co_pop = [](auto &bufa, auto &bufb){
        bufa.pop();
        bufb.pop();
    };

//    auto co_clear = [](auto &bufa, auto &bufb){
//        bufa.clear();
//        bufb.clear();
//    };
//
    using namespace std::placeholders;
    #define TEST(count, operation, desc) PRIORITY_QUEUE_ASSERT_EQUIVALENCE(priority_queuea, priority_queueb, std::function<operation_t>( \
                                            std::bind(timed_func<operation_t, op_args_t>, desc, \
                                            std::function<operation_t>(std::bind(repeat<operation_t, op_args_t>, count, operation, _1, _2)), \
                                        _1, _2)))
    
    println("Warning: because i can't iterate over Lab::priority_queue, I can only check your answer after all operations done.");
    TEST(1000, co_push, "push1");
    TEST(1000000, co_push, "push2");
    TEST(1234, co_pop, "pop1");
    TEST(1000, co_push, "push3");
    TEST(543, co_pop, "pop2");
    dynamic_assert(priority_queue_destroy_and_check(priority_queuea, priority_queueb), "check failed.");
    TEST(1000, co_push, "push3");
    TEST(543, co_pop, "pop2");
//    TEST(2, co_clear, "clear1");
    TEST(3456, co_push, "push4");
    dynamic_assert(priority_queue_destroy_and_check(priority_queuea, priority_queueb), "check failed.");
    println("All tests done.");
    return 0;
}
