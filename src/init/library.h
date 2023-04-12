/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-03-05 10:32
 * LastModified : 2023-03-05 10:32
 * Filename : library.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_LIBRARY_H__
#define __LUNAR_LIBRARY_H__

#include <memory>
#include "init/module.h"

namespace lunar {

    class Library {
    public:
        static Module::ptr GetModule(const std::string& path);
    };

}

#endif
