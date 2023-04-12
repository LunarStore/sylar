/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-03-04 19:58
 * LastModified : 2023-03-04 19:58
 * Filename : application.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_APPLICATION_H__
#define __LUNAR_APPLICATION_H__

#include "http/httpserver.h"

namespace lunar {

class Application {
public:
    Application();

    static Application* GetInstance() { return s_instance;}
    bool init(int argc, char** argv);
    bool run();

    bool getServer(const std::string& type, std::vector<TcpServer::ptr>& svrs);
    void listAllServer(std::map<std::string, std::vector<TcpServer::ptr> >& servers);

private:
    int main(int argc, char** argv);
    int run_fiber();
private:
    int m_argc = 0;
    char** m_argv = nullptr;

    //std::vector<sylar::http::HttpServer::ptr> m_httpservers;
    std::map<std::string, std::vector<TcpServer::ptr> > m_servers;
    IOManager::ptr m_mainIOManager;
    static Application* s_instance;
};

}

#endif
