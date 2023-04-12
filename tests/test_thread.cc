#include"base/thread.h"
#include"base/log.h"
#include<iostream>
static lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");
int main(){
    lunar::Thread::ptr t1(new lunar::Thread([](){
        LUNAR_LOG_INFO(g_logger) << "t1";
    }, "t1"));

    // lunar::Thread::ptr t2 = t1;
    // LUNAR_LOG_DEBUG(g_logger) << "t1:"<< t1.use_count() << "--" << t2.use_count() << "--" << t1->shared_from_this().use_count();
    // lunar::Thread::ptr t2(new lunar::Thread([](){
    //     LUNAR_LOG_INFO(g_logger) << "t2";
    // }, "t2"));
    // char  c;
    // std::cin>> c;
    LUNAR_LOG_INFO(g_logger) << "over";
    //         LUNAR_LOG_DEBUG(g_logger) << "t1:"<< t1.use_count() << "--" << t2.use_count()<< "--" << t1->shared_from_this().use_count();
    return 0;
}
