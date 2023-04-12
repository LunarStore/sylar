#include "http/httpserver.h"
#include "base/log.h"
// #include "sylar/http/servlets/config_servlet.h"
// #include "sylar/http/servlets/status_servlet.h"

namespace lunar {
    namespace http {

        static lunar::Logger::ptr g_logger = LUNAR_LOG_NAME("system");

        HttpServer::HttpServer(bool keepalive
                    ,lunar::IOManager* worker
                    ,lunar::IOManager* io_worker
                    ,lunar::IOManager* accept_worker)
            :TcpServer(worker, io_worker, accept_worker)
            ,m_isKeepalive(keepalive) {
            m_dispatch.reset(new ServletDispatch);

            m_type = "http";
            // m_dispatch->addServlet("/_/status", Servlet::ptr(new StatusServlet));
            // m_dispatch->addServlet("/_/config", Servlet::ptr(new ConfigServlet));
        }

        void HttpServer::setName(const std::string& v) {
            TcpServer::setName(v);
            m_dispatch->setDefault(std::make_shared<NotFoundServlet>(v));
        }

        void HttpServer::handleClient(Socket::ptr client) {
            LUNAR_LOG_DEBUG(g_logger) << "handleClient " << *client;
            HttpSession::ptr session(new HttpSession(client));
            do {
                auto req = session->recvRequest();
                if(!req) {
                    LUNAR_LOG_DEBUG(g_logger) << "recv http request fail, errno="
                        << errno << " errstr=" << strerror(errno)
                        << " cliet:" << *client << " keep_alive=" << m_isKeepalive;
                    break;
                }

                HttpResponse::ptr rsp(new HttpResponse(req->getVersion()
                                    ,req->isClose() || !m_isKeepalive));
                rsp->setHeader("Server", getName());
                m_dispatch->handle(req, rsp, session);
                session->sendResponse(rsp);

                if(!m_isKeepalive || req->isClose()) {
                    break;
                }
            } while(true);
            session->close();
        }

    }
}
