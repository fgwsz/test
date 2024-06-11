#include"test.hpp"
#include<cstddef>//::std::size_t
#include<cstdio>//::std::printf
#include<chrono>//::std::chrono
#include<ratio>//::std::ratio
#include<vector>//::std::vector
#include<unordered_map>//::std::unordered_map
#include<exception>//::std::exception
namespace test{
namespace detail{
class Timer{
    using clock=::std::chrono::high_resolution_clock;
    using time_point=typename clock::time_point;
    time_point begin_,end_;
    template<typename Period>
    double delta(void)noexcept{
        return ::std::chrono::duration_cast<
            ::std::chrono::duration<double,Period>
        >(this->end_-this->begin_).count();
    }
public:
    void start(void)noexcept{
        this->begin_=clock::now();
    }
    void stop(void)noexcept{
        this->end_=clock::now();
    }
    double delta_nanoseconds(void)noexcept{
        return this->delta<::std::nano>();
    }
    double delta_microseconds(void)noexcept{
        return this->delta<::std::micro>();
    }
    double delta_milliseconds(void)noexcept{
        return this->delta<::std::milli>();
    }
    double delta_seconds(void)noexcept{
        return this->delta<::std::ratio<1>>();
    }
    double delta_minutes(void)noexcept{
        return this->delta<::std::ratio<60>>();
    }
    double delta_hours(void)noexcept{
        return this->delta<::std::ratio<3600>>();
    }
};
static ::std::vector<::std::string> unit_names={};
static ::std::vector<::std::function<void(void)>> unit_functions={};
static ::std::vector<::std::string> unit_errors={};
static ::std::unordered_map<::std::string,::std::size_t> unit_name_to_index={};
static ::std::size_t expr_count=0;
static ::std::size_t expr_fail_count=0;
static ::std::size_t expr_pass_count=0;
bool unit_push(
    ::std::string const& unit_name,
    ::std::function<void(void)> const& unit_function
)noexcept{
    if(::test::detail::unit_name_to_index.count(unit_name)==0){
        ::test::detail::unit_names.emplace_back(unit_name);
        ::test::detail::unit_functions.emplace_back(unit_function);
        ::test::detail::unit_name_to_index.emplace(
            unit_name
            ,::test::detail::unit_name_to_index.size()
        );
        return true;
    }else{
        return false;
    }
}
void error_push(
    ::std::string const& file
    ,::std::string const& line
    ,::std::string const& expr
)noexcept{
    ::test::detail::unit_errors.emplace_back(
        "\t\t<file> "+file
        +"\n\t\t<line> "+line
        +"\n\t\t<expr> "+expr
    );
}
void expr_count_incement(void)noexcept{
    ++::test::detail::expr_count;
}
void expr_fail_count_increment(void)noexcept{
    ++::test::detail::expr_fail_count;
}
void expr_pass_count_increment(void)noexcept{
    ++::test::detail::expr_pass_count;
}
static bool exec(::std::size_t unit_index)noexcept{
    ::test::detail::unit_errors.clear();
    ::test::detail::expr_count=0;
    ::test::detail::expr_pass_count=0;
    ::test::detail::expr_fail_count=0;
    bool unit_is_pass=false;
    bool unit_has_exception=false;
    ::std::string unit_exception_what={};
    Timer unit_timer={};
    auto catch_callback=[
        &unit_timer
        ,&unit_exception_what
        ,&unit_has_exception
    ](::std::string const& what){
        unit_timer.stop();
        unit_exception_what
            .append("\"").append(what).append("\"");
        unit_has_exception=true;
    };
    unit_timer.start();
    try{
        ::test::detail::unit_functions[unit_index]();
    }catch(char const* c_str){
        catch_callback(c_str);
    }catch(::std::string const& string){
        catch_callback(string);
    }catch(::std::exception const& exception){
        catch_callback(exception.what());
    }catch(...){
        catch_callback("unknown exception.");
    }
    if(!unit_has_exception){
        unit_timer.stop();
    }
    unit_is_pass=(!unit_has_exception)
        &&::test::detail::unit_errors.empty();
    ::std::printf(
        "[test::unit \"%s\"] [%s] (%f ms)\n"
        "\texpr:%zu,pass:%zu,fail:%zu.\n"
        ,::test::detail::unit_names[unit_index].c_str()
        ,::std::string(unit_is_pass?"pass":"fail").c_str()
        ,unit_timer.delta_milliseconds()
        ,::test::detail::expr_count
        ,::test::detail::expr_pass_count
        ,::test::detail::expr_fail_count
    );
    for(
        ::std::size_t index=0;
        index<::test::detail::unit_errors.size();
        ++index
    ){
        ::std::printf(
            "\t<fail> %zu\n"
            "%s\n"
            ,index
            ,::test::detail::unit_errors[index].c_str()
        );
    }
    if(unit_has_exception){
        ::std::printf(
            "\t<exce>\n"
            "\t\t<what> %s\n"
            ,unit_exception_what.c_str()
        );
    }
    return unit_is_pass;
}
}//namespace test::detail
void exec(void)noexcept{
    ::std::size_t unit_count=0;
    ::std::size_t unit_pass_count=0;
    ::std::size_t unit_fail_count=0;
    for(
        ::std::size_t index=0;
        index<::test::detail::unit_functions.size();
        ++index
    ){
        if(::test::detail::exec(index)){
            ++unit_pass_count;
        }else{
            ++unit_fail_count;
        }
        ++unit_count;
    }
    ::std::printf(
        "[test::all]\n"
        "\tunit:%zu,pass:%zu,fail:%zu.\n"
        ,unit_count
        ,unit_pass_count
        ,unit_fail_count
    );
}
void exec(std::string const& unit_name)noexcept{
    if(::test::detail::unit_name_to_index.count(unit_name)==0){
        ::std::printf(
            "[test::unit \"%s\"] can't be found.\n"
            ,unit_name.c_str()
        );
        return;
    }
    ::test::detail::exec(::test::detail::unit_name_to_index[unit_name]);
}
}//namespace test
