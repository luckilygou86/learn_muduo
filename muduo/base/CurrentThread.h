// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include "muduo/base/Types.h"

namespace muduo
{
namespace CurrentThread
{
  // internal
  //__thread 修饰的变量是线程局部储存的 __thread 修饰的话是每个线程范围内的全局变量，每个线程都有一份
  //__thread 只能修饰POD类型（与c兼容的原始数据。但是用户自定义的构造函数或虚函数不是
  extern __thread int t_cachedTid;      //线程真实pid（tid）的缓存 是为了减少::syscall(SYS_gettid)系统调用
  extern __thread char t_tidString[32]; //这是tid的字符串表示形式
  extern __thread int t_tidStringLength;
  extern __thread const char* t_threadName; //每个线程的名称
  void cacheTid();

  inline int tid()
  {
    if (__builtin_expect(t_cachedTid == 0, 0))
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline int tidStringLength() // for logging
  {
    return t_tidStringLength;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();

  void sleepUsec(int64_t usec);  // for testing

  string stackTrace(bool demangle);
}  // namespace CurrentThread
}  // namespace muduo

#endif  // MUDUO_BASE_CURRENTTHREAD_H
