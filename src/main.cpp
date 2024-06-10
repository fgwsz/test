#include<test/test.h>
TEST_UNIT(hello){
    TEST_CASE(1+1==2);
    TEST_CASE(1+2==3);
}
TEST_UNIT(world){
    TEST_CASE(1+1==3);
    TEST_CASE(1+2==4);
    throw "???";
    TEST_CASE(1+1==2);//TODO
}
int main(int argc,char* argv[]){
    ::test::exec();
    ::test::exec("world");
    ::test::exec("undefined unit");
    return 0;
}
