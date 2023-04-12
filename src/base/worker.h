/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-03-05 09:53
 * LastModified : 2023-03-05 09:53
 * Filename : worker.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_WORKER_H__
#define __LUNAR_WORKER_H__

#include "base/mutex.h"
#include "base/singleton.h"
#include "base/log.h"
#include "base/iomanager.h"

namespace lunar {

    class WorkerManager {
    public:
        WorkerManager();
        void add(Scheduler::ptr s);
        Scheduler::ptr get(const std::string& name);
        IOManager::ptr getAsIOManager(const std::string& name);

        template<class FiberOrCb>
        void schedule(const std::string& name, FiberOrCb fc, int thread = -1) {
            auto s = get(name);
            if(s) {
                s->schedule(fc, thread);
            } else {
                static lunar::Logger::ptr s_logger = LUNAR_LOG_NAME("system");
                LUNAR_LOG_ERROR(LUNAR_LOG_NAME("system")) << "schedule name=" << name
                    << " not exists";
            }
        }

        template<class Iter>
        void schedule(const std::string& name, Iter begin, Iter end) {
            auto s = get(name);
            if(s) {
                s->schedule(begin, end);
            } else {
                static lunar::Logger::ptr s_logger = LUNAR_LOG_NAME("system");
                LUNAR_LOG_ERROR(LUNAR_LOG_NAME("system")) << "schedule name=" << name
                    << " not exists";
            }
        }

        bool init();
        bool init(const std::map<std::string, std::map<std::string, std::string> >& v);
        void stop();

        bool isStoped() const { return m_stop;}
        std::ostream& dump(std::ostream& os);

        uint32_t getCount();
    private:
        std::map<std::string, std::vector<Scheduler::ptr> > m_datas;
        bool m_stop;
    };

    typedef lunar::Singleton<WorkerManager> WorkerMgr;

}

#endif
