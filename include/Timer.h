#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include "TimeStamp.h"
#include "noncopyable.h"

class Timer : noncopyable{
public:
    using TimerCallback = std::function<void()>;

    Timer(TimerCallback cb, TimeStamp when, double interval)
    :callback_(move(cb)),
     expiration_(when),
     interval_(interval),
     repeat_(interval > 0.0) {}

     void run()const{
        callback_(); // 执行定时器回调函数
     }

     TimeStamp expiration() const {
        return expiration_; // 返回定时器到期时间
     }

     bool repeat() const {
        return repeat_; // 返回定时器是否重复执行
     }

     void restart(TimeStamp now);

private:
    const TimerCallback callback_; // 定时器回调函数
    TimeStamp expiration_; // 定时器到期时间
    const double interval_; // 定时器间隔时间
    const bool repeat_; // 是否重复执行
};

#endif
