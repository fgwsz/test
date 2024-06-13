#include"test.hpp"
#include<cstddef>//::std::size_t
#include<cstdio>//::std::printf
#include<cmath>//::std::floor
#include<ratio>//::std::ratio
#include<unordered_map>//::std::unordered_map
#include<exception>//::std::exception

namespace test{
namespace detail{
class CheckFailedException:public ::std::exception{
    ::std::string file_,line_,info_,what_;
public:
    CheckFailedException(
        ::std::string const& file,::std::string const& line
        ,::std::string const& info
    )noexcept
    :file_(file),line_(line),info_(info){
        this->what_=this->file_+"("+this->line_+"): "+this->info_;
    }
    virtual char const* what(void)const noexcept override{
        return this->what_.c_str();
    }
    ::std::string const& file(void)const noexcept{
        return this->file_;
    }
    ::std::string const& line(void)const noexcept{
        return this->line_;
    }
    ::std::string const& info(void)const noexcept{
        return this->info_;
    }
};
class AssertFailedException:public ::std::exception{
    ::std::string file_,line_,info_,what_;
public:
    AssertFailedException(
        ::std::string const& file,::std::string const& line
        ,::std::string const& info
    )noexcept
    :file_(file),line_(line),info_(info){
        this->what_=this->file_+"("+this->line_+"): "+this->info_;
    }
    virtual char const* what()const noexcept override{
        return this->what_.c_str();
    }
    ::std::string const& file(void)const noexcept{
        return this->file_;
    }
    ::std::string const& line(void)const noexcept{
        return this->line_;
    }
    ::std::string const& info(void)const noexcept{
        return this->info_;
    }
};
static ::std::vector<::std::string> case_names={};
static ::std::vector<::std::function<void(void)>> case_functions={};
static ::std::vector<::test::detail::CheckFailedException> case_errors={};
static ::std::unordered_map<::std::string,::std::size_t>
    case_name_to_index={};
static ::std::vector<::std::string> group_names={};
static ::std::vector<::std::vector<::std::string>> group_bodys={};
static ::std::unordered_map<::std::string,::std::size_t>
    group_name_to_index={};
static ::std::size_t check_count=0;
static ::std::size_t check_failed_count=0;
static ::std::size_t check_passed_count=0;
}//namespace test::detail
bool case_register(
    ::std::string const& case_name,
    ::std::function<void(void)> const& case_function
)noexcept{
    if(::test::detail::case_name_to_index.count(case_name)!=0){
        return false;
    }
    ::test::detail::case_names.emplace_back(case_name);
    ::test::detail::case_functions.emplace_back(case_function);
    ::test::detail::case_name_to_index.emplace(
        case_name,::test::detail::case_name_to_index.size()
    );
    return true;
}
bool group_register(
    ::std::string const& group_name
    ,::std::vector<::std::string> const& group_body
)noexcept{
    if(::test::detail::group_name_to_index.count(group_name)!=0){
        return false;
    }
    ::test::detail::group_names.emplace_back(group_name);
    ::test::detail::group_bodys.emplace_back(group_body);
    ::test::detail::group_name_to_index.emplace(
        group_name,::test::detail::group_name_to_index.size()
    );
    return true;
}
namespace detail{
    template<typename Period,typename TimePoint>
    double delta(TimePoint const& begin,TimePoint const& end)noexcept{
        return ::std::chrono::duration_cast<
            ::std::chrono::duration<double,Period>
        >(end-begin).count();
    }
}//namespace test::detail
void Timer::start(void)noexcept{
    this->begin_=Timer::clock::now();
}
void Timer::stop(void)noexcept{
    this->end_=Timer::clock::now();
}
double Timer::delta_nanoseconds(void)const noexcept{
    return ::test::detail::delta<::std::nano,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_microseconds(void)const noexcept{
    return ::test::detail::delta<::std::micro,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_milliseconds(void)const noexcept{
    return ::test::detail::delta<::std::milli,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_seconds(void)const noexcept{
    return ::test::detail::delta<::std::ratio<1>,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_minutes(void)const noexcept{
    return ::test::detail::delta<::std::ratio<60>,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_hours(void)const noexcept{
    return ::test::detail::delta<
            ::std::ratio<3600>,typename Timer::time_point
    >(this->begin_,this->end_);
}
namespace detail{
static ::std::string nanoseconds_to_string(double ns)noexcept{
    constexpr double c_1ns=1;
    constexpr double c_1us=1000*c_1ns;
    constexpr double c_1ms=1000*c_1us;
    constexpr double c_1s=1000*c_1ms;
    constexpr double c_1m=60*c_1s;
    constexpr double c_1h=60*c_1m;
    double integer=0;
    double others=0;
    if(ns>=c_1h){
        integer=::std::floor(ns/c_1h);
        others=ns-integer*c_1h;
        return ::std::to_string(static_cast<::std::size_t>(integer))+" h "
            +::test::detail::nanoseconds_to_string(others);
    }else if(ns>=c_1m){
        integer=::std::floor(ns/c_1m);
        others=ns-integer*c_1m;
        return ::std::to_string(static_cast<::std::size_t>(integer))+" m "
            +::test::detail::nanoseconds_to_string(others);
    }else if(ns>=c_1s){
        integer=::std::floor(ns/c_1s);
        others=ns-integer*c_1s;
        return ::std::to_string(static_cast<::std::size_t>(integer))+" s "
            +::test::detail::nanoseconds_to_string(others);
    }else if(ns>=c_1ms){
        integer=::std::floor(ns/c_1ms);
        others=ns-integer*c_1ms;
        return ::std::to_string(static_cast<::std::size_t>(integer))+" ms "
            +::test::detail::nanoseconds_to_string(others);
    }else if(ns>=c_1us){
        integer=::std::floor(ns/c_1us);
        others=ns-integer*c_1us;
        return ::std::to_string(static_cast<::std::size_t>(integer))+" us "
            +::test::detail::nanoseconds_to_string(others);
    }
    return ::std::to_string(static_cast<::std::size_t>(ns))+" ns";
}
}//namespace test::detail
::std::string Timer::delta_string(void)const noexcept{
    return ::test::detail::nanoseconds_to_string(this->delta_nanoseconds());
}
namespace detail{
void check_failed(
    ::std::string const& file,::std::string const& line
    ,::std::string const& info
)noexcept{
    ::test::detail::case_errors.emplace_back(
        ::test::detail::CheckFailedException(file,line,info)
    );
}
void assert_failed(
    ::std::string const& file,::std::string const& line
    ,::std::string const& info
){
    throw ::test::detail::AssertFailedException(file,line,info);
}
void check_count_incement(void)noexcept{
    ++::test::detail::check_count;
}
void check_failed_count_increment(void)noexcept{
    ++::test::detail::check_failed_count;
}
void check_passed_count_increment(void)noexcept{
    ++::test::detail::check_passed_count;
}
static void print_total_info(
    ::std::string type,bool is_passed,::test::Timer const& timer
    ,::std::string item_type,::std::size_t count,::std::size_t passed_count
    ,::std::size_t failed_count,::std::size_t tab_count=0
)noexcept{
    ::std::string format_string=
        ::std::string(tab_count,'\t')
        +"[%s] [%s] (%s)\n"
        +::std::string(tab_count+1,'\t')
        +"%s:%zu,passed:%zu,failed:%zu. (%.2f %%)\n";
    ::std::printf(
        format_string.c_str(),type.c_str()
        ,::std::string(is_passed?"passed":"failed").c_str()
        ,timer.delta_string().c_str(),item_type.c_str()
        ,count,passed_count,failed_count
        ,(count==0?double{100}:(static_cast<double>(passed_count)
                /static_cast<double>(count)*double{100}))
    );
}
static bool execute_case(
    ::std::size_t case_index,::std::size_t tab_count=0
)noexcept{
    if(case_index>=case_names.size()){
        return false;
    }
    ::test::detail::case_errors.clear();
    ::test::detail::check_count=0;
    ::test::detail::check_passed_count=0;
    ::test::detail::check_failed_count=0;
    bool case_is_passed=false;
    bool case_has_exception=false;
    ::std::string case_exception_what={};
    ::test::Timer case_timer={};
    auto catch_std_string=
        [&case_timer,&case_exception_what,&case_has_exception,&tab_count]
        (::std::string const& std_string)noexcept{
            case_timer.stop();
            case_exception_what=
                ::std::string(tab_count+1,'\t')+"[exception]\n"
                +::std::string(tab_count+2,'\t')+"<what> \""
                +std_string+"\"\n";
            case_has_exception=true;
        };
    auto catch_std_exception=
        [&catch_std_string](::std::exception const& std_exception)noexcept{
            return catch_std_string(std_exception.what());
        };
    auto catch_unknown_exception=
        [&case_timer,&case_exception_what,&case_has_exception,&tab_count]
        (void)noexcept{
            case_timer.stop();
            case_exception_what=
                ::std::string(tab_count+1,'\t')+"[exception]\n"
                +::std::string(tab_count+2,'\t')+"[unknown exception]\n";
            case_has_exception=true;
        };
    auto catch_test_assert_failed_exception=
        [&case_timer,&case_exception_what,&case_has_exception,&tab_count]
        (::test::detail::AssertFailedException const& exception)noexcept{
            case_timer.stop();
            case_exception_what=
                ::std::string(tab_count+1,'\t')+"[test::assert] [failed]\n"
                +::std::string(tab_count+2,'\t')+"<file> "
                +exception.file()+'\n'
                +::std::string(tab_count+2,'\t')+"<line> "
                +exception.line()+'\n'
                +::std::string(tab_count+2,'\t')+"<info> "
                +exception.info()+'\n';
            case_has_exception=true;
        };
    case_timer.start();
    try{
        ::test::detail::case_functions[case_index]();
    }catch(char const* c_str){
        catch_std_string(c_str);
    }catch(::std::string const& string){
        catch_std_string(string);
    }catch(::test::detail::AssertFailedException const& exception){
        catch_test_assert_failed_exception(exception);
    }catch(::std::exception const& exception){
        catch_std_exception(exception);
    }catch(...){
        catch_unknown_exception();
    }
    if(!case_has_exception){
        case_timer.stop();
    }
    case_is_passed=(!case_has_exception)
        &&::test::detail::case_errors.empty();
    ::test::detail::print_total_info(
        "test::case \""+::test::detail::case_names[case_index]+"\""
        ,case_is_passed,case_timer,"check",::test::detail::check_count
        ,::test::detail::check_passed_count
        ,::test::detail::check_failed_count,tab_count
    );
    ::std::string format_string={};
    for(
        ::std::size_t index=0;index<::test::detail::case_errors.size();++index
    ){
        format_string=
            ::std::string(tab_count+1,'\t')+"[test::check] [failed] %zu\n"
            +::std::string(tab_count+2,'\t')+"<file> %s\n"
            +::std::string(tab_count+2,'\t')+"<line> %s\n"
            +::std::string(tab_count+2,'\t')+"<info> %s\n";
        ::std::printf(
            format_string.c_str(),index
            ,::test::detail::case_errors[index].file().c_str()
            ,::test::detail::case_errors[index].line().c_str()
            ,::test::detail::case_errors[index].info().c_str()
        );
    }
    if(case_has_exception){
        ::std::printf(case_exception_what.c_str());
    }
    return case_is_passed;
}
static bool execute_group(
    ::std::size_t group_index,::std::size_t tab_count=0
)noexcept{
    if(group_index>=::test::detail::group_names.size()){
        return false;
    }
    ::std::string format_string={};
    format_string=
        ::std::string(tab_count,'\t')+"[test::group \"%s\"] [begin]\n";
    ::std::printf(
        format_string.c_str(),::test::detail::group_names[group_index].c_str()
    );
    ::std::size_t case_count=0;
    ::std::size_t case_passed_count=0;
    ::std::size_t case_failed_count=0;
    bool group_is_passed=false;
    ::test::Timer timer={};
    timer.start();
    for(auto const& case_name: ::test::detail::group_bodys[group_index]){
        if(::test::detail::case_name_to_index.count(case_name)==0){
            format_string=::std::string(tab_count+1,'\t')
                +"[test::case \"%s\"] [failed] can't be found.\n";
            ::std::printf(format_string.c_str(),case_name.c_str());
            ++case_failed_count;
        }else{
            if(::test::detail::execute_case(
                ::test::detail::case_name_to_index[case_name],tab_count+1
            )){
                ++case_passed_count;
            }else{
                ++case_failed_count;
            }
        }
        ++case_count;
    }
    timer.stop();
    group_is_passed=case_passed_count==case_count;
    ::test::detail::print_total_info(
        "test::group \""+::test::detail::group_names[group_index]+"\""
        ,group_is_passed,timer,"case",case_count,case_passed_count
        ,case_failed_count,tab_count+1
    );
    format_string=
        ::std::string(tab_count,'\t')+"[test::group \"%s\"] [end]\n";
    ::std::printf(format_string.c_str(),group_names[group_index].c_str());
    return group_is_passed;
}
}//namespace test::detail
void execute_case(std::string const& case_name)noexcept{
    if(::test::detail::case_name_to_index.count(case_name)==0){
        ::std::printf(
            "[test::case \"%s\"] [failed] can't be found.\n",case_name.c_str()
        );
    }else{
        ::test::detail::execute_case(
            ::test::detail::case_name_to_index[case_name]
        );
    }
}
void execute_group(::std::string const& group_name)noexcept{
    if(::test::detail::group_name_to_index.count(group_name)==0){
        ::std::printf(
            "[test::group \"%s\"] [failed] can't be found.\n"
            ,group_name.c_str()
        );
    }else{
        ::test::detail::execute_group(
            ::test::detail::group_name_to_index[group_name]
        );
    }
}
void execute_case_all(void)noexcept{
    ::std::printf("[test::case all] [begin]\n");
    ::std::size_t case_count=0;
    ::std::size_t case_passed_count=0;
    ::std::size_t case_failed_count=0;
    ::test::Timer timer={};
    timer.start();
    for(
        ::std::size_t index=0;index<::test::detail::case_names.size();++index
    ){
        if(::test::detail::execute_case(index,1)){
            ++case_passed_count;
        }else{
            ++case_failed_count;
        }
        ++case_count;
    }
    timer.stop();
    ::test::detail::print_total_info(
        "test::case all",case_passed_count==case_count,timer,"case",case_count
        ,case_passed_count,case_failed_count,1
    );
    ::std::printf("[test::case all] [end]\n");
}
void execute_group_all(void)noexcept{
    ::std::printf("[test::group all] [begin]\n");
    ::std::size_t group_count=0;
    ::std::size_t group_passed_count=0;
    ::std::size_t group_failed_count=0;
    ::test::Timer timer={};
    timer.start();
    for(
        ::std::size_t index=0;index<::test::detail::group_names.size();++index
    ){
        if(::test::detail::execute_group(index,1)){
            ++group_passed_count;
        }else{
            ++group_failed_count;
        }
        ++group_count;
    }
    timer.stop();
    ::test::detail::print_total_info(
        "test::group all",group_passed_count==group_count,timer,"group"
        ,group_count,group_passed_count,group_failed_count,1
    );
    ::std::printf("[test::group all] [end]\n");
}
}//namespace test
