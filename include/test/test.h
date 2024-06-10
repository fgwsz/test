#pragma once
#include<string_view>//::std::string_view
#include<functional>//::std::function
#include<stdexcept>//::std::runtime_error
#include<string>//::std::string ::std::to_string
namespace test{
void exec(void)noexcept;
void exec(std::string_view const& unit_name)noexcept;
namespace detail{
bool unit_add(
    ::std::string_view const& unit_name,
    ::std::function<void(void)> const& unit_function
)noexcept;
void throw_error(::std::runtime_error const& runtime_error)noexcept;
void case_count_incement(void)noexcept;
void case_fail_count_increment(void)noexcept;
void case_pass_count_increment(void)noexcept;
}//namespace test::detail
}//namespace test
//public
#define TEST_UNIT(unit_name__) \
    static void test_unit_function_of_##unit_name__(void); \
    static bool test_unit_register_of_##unit_name__= \
    ::test::detail::unit_add( \
        #unit_name__, \
        ::std::function<void(void)>{ \
            test_unit_function_of_##unit_name__ \
        } \
    ); \
    void test_unit_function_of_##unit_name__(void) \
//
//public
#define TEST_CASE(...) do{ \
    ::test::detail::case_count_incement(); \
    if(!(__VA_ARGS__)){ \
        ::test::detail::case_fail_count_increment(); \
        ::test::detail::throw_error(::std::runtime_error( \
            "\t\t<file> "+::std::string(__FILE__)+"\n" \
            "\t\t<line> "+::std::to_string(__LINE__)+"\n" \
            "\t\t<case> "+::std::string(#__VA_ARGS__) \
        )); \
    }else{ \
        ::test::detail::case_pass_count_increment(); \
    } \
}while(0) \
//
