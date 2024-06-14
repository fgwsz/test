#ifndef __TEST_TEST_HPP__
#define __TEST_TEST_HPP__

#include<cstdio>//::std::FILE ::std::fopen ::std::printf ::std::fclose
#include<stdexcept>//::std::runtime_error
#include"test/test.hpp"

TEST_CASE(c_str_exception){
    throw "c_str exception";
}
TEST_CASE(string_exception){
    throw "string exception";
}
TEST_CASE(std_exception){
    throw ::std::runtime_error{"std::exception"};
}
TEST_CASE(unknown_exception){
    struct Foo{};
    throw Foo{};
}
TEST_CASE(empty_c_str_exception){
    throw "";
}
TEST_CASE(empty_string_exception){
    throw ::std::string{""};
}
TEST_CASE(empty_std_exception){
    throw ::std::runtime_error{""};
}
TEST_CASE(check_passed){
    TEST_CHECK(1==1);
    TEST_CHECK(2!=1);
    TEST_CHECK(2>1);
    TEST_CHECK(2>=1);
    TEST_CHECK(2>=2);
    TEST_CHECK(1<2);
    TEST_CHECK(1<=2);
    TEST_CHECK(1<=1);
    TEST_CHECK_OP(==,1,1);
    TEST_CHECK_OP(!=,2,1);
    TEST_CHECK_OP(>,2,1);
    TEST_CHECK_OP(>=,2,1);
    TEST_CHECK_OP(>=,2,2);
    TEST_CHECK_OP(<,1,2);
    TEST_CHECK_OP(<=,1,2);
    TEST_CHECK_OP(<=,1,1);
    TEST_CHECK_EQ(1,1);
    TEST_CHECK_NE(2,1);
    TEST_CHECK_GT(2,1);
    TEST_CHECK_GE(2,1);
    TEST_CHECK_GE(2,2);
    TEST_CHECK_LT(1,2);
    TEST_CHECK_LE(1,2);
    TEST_CHECK_LE(1,1);
    TEST_CHECK_AND(true,true);
    TEST_CHECK_OR(false,true);
    TEST_CHECK_NOT(false);
}
TEST_CASE(check_failed){
    TEST_CHECK(!(1==1));
    TEST_CHECK(!(2!=1));
    TEST_CHECK(!(2>1));
    TEST_CHECK(!(2>=1));
    TEST_CHECK(!(2>=2));
    TEST_CHECK(!(1<2));
    TEST_CHECK(!(1<=2));
    TEST_CHECK(!(1<=1));
    TEST_CHECK_OP(==,2,1);
    TEST_CHECK_OP(!=,1,1);
    TEST_CHECK_OP(>,2,2);
    TEST_CHECK_OP(>=,1,2);
    TEST_CHECK_OP(<,1,1);
    TEST_CHECK_OP(<=,2,1);
    TEST_CHECK_EQ(2,1);
    TEST_CHECK_NE(1,1);
    TEST_CHECK_GT(2,2);
    TEST_CHECK_GE(1,2);
    TEST_CHECK_LT(1,1);
    TEST_CHECK_LE(2,1);
    TEST_CHECK_AND(true,false);
    TEST_CHECK_OR(false,false);
    TEST_CHECK_NOT(true);
}
TEST_CASE(assert_passed){
    TEST_ASSERT(1==1);
    TEST_ASSERT(2!=1);
    TEST_ASSERT(2>1);
    TEST_ASSERT(2>=1);
    TEST_ASSERT(2>=2);
    TEST_ASSERT(1<2);
    TEST_ASSERT(1<=2);
    TEST_ASSERT(1<=1);
    TEST_ASSERT_OP(==,1,1);
    TEST_ASSERT_OP(!=,2,1);
    TEST_ASSERT_OP(>,2,1);
    TEST_ASSERT_OP(>=,2,1);
    TEST_ASSERT_OP(>=,2,2);
    TEST_ASSERT_OP(<,1,2);
    TEST_ASSERT_OP(<=,1,2);
    TEST_ASSERT_OP(<=,1,1);
    TEST_ASSERT_EQ(1,1);
    TEST_ASSERT_NE(2,1);
    TEST_ASSERT_GT(2,1);
    TEST_ASSERT_GE(2,1);
    TEST_ASSERT_GE(2,2);
    TEST_ASSERT_LT(1,2);
    TEST_ASSERT_LE(1,2);
    TEST_ASSERT_LE(1,1);
    TEST_ASSERT_AND(true,true);
    TEST_ASSERT_OR(false,true);
    TEST_ASSERT_NOT(false);
}
TEST_CASE(assert_failed){
    TEST_CHECK(1==1);
    TEST_CHECK(2!=1);
    //TEST_ASSERT(!(1==1));
    //TEST_ASSERT(!(2!=1));
    //TEST_ASSERT(!(2>1));
    //TEST_ASSERT(!(2>=1));
    //TEST_ASSERT(!(2>=2));
    //TEST_ASSERT(!(1<2));
    //TEST_ASSERT(!(1<=2));
    //TEST_ASSERT(!(1<=1));
    //TEST_ASSERT_OP(==,2,1);
    //TEST_ASSERT_OP(!=,1,1);
    //TEST_ASSERT_OP(>,2,2);
    //TEST_ASSERT_OP(>=,1,2);
    //TEST_ASSERT_OP(<,1,1);
    //TEST_ASSERT_OP(<=,2,1);
    //TEST_ASSERT_EQ(2,1);
    //TEST_ASSERT_NE(1,1);
    //TEST_ASSERT_GT(2,2);
    //TEST_ASSERT_GE(1,2);
    //TEST_ASSERT_LT(1,1);
    //TEST_ASSERT_LE(2,1);
    TEST_ASSERT_AND(true,false);
    //TEST_ASSERT_OR(false,false);
    //TEST_ASSERT_NOT(true);
}
TEST_CASE(static_assert_passed){
    TEST_STATIC_ASSERT(1+1==2);
    TEST_STATIC_ASSERT_NOT(1+1==3);
}
TEST_CASE(static_assert_failed){
    //TEST_STATIC_ASSERT(1+1==3);
    //TEST_STATIC_ASSERT_NOT(1+1==2);
}
TEST_GROUP(passed_group){
    TEST_GROUP_ELEMENT(check_passed);
    TEST_GROUP_ELEMENT(assert_passed);
    TEST_GROUP_ELEMENT(static_assert_passed);
}
TEST_GROUP(failed_group){
    TEST_GROUP_ELEMENT(c_str_exception);
    TEST_GROUP_ELEMENT(string_exception);
    TEST_GROUP_ELEMENT(std_exception);
    TEST_GROUP_ELEMENT(unknown_exception);
    TEST_GROUP_ELEMENT(empty_c_str_exception);
    TEST_GROUP_ELEMENT(empty_string_exception);
    TEST_GROUP_ELEMENT(empty_std_exception);
    TEST_GROUP_ELEMENT(check_failed);
    TEST_GROUP_ELEMENT(assert_failed);
    TEST_GROUP_ELEMENT(static_assert_failed);
    TEST_GROUP_ELEMENT(undefined);
}
void test_console_output(void)noexcept{
    ::test::execute_case("check_passed");
    ::test::execute_case("undefined");
    ::test::execute_case_all();
    ::test::execute_group("passed_group");
    ::test::execute_group("undefined");
    ::test::execute_group_all();
}
void test_file_output(void)noexcept{
    char const* file_path="output.txt";
    ::std::FILE* output_stream=::std::fopen(file_path,"w");
    if(!output_stream){
        ::std::printf("Output file \"%s\" failed to open.\n",file_path);
    }
    ::std::printf("Output file \"%s\" opened successfully.\n",file_path);
    ::test::execute_case("check_passed",output_stream);
    ::test::execute_case("undefined",output_stream);
    ::test::execute_case_all(output_stream);
    ::test::execute_group("passed_group",output_stream);
    ::test::execute_group("undefined",output_stream);
    ::test::execute_group_all(output_stream);
    ::std::fclose(output_stream);
    ::std::printf("Output file \"%s\" written successfully.\n",file_path);
}

#endif//__TEST_TEST_HPP__
