#include"base/iomanager.h"
#include"net/address.h"
#include"net/socket.h"


static lunar::Logger::ptr g_looger = LUNAR_LOG_ROOT();

void test_socket() {
    //std::vector<sylar::Address::ptr> addrs;
    //sylar::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    //sylar::IPAddress::ptr addr;
    //for(auto& i : addrs) {
    //    SYLAR_LOG_INFO(g_looger) << i->toString();
    //    addr = std::dynamic_pointer_cast<sylar::IPAddress>(i);
    //    if(addr) {
    //        break;
    //    }
    //}
    lunar::IPAddress::ptr addr = lunar::Address::LookupAnyIPAddress("www.baidu.com");
    if(addr) {
        LUNAR_LOG_INFO(g_looger) << "get address: " << addr->toString();
    } else {
        LUNAR_LOG_ERROR(g_looger) << "get address fail";
        return;
    }

    lunar::Socket::ptr sock = lunar::Socket::CreateTCP(addr);
    addr->setPort(80);
    LUNAR_LOG_INFO(g_looger) << "addr=" << addr->toString();
    if(!sock->connect(addr)) {
        LUNAR_LOG_ERROR(g_looger) << "connect " << addr->toString() << " fail";
        return;
    } else {
        LUNAR_LOG_INFO(g_looger) << "connect " << addr->toString() << " connected";
    }

    const char buff[] = "GET / HTTP/1.0\r\n\r\n";
    int rt = sock->send(buff, sizeof(buff));
    if(rt <= 0) {
        LUNAR_LOG_INFO(g_looger) << "send fail rt=" << rt;
        return;
    }

    std::string buffs;
    buffs.resize(4096);
    rt = sock->recv(&buffs[0], buffs.size());

    if(rt <= 0) {
        LUNAR_LOG_INFO(g_looger) << "recv fail rt=" << rt;
        return;
    }

    buffs.resize(rt);
    LUNAR_LOG_INFO(g_looger) << buffs;
}
int main(int argc, char** argv) {
    lunar::IOManager iom(2,"mm");
    //iom.schedule(&test_socket);
    iom.schedule(test_socket);
    return 0;
}