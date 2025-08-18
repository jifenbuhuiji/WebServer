#include "Timer.h"

void Timer::restart(TimeStamp now) {
    if (repeat_) {
        expiration_ = addTime(now, interval_); // 如果是重复定时器，重新计算到期时间
    } else {
        expiration_ = TimeStamp::invalid(); // 如果不是重复定时器，将到期时间设置为无效
    }
}