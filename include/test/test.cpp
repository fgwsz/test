#include<test/test.h>
#include<cstddef>//::std::size_t
#include<iostream>//::std::cout
#include<vector>//::std::vector
#include<chrono>//::std::chrono
namespace test{
static ::std::vector<::std::string_view> __unit_names={};
static ::std::vector<::std::function<void(void)>> __unit_functions={};
static ::std::vector<::std::runtime_error> __unit_errors={};
static ::std::size_t __unit_count=0;
static ::std::size_t __unit_fail_count=0;
static ::std::size_t __unit_pass_count=0;
static ::std::size_t __case_count=0;
static ::std::size_t __case_fail_count=0;
static ::std::size_t __case_pass_count=0;
bool __unit_add(
    ::std::string_view const& unit_name,
    ::std::function<void(void)> const& unit_function
)noexcept{
    ::test::__unit_names.push_back(unit_name);
    ::test::__unit_functions.push_back(unit_function);
    ++::test::__unit_count;
    return true;
}
void __throw_error(::std::runtime_error const& runtime_error)noexcept{
    ::test::__unit_errors.push_back(runtime_error);
}
void __case_count_incement(void)noexcept{
    ++::test::__case_count;
}
void __case_fail_count_increment(void)noexcept{
    ++::test::__case_fail_count;
}
void __case_pass_count_increment(void)noexcept{
    ++::test::__case_pass_count;
}
void exec(void)noexcept{
    ::std::chrono::high_resolution_clock::time_point start_time={};
    ::std::chrono::high_resolution_clock::time_point end_time={};
    double duration=0;
    ::std::string exception_string={};
    bool unit_is_pass=false;
    ::test::__unit_errors.clear();
    for(
        ::std::size_t index=0;
        index<::test::__unit_functions.size();
        ++index
    ){
        unit_is_pass=false;
        ::test::__case_count=0;
        ::test::__case_pass_count=0;
        ::test::__case_fail_count=0;
        start_time=::std::chrono::high_resolution_clock::now();
        try{
            ::test::__unit_functions[index]();
        }catch(::std::exception const& exception){
            exception_string=exception.what();
        }catch(::std::string const& string){
            exception_string=string;
        }catch(::std::string_view const& string_view){
            exception_string=string_view;
        }catch(char const* c_str){
            exception_string=c_str;
        }catch(...){
            exception_string="unknown exception!";
        }
        end_time=::std::chrono::high_resolution_clock::now();
        duration=::std::chrono::duration_cast<::std::chrono::duration<double>>(
                end_time-start_time
            ).count()*1000;//ms
        unit_is_pass=exception_string.empty()&&::test::__unit_errors.empty();
        ::std::cout<<"[test::UNIT] "<<::test::__unit_names[index]
            <<" ["<<(unit_is_pass?"PASS":"FAIL")<<"] ("<<duration<<" ms)\n";
        ::std::cout<<"\tcase:"<<::test::__case_count<<","
            <<"pass:"<<::test::__case_pass_count<<","
            <<"fail:"<<::test::__case_fail_count<<".\n";
        for(::std::size_t i=0;auto const& error: ::test::__unit_errors){
            ::std::cout<<"\t<fail> "<<i<<"\n";
            ::std::cout<<error.what()<<"\n";
            ++i;
        }
        if(!exception_string.empty()){
            ::std::cout<<"\t<fail> "<<::test::__unit_errors.size()<<"\n"
                <<"\t\t<exce> "<<exception_string<<"\n";
        }
        exception_string.clear();
        ::test::__unit_errors.clear();
        if(unit_is_pass){
            ++::test::__unit_pass_count;
        }else{
            ++::test::__unit_fail_count;
        }
    }
    ::std::cout<<"[test::TOTAL]\n";
    ::std::cout<<"\tunit:"<<::test::__unit_count<<","
        <<"pass:"<<::test::__unit_pass_count<<","
        <<"fail:"<<::test::__unit_fail_count<<".\n";
}
void exec(std::string_view const& unit_name)noexcept{
    ::std::size_t index=0;
    for(auto const& name: ::test::__unit_names){
        if(name==unit_name){
            break;
        }
        ++index;
    }
    if(index==::test::__unit_names.size()){
        ::std::cout<<"[test::UNIT] "<<unit_name<<" can't be found.\n";
        return;
    }
    ::std::chrono::high_resolution_clock::time_point start_time={};
    ::std::chrono::high_resolution_clock::time_point end_time={};
    double duration=0;
    ::std::string exception_string={};
    bool unit_is_pass=false;
    ::test::__case_count=0;
    ::test::__case_pass_count=0;
    ::test::__case_fail_count=0;
    start_time=::std::chrono::high_resolution_clock::now();
    ::test::__unit_errors.clear();
    try{
        ::test::__unit_functions[index]();
    }catch(::std::exception const& exception){
        exception_string=exception.what();
    }catch(::std::string const& string){
        exception_string=string;
    }catch(::std::string_view const& string_view){
        exception_string=string_view;
    }catch(char const* c_str){
        exception_string=c_str;
    }catch(...){
        exception_string="unknown exception.";
    }
    end_time=::std::chrono::high_resolution_clock::now();
    duration=::std::chrono::duration_cast<::std::chrono::duration<double>>(
            end_time-start_time
        ).count()*1000;//ms
    unit_is_pass=exception_string.empty()&&::test::__unit_errors.empty();
    ::std::cout<<"[test::UNIT] "<<::test::__unit_names[index]
        <<" ["<<(unit_is_pass?"PASS":"FAIL")<<"] ("<<duration<<" ms)\n";
    ::std::cout<<"\tcase:"<<::test::__case_count<<","
        <<"pass:"<<::test::__case_pass_count<<","
        <<"fail:"<<::test::__case_fail_count<<".\n";
    for(::std::size_t i=0;auto const& error: ::test::__unit_errors){
        ::std::cout<<"\t<fail> "<<i<<"\n";
        ::std::cout<<error.what()<<"\n";
        ++i;
    }
    if(!exception_string.empty()){
        ::std::cout<<"\t<fail> "<<::test::__unit_errors.size()<<"\n"
            <<"\t\t<exce> "<<exception_string<<"\n";
    }
    ::test::__unit_errors.clear();
}
}//namespace test
