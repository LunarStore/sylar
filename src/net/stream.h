/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-02-27 15:24
 * LastModified : 2023-02-27 15:24
 * Filename : stream.h
 * Description : copy sylar
 ************************************/

#ifndef __LUNAR_STREAM_H__
#define __LUNAR_STREAM_H__

#include <memory>
#include "net/bytearray.h"

namespace lunar {

    /**
     * @brief 流结构
     */
    class Stream {
    public:
        typedef std::shared_ptr<Stream> ptr;
        /**
         * @brief 析构函数
         */
        virtual ~Stream() {}

        /**
         * @brief 读数据
         * @param[out] buffer 接收数据的内存
         * @param[in] length 接收数据的内存大小
         * @return
         *      @retval >0 返回接收到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int read(void* buffer, size_t length) = 0;

        /**
         * @brief 读数据
         * @param[out] ba 接收数据的ByteArray
         * @param[in] length 接收数据的内存大小
         * @return
         *      @retval >0 返回接收到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int read(ByteArray::ptr ba, size_t length) = 0;

        /**
         * @brief 读固定长度的数据
         * @param[out] buffer 接收数据的内存
         * @param[in] length 接收数据的内存大小
         * @return
         *      @retval >0 返回接收到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int readFixSize(void* buffer, size_t length);

        /**
         * @brief 读固定长度的数据
         * @param[out] ba 接收数据的ByteArray
         * @param[in] length 接收数据的内存大小
         * @return
         *      @retval >0 返回接收到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int readFixSize(ByteArray::ptr ba, size_t length);

        /**
         * @brief 写数据
         * @param[in] buffer 写数据的内存
         * @param[in] length 写入数据的内存大小
         * @return
         *      @retval >0 返回写入到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int write(const void* buffer, size_t length) = 0;

        /**
         * @brief 写数据
         * @param[in] ba 写数据的ByteArray
         * @param[in] length 写入数据的内存大小
         * @return
         *      @retval >0 返回写入到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int write(ByteArray::ptr ba, size_t length) = 0;

        /**
         * @brief 写固定长度的数据
         * @param[in] buffer 写数据的内存
         * @param[in] length 写入数据的内存大小
         * @return
         *      @retval >0 返回写入到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int writeFixSize(const void* buffer, size_t length);

        /**
         * @brief 写固定长度的数据
         * @param[in] ba 写数据的ByteArray
         * @param[in] length 写入数据的内存大小
         * @return
         *      @retval >0 返回写入到的数据的实际大小
         *      @retval =0 被关闭
         *      @retval <0 出现流错误
         */
        virtual int writeFixSize(ByteArray::ptr ba, size_t length);

        /**
         * @brief 关闭流
         */
        virtual void close() = 0;
    };

}

#endif
