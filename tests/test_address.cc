#include"net/address.h"
#include"base/log.h"
#include<vector>
#include<map>
#include<string>
static lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");
void testLookUp(){
    std::vector<lunar::Address::ptr> addrs;

    lunar::Address::LookUp(addrs, "baidu.com:3360", AF_INET, SOCK_STREAM);

    for(int i = 0; i < addrs.size(); i++){
        LUNAR_LOG_DEBUG(g_logger) << addrs[i]->toString();
    }
}

void testGetInterfaceAddresses(){
    std::multimap<std::string, std::pair<lunar::Address::ptr, uint32_t>> addrInfo;

    lunar::Address::GetInterfaceAddresses(addrInfo);

    for(auto item : addrInfo){
        LUNAR_LOG_DEBUG(g_logger) << item.first
            << "--" << item.second.first->toString()
            << "--" << item.second.second
            << "--" << (std::dynamic_pointer_cast<lunar::IPv4Address>(item.second.first))->getBroadcastAddress(item.second.second)->toString()
            << "--" << (std::dynamic_pointer_cast<lunar::IPv4Address>(item.second.first))->getNetWordAddress(item.second.second)->toString()
            << "--" << (std::dynamic_pointer_cast<lunar::IPv4Address>(item.second.first))->getSubnetMask(item.second.second)->toString();
    }
}

int main(){
    testLookUp();
    // testGetInterfaceAddresses();
    return 0;
}