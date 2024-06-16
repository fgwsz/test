#ifndef __TEST_TEST_STATIC_HPP__
#define __TEST_TEST_STATIC_HPP__
#include"test/test.hpp"
void foo(void)noexcept{
    TEST_STATIC_CHECK(-2==0);TEST_STATIC_CHECK(-2==1);
    TEST_STATIC_CHECK(-2==2);
}
TEST_STATIC_CHECK(-2==3);TEST_STATIC_CHECK(-2==4);
TEST_STATIC_CHECK(-2==5);
#endif//__TEST_TEST_STATIC_HPP__
