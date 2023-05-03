/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-02-16 15:50
 * LastModified : 2023-02-16 15:50
 * Filename : timer.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_TIMER_H__
#define __LUNAR_TIMER_H__
#include<stdint.h>
#include<functional>
#include<memory>
#include<set>
#include<vector>
#include<functional>
#include<algorithm>
#include <sys/types.h>
#include <dirent.h>

#include"base/util.h"
#include"base/mutex.h"
namespace lunar{
    class TimerManager;
    class Timer: public std::enable_shared_from_this<Timer>{
        friend class TimerManager;
    public:
        typedef std::shared_ptr<Timer> ptr;
        typedef std::function<void(void)> CallBackType;
        struct Comparator{
            bool operator()(const Timer::ptr& lhs, const Timer::ptr& rhs) const;
        };
    public:
        Timer(uint64_t interval, bool isLoop, CallBackType cb, TimerManager* mgr);
        Timer(uint64_t next);

        void cancel();
        void refresh();
        bool reset(uint64_t itl, bool fromNow);
    private:
        //间隔
        uint64_t m_interval = 0;
        //下一次执行时间;
        uint64_t m_next = ~0ull;
        //是否循环
        bool m_isLoop = false;
        CallBackType m_cb = nullptr;
        TimerManager* m_mgr = nullptr;
    };

    class TimerManager{
        friend class Timer;
    public:
        //typedef std::shared_ptr<TimerManager> ptr;
        typedef std::set<Timer::ptr, Timer::Comparator> TimerSetType;
        typedef RWMutex MutexType;
    public:
        Timer::ptr addTimer(uint64_t interval, Timer::CallBackType cb, bool isLoop = false);
        bool addTimer(Timer::ptr time);

        void listAllExpire(std::vector<std::function<void (void) >>& cbs);
        uint64_t getFirstTimeOut();
        bool hasTimer();
    public:
        virtual void onTimerInsertedFront() = 0;
        virtual ~TimerManager(){}
    private:
        TimerSetType m_tss;
        MutexType m_rwmutex;
    };
}

#endif