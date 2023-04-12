#include "init/daemon.h"
#include "base/iomanager.h"
#include "base/log.h"

static lunar::Logger::ptr g_logger = LUNAR_LOG_ROOT();

lunar::Timer::ptr timer;
int server_main(int argc, char** argv) {
    LUNAR_LOG_INFO(g_logger) << lunar::ProcessInfoMgr::GetInstance()->toString();
    lunar::IOManager iom(1);
    timer = iom.addTimer(1000, [&iom](){
            LUNAR_LOG_INFO(g_logger) << "onTimer";
            static int count = 0;
            if(++count > 1) {
                //exit(1);
                timer->cancel();
                return;
            }
    }, true);
    return 0;
}

int main(int argc, char** argv) {
    return lunar::start_daemon(argc, argv, server_main, argc != 1);
}
