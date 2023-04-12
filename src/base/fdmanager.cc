#include"base/fdmanager.h"


namespace lunar{
    static Logger::ptr g_logger = LUNAR_LOG_NAME("system");

    FdCtx::FdCtx(int fd):m_isClosed(false),
        m_isUserNonBlock(false),
        m_isSysNonBlock(false),
        m_isSocket(false),
        m_recvTimeout(-1),
        m_sendTimeout(-1),
        m_fd(fd){
        init();
    }
    void FdCtx::init(){
        m_recvTimeout = -1;
        m_sendTimeout = -1;
        struct stat fd_stat = { 0 };
        if((-1 == fstat(m_fd, &fd_stat))){
            m_isSysNonBlock = false;
            m_isSocket = false;
        }else{
            m_isSocket = S_ISSOCK(fd_stat.st_mode);
        }

        if(m_isSocket){
            int flags = fcntl_f(m_fd, F_GETFL, 0);

            if(flags == -1){
                LUNAR_LOG_ERROR(g_logger) << "fcntl_f("
                    << m_fd << ","
                    << F_GETFL << ","
                    << 0  <<")";
                LUNAR_ASSERT(false);
            }
            if(!(flags & O_NONBLOCK)){
                fcntl_f(m_fd, F_SETFL, flags | O_NONBLOCK);
            }
            m_isSysNonBlock = true;

        }else{
            m_isSysNonBlock = false;
        }

        m_isClosed = false;
        m_isUserNonBlock = false;
    }

    uint64_t FdCtx::getTimeout(int type) const{
        if(type == SO_RCVTIMEO) {
            return m_recvTimeout;
        } else {
            return m_sendTimeout;
        }
    }
    void FdCtx::setTimeout(int type, uint64_t v){
        if(type == SO_RCVTIMEO) {
            m_recvTimeout = v;
        } else {
            m_sendTimeout = v;
        }
    }
    FdManager::FdManager(){
        m_fdCtxs.resize(64);
    }
    FdCtx::ptr FdManager::get(int fd, bool autoCreate){
        if(fd == -1){
            return nullptr;
        }
        MutexType::Lock lock(m_mutex);

        if(fd >= (int)m_fdCtxs.size()){
            if(autoCreate){
                m_fdCtxs.resize(fd * 1.5);
            }else{
                return nullptr;
            }
        }

        if(m_fdCtxs[fd] == nullptr && autoCreate){
            m_fdCtxs[fd].reset(new FdCtx(fd));
        }

        return m_fdCtxs[fd];
    }
    void FdManager::del(int fd){
        MutexType::Lock lock(m_mutex);
        if(fd >= (int)m_fdCtxs.size()){
            return;
        }

        m_fdCtxs[fd].reset();
    }
}