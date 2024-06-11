#pragma once
#include<string>//::std::string ::std::to_string
#include<functional>//::std::function
namespace test{
void exec(void)noexcept;
void exec(::std::string const& unit_name)noexcept;
namespace detail{
bool unit_push(
    ::std::string const& unit_name
    ,::std::function<void(void)> const& unit_function
)noexcept;
void error_push(
    ::std::string const& file
    ,::std::string const& line
    ,::std::string const& expr
)noexcept;
void expr_count_incement(void)noexcept;
void expr_fail_count_increment(void)noexcept;
void expr_pass_count_increment(void)noexcept;
}//namespace test::detail
}//namespace test
//public
#define TEST_UNIT(unit_name__)                             \
    static void test_unit_function_of_##unit_name__(void); \
    static bool test_unit_register_of_##unit_name__=       \
        ::test::detail::unit_push(                         \
            #unit_name__,                                  \
            ::std::function<void(void)>{                   \
                test_unit_function_of_##unit_name__        \
            }                                              \
        );                                                 \
    void test_unit_function_of_##unit_name__(void)         \
//
//public
#define TEST_EXPR(...) do{                                 \
    ::test::detail::expr_count_incement();                 \
    if(!(__VA_ARGS__)){                                    \
        ::test::detail::expr_fail_count_increment();       \
        ::test::detail::error_push(                        \
            __FILE__                                       \
            ,::std::to_string(__LINE__)                    \
            ,#__VA_ARGS__                                  \
        );                                                 \
    }else{                                                 \
        ::test::detail::expr_pass_count_increment();       \
    }                                                      \
}while(0)                                                  \
//
