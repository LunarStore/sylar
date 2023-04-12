/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-02-01 10:22
 * LastModified : 2023-02-01 10:22
 * Filename : macro.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_MACRO_H__
#define __LUNAR_MACRO_H__

#include <string.h>
#include <assert.h>
#include "base/log.h"
#include "base/util.h"

/// 断言宏封装
#define LUNAR_ASSERT(x) \
    if(!(x)) { \
        LUNAR_LOG_ERROR(LUNAR_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << lunar::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

/// 断言宏封装
#define LUNAR_ASSERT2(x, w) \
    if(!(x)) { \
        LUNAR_LOG_ERROR(LUNAR_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << lunar::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#endif
