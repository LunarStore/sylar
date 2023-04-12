#include "base/log.h"


namespace lunar{
    struct LogIniter{
        LogIniter(){
            init();
        }
        void init(){
            Logger::ptr logger;
            #define XX(name, logger) \
            logger.reset(new Logger(name)); \
            logger->addAppender(LogAppender::ptr(new StdoutLogAppender())); \
            logger->addAppender(LogAppender::ptr(new FileLogAppender())); \
            loggerMgr::GetInstance()->addLogger(name, logger)

            XX("system", logger);
            #undef XX

            #define XX(name, logger) \
            logger.reset(new Logger("destroy"));\
            logger->setFormatter(LogFormatter::ptr(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%F%T[%p]%T[%c]%T%f:%l%T%m%n")));\
            logger->addAppender(LogAppender::ptr(new StdoutLogAppender()));\
            loggerMgr::GetInstance()->addLogger(name, logger)


            XX("destroy", logger);
            #undef XX
        }
    };

    class FileFormatItem : public LogFormatter::FormatItem{
    public:
        FileFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getFile();
        }
    };

    class LineFormatItem : public LogFormatter::FormatItem{
    public:
        LineFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getLine();
        }
    };

    class ElapseFormatItem : public LogFormatter::FormatItem{
    public:
        ElapseFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getElapse();
        }
    };

    class ThreadIdFormatItem : public LogFormatter::FormatItem{
    public:
        ThreadIdFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getThreadId();
        }
    };

    class FiberIdFormatItem : public LogFormatter::FormatItem{
    public:
        FiberIdFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getFiberId();
        }
    };

    class TimeFormatItem : public LogFormatter::FormatItem{
    public:
        TimeFormatItem(const std::string& str = "%Y-%m-%d %H:%M:%S"): m_fmt(str){
            if(str.empty()){
                m_fmt.assign("%Y-%m-%d %H:%M:%S");
            }
        };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            struct tm tm;
            time_t time = event->getTimeStamp();
            localtime_r(&time, &tm);
            char buf[64];
            strftime(buf, sizeof(buf), m_fmt.c_str(), &tm);
            os << buf;
        }
    private:
        std::string m_fmt;
    };

    class ThreadNameFormatItem : public LogFormatter::FormatItem{
    public:
        ThreadNameFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getThreadName();
        }
    };

    class MessageFormatItem : public LogFormatter::FormatItem{
    public:
        MessageFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getMsg().str();
        }
    };

    class LevelFormatItem : public LogFormatter::FormatItem{
    public:
        LevelFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << LogLevel::ToString(event->getLevel());
        }
    };

    class TabFormatItem : public LogFormatter::FormatItem{
    public:
        TabFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << "\t";
        }
    };

    class NewLineFormatItem : public LogFormatter::FormatItem{
    public:
        NewLineFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << std::endl;
        }
    };

    class StringFormatItem : public LogFormatter::FormatItem{
    public:
        StringFormatItem(const std::string& str): m_string(str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << m_string;
        }
    private:
        std::string m_string;
    };

    class LoggerNameFormatItem : public LogFormatter::FormatItem{
    public:
        LoggerNameFormatItem(const std::string& str) {  };
        virtual void format(LogEvent::ptr event, std::ostream& os) override{
            os << event->getLogger()->getName();
        }
    };
    const std::string LogLevel::ToString(LogLevel::Level level){
        switch(level){
            #define XX(level) \
            case Level::level: \
                return #level; \
                break;

            XX(DEBUG)
            XX(INFO)
            XX(WARONG)
            XX(ERROR)
            XX(FATAL)
            #undef XX

            default: 
                return "UNKNOW";
        }
        return "UNKNOW";
    }

    LogEvent::LogEvent(
        const char* file,
        uint32_t line,
        uint32_t elapse,
        uint32_t threadId,
        uint32_t fiberId,
        uint64_t timeStamp,
        const std::string& threadName,
        LogLevel::Level level,
        Logger::ptr logger
    ):m_file(file),
    m_line(line),
    m_elapse(elapse),
    m_threadId(threadId),
    m_fiberId(fiberId),
    m_timeStamp(timeStamp),
    m_threadName(threadName),
    m_level(level),
    m_logger(logger){
    
    }

    LogEventWrap::LogEventWrap(LogEvent::ptr event):
        m_event(event){
    }

    LogEventWrap::~LogEventWrap(){
        m_event->getLogger()->log(m_event);
    }
    
    LogFormatter::LogFormatter(const std::string pattern):
        m_pattern(pattern){
        init();
    }

    std::stringstream& LogEventWrap::getMsg(){
        return m_event->getMsg();
    }

    //%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n
    void LogFormatter::init(){
        std::vector<std::tuple<std::string, std::string>> res;
        int len = m_pattern.length();

        //state -- 0 普通字符部分/日志修饰字符
        //state -- 1 格式化字符部分
        //state -- 2 格式化字符参数部分
        int pLt = 0, pRt = 0, state = 0 ;

        //'\0'看成万能字符
        while(pRt <= len){
            if(state == 0){
                //状态升级
                if(pRt == len || m_pattern[pRt] == '%'){
                    if(pLt < pRt){
                        res.push_back(std::make_tuple("s", m_pattern.substr(pLt, pRt - pLt)));
                    }
                    state = 1;  //升级
                    pLt = pRt + 1;
                }
            }else if(state == 1){
                //状态还原 或 状态升级 
                //或 此时遇到非{，非%，非字母的字符，则隐式代表格式化字符部分结束
                if(pRt < len && m_pattern[pRt] == '{'){
                    if(pLt < pRt){
                        res.push_back(std::make_tuple(m_pattern.substr(pLt, pRt - pLt), ""));
                    }else{
                        //错误：没有模式字符只有选项参数
                        res.push_back(std::make_tuple("s", "<parse error> empty format character : "));
                    }
                    state = 2;
                    pLt = pRt + 1;
                }
                else if(pRt < len && m_pattern[pRt] == '%'){
                    if(pLt < pRt){
                        res.push_back(std::make_tuple(m_pattern.substr(pLt, pRt - pLt), ""));
                    }
                    state = 0;
                    pLt = pRt;
                    continue;
                }else if(pRt == len || !isalpha(m_pattern[pRt])){
                    if(pLt < pRt){
                        res.push_back(std::make_tuple(m_pattern.substr(pLt, pRt - pLt), ""));
                    }
                    state = 0;
                    pLt = pRt;
                }
            }else{  //state == 2
                //状态还原
                //缺少}，结尾（"\0"）默认为'}'
                if(pRt == len || m_pattern[pRt] == '}'){
                    std::get<1>(res.back()) = std::get<1>(res.back()) + m_pattern.substr(pLt, pRt - pLt);
                    state = 0;
                    pLt = pRt + 1;
                }
            }
            pRt++;
        }

        // for(int i = 0; i < res.size(); i++){
        //     std::cout << "(" << std::get<0>(res[i]) << ")" 
        //         << "(" << std::get<1>(res[i]) << ")" 
        //         << std::endl;
        // }

        static std::unordered_map<std::string, std::function<FormatItem::ptr(const std::string&)>> fmt_fun = {
            #define XX(fmt, item) \
                {fmt, [](const std::string& str)->FormatItem::ptr { return FormatItem::ptr(new item(str)); }},
            XX("s", StringFormatItem)
            XX("d", TimeFormatItem)
            XX("t", ThreadIdFormatItem)
            XX("N", ThreadNameFormatItem)
            XX("f", FiberIdFormatItem)
            XX("p", LevelFormatItem)
            XX("c", LoggerNameFormatItem)
            XX("F", FileFormatItem)
            XX("l", LineFormatItem)
            XX("m", MessageFormatItem)
            XX("T", TabFormatItem)
            XX("n", NewLineFormatItem)

            #undef XX
        };

        for(auto it : res){
            std::string fmt = std::get<0>(it);
            std::string str = std::get<1>(it);
            auto pos = fmt_fun.find(fmt);
            if(pos == fmt_fun.end()){
                //错误的fmt
                m_items.push_back(fmt_fun["s"]("<parse error> Unrecognized format"));
            }else{
                m_items.push_back(pos->second(str));
            }
        }
    }

    void LogFormatter::format(LogEvent::ptr event, std::ostream& os){
        std::stringstream ss;
        for(auto it : m_items){
            it->format(event, ss);
        }
        os << ss.str();
    }

    Logger::Logger(const std::string& name):
        m_name(name){
        m_formatter.reset(new LogFormatter());
    }
    void Logger::log(LogEvent::ptr event){
        MutexType::ReadLock lock(m_mutex);
        if(m_level <= event->getLevel()){
            for(auto it : m_Appenders){
                it->log(event);
            }
        }
    }
    void Logger::addAppender(LogAppender::ptr apd){
            MutexType::WriteLock lock(m_mutex);
            auto itr = std::find(m_Appenders.begin(), m_Appenders.end(), apd);
            if(itr == m_Appenders.end()){
                if(apd->getFormatter() == nullptr){
                    apd->setFormatter(m_formatter);
                }
                m_Appenders.push_back(apd);
            }
    }
    void Logger::delAppender(LogAppender::ptr apd){
        MutexType::WriteLock lock(m_mutex);
        auto itr = std::find(m_Appenders.begin(), m_Appenders.end(), apd);
        if(itr != m_Appenders.end()){
            m_Appenders.erase(itr);
        }
    }
    LogFormatter::ptr Logger::getFormatter() {
        MutexType::ReadLock lock(m_mutex);
        return m_formatter; 
    }

    void Logger::setFormatter(LogFormatter::ptr fmt) {
        MutexType::WriteLock lock(m_mutex);
        m_formatter = fmt;
    }

    std::string Logger::getName() {
        MutexType::ReadLock lock(m_mutex);
        return m_name;
    }

    void Logger::setName(const std::string& name) {
        MutexType::WriteLock lock(m_mutex);
        m_name = name;
    }

    LogFormatter::ptr LogAppender::getFormatter() {
        MutexType::Lock lock(m_mutex);
        return m_formatter;
    }
    void LogAppender::setFormatter(LogFormatter::ptr fmt) {
        MutexType::Lock lock(m_mutex);
        m_formatter = fmt;
    }
    FileLogAppender::FileLogAppender(const char* name):
        m_name(name){
        reopen();
    }
    void FileLogAppender::reopen(){
        if(m_of){
            m_of.close();
        }
        m_of.open(m_name, std::ios::out| std::ios::app);
    }

    void FileLogAppender::log(LogEvent::ptr event){
        MutexType::Lock lock(m_mutex);
        reopen();
        if(m_level <= event->getLevel()){
            m_formatter->format(event, m_of);
        }
    }

    FileLogAppender::~FileLogAppender(){
        if(m_of){
            m_of.close();
        }
    }


    void StdoutLogAppender::log(LogEvent::ptr event){
        MutexType::Lock lock(m_mutex);
        if(m_level <= event->getLevel()){
            m_formatter->format(event, std::cout);
        }
    }

    LoggerManager::LoggerManager(){

        m_root.reset(new Logger("root"));
        m_root->addAppender(LogAppender::ptr(new StdoutLogAppender()));

        addLogger("root", m_root);
    }

    Logger::ptr LoggerManager::getRoot(){
        return m_root;
    }

    Logger::ptr LoggerManager::getLoggerByName(const std::string& name){
        static struct LogIniter __log_init;
        MutexType::ReadLock lock(m_mutex);
        auto pos = m_loggers.find(name);
        if(pos == m_loggers.end()){
            return m_root;
        }
        return m_loggers[name];
    }

    void LoggerManager::addLogger(const std::string& name, Logger::ptr logger){
        MutexType::WriteLock lock(m_mutex);
        auto pos = m_loggers.find(name);
        if(pos != m_loggers.end()){
            return;
        }
        m_loggers.insert({name, logger});
    }


}


