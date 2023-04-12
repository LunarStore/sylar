/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-02-05 16:30
 * LastModified : 2023-02-05 16:30
 * Filename : iomanager.h
 * Description : 1.0 *
 ************************************/

#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

#include<memory>
#include<sys/epoll.h>
#include<vector>
#include<atomic>
#include<functional>
#include<unistd.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include<string.h>

#include"base/scheduler.h"
#include"base/mutex.h"
#include"base/fiber.h"
#include"base/mutex.h"
#include"base/timer.h"
namespace lunar{

    class IOManager: public Scheduler, public TimerManager{
    public:
        typedef RWMutex MutexType;
        typedef std::shared_ptr<IOManager> ptr;
        enum Event{
            NONE    = 0,
            READ    = EPOLLIN,
            WRITE   = EPOLLOUT
        };
        struct FdContext {
            typedef Mutex MutexType;
            struct EventContext{
                void reset();
                Fiber::ptr m_fiber = nullptr;
                std::function<void(void)> m_cb = nullptr;
                Scheduler* m_scheduler = nullptr;
            };
            // nolock
            void TrigleEvent(Event event);
            EventContext& getEventContext(Event event);
            void resetEventContext(Event event);
            EventContext read;
            EventContext write;
            Event m_events = NONE;
            int m_fd = -1;
            MutexType m_mutex;
        };
    public:
        IOManager(uint32_t threadCount = 1, const std::string& name = "",bool useCur = true);
        ~IOManager();
    public:
        void resize(size_t size);
        int addEvent(int fd, Event event, std::function<void(void)> cb = nullptr);
        int delEvent(int fd, Event event);
        int cancelEvent(int fd, Event event);
        int cancelAll(int fd);
    public:
        virtual bool isStoped() override;
        virtual void idle() override;
        virtual void tickle() override;
        virtual void onTimerInsertedFront() override;
    public:
        static IOManager* GetThis();
    private:
        std::vector<FdContext*> m_fdContexts;
        std::atomic<uint32_t> m_penddingEventCount = { 0 };
        int m_pipfd[2];
        int m_epollfd;
        MutexType m_mutex;
    };
}

#endif