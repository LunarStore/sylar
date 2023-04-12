#include"net/address.h"


namespace lunar{
    static Logger::ptr g_logger = LUNAR_LOG_NAME("system");
    // 左移0位 sizeof(T)*8
    // 左移1位 sizeof(T)*8 - 1
    template<typename T>
    static T __CreateMask(uint32_t prefixLen){
        return (~(T(0))) << (sizeof(T) * 8 - prefixLen);
    }

    template<typename T>
    static uint32_t __BitCount(T v){
        uint32_t res = 0;
        while(v){
            v &= (v - 1);
            res++;
        }

        return res;
    }

    Address::ptr Address::LookupAny(const std::string& host,
                                int family, int type, int protocol) {
        std::vector<Address::ptr> result;
        if(LookUp(result, host, family, type, protocol)) {
            return result[0];
        }
        return nullptr;
    }
    bool Address::LookUp(std::vector<Address::ptr>& result, const std::string& host,
                     sa_family_t family, int type, int protocol){
        addrinfo hints = { 0 }, *res = nullptr, *next = nullptr;
        hints.ai_family = family;
        hints.ai_socktype = type;
        hints.ai_protocol = protocol;
        std::string node, service;
        char* pos = nullptr;

        if((pos = (char *)memchr(host.c_str(), ':', host.length())) == nullptr){
            //没有服务
            node = host;
        }else{
            //有服务
            node = host.substr(0, pos - host.c_str());
            service = host.substr(pos - host.c_str() + 1);
        }
        int rt = getaddrinfo(node.c_str(), service.c_str(), &hints, &res);
        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "error : Address::LookUp(host:" << host << ","
                << family << "," << type << ","
                << protocol<< "):" << "rt = " 
                << rt << "<"<< gai_strerror(rt)
                << ">";
            return false;
        }
        next = res;

        while(next != nullptr){
            result.push_back(Create(next->ai_addr));
            next = next->ai_next;
        }
        freeaddrinfo(res);
        return true;
    }
    IPAddress::ptr Address::LookupAnyIPAddress(const std::string& host,
                                    int family, int type, int protocol) {
        std::vector<Address::ptr> result;
        if(LookUp(result, host, family, type, protocol)) {
            //for(auto& i : result) {
            //    std::cout << i->toString() << std::endl;
            //}
            for(auto& i : result) {
                IPAddress::ptr v = std::dynamic_pointer_cast<IPAddress>(i);
                if(v) {
                    return v;
                }
            }
        }
        return nullptr;
    }
    Address::ptr Address::Create(const sockaddr* addr){
        if(addr == nullptr){
            return nullptr;
        }
        Address::ptr res;
        switch(addr->sa_family){
            case AF_INET:
                res.reset(new IPv4Address(*((sockaddr_in*)addr)));
                break;
            default:
                res.reset(new UnknowAdress(*addr));
        }

        return res;
    }
    bool Address::GetInterfaceAddresses(std::multimap<std::string
        ,std::pair<Address::ptr, uint32_t> >& result,
        sa_family_t family){
        struct ifaddrs *ifaddr, *ifa;
        
        if(getifaddrs(&ifaddr) == -1){
            LUNAR_LOG_ERROR(g_logger) << "Address::GetInterfaceAddresses getifaddrs error:<"
                << "errno = " << errno
                << strerror(errno) << ">";
            return false;
        }

        for(ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next){
            sa_family_t ifaFamily = ifa->ifa_addr->sa_family;
            if(ifa->ifa_addr == nullptr || (family != AF_UNSPEC && family != ifaFamily)){
                continue;
            }

            std::string name(ifa->ifa_name);
            uint32_t prefixLen;
            Address::ptr addr;
            switch(ifa->ifa_addr->sa_family){
                case AF_INET:
                    prefixLen = __BitCount(((sockaddr_in*)ifa->ifa_netmask)->sin_addr.s_addr);
                    break;
                default:
                    prefixLen = 0;
                    break;
            }
            addr = Create(ifa->ifa_addr);
            result.insert({name, {addr, prefixLen}});
        }

        freeifaddrs(ifaddr);
        return true;
    }

    
    bool Address::GetInterfaceAddresses(std::vector<std::pair<Address::ptr, uint32_t> >&result
                        ,const std::string& iface, int family) {
        if(iface.empty() || iface == "*") {
            if(family == AF_INET || family == AF_UNSPEC) {
                result.push_back(std::make_pair(Address::ptr(new IPv4Address()), 0u));
            }
            return true;
        }

        std::multimap<std::string
            ,std::pair<Address::ptr, uint32_t> > results;

        if(!GetInterfaceAddresses(results, family)) {
            return false;
        }

        auto its = results.equal_range(iface);
        for(; its.first != its.second; ++its.first) {
            result.push_back(its.first->second);
        }
        return !result.empty();
    }
    bool Address::operator<(const Address& rhs) const{
        socklen_t comnLen = std::min(getAddrLen(), rhs.getAddrLen());
        int rt = memcmp(getAddr(), rhs.getAddr(), comnLen);
        if(rt < 0){
            return true;
        }else if(rt > 0){
            return false;
        }else{
            return getAddrLen() < rhs.getAddrLen();
        }
    }
    bool Address::operator==(const Address& rhs) const{
        return getAddrLen() == rhs.getAddrLen() && 
            memcmp(getAddr(), rhs.getAddr(), getAddrLen()) == 0;
    }
    bool Address::operator!=(const Address& rhs)const{ 
        return !(*this == rhs);
    }
    IPv4Address::IPv4Address(const sockaddr_in& address){
        m_addr = address;
    }
    IPv4Address::IPv4Address(uint32_t address, uint16_t port){
        memset(&m_addr, 0, sizeof(m_addr));
        m_addr.sin_addr.s_addr = byteswapOnLittleEndian(address);
        m_addr.sin_family = AF_INET;
        m_addr.sin_port = byteswapOnLittleEndian(port);
    }
    const std::string IPv4Address::toString()const{
        std::stringstream ss;
        sockaddr_in addr = { 0 };
        addr.sin_addr.s_addr = byteswapOnLittleEndian(m_addr.sin_addr.s_addr);
        addr.sin_port = byteswapOnLittleEndian(m_addr.sin_port);

        ss << ((addr.sin_addr.s_addr >> 24) & 0xff) << "."
            << ((addr.sin_addr.s_addr >> 16) & 0xff) << "."
            <<((addr.sin_addr.s_addr >> 8) & 0xff) << "."
            <<((addr.sin_addr.s_addr >> 0) & 0xff) << ":"
            << addr.sin_port;
        return ss.str();
    }
    IPAddress::ptr IPv4Address::getBroadcastAddress(uint32_t prefixLen){
        if(prefixLen > 32){
            return nullptr;
        }
        sockaddr_in broadcastAddr(m_addr);
        broadcastAddr.sin_addr.s_addr |=  byteswapOnLittleEndian(~__CreateMask<uint32_t>(prefixLen));
        return IPv4Address::ptr(new IPv4Address(broadcastAddr));
    }

    IPAddress::ptr IPv4Address::getNetWordAddress(uint32_t prefixLen) {
        if(prefixLen > 32){
            return nullptr;
        }

        sockaddr_in netWord(m_addr);
        netWord.sin_addr.s_addr &= byteswapOnLittleEndian(~__CreateMask<uint32_t>(prefixLen));
        return IPv4Address::ptr(new IPv4Address(netWord));
    }

    IPAddress::ptr IPv4Address::getSubnetMask(uint32_t prefixLen) {
        if(prefixLen > 32){
            return nullptr;
        }

        sockaddr_in submask = { 0 };
        submask.sin_addr.s_addr = byteswapOnLittleEndian(__CreateMask<uint32_t>(prefixLen));
        submask.sin_family = AF_INET;
        return IPv4Address::ptr(new IPv4Address(submask));
    }

    uint16_t IPv4Address::getPort() {
        return byteswapOnLittleEndian(m_addr.sin_port);
    }

    void IPv4Address::setPort(uint16_t port) {
        m_addr.sin_port = byteswapOnLittleEndian(port);
    }

    socklen_t IPv4Address::getAddrLen()const{
        return sizeof(m_addr);
    }

    const sockaddr* IPv4Address::getAddr()const {
        return (const sockaddr*)(&m_addr);
    }
    sockaddr* IPv4Address::getAddr() {
        return (sockaddr*)(&m_addr);
    }
    sa_family_t IPv4Address::getFamily() const {
        return m_addr.sin_family;
    }
    UnknowAdress::UnknowAdress(const sockaddr& addr){
        m_addr = addr;
    }
    UnknowAdress::UnknowAdress(sa_family_t family){
        m_addr.sa_family = family;
    }
    const std::string UnknowAdress::toString()const {
        std::stringstream ss;
        ss << "[UnknownAddress family=" << m_addr.sa_family << "]";
        return ss.str();
    }

    socklen_t UnknowAdress::getAddrLen()const{
        return sizeof(m_addr);
    }

    const sockaddr* UnknowAdress::getAddr()const {
        return (const sockaddr*)(&m_addr);
    }
    sockaddr* UnknowAdress::getAddr() {
        return (sockaddr*)(&m_addr);
    }
    sa_family_t UnknowAdress::getFamily() const {
        return m_addr.sa_family;
    }
    std::ostream& operator<<(std::ostream& os, const Address& addr) {
        os << addr.toString();
        return os;
    }
}