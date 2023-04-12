#include"base/fiber.h"
#include"base/config.h"
#include"base/scheduler.h"
namespace lunar{
    static std::atomic<uint32_t> s_fiber_id = { 0 };
    static std::atomic<uint32_t> s_fiber_count = { 0 };
    //切缘到线程的协程
    static thread_local Fiber::ptr t_threadFiber(nullptr);
    //当前执行的协程
    static thread_local Fiber::ptr t_fiber(nullptr);

    static ConfigVar<uint32_t>::ptr g_stack_size = ConfigVarMgr::GetInstance()->lookUp("fiber.stackSize", uint32_t(1024*1024), "fiber's stack size");
    
    static Logger::ptr g_logger = LUNAR_LOG_NAME("system");

    Fiber::Fiber(CallBackType cb, bool withThread, uint32_t stackSize): m_cb(cb), m_withThread(withThread){
        //lunar::Fiber::GetThis();
        s_fiber_count++;
        m_id = s_fiber_id++;
        m_state = INIT;

        m_stackSize = stackSize ? stackSize : g_stack_size->getValue();
        m_stackPtr = (void*)malloc(m_stackSize);

        LUNAR_ASSERT2(getcontext(&m_ctx) == 0, "getcontext(...)");
        m_ctx.uc_link = nullptr;
        m_ctx.uc_stack.ss_sp = m_stackPtr;
        m_ctx.uc_stack.ss_size = m_stackSize;

        makecontext(&m_ctx, MainFun, 0);

        LUNAR_LOG_DEBUG(g_logger) << "Fiber::Fiber(...)id=" << m_id;
    }
    Fiber::Fiber(){
        s_fiber_count++;
        m_id = s_fiber_id++;
        m_state = INIT;
        m_stackSize = 0;
        m_stackPtr = nullptr;

        LUNAR_ASSERT2(getcontext(&m_ctx) == 0, "getcontext(...)");
        m_ctx.uc_link = nullptr;
        m_ctx.uc_stack.ss_sp = m_stackPtr;
        m_ctx.uc_stack.ss_size = m_stackSize;

        LUNAR_LOG_DEBUG(g_logger) << "Fiber::Fiber()id=" << m_id;
    }
    Fiber::~Fiber(){
        if(m_stackPtr){
            LUNAR_ASSERT(m_state != EXEC &&
                m_state != HOLD);
            free(m_stackPtr);
        }
        if(t_fiber.get() == this){
            t_fiber.reset();
        }
        s_fiber_count--;
        //GetThis()->getId();
        LUNAR_LOG_DEBUG(LUNAR_LOG_NAME("destroy")) << "Fiber::~Fiber()id=" << m_id;
        //Thread::GetName();
    }

    void Fiber::reset(CallBackType cb){
        LUNAR_ASSERT(m_stackPtr);
        LUNAR_ASSERT(m_state == TERM
            || m_state == EXCE
            || m_state == INIT);

        m_state = INIT;
        m_cb = cb;
        LUNAR_ASSERT2(getcontext(&m_ctx) == 0, "getcontext(...)");
        m_ctx.uc_link = nullptr;
        m_ctx.uc_stack.ss_sp = m_stackPtr;
        m_ctx.uc_stack.ss_size = m_stackSize;

        makecontext(&m_ctx, MainFun, 0);

    }

    void Fiber::swapIn(){
        LUNAR_ASSERT(m_state == INIT ||
            m_state == HOLD)
        if(m_withThread){
            LUNAR_ASSERT( t_threadFiber == t_fiber &&
                t_fiber->m_state == EXEC);
            SetThis(shared_from_this());
            t_threadFiber->m_state = HOLD;
            int rt = 0;
            if((rt = swapcontext(&t_threadFiber->m_ctx, &m_ctx))){
                LUNAR_LOG_ERROR(g_logger) << "Fiber::swapIn: swapcontext(...)error rt = " 
                    << rt
                    << "fiberId = "
                    << m_id;
                throw std::logic_error("swapcontext error");
            }

            LUNAR_ASSERT( t_threadFiber == t_fiber &&
                t_fiber->m_state == EXEC);

        }else{
            LUNAR_ASSERT( Scheduler::GetScheRunFiber() == t_fiber &&
                t_fiber->m_state == EXEC);
            SetThis(shared_from_this());
            Scheduler::GetScheRunFiber()->m_state = HOLD;
            int rt = 0;
            auto raw_ptr = Scheduler::GetScheRunFiber().get();
            if((rt = swapcontext(&(raw_ptr->m_ctx), &m_ctx))){
                LUNAR_LOG_ERROR(g_logger) << "Fiber::swapIn: swapcontext(...)error rt = " 
                    << rt
                    << "fiberId = "
                    << m_id;
                throw std::logic_error("swapcontext error");
            }

            LUNAR_ASSERT( Scheduler::GetScheRunFiber() == t_fiber &&
                t_fiber->m_state == EXEC);
        }
    }
    void Fiber::swapOut(){
        LUNAR_ASSERT(m_state != EXEC &&
            m_state != INIT);
        if(m_withThread){
            LUNAR_ASSERT(t_threadFiber != t_fiber &&
                t_threadFiber->m_state == HOLD &&
                t_fiber == shared_from_this());
            SetThis(t_threadFiber);
            int rt = 0;
            if((rt = swapcontext(&m_ctx, &t_threadFiber->m_ctx))){
                LUNAR_LOG_ERROR(g_logger) << "Fiber::swapOut: swapcontext(...)error rt = " 
                    << rt
                    << "fiberId = "
                    << m_id;
                throw std::logic_error("swapcontext error");
            }
            LUNAR_ASSERT(t_threadFiber != t_fiber &&
                t_threadFiber->m_state == HOLD &&
                t_fiber == shared_from_this());
        }else{
            LUNAR_ASSERT(Scheduler::GetScheRunFiber() != t_fiber &&
                Scheduler::GetScheRunFiber()->m_state == HOLD &&
                t_fiber == shared_from_this());
            SetThis(Scheduler::GetScheRunFiber());
            int rt = 0;
            //raw_ptr这一步不可省略
            //临时对象在一行执行完才析构
            auto raw_ptr = Scheduler::GetScheRunFiber().get();
            if((rt = swapcontext(&m_ctx, &(raw_ptr->m_ctx)))){
                LUNAR_LOG_ERROR(g_logger) << "Fiber::swapOut: swapcontext(...)error rt = " 
                    << rt
                    << "fiberId = "
                    << m_id;
                throw std::logic_error("swapcontext error");
            }
            LUNAR_ASSERT(Scheduler::GetScheRunFiber() != t_fiber &&
                Scheduler::GetScheRunFiber()->m_state == HOLD &&
                t_fiber == shared_from_this());
        }
    }

    void Fiber::MainFun(){
        Fiber::ptr cur = GetThis();
        LUNAR_ASSERT(cur != t_threadFiber);

        try{
            cur->m_cb();

            cur->m_state = TERM;
        }catch(std::exception& e){
            LUNAR_LOG_ERROR(g_logger) << "Fiber::MainFun() : exception:" 
                << e.what();
                cur->m_state = EXCE;
        }catch(...){
            LUNAR_LOG_ERROR(g_logger) << "Fiber::MainFun() : unknow exception。" ;
            cur->m_state = EXCE;
        }

        auto raw_ptr = cur.get();
        cur.reset();
        raw_ptr->swapOut();

        LUNAR_ASSERT2(false, "never reach fiber_id=" + std::to_string(raw_ptr->getId()));
    }
    void Fiber::YieldToHold(){
        Fiber::ptr cur = GetThis();
        cur->m_state = HOLD;

        cur->swapOut();
    }
    Fiber::ptr Fiber::GetThis(){
        if(t_fiber){
            return t_fiber;
        }

        LUNAR_ASSERT(t_threadFiber == nullptr);
        Fiber::ptr mainFiber(new Fiber());

        t_threadFiber = mainFiber;
        SetThis(mainFiber);
        return t_fiber;
    }
    void Fiber::SetThis(Fiber::ptr fiberPtr){
        LUNAR_ASSERT(fiberPtr != nullptr &&
            (fiberPtr->m_state == INIT ||
            fiberPtr->m_state == HOLD));
        t_fiber = fiberPtr;
        fiberPtr->m_state = EXEC;
    }

    uint32_t Fiber::GetFiberId(){
        if(t_fiber != nullptr){
            return t_fiber->getId();
        }else{
            return UINT32_MAX;
        }
    }
}