/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-02-02 09:37
 * LastModified : 2023-02-02 09:37
 * Filename : scheduler.h
 * Description : 1.0 *
 ************************************/

#ifndef __SCHEDULER_H__

#define __SCHEDULER_H__
#include<list>
#include<memory>
#include<vector>
#include<atomic>
#include<functional>

#include"base/fiber.h"
#include"base/thread.h"
#include"base/log.h"
#include"base/thread.h"
#include"base/util.h"
#include"base/mutex.h"
namespace lunar{
    //类线程池
    class Scheduler : public std::enable_shared_from_this<Scheduler>{
    public:
        typedef std::shared_ptr<Scheduler> ptr;
        typedef Mutex MutexType;
    protected:
        struct FiberAndThread{
        public:
            Fiber::ptr m_fiber;
            std::function<void(void)> m_cb;
            pid_t m_tId;
        public:
            FiberAndThread(): m_fiber(nullptr), m_cb(nullptr), m_tId(-1) {  };
            FiberAndThread(Fiber::ptr f, pid_t tId): m_fiber(f),m_cb(nullptr), m_tId(tId) {  }

            FiberAndThread(Fiber::ptr* fp, pid_t tId): m_cb(nullptr), m_tId(tId) {
                swap(m_fiber, *fp);
            }

            FiberAndThread(std::function<void(void)> cb, pid_t tId): m_fiber(nullptr), m_cb(cb), m_tId(tId) {  }

            FiberAndThread(std::function<void(void)>* cb, pid_t tId): m_fiber(nullptr), m_tId(tId){
                swap(m_cb, *cb);
            }
        };
    public:
        Scheduler(uint32_t threadCount, const std::string& name,bool useCur = true);
        ~Scheduler();
        const std::string& getName() const { return m_name;}
        void start();
        void stop();
        void run();
        bool HasIdleThread() { return m_idleThreadCount != 0; };
    public:
        virtual bool isStoped();
        virtual void idle();
        virtual void tickle();
    public:
        static Scheduler* GetThis();
        
        static Fiber::ptr GetScheRunFiber();
        std::ostream& dump(std::ostream& os);
    public:
        template<typename FiberOrCb>
        void schedule(FiberOrCb fOrcb, pid_t tId = -1){
            bool needTickle = false;
            {
                MutexType::Lock lock(m_mutex);

                needTickle = scheduleNoLock(fOrcb, tId);
            }

            if(needTickle){
                tickle();
            }
        }

        template<typename ForwardIterator>
        void schedule(ForwardIterator begin, ForwardIterator end, pid_t tId = -1){
            bool needTickle = false;
            {
                MutexType::Lock lock(m_mutex);

                for(ForwardIterator itr = begin;
                    itr != end; itr++){
                    needTickle = scheduleNoLock(*itr, tId) || needTickle;
                }
            }

            if(needTickle){
                tickle();
            }
        }
    protected:
        template<typename FiberOrCb>
        bool scheduleNoLock(FiberOrCb fOrCb, pid_t tId){
            bool needTickle = m_tasks.empty();
            FiberAndThread fiC(fOrCb, tId);
            if(fiC.m_cb || fiC.m_fiber){
                m_tasks.push_back(fiC);
            }

            return needTickle;
        }
    private:
        uint32_t m_threadCount;
        std::string m_name;
        std::list<FiberAndThread> m_tasks;

        std::vector<Thread::ptr> m_threadPool;

        std::vector<pid_t> m_threadIds;
        std::atomic<uint32_t> m_activeThreadCount = { 0 };
        std::atomic<uint32_t> m_idleThreadCount = { 0 };

        Fiber::ptr m_rootFiber;
        pid_t m_rootThreadId;
        bool m_stop;
        MutexType  m_mutex;
    };
}


#endif