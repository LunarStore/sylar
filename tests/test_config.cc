#include"base/log.h"
#include"base/config.h"
#include<vector>

static lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");
int main(){
    lunar::ConfigVar<int>::ptr _int = lunar::ConfigVarMgr::GetInstance()->lookUp("a", 17, "int test");
    lunar::ConfigVar<std::vector<int>>::ptr _vec = lunar::ConfigVarMgr::GetInstance()->lookUp("test", std::vector<int>(), "int vec");
    static lunar::ConfigVar<uint64_t>::ptr g_tcp_server_read_timeout =
    lunar::ConfigVarMgr::GetInstance()->lookUp("tcp_server.read_timeout", (uint64_t)(60 * 1000 * 2),
            "tcp server read timeout");
    _vec->addListener([](const std::vector<int>& o, const std::vector<int>& n){
        LUNAR_LOG_DEBUG(LUNAR_LOG_ROOT()) << "hello";
    });
    LUNAR_LOG_DEBUG(LUNAR_LOG_ROOT()) << _vec->getValue().size()
    <<_vec->getDescription();
    lunar::ConfigVarMgr::GetInstance()->loadFromFile("test.yml");
    LUNAR_LOG_DEBUG(LUNAR_LOG_ROOT()) << _int->getValue()
        << _int->getDescription();

    LUNAR_LOG_DEBUG(LUNAR_LOG_ROOT()) << "--------------";

    for(size_t i = 0; i < _vec->getValue().size(); i++){
        LUNAR_LOG_DEBUG(LUNAR_LOG_ROOT())<< _vec->getValue()[i];
    }

    LUNAR_LOG_DEBUG(g_logger) << "-------------------------------------";

    LUNAR_LOG_DEBUG(g_logger) << g_tcp_server_read_timeout->getValue();

    return 0;
}