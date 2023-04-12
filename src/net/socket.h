/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-02-25 15:24
 * LastModified : 2023-02-25 15:24
 * Filename : socket.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_SOCKET_H__
#define __LUNAR_SOCKET_H__
#include<memory>
#include<netinet/tcp.h>

#include"net/address.h"
#include"base/hook.h"
#include"base/fdmanager.h"
#include"base/iomanager.h"
#include"base/noncopyable.h"
namespace lunar{
    class Socket: public std::enable_shared_from_this<Socket>, Noncopyable{
    public:
        typedef std::shared_ptr<Socket> ptr;
    public:
    /**
     * @brief Socket类型
     */
    enum Type {
        /// TCP类型
        TCP = SOCK_STREAM,
        /// UDP类型
        UDP = SOCK_DGRAM
    };

    /**
     * @brief Socket协议簇
     */
    enum Family {
        /// IPv4 socket
        IPv4 = AF_INET,
        // /// IPv6 socket
        // IPv6 = AF_INET6,
        // /// Unix socket
        // UNIX = AF_UNIX,
    };

    /**
     * @brief 创建TCP Socket(满足地址类型)
     * @param[in] address 地址
     */
    static Socket::ptr CreateTCP(Address::ptr address);

    /**
     * @brief 创建UDP Socket(满足地址类型)
     * @param[in] address 地址
     */
    static Socket::ptr CreateUDP(Address::ptr address);

    /**
     * @brief 创建IPv4的TCP Socket
     */
    static Socket::ptr CreateTCPSocket();

    /**
     * @brief 创建IPv4的UDP Socket
     */
    static Socket::ptr CreateUDPSocket();
    public:
        Socket(sa_family_t family, int type, int protocol = 0);
        virtual ~Socket();
    protected:
        bool init(int sock);
        bool newSock();
        bool initSock();
    public:
        Address::ptr getLocalAddress();
        Address::ptr getRemoteAddress();
        void close();
        bool isValid();
        bool isConnected();
        bool setOption(int level, int optname, const void* optval, socklen_t optlen);

        template<typename T>
        bool setOption(int level, int optname, const T& optval){
            return setOption(level, optname, &optval, sizeof(T));
        }
        bool getOption(int level, int optname, void* optval, socklen_t* optlen);
        
        template<typename T>
        bool getOption(int level, int optname, T& optval){
            socklen_t optlen = sizeof(T);
            return getOption(level, optname, &optval, &optlen);
        }
        uint64_t getSendTimeout();
        //毫秒
        void setSendTimeout(uint64_t to);
        uint64_t getRecvTimeout();
        void setRecvTimeout(uint64_t to);
        
    public:
        bool bind(Address::ptr addr);
        bool listen(int backlog = SOMAXCONN);
        Socket::ptr accept();
        bool connect(Address::ptr addr, uint64_t to = -1);
        int send(const void* buffer, size_t length, int flags = 0);
        int send(const iovec* buffers, size_t length, int flags = 0);
        int sendTo(const void* buffer, size_t length, const Address::ptr to, int flags = 0);
        int sendTo(const iovec* buffers, size_t length, const Address::ptr to, int flags = 0);
        int recv(void* buffer, size_t length, int flags = 0);
        int recv(iovec* buffers, size_t length, int flags = 0);
        int recvFrom(void* buffer, size_t length, Address::ptr from, int flags = 0);
        int recvFrom(iovec* buffers, size_t length, Address::ptr from, int flags = 0);
    public:
        std::ostream& dump(std::ostream& os) const; 
        int getError();
        std::string toString() const;
        bool cancelRead();
        bool cancelWrite();
        bool cancelAccept();
        bool cancelAll();
    private:
        int m_sock;
        sa_family_t m_family;
        int m_type;
        int m_protocol;
        bool m_isConnected;
        Address::ptr m_localAddress;
        Address::ptr m_remoteAddress;

    };

    std::ostream& operator<<(std::ostream& os, const Socket& sock);
}

#endif