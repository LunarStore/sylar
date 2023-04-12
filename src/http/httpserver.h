/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-03-02 16:55
 * LastModified : 2023-03-02 16:55
 * Filename : httpserver.h
 * Description : 1.0 *
 ************************************/


#ifndef __LUNAR_HTTP_SERVER_H__
#define __LUNAR_HTTP_SERVER_H__

#include "net/tcpserver.h"
#include "http/httpsession.h"
#include "http/servlet.h"

namespace lunar {
    namespace http {

        /**
         * @brief HTTP服务器类
         */
        class HttpServer : public TcpServer {
        public:
            /// 智能指针类型
            typedef std::shared_ptr<HttpServer> ptr;

            /**
             * @brief 构造函数
             * @param[in] keepalive 是否长连接
             * @param[in] worker 工作调度器
             * @param[in] accept_worker 接收连接调度器
             */
            HttpServer(bool keepalive = false
                    ,lunar::IOManager* worker = lunar::IOManager::GetThis()
                    ,lunar::IOManager* io_worker = lunar::IOManager::GetThis()
                    ,lunar::IOManager* accept_worker = lunar::IOManager::GetThis());

            /**
             * @brief 获取ServletDispatch
             */
            ServletDispatch::ptr getServletDispatch() const { return m_dispatch;}

            /**
             * @brief 设置ServletDispatch
             */
            void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v;}

            virtual void setName(const std::string& v) override;
        protected:
            virtual void handleClient(Socket::ptr client) override;
        private:
            /// 是否支持长连接
            bool m_isKeepalive;
            /// Servlet分发器
            ServletDispatch::ptr m_dispatch;
        };

    }
}

#endif
