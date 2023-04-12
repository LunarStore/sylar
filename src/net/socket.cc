#include"net/socket.h"

namespace lunar{
    static Logger::ptr g_logger = LUNAR_LOG_NAME("system");

    Socket::ptr Socket::CreateTCP(Address::ptr address) {
        Socket::ptr sock(new Socket(address->getFamily(), TCP, 0));
        return sock;
    }

    Socket::ptr Socket::CreateUDP(Address::ptr address) {
        Socket::ptr sock(new Socket(address->getFamily(), UDP, 0));
        sock->newSock();
        sock->m_isConnected = true;
        return sock;
    }

    Socket::ptr Socket::CreateTCPSocket() {
        Socket::ptr sock(new Socket(IPv4, TCP, 0));
        return sock;
    }

    Socket::ptr Socket::CreateUDPSocket() {
        Socket::ptr sock(new Socket(IPv4, UDP, 0));
        sock->newSock();
        sock->m_isConnected = true;
        return sock;
    }
    Socket::Socket(sa_family_t family, int type, int protocol):
        m_sock(-1),
        m_family(family),
        m_type(type),
        m_protocol(protocol),
        m_isConnected(false){
        
    }

    Socket::~Socket(){
        close();
    }

    bool Socket::init(int sock){
        FdCtx::ptr fdCtx = FdMgr::GetInstance()->get(sock);

        if(!fdCtx || fdCtx->isClose() || !fdCtx->isSocket()){
            return false;
        }
        m_sock = sock;
        initSock();
        m_isConnected = true;
        getLocalAddress();
        getRemoteAddress();
        return true;
    }
    bool Socket::newSock(){
        if(isValid()){
            return false;
        }
        int rt = ::socket(m_family, m_type, m_protocol);
        if(rt == -1){
            LUNAR_LOG_ERROR(g_logger) << "socket(" << m_family
                << ", " << m_type << ", " << m_protocol << ") errno="
                << errno << " errstr=" << strerror(errno);
            return false;
        }
        m_sock = rt;
        initSock();
        return true;
    }

    bool Socket::initSock(){
        int val = 1;
        setOption(SOL_SOCKET, SO_REUSEADDR, val);
        if(m_type == SOCK_STREAM){
            setOption(IPPROTO_TCP, TCP_NODELAY, val);
        }
        return true;
    }
    Address::ptr Socket::getLocalAddress(){
        if(m_localAddress){
            return m_localAddress;
        }
        Address::ptr addr;
        switch(m_family){
            case AF_INET:
                addr.reset(new IPv4Address());
                break;
            default:
                addr.reset(new UnknowAdress(m_family));
        }
        socklen_t len = addr->getAddrLen();
        if( getsockname(m_sock, addr->getAddr(), &len) ){
            LUNAR_LOG_ERROR(g_logger) << "getsockname error sock = "
                << m_sock << "<errno = "
                << errno << ":" << strerror(errno);
        }

        m_localAddress = addr;
        return addr;
    }

    Address::ptr Socket::getRemoteAddress(){
        if(m_remoteAddress){
            return m_remoteAddress;
        }

        Address::ptr addr;
        switch(m_family){
            case AF_INET:
                addr.reset(new IPv4Address());
                break;
            default:
                addr.reset(new UnknowAdress(m_family));
        }
        socklen_t len = addr->getAddrLen();
        if( getpeername(m_sock, addr->getAddr(), &len) ){
            LUNAR_LOG_ERROR(g_logger) << "getpeername error sock = "
                << m_sock << "<errno = "
                << errno << ":" << strerror(errno);
        }

        m_remoteAddress = addr;
        return addr;
    }

    void Socket::close(){
        if(!isValid() || !isConnected()){
            return;
        }
        m_isConnected = false;
        int rt = ::close(m_sock);
        m_sock = -1;
        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "Socket::close error ::close(" << m_sock
                <<")<errno = " << errno
                << ": " << strerror(errno)
                << ">";
        }
        return;
    } 
    bool Socket::isValid(){
        return m_sock != -1;
    }

    bool Socket::isConnected(){
        return m_isConnected;
    }

    bool Socket::setOption(int level, int optname,const void* optval, socklen_t optlen){
        int rt = ::setsockopt(m_sock, level, optname, optval, optlen);

        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "Socket::setOption error ::setsockopt(" << m_sock
                << "," << level
                << "," << optname
                << "..)<errno = " << errno
                << ":" << strerror(errno)
                <<">";
            return false;
        }
        return true;
    }
    bool Socket::getOption(int level, int optname, void* optval, socklen_t* optlen){
        int rt = ::getsockopt(m_sock, level, optname, optval, optlen);

        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "Socket::getOption error ::getsockopt(" << m_sock
                << "," << level
                << "," << optname
                << "..)<errno = " << errno
                << ":" << strerror(errno)
                <<">";
            return false;
        }
        return true;
    }
    uint64_t Socket::getSendTimeout(){
        FdCtx::ptr fdCtx = FdMgr::GetInstance()->get(m_sock);
        if(fdCtx){
            return fdCtx->getTimeout(SO_SNDTIMEO);
        }
        return (uint64_t)-1;
    }
    void Socket::setSendTimeout(uint64_t to){
        struct timeval tv = {(int)to / 1000 , (int)(to % 1000) * 1000};

        setOption(SOL_SOCKET, SO_SNDTIMEO, tv);
    }
    uint64_t Socket::getRecvTimeout(){
        FdCtx::ptr fdCtx = FdMgr::GetInstance()->get(m_sock);
        if(fdCtx){
            return fdCtx->getTimeout(SO_RCVTIMEO);
        }
        return (uint64_t)-1;
    }
    void Socket::setRecvTimeout(uint64_t to){
        struct timeval tv = {(int)to / 1000 , (int)(to % 1000) * 1000};

        setOption(SOL_SOCKET, SO_RCVTIMEO, tv);
    }
    bool Socket::bind(Address::ptr addr){
        if(!isValid()){
            newSock();
            LUNAR_ASSERT(isValid());
        }
        if(m_family != addr->getFamily()){
            LUNAR_LOG_ERROR(g_logger) << "bind sock.family("
                << m_family << ") addr.family(" << addr->getFamily()
                << ") not equal, addr=" << addr->toString();
            return false;
        }
        int rt = ::bind(m_sock, addr->getAddr(), addr->getAddrLen());

        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "Socket::bind error ::bind(" << m_sock 
                << ","<< addr->toString()<<")<errno = " << errno
                << ":" << strerror(errno)
                << ">";
            return false;
        }

        getLocalAddress();
        return true;
    }
    bool Socket::listen(int backlog){
        if(!isValid()){
            LUNAR_LOG_ERROR(g_logger) << "listen sock = -1";
            return false;
        }

        int rt = ::listen(m_sock, backlog);

        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "Socket::listen errno ::listen(" << m_sock
                <<"," << backlog
                <<")<errno = " << errno
                <<":" << strerror(errno)
                <<">";
            return false;
        }
        return true;
    }

    Socket::ptr Socket::accept(){
        LUNAR_ASSERT(isValid());
        Socket::ptr sock(new Socket(m_family, m_type, m_protocol));
        int rt = ::accept(m_sock, nullptr, nullptr);
        if(rt == -1){
            LUNAR_LOG_ERROR(g_logger) << "Socket::accept() error ::accept(" << m_sock
                << ",...)<errno = " << errno
                << ":" << strerror(errno)
                <<">";
            return nullptr;
        }

        if(!sock->init(rt)){
            return nullptr;
        }
        //init里面已经获取了对端地址和本端地址
        // sock->getLocalAddress();
        // sock->getRemoteAddress();
        return sock;
    }


    bool Socket::connect(Address::ptr addr, uint64_t to){
        if(!isValid()){
            newSock();
            LUNAR_ASSERT(isValid());
        }
        if(m_family != addr->getFamily()){
            LUNAR_LOG_ERROR(g_logger) << "connect sock.family("
                << m_family << ") addr.family(" << addr->getFamily()
                << ") not equal, addr=" << addr->toString();
            return false;
        }

        if(to == (uint64_t)-1) {
            if(::connect(m_sock, addr->getAddr(), addr->getAddrLen())) {
                LUNAR_LOG_ERROR(g_logger) << "sock=" << m_sock << " connect(" << addr->toString()
                    << ") error errno=" << errno << " errstr=" << strerror(errno);
                close();
                return false;
            }
        } else {
            if(::connect_with_timeout(m_sock, addr->getAddr(), addr->getAddrLen(), to)) {
                LUNAR_LOG_ERROR(g_logger) << "sock=" << m_sock << " connect(" << addr->toString()
                    << ") timeout=" << to << " error errno="
                    << errno << " errstr=" << strerror(errno);
                close();
                return false;
            }
        }
        m_isConnected = true;
        getRemoteAddress();
        getLocalAddress();
        return true;
    }

    
    int Socket::send(const void* buffer, size_t length, int flags) {
        if(isConnected()) {
            return ::send(m_sock, buffer, length, flags);
        }
        return -1;
    }

    int Socket::send(const iovec* buffers, size_t length, int flags) {
        if(isConnected()) {
            msghdr msg;
            memset(&msg, 0, sizeof(msg));
            msg.msg_iov = (iovec*)buffers;
            msg.msg_iovlen = length;
            return ::sendmsg(m_sock, &msg, flags);
        }
        return -1;
    }

    int Socket::sendTo(const void* buffer, size_t length, const Address::ptr to, int flags) {
        if(isConnected()) {
            return ::sendto(m_sock, buffer, length, flags, to->getAddr(), to->getAddrLen());
        }
        return -1;
    }

    int Socket::sendTo(const iovec* buffers, size_t length, const Address::ptr to, int flags) {
        if(isConnected()) {
            msghdr msg;
            memset(&msg, 0, sizeof(msg));
            msg.msg_iov = (iovec*)buffers;
            msg.msg_iovlen = length;
            msg.msg_name = to->getAddr();
            msg.msg_namelen = to->getAddrLen();
            return ::sendmsg(m_sock, &msg, flags);
        }
        return -1;
    }

    int Socket::recv(void* buffer, size_t length, int flags) {
        if(isConnected()) {
            return ::recv(m_sock, buffer, length, flags);
        }
        return -1;
    }

    int Socket::recv(iovec* buffers, size_t length, int flags) {
        if(isConnected()) {
            msghdr msg;
            memset(&msg, 0, sizeof(msg));
            msg.msg_iov = (iovec*)buffers;
            msg.msg_iovlen = length;
            return ::recvmsg(m_sock, &msg, flags);
        }
        return -1;
    }

    int Socket::recvFrom(void* buffer, size_t length, Address::ptr from, int flags) {
        if(isConnected()) {
            socklen_t len = from->getAddrLen();
            return ::recvfrom(m_sock, buffer, length, flags, from->getAddr(), &len);
        }
        return -1;
    }

    int Socket::recvFrom(iovec* buffers, size_t length, Address::ptr from, int flags) {
        if(isConnected()) {
            msghdr msg;
            memset(&msg, 0, sizeof(msg));
            msg.msg_iov = (iovec*)buffers;
            msg.msg_iovlen = length;
            msg.msg_name = from->getAddr();
            msg.msg_namelen = from->getAddrLen();
            return ::recvmsg(m_sock, &msg, flags);
        }
        return -1;
    }
    int Socket::getError() {
        int error = 0;
        socklen_t len = sizeof(error);
        if(!getOption(SOL_SOCKET, SO_ERROR, &error, &len)) {
            error = errno;
        }
        return error;
    }

    std::ostream& Socket::dump(std::ostream& os) const {
        os << "[Socket sock=" << m_sock
        << " is_connected=" << m_isConnected
        << " family=" << m_family
        << " type=" << m_type
        << " protocol=" << m_protocol;
        if(m_localAddress) {
            os << " local_address=" << m_localAddress->toString();
        }
        if(m_remoteAddress) {
            os << " remote_address=" << m_remoteAddress->toString();
        }
        os << "]";
        return os;
    }

    std::string Socket::toString() const {
        std::stringstream ss;
        dump(ss);
        return ss.str();
    }

    bool Socket::cancelRead() {
        return !(IOManager::GetThis()->cancelEvent(m_sock, lunar::IOManager::READ));
    }

    bool Socket::cancelWrite() {
        return !(IOManager::GetThis()->cancelEvent(m_sock, lunar::IOManager::WRITE));
    }

    bool Socket::cancelAccept() {
        return !(IOManager::GetThis()->cancelEvent(m_sock, lunar::IOManager::READ));
    }

    bool Socket::cancelAll() {
        return !(IOManager::GetThis()->cancelAll(m_sock));
    }

    std::ostream& operator<<(std::ostream& os, const Socket& sock) {
        return sock.dump(os);
    }
}