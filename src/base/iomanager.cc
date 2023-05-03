#include"base/iomanager.h"
#include"base/macro.h"
namespace lunar{

    static Logger::ptr g_logger = LUNAR_LOG_NAME("system");
    void IOManager::FdContext::EventContext::reset(){
        m_fiber.reset();
        m_cb = nullptr;
        m_scheduler = nullptr;
    }

    void IOManager::FdContext::TrigleEvent(Event event){
        if(!(m_events & event)){
            return;
        }
        m_events = (Event)(m_events & (~event));
        EventContext& ectx = getEventContext(event);
        LUNAR_ASSERT((ectx.m_fiber || ectx.m_cb) && (ectx.m_scheduler != nullptr));

        if(ectx.m_fiber){
            ectx.m_scheduler->schedule(&ectx.m_fiber);
        }else{
            ectx.m_scheduler->schedule(&ectx.m_cb);
        }

        resetEventContext(event);
    }

    IOManager::FdContext::EventContext& IOManager::FdContext::getEventContext(Event event){
        switch(event){
            case READ:
                return read;
                break;
            case WRITE:
                return write;
                break;
            default: break;
        }
        LUNAR_ASSERT2(false, "unknow Event");
    }

    void IOManager::FdContext::resetEventContext(Event event){
        switch(event){
            case READ:
                read.reset();
                return;
            case WRITE:
                write.reset();
                return;
            default: break;
        }
        LUNAR_ASSERT2(false, "unknow Event");
    }

    IOManager::IOManager(uint32_t threadCount, const std::string& name,bool useCur):
        Scheduler(threadCount, name, useCur){
        //将pipfd读端设置成非阻塞。
        int flag = 0;
        int rt = 0;
        rt = pipe(m_pipfd);
        LUNAR_ASSERT(rt == 0);
        flag = fcntl(m_pipfd[0], F_GETFL);
        rt = fcntl(m_pipfd[0], F_SETFL, flag | O_NONBLOCK);
        LUNAR_ASSERT(rt == 0);

        //fd可读/边沿触发
        m_epollfd = epoll_create(50);
        epoll_event epevent = { 0 };
        epevent.events = EPOLLIN | EPOLLET;
        epevent.data.fd = m_pipfd[0];
        rt = epoll_ctl(m_epollfd, EPOLL_CTL_ADD, m_pipfd[0], &epevent);

        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "epoll_ctl(" << m_epollfd <<", "
                << EPOLL_CTL_ADD << ", "<<m_pipfd[0] << ", " << epevent.events << ")";
            LUNAR_ASSERT(false);
        }
        resize(32);

        start();
    }

    IOManager::~IOManager(){
        stop();
        close(m_pipfd[0]);
        close(m_pipfd[1]);
        close(m_epollfd);
        for(size_t i = 0; i < m_fdContexts.size(); i++){
            delete m_fdContexts[i];
        }
    }
    void IOManager::resize(size_t size){
        MutexType::WriteLock wrlock(m_mutex);
        if(size <= m_fdContexts.size()){
            //不可减少
            return;
        }
        m_fdContexts.resize(size);
        for(size_t i = 0; i < size; i++){
            if(m_fdContexts[i] == nullptr){
                m_fdContexts[i] = new FdContext;
                m_fdContexts[i]->m_fd = i;
            }
        }
    }

    int IOManager::addEvent(int fd, Event event, std::function<void(void)> cb){
        MutexType::ReadLock rdlock(m_mutex);
        if((int)m_fdContexts.size() <= fd){
            rdlock.unlock();
            resize(fd * 1.5);
        }
        rdlock.lock();
        FdContext* fdctx = m_fdContexts[fd];
        rdlock.unlock();

        FdContext::MutexType::Lock lock(fdctx->m_mutex);
        if(fdctx->m_events & event){
            //事件存在
            LUNAR_LOG_ERROR(g_logger) << "fd = " << fd 
                <<", event = " << event 
                <<" many time add";
            LUNAR_ASSERT(false);
        }

        int op = fdctx->m_events ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
        epoll_event epevent = { 0 };
        epevent.events = event | EPOLLET;
        epevent.data.ptr = fdctx;

        int rt = epoll_ctl(m_epollfd, op, fd, &epevent);
        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "epoll_ctl(" << m_epollfd <<", "
                << op << ", "<< fd << ", " << epevent.events << "):"
                << "<errno[" << errno <<"]:"<< strerror(errno) << ">";
            
            return -1;
        }
        m_penddingEventCount++;
        fdctx->m_events = (Event)(fdctx->m_events | event);
        FdContext::EventContext& ectx = fdctx->getEventContext(event);

        LUNAR_ASSERT(!ectx.m_cb && !ectx.m_fiber && !ectx.m_scheduler);

        if(cb){
            ectx.m_cb = cb;
            //error note: 不能用shared_from_this
            //ectx.m_scheduler = Scheduler::GetThis() || shared_from_this();
        }else{
            ectx.m_fiber = Fiber::GetThis();
        }
        ectx.m_scheduler = Scheduler::GetThis() ? Scheduler::GetThis()  : this;

        return 0;
    }

    int IOManager::delEvent(int fd, Event event){
        MutexType::ReadLock rdlock(m_mutex);
        if((int)m_fdContexts.size() <= fd){
            //fd过大
            return -1;
        }
        FdContext* fdctx = m_fdContexts[fd];
        rdlock.unlock();


        FdContext::MutexType::Lock lock(fdctx->m_mutex);
        if(!(fdctx->m_events & event)){
            //事件不存在
            return -1;
        }
        Event leftEvent = (Event)(fdctx->m_events & (~event));
        int op = leftEvent ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
        epoll_event epevent = { 0 };
        epevent.events = leftEvent | EPOLLET;
        epevent.data.ptr = fdctx;

        int rt = epoll_ctl(m_epollfd, op, fd, &epevent);
        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "epoll_ctl(" << m_epollfd <<", "
                << op << ", "<< fd << ", " << epevent.events << "):"
                << "<errno[" << errno <<"]:"<< strerror(errno) << ">";
            
            return -1;
        }
        m_penddingEventCount--;
        fdctx->m_events = leftEvent;
        fdctx->resetEventContext(event);
        return 0;
    }

    int IOManager::cancelEvent(int fd, Event event){
        MutexType::ReadLock rdlock(m_mutex);
        if((int)m_fdContexts.size() <= fd){
            //fd过大
            return -1;
        }
        FdContext* fdctx = m_fdContexts[fd];
        rdlock.unlock();
        
        FdContext::MutexType::Lock lock(fdctx->m_mutex);
        if(!(fdctx->m_events & event)){
            //事件不存在
            return -1;
        }
        Event leftEvent = (Event)(fdctx->m_events & (~event));
        int op = leftEvent ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
        epoll_event epevent = { 0 };
        epevent.events = leftEvent | EPOLLET;
        epevent.data.ptr = fdctx;

        int rt = epoll_ctl(m_epollfd, op, fd, &epevent);
        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "epoll_ctl(" << m_epollfd <<", "
                << op << ", "<< fd << ", " << epevent.events << "):"
                << "<errno[" << errno <<"]:"<< strerror(errno) << ">";
            
            return -1;
        }
        fdctx->TrigleEvent(event);
        m_penddingEventCount--;
        return 0;
    }

    int IOManager::cancelAll(int fd){
        MutexType::ReadLock rdlock(m_mutex);
        if((int)m_fdContexts.size() <= fd){
            //fd过大
            return -1;
        }
        FdContext* fdctx = m_fdContexts[fd];
        rdlock.unlock();

        FdContext::MutexType::Lock lock(fdctx->m_mutex);
        if(fdctx->m_events == NONE){
            //没有一个事件
            return -1;
        }
        Event hasEvent = (Event)(fdctx->m_events);
        int op = EPOLL_CTL_DEL;
        epoll_event epevent = { 0 };
        epevent.events = NONE;
        epevent.data.ptr = fdctx;

        int rt = epoll_ctl(m_epollfd, op, fd, &epevent);
        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "epoll_ctl(" << m_epollfd <<", "
                << op << ", "<< fd << ", " << epevent.events << "):"
                << "<errno[" << errno <<"]:"<< strerror(errno) << ">";
            
            return -1;
        }
        if(hasEvent & READ){
            fdctx->TrigleEvent(READ);
            m_penddingEventCount--;
        }

        if(hasEvent & WRITE){
            fdctx->TrigleEvent(WRITE);
            m_penddingEventCount--;
        }

        return 0;
    }

    bool IOManager::isStoped(){
        return Scheduler::isStoped() && 
            m_penddingEventCount == 0 &&
            !(TimerManager::hasTimer());
    }

    static const uint32_t MAXFD = 256;
    static uint64_t MAX_TIMEOUT = 3000;
    void IOManager::idle(){
        epoll_event* epevents = new epoll_event[MAXFD]();
        std::shared_ptr<epoll_event> shared_event(epevents ,[](epoll_event *ptr){
            delete[] ptr;
        });
        while(!isStoped()){
            int rt = 0;
            do{
                uint64_t curTime = lunar::GetCurrentMiliSTime();
                uint64_t firstTimerTime = TimerManager::getFirstTimeOut();
                uint64_t timeOut = firstTimerTime > curTime ? firstTimerTime - curTime : 0;

                timeOut = std::min(timeOut, MAX_TIMEOUT);
                rt = epoll_wait(m_epollfd, epevents, MAXFD, (time_t)timeOut);
            }while((rt < 0) && (errno == EINTR));

            std::vector<Timer::CallBackType> cbs;
            TimerManager::listAllExpire(cbs);

            Scheduler::schedule(cbs.begin(), cbs.end());
            for(int i = 0; i < rt; i++){
                //pip IO
                if(epevents[i].data.fd == m_pipfd[0]){
                    char pipbuf[256];
                    LUNAR_LOG_DEBUG(g_logger) << "tickle";
                    while(read(m_pipfd[0], pipbuf, 256) > 0);

                    continue;
                }
                //else
                //socket IO
                FdContext* fdctx = (FdContext*)(epevents[i].data.ptr);
                Event triEvent = (Event)((READ | WRITE) & epevents[i].events);

                if((epevents[i].events & EPOLLHUP) || (epevents[i].events & EPOLLERR)){
                    triEvent = (Event)(epevents[i].events | READ | WRITE); 
                }

                FdContext::MutexType::Lock lock(fdctx->m_mutex);
                if((fdctx->m_events & triEvent) == NONE){
                    continue;
                }

                int fd = fdctx->m_fd;
                Event leftEvent = (Event)(fdctx->m_events &(~triEvent));
                int op = leftEvent ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
                epoll_event epe = { 0 };
                epe.events = leftEvent | EPOLLET;
                epe.data.ptr = fdctx;

                int rteCtl = epoll_ctl(m_epollfd, op, fd, &epe);
                if(rteCtl){
                    //修改m_epollfd set失败，下次还会触发，所以continue就好了
                    LUNAR_LOG_ERROR(g_logger) << "epoll_ctl(" << m_epollfd <<", "
                        << op << ", "<< fd << ", " << epe.events << "):"
                        << "<errno[" << errno <<"]:"<< strerror(errno) << ">";
                        continue;
                }

                if(triEvent & READ){
                    fdctx->TrigleEvent(READ);
                    m_penddingEventCount--;
                }

                if(triEvent & WRITE){
                    fdctx->TrigleEvent(WRITE);
                    m_penddingEventCount--;
                }
                
            }

            Fiber::YieldToHold();
        }
    }
    void IOManager::tickle() {
        if(!HasIdleThread()) return;
        int rt = write(m_pipfd[1], "T", 1);
        LUNAR_ASSERT(rt == 1);
        //LUNAR_LOG_DEBUG(g_logger) << "tickle" << rt << strerror(errno) << m_pipfd[1];
    }
    void IOManager::onTimerInsertedFront(){
        tickle();
    }
    IOManager* IOManager::GetThis(){
        return dynamic_cast<IOManager*>(Scheduler::GetThis());
    }
}