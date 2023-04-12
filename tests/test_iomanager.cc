#include"base/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<string.h>
#include <fcntl.h>
#include"base/log.h"

static lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");
void test(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;

    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "180.101.50.188", &addr.sin_addr.s_addr);

    int rt = connect(sockfd, (const sockaddr*)&addr, sizeof(addr));
    if(rt == -1 && EINPROGRESS == errno){

        // iom->addEvent(sockfd, lunar::IOManager::READ, [](){
        //     LUNAR_LOG_DEBUG(g_logger) << "read cb";
        // });

        lunar::IOManager::GetThis()->addEvent(sockfd, lunar::IOManager::WRITE, [](){
            LUNAR_LOG_DEBUG(g_logger) << "write cb";
        });
    }else{
        LUNAR_LOG_DEBUG(g_logger) << "error:" << errno << strerror(errno);
    }
}

void test_timer(){
    lunar::IOManager iom(2, "tm");

    iom.addTimer(1000, [](){
        LUNAR_LOG_DEBUG(g_logger) << "timer...";
    }, true);

}

int main(){
    // lunar::IOManager iom(10, "mmm");
    // iom.schedule(test);
    test_timer();
    LUNAR_LOG_DEBUG(g_logger) << "return";
    return 0;
}