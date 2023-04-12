#include "init/application.h"

#include <unistd.h>
#include <signal.h>

#include "net/tcpserver.h"
#include "init/daemon.h"
#include "base/config.h"
#include "init/env.h"
#include "base/log.h"
#include "init/module.h"
#include "base/worker.h"


#include "http/servlet.h"
#include "http/httpserver.h"
namespace lunar {

static lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");

static lunar::ConfigVar<std::string>::ptr g_server_work_path =
    lunar::ConfigVarMgr::GetInstance()->lookUp("server.work_path"
            ,std::string("/apps/work/lunar")
            , "server work path");

static lunar::ConfigVar<std::string>::ptr g_server_pid_file =
    lunar::ConfigVarMgr::GetInstance()->lookUp("server.pid_file"
            ,std::string("lunar.pid")
            , "server pid file");


static lunar::ConfigVar<std::vector<TcpServerConf> >::ptr g_servers_conf
    = lunar::ConfigVarMgr::GetInstance()->lookUp("servers", std::vector<TcpServerConf>(), "http server config");

Application* Application::s_instance = nullptr;

Application::Application() {
    s_instance = this;
}

bool Application::init(int argc, char** argv) {
    m_argc = argc;
    m_argv = argv;

    lunar::EnvMgr::GetInstance()->addHelp("s", "start with the terminal");
    lunar::EnvMgr::GetInstance()->addHelp("d", "run as daemon");
    lunar::EnvMgr::GetInstance()->addHelp("c", "conf path default: ./conf");
    lunar::EnvMgr::GetInstance()->addHelp("p", "print help");

    bool is_print_help = false;
    if(!lunar::EnvMgr::GetInstance()->init(argc, argv)) {
        is_print_help = true;
    }

    if(lunar::EnvMgr::GetInstance()->has("p")) {
        is_print_help = true;
    }

    std::string conf_path = lunar::EnvMgr::GetInstance()->getConfigPath();
    LUNAR_LOG_INFO(g_logger) << "load conf path:" << conf_path;
    lunar::ConfigVarMgr::GetInstance()->loadFromConfDir(conf_path);

    ModuleMgr::GetInstance()->init();
    std::vector<Module::ptr> modules;
    ModuleMgr::GetInstance()->listAll(modules);

    for(auto i : modules) {
        i->onBeforeArgsParse(argc, argv);
    }

    if(is_print_help) {
        lunar::EnvMgr::GetInstance()->printHelp();
        return false;
    }

    for(auto i : modules) {
        i->onAfterArgsParse(argc, argv);
    }
    modules.clear();

    int run_type = 0;
    if(lunar::EnvMgr::GetInstance()->has("s")) {
        run_type = 1;
    }
    if(lunar::EnvMgr::GetInstance()->has("d")) {
        run_type = 2;
    }

    if(run_type == 0) {
        lunar::EnvMgr::GetInstance()->printHelp();
        return false;
    }
    
    g_logger->setLevel(LogLevel::INFO);
    return true;
}

bool Application::run() {
    bool is_daemon = lunar::EnvMgr::GetInstance()->has("d");
    return start_daemon(m_argc, m_argv,
            std::bind(&Application::main, this, std::placeholders::_1,
                std::placeholders::_2), is_daemon);
}

int Application::main(int argc, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    LUNAR_LOG_INFO(g_logger) << "main";
    std::string conf_path = lunar::EnvMgr::GetInstance()->getConfigPath();
    lunar::ConfigVarMgr::GetInstance()->loadFromConfDir(conf_path, true);
    {
        std::string pidfile = g_server_work_path->getValue()
                                    + "/" + g_server_pid_file->getValue();
        std::ofstream ofs(pidfile);
        if(!ofs) {
            LUNAR_LOG_ERROR(g_logger) << "open pidfile " << pidfile << " failed";
            return false;
        }
        ofs << getpid();
    }

    m_mainIOManager.reset(new lunar::IOManager(1,  "main", true));
    m_mainIOManager->schedule(std::bind(&Application::run_fiber, this));
    m_mainIOManager->addTimer(2000, [](){
            //LUNAR_LOG_INFO(g_logger) << "hello";
    }, true);
    m_mainIOManager->stop();
    return 0;
}

int Application::run_fiber() {
    std::vector<Module::ptr> modules;
    ModuleMgr::GetInstance()->listAll(modules);
    bool has_error = false;
    for(auto& i : modules) {
        if(!i->onLoad()) {
            LUNAR_LOG_ERROR(g_logger) << "module name="
                << i->getName() << " version=" << i->getVersion()
                << " filename=" << i->getFilename();
            has_error = true;
        }
    }
    if(has_error) {
        _exit(0);
    }

    lunar::WorkerMgr::GetInstance()->init();

    auto http_confs = g_servers_conf->getValue();
    std::vector<TcpServer::ptr> svrs;
    for(auto& i : http_confs) {
        LUNAR_LOG_DEBUG(g_logger) << std::endl << LexicalCast<TcpServerConf, std::string>()(i);

        std::vector<Address::ptr> address;
        for(auto& a : i.address) {
            size_t pos = a.find(":");
            if(pos == std::string::npos) {
                LUNAR_LOG_ERROR(g_logger) << "invalid address: " << a;
                continue;
            }
            int32_t port = atoi(a.substr(pos + 1).c_str());
            //127.0.0.1
            auto addr = lunar::Address::LookupAny(a);
            if(addr) {
                address.push_back(addr);
                continue;
            }
            std::vector<std::pair<Address::ptr, uint32_t> > result;
            if(lunar::Address::GetInterfaceAddresses(result,
                                        a.substr(0, pos))) {
                for(auto& x : result) {
                    auto ipaddr = std::dynamic_pointer_cast<IPAddress>(x.first);
                    if(ipaddr) {
                        ipaddr->setPort(port);
                    }
                    address.push_back(ipaddr);
                }
                continue;
            }
        }
        IOManager* accept_worker = lunar::IOManager::GetThis();
        IOManager* io_worker = lunar::IOManager::GetThis();
        IOManager* process_worker = lunar::IOManager::GetThis();
        if(!i.accept_worker.empty()) {
            accept_worker = lunar::WorkerMgr::GetInstance()->getAsIOManager(i.accept_worker).get();
            if(!accept_worker) {
                LUNAR_LOG_ERROR(g_logger) << "accept_worker: " << i.accept_worker
                    << " not exists";
                _exit(0);
            }
        }
        if(!i.io_worker.empty()) {
            io_worker = lunar::WorkerMgr::GetInstance()->getAsIOManager(i.io_worker).get();
            if(!io_worker) {
                LUNAR_LOG_ERROR(g_logger) << "io_worker: " << i.io_worker
                    << " not exists";
                _exit(0);
            }
        }
        if(!i.process_worker.empty()) {
            process_worker = lunar::WorkerMgr::GetInstance()->getAsIOManager(i.process_worker).get();
            if(!process_worker) {
                LUNAR_LOG_ERROR(g_logger) << "process_worker: " << i.process_worker
                    << " not exists";
                _exit(0);
            }
        }

        TcpServer::ptr server;
        if(i.type == "http") {
            server.reset(new lunar::http::HttpServer(i.keepalive,
                            process_worker, io_worker, accept_worker));
            server->setType(i.type);
        } else {
            LUNAR_LOG_ERROR(g_logger) << "invalid server type=" << i.type
                << LexicalCast<TcpServerConf, std::string>()(i);
            _exit(0);
        }
        if(!i.name.empty()) {
            server->setName(i.name);
        }
        std::vector<Address::ptr> fails;
        if(!server->bind(address, fails, i.ssl)) {
            for(auto& x : fails) {
                LUNAR_LOG_ERROR(g_logger) << "bind address fail:"
                    << *x;
            }
            _exit(0);
        }

        server->setConf(i);
        //server->start();
        m_servers[i.type].push_back(server);
        svrs.push_back(server);
    }

    for(auto& i : modules) {
        i->onServerReady();
    }

    for(auto& i : svrs) {
        i->start();
    }


    for(auto& i : modules) {
        i->onServerUp();
    }
    return 0;
}

bool Application::getServer(const std::string& type, std::vector<TcpServer::ptr>& svrs) {
    auto it = m_servers.find(type);
    if(it == m_servers.end()) {
        return false;
    }
    svrs = it->second;
    return true;
}

void Application::listAllServer(std::map<std::string, std::vector<TcpServer::ptr> >& servers) {
    servers = m_servers;
}

}
