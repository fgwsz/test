#include"fgtest.h"
#include<cstddef>//::std::size_t
#include<iostream>//::std::cout
#include<vector>//::std::vector
#include<chrono>//::std::chrono
namespace fgtest{
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
    ::fgtest::__unit_names.push_back(unit_name);
    ::fgtest::__unit_functions.push_back(unit_function);
    ++::fgtest::__unit_count;
    return true;
}
void __throw_error(::std::runtime_error const& runtime_error)noexcept{
    ::fgtest::__unit_errors.push_back(runtime_error);
}
void __case_count_incement(void)noexcept{
    ++::fgtest::__case_count;
}
void __case_fail_count_increment(void)noexcept{
    ++::fgtest::__case_fail_count;
}
void __case_pass_count_increment(void)noexcept{
    ++::fgtest::__case_pass_count;
}
void exec(void)noexcept{
    ::std::chrono::high_resolution_clock::time_point start_time={};
    ::std::chrono::high_resolution_clock::time_point end_time={};
    double duration=0;
    ::std::string exception_string={};
    bool unit_is_pass=false;
    ::fgtest::__unit_errors.clear();
    for(
        ::std::size_t index=0;
        index<::fgtest::__unit_functions.size();
        ++index
    ){
        unit_is_pass=false;
        ::fgtest::__case_count=0;
        ::fgtest::__case_pass_count=0;
        ::fgtest::__case_fail_count=0;
        start_time=::std::chrono::high_resolution_clock::now();
        try{
            ::fgtest::__unit_functions[index]();
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
        unit_is_pass=exception_string.empty()&&::fgtest::__unit_errors.empty();
        ::std::cout<<"[FGTEST UNIT] "<<::fgtest::__unit_names[index]
            <<" ["<<(unit_is_pass?"PASS":"FAIL")<<"] ("<<duration<<" ms)\n";
        ::std::cout<<"\tcase:"<<::fgtest::__case_count<<","
            <<"pass:"<<::fgtest::__case_pass_count<<","
            <<"fail:"<<::fgtest::__case_fail_count<<","
            <<"jump:"<<::fgtest::__case_count-(
                ::fgtest::__case_pass_count+::fgtest::__case_fail_count
            )<<".\n";
        for(::std::size_t i=0;auto const& error: ::fgtest::__unit_errors){
            ::std::cout<<"\t<fail> "<<i<<"\n";
            ::std::cout<<error.what()<<"\n";
            ++i;
        }
        if(!exception_string.empty()){
            ::std::cout<<"\t<fail> "<<::fgtest::__unit_errors.size()<<"\n"
                <<"\t\t<exce> "<<exception_string<<"\n";
        }
        exception_string.clear();
        ::fgtest::__unit_errors.clear();
        if(unit_is_pass){
            ++::fgtest::__unit_pass_count;
        }else{
            ++::fgtest::__unit_fail_count;
        }
    }
    ::std::cout<<"[FGTEST TOTAL]\n";
    ::std::cout<<"\tunit:"<<::fgtest::__unit_count<<","
        <<"pass:"<<::fgtest::__unit_pass_count<<","
        <<"fail:"<<::fgtest::__unit_fail_count<<".\n";
}
void exec(std::string_view const& unit_name)noexcept{
    ::std::size_t index=0;
    for(auto const& name: ::fgtest::__unit_names){
        if(name==unit_name){
            break;
        }
        ++index;
    }
    if(index==::fgtest::__unit_names.size()){
        ::std::cout<<"[FGTEST UNIT] "<<unit_name<<" can't be found.";
        return;
    }
    ::std::chrono::high_resolution_clock::time_point start_time={};
    ::std::chrono::high_resolution_clock::time_point end_time={};
    double duration=0;
    ::std::string exception_string={};
    bool unit_is_pass=false;
    ::fgtest::__case_count=0;
    ::fgtest::__case_pass_count=0;
    ::fgtest::__case_fail_count=0;
    start_time=::std::chrono::high_resolution_clock::now();
    ::fgtest::__unit_errors.clear();
    try{
        ::fgtest::__unit_functions[index]();
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
    unit_is_pass=exception_string.empty()&&::fgtest::__unit_errors.empty();
    ::std::cout<<"[FGTEST UNIT] "<<::fgtest::__unit_names[index]
        <<" ["<<(unit_is_pass?"PASS":"FAIL")<<"] ("<<duration<<" ms)\n";
    ::std::cout<<"\tcase:"<<::fgtest::__case_count<<","
        <<"pass:"<<::fgtest::__case_pass_count<<","
        <<"fail:"<<::fgtest::__case_fail_count<<","
        <<"jump:"<<::fgtest::__case_count-(
            ::fgtest::__case_pass_count+::fgtest::__case_fail_count
        )<<".\n";
    for(::std::size_t i=0;auto const& error: ::fgtest::__unit_errors){
        ::std::cout<<"\t<fail> "<<i<<"\n";
        ::std::cout<<error.what()<<"\n";
        ++i;
    }
    if(!exception_string.empty()){
        ::std::cout<<"\t<fail> "<<::fgtest::__unit_errors.size()<<"\n"
            <<"\t\t<exce> "<<exception_string<<"\n";
    }
    ::fgtest::__unit_errors.clear();
}
}//namespace fgtest
