#include "net/tcpserver.h"
#include "base/iomanager.h"
#include "base/log.h"

static lunar::Logger::ptr g_logger = LUNAR_LOG_ROOT();

void run() {
    auto addr = lunar::Address::LookupAny("0.0.0.0:8020");
    //auto addr2 = sylar::UnixAddress::ptr(new sylar::UnixAddress("/tmp/unix_addr"));
    std::vector<lunar::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    lunar::TcpServer::ptr tcp_server(new lunar::TcpServer);
    std::vector<lunar::Address::ptr> fails;
    while(!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    
}
int main(int argc, char** argv) {
    lunar::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
