#include"base/fiber.h"

lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");
void test(){
    lunar::Fiber::ptr fp(new lunar::Fiber([](){
        LUNAR_LOG_DEBUG(g_logger) << "fiber fun begin";
        lunar::Fiber::YieldToHold();
        LUNAR_LOG_DEBUG(g_logger) << "fiber fun end";
    } , true));
    lunar::Fiber::GetThis();

    fp->swapIn();
    LUNAR_LOG_DEBUG(g_logger) << "fiber fun out";
    fp->swapIn();
}

int main(){
    test();

    LUNAR_LOG_DEBUG(g_logger) << "main over";
    return 0;
}