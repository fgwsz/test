#ifndef __LOG_HPP__
#define __LOG_HPP__

#include<type_traits>//::std::enable_if

template<typename OutputStream,typename Type>
auto check_output(Type&& variable)->decltype(
    ::std::declval<OutputStream>()<<::std::forward<Type>(variable)
    ,::std::true_type
);
template<typename OutputStream,typename Type>
auto check_output(...)->::std::false_type;

template<typename OutputStream,typename Type>
OutputStream& operator<<(
    OutputStream& os
    ,Type&& value
    ,::std::enable_if_t<(decltype(),true),int>_=0
)noexcept{
}

#endif//__LOG_HPP__
