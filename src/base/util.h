/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-01-26 18:03
 * LastModified : 2023-01-26 18:03
 * Filename : util.h
 * Description : 1.0
 ************************************/

#ifndef __LUNAR_UTIL_H__

#define __LUNAR_UTIL_H__

#include <sys/types.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <unistd.h>
#include <cxxabi.h>
#include<string>
#include<vector>
#include <execinfo.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>
#include <boost/lexical_cast.hpp>


#include"base/log.h"
#include"base/fiber.h"
namespace lunar{
    pid_t GetThreadId();

    uint32_t GetFiberId();
    uint32_t GetElapse();


    /**
     * @brief 获取当前的调用栈
     * @param[out] bt 保存调用栈
     * @param[in] size 最多返回层数
     * @param[in] skip 跳过栈顶的层数
     */
    void Backtrace(std::vector<std::string>& bt, int size = 64, int skip = 1);

    /**
     * @brief 获取当前栈信息的字符串
     * @param[in] size 栈的最大层数
     * @param[in] skip 跳过栈顶的层数
     * @param[in] prefix 栈信息前输出的内容
     */
    std::string BacktraceToString(int size = 64, int skip = 2, const std::string& prefix = "");

    template<class T>
    const char* TypeToName() {
        static const char* s_name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
        return s_name;
    }
    std::string Time2Str(time_t ts = time(0), const std::string& format = "%Y-%m-%d %H:%M:%S");

    uint64_t GetCurrentMiliSTime();

    template<class V, class Map, class K>
    V GetParamValue(const Map& m, const K& k, const V& def = V()) {
        auto it = m.find(k);
        if(it == m.end()) {
            return def;
        }
        try {
            return boost::lexical_cast<V>(it->second);
        } catch (...) {
        }
        return def;
    }

    class StringUtil {
    public:

        static std::string UrlEncode(const std::string& str, bool space_as_plus = true);
        static std::string UrlDecode(const std::string& str, bool space_as_plus = true);

        static std::string Trim(const std::string& str, const std::string& delimit = " \t\r\n");
        static std::string TrimLeft(const std::string& str, const std::string& delimit = " \t\r\n");
        static std::string TrimRight(const std::string& str, const std::string& delimit = " \t\r\n");

        static std::string WStringToString(const std::wstring& ws);
        static std::wstring StringToWString(const std::string& s);

    };

    class FSUtil {
    public:
        static void ListAllFile(std::vector<std::string>& files
                                ,const std::string& path
                                ,const std::string& subfix);
    };
}

#endif