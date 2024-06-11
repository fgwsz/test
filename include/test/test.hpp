#pragma once
#include<string>//::std::string ::std::to_string
#include<functional>//::std::function
#include<sstream>//::std::ostringstream
namespace test{
void exec(void)noexcept;
void exec(::std::string const& case_name)noexcept;
namespace detail{
bool case_push(
    ::std::string const& case_name
    ,::std::function<void(void)> const& case_function
)noexcept;
void error_push(
    ::std::string const& file
    ,::std::string const& line
    ,::std::string const& check
)noexcept;
void assert_failed(
    ::std::string const& file
    ,::std::string const& line
    ,::std::string const& check
)noexcept;
void check_count_incement(void)noexcept;
void check_failed_count_increment(void)noexcept;
void check_passed_count_increment(void)noexcept;
}//namespace test::detail
}//namespace test
//public
#define TEST_CASE(case_name__)                             \
    static void test_case_function_of_##case_name__(void); \
    static bool test_case_register_of_##case_name__=       \
        ::test::detail::case_push(                         \
            #case_name__,                                  \
            ::std::function<void(void)>{                   \
                test_case_function_of_##case_name__        \
            }                                              \
        );                                                 \
    void test_case_function_of_##case_name__(void)         \
//
//public
#define TEST_CHECK(...) do{                                \
    ::test::detail::check_count_incement();                \
    if(!(__VA_ARGS__)){                                    \
        ::test::detail::check_failed_count_increment();    \
        ::test::detail::error_push(                        \
            __FILE__                                       \
            ,::std::to_string(__LINE__)                    \
            ,#__VA_ARGS__                                  \
        );                                                 \
    }else{                                                 \
        ::test::detail::check_passed_count_increment();    \
    }                                                      \
}while(0)                                                  \
//
//public
#define TEST_CHECK_OP(operator__,lhs__,rhs__) do{          \
    ::test::detail::check_count_incement();                \
    if(!((lhs__)operator__(rhs__))){                       \
        ::std::stringstream ss;                            \
        ss.str("");                                        \
        ss<<(lhs__);                                       \
        ::std::string lhs_string=ss.str();                 \
        ss.str("");                                        \
        ss<<(rhs__);                                       \
        ::std::string rhs_string=ss.str();                 \
        ::test::detail::check_failed_count_increment();    \
        ::test::detail::error_push(                        \
            __FILE__                                       \
            ,::std::to_string(__LINE__)                    \
            ,lhs_string+" "#operator__" "+rhs_string       \
        );                                                 \
    }else{                                                 \
        ::test::detail::check_passed_count_increment();    \
    }                                                      \
}while(0)                                                  \
//
//public
#define TEST_CHECK_EQ(lhs__,rhs__) TEST_CHECK_OP(==,lhs__,rhs__)
//public
#define TEST_CHECK_NE(lhs__,rhs__) TEST_CHECK_OP(!=,lhs__,rhs__)
//public
#define TEST_CHECK_GT(lhs__,rhs__) TEST_CHECK_OP(>,lhs__,rhs__)
//public
#define TEST_CHECK_GE(lhs__,rhs__) TEST_CHECK_OP(>=,lhs__,rhs__)
//public
#define TEST_CHECK_LT(lhs__,rhs__) TEST_CHECK_OP(<,lhs__,rhs__)
//public
#define TEST_CHECK_LE(lhs__,rhs__) TEST_CHECK_OP(<=,lhs__,rhs__)
//public
#define TEST_ASSERT(...) do{                               \
    if(!(__VA_ARGS__)){                                    \
        ::test::detail::assert_failed(                     \
            __FILE__                                       \
            ,::std::to_string(__LINE__)                    \
            ,#__VA_ARGS__                                  \
        );                                                 \
    }                                                      \
}while(0)                                                  \
//
//public
#define TEST_ASSERT_OP(operator__,lhs__,rhs__) do{         \
    if(!((lhs__)operator__(rhs__))){                       \
        ::std::stringstream ss;                            \
        ss.str("");                                        \
        ss<<(lhs__);                                       \
        ::std::string lhs_string=ss.str();                 \
        ss.str("");                                        \
        ss<<(rhs__);                                       \
        ::std::string rhs_string=ss.str();                 \
        ::test::detail::assert_failed(                     \
            __FILE__                                       \
            ,::std::to_string(__LINE__)                    \
            ,lhs_string+" "#operator__" "+rhs_string       \
        );                                                 \
    }                                                      \
}while(0)                                                  \
//
//public
#define TEST_ASSERT_EQ(lhs__,rhs__) TEST_ASSERT_OP(==,lhs__,rhs__)
//public
#define TEST_ASSERT_NE(lhs__,rhs__) TEST_ASSERT_OP(!=,lhs__,rhs__)
//public
#define TEST_ASSERT_GT(lhs__,rhs__) TEST_ASSERT_OP(>,lhs__,rhs__)
//public
#define TEST_ASSERT_GE(lhs__,rhs__) TEST_ASSERT_OP(>=,lhs__,rhs__)
//public
#define TEST_ASSERT_LT(lhs__,rhs__) TEST_ASSERT_OP(<,lhs__,rhs__)
//public
#define TEST_ASSERT_LE(lhs__,rhs__) TEST_ASSERT_OP(<=,lhs__,rhs__)
