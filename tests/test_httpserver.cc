#include "http/httpserver.h"
#include "base/log.h"
#include "http/servlet.h"
static lunar::Logger::ptr g_logger = LUNAR_LOG_ROOT();

#define XX(...) #__VA_ARGS__


lunar::IOManager::ptr worker;
void run() {
    g_logger->setLevel(lunar::LogLevel::INFO);
    //lunar::http::HttpServer::ptr server(new lunar::http::HttpServer(true, worker.get(), lunar::IOManager::GetThis()));
    lunar::http::HttpServer::ptr server(new lunar::http::HttpServer(true));
    lunar::Address::ptr addr = lunar::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/sylar/xx", [](lunar::http::HttpRequest::ptr req
                ,lunar::http::HttpResponse::ptr rsp
                ,lunar::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/sylar/*", [](lunar::http::HttpRequest::ptr req
                ,lunar::http::HttpResponse::ptr rsp
                ,lunar::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/sylarx/*", [](lunar::http::HttpRequest::ptr req
                ,lunar::http::HttpResponse::ptr rsp
                ,lunar::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });

    server->start();
}

int main(int argc, char** argv) {
    lunar::IOManager iom(2, "main", true);
    worker.reset(new lunar::IOManager(3,  "worker", false));
    iom.schedule(run);
    return 0;
}
