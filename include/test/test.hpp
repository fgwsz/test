#ifndef __TEST_HPP__
#define __TEST_HPP__

#include<cstdio>//::std::FILE stdout
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
    ,::std::vector<::std::string/*element case name*/> const& group_body
)noexcept;
void execute_case(
    ::std::string const& case_name
    ,::std::FILE* output_stream=stdout
)noexcept;
void execute_group(
    ::std::string const& group_name
    ,::std::FILE* output_stream=stdout
)noexcept;
void execute_case_all(::std::FILE* output_stream=stdout)noexcept;
void execute_group_all(::std::FILE* output_stream=stdout)noexcept;
class Timer{
public:
    void start(void)noexcept;
    void stop(void)noexcept;
    double delta_nanoseconds(void)const noexcept;
    double delta_microseconds(void)const noexcept;
    double delta_milliseconds(void)const noexcept;
    double delta_seconds(void)const noexcept;
    double delta_minutes(void)const noexcept;
    double delta_hours(void)const noexcept;
    ::std::string delta_string(void)const noexcept;
private:
    using clock=::std::chrono::high_resolution_clock;
    using time_point=typename clock::time_point;
    time_point begin_,end_;
};
namespace detail{
void check_failed(
    ::std::string const& file
    ,::std::string const& line
    ,::std::string const& info
)noexcept;
void assert_failed(
    ::std::string const& file
    ,::std::string const& line
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
            #case_name__                                                     \
            ,test_case_function_of_##case_name__                             \
        );                                                                   \
    static void test_case_function_of_##case_name__(void)                    \
//
//public
#define TEST_GROUP(group_name__)                                             \
    static ::std::vector<::std::string> test_group_body_of_##group_name__={};\
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
//private
#define __TEST_STR_IMPL(...) #__VA_ARGS__
//public
#define TEST_STR(...) __TEST_STR_IMPL(__VA_ARGS__)
//public
#define TEST_CHECK(...) do{                                                  \
    ::test::detail::check_count_incement();                                  \
    if(!(__VA_ARGS__)){                                                      \
        ::test::detail::check_failed_count_increment();                      \
        ::test::detail::check_failed(                                        \
            __FILE__                                                         \
            ,TEST_STR(__LINE__)                                              \
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
        ::test::detail::check_failed_count_increment();                      \
        ::test::detail::check_failed(                                        \
            __FILE__                                                         \
            ,TEST_STR(__LINE__)                                              \
            ,(::std::ostringstream{}<<(lhs__)<<" "#operator__" "<<(rhs__))   \
                .str()                                                       \
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
            ,TEST_STR(__LINE__)                                              \
            ,#__VA_ARGS__                                                    \
        );                                                                   \
    }                                                                        \
}while(0)                                                                    \
//
//public
#define TEST_ASSERT_OP(operator__,lhs__,rhs__) do{                           \
    if(!((lhs__)operator__(rhs__))){                                         \
        ::test::detail::assert_failed(                                       \
            __FILE__                                                         \
            ,TEST_STR(__LINE__)                                              \
            ,(::std::ostringstream{}<<(lhs__)<<" "#operator__" "<<(rhs__))   \
                .str()                                                       \
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
//private
namespace test{
namespace detail{
template<bool condition__>
struct StaticCheckHelper{
    using type=unsigned char;
    static constexpr type value=((type)(-1));
};
template<>
struct StaticCheckHelper<false>{
    using type=unsigned int;
    static constexpr type value=
        static_cast<type>(StaticCheckHelper<true>::value)+1;
};
template<
    typename File__
    ,unsigned long long line__
    ,typename Info__
    ,bool condition__
>
struct StaticCheckImpl{
    static constexpr typename StaticCheckHelper<true>::type value=
        StaticCheckHelper<condition__>::value;
};
template<char...chars__>
struct StaticString{};
template<unsigned long long index__,unsigned long long size__>
static constexpr char char_array_at(char const(&char_array)[size__])noexcept{
    return char_array[index__<size__?index__:(size__-1)];
}
template<char...chars__>
auto static_string_trim_impl(StaticString<chars__...>)noexcept
->StaticString<chars__...>;
template<char...chars__,char...others__>
auto static_string_trim_impl(
    StaticString<chars__...>
    ,StaticString<'\0'>
    ,StaticString<others__>...
)noexcept
->StaticString<chars__...>;
template<char char__,char...chars__,char...others__>
auto static_string_trim_impl(
    StaticString<chars__...>
    ,StaticString<char__>
    ,StaticString<others__>...
)noexcept
->decltype(static_string_trim_impl(
    StaticString<chars__...,char__>{}
    ,StaticString<others__>{}...
));
template<char...chars__>
auto static_string_trim(StaticString<chars__...>)noexcept
->decltype(::test::detail::static_string_trim_impl(StaticString<chars__>{}...));
//private
#define __TEST_CHAR_SEQUENCE_16(n__,char_array__)                            \
    ::test::detail::char_array_at<0x##n__##0>(char_array__)                  \
    ,::test::detail::char_array_at<0x##n__##1>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##2>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##3>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##4>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##5>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##6>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##7>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##8>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##9>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##A>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##B>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##C>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##D>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##E>(char_array__)                 \
    ,::test::detail::char_array_at<0x##n__##F>(char_array__)                 \
//
//private
#define __TEST_CHAR_SEQUENCE_256(n__,char_array__)                           \
    __TEST_CHAR_SEQUENCE_16(n__##0,char_array__)                             \
    ,__TEST_CHAR_SEQUENCE_16(n__##1,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##2,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##3,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##4,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##5,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##6,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##7,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##8,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##9,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##A,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##B,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##C,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##D,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##E,char_array__)                            \
    ,__TEST_CHAR_SEQUENCE_16(n__##F,char_array__)                            \
//
//private
#define __TEST_CHAR_SEQUENCE(char_array__)                                   \
    __TEST_CHAR_SEQUENCE_256(0,char_array__)                                 \
//
//private
#define __TEST_MAKE_STATIC_STRING(char_array__)                              \
    decltype(::test::detail::static_string_trim(                             \
        ::test::detail::StaticString<                                        \
            __TEST_CHAR_SEQUENCE(char_array__)                               \
        >{}                                                                  \
    ))                                                                       \
//
}//namespace test::detail
}//namespace test
//public
#define TEST_STATIC_CHECK(...)                                               \
     extern decltype(::test::detail::StaticCheckImpl<                        \
        __TEST_MAKE_STATIC_STRING(__FILE__)                                  \
        ,__LINE__                                                            \
        ,__TEST_MAKE_STATIC_STRING(#__VA_ARGS__)                             \
        ,static_cast<bool>(__VA_ARGS__)                                      \
    >::value-0) test_static_check_expression                                 \
//
//public
#define TEST_STATIC_CHECK_NOT(...) TEST_STATIC_CHECK(!(__VA_ARGS__))
//public
#define TEST_STATIC_ASSERT(...) static_assert(                               \
    static_cast<bool>(__VA_ARGS__)                                           \
    ,__FILE__ "(" TEST_STR(__LINE__) "): " #__VA_ARGS__                      \
)                                                                            \
//
//public
#define TEST_STATIC_ASSERT_NOT(...) TEST_STATIC_ASSERT(!(__VA_ARGS__))

#endif//__TEST_HPP__
