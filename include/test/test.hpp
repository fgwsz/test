#pragma once
#include<cstddef>//::std::size_t
#include<string>//::std::string
#include<functional>//::std::function
#include<vector>//::std::vector
#include<chrono>//::std::chrono
#include<sstream>//::std::ostringstream
namespace test{
bool case_register(
    ::std::string const& case_name
    ,::std::function<void(void)> const& case_function
)noexcept;
bool group_register(
    ::std::string const& group_name
    ,::std::vector<::std::string> const& group_body
)noexcept;
void execute_case(::std::string const& case_name)noexcept;
void execute_group(::std::string const& group_name)noexcept;
void execute_case_all(void)noexcept;
void execute_group_all(void)noexcept;
class Timer{
public:
    void start(void)noexcept;
    void stop(void)noexcept;
    double delta_nanoseconds(void)noexcept;
    double delta_microseconds(void)noexcept;
    double delta_milliseconds(void)noexcept;
    double delta_seconds(void)noexcept;
    double delta_minutes(void)noexcept;
    double delta_hours(void)noexcept;
private:
    using clock=::std::chrono::high_resolution_clock;
    using time_point=typename clock::time_point;
    time_point begin_,end_;
};
namespace detail{
void check_failed(
    ::std::string const& file
    ,::std::size_t line
    ,::std::string const& info
)noexcept;
void assert_failed(
    ::std::string const& file
    ,::std::size_t line
    ,::std::string const& info
);
void check_count_incement(void)noexcept;
void check_failed_count_increment(void)noexcept;
void check_passed_count_increment(void)noexcept;
}//namespace test::detail
}//namespace test
//public
#define TEST_CASE(case_name__)                                               \
    static void test_case_function_of_##case_name__(void);                   \
    static bool test_case_is_registered_of_##case_name__=                    \
        ::test::case_register(                                               \
            #case_name__,                                                    \
            ::std::function<void(void)>{                                     \
                test_case_function_of_##case_name__                          \
            }                                                                \
        );                                                                   \
    void test_case_function_of_##case_name__(void)                           \
//
//public
#define TEST_GROUP(group_name__)                                             \
    static ::std::vector<::std::string>                                      \
        test_group_body_of_##group_name__={};                                \
    static void test_group_init_of_##group_name__(                           \
        ::std::vector<::std::string>& group=                                 \
            test_group_body_of_##group_name__                                \
    )noexcept;                                                               \
    static bool test_group_is_registered_of_##group_name__=[](void)noexcept{ \
        test_group_init_of_##group_name__();                                 \
        return ::test::group_register(                                       \
            #group_name__                                                    \
            ,test_group_body_of_##group_name__                               \
        );                                                                   \
    }();                                                                     \
    static void test_group_init_of_##group_name__(                           \
        ::std::vector<::std::string>& group                                  \
    )noexcept                                                                \
//
//public
#define TEST_GROUP_ELEMENT(case_name__) do{                                  \
    group.emplace_back(#case_name__);                                        \
}while(0)                                                                    \
//
//public
#define TEST_CHECK(...) do{                                                  \
    ::test::detail::check_count_incement();                                  \
    if(!(__VA_ARGS__)){                                                      \
        ::test::detail::check_failed_count_increment();                      \
        ::test::detail::check_failed(                                        \
            __FILE__                                                         \
            ,__LINE__                                                        \
            ,#__VA_ARGS__                                                    \
        );                                                                   \
    }else{                                                                   \
        ::test::detail::check_passed_count_increment();                      \
    }                                                                        \
}while(0)                                                                    \
//
//public
#define TEST_CHECK_OP(operator__,lhs__,rhs__) do{                            \
    ::test::detail::check_count_incement();                                  \
    if(!((lhs__)operator__(rhs__))){                                         \
        ::std::stringstream ss;                                              \
        ss.str("");                                                          \
        ss<<(lhs__);                                                         \
        ::std::string lhs_string=ss.str();                                   \
        ss.str("");                                                          \
        ss<<(rhs__);                                                         \
        ::std::string rhs_string=ss.str();                                   \
        ::test::detail::check_failed_count_increment();                      \
        ::test::detail::check_failed(                                        \
            __FILE__                                                         \
            ,__LINE__                                                        \
            ,lhs_string+" "#operator__" "+rhs_string                         \
        );                                                                   \
    }else{                                                                   \
        ::test::detail::check_passed_count_increment();                      \
    }                                                                        \
}while(0)                                                                    \
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
#define TEST_CHECK_AND(lhs__,rhs__) TEST_CHECK_OP(&&,lhs__,rhs__)
//public
#define TEST_CHECK_OR(lhs__,rhs__) TEST_CHECK_OP(||,lhs__,rhs__)
//public
#define TEST_CHECK_NOT(...) TEST_CHECK(!(__VA_ARGS__))
//public
#define TEST_ASSERT(...) do{                                                 \
    if(!(__VA_ARGS__)){                                                      \
        ::test::detail::assert_failed(                                       \
            __FILE__                                                         \
            ,__LINE__                                                        \
            ,#__VA_ARGS__                                                    \
        );                                                                   \
    }                                                                        \
}while(0)                                                                    \
//
//public
#define TEST_ASSERT_OP(operator__,lhs__,rhs__) do{                           \
    if(!((lhs__)operator__(rhs__))){                                         \
        ::std::stringstream ss;                                              \
        ss.str("");                                                          \
        ss<<(lhs__);                                                         \
        ::std::string lhs_string=ss.str();                                   \
        ss.str("");                                                          \
        ss<<(rhs__);                                                         \
        ::std::string rhs_string=ss.str();                                   \
        ::test::detail::assert_failed(                                       \
            __FILE__                                                         \
            ,__LINE__                                                        \
            ,lhs_string+" "#operator__" "+rhs_string                         \
        );                                                                   \
    }                                                                        \
}while(0)                                                                    \
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
//public
#define TEST_ASSERT_AND(lhs__,rhs__) TEST_ASSERT_OP(&&,lhs__,rhs__)
//public
#define TEST_ASSERT_OR(lhs__,rhs__) TEST_ASSERT_OP(||,lhs__,rhs__)
//public
#define TEST_ASSERT_NOT(...) TEST_ASSERT(!(__VA_ARGS__))
