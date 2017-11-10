//////////////////////////////////////////////////BEGIN RLIB
#ifndef R_PRINT_HPP
#define R_PRINT_HPP

#include <iostream>

namespace rlib {
	template<typename PrintFinalT>
	void print(PrintFinalT reqArg)
	{
		::std::cout << reqArg;
		return;
	}
	template<typename Required, typename... Optional>
	void print(Required reqArgs, Optional... optiArgs)
	{
		::std::cout << reqArgs << ' ';
		print(optiArgs ...);
		return;
	}
	template<typename... Optional>
	void println(Optional... optiArgs)
	{
		print(optiArgs ...);
		::std::cout << ::std::endl;
		return;
	}

	template<typename Iterable, typename Printable>
	void print_iter(Iterable arg, Printable spliter)
	{
        for(const auto & i : arg)
		    ::std::cout << i << spliter;
		return;
	}
	template<typename Iterable, typename Printable>
	void println_iter(Iterable arg, Printable spliter)
	{
		print_iter(arg, spliter);
		::std::cout << ::std::endl;
		return;
	}
    template<typename Iterable>
	void print_iter(Iterable arg)
	{
        for(const auto & i : arg)
		    ::std::cout << i << ' ';
		return;
	}
	template<typename Iterable>
	void println_iter(Iterable arg)
	{
		print_iter(arg);
		::std::cout << ::std::endl;
		return;
	}
}
#endif


#ifndef RLIB_ADV_CALLABLE
#define RLIB_ADV_CALLABLE

#include <type_traits>

namespace rlib {
    template<typename T>
    struct is_callable_helper {
    private:
        typedef char(&yes)[1];
        typedef char(&no)[2];

        struct Fallback { void operator()(); };
        struct Derived : T, Fallback { };

        template<typename U, U> struct Check;

        template<typename>
        static yes test(...);

        template<typename C>
        static no test(Check<void (Fallback::*)(), &C::operator()>*);

    public:
        static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
    };
    template<typename T>
    struct is_callable
        : std::conditional<
            std::is_class<T>::value,
            is_callable_helper<T>,
            std::is_function<T>>::type
    {};
}
#endif
////////////////////////////////////////////////////

#include <cstdlib>
#define dynamic_assert(cond, message) do { \
        if(!cond) { \
            rlib::println("dynamic assertion failed:", message); \
            std::exit(2); \
        } \
    } while(false)

// -- operation must be a templated callable object, usually templated lambda.
// NEW: operation must fuck two buf at same time.
#define ASSERT_EQUIVALENCE(bufA, bufB, operation, equal_checker) \
    do { \
        static_assert(std::is_same<rlib::is_callable<decltype(equal_checker<double>)>::type, \
                    std::true_type>::value, \
                    "equal_checker is not callable"); \
        dynamic_assert(equal_checker(bufA, bufB), "given buf is not equal."); \
        operation(bufA, bufB); \
        dynamic_assert(equal_checker(bufA, bufB), "operation failed."); \
    } while(false)

//vector
#include "lab_vector.hpp"
#include <vector>

template<typename data_t>
bool vector_equal(const Lab::vector<data_t> &vcta, const std::vector<data_t> &vctb)
{
    if(vcta.size() != vctb.size()) return false;
    Lab::vector<data_t> &fake_vcta = const_cast<Lab::vector<data_t> &>(vcta);
    for(auto ia = fake_vcta.begin(), ib = vctb.begin();
        ia != fake_vcta.end() && ib != vctb.end();
        ++ia, ++ib)
        {
            if(*ia != *ib) return false;
        }
    return true;
}
#define VECTOR_ASSERT_EQUIVALENCE(bufA, bufB, operation) ASSERT_EQUIVALENCE(bufA, bufB, operation, vector_equal)



