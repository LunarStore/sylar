#include"base/timer.h"

namespace lunar{

    //注意加锁！！！！！！！！

    bool Timer::Comparator::operator()(const Timer::ptr& lhs, const Timer::ptr& rhs) const{
        if(!lhs){
            return true;
        }

        if(!rhs){
            return false;
        }
        if(lhs->m_next < rhs->m_next){
            return true;
        }else if(lhs->m_next > rhs->m_next){
            return false;
        }else{
            return lhs.get() < rhs.get();
        }
    }
    Timer::Timer(uint64_t interval, bool isLoop, CallBackType cb, TimerManager* mgr):
        m_interval(interval),
        m_isLoop(isLoop),
        m_cb(cb),
        m_mgr(mgr){
        uint64_t now = lunar::GetCurrentMiliSTime();

        m_next = now + m_interval;
    }
    Timer::Timer(uint64_t next){
        m_next = next;
    }

    void Timer::cancel(){
        //读写锁可以连用吗？？？
        TimerManager::MutexType::WriteLock wlock(m_mgr->m_rwmutex);
        auto pos = m_mgr->m_tss.find(shared_from_this());
        if(pos == m_mgr->m_tss.end()){
            return;
        }
        m_mgr->m_tss.erase(pos);
        wlock.unlock();

        m_cb = nullptr;

    }
    void Timer::refresh(){
        //不必判断mgr是否存在
        TimerManager::MutexType::WriteLock wlock(m_mgr->m_rwmutex);
        auto pos = m_mgr->m_tss.find(shared_from_this());
        if(pos == m_mgr->m_tss.end()){
            return;
        }

        m_mgr->m_tss.erase(pos);
        wlock.unlock();


        m_next = lunar::GetCurrentMiliSTime() + m_interval;

        m_mgr->addTimer(shared_from_this());

    }
    bool Timer::reset(uint64_t intervl, bool fromNow){
        TimerManager::MutexType::WriteLock wlock(m_mgr->m_rwmutex);
        auto pos = m_mgr->m_tss.find(shared_from_this());
        if(pos == m_mgr->m_tss.end()){
            return false;
        }

        m_mgr->m_tss.erase(pos);
        wlock.unlock();

        time_t start;
        if(fromNow){
            start = lunar::GetCurrentMiliSTime();
        }else{
            start = m_next - m_interval;
        }

        m_next = start + intervl;
        m_interval = intervl;

        m_mgr->addTimer(shared_from_this());
        return true;
    }

    Timer::ptr TimerManager::addTimer(uint64_t interval, Timer::CallBackType cb, bool isLoop){
        Timer::ptr time(new Timer(interval, isLoop, cb, this));

        if(addTimer(time)){
            return time;
        }else{
            return nullptr;
        }

        return nullptr;

    }
    bool TimerManager::addTimer(Timer::ptr time){
        MutexType::WriteLock wlock(m_rwmutex);
        if(time->m_cb == nullptr){
            return false;
        }
        auto pos = m_tss.insert(time).first;
        //插到前面需要tickle;
        if(pos == m_tss.begin()){
            wlock.unlock();
            //唤醒等待旧定时器的线程
            onTimerInsertedFront();
        }

        return true;
    }

    void TimerManager::listAllExpire(std::vector<std::function<void (void) >>& cbs){

        //不能采用加读锁后加写锁的方式，关读锁后到加写锁的过程中，可能会导致不一致，出现线程安全问题。
        Timer::ptr now_t(new Timer(lunar::GetCurrentMiliSTime()));

        MutexType::WriteLock wlock(m_rwmutex);
        auto end = m_tss.upper_bound(now_t);
        std::vector<Timer::ptr> expired(m_tss.begin(), end);

        cbs.reserve(expired.size());

        m_tss.erase(m_tss.begin(), end);

        for(auto itr = expired.begin(); itr != expired.end(); itr++){
            cbs.push_back((*itr)->m_cb);
            if((*itr)->m_isLoop){
                (*itr)->m_next = (*itr)->m_interval + now_t->m_next;
                m_tss.insert(*itr);
            }else{
                (*itr)->m_cb = nullptr;
                //(*itr)->m_next = ~0ull;
            }
        }
    }

    time_t TimerManager::getFirstTimeOut(){
        MutexType::ReadLock rlock(m_rwmutex);
        //
        if(m_tss.begin() == m_tss.end()){
            return ~0ull;
        }
        return (*m_tss.begin())->m_next;
    }

    bool TimerManager::hasTimer(){
        MutexType::ReadLock rlock(m_rwmutex);
        return !m_tss.empty();
    }

}