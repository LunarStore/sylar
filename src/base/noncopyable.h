/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-03-02 14:55
 * LastModified : 2023-03-02 14:55
 * Filename : noncopyable.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_NONCOPYABLE_H__
#define __LUNAR_NONCOPYABLE_H__

namespace lunar {

/**
 * @brief 对象无法拷贝,赋值
 */
class Noncopyable {
public:
    /**
     * @brief 默认构造函数
     */
    Noncopyable() = default;

    /**
     * @brief 默认析构函数
     */
    ~Noncopyable() = default;

    /**
     * @brief 拷贝构造函数(禁用)
     */
    Noncopyable(const Noncopyable&) = delete;

    /**
     * @brief 赋值函数(禁用)
     */
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}

#endif