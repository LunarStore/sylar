/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-02-23 16:52
 * LastModified : 2023-02-23 16:52
 * Filename : address.h
 * Description : 不实现IPv6，只用IPv4
 ************************************/

#ifndef __LUNAR_ADDRESS_H__
#define __LUNAR_ADDRESS_H__
#include<memory>
#include<stdint.h>
#include<sstream>
#include<string>
#include<netinet/in.h>
#include<netdb.h>
#include<vector>
#include<string.h>
#include<map>
#include <sys/types.h>
#include <ifaddrs.h>

#include"base/log.h"
#include"net/endian.h"
namespace lunar{
    class IPAddress;
    class Address : public std::enable_shared_from_this<Address>{
    public:
        typedef std::shared_ptr<Address> ptr;
    public:
        static Address::ptr LookupAny(const std::string& host,
            int family = AF_INET, int type = 0, int protocol = 0);
        static bool LookUp(std::vector<Address::ptr>& result, const std::string& host,
            sa_family_t family = AF_INET, int type = 0, int protocol = 0);
        static std::shared_ptr<IPAddress> LookupAnyIPAddress(const std::string& host,
            int family = AF_INET, int type = 0, int protocol = 0);
        static Address::ptr Create(const sockaddr* addr);
        //std::multimap : name - Address::ptr - prefixLen
        //family:关注的家族
        static bool GetInterfaceAddresses(std::multimap<std::string
                        ,std::pair<Address::ptr, uint32_t> >& result,
                        sa_family_t family = AF_INET);
        static bool GetInterfaceAddresses(std::vector<std::pair<Address::ptr, uint32_t> >&result
                ,const std::string& iface, int family = AF_INET);
    public:
        virtual const std::string toString()const = 0;
        virtual const sockaddr* getAddr()const = 0;
        virtual sockaddr* getAddr() = 0;
        virtual socklen_t getAddrLen()const = 0;
        virtual sa_family_t getFamily() const = 0;
        //析构函数不能是纯虚函数
        virtual ~Address()  {  };
    public:
        bool operator<(const Address& rhs) const;
        bool operator==(const Address & rhs) const;
        bool operator!=(const Address & rhs) const;
    };

    class IPAddress : public Address{
    public:
        typedef std::shared_ptr<IPAddress> ptr;

    public:
        virtual IPAddress::ptr getBroadcastAddress(uint32_t prefixLen) = 0;

        virtual IPAddress::ptr getNetWordAddress(uint32_t prefixLen) = 0;

        virtual IPAddress::ptr getSubnetMask(uint32_t prefixLen) = 0;

        virtual uint16_t getPort() = 0;

        virtual void setPort(uint16_t port) = 0;

    };

    class IPv4Address : public IPAddress{
    public:
        typedef std::shared_ptr<IPv4Address> ptr;
    public:
        IPv4Address(const sockaddr_in& address);
        IPv4Address(uint32_t address = INADDR_ANY, uint16_t port = 0);
    public:
        virtual const std::string toString()const override;
        virtual IPAddress::ptr getBroadcastAddress(uint32_t prefixLen) override;

        virtual IPAddress::ptr getNetWordAddress(uint32_t prefixLen) override;

        virtual IPAddress::ptr getSubnetMask(uint32_t prefixLen) override;

        virtual uint16_t getPort() override;

        virtual void setPort(uint16_t port) override;

        virtual socklen_t getAddrLen()const override;

        virtual const sockaddr* getAddr()const override;
        virtual sockaddr* getAddr() override;
        virtual sa_family_t getFamily() const override;
    private:
        sockaddr_in m_addr;
    };
    // class UnixAddress : public Address{
    //     //日后完善
    // public:
    //     typedef std::shared_ptr<UnixAddress> ptr;
    // public:
    // public:

    // };

    class UnknowAdress : public Address{
    public:
        typedef std::shared_ptr<UnknowAdress> ptr;
    public:
        UnknowAdress(sa_family_t family);
        UnknowAdress(const sockaddr& addr);
        virtual const std::string toString()const override;
        virtual socklen_t getAddrLen()const override;
        virtual const sockaddr* getAddr()const override;
        virtual sockaddr* getAddr() override;
        virtual sa_family_t getFamily() const override;
    private:
        sockaddr m_addr;
    };
    std::ostream& operator<<(std::ostream& os, const Address& addr);
}

#endif