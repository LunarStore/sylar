#include "init/module.h"
#include "http/http.h"
#include "init/application.h"
#include "net/tcpserver.h"
#include "http/httpserver.h"
#include "net/bytearray.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
int32_t handle(lunar::http::HttpRequest::ptr request
        , lunar::http::HttpResponse::ptr response
        , lunar::http::HttpSession::ptr session) {
            std::stringstream ss;
            response->setStatus(lunar::http::HttpStatus::OK);
            response->setHeader("Content-Type", "image/jpg");
            // std::ifstream ifs;
            // ifs.open("~/Lunar/web/img/Lunar.jpg", std::ios::in | std::ios::binary);
            // ss << ifs;
            lunar::ByteArray::ptr ba(new lunar::ByteArray());
            ba->readFromFile("/root/Lunar/web/img/Lunar.jpg");
            ba->setPosition(0);
            response->setBody(ba->toString());

            return 0;
}

class Index : public lunar::Module{
public:
    Index(const std::string& name
                ,const std::string& version
                ,const std::string& filename):
                lunar::Module(name, version, filename){

    }
    
    virtual bool onServerReady() override{
        std::vector<lunar::TcpServer::ptr> svrs;
        lunar::Application::GetInstance()->getServer("http", svrs);

        for(auto& i : svrs){
            lunar::http::HttpServer::ptr hs = std::dynamic_pointer_cast<lunar::http::HttpServer>(i);
            if(hs){
                hs->getServletDispatch()->addServlet("/index", handle);
            }
        }
        return true;
    }

};

int main(){
    // Index id("test", "1.1", "/index");
    lunar::ByteArray::ptr ba(new lunar::ByteArray());
    ba->readFromFile("/root/Lunar/web/img/Lunar.jpg");
    ba->setPosition(0);
    LUNAR_LOG_DEBUG(LUNAR_LOG_ROOT()) << ba->toString();
    return 0;
}

extern "C"{
    lunar::Module* CreateModule(){
        return new Index("/index", "1.1", "index");
    }
    void DestoryModule(lunar::Module* module){
        delete module;
    }
}

