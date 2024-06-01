#pragma once
#include<string_view>//::std::string_view
#include<functional>//::std::function
#include<stdexcept>//::std::runtime_error
#include<string>//::std::string ::std::to_string
namespace test{
//public
void exec(void)noexcept;
//public
void exec(std::string_view const& unit_name)noexcept;
//private
bool __unit_add(
    ::std::string_view const& unit_name,
    ::std::function<void(void)> const& unit_function
)noexcept;
//private
void __throw_error(::std::runtime_error const& runtime_error)noexcept;
//private
void __case_count_incement(void)noexcept;
//private
void __case_fail_count_increment(void)noexcept;
//private
void __case_pass_count_increment(void)noexcept;
}//namespace test
//private
#define __TEST_UNIT_FUNCTION_NAME(__UNIT_NAME__) \
    __test_unit_function_of_##__UNIT_NAME__ \
//
//private
#define __TEST_UNIT_ADD(__UNIT_NAME__) \
    static bool __test_unit_register_of_##__UNIT_NAME__= \
    ::test::__unit_add( \
        #__UNIT_NAME__, \
        ::std::function<void(void)>{ \
            __TEST_UNIT_FUNCTION_NAME(__UNIT_NAME__) \
        } \
    ) \
//
//private
#define __TEST_THROW_ERROR(__CASE__) do { \
    ::test::__throw_error(::std::runtime_error( \
        "\t\t<file> "+::std::string(__FILE__)+"\n" \
        "\t\t<line> "+::std::to_string(__LINE__)+"\n" \
        "\t\t<case> "+__CASE__ \
    )); \
}while(0) \
//
//public
#define TEST_UNIT(__UNIT_NAME__) \
    static void __TEST_UNIT_FUNCTION_NAME(__UNIT_NAME__)(void); \
    __TEST_UNIT_ADD(__UNIT_NAME__); \
    void __TEST_UNIT_FUNCTION_NAME(__UNIT_NAME__)(void) \
//
//public
#define TEST_CASE(...) do{ \
    ::test::__case_count_incement(); \
    if(!(__VA_ARGS__)){ \
        ::test::__case_fail_count_increment(); \
        __TEST_THROW_ERROR(#__VA_ARGS__); \
    }else{ \
        ::test::__case_pass_count_increment(); \
    } \
}while(0) \
//
