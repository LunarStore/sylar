#include"base/log.h"
#include"base/thread.h"

static lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");
void test_lock(){
    lunar::Thread::ptr t1(new lunar::Thread([](){
        while(true){
            LUNAR_LOG_DEBUG(g_logger) << "---------------------------------------------------------";
        }
    }, "t1"));

    lunar::Thread::ptr t2(new lunar::Thread([](){
        while(true){
            LUNAR_LOG_DEBUG(g_logger) << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
        }
    }, "t2"));

    t1->join();
    t2->join();
}
void test_log(){
    LUNAR_LOG_DEBUG(LUNAR_LOG_ROOT()) << "hello";
    LUNAR_LOG_DEBUG(LUNAR_LOG_NAME("system")) << "system hello";
}
int main(){
    // lunar::Logger::ptr logger(new lunar::Logger());
    // logger->addAppender(lunar::LogAppender::ptr(new lunar::StdoutLogAppender()));
    // LUNAR_LOG_DEBUG(logger) << "hello";

    test_lock();
    return 0;
}