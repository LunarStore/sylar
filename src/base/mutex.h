/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-01-30 16:46
 * LastModified : 2023-01-30 16:46
 * Filename : mutex.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_MUTEX_H__
#define __LUNAR_MUTEX_H__
#include <semaphore.h>
#include <stdint.h>
#include<string.h>
#include <pthread.h>


#include "base/noncopyable.h"
namespace lunar{
    class Semaphore : Noncopyable{
    public:
        Semaphore(uint32_t count = 0);
        ~Semaphore();
        void wait();

        void post();
    private:
        sem_t m_semaphore;
    };


    template<typename T>
    class ScopedLockImpl{
    public:
        ScopedLockImpl(T& mutex) : m_mutex(mutex){
            m_locked = false;
            lock();
        }
        ~ScopedLockImpl(){
            unlock();
        }
        void lock(){
            if(!m_locked){
                m_locked = true;
                m_mutex.lock();
            }
        }
        void unlock(){
            if(m_locked){
                m_mutex.unlock();
                m_locked = false;
            }
        }
    private:
        T& m_mutex;
        bool m_locked;
    };

    template<typename T>
    class ReadScopedLockImpl{
    public:
        ReadScopedLockImpl(T& rwMutex) : m_rwMutex(rwMutex){
            m_locked = false;
            lock();
        }
        ~ReadScopedLockImpl(){
            unlock();
        }
        void lock(){
            if(!m_locked){
                m_locked = true;
                m_rwMutex.rdLock();
            }
        }
        void unlock(){
            if(m_locked){
                m_rwMutex.unlock();
                m_locked = false;
            }
        }
    private:
        T& m_rwMutex;
        bool m_locked;
    };


    template<typename T>
    class WriteScopedLockImpl{
    public:
        WriteScopedLockImpl(T& rwMutex) : m_rwMutex(rwMutex){
            m_locked = false;
            lock();
        }
        ~WriteScopedLockImpl(){
            unlock();
        }
        void lock(){
            if(!m_locked){
                m_locked = true;
                m_rwMutex.wrLock();
            }
        }
        void unlock(){
            if(m_locked){
                m_rwMutex.unlock();
                m_locked = false;
            }
        }
    private:
        T& m_rwMutex;
        bool m_locked;
    };


    class Mutex : Noncopyable{
    public:
        typedef ScopedLockImpl<Mutex> Lock;
    public:
        Mutex(){
            pthread_mutex_init(&m_mutex, nullptr);
        }
        ~Mutex(){
            pthread_mutex_destroy(&m_mutex);
        }
        void lock(){
            pthread_mutex_lock(&m_mutex);
        }
        void unlock(){
            pthread_mutex_unlock(&m_mutex);
        }
    private:
        pthread_mutex_t m_mutex;
    };

    class RWMutex : Noncopyable{
    public:
        typedef ReadScopedLockImpl<RWMutex>  ReadLock;
        typedef WriteScopedLockImpl<RWMutex>  WriteLock;
    public:
        RWMutex(){
            pthread_rwlock_init(&m_rwMutex, nullptr);
        }
        ~RWMutex(){
            pthread_rwlock_destroy(&m_rwMutex);
        }
        void rdLock(){
            pthread_rwlock_rdlock(&m_rwMutex);
        }

        void wrLock(){
            pthread_rwlock_wrlock(&m_rwMutex);
        }

        void unlock(){
            pthread_rwlock_unlock(&m_rwMutex);
        }
    private:
        pthread_rwlock_t m_rwMutex;
    };

}


#endif