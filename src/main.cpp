#include<test/test.hpp>
TEST_UNIT(hello){
    TEST_EXPR(1+1==2);
    TEST_EXPR(1+2==3);
}
TEST_UNIT(world){
    TEST_EXPR(1+1==3);
    TEST_EXPR(1+2==4);
    throw "";
    TEST_EXPR(1+1==2);//TODO
}
int main(int argc,char* argv[]){
    ::test::exec();
    ::test::exec("world");
    ::test::exec("undefined");
    return 0;
}
