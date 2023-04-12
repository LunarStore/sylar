/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-01-29 15:35
 * LastModified : 2023-01-29 15:35
 * Filename : thread.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_THREAD_H__

#define __LUNAR_THREAD_H__
#include<memory>
#include<pthread.h>
#include<functional>
#include<string>

#include"base/util.h"
#include"base/log.h"
#include"base/mutex.h"
#include"base/noncopyable.h"
namespace lunar{

    class Thread : public std::enable_shared_from_this<Thread>, Noncopyable{
    public:
        typedef std::shared_ptr<Thread> ptr;
        typedef std::function<void(void)> CallBackType;
    public:
        Thread(const CallBackType& cb, const std::string& name = "unknow");
        ~Thread();
    public:
        static void* Run(void* arg);
        static const std::string& GetName();
        static void SetName(const std::string& name);
        static Thread::ptr GetThis();
    public:
        void join();
        //void setName(const std::string name);
        const std::string& getName();
        pid_t getThreadId() { return m_id; }
    private:
        //真实线程（进程）id
        pid_t m_id;
        //Posix定义的id
        pthread_t m_pthread;
        //线程名
        std::string m_name;
        //线程回调函数
        CallBackType m_cb;
        Semaphore m_sem;
    };
}

#endif