#ifndef __TEST_TEST_STATIC_HPP__
#define __TEST_TEST_STATIC_HPP__
#include"test.hpp"
void foo(void)noexcept{
    TEST_STATIC_CHECK(1+1==3);
    TEST_STATIC_CHECK_NOT(1+1==2);
}
#if TEST_HAS_COUNTER
    TEST_STATIC_CHECK(1+1==3);
    TEST_STATIC_CHECK_NOT(1+1==2);
#endif//TEST_HAS_COUNTER
#endif//__TEST_TEST_STATIC_HPP__
