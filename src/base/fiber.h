/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-01-31 19:05
 * LastModified : 2023-01-31 19:05
 * Filename : fiber.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_FIBER_H__
#define __LUNAR_FIBER_H__
#include<memory>
#include<atomic>
#include<stdint.h>
#include<ucontext.h>
#include<functional>
#include <stdlib.h>



#include"base/macro.h"
#include"base/log.h"
namespace lunar{
    class Fiber :public std::enable_shared_from_this<Fiber>{
    public:
        typedef std::shared_ptr<Fiber> ptr;
        typedef std::function<void(void)> CallBackType;
        enum State{
            INIT,
            EXEC,
            TERM,
            EXCE,
            HOLD
        };

    public:
        Fiber(CallBackType cb, bool withThread = false, uint32_t stackSize = 0);
        Fiber();
        ~Fiber();
    public:
        void swapIn();
        State getState() { return m_state; };
        uint32_t getId() { return m_id; };
        void reset(CallBackType cb);
    private:
        void swapOut();
    public:
        static void MainFun();
        static void YieldToHold();
        static Fiber::ptr GetThis();
        static void SetThis(Fiber::ptr fiberPtr);
        static uint32_t GetFiberId();
    private:
        CallBackType m_cb;
        State m_state;
        uint32_t m_id;
        ucontext_t m_ctx;
        uint32_t m_stackSize;
        bool m_withThread;
        void* m_stackPtr;
    };
}

#endif