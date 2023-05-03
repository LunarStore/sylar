#include"base/thread.h"
#include<string.h>

namespace lunar{
    static thread_local Thread* t_thread = nullptr;
    static thread_local std::string t_thread_name("unknow");

    static Logger::ptr g_logger = LUNAR_LOG_NAME("system");
    Thread::Thread(const CallBackType& cb, const std::string& name): m_id(-1), m_pthread(0), m_name(name), m_cb(cb), m_sem(0){

        if(name.empty()){
            m_name = "unknow";
        }
        int rt = pthread_create(&m_pthread, nullptr, &Thread::Run, this);
        if(rt){
            LUNAR_LOG_ERROR(g_logger) << "pthread_create(...) fail, rt = "
                << rt << "thread name = " 
                << m_name;
            throw std::logic_error("pthread_create error");
        }

        m_sem.wait();
    }

    const std::string& Thread::GetName(){
        return t_thread_name;
    }

    void Thread::SetName(const std::string& name){
        if(t_thread){
            t_thread->m_name = t_thread_name = name;
        }else{
            t_thread_name = "unknow";
        }
    }

    Thread* Thread::GetThis(){
        if(t_thread){
            return t_thread;
        }else{
            return nullptr;
        }
    }

    void Thread::join(){
        if(m_pthread){
            int rt = pthread_join(m_pthread, nullptr);
            if(rt){
                LUNAR_LOG_ERROR(g_logger) << "pthread_join(...) fail, rt = "
                    << rt << "thread name = " 
                    << m_name;
                throw std::logic_error("pthread_join error");
            }
            m_pthread = 0;
        }
    }
    const std::string& Thread::getName(){
        return m_name;
    }
    Thread::~Thread(){
        if(m_pthread){
            int rt = pthread_detach(m_pthread);
            if(rt){
                LUNAR_LOG_ERROR(g_logger) << "pthread_detach(...) fail, rt = "
                    << rt << "thread name = " 
                    << m_name << "<" << strerror(rt) << ">";
            }
        }
        LUNAR_LOG_DEBUG(g_logger) << "Thread::~Thread()";
    }

    void* Thread::Run(void* arg){
        Thread* thread = ((Thread *)arg);

        t_thread = thread;
        t_thread_name = thread->m_name;
        thread->m_id = GetThreadId();
        pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str());

        thread->m_sem.post();
        CallBackType cb;
        cb.swap(thread->m_cb);

        cb();

        return nullptr;
    }

}
