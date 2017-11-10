/**
 * By recolic, Nov 10.
 */

#include <chrono>
#include <iostream>
#include <random>
#include <vector>
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
    Lab::vector<data_t> vcta;
    std::vector<data_t> vctb;
    using op_arg1_t = Lab::vector<data_t> &;
    using op_arg2_t = std::vector<data_t> &;
    #define op_args_t op_arg1_t, op_arg2_t
    using operation_t = void(op_args_t);

    auto co_push_back = [](auto &bufa, auto &bufb){
        auto val = m_rand();
        bufa.push_back(val);
        bufb.push_back(val);
    };

    auto co_pop_back = [](auto &bufa, auto &bufb){
        bufa.pop_back();
        bufb.pop_back();
    };

    auto co_erase = [](auto &bufa, auto &bufb){
        bufa.erase(bufa.begin() + 10);
        bufb.erase(bufb.begin() + 10);
    };

    auto co_clear = [](auto &bufa, auto &bufb){
        bufa.clear();
        bufb.clear();
    };

    auto co_shrink = [](auto &bufa, auto &bufb){
        bufa.shrink_to_fit();
        bufb.shrink_to_fit();
    };

    auto co_reserve = [](auto &bufa, auto &bufb){
        bufa.reserve(10000);
        bufb.reserve(10000);
    };

    using namespace std::placeholders;
    #define TEST(count, operation, desc) VECTOR_ASSERT_EQUIVALENCE(vcta, vctb, std::function<operation_t>( \
                                            std::bind(timed_func<operation_t, op_args_t>, desc, \
                                            std::function<operation_t>(std::bind(repeat<operation_t, op_args_t>, count, operation, _1, _2)), \
                                        _1, _2)))
    TEST(1000, co_push_back, "push1");
    TEST(1000000, co_push_back, "push2");
    TEST(9999, co_pop_back, "pop1");
    TEST(5432, co_push_back, "push3");
    TEST(123, co_pop_back, "pop2");
    TEST(1, co_erase, "erase1");
    TEST(66, co_push_back, "push4");
    TEST(543, co_erase, "erase2");
    TEST(2, co_clear, "clear1");
    TEST(3456, co_push_back, "push5");
    TEST(2, co_shrink, "shrink1");
    TEST(233, co_push_back, "push6");
    TEST(2, co_reserve, "reserve1");
    TEST(666, co_push_back, "push7");
    TEST(2, co_shrink, "shrink2");
    println("All tests done.");
    return 0;
}
