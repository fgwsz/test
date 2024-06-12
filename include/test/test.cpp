#include"test.hpp"
#include<cstddef>//::std::size_t
#include<cstdio>//::std::printf
#include<ratio>//::std::ratio
#include<unordered_map>//::std::unordered_map
#include<exception>//::std::exception
namespace test{
namespace detail{
static ::std::vector<::std::string> case_names={};
static ::std::vector<::std::function<void(void)>> case_functions={};
static ::std::vector<::std::string> case_errors={};
static ::std::unordered_map<::std::string,::std::size_t> case_name_to_index={};
static ::std::vector<::std::string> group_names={};
static ::std::vector<::std::vector<::std::string>> group_bodys={};
static ::std::unordered_map<::std::string,::std::size_t> group_name_to_index={};
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
        case_name
        ,::test::detail::case_name_to_index.size()
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
        group_name
        ,::test::detail::group_name_to_index.size()
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
double Timer::delta_nanoseconds(void)noexcept{
    return ::test::detail::delta<::std::nano,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_microseconds(void)noexcept{
    return ::test::detail::delta<::std::micro,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_milliseconds(void)noexcept{
    return ::test::detail::delta<::std::milli,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_seconds(void)noexcept{
    return ::test::detail::delta<::std::ratio<1>,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_minutes(void)noexcept{
    return ::test::detail::delta<::std::ratio<60>,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_hours(void)noexcept{
    return ::test::detail::delta<::std::ratio<3600>,typename Timer::time_point>
        (this->begin_,this->end_);
}
namespace detail{
void check_failed(
    ::std::string const& file
    ,::std::string const& line
    ,::std::string const& info
)noexcept{
    ::test::detail::case_errors.emplace_back(
        "[test::check] [failed]"
        "\n\t\t<file> "+file
        +"\n\t\t<line> "+line
        +"\n\t\t<info> "+info
    );
}
class TestAssertFailedException:public ::std::exception{
    ::std::string what_;
public:
    TestAssertFailedException(::std::string const& what)
        :what_(what)
    {}
    virtual char const* what()const noexcept override{
        return this->what_.c_str();
    }
};
void assert_failed(
    ::std::string const& file
    ,::std::string const& line
    ,::std::string const& info
){
    throw ::test::detail::TestAssertFailedException{
        "[test::assert] [failed]"
        "\n\t\t<file> "+file
        +"\n\t\t<line> "+line
        +"\n\t\t<info> "+info
    };
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
    ::std::string type
    ,bool is_passed
    ,::test::Timer timer
    ,::std::string item_type
    ,::std::size_t count
    ,::std::size_t passed_count
    ,::std::size_t failed_count
)noexcept{
    ::std::printf(
        "[%s] [%s] (%f ms)\n"
        "\t%s:%zu,passed:%zu,failed:%zu. (%f %%)\n"
        ,type.c_str()
        ,::std::string(is_passed?"passed":"failed").c_str()
        ,timer.delta_milliseconds()
        ,item_type.c_str()
        ,count
        ,passed_count
        ,failed_count
        ,(count==0
            ?double{100}
            :(static_cast<double>(passed_count)
                /static_cast<double>(count)*double{100}))
    );
}
static bool execute_case(
    ::std::size_t case_index
)noexcept{
    ::test::detail::case_errors.clear();
    ::test::detail::check_count=0;
    ::test::detail::check_passed_count=0;
    ::test::detail::check_failed_count=0;
    bool case_is_passed=false;
    bool case_has_exception=false;
    ::std::string case_exception_what={};
    ::test::Timer case_timer={};
    auto catch_callback=[
        &case_timer
        ,&case_exception_what
        ,&case_has_exception
    ](::std::string const& what){
        case_timer.stop();
        case_exception_what=what;
        case_has_exception=true;
    };
    case_timer.start();
    try{
        ::test::detail::case_functions[case_index]();
    }catch(char const* c_str){
        catch_callback("<what> \""+::std::string{c_str}+"\"");
    }catch(::std::string const& string){
        catch_callback("<what> \""+string+"\"");
    }catch(::test::detail::TestAssertFailedException const& exception){
        catch_callback(exception.what());
    }catch(::std::exception const& exception){
        catch_callback("<what> \""+::std::string{exception.what()}+"\"");
    }catch(...){
        catch_callback("[unknown exception]");
    }
    if(!case_has_exception){
        case_timer.stop();
    }
    case_is_passed=(!case_has_exception)
        &&::test::detail::case_errors.empty();
    ::test::detail::print_total_info(
        "test::case \""+::test::detail::case_names[case_index]+"\""
        ,case_is_passed
        ,case_timer
        ,"check"
        ,::test::detail::check_count
        ,::test::detail::check_passed_count
        ,::test::detail::check_failed_count
    );
    for(
        ::std::size_t index=0;
        index<::test::detail::case_errors.size();
        ++index
    ){
        ::std::printf(
            "\t[test::error] %zu\n"
            "\t\t%s\n"
            ,index
            ,::test::detail::case_errors[index].c_str()
        );
    }
    if(case_has_exception){
        ::std::printf(
            "\t[exception]\n"
            "\t\t%s\n"
            ,case_exception_what.c_str()
        );
    }
    return case_is_passed;
}
}//namespace test::detail
void execute_case_all(void)noexcept{
    ::std::printf("[test::execute_case_all()] [begin]\n");
    ::std::size_t case_count=0;
    ::std::size_t case_passed_count=0;
    ::std::size_t case_failed_count=0;
    ::test::Timer timer={};
    timer.start();
    for(
        ::std::size_t index=0;
        index<::test::detail::case_functions.size();
        ++index
    ){
        if(::test::detail::execute_case(index)){
            ++case_passed_count;
        }else{
            ++case_failed_count;
        }
        ++case_count;
    }
    timer.stop();
    ::test::detail::print_total_info(
        "test::total"
        ,case_passed_count==case_count
        ,timer
        ,"case"
        ,case_count
        ,case_passed_count
        ,case_failed_count
    );
    ::std::printf("[test::execute_case_all()] [end]\n");
}
void execute_case(std::string const& case_name)noexcept{
    ::std::printf(
        "[test::execute_case(\"%s\")] [begin]\n"
        ,case_name.c_str()
    );
    if(::test::detail::case_name_to_index.count(case_name)==0){
        ::std::printf(
            "[test::case \"%s\"] can't be found.\n"
            ,case_name.c_str()
        );
    }else{
        ::test::detail::execute_case(
            ::test::detail::case_name_to_index[case_name]
        );
    }
    ::std::printf(
        "[test::execute_case(\"%s\")] [end]\n"
        ,case_name.c_str()
    );
}
void execute_group(::std::string const& group_name)noexcept{
    if(::test::detail::group_name_to_index.count(group_name)==0){
        ::std::printf(
            "[test::group \"%s\"] [failed] can't be found.\n"
            ,group_name.c_str()
        );
        return;
    }
    ::std::printf(
        "[test::group \"%s\"] [begin]\n"
        ,group_name.c_str()
    );
    ::std::size_t case_count=0;
    ::std::size_t case_passed_count=0;
    ::std::size_t case_failed_count=0;
    ::test::Timer timer={};
    auto const& group_body=::test::detail::group_bodys[
        ::test::detail::group_name_to_index[group_name]
    ];
    timer.start();
    for(auto const& case_name:group_body){
        if(::test::detail::case_name_to_index.count(case_name)==0){
            ::std::printf(
                "[test::case \"%s\"] [failed] can't be found.\n"
                ,case_name.c_str()
            );
            ++case_failed_count;
        }else{
            if(
                ::test::detail::execute_case(
                    ::test::detail::case_name_to_index[case_name]
                )
            ){
                ++case_passed_count;
            }else{
                ++case_failed_count;
            }
        }
        ++case_count;
    }
    timer.stop();
    ::test::detail::print_total_info(
        "test::total"
        ,case_passed_count==case_count
        ,timer
        ,"case"
        ,case_count
        ,case_passed_count
        ,case_failed_count
    );
    ::std::printf(
        "[test::group \"%s\"] [end]\n"
        ,group_name.c_str()
    );
}
}//namespace test
