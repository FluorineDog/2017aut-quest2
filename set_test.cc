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
    Lab::set<data_t> seta;
    std::set<data_t> setb;
    using op_arg1_t = Lab::set<data_t> &;
    using op_arg2_t = std::set<data_t> &;
    #define op_args_t op_arg1_t, op_arg2_t
    using operation_t = void(op_args_t);

    auto co_insert = [](auto &bufa, auto &bufb){
        auto val = m_rand();
        bufa.insert(val);
        bufb.insert(val);
    };

    auto co_erase = [](auto &bufa, auto &bufb){
        bufa.erase(++bufa.begin());
        bufb.erase(++bufb.begin());
    };

    auto co_clear = [](auto &bufa, auto &bufb){
        bufa.clear();
        bufb.clear();
    };

    using namespace std::placeholders;
    #define TEST(count, operation, desc) SET_ASSERT_EQUIVALENCE(seta, setb, std::function<operation_t>( \
                                            std::bind(timed_func<operation_t, op_args_t>, desc, \
                                            std::function<operation_t>(std::bind(repeat<operation_t, op_args_t>, count, operation, _1, _2)), \
                                        _1, _2)))
    TEST(1000, co_insert, "push1");
    TEST(1000000, co_insert, "push2");
    TEST(1234, co_erase, "erase1");
    TEST(1000, co_insert, "push3");
    TEST(543, co_erase, "erase2");
    TEST(2, co_clear, "clear1");
    TEST(3456, co_insert, "push4");
    println("All tests done.");
    return 0;
}
