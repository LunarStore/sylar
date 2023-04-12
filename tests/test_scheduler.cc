#include"base/scheduler.h"
#include"base/hook.h"

lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");
void fun(){

    lunar::set_hook_enable(false);
    static int count = 0;
    LUNAR_LOG_ERROR(g_logger) << "fun:"<<count;
    if(count < 5){
        lunar::Scheduler::GetThis()->schedule(fun);
        count++;
    }
    sleep(1);
}

int main(){
    g_logger->setLevel(lunar::LogLevel::ERROR);
    lunar::Scheduler::ptr sch(new lunar::Scheduler(1, "test_sche"));
    sch->schedule(fun);
    sch->start();
    sch->stop();
    LUNAR_LOG_DEBUG(g_logger) << "end";
}